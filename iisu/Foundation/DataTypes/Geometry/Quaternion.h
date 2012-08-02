/*
NOTE THAT THIS FILE IS BASED ON MATERIAL FROM:

Magic Software, Inc.
http://www.geometrictools.com/
Copyright (c) 2000, All Rights Reserved

and from swarmanoid 3D math library
credits to: Javier Martinez.
*/
#pragma once

#include <System/Math/Math.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Geometry/Vector2.h>
#include <ostream>

namespace SK 
{
	class Matrix3;
	class Matrix4;

	/**
	 * \class	Quaternion
	 *
	 * \brief	Representation of a Quaternion, i.e. a rotation around an axis.
	 */

	class IISUSDK_API Quaternion
	{
	public:
		// ************** DATA **************
		float x, y, z, w;

		//*********** Constructor and access ***********

		//! Empty constructor: initialize to IDENTITY
		Quaternion ();
		//! Construct a quaternion from 4 manual w/x/y/z values
		Quaternion ( float w, float x, float y, float z );

		Quaternion ( const Quaternion& quat );
		//! Construct a quaternion from a rotation matrix
		explicit Quaternion ( const Matrix3& m3x3 );
		//! Construct a quaternion from a homogeneous matrix
		explicit Quaternion ( const Matrix4& m4x4 );
		//! Construct a quaternion from an angle/axis
		Quaternion ( float angle, const Vector3& axis );
		//! Construct a quaternion from 3 orthonormal local axes
		Quaternion ( const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis );
		//! Construct from a rotation vector.
		Quaternion ( const Vector3& rotVec );

		//! Pointer access for direct copying
		float* ptr();

		//! Pointer access for direct copying
		const float* ptr() const;

		//! init this quaternion from a 3x3 rotation matrix
		//  \warning YOU MAY GET A NON-NORMALIZED QUATERNION AS OUTPUT of fromMatrix3
		void fromMatrix3 ( const Matrix3& m3x3 );
		//! init this quaternion from the rotational part of a 4x4 homogeneous matrix
		//  \warning YOU MAY GET A NON-NORMALIZED QUATERNION AS OUTPUT of fromMatrix4
		void fromMatrix4 ( const Matrix4& m4x4 );
		//! init this quaternion from a rotation vector
		void fromRotationVector ( const Vector3& rotVec );
		/** init a quaternion from an angle/axis
		*  \pre (x, y, z) <b>must</b> be a unit vector.
		*/
		//! init this quaternion from a rotation axis and an angle
		void fromAngleAxis ( const float& angle, const Vector3& axis );
		//! init this quaternion from 3 orthonormal local axes
		//  \warning YOU MAY GET A NON-NORMALIZED QUATERNION AS OUTPUT of fromAxes
		void fromAxes ( const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis );

		/**
		 * \fn	void Quaternion::fromSwingTwist(const Vector3& swingTwist, float epsilon = 1e-4f);
		 *
		 * \brief	.
		 *
		 * \param	swingTwist	The swing twist.
		 * \param	epsilon   	(optional) the epsilon.
		 */

		void fromSwingTwist(const Vector3& swingTwist, float epsilon = 1e-4f);


		// QuaternionCheckFlag clean & comment

		/**
		 * \fn	void Quaternion::toMatrix3( Matrix3& m3x3 ) const;
		 *
		 * \brief	Converts to a 3x3 matrix.
		 *
		 * \param [out]	m3x3	The 3x3 matrix.
		 */

		void toMatrix3( Matrix3& m3x3 ) const;

		/**
		 * \fn	void Quaternion::toMatrix4( Matrix4& m4x4 ) const;
		 *
		 * \brief	Converts to a 4x4 matrix.
		 *
		 * \param [out]	m4x4	The 4x4 matrix.
		 */

		void toMatrix4( Matrix4& m4x4 ) const;

		/**
		 * \fn	void Quaternion::toRotationVector ( Vector3& rotVec ) const;
		 *
		 * \brief	Converts to a rotation vector.
		 *
		 * \param [out]	rotVec	The rotation vector.
		 */

		void toRotationVector ( Vector3& rotVec ) const;

		/**
		 * \fn	void Quaternion::toAngleAxis ( float& angle, Vector3& axis ) const;
		 *
		 * \brief	Converts this object to an angle axis.
		 *
		 * \param [out]	angle	The angle.
		 * \param [out]	axis 	The axis.
		 */

		void toAngleAxis ( float& angle, Vector3& axis ) const;

