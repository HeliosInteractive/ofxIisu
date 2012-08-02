#include <limits>


namespace SK 
{

	//----------------------------- CONSTRUCTOR ----------------------------------
	SK_FORCE_INLINE Vector3i::Vector3i(void)
		: x(0),y(0),z(0)
	{
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i::Vector3i(int32_t xIni, int32_t yIni, int32_t zInt)
		:  x(xIni), y(yIni), z(zInt)
	{	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i::Vector3i(const Vector3i& other)
		: x(other.x), y(other.y), z(other.z)
	{
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i::Vector3i( const int32_t* pValues )
		: x( pValues[0] ), y( pValues[1] ), z( pValues[2] )
	{
	}

	//----------------------------- MEMBER ACCESS  -------------------------------
	SK_FORCE_INLINE int32_t& Vector3i::operator[] (int32_t i)
	{
		// assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
		return (&x)[i];
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector3i::operator[] (int32_t i) const
	{
		// assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
		return (&x)[i];
	}

	//----------------------------- assignment and comparison BEGIN --------------
	SK_FORCE_INLINE Vector3i& Vector3i::operator= (const Vector3i& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3i::operator== (const Vector3i& other) const
	{
		return ( x == other.x && y == other.y && z == other.z);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3i::operator!= (const Vector3i& other) const
	{
		return ( x != other.x || y != other.y || z != other.z );
	}

	//----------------------------- arithmetic operations BEGIN -------------------
	SK_FORCE_INLINE Vector3i Vector3i::operator+ (const Vector3i& other) const
	{
		return Vector3i (
			x + other.x,
			y + other.y,
			z + other.z
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i Vector3i::operator- (const Vector3i& other) const
	{
		return Vector3i (
			x - other.x,
			y - other.y,
			z - other.z
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i Vector3i::operator* (int32_t iScalar) const
	{
		return Vector3i (
			x * iScalar,
			y * iScalar,
			z * iScalar
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i operator* (int32_t iScalar, const Vector3i& other)
	{
		return Vector3i( 
			iScalar * other.x, 
			iScalar * other.y,
			iScalar * other.z
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i Vector3i::operator/ (int32_t iScalar) const
	{	
		if (iScalar != 0)
		{		
			return Vector3i (
				x / iScalar,
				y / iScalar,
				z / iScalar
				);
		}
		else
		{		
			return Vector3i (
				std::numeric_limits<int32_t>::max(),
				std::numeric_limits<int32_t>::max(),
				std::numeric_limits<int32_t>::max()
				);
		}	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i Vector3i::operator- () const
	{
		return Vector3i(
			-x,
			-y,
			-z
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i Vector3i::operator * ( const Vector3i& other ) const
	{
		return Vector3i (
			x * other.x,
			y * other.y,
			z * other.z
			);
	}

	//----------------------------- arithmetic updates ---------------------------
	SK_FORCE_INLINE Vector3i& Vector3i::operator+= (const Vector3i& rkV)
	{
		x += rkV.x;
		y += rkV.y;
		z += rkV.z;
		return *this;
	}
	//----------------------------------------------------------------------------

	SK_FORCE_INLINE Vector3i& Vector3i::operator-= (const Vector3i& rkV)
	{
		x -= rkV.x;
		y -= rkV.y;
		z -= rkV.z;
		return *this;
	}
	//----------------------------------------------------------------------------

	SK_FORCE_INLINE Vector3i& Vector3i::operator*= (int32_t iScalar)
	{
		x *= iScalar;
		y *= iScalar;
		z *= iScalar;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i& Vector3i::operator/= (int32_t iValue)
	{
		if (iValue != 0)
		{		
			x /= iValue;
			y /= iValue;
			z /= iValue;
		}
		else
		{
			x = std::numeric_limits<int32_t>::max();
			y = std::numeric_limits<int32_t>::max();
			z = std::numeric_limits<int32_t>::max();
		}

		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3i& Vector3i::operator*= (const Vector3i& v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		return *this;
	}

	//----------------------------- vector operations ----------------------------
	SK_FORCE_INLINE float Vector3i::length () const
	{
		return Math::sqrt(float(x*x + y*y + z*z));
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector3i::squaredLength () const
	{
		return x*x + y*y + z*z;
	}

	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector3i::squaredDistance (const Vector3i& other) const
	{
		int32_t dx = x - other.x;
		int32_t dy = y - other.y;
		int32_t dz = z - other.z;
		return dx*dx + dy*dy + dz*dz;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE int32_t Vector3i::dot (const Vector3i& other) const
	{
		return x*other.x + y*other.y + z*other.z;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3i::isZeroLength(void) const
	{
		return ( x==0 && y==0 && z == 0);
	}

}//end of namespace SK

