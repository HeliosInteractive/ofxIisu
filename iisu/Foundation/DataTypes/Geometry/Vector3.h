#pragma once

#include <System/Math/Math.h>
#include <Platform/SkPlatform.h>
#include <ostream>

namespace SK
{

	class Quaternion;
	class Matrix3;
	class Matrix4;
	class Frame;

	/**
	 * \class	Vector3
	 *
	 * \brief	3-dimensional vector.
	 */

	class IISUSDK_API Vector3 
	{
	public:
		//*********** Constructor and access ***********

		/**
		 * \fn	Vector3::Vector3 (void);
		 *
		 * \brief	Default constructor.
		 *	Initializes to ZERO.
		 */

		Vector3 (void);

		/**
		 * \fn	Vector3::Vector3 (float x, float y, float z);
		 *
		 * \brief	Explicit constructor from coefficients.
		 *
		 * \param	x	The x coordinate.
		 * \param	y	The y coordinate.
		 * \param	z	The z coordinate.
		 */

		Vector3 (float x, float y, float z);

		/**
		 * \fn	Vector3::Vector3 (const Vector3& other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other vector.
		 */

		Vector3 (const Vector3& other);

		/**
		 * \fn	explicit Vector3::Vector3( const float* pValues );
		 *
		 * \brief	Constructor from an array of values.
		 *
		 * \param	pValues	The values.
		 */

		explicit Vector3( const float* pValues );

		//! coordinate access
		float& operator[] (int32_t i);
		//! coordinate access
		const float& operator[] (int32_t i) const;

		/**
		 * \fn	void Vector3::fromQuaternion(const Quaternion& quat);
		 *
		 * \brief	Initializes this object from a quaternion.
		 *
		 * \param	quat	The quaternion.
		 */

		void fromQuaternion(const Quaternion& quat);

		/**
		 * \fn	void Vector3::fromMatrix3(const Matrix3& m3x3);
		 *
		 * \brief	Initializes this object from a 3x3 matrix.
		 *
		 * \param	m3x3	The 3x3 matrix.
		 */

		void fromMatrix3(const Matrix3& m3x3);

		/**
		 * \fn	void Vector3::fromMatrix4(const Matrix4& m4x4);
		 *
		 * \brief	Initializes this object from a 4x4 matrix.
		 *
		 * \param	m3x3	The 4x4 matrix.
		 */

		void fromMatrix4(const Matrix4& m4x4);

		/**
		 * \fn	void Vector3::toQuaternion(Quaternion& quat) const;
		 *
		 * \brief	Converts this object to a quaternion.
		 *
		 * \param [out]	quat	The quaternion.
		 */

		void toQuaternion(Quaternion& quat) const;

		/**
		 * \fn	void Vector3::toMatrix3(Matrix3& m3x3) const;
		 *
		 * \brief	Converts this object to a matrix 3.
		 *
		 * \param [out]	m3x3	The 3x3 matrix.
		 */

		void toMatrix3(Matrix3& m3x3) const;

		/**
		 * \fn	void Vector3::toMatrix4(Matrix4& m4x4) const;
		 *
		 * \brief	Converts this object to a 4x4 matrix.
		 *
		 * \param [in,out]	m4x4	The 4x4 matrix.
		 */

		void toMatrix4(Matrix4& m4x4) const;

		/**
		 * \fn	Quaternion Vector3::toQuaternion() const;
		 *
		 * \brief	Converts this object to a quaternion.
		 *
		 * \return	This object as a Quaternion.
		 */

		Quaternion toQuaternion() const;

		/**
		 * \fn	Matrix3 Vector3::toMatrix3() const;
		 *
		 * \brief	Converts this object to a 3x3 matrix.
		 *
		 * \return	This object as a Matrix3.
		 */

		Matrix3 toMatrix3() const;

		/**
		 * \fn	Matrix4 Vector3::toMatrix4() const;
		 *
		 * \brief	Converts this object to a 4x4 matrix.
		 *
		 * \return	This object as a Matrix4.
		 */

		Matrix4 toMatrix4() const;

		//*********** Assignment and comparison ***********

		/// assignment
		Vector3& set(float _x, float _y, float _z);

		/// Equality with tolerance 
		bool equals ( const Vector3& other, const float tolerance  = Math::ZERO_TOLERANCE) const;
		//Vector3& operator= (const Vector3& other);
		//! test for equality
		bool operator== (const Vector3& other) const;
		//! test for inequality
		bool operator!= (const Vector3& other) const;

		//*********** Arithmetic operations ***********

		//! addition
		Vector3 operator+ (const Vector3& other) const;
		//! subtraction
		Vector3 operator- (const Vector3& other) const;	
		//! uniform scaling
		Vector3 operator* (float scalar) const;
		//! uniform scaling
		friend Vector3 IISUSDK_API operator* (float scalar, const Vector3& other);		
		//! uniform scaling
		Vector3 operator/ (float scalar) const;	
		//! negation
		Vector3 operator- () const;
		//! multiply component by component
		Vector3 operator * ( const Vector3& other ) const;

		//*********** Arithmetic updates ***********

