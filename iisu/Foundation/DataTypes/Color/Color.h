

#pragma once

#include <System/Math/Math.h>
#include <ostream>

namespace SK
{
	typedef uint32_t RGBA;
	typedef uint32_t ARGB;
	typedef uint32_t ABGR;
	typedef uint32_t BGRA;

	/**
	* \class	Color4c
	*	 
	* \brief	Class representing color with 4 uint8_t = 4bytes (Red, Green, Blue, Alpha)
	* 
	*/

	class IISUSDK_API Color4c
	{
	public:
		static const Color4c BLACK;
		static const Color4c BLUE;
		static const Color4c CYAN;
		static const Color4c GREEN;
		static const Color4c MAGENTA;
		static const Color4c RED;
		static const Color4c WHITE;
		static const Color4c YELLOW;
		static const Color4c PURPLE;

		/**
		* \fn	explicit Color4c::Color4c(ARGB val);
		*
		* \brief	Constructor from a 32bit unsigned integer (ARGB). 
		*
		* \param	val	The value.
		*/

		explicit Color4c(ARGB val);

		/**
		* \fn	explicit Color4c::Color4c(uint8_t _r=255, uint8_t _g=255, uint8_t _b=255, uint8_t _a=255)
		*
		* \brief	Constructor.
		*
		* \param	_r	(optional) the red value.
		* \param	_g	(optional) the green value.
		* \param	_b	(optional) the blue value.
		* \param	_a	(optional) alpha value.
		*/

		explicit Color4c(uint8_t _r=255, uint8_t _g=255, uint8_t _b=255, uint8_t _a=255){ r=_r; g=_g; b=_b; a=_a; }
		uint8_t b,g,r,a;
	};

	/**
	* \class	Color4f
	*
	* \brief	Class representing color.
	*     
	*  \remark color is represented as 4 components, each of which is a
	*          floating-point value from 0.0 to 1.0.
	*	\par    
	*		    The 3 'normal' color components are red, green and blue, a higher
	*          number indicating greater amounts of that component in the color.
	*          The forth component is the 'alpha' value, which represents
	*          opacity. In this case, 0.0 is completely transparent and 1.0 is
	*          fully opaque.
	*/

	class IISUSDK_API Color4f
	{
	public:

		static const Color4f COLOR_LIST[];
		static const Color4f BLACK;
		static const Color4f BLUE;
		static const Color4f CYAN;
		static const Color4f GREEN;
		static const Color4f MAGENTA;
		static const Color4f YELLOW;
		static const Color4f RED;
		static const Color4f WHITE;
		static const Color4f GRAY;
		static const Color4f PURPLE;

		/**
		* \fn	explicit Color4f::Color4f( float red = 1.0f, float green = 1.0f, float blue = 1.0f,
		* 		float alpha = 1.0f )
		*
		* \brief	Constructor.
		*
		* \param	red  	(optional) the red value (from 0.0 to 1.0).
		* \param	green	(optional) the green value (from 0.0 to 1.0).
		* \param	blue 	(optional) the blue value (from 0.0 to 1.0). 
		* \param	alpha	(optional) the alpha value (from 0.0 to 1.0).
		*/

		explicit Color4f( float red = 1.0f,
			float green = 1.0f,
			float blue = 1.0f,
			float alpha = 1.0f ) : r(red), g(green), b(blue), a(alpha)
		{ }

		/**
		* \fn	explicit Color4f::Color4f( const Color4c& c)
		*
		* \brief	conversion constructor from a Color4c.
		*
		* \param	c	The color.
		*/

		explicit Color4f( const Color4c& c) : r(c.r/255.f), g(c.g/255.f), b(c.b/255.f), a(c.a/255.f) {}

		/**
		 * \fn	const Color4f& Color4f::operator=( const Color4c& c)
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	c	The color.
		 *
		 * \return	A shallow copy of this object.
		 */

