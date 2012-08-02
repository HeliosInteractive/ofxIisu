#include <limits>

namespace SK 
{

	//----------------------------- CONSTRUCTOR -----------------------------------------------
	SK_FORCE_INLINE Vector3::Vector3(void)
		: x(0.f), y(0.f), z(0.f)
	{
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3::Vector3(float fX, float fY, float fZ)
		:  x(fX), y(fY), z(fZ) 
	{	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3::Vector3(const Vector3& other)
		:x(other.x), y(other.y), z(other.z)
	{	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3::Vector3( const float* pValues)
		: x( pValues[0] ), y( pValues[1] ), z( pValues[2] )
	{
	}

	//----------------------------- MEMBER ACCESS  -----------------------------------------------
	SK_FORCE_INLINE float& Vector3::operator[] (int32_t i)
	{
		// assert:  0 <= i < 2; x, y, and z are packed into 3*sizeof(float)
		//          bytes
		return (&x)[i];//aValues[i];
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE const float& Vector3::operator[] (int32_t i) const
	{
		// assert:  0 <= i < 2; x, y, and z are packed into 3*sizeof(float)
		//          bytes
		return (&x)[i];//aValues[i];
	}

	//----------------------------- assignment and comparison BEGIN -----------------------------------------------
	/*
	SK_FORCE_INLINE Vector3& Vector3::operator= (const Vector3& other)
	{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
	}*/

	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3& Vector3::set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;

		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool  Vector3::equals ( const Vector3& other, const float tolerance) const
	{
		return( Math::equal(this->distance(other),0.0,tolerance) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3::operator== (const Vector3& other) const
	{
		return ( Math::equal(x, other.x) && Math::equal(y, other.y) && Math::equal(z, other.z) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3::operator!= (const Vector3& other) const
	{
		return ( !Math::equal(x, other.x) || !Math::equal(y, other.y) || !Math::equal(z, other.z) );
	}

	//----------------------------- arithmetic operations BEGIN --------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::operator+ (const Vector3& other) const
	{
		return Vector3 (
			x + other.x,
			y + other.y,
			z + other.z
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::operator- (const Vector3& other) const
	{
		return Vector3 (
			x - other.x,
			y - other.y,
			z - other.z
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::operator* (float scalar) const
	{
		return Vector3 (
			scalar*x,
			scalar*y,
			scalar*z
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 operator* (float scalar, const Vector3& other)
	{
		return Vector3 (
			scalar*other.x,
			scalar*other.y,
			scalar*other.z
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::operator/ (float scalar) const
	{
		if ( scalar != 0.0f )
		{
			float invScalar = 1.0f/scalar;
			return Vector3 (
				invScalar * x,
				invScalar * y,
				invScalar * z
				);
		}
		else
		{
			return Vector3(	std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() );
		}
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::operator- () const
	{
		return Vector3(
			-x,
			-y,
			-z
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::operator * ( const Vector3& other ) const
	{
		return Vector3 (
			x * other.x,
			y * other.y,
			z * other.z );
	}

	//----------------------------- arithmetic updates --------------------------------------------
	SK_FORCE_INLINE Vector3& Vector3::operator+= (const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3& Vector3::operator-= (const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3& Vector3::operator*= (float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3& Vector3::operator/= (float scalar)
	{
		if ( scalar != 0.0 )
		{
			float invScalar = 1.0f/scalar;
			x *= invScalar;
			y *= invScalar;
			z *= invScalar;
		}
		else
		{
			x = std::numeric_limits<float>::max();
			y = std::numeric_limits<float>::max();
			z = std::numeric_limits<float>::max();
		}

		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3& Vector3::operator*= (const Vector3& v)
	{
		x*=v.x;
		y*=v.y;
		z*=v.z;
		return *this;
	}

	//----------------------------- arithmetic operations BEGIN --------------------------------------------
	SK_FORCE_INLINE float Vector3::length () const
	{
		return Math::sqrt(x*x + y*y + z*z);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::squaredLength () const
	{
		return x*x + y*y + z*z;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::normalize (float tolerance)
	{
		float fLength = length();

		if ( fLength > tolerance )
		{
			float fInvLength = 1.f/fLength;
			x *= fInvLength;
			y *= fInvLength;
			z *= fInvLength;
		}
		else
		{
			fLength = 0.0;
		}

		return fLength;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::normalizedCopy(void) const
	{
		Vector3 ret = *this;
		ret.normalize();
		return ret;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::dot (const Vector3& other) const
	{
		return x*other.x + y*other.y + z*other.z;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::cross (const Vector3& other) const
	{
		return Vector3(
			y*other.z - z*other.y,
			z*other.x - x*other.z,
			x*other.y - y*other.x
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::unitCross (const Vector3& other) const
	{
		Vector3 kCross(
			y*other.z - z*other.y,
			z*other.x - x*other.z,
			x*other.y - y*other.x
			);

		kCross.normalize();
		return kCross;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::perpendicular(void) const
	{
		static const float squareZero = Math::ZERO_TOLERANCE * Math::ZERO_TOLERANCE;

		Vector3 perp = this->cross( Vector3::UNIT_X );

		// Check length
		if( perp.squaredLength() < squareZero )
		{
			/* This vector is the Y axis multiplied by a scalar, so we have
			to use another axis.
			*/
			perp = this->cross( Vector3::UNIT_Y );
		}
		perp.normalize();

		return perp;
	}		
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3::isZeroLength ( void ) const
	{	
		return ( squaredLength() < ( Math::ZERO_TOLERANCE * Math::ZERO_TOLERANCE ) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::distance ( const Vector3& other ) const
	{
		return ( *this - other ).length();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::squaredDistance(const Vector3& other) const
	{
		return (*this - other).squaredLength();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector3::makeFloor ( const Vector3& cmp )
	{
		if ( cmp.x < x ) x = cmp.x;
		if ( cmp.y < y ) y = cmp.y;
		if ( cmp.z < z ) z = cmp.z;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector3::makeCeil ( const Vector3& cmp )
	{
		if ( cmp.x > x ) x = cmp.x;
		if ( cmp.y > y ) y = cmp.y;
		if ( cmp.z > z ) z = cmp.z;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::reflect(const Vector3& normal) const
	{
		return Vector3( *this - ( 2.0f * this->dot(normal) * normal ) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector3::isValid() const
	{
		if( SK_REAL_IS_VALID(x) && SK_REAL_IS_VALID(y) && SK_REAL_IS_VALID(z))
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Vector3::GetRotationBetween(const Vector3& source, const Vector3& destination, const Vector3& fallbackAxis, float epsilon)
	{
		Vector3 res = Vector3::ZERO;

		Vector3 v0 = source;
		Vector3 v1 = destination;
		v0.normalize();
		v1.normalize();

		float d = v0.dot(v1);
		
		// Check if source and destination are already aligned.
		if (d > 1.0f - epsilon)
		{
			return res;
		}
		
		// Check if source and destination are opposite. In this case any axis in the plan orthogonal to
		// the source (or the destination - it is the same plan) is a rotation axis taking the source to
		// the destination.
		if (d < -1.0f + epsilon)
		{
			// The fallback axis should not be 0.
			if (fallbackAxis.length() < epsilon)
			{
				return res;
			}

			res = fallbackAxis;
			res.normalize();
			res *= Math::PI;
		}

		// this = v0 ^ v1 / |v0 ^ v1| * arccos(v0 * v1).
		res = v0.cross(v1);
		res.normalize();
		res *= Math::aCos(v0.dot(v1));

		return res;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector3::generateOrthonormalBasis (Vector3& baseU, Vector3& baseV,	Vector3& baseW, bool isUnitLengthW)
	{
		if ( !isUnitLengthW )
			baseW.normalize();

		float invLength;

		if (Math::abs(baseW[0]) >=
			Math::abs(baseW[1]) )
		{
			// W.x or W.z is the largest magnitude component, swap them
			invLength = Math::invSqrt( baseW[0] * baseW[0] + baseW[2] * baseW[2] );
			baseU[0] = -baseW[2] * invLength;
			baseU[1] =  0.0f;
			baseU[2] =  baseW[0] * invLength;
			baseV[0] =  baseW[1] * baseU[2];
			baseV[1] =  baseW[2] * baseU[0] - baseW[0] * baseU[2];
			baseV[2] = -baseW[1] * baseU[0];
		}
		else
		{
			// W.y or W.z is the largest magnitude component, swap them
			invLength = Math::invSqrt(baseW[1] * baseW[1] + baseW[2] * baseW[2]);
			baseU[0] = 0.0f;
			baseU[1] =  baseW[2] * invLength;
			baseU[2] = -baseW[1] * invLength;
			baseV[0] =  baseW[1] * baseU[2] - baseW[2] * baseU[1];
			baseV[1] = -baseW[0] * baseU[2];
			baseV[2] =  baseW[0] * baseU[1];
		}
		/*

		if ( Math::abs(rkW.x) >= Math::abs(rkW.y)
		&&   Math::abs(rkW.x) >= Math::abs(rkW.z) )
		{
		rkU.x = -rkW.y;
		rkU.y = +rkW.x;
		rkU.z = 0.0;
		}
		else
		{
		rkU.x = 0.0;
		rkU.y = +rkW.z;
		rkU.z = -rkW.y;
		}

		rkU.normalize();
		rkV = rkW.cross(rkU);
		*/
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector3::orthonormalize (Vector3& kX, Vector3& kY, Vector3& kZ)
	{
		// If the input vectors are v0, v1, and v2, then the Gram-Schmidt
		// orthonormalization produces vectors u0, u1, and u2 as follows,
		//
		//   u0 = v0/|v0|
		//   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
		//   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
		//
		// where |A| indicates length of vector A and A*B indicates dot
		// product of vectors A and B.

		// compute u0
		kX.normalize();

		// compute u1
		float fDot0 = kX.dot(kY); 
		kY -= fDot0*kX;
		kY.normalize();

		// compute u2
		float fDot1 = kY.dot(kZ);
		fDot0 = kX.dot(kZ);
		kZ -= fDot0*kX + fDot1*kY;
		kZ.normalize();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::unsignedAngle(const Vector3& v1, const Vector3& v2)
	{   
		float lenProduct = v1.length() * v2.length();
		// Divide by zero check
		if(lenProduct < Math::ZERO_TOLERANCE)
			lenProduct = Math::ZERO_TOLERANCE;

		float f = v1.dot(v2) / lenProduct;

		f = Math::clamp(f, (float)-1.0f, (float)1.0f);
		return Math::aCos(f);

		//return Math::aCos( v1.dot(v2) / (v1.length()*v2.length()) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector3::signedAngle( const Vector3& v1, const Vector3& v2,  const Vector3& reference )
	{   
		Vector3 c = v1.cross(v2);
		float angle = Math::aTan2(c.length(), v1.dot(v2));
		return ( c.dot(reference) < 0.f ) ? -angle : angle;
	}

}//end of namespace SK
