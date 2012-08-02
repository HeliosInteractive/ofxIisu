#pragma once
#include <assert.h>
#include <string.h>    // for memcpy
#include <Platform/SkPlatform.h>
#include <Foundation/DataTypes/Color/Color.h>
#include <Framework/Instances/SharedPtr.h>
#include <Foundation/DataTypes/Image/ImageInfos.h>
#include <Foundation/DataTypes/Geometry/Vector2i.h>

namespace SK {

	/**
	 * \class	Image
	 *
	 * \brief	Class implementing a 2D Image. 
	 */

	class IISUSDK_API Image 
	{
	public:
		
		/**
		 * \fn	Image::Image();
		 *
		 * \brief	Default constructor.
		 */

		Image();

		/**
		 * \fn	Image::Image(const ImageInfos& infos, uint8_t align=16);
		 *
		 * \brief	Constructor.
		 *
		 * \param	infos	The image information attribute.
		 * \param	align	(optional) the number of bytes the memory address of the image buffer  must be aligned on.	
		 */

		Image(const ImageInfos& infos, uint8_t align=16);
		
		/**
		 * \fn	Image::Image(const Image& img);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	img	The image.
		 */

		Image(const Image& img);
		
		/**
		 * \fn	SK::ImageInfos Image::getImageInfos() const;
		 *
		 * \brief	Gets the image infos.
		 *
		 * \return	The image infos.
		 */

		SK::ImageInfos getImageInfos() const;

		/**
		 * \fn	uint8_t* Image::getRAW() const;
		 *
		 * \brief	Gets the image raw buffer.
		 *
		 * \return	The image raw buffer.
		 */

		uint8_t* getRAW() const;
		
		/**
		 * \fn	void Image::resize(uint32_t width, uint32_t height, bool forceReallocation,
		 * 		uint8_t align=16);
		 *
		 * \brief	Resizes images raw buffer.
		 *
		 * \param	width			 	The new image width (pixels).
		 * \param	height			 	The new image height (pixels).
		 * \param	forceReallocation	true to force reallocation. 
		 * 		 						Will delete old buffer and recreate a new one even if size is smaller.
		 * \param	align			 	(optional) the number of bytes the memory address of the image buffer must be aligned on.
		 */

		void resize(uint32_t width, uint32_t height, bool forceReallocation, uint8_t align=16);

		/**
		 * \fn	void Image::resize(const ImageInfos& infos, bool forceReallocation, uint8_t align=16);
		 *
		 * \brief	Resizes images raw buffer according to new image information attribute (number of pixels and image depth).
		 *
		 * \param	infos			 	The new image information attribute.
		 * \param	forceReallocation	true to force reallocation. 
		 * 		 						Will delete old buffer and recreate a new one even if size is smaller.
		 * \param	align			 	(optional) the number of bytes the memory address of the image buffer must be aligned on.
		 */
		void resize(const ImageInfos& infos, bool forceReallocation, uint8_t align=16);

		/**
		 * \fn	void Image::reset(uint8_t aucResetValue);
		 *
		 * \brief	Resets the image raw buffer to the given value.
		 *
		 * \param	aucResetValue	The reset value.
		 */

		void reset(uint8_t aucResetValue);

		/**
		 * \fn	uint32_t Image::operator()(uint32_t x, uint32_t y) const;
		 *
		 * \brief	Gets global index from pixel position
		 * \param	x pixel's x position
		 * \param	y pixel's y position
		 * \remark   no assert version
		 */

		uint32_t operator()(uint32_t x, uint32_t y) const;
		
		/**
		 * \fn	uint32_t Image::at(uint32_t x, uint32_t y) const;
		 *
		 * \brief	Gets global index from pixel position
		 *		  
		 * \param x pixel's x position
		 *		  
		 * \param y pixel's y position
		 *		  
		 * \remark   asserted version
		 */

		uint32_t at(uint32_t x, uint32_t y) const;

		/**
		 * \fn	Vector2i Image::operator()(uint32_t index) const;
		 *
		 * \brief	Gets pixel position from global index
		 * 
		 * \param  index global index
		 *		 
		 * \return  the pixel position 
		 *		 
		 * \remark   non asserted version  
		 */

		Vector2i operator()(uint32_t index) const;
		
		/*
		* \brief return pixel position from global index.
		* \param	index global index
		* \remark   no assert version
		*/

		/**
		 * \fn	Vector2i Image::at(uint32_t index) const;
		 *
		 * \brief	Gets pixel position from global index
		 *
		 * \param	 index global index
		 *
		 * \return  the pixel position 
		 *		 
		 */

		Vector2i at(uint32_t index) const;
		
		
		/**
		 * \fn	void Image::writePixel (int32_t x, int32_t y, const T& pix )
		 *
		 * \brief	Writes a pixel.
		 *
		 * \tparam T pixel type
		 *		 
		 * \param	x  	The x coordinate.
		 * \param	y  	The y coordinate.
		 * \param	pix	The pixel data.
		 */

		template <typename T>
		void writePixel (int32_t x, int32_t y, const T&  pix )
		{
			((T*)getRAW())[x+y*m_infos.width] = pix;
		}
		
		/**
		 * \fn	const T& Image::readPixel (int32_t x, int32_t y) const
		 *
		 * \brief	Reads a pixel.
		 *
		 * \tparam T pixel type
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 *
		 * \return	The pixel data.
		 */
		template <typename T>
		const T& readPixel (int32_t x, int32_t y) const
		{
			return ((T*)getRAW())[x+y*m_infos.width];
		}
		Image& operator=(const Image& img);
		
		~Image();
				
	private:
			
		ImageInfos m_infos;
		uint8_t *m_imageData;
		uint8_t m_align;
		
	};

	/**
	* \fn	inline void copyImage(const Image* pSource, Image* pDestination)
	*
	* \brief	Copies an image
	* \param	pSource					source image.
	* \param [in,out]	pDestination	destination image.
	* \remark source and destination images must have same image information,
	*         and already be allocated in memory.
	*/
	inline void copyImage(const Image* pSource, Image* pDestination)
	{
        pDestination->resize(pSource->getImageInfos(),false);
		uint32_t sourceBytesSize = pSource->getImageInfos().bytesRAW();
		assert(sourceBytesSize <= pDestination->getImageInfos().bytesRAW());
		if (sourceBytesSize){ // no need to copy if size is 0
			uint8_t* source = pSource->getRAW();
			uint8_t* destination = pDestination->getRAW();
			memcpy(destination, source, sourceBytesSize);
		}
	}
	//functions to return image size in px from default width & height

	/**
	 * \fn	uint32_t getDefaultSize(uint32_t w,uint32_t h);
	 *
	 * \brief	Gets the image size in px from default width & height.
	 *
	 * \param	w	The width.
	 * \param	h	The height.
	 *
	 * \return	The the image size in px.
	 */

	uint32_t getDefaultSize(uint32_t w,uint32_t h) ;

	
	
}