		const Color4f& operator=( const Color4c& c) 
		{
			r = c.r/255.f; g=c.g/255.f; b=c.b/255.f; a=c.a/255.f;
			return *this;
		}

		/**
		 * \fn	bool Color4f::operator==(const Color4f& rhs) const;
		 *
		 * \brief	Equality operator.
		 *
		 * \param	rhs	The color to be compared to.
		 *
		 * \return	true if the colors are considered equivalent.
		 */

		bool operator==(const Color4f& rhs) const;

		/**
		 * \fn	bool Color4f::operator!=(const Color4f& rhs) const;
		 *
		 * \brief	Finaliser.
		 *
		 * \param	rhs	The color to be compared to.
		 *		 
		 * \return	true if the colors are not considered equivalent.
		 */

		bool operator!=(const Color4f& rhs) const;

		float r,g,b,a;

		/**
		 * \fn	RGBA Color4f::getAsRGBA(void) const;
		 *
		 * \brief	Gets the color as RGBA.
		 *
		 * \return	RGBA color.
		 */

		RGBA getAsRGBA(void) const;

		/**
		 * \fn	ARGB Color4f::getAsARGB(void) const;
		 *
		 * \brief	Gets the color as ARGB.
		 *
		 * \return	ARGB color.
		 */

		ARGB getAsARGB(void) const;

		/**
		 * \fn	BGRA Color4f::getAsBGRA(void) const;
		 *
		 * \brief	Gets the color as BGRA.
		 *
		 * \return	BGRA color.
		 */

		BGRA getAsBGRA(void) const;

		/**
		 * \fn	ABGR Color4f::getAsABGR(void) const;
		 *
		 * \brief	Gets the color as ABGR.
		 *
		 * \return	ABGR color.
		 */

		ABGR getAsABGR(void) const;

		/**
		 * \fn	void Color4f::setAsRGBA(const RGBA val);
		 *
		 * \brief	Sets the color from RGBA.
		 *
		 * \param	val	The RGBA color.
		 */

		void setAsRGBA(const RGBA val);

		/**
		 * \fn	void Color4f::setAsARGB(const ARGB val);
		 *
		 * \brief	Sets the color from ARGB.
		 *
		 * \param	val	The ARGB color.
		 */

		void setAsARGB(const ARGB val);

		/**
		 * \fn	void Color4f::setAsBGRA(const BGRA val);
		 *
		 * \brief	Sets the color from BGRA.
		 *
		 * \param	val	The BGRA color.
		 */

		void setAsBGRA(const BGRA val);

		/**
		 * \fn	void Color4f::setAsABGR(const ABGR val);
		 *
		 * \brief	Sets the color from ABGR.
		 *
		 * \param	val	The ABGR color.
		 */

		void setAsABGR(const ABGR val);

		/**
		 * \fn	void Color4f::saturate(void);
		 *
		 * \brief	Clamps color components to the range [0:1].
		 */

		void saturate(void);

		/** As saturate, except that this color value is unaffected and
		the saturated color value is returned as a copy. */

		/**
		 * \fn	Color4f Color4f::saturateCopy(void) const;
		 *
		 * \brief	Clamps a copied color components to the range [0:1] and retursn it.
		 *
		 * \return	The clamped copy color.
		 */

		Color4f saturateCopy(void) const;

		/**
		 * \fn	inline float Color4f::operator[] ( const size_t i ) const
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	i	index of the color component.
		 *
		 * \return	The indexed color component.
		 */

		inline float operator [] ( const size_t i ) const
		{
			assert( i < 4 );

			return *(&r+i);
		}

		/**
		 * \fn	inline float& Color4f::operator[] ( const size_t i )
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	i	index of the color component.
		 *
		 * \return	The indexed color component.
		 */

		inline float& operator [] ( const size_t i )
		{
			assert( i < 4 );

			return *(&r+i);
		}