		/**
		 * \fn	void Quaternion::toAxes ( Vector3& xAxis, Vector3& yAxis, Vector3& zAxis ) const;
		 *
		 * \brief	Converts this object to the axes.
		 *
		 * \param [out]	xAxis	The x coordinate axis.
		 * \param [out]	yAxis	The y coordinate axis.
		 * \param [out]	zAxis	The z coordinate axis.
		 */

		void toAxes ( Vector3& xAxis, Vector3& yAxis, Vector3& zAxis ) const;

		/**
		 * \fn	void Quaternion::toSwingTwist(Vector3& swingTwist, float epsilon = 1e-4f) const;
		 *
		 * \brief	Converts this object to a swing twist.
		 *
		 * \param [out]	swingTwist	The swing twist vector.
		 * \param	epsilon			  	(optional) the tolerance.
		 */

		void toSwingTwist(Vector3& swingTwist, float epsilon = 1e-4f) const;

		/**
		 * \fn	Matrix3 Quaternion::toMatrix3() const;
		 *
		 * \brief	Converts this object to a matrix 3.
		 *
		 * \return	This object as a Matrix3.
		 */

		Matrix3 toMatrix3() const;

		/**
		 * \fn	Matrix4 Quaternion::toMatrix4() const;
		 *
		 * \brief	Converts this object to a matrix 4.
		 *
		 * \return	This object as a Matrix4.
		 */

		Matrix4 toMatrix4() const;

		/**
		 * \fn	Vector3 Quaternion::toRotationVector() const;
		 *
		 * \brief	Converts this object to a rotation vector.
		 *
		 * \return	The rotation Vector3.
		 */

		Vector3 toRotationVector() const;

		/**
		 * \fn	Vector3 Quaternion::toSwingTwist(float epsilon = 1e-4f) const;
		 *		 
		 * \brief	Converts this object to a swing twist.
		 *
		 * \param	epsilon			  	(optional) the tolerance.
		 *
		 * \return	The swing twist as a Vector3.
		 */

		Vector3 toSwingTwist(float epsilon = 1e-4f) const;


		/**
		 * \fn	Quaternion& Quaternion::setWXYZ(float _w, float _x, float _y, float _z);
		 *
		 * \brief	Sets the components.
		 *
		 * \param	_w	The w.
		 * \param	_x	The x coordinate.
		 * \param	_y	The y coordinate.
		 * \param	_z	The z coordinate.
		 *
		 * \return	This object.
		 */

		Quaternion& setWXYZ(float _w, float _x, float _y, float _z);

		/**
		 * \fn	Quaternion& Quaternion::setXYZW(float _x, float _y, float _z, float _w);
		 *
		 * \brief	Sets an xyzw.
		 *
		 * \param	_x	The x coordinate.
		 * \param	_y	The y coordinate.
		 * \param	_z	The z coordinate.
		 * \param	_w	The w.
		 *
		 * \return	This object.
		 */

		Quaternion& setXYZW(float _x, float _y, float _z, float _w);

		/// Get the local x-axis
		Vector3 xAxis ( void ) const;
		/// Get the local y-axis
		Vector3 yAxis ( void ) const;
		/// Get the local z-axis
		Vector3 zAxis ( void ) const;
		/// Get the rotation unit axis in case the quaternion is a rotation
		Vector3 rAxis ( float tolerance = 1e-06 ) const;

		/// Equality (on normalized quaternions) with tolerance (tolerance is max angle difference)
		bool equals ( const Quaternion& rhs, const float tolerance  = 1e-06) const;
		//! angle difference (on normalized quaternions) 
		float getAngleTo ( const Quaternion& rhs ) const;
		//! test for equality
		bool operator== ( const Quaternion& rhs ) const;
		//! test for inequality
		bool operator!= ( const Quaternion& rhs ) const;
		//! test for identity
		bool isIdentity ( float tolerance = 1e-4f) const;


		//! Add two quaternions
		Quaternion operator+ ( const Quaternion& rkQ ) const;
		//! Subtract a quaternion from another quaternion
		Quaternion operator- ( const Quaternion& rkQ ) const;
		//! Multiply two quaternions
		Quaternion operator* ( const Quaternion& rkQ ) const;
		//! Multiply a quaternion by a scalar
		Quaternion operator* ( float fScalar ) const;
		//! Divide a quaternion by a scalar
		Quaternion operator/ ( float fScalar ) const;
		//! Multiply a quaternion by a scalar
		friend Quaternion operator* ( float fScalar, const Quaternion& rkQ );			