		//! addition
		Vector3& operator+= (const Vector3& other);
		//! subtraction
		Vector3& operator-= (const Vector3& other);
		//! uniform scaling
		Vector3& operator*= (float scalar);
		//! uniform scaling
		Vector3& operator/= (float scalar);
		//! multiply component by component
		Vector3& operator*= (const Vector3& other);

		//*********** Vector operations ***********

		//! Returns the length (magnitude) of the vector. 
		float length () const;

		//! Returns the square of the length(magnitude) of the vector
		float squaredLength () const;

		//! Normalizes this vector and return it's previous length
		float normalize (float tolerance = Math::ZERO_TOLERANCE);

		//! As normalize, except that this vector is unaffected and the normalized vector is returned as a copy. 
		Vector3 normalizedCopy (void) const	;

		//! Calculates the dot (scalar) product of this vector with another. 
		float dot (const Vector3& other) const;

		//! Calculates the cross-product of this vector with another.
		Vector3 cross (const Vector3& other) const;

		//! Calculates the normalized cross-product of this vector with another.
		Vector3 unitCross (const Vector3& other) const;

		//! Generates a vector perpendicular to this vector (eg an 'up' vector). 
		Vector3 perpendicular(void) const;			

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
		float distance ( const Vector3& other ) const;

		//! Returns the square of the distance to another vector. 
		float squaredDistance ( const Vector3& other ) const;

		//! Sets this vector's components to the minimum of its own and the	ones of the passed in vector.
		/** 
		@remarks
		'Minimum' in this case means the combination of the lowest
		value of x, y and z from both vectors. Lowest is taken just
		numerically, not magnitude, so -1 < 0.
		*/
		void makeFloor ( const Vector3& cmp );

		//! Sets this vector's components to the maximum of its own and the ones of the passed in vector.
		/** 
		@remarks
		'Maximum' in this case means the combination of the highest
		value of x, y and z from both vectors. Highest is taken just
		numerically, not magnitude, so 1 > -3.
		*/
		void makeCeil ( const Vector3& cmp );

		//! Calculates a reflection vector to the plane with the given normal . 
		Vector3 reflect( const Vector3& normal) const;

		//! Return false if one of the components of the vector is not a valid number. (Infinite or NaN)
		bool isValid() const;

		//! Transform pt (seen as a point not a vector) by frame, store the result in this.
		static Vector3 TransformPoint(const Frame& frame, const Vector3& pt);

		//! Transform pt (seen as a vector not a point, so this is only a rotation) by frame, store the result in this.
		static Vector3 RotateVector(const Frame& frame, const Vector3& vec);

		//! Transform pt (seen as a vector not a point, so this is only a rotation) by quat, store the result in this.
		static Vector3 RotateVector(const Quaternion& quat, const Vector3& vec);

		//! Transform pt (seen as a point not a vector) by the inverse of frame, store the result in this.
		static Vector3 InverseTransformPoint(const Frame& frame, const Vector3& pt);

		//! Transform pt (seen as a vector not a point, so this is only a rotation) by the inverse of frame, store the result in this.
		static Vector3 InverseRotateVector(const Frame& frame, const Vector3& vec);

		//! Transform pt (seen as a vector not a point, so this is only a rotation) by the inverse of quat, store the result in this.
		static Vector3 InverseRotateVector(const Quaternion& quat, const Vector3& vec);

		//! Get the shortest rotation that takes the source vector to the destination vector. 
		static Vector3 GetRotationBetween(const Vector3& source, const Vector3& destination, const Vector3& fallbackAxis, float epsilon = 1e-4f);

		//! Generate an orthonormal basis: (unit length, mutually perpendicular).
		/** Input W must be initialize to a nonzero vector, output is {U,V,W}
		an orthonormal basis.  A hint is provided about whether or not W
		is already unit length.
		*/
		static void generateOrthonormalBasis (Vector3& uOutputAxis, Vector3& vOutputAxis, Vector3& wInputAxis, bool unitLengthW = true);

		//! Gram-Schmidt orthonormalization.
		/** Take linearly independent vectors X and Y, Z and compute 
		an orthonormal set (unit length, mutually perpendicular).  
		*/
		static void orthonormalize (Vector3& xAxis, Vector3& yAxis, Vector3& zAxis);	

		//! Computes the unsigned angle in radian between 2 arbitrary non ZERO vectors
		static float unsignedAngle(const Vector3& v1, const Vector3& v2);

		//! Computes the signed angle in radian between 2 arbitrary non ZERO vectors, using a reference vector for the sign.
		static float signedAngle(const Vector3& v1, const Vector3& v2, const Vector3& reference);
		
		/** Function for writing to a stream.
		*/
		inline friend std::ostream& operator <<
			( std::ostream& o, const Vector3& v )
		{
			o << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
			return o;
		}

		// member access (allows V.x or V[0], V.y or V[1], V.z or V[2])
		float x, y, z;

	public:
		// special points
		///< The zero vector
		static const Vector3 ZERO;
		///< The all one vector
		static const Vector3 ONE;	
		///< The unit vector (x)
		static const Vector3 UNIT_X;
		///< The unit vector (y)
		static const Vector3 UNIT_Y;
		///< The unit vector (z)
		static const Vector3 UNIT_Z;
	};

}//end of namespace SK

#ifndef SK_DEBUG
#include "Vector3.inl"
#endif
