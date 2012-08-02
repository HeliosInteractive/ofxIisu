/* Version: $Id: Vector4.h 12995 2011-01-17 17:31:07Z jeremie $ */
// Vector4.h: interface for the Vector4 class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <System/Math/Math.h>
#include <Platform/SkPlatform.h>
#include <ostream>


namespace SK 
{
	/**
	 * \class	Vector4
	 *
	 * \brief	4-dimensional homogeneous vector.	
	 */

	class IISUSDK_API Vector4
	{
	public:

		//*********** Constructor and access ***********

		/**
		 * \fn	Vector4::Vector4(void);
		 *
		 * \brief	Default constructor.
		 *		 
		 *	Initializes to ZERO
		 */

		Vector4(void);

		/**
		 * \fn	Vector4::Vector4(float x, float y, float z, float w);
		 *
		 * \brief	Explicit constructor from coefficients.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 * \param	z	The z coordinate.
		 * \param	w	The width.
		 */

		Vector4(float x, float y, float z, float w);

		/**
		 * \fn	Vector4::Vector4(const Vector4& other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		Vector4(const Vector4& other);

		/**
		 * \fn	explicit Vector4::Vector4( const float* pValues );
		 *
		 * \brief	Constructor from an array of values.
		 *
		 * \param	pValues	The values.
		 */

		explicit Vector4( const float* pValues );

		//! coordinate access
		float& operator[] (int32_t i);
		//! coordinate access
		const float& operator[] (int32_t i) const;

		//*********** Assignment and comparison ***********

		//! assignment
		Vector4& operator= (const Vector4& other);
		//! test for equality
		bool operator== (const Vector4& other) const;
		//! test for inequality
		bool operator!= (const Vector4& other) const;

		//*********** Arithmetic operations ***********

		//! addition
		Vector4 operator+ (const Vector4& other) const;
		//! subtraction
		Vector4 operator- (const Vector4& other) const;	
		//! uniform scaling
		Vector4 operator* (float scalar) const;
		//! uniform scaling
		friend Vector4 operator* (float scalar, const Vector4& other);		
		//! uniform scaling
		Vector4 operator/ (float scalar) const;	
		//! negation
		Vector4 operator- () const;
		//! multiply component by component
		Vector4 operator * ( const Vector4& other ) const;

		//*********** Arithmetic updates ***********

		//! addition
		Vector4& operator+= (const Vector4& other);
		//! subtraction
		Vector4& operator-= (const Vector4& other);
		//! uniform scaling
		Vector4& operator*= (float scalar);
		//! uniform scaling
		Vector4& operator/= (float scalar);
		//! multiply component by component
		Vector4& operator*= (const Vector4& other);

		//*********** Vector operations ***********

		//! Returns the length (magnitude) of the vector. 
		float length () const;

		//! Returns the square of the length(magnitude) of the vector
		float squaredLength () const;

		//! Calculates the dot (scalar) product of this vector with another. 
		float dot (const Vector4& other) const;

		//! Returns true if this vector is zero length. 
		bool isZeroLength ( void ) const;

		//! Returns the distance to another vector.
		/** 
		@warning
		This operation requires a square root and is expensive in
		terms of CPU operations. If you don't need to know the exact
		distance (e.g. for just comparing distances) use squaredDistance()
		instead.
		*/
		float distance ( const Vector4& other ) const;

		//! Returns the square of the distance to another vector. 
		float squaredDistance ( const Vector4& other ) const;
		//! Sets this vector's components to the minimum of its own and the	ones of the passed in vector.
		/** 
		@remarks
		'Minimum' in this case means the combination of the lowest
		value of x, y, z and w from both vectors. Lowest is taken just
		numerically, not magnitude, so -1 < 0.
		*/
		void makeFloor ( const Vector4& cmp );

		//! Sets this vector's components to the maximum of its own and the ones of the passed in vector.
		/** 
		@remarks
		'Maximum' in this case means the combination of the highest
		value of x, y, z and w from both vectors. Highest is taken just
		numerically, not magnitude, so 1 > -3.
		*/
		void makeCeil ( const Vector4& cmp );

		//! Return false if one of the components of the vector is not a valid number. (Infinite or NaN)
		bool isValid() const;

		/** Function for writing to a stream.
		*/

		inline friend std::ostream& operator <<
			(std::ostream& o, const Vector4& v )
		{
			o << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
			return o;
		}

		// member access (allows V.x or V[0], V.y or V[1])
		float x,y,z,w;

		// special points
		///< The zero vector
		static const Vector4 ZERO;
	};



}//end of namespace SK

#ifndef SK_DEBUG
#include "Vector4.inl"
#endif

