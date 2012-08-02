#pragma once
#include <Platform/SkPlatform.h>
#include <Foundation/DataTypes/Image/Image.h>
#include <Foundation/DataTypes/Array/Array.h>

namespace SK {

	/**
	 * \class	ColorConvertor
	 *
	 * \brief	Interface of an ARGB-32bit image color convertor. 
	 */

	class IISUSDK_API ColorConvertor
	{
	public:

		/**
		 * \fn	Image* ColorConvertor::toARGB32(const Image* srcImage) const;
		 *
		 * \brief	Converts a srcImage to an ARGB 32bit stored image.
		 *
		 * \param	srcImage	Source image.
		 *
		 * \return	The result of the operation (newly allocated image).
		 */

		Image* toARGB32(const Image* srcImage) const;

		/**
		 * \fn	virtual void ColorConvertor::toARGB32(const Image* srcImage, uint8_t* dstBuffer) const =0;
		 *
		 * \brief	Converts a srcImage to an ARGB 32bit stored image.
		 *
		 * \param	srcImage		 	Source image.
		 * \param [out]	dstBuffer	buffer for destination data.
		 */

		virtual void toARGB32(const Image* srcImage, uint8_t* dstBuffer) const =0;

		/**
		 * \fn	virtual ColorConvertor::~ColorConvertor()
		 *
		 * \brief	Destructor.
		 */

		virtual ~ColorConvertor(){}
	};

	/**
	 * \class	DefaultColorConvertor
	 *
	 * \brief	Default implementation the the interface ColorConvertor. 
	 */

	class IISUSDK_API DefaultColorConvertor : public ColorConvertor 
	{
	public:

		/**
		 * \fn	void DefaultColorConvertor::toARGB32(const Image* srcImage, uint8_t* dstBuffer) const;
		 *
		 * \brief	Converts a srcImage to an ARGB 32bit stored image.
		 *
		 * \param	srcImage		 	Source image.
		 * \param [out]	dstBuffer	buffer for destination data.
		 */
		void toARGB32(const Image* srcImage, uint8_t* dstBuffer) const;
	};

	/**
	 * \class	PaletteColorConvertor
	 *
	 * \brief	Implementation of a Palette color convertor
	 * 	 
	 * 	Implementation of a palette color convertor. 
	 * 	It uses of a min/max range for mapping image values to ARGB32 colors stored in a specified color table (256 colors mandatory).  
	 */

	class IISUSDK_API PaletteColorConvertor : public ColorConvertor
	{
	public:

		/**
		 * \fn	PaletteColorConvertor::PaletteColorConvertor();
		 *
		 * \brief	Default constructor.
		 *		 Initializes min,max and shift to 0, palette to NULL
		 */

		PaletteColorConvertor();

		/**
		 * \fn	PaletteColorConvertor::PaletteColorConvertor(int32_t minValue, int32_t maxValue,
		 * 		SK::Color4c* palette=NULL, uint32_t shift=0);
		 *
		 * \brief	Explicit constructor.
		 *
		 * \param	minValue	The minimum value.
		 * \param	maxValue	The maximum value.
		 * \param	palette 	(optional) [in] the palette color table.
		 * \param	shift   	(optional) the bit shift.
		 */

		PaletteColorConvertor(int32_t minValue, int32_t maxValue, SK::Array<SK::Color4c> palette, uint32_t shift=0);

		/**
		 * \fn	void PaletteColorConvertor::toARGB32(const Image* srcImage, uint8_t* dstBuffer) const;
		 *
		 * \brief	Converts a srcImage to an ARGB 32bit stored image.
		 *
		 * \param	srcImage		 	Source image.
		 * \param [out]	dstBuffer	    buffer for destination data (at least same size as srcImage).
		 *		  
		 *	supported conversions:
		 *		 1 channel 8 bits unsigned -> direct mapping through the color table  
		 *		 1 channel 16 bits unsigned	-> bitshifted mapping through the color table according to range
		 *		 1 channel 16 bits (un)signed -> bitshifted mapping through the color table according to range  
		 *		 1 channel 32 bits float ->	mapping through the color table according to range	 
		 */

		void toARGB32(const Image* srcImage, uint8_t* dstBuffer) const;

		/**
		 * \fn	PaletteColorConvertor& PaletteColorConvertor::operator=(const PaletteColorConvertor& other);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A shallow copy of this object.
		 */

		PaletteColorConvertor& operator=(const PaletteColorConvertor& other);

		/**
		 * \fn	void PaletteColorConvertor::setRange(int32_t minValue, int32_t maxValue);
		 *
		 * \brief	Sets the range.
		 *
		 * \param	minValue	The minimum value.
		 * \param	maxValue	The maximum value.
		 */

		void setRange(int32_t minValue, int32_t maxValue);

		/**
		 * \fn	int32_t PaletteColorConvertor::getMinValue() const;
		 *
		 * \brief	Gets the minimum value.
		 *
		 * \return	The minimum value.
		 */

		int32_t getMinValue() const;	

		/**
		 * \fn	int32_t PaletteColorConvertor::getMaxValue() const;
		 *
		 * \brief	Gets the maximum value.
		 *
		 * \return	The maximum value.
		 */

		int32_t getMaxValue() const;	

		/**
		 * \fn	uint32_t PaletteColorConvertor::getBitShift() const;
		 *
		 * \brief	Gets the bit shift.
		 *
		 * \return	The bit shift.
		 */

		uint32_t getBitShift() const;

		/**
		 * \fn	SK::Color4c* PaletteColorConvertor::getPalette() const;
		 *
		 * \brief	Gets the palette.
		 *
		 * \return	the palette.
		 */

		SK::Array<SK::Color4c> getPalette() const;

	private:
	
		SK::Array<SK::Color4c> m_palette;
		uint32_t m_bitsShift;// Shift if 16 bits
		int32_t m_minValue;
		int32_t m_maxValue;
	};
}