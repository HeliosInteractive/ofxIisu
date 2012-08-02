#pragma once

#include <System/Math/Math.h>
#include <Platform/SkPlatform.h>
#include <ostream>

namespace SK
{
	/**
	 * \class	Vector3i
	 *
	 * \brief	3-dimensional vector (integer coefficients). 
	 */

	class IISUSDK_API Vector3i
	{
	public:
		//*********** Constructor and access ***********	

		/**
		 * \fn	Vector3i::Vector3i (void);
		 *
		 * \brief	Default constructor.
		 *
		 * Initializes to ZERO
		 */

		Vector3i (void);

		/**
		 * \fn	Vector3i::Vector3i (int32_t x, int32_t y, int32_t z);
		 *
		 * \brief	Explicit constructor from coefficients.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 * \param	z	The z coordinate.
		 */

		Vector3i (int32_t x, int32_t y, int32_t z);

		/**
		 * \fn	Vector3i::Vector3i (const Vector3i& other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		Vector3i (const Vector3i& other);

		/**
		 * \fn	explicit Vector3i::Vector3i( const int32_t * pValues );
		 *
		 * \brief	Constructor from an array of values.
		 *
		 * \param	pValues	The values.
		 */

		explicit Vector3i( const int32_t * pValues );

		//! coordinate access
		int32_t& operator[] (int32_t iIndex);
		//! coordinate access
		int32_t operator[] (int32_t iIndex) const;

		//*********** Assignment and comparison ***********

		//! assignment
		Vector3i& operator= (const Vector3i& other);
		//! test for equality
		bool operator== (const Vector3i& other) const;
		//! test for inequality
		bool operator!= (const Vector3i& other) const;

		//*********** Arithmetic operations ***********

		//! addition
		Vector3i operator+ (const Vector3i& other) const;
		//! subtraction
		Vector3i operator- (const Vector3i& other) const;
		//! uniform scaling
		Vector3i operator* (int32_t scalar) const;
		//! uniform scaling
		friend Vector3i operator* (int32_t scalar, const Vector3i& other);	
		//! uniform scaling
		Vector3i operator/ (int32_t scalar) const;
		//! negation
		Vector3i operator- () const;
		//! multiply component by component
		Vector3i operator * ( const Vector3i& other) const;

		//*********** Arithmetic updates ***********

		//! addition
		Vector3i& operator+= (const Vector3i& rkV);
		//! subtraction
		Vector3i& operator-= (const Vector3i& rkV);
		//! uniform scaling
		Vector3i& operator*= (int32_t scalar);
		//! uniform scaling
		Vector3i& operator/= (int32_t scalar);
		//! multiply component by component
		Vector3i& operator*= (const Vector3i& other);

		//*********** Vector operations ***********

		//! Returns the length (magnitude) of the vector. 
		float length () const;

		//! Returns the square of the length(magnitude) of the vector
		int32_t squaredLength () const;

		//! Returns the squared distance to the other vector
		int32_t squaredDistance (const Vector3i& other) const;

		//! Calculates the dot (scalar) product of this vector with another. 
		int32_t dot (const Vector3i& other) const;	

		//! Returns true if this vector is zero length.
		bool isZeroLength (void) const;

		/** Function for writing to a stream.
		*/
		inline friend std::ostream& operator<< ( std::ostream& o, const Vector3i& v )
		{
			o << "Vector3i(" << v.x << ", " << v.y << ", " << v.z << ")";
			return o;
		}

	public:
		// member access (allows V.x or V[0], V.y or V[1])
		int32_t x,y,z;

		// special points
		///< The zero vector
		static const Vector3i ZERO;
		///< The all one vector
		static const Vector3i ONE;	
		///< The unit vector (x)
		static const Vector3i UNIT_X;
		///< The unit vector (y)
		static const Vector3i UNIT_Y;
		///< The unit vector (z)
		static const Vector3i UNIT_Z;
		///< The negative unit vector (x)
		static const Vector3i NEGATIVE_UNIT_X;
		///< The negative unit vector (y)
		static const Vector3i NEGATIVE_UNIT_Y;
		///< The negative unit vector (z)
		static const Vector3i NEGATIVE_UNIT_Z;

	};

}//end of namespace SK

#ifndef SK_DEBUG
#include "Vector3i.inl"
#endif