		//! Perform compound assignment and addition with a quaternion
		Quaternion & operator +=( const Quaternion& q );
		//! Perform compound assignment and subtraction by a quaternion
		Quaternion & operator -=( const Quaternion& q );
		//! Perform compound assignment and multiplication by a quaternion
		Quaternion & operator *=( const Quaternion& q);
		//! Perform compound assignment and multiplication by a scalar
		Quaternion & operator *=( float scalar  );
		//! Perform compound assignment and division by a scalar
		Quaternion & operator /=( float scalar  );

		//! Negate all elements of a quaternion
		Quaternion operator- () const;

		//! dot product
		float dot ( const Quaternion& rkQ ) const;  
		//! length of the quaternion (norm)
		float length () const;
		//! squared length of the quaternion 
		float squaredLength () const;  // dot product
		// check if quaternion has a nonzero axis length
		bool hasAxes (float tolerance = 1e-06) const; 

		//! Normalize a quaternion (set length to 1)
		float normalize ( void );
		//! Normalize a quaternion if length is not close to 1.
		void normalizeIfNeeded ( void );
		//! As normalize, except that this vector is unaffected and the normalized vector is returned as a copy. 
		Quaternion getNormalized (void) const	;

		// apply to non-zero quaternion
		Quaternion getInverse () const;  
		// apply to unit-length quaternion
		Quaternion getUnitInverse () const;
		/** \return in-place conjugation. */
		Quaternion& conjugate();
		/** \return the conjugate quaternion. */
		Quaternion getConjugate() const;
		Quaternion getExp () const;
		Quaternion getLog () const;		

		/** \return the given vector transformed by the rotation represented by the given quaternion. 
		*  \pre the given quaternion <B>must</B> be normalized.
		*/
		Vector3 operator* ( const Vector3& rkVector ) const;

		//Careful ordering is important
		//TODO: clarify this
		/// Calculate the local roll element of this quaternion
		float getZYXRoll ( void ) const;
		/// Calculate the local pitch element of this quaternion
		float getZYXPitch ( void ) const;
		/// Calculate the local yaw element of this quaternion
		float getZYXYaw ( void ) const;		
		// when using EulerQuaternion, x,y,z of the quaternion are used as angles (and w=0).
		Quaternion toEulerQuaternion( void ) const;
		Quaternion fromEulerQuaternion( void ) const;

		//! Get the shortest rotation that takes the source vector to the destination vector. 
		static Quaternion GetRotationBetween ( const Vector3& source, const Vector3& destination, const Vector3& fallbackAxis );

		/// spherical linear interpolation
		static Quaternion Slerp ( float fT, const Quaternion& rkP,
			const Quaternion& rkQ, bool shortestPath = false );

		static Quaternion SlerpExtraSpins ( float fT,
			const Quaternion& rkP, const Quaternion& rkQ,
			int32_t iExtraSpins );

		/// setup for spherical quadratic interpolation
		static void Intermediate ( const Quaternion& rkQ0,
			const Quaternion& rkQ1, const Quaternion& rkQ2,
			Quaternion& rka, Quaternion& rkB );

		/// spherical quadratic interpolation
		static Quaternion Squad ( float fT, const Quaternion& rkP,
			const Quaternion& rkA, const Quaternion& rkB,
			const Quaternion& rkQ, bool shortestPath = false );

		/// normalized linear interpolation - faster but less accurate (non-constant rotation velocity)
		static Quaternion NLerp ( float fT, const Quaternion& rkP,
			const Quaternion& rkQ, bool shortestPath = false );

		/// Clamp quaternion using the swing-twist model.
		Quaternion clamp(const Quaternion& limitFrame, const SK::Vector2& swingLimit, const SK::Vector2& twistLimit);

		/**
		 * \fn	inline friend std::ostream& Quaternion::operator<< ( std::ostream& o, const Quaternion& q )
		 *
		 * \brief	Output stream operator.
		 *
		 * \param [in,out]	o	The output stream.
		 * \param	q		 	The quaternion.
		 *
		 * \return	The updated output stream.
		 */

		inline friend std::ostream& operator <<
			( std::ostream& o, const Quaternion& q )
		{
			o << "Quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
			return o;
		}



		/// special values
		static const Quaternion ZERO;
		static const Quaternion IDENTITY;

	protected:

		/// cutoff for sine near zero
		static const float ms_fEpsilon;

	};
}

#ifndef SK_DEBUG
#include "Quaternion.inl"
#endif

