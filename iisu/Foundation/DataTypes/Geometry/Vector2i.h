#pragma once

#include <System/Math/Math.h>
#include <Platform/SkPlatform.h>
#include <ostream>

namespace SK
{
	/**
	 * \class	Vector2i
	 *
	 * \brief	2-dimensional vector (integer coefficients). 
	 */

	class IISUSDK_API Vector2i
	{
	public:
		//*********** Constructor and access ***********	

		/**
		 * \fn	Vector2i::Vector2i (void);
		 *
		 * \brief	Default constructor.
		 *		Initialilzes to ZERO
		 */

		Vector2i (void);

		/**
		 * \fn	Vector2i::Vector2i (int32_t x, int32_t y);
		 *
		 * \brief	Explicit constructor from coefficients.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 */

		Vector2i (int32_t x, int32_t y);

		/**
		 * \fn	Vector2i::Vector2i (const Vector2i& other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		Vector2i (const Vector2i& other);

		/**
		 * \fn	explicit Vector2i::Vector2i( const int32_t * pValues );
		 *
		 * \brief	Constructor from an array of values.
		 *
		 * \param	pValues	The values.
		 */

		explicit Vector2i( const int32_t * pValues );

		/**
		 * \fn	int32_t& Vector2i::operator[] (int32_t iIndex);
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	iIndex	index of the value.
		 *
		 * \return	The indexed value.
		 */

		int32_t& operator[] (int32_t iIndex);

		/**
		 * \fn	int32_t Vector2i::operator[] (int32_t iIndex) const;
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	iIndex	index of the value.
		 *
		 * \return	The indexed value.
		 */

		int32_t operator[] (int32_t iIndex) const;

		//*********** Assignment and comparison ***********

		//! assignment
		Vector2i& operator= (const Vector2i& other);
		//! test for equality
		bool operator== (const Vector2i& other) const;
		//! test for inequality
		bool operator!= (const Vector2i& other) const;

		//*********** Arithmetic operations ***********

		//! addition
		Vector2i operator+ (const Vector2i& other) const;
		//! subtraction
		Vector2i operator- (const Vector2i& other) const;
		//! uniform scaling
		Vector2i operator* (int32_t scalar) const;
		//! uniform scaling
		friend Vector2i operator* (int32_t scalar, const Vector2i& other);	
		//! uniform scaling
		Vector2i operator/ (int32_t scalar) const;
		//! negation
		Vector2i operator- () const;
		//! multiply component by component
		Vector2i operator * ( const Vector2i& other) const;

		//*********** Arithmetic updates ***********

		//! addition
		Vector2i& operator+= (const Vector2i& rkV);
		//! subtraction
		Vector2i& operator-= (const Vector2i& rkV);
		//! uniform scaling
		Vector2i& operator*= (int32_t scalar);
		//! uniform scaling
		Vector2i& operator/= (int32_t scalar);
		//! multiply component by component
		Vector2i& operator*= (const Vector2i& other);

		//*********** Vector operations ***********

		//! Returns the length (magnitude) of the vector. 
		float length () const;

		//! Returns the square of the length(magnitude) of the vector
		int32_t squaredLength () const;

		//! Calculates the dot (scalar) product of this vector with another. 
		int32_t dot (const Vector2i& other) const;	

		//! Calculates the dot (scalar) product of this vector rotated by 90 degree left with another.
		int32_t perpendicularDot (const Vector2i& other) const;

		//! return a perpendicular vector (-y,x)
		Vector2i perpendicular () const;

		//! Returns true if this vector is zero length.
		bool isZeroLength (void) const;

		//! computes the signed angle in radian between 2 arbitrary vectors
		static float signedAngle(const Vector2i& v1, const Vector2i& v2);

		//! computes the unsigned angle in radian between 2 arbitrary vectors
		static float unsignedAngle(const Vector2i& v1, const Vector2i& v2);

		//! Rotates the point anticlockwise around a center by a specified angle
		Vector2i& rotateBy(float angle, const Vector2i& center = Vector2i::ZERO);

		//! Calculates a reflection vector to the plane with the given normal . 
		Vector2i reflect( const Vector2i& normal) const;

		/** Function for writing to a stream.
		*/
		inline friend std::ostream& operator<< (std::ostream& o, const Vector2i& v )
		{
			o << "Vector2(" << v.x << ", " << v.y <<  ")";
			return o;
		}

	public:
		// member access (allows V.x or V[0], V.y or V[1])
		int32_t x, y;

		// special points
		///< The zero vector
		static const Vector2i ZERO;
		///< The unit vector (x)
		static const Vector2i UNIT_X;
		///< The unit vector (y)
		static const Vector2i UNIT_Y;
		///< The negative unit vector (x)
		static const Vector2i NEGATIVE_UNIT_X;
		///< The negative unit vector (y)
		static const Vector2i NEGATIVE_UNIT_Y;
	};

}//end of namespace SK

#ifndef SK_DEBUG
#include "Vector2i.inl"
#endif

