#include <limits>

namespace SK 
{

	//----------------------------- CONSTRUCTOR -----------------------------------------------
	SK_FORCE_INLINE Vector2::Vector2(void)
		: x(0),y(0)
	{
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2::Vector2(float fX, float fY)
		:  x(fX), y(fY)
	{	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2::Vector2(const Vector2& other)
		: x(other.x), y(other.y)
	{	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2::Vector2( const float* pValues )
		: x( pValues[0] ), y( pValues[1] )
	{
	}

	//----------------------------- MEMBER ACCESS  -----------------------------------------------
	SK_FORCE_INLINE float& Vector2::operator[] (int32_t index)
	{
		// assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
		return (&x)[index];//aValues[index];
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::operator[] (int32_t index) const
	{
		// assert:  0 <= i < 2; x and y are packed into 2*sizeof(float) bytes
		return (&x)[index];
	}

	//----------------------------- assignment and comparison BEGIN -----------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::operator= (const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector2::operator== (const Vector2& other) const
	{
		return ( Math::equal(x, other.x) && Math::equal(y, other.y) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector2::operator!= (const Vector2& other) const
	{
		return ( !Math::equal(x, other.x) || !Math::equal(x, other.x) );
	}

	//----------------------------- arithmetic operations BEGIN --------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::operator+ (const Vector2& other) const
	{
		return Vector2 (
			x + other.x,
			y + other.y
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::operator- (const Vector2& other) const
	{
		return Vector2 (
			x - other.x,
			y - other.y
			);	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::operator* (float scalar) const
	{
		return Vector2 (
			x * scalar,
			y * scalar
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 operator* (float scalar, const Vector2& other) 
	{
		return Vector2( 
			scalar * other.x, 
			scalar * other.y
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::operator/ (float scalar) const
	{	
		if (scalar != 0.0f)
		{		
			float invScalar = 1.0f/scalar;
			return Vector2 (
				invScalar * x ,
				invScalar * y
				);
		}
		else
		{		
			return Vector2 (
				std::numeric_limits<float>::max(),
				std::numeric_limits<float>::max()
				);
		}	
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::operator- () const
	{
		return Vector2(
			-x,
			-y
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::operator * ( const Vector2& other ) const
	{
		return Vector2 (
			x * other.x,
			y * other.y
			);
	}

	//----------------------------- arithmetic updates --------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::operator+= (const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::operator-= (const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::operator*= (float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::operator/= (float scalar)
	{
		if ( scalar != 0.0 )
		{
			float invScalar = 1.0f/scalar;
			x *= invScalar;
			y *= invScalar;
		}
		else
		{
			x = std::numeric_limits<float>::max();
			y = std::numeric_limits<float>::max();
		}

		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::operator*= (const Vector2& v)
	{
		x*=v.x;
		y*=v.y;
		return *this;
	}

	//----------------------------- vector operations ----------------------------

	SK_FORCE_INLINE float Vector2::length () const
	{
		return Math::sqrt(x*x +y*y);
	}

	//----------------------------- vector operations ----------------------------

	SK_FORCE_INLINE float Vector2::distance (const Vector2& other) const
	{
		return ( *this - other ).length();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::squaredDistance(const Vector2& other) const
	{
		return (*this - other).squaredLength();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::squaredLength () const
	{
		return x*x + y*y;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::normalize (float fTolerance)
	{
		float fLength = length();

		if ( fLength > fTolerance )
		{
			float fInvLength = 1.f/fLength;
			x *= fInvLength;
			y *= fInvLength;
		}
		else
		{
			fLength = 0.0;
		}

		return fLength;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::normalizedCopy(void) const
	{
		Vector2 ret = *this;
		ret.normalize();
		return ret;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::dot (const Vector2& other) const
	{
		return x*other.x + y*other.y;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::perpendicularDot (const Vector2& other) const
	{
		//return y*other.x -x*other.y;
		return x*other.y - y*other.x;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::perpendicular () const
	{
		// vector orthogonal to (x,y) is (-y,x)
		return Vector2( -y, x );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::unitPerpendicular () const
	{
		// unit vector orthogonal to (x,y) is (y,-x)/sqrt(x^2+y^2)
		Vector2 kCross( y, -x );	
		kCross.normalize();
		return kCross;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::randomDeviant(float angle) const
	{
		angle *=  Math::unitRandom() * Math::TWO_PI;
		float cosa = Math::cos(angle);
		float sina = Math::sin(angle);
		return  Vector2(
			cosa * x - sina * y ,
			sina * x + cosa * y );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Vector2::isZeroLength(void) const
	{
		float sqlen = (x * x) + (y * y);
		return (sqlen < (1e-06 * 1e-06));
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector2::orthonormalize(Vector2& U, Vector2& V)
	{
		// If the input vectors are v0 and v1, then the Gram-Schmidt
		// orthonormalization produces vectors u0 and u1 as follows,
		//
		//   u0 = v0/|v0|
		//   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
		//
		// where |A| indicates length of vector A and A*B indicates dot
		// product of vectors A and B.

		// compute u0
		U.normalize();

		// compute u1
		float fDot0 = U.dot(V); 
		V -= fDot0*U;
		V.normalize();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Vector2::generateOrthonormalBasis (Vector2& U, Vector2& V)
	{
		V.normalize();
		U = V.perpendicular();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::signedAngle(const Vector2& v1, const Vector2& v2)
	{   
		// changed this because it doesn't take the orientation into account
		// return Math::aCos( v1.dot(v2) / (v1.length()*v2.length()) ) ;
		return Math::aTan2(v1.perpendicularDot(v2), v1.dot(v2));
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::unsignedAngle(const Vector2& v1, const Vector2& v2)
	{   	
		return Math::aCos( v1.dot(v2) / (v1.length()*v2.length()) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Vector2::unsignedAngleNormalized(const Vector2& v1, const Vector2& v2)
	{   
		return Math::aCos(v1.dot(v2)); 
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2& Vector2::rotateBy(float angle, const Vector2& center)
	{	
		const float cs = Math::cos(angle);
		const float sn = Math::sin(angle);

		x -= center.x;
		y -= center.y;

		float newX = x*cs - y*sn;
		y = x*sn + y*cs;
		x = newX;

		x += center.x;
		y += center.y;
		return *this;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector2 Vector2::reflect(const Vector2& normal) const
	{
		return Vector2( *this - ( 2 * this->dot(normal) * normal ) );
	}

}//end of namespace SK