		/**
		 * \fn	inline float* Color4f::ptr()
		 *
		 * \brief	Pointer accessor for direct copying.
		 *
		 * \return	A pointer to the color.
		 */

		inline float* ptr()
		{
			return &r;
		}

		/**
		 * \fn	inline float* Color4f::ptr()
		 *
		 * \brief	Pointer accessor for direct copying.
		 *
		 * \return	A pointer to the color.
		 */

		inline const float* ptr() const
		{
			return &r;
		}


		// arithmetic operations

		/**
		 * \fn	inline Color4f Color4f::operator+ ( const Color4f& color ) const
		 *
		 * \brief	Addition operator.
		 *
		 * \param	color	The color.
		 *
		 * \return	The resulted color of the addition component by component.
		 */

		inline Color4f operator + ( const Color4f& color ) const
		{
			Color4f kSum;

			kSum.r = r + color.r;
			kSum.g = g + color.g;
			kSum.b = b + color.b;
			kSum.a = a + color.a;

			return kSum;
		}

		/**
		 * \fn	inline Color4f Color4f::operator- ( const Color4f& color ) const
		 *
		 * \brief	Negation operator.
		 *
		 * \param	color	The color.
		 *
		 * \return	The resulted color of the subtraction component by component.
		 */

		inline Color4f operator - ( const Color4f& color ) const
		{
			Color4f kDiff;

			kDiff.r = r - color.r;
			kDiff.g = g - color.g;
			kDiff.b = b - color.b;
			kDiff.a = a - color.a;

			return kDiff;
		}

		/**
		 * \fn	inline Color4f Color4f::operator* (const float scalar ) const
		 *
		 * \brief	Scalar multiplication operator.
		 *
		 * \param	scalar	The scalar.
		 *
		 * \return	The resulted color of the multiplication of each component by the scalar.
		 */

		inline Color4f operator * (const float scalar ) const
		{
			Color4f kProd;

			kProd.r = scalar*r;
			kProd.g = scalar*g;
			kProd.b = scalar*b;
			kProd.a = scalar*a;

			return kProd;
		}

		/**
		 * \fn	inline Color4f Color4f::operator* ( const Color4f& rhs) const
		 *
		 * \brief	Multiplication operator.
		 *
		 * \param	rhs	The color.
		 *
		 * \return	The resulted color of the multiplication component by component.
		 */

		inline Color4f operator * ( const Color4f& rhs) const
		{
			Color4f kProd;

			kProd.r = rhs.r * r;
			kProd.g = rhs.g * g;
			kProd.b = rhs.b * b;
			kProd.a = rhs.a * a;

			return kProd;
		}

		/**
		 * \fn	inline Color4f Color4f::operator/ ( const Color4f& rhs) const
		 *
		 * \brief	Division operator.
		 *
		 * \param	rhs	The color.
		 *
		 * \return	The resulted color of the division component by component of rhs color and this color.
		 */

		inline Color4f operator / ( const Color4f& rhs) const
		{
			Color4f kProd;

			kProd.r = rhs.r / r;
			kProd.g = rhs.g / g;
			kProd.b = rhs.b / b;
			kProd.a = rhs.a / a;

			return kProd;
		}

		/**
		 * \fn	inline Color4f Color4f::operator/ (const float scalar ) const
		 *
		 * \brief	Scalar division operator.
		 *
		 * \param	scalar	The scalar.
		 *
		 * \return	The resulted color of the division of each component by the scalar.
		 */

		inline Color4f operator / (const float scalar ) const
		{
			assert( scalar != 0.0 );

			Color4f kDiv;

			float fInv = 1.0f / scalar;
			kDiv.r = r * fInv;
			kDiv.g = g * fInv;
			kDiv.b = b * fInv;
			kDiv.a = a * fInv;

			return kDiv;
		}

