#pragma once
#include <Platform/SkPlatform.h>


namespace SK
{
	/**
	 * \struct	ImageInfos
	 *
	 * \brief	Image information. 
	 */

	struct IISUSDK_API ImageInfos
	{
		/**
		 * \enum	ImageDepthEnum
		 *
		 * \brief	Depth of the image. 
		 */

		enum ImageDepthEnum {
			IMAGE_DEPTH_1U,
			IMAGE_DEPTH_8U,
			IMAGE_DEPTH_8S,
			IMAGE_DEPTH_16U,
			IMAGE_DEPTH_16S,
			IMAGE_DEPTH_32S,
			IMAGE_DEPTH_32F,
			IMAGE_DEPTH_MAX
		};

		/**
		 * \enum	PixelTypeEnum
		 *
		 * \brief	Pixel Types. 
		 */

		enum IISUSDK_API PixelTypeEnum {
			GRAY_PIXEL,
			RGB_PIXEL,
			RGBA_PIXEL,
			ARGB_PIXEL,
			ABGR_PIXEL,
			BGRA_PIXEL,
			YUV422_PIXEL,
			CUSTOM_PIXEL
		};

		/**
		 * \fn	ImageInfos()
		 *
		 * \brief	Default constructor.
		 */

		ImageInfos() : width(0), height(0), channelsNb(0), depth(IMAGE_DEPTH_MAX), pixelType(CUSTOM_PIXEL) {}

		/**
		 * \fn	ImageInfos(uint32_t _width, uint32_t _height, uint32_t _channelsNb, ImageDepthEnum _depth,
		 * 		PixelTypeEnum _pixelType=CUSTOM_PIXEL )
		 *
		 * \brief	Constructor.
		 *
		 * \param	_width	   	The width.
		 * \param	_height	   	The height.
		 * \param	_channelsNb	The number of channels.
		 * \param	_depth	   	The depth.
		 * \param	_pixelType 	(optional) type of the pixel.
		 */

		ImageInfos(uint32_t _width, uint32_t _height, uint32_t _channelsNb, ImageDepthEnum _depth, PixelTypeEnum _pixelType=CUSTOM_PIXEL ) :
				width(_width), height(_height), channelsNb(_channelsNb), depth(_depth), pixelType(_pixelType) {} 
		
		uint32_t width, height, channelsNb;
		ImageDepthEnum depth;
		PixelTypeEnum pixelType;

		/**
		 * \fn	uint32_t bitsDepth() const
		 *
		 * \brief	Gets the number of bits per channel.
		 *
		 * \return	The number of bits per channel.
		 */

		uint32_t bitsDepth() const
		{
			static const int32_t IMAGE_DEPTH_BIT[IMAGE_DEPTH_MAX] = { 1,8,8,16,16,32,32 };
			return IMAGE_DEPTH_BIT[depth];
		}

		/**
		 * \fn	uint32_t bytesDepth() const
		 *
		 * \brief	Gets the number of bytes per channel.
		 *
		 * \return	The number of bytes per channel.
		 */

		uint32_t bytesDepth() const
		{
			static int32_t IMAGE_DEPTH_BYTE[IMAGE_DEPTH_MAX] = { 1,1,1,2,2,4,4 };
			return IMAGE_DEPTH_BYTE[depth];
		}

		/**
		 * \fn	uint32_t bytesWidth() const
		 *
		 * \brief	Gets the image's width in bytes (line stride)
		 *
		 * \return	The image's width in bytes (line stride).
		 */

		uint32_t bytesWidth() const
		{
			static int32_t IMAGE_DEPTH_BYTE[IMAGE_DEPTH_MAX] = { 1,1,1,2,2,4,4 };
			return width * channelsNb * IMAGE_DEPTH_BYTE[depth];
		}

		/**
		 * \fn	uint32_t bytesPerPixel() const
		 *
		 * \brief	Gets the number of bytes per pixel.
		 *
		 * \return	The number of bytes per pixel.
		 */

		uint32_t bytesPerPixel() const
		{
			static int32_t IMAGE_DEPTH_BYTE[IMAGE_DEPTH_MAX] = { 1,1,1,2,2,4,4 };
			return channelsNb * IMAGE_DEPTH_BYTE[depth];
		}

		/**
		 * \fn	uint32_t bytesRAW() const
		 *
		 * \brief	Gets the image's raw buffer size in bytes.
		 *
		 * \return	The image's raw buffer size in bytes.
		 */

		uint32_t bytesRAW() const
		{
			static int32_t IMAGE_DEPTH_BYTE[IMAGE_DEPTH_MAX] = { 1,1,1,2,2,4,4 };
			return width * height * channelsNb * IMAGE_DEPTH_BYTE[depth];
		}

		/**
		 * \fn	uint32_t pixels() const
		 *
		 * \brief	Gets the number of pixels.
		 *
		 * \return	The number of pixels.
		 */

		uint32_t pixels() const
		{
			return width * height ;
		}

		/**
		 * \fn	bool isFloating()
		 *
		 * \brief	Query if image format is using floating point values.
		 *
		 * \return	true if floating, false if not.
		 */

		bool isFloating() { return depth == IMAGE_DEPTH_32F;}

		/**
		 * \fn	bool operator!=(const ImageInfos& infos)
		 *
		 * \brief	Compare two image information.
		 *
		 * \param	infos	The other ImageInfos.
		 */

		bool operator!=(const ImageInfos& infos)const
		{
			if (infos.width != width || infos.height != height || infos.channelsNb != channelsNb || infos.depth != depth || infos.pixelType != pixelType)
			{
				return true;
			}
			return false;
		}

		/**
		 * \fn	const char* imageTypeString() const
		 *
		 * \brief	Gets the type of depth as a string.
		 *
		 * \return	The type of depth as a string, empty string if unknown.
		 */

		const char* imageTypeString() const
		{
			switch (depth)
			{
			case IMAGE_DEPTH_1U:				return "Bool";
			case IMAGE_DEPTH_8U:				return "UChar";
			case IMAGE_DEPTH_8S:				return "Char";
			case IMAGE_DEPTH_16U:				return "UShort";
			case IMAGE_DEPTH_16S:				return "Short";
			case IMAGE_DEPTH_32S:				return "Int";
			case IMAGE_DEPTH_32F:				return "Float";
			default: break;
			}
			return "";
		}

		/**
		 * \fn	const char* pixelTypeToString() const
		 *
		 * \brief	Gets the type of pixel as a string. 
		 *
		 * \return	The type of pixel as a string, empty string if unknown. 
		 */

		const char* pixelTypeToString() const
		{
			switch(pixelType)
			{
			case GRAY_PIXEL:					return "Gray";
			case RGB_PIXEL: 					return "RGB";		
			case RGBA_PIXEL:					return "RGBA";		
			case ARGB_PIXEL:					return "ARGB";
			case ABGR_PIXEL:					return "ABGR";
			case BGRA_PIXEL:					return "BGRA";
			case YUV422_PIXEL:					return "YUV422";
			case CUSTOM_PIXEL:					return "Custom";
			}
			return "";
		}
	};
}

