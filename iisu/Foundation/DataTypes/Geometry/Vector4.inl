#include <limits>

namespace SK 
{

	//----------------------------- CONSTRUCTOR -----------------------------------------------
	SK_FORCE_INLINE Vector4::Vector4(void)
		: x(0), y(0), z(0), w(0)
	{
	}
	SK_FORCE_INLINE Vector4::Vector4(float x0, float y0, float z0, float w0) 
		: x(x0), y(y0), z(z0), w(w0)
	{
	}
	SK_FORCE_INLINE Vector4::Vector4(const Vector4& other) 
		: x(other.x), y(other.y), z(other.z), w(other.w) 
	{
	}
	SK_FORCE_INLINE Vector4::Vector4( const float* pValues)
		: x( pValues[0] ), y( pValues[1] ), z( pValues[2] ), w( pValues[3] )
	{
	}

	//----------------------------- MEMBER ACCESS  -----------------------------------------------
	SK_FORCE_INLINE float& Vector4::operator[] (int32_t i)
	{
		// assert:  0 <= i < 3; x, y, and z are packed into 4*sizeof(float)
		//          bytes
		return (&x)[i];
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE const float& Vector4::operator[] (int32_t i) const
	{
		// assert:  0 <= i < 3; x, y, and z are packed into 4*sizeof(float)
		//          bytes
		return (&x)[i];
	}

	//----------------------------- assignment and comparison BEGIN -----------------------------------------------
	SK_FORCE_INLINE Vector4& Vector4::operator= (const Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector4::operator== (const Vector4& other) const
	{
		return ( Math::equal(x, other.x) && Math::equal(y, other.y) && Math::equal(z, other.z) && Math::equal(w, other.w) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector4::operator!= (const Vector4& other) const
	{
		return ( !Math::equal(x, other.x) || !Math::equal(y, other.y) || !Math::equal(z, other.z) || !Math::equal(w, other.w) );
	}

	//----------------------------- arithmetic operations BEGIN --------------------------------------------
	SK_FORCE_INLINE Vector4 Vector4::operator+ (const Vector4& other) const
	{
		return Vector4 (
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Vector4::operator- (const Vector4& other) const
	{
		return Vector4 (
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Vector4::operator* (float scalar) const
	{
		return Vector4 (
			scalar*x,
			scalar*y,
			scalar*z,
			scalar*w
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 operator* (float scalar, const Vector4& other)
	{
		return Vector4 (
			scalar*other.x,
			scalar*other.y,
			scalar*other.z,
			scalar*other.w
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Vector4::operator/ (float scalar) const
	{
		if ( scalar != 0.0f )
		{
			float invScalar = 1.0f/scalar;
			return Vector4 (
				invScalar * x,
				invScalar * y,
				invScalar * z,
				invScalar * w
				);
		}
		else
		{
			return Vector4(	std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() );
		}
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Vector4::operator- () const
	{
		return Vector4(
			-x,
			-y,
			-z,
			-w
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Vector4::operator * ( const Vector4& other ) const
	{
		return Vector4 (
			x * other.x,
			y * other.y,
			z * other.z,
			w * other.w );
	}

	//----------------------------- arithmetic updates --------------------------------------------
	SK_FORCE_INLINE Vector4& Vector4::operator+= (const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4& Vector4::operator-= (const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4& Vector4::operator*= (float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4& Vector4::operator/= (float scalar)
	{
		if ( scalar != 0.0 )
		{
			float invScalar = 1.0f/scalar;
			x *= invScalar;
			y *= invScalar;
			z *= invScalar;
			w *= invScalar;
		}
		else
		{
			x = std::numeric_limits<float>::max();
			y = std::numeric_limits<float>::max();
			z = std::numeric_limits<float>::max();
			w = std::numeric_limits<float>::max();
		}

		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4& Vector4::operator*= (const Vector4& v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		w*=v.w;
		return *this;
	}

	//----------------------------- arithmetic operations BEGIN --------------------------------------------
	SK_FORCE_INLINE float Vector4::length () const
	{
		return Math::sqrt(x*x + y*y + z*z+ w*w);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector4::squaredLength () const
	{
		return x*x + y*y + z*z+ w*w;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector4::dot (const Vector4& other) const
	{
		return x*other.x + y*other.y + z*other.z+ w*other.w;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector4::isZeroLength ( void ) const
	{	
		return ( squaredLength() < ( 1e-06f * 1e-06f ) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector4::distance ( const Vector4& other ) const
	{
		return ( *this - other ).length();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector4::squaredDistance(const Vector4& other) const
	{
		return (*this - other).squaredLength();
	}

	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector4::makeFloor ( const Vector4& cmp )
	{
		if ( cmp.x < x ) x = cmp.x;
		if ( cmp.y < y ) y = cmp.y;
		if ( cmp.z < z ) z = cmp.z;
		if ( cmp.w < w ) w = cmp.w;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector4::makeCeil ( const Vector4& cmp )
	{
		if ( cmp.x > x ) x = cmp.x;
		if ( cmp.y > y ) y = cmp.y;
		if ( cmp.z > z ) z = cmp.z;
		if ( cmp.w > w ) w = cmp.w;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector4::isValid() const
	{
		if( SK_REAL_IS_VALID(x) && SK_REAL_IS_VALID(y) && SK_REAL_IS_VALID(z)  && SK_REAL_IS_VALID(w))
		{
			return true;
		}
		return false;
	}

}//end of namespace SK