		/**
		 * \fn	inline friend Color4f Color4f::operator* (const float scalar, const Color4f& color )
		 *
		 * \brief	Multiplication operator.
		 *
		 * \param	scalar	The first value to multiply.
		 * \param	color 	The second value to multiply.
		 *
		 * \return	The resulted color of the multiplication component by component.
		 */

		inline friend Color4f operator * (const float scalar, const Color4f& color )
		{
			Color4f kProd;

			kProd.r = scalar * color.r;
			kProd.g = scalar * color.g;
			kProd.b = scalar * color.b;
			kProd.a = scalar * color.a;

			return kProd;
		}

		// arithmetic updates

		/**
		 * \fn	inline Color4f& Color4f::operator+= ( const Color4f& color )
		 *
		 * \brief	Addition assignment operator.
		 *
		 * \param	color	The color.
		 *
		 * \return	The resulted color of the addition component by component.
		 */

		inline Color4f& operator += ( const Color4f& color )
		{
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;

			return *this;
		}

		/**
		 * \fn	inline Color4f& Color4f::operator-= ( const Color4f& color )
		 *
		 * \brief	Subtraction assignment operator.
		 *
		 * \param	color	The color.
		 *
		 * \return	The resulted color of the subtraction component by component.
		 */

		inline Color4f& operator -= ( const Color4f& color )
		{
			r -= color.r;
			g -= color.g;
			b -= color.b;
			a -= color.a;

			return *this;
		}

		/**
		 * \fn	inline Color4f& Color4f::operator*= (const float scalar )
		 *
		 * \brief	Multiplication assignment operator.
		 *
		 * \param	scalar	The scalar.
		 *
		 * \return	The result of the multiplication of each component by a scalar.
		 */

		inline Color4f& operator *= (const float scalar )
		{
			r *= scalar;
			g *= scalar;
			b *= scalar;
			a *= scalar;
			return *this;
		}

		/**
		 * \fn	inline Color4f& Color4f::operator/= (const float scalar )
		 *
		 * \brief	Division assignment operator.
		 *
		 * \param	scalar	The scalar.
		 *
		 * \return	The result of the division of each component by a scalar.
		 */

		inline Color4f& operator /= (const float scalar )
		{
			assert( scalar != 0.0f );

			float fInv = 1.0f / scalar;

			r *= fInv;
			g *= fInv;
			b *= fInv;
			a *= fInv;

			return *this;
		}

		/**
		 * \fn	void Color4f::setHSB(float hue, float saturation, float brightness);
		 *
		 * \brief	Set a color value from Hue, Saturation and Brightness.
		 *
		 * \param	hue		  	The Hue value, scaled to the [0,1] range as opposed to the 0-360
		 * \param	saturation	The Saturation level, [0,1]
		 * \param	brightness	The Brightness level, [0,1]
		 */

		void setHSB(float hue, float saturation, float brightness);

		/**
		 * \fn	void Color4f::getHSB(float* hue, float* saturation, float* brightness) const;
		 *
		 * \brief	Convert the current color to Hue, Saturation and Brightness values.
		 *
		 * \param [out]	hue		  	The Hue value, scaled to the [0,1] range as opposed to the 0-360
		 * \param [out]	saturation	The Saturation level, [0,1]
		 * \param [out]	brightness	The Brightness level, [0,1]
		 */

		void getHSB(float* hue, float* saturation, float* brightness) const;

		/**
		 * \fn	inline friend std::ostream& Color4f::operator<< ( std::ostream& o, const Color4f& c )
		 *
		 * \brief	Function for writing to a stream output.
		 *
		 * \param [in,out]	o	The stream output.
		 * \param	c		 	The color.
		 *
		 * \return	Updated stream output.
		 */

		inline friend std::ostream& operator <<

			( std::ostream& o, const Color4f& c )
		{
			o << "Color4f(R:" << c.r << ", G:" << c.g << ", B:" << c.b << ", A:" << c.a << ")";
			return o;
		}

	};

} 
