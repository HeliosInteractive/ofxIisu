#include <limits>

namespace SK 
{

	//----------------------------- CONSTRUCTOR ----------------------------------
	SK_FORCE_INLINE Vector2i::Vector2i(void)
		: x(0),y(0)
	{
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i::Vector2i(int32_t xIni, int32_t yIni)
		:  x(xIni), y(yIni)
	{	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i::Vector2i(const Vector2i& other)
		: x(other.x), y(other.y)
	{
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i::Vector2i( const int32_t* pValues )
		: x( pValues[0] ), y( pValues[1] )
	{
	}

	//----------------------------- MEMBER ACCESS  -------------------------------
	SK_FORCE_INLINE int32_t& Vector2i::operator[] (int32_t i)
	{
		// assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
		return (&x)[i];
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector2i::operator[] (int32_t i) const
	{
		// assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
		return (&x)[i];
	}

	//----------------------------- assignment and comparison BEGIN --------------
	SK_FORCE_INLINE Vector2i& Vector2i::operator= (const Vector2i& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector2i::operator== (const Vector2i& other) const
	{
		return ( x == other.x && y == other.y );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector2i::operator!= (const Vector2i& other) const
	{
		return ( x != other.x || y != other.y );
	}

	//----------------------------- arithmetic operations BEGIN -------------------
	SK_FORCE_INLINE Vector2i Vector2i::operator+ (const Vector2i& other) const
	{
		return Vector2i (
			x + other.x,
			y + other.y
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::operator- (const Vector2i& other) const
	{
		return Vector2i (
			x - other.x,
			y - other.y
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::operator* (int32_t iScalar) const
	{
		return Vector2i (
			x * iScalar,
			y * iScalar
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i operator* (int32_t iScalar, const Vector2i& other)
	{
		return Vector2i( 
			iScalar * other.x, 
			iScalar * other.y
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::operator/ (int32_t iScalar) const
	{	
		if (iScalar != 0)
		{		
			return Vector2i (
				x / iScalar,
				y / iScalar
				);
		}
		else
		{		
			return Vector2i (
				std::numeric_limits<int32_t>::max(),
				std::numeric_limits<int32_t>::max()
				);
		}	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::operator- () const
	{
		return Vector2i(
			-x,
			-y
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::operator * ( const Vector2i& other ) const
	{
		return Vector2i (
			x * other.x,
			y * other.y
			);
	}

	//----------------------------- arithmetic updates ---------------------------
	SK_FORCE_INLINE Vector2i& Vector2i::operator+= (const Vector2i& rkV)
	{
		x += rkV.x;
		y += rkV.y;
		return *this;
	}
	//----------------------------------------------------------------------------

	SK_FORCE_INLINE Vector2i& Vector2i::operator-= (const Vector2i& rkV)
	{
		x -= rkV.x;
		y -= rkV.y;
		return *this;
	}
	//----------------------------------------------------------------------------

	SK_FORCE_INLINE Vector2i& Vector2i::operator*= (int32_t iScalar)
	{
		x *= iScalar;
		y *= iScalar;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i& Vector2i::operator/= (int32_t iValue)
	{
		if (iValue != 0)
		{		
			x /= iValue;
			y /= iValue;
		}
		else
		{
			x = std::numeric_limits<int32_t>::max();
			y = std::numeric_limits<int32_t>::max();
		}

		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i& Vector2i::operator*= (const Vector2i& v)
	{
		x*=v.x;
		y*=v.y;
		return *this;
	}

	//----------------------------- vector operations ----------------------------
	SK_FORCE_INLINE float Vector2i::length () const
	{
		return Math::sqrt(float(x*x +y*y));
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector2i::squaredLength () const
	{
		return x*x +y*y;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector2i::dot (const Vector2i& other) const
	{
		return x*other.x + y*other.y;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector2i::perpendicularDot (const Vector2i& other) const
	{
		//return y*other.x -x*other.y;
		return x*other.y - y*other.x;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::perpendicular() const
	{
		// vector orthogonal to (x,y) is (-y,x)
		return Vector2i( -y, x );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector2i::isZeroLength(void) const
	{
		return ( x==0 && y==0);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2i::signedAngle(const Vector2i& v1, const Vector2i& v2)
	{   
		// changed this because it doesn't take the orientation into account
		// return Math::aCos( v1.dot(v2) / (v1.length()*v2.length()) ) ;
		return Math::aTan2((float)v1.perpendicularDot(v2), (float)v1.dot(v2));
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2i::unsignedAngle(const Vector2i& v1, const Vector2i& v2)
	{   	
		return Math::aCos( v1.dot(v2) / (v1.length()*v2.length()) ) ;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i& Vector2i::rotateBy(float angle, const Vector2i& center)
	{	
		const float cs = Math::cos(angle);
		const float sn = Math::sin(angle);

		x -= center.x;
		y -= center.y;

		int32_t newX = (int32_t) ( (float)x*cs - (float)y*sn );
		y = (int32_t) ( (float) x*sn + (float)y*cs );
		x = newX;

		x += center.x;
		y += center.y;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2i Vector2i::reflect(const Vector2i& normal) const
	{
		return Vector2i( *this - ( 2 * this->dot(normal) * normal ) );
	}

}//end of namespace SK

