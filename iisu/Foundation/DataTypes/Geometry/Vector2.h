#pragma once

#include <System/Math/Math.h>
#include <Platform/SkPlatform.h>
#include <ostream>

namespace SK
{
	/**
	 * \class	Vector2
	 *
	 * \brief	2-dimensional vector.
	 */
	 
	class IISUSDK_API Vector2
	{
	public:
		//*********** Constructor and access ***********	

		/**
		 * \fn	Vector2::Vector2 (void);
		 *
		 * \brief	Default constructor.
		 *		 Initializes to ZERO
		 */

		Vector2 (void);	

		/**
		 * \fn	Vector2::Vector2 (float x, float y);
		 *
		 * \brief	Explicit constructor from values.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 */

		Vector2 (float x, float y);	

		/**
		 * \fn	Vector2::Vector2 (const Vector2& other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		Vector2 (const Vector2& other);

		/**
		 * \fn	explicit Vector2::Vector2( const float* pValues );
		 *
		 * \brief	Constructor from an array of values.
		 *
		 * \param	pValues	The values.
		 */

		explicit Vector2( const float* pValues );

		//! coordinate access
		float& operator[] (int32_t index);	
		//! coordinate access
		float operator[] (int32_t index) const; 	

		//*********** Assignment and comparison ***********

		//! assignment
		Vector2& operator= (const Vector2& other);
		//! test for equality
		bool operator== (const Vector2& other) const;
		//! test for inequality
		bool operator!= (const Vector2& other) const;

		//*********** Arithmetic operations ***********

		//! addition
		Vector2 operator+ (const Vector2& other) const;
		//! subtraction
		Vector2 operator- (const Vector2& other) const;
		//! uniform scaling
		Vector2 operator* (float scalar) const;
		//! uniform scaling
		friend Vector2 operator* (float scalar, const Vector2& other);
		//! uniform scaling
		Vector2 operator/ (float scalar) const;
		//! negation
		Vector2 operator- () const;
		//! multiply component by component
		Vector2 operator * ( const Vector2& other) const;

		//*********** Arithmetic updates ***********

		//! addition
		Vector2& operator+= (const Vector2& other);
		//! subtraction
		Vector2& operator-= (const Vector2& other);
		//! uniform scaling
		Vector2& operator*= (float scalar);
		//! uniform scaling
		Vector2& operator/= (float scalar);
		//! multiply component by component
		Vector2& operator*= (const Vector2& other);

		//*********** Vector operations ***********

		//! Returns the length (magnitude) of the vector. 
		float length () const;

		//! Returns the square of the length(magnitude) of the vector
		float squaredLength () const;

		//! Returns the distance to another vector.
		float distance (const Vector2& other) const;

		//! Returns the squared distance to another vector.
		float squaredDistance(const Vector2& other) const;

		//! Normalizes this vector and return it's previous length
		float normalize (float tolerance = 1e-06);

		//! As normalize, except that this vector is unaffected and the normalized vector is returned as a copy. 
		Vector2 normalizedCopy (void) const	;

		//! Calculates the dot (scalar) product of this vector with another. 
		float dot (const Vector2& other) const;	

		//! Calculates the dot (scalar) product of this vector rotated by 90 degree left with another.
		float perpendicularDot (const Vector2& other) const;

		//! return a perpendicular vector (-y,x)
		Vector2 perpendicular () const;

		//! return a normalized perpendicular vector
		Vector2 unitPerpendicular () const;

		//! Generates a new random vector which deviates from this vector by a given angle in a random direction. 
		/** Default angle value is 1 degree.
		*/
		Vector2 randomDeviant (float angle = Math::PI_OVER_180) const;		

		//! Returns true if this vector is zero length.
		bool isZeroLength (void) const;

		//! Gram-Schmidt orthonormalization.  
		/** Take linearly independent vectors U and V and compute 
		an orthonormal set (unit length, mutually perpendicular).  
		*/
		static void orthonormalize (Vector2& U, Vector2& V);

		//! Generate an orthonormal basis
		/** Input V must be a nonzero vector.  The output is an orthonormal basis
		{U,V}.  The input V is normalized by this function.  If you know V is
		already unit length, use U = V.Perp().
		*/
		static void generateOrthonormalBasis (Vector2& U, Vector2& V);

		//! Computes the signed angle in radian between 2 arbitrary vectors
		static float signedAngle(const Vector2& v1, const Vector2& v2);

		//! Computes the unsigned angle in radian between 2 arbitrary vectors
		static float unsignedAngle(const Vector2& v1, const Vector2& v2);

		//! Computes the unsigned angle in radian between 2 normalized vectors
		static float unsignedAngleNormalized(const Vector2& v1, const Vector2& v2);

		//! Rotates the point anticlockwise around a center by a specified angle
		Vector2& rotateBy(float angle, const Vector2& center = Vector2::ZERO);

		//! Calculates a reflection vector to the plane with the given normal . 
		Vector2 reflect( const Vector2& normal) const;

		/** Function for writing to a stream.
		*/
		inline friend std::ostream& operator << 
			( std::ostream& o, const Vector2& v )
		{
			o << "Vector2(" << v.x << ", " << v.y <<  ")";
			return o;
		}

	public:
		// member access (allows V.x or V[0], V.y or V[1])
		float x,y;

		// special points
		///< The zero vector
		static const Vector2 ZERO;
		///< The unit vector (x)
		static const Vector2 UNIT_X;
		///< The unit vector (y)
		static const Vector2 UNIT_Y;
		///< The negative unit vector (x)
		static const Vector2 NEGATIVE_UNIT_X;
		///< The negative unit vector (y)
		static const Vector2 NEGATIVE_UNIT_Y;

	};

}//end of namespace SK

#ifndef SK_DEBUG
#include "Vector2.inl"
#endif
