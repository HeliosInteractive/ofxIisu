#pragma once

#include <System/Math/Math.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <ostream>

namespace  SK 
{

	class
		Quaternion;

	/**
	 * \class	Matrix3
	 *
	 * \brief	Implementation of a 3x3 matrix which can represent rotations around axes.
	 *	        The coordinate system is assumed to be <b>right-handed</b>.
	 *          Members are stored in ROW MAJOR LAYOUT.
	 */

	class IISUSDK_API Matrix3
	{
	public:

		//! Members are stored in ROW MAJOR LAYOUT.
		float	_11, _12, _13;
		float	_21, _22, _23;
		float	_31, _32, _33;

 		/**
		 * \fn	Matrix3::Matrix3 ()
		 *
		 * \brief	Default constructor.
		 *		    Initializes the matrix to IDENTITY
		 */

		Matrix3 () { *this = IDENTITY; }


		/**
		 * \fn	explicit Matrix3::Matrix3 ( float m11, float m12, float m13, float m21, float m22,
		 * 		float m23, float m31, float m32, float m33 );
		 *
		 * \brief	Explicit complete constructor in ROW MAJOR LAYOUT.
		 *
		 * \param	m11	The element (1,1).
		 * \param	m12	The element (1,2).
		 * \param	m13	The element (1,3).
		 * \param	m21	The element (2,1).
		 * \param	m22	The element (2,2).
		 * \param	m23	The element (2,3).
		 * \param	m31	The element (3,1).
		 * \param	m32	The element (3,2).
		 * \param	m33	The element (3,3).
		 */

		explicit Matrix3 (
			float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33 );

		/**
		 * \fn	explicit Matrix3::Matrix3 (const Vector3 &xAxis, const Vector3 &yAxis,
		 * 		const Vector3 &zAxis);
		 *
		 * \brief	Constructor via 3 orthogonal axes.
		 *
		 * \param	xAxis	The x coordinate axis.
		 * \param	yAxis	The y coordinate axis.
		 * \param	zAxis	The z coordinate axis.
		 */

		explicit Matrix3 (const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);

		/**
		 * \fn	float& Matrix3::operator()(uint32_t row, uint32_t col);
		 *
		 * \brief	Accessor.
		 */

		float& operator()(uint32_t row, uint32_t col);

		/**
		 * \fn	float Matrix3::operator()(uint32_t row, uint32_t col) const;
		 *
		 * \brief	Accessor.
		 */

		float operator()(uint32_t row, uint32_t col) const;

		/**
		 * \fn	Vector3 Matrix3::getColumn (int32_t colId) const;
		 *
		 * \brief	Gets a column.
		 *
		 * \param	colId	Identifier for the col.
		 *
		 * \return	The column.
		 */

		Vector3 getColumn (int32_t colId) const;

		//*********** Assignment and comparison ***********			


		/**
		 * \fn	bool Matrix3::operator== (const Matrix3& other) const;
		 *
		 * \brief	Equality operator.
		 *
		 * \param	other	The other matrix.
		 *
		 * \return	true if the matrices are strictly equal.
		 */

		bool operator== (const Matrix3& other) const;
		//! test for strict inequality

		/**
		 * \fn	bool Matrix3::operator!= (const Matrix3& other) const;
		 *
		 * \brief	Inequality operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	true if the matrices are strictly unequal.
		 */

		bool operator!= (const Matrix3& other) const;

		//*********** Algebra operations ***********

		/**
		 * \fn	Matrix3 Matrix3::operator+ (const Matrix3& other) const;
		 *
		 * \brief	Addition operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 operator+ (const Matrix3& other) const;

		/**
		 * \fn	Matrix3 Matrix3::operator- (const Matrix3& other) const;
		 *
		 * \brief	subtraction operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 operator- (const Matrix3& other) const;

		/**
		 * \fn	Matrix3 Matrix3::operator* (float scalar) const;
		 *
		 * \brief	Scalar multiplication operator.
		 *
		 * \param	scalar	The scalar.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 operator* (float scalar) const;

		/**
		 * \fn	friend Matrix3 Matrix3::operator* (float scalar, const Matrix3& other);
		 *
		 * \brief	Scalar multiplication operator.
		 *
		 * \param	scalar	The first value to multiply.
		 * \param	other 	The matrix to be scaled.
		 *
		 * \return	The result of the operation.
		 */

		friend Matrix3 operator* (float scalar, const Matrix3& other);		

		/**
		 * \fn	Matrix3 Matrix3::operator/ (float scalar) const;
		 *
		 * \brief	Scalar division operator.
		 *
		 * \param	scalar	The scalar.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 operator/ (float scalar) const;
		//! negation

		/**
		 * \fn	Matrix3 Matrix3::operator- () const;
		 *
		 * \brief	Negation operator.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 operator- () const;

		/**
		 * \fn	Matrix3 Matrix3::concatenate(const Matrix3 &m2) const;
		 *
		 * \brief	Matrix multiplication (cross product).
		 *
		 * \param	m2	The second matrix.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 concatenate(const Matrix3 &m2) const;

		/**
		 * \fn	Matrix3 Matrix3::operator* ( const Matrix3& other ) const;
		 *
		 * \brief	Matrix multiplication operator (cross product).
		 *
		 * \param	other	The second matrix.
		 *
		 * \return	The result of the operation.
		 */

		Matrix3 operator * ( const Matrix3& other ) const;

		//! Vector3 transformation using '*'

		/**
		 * \fn	Vector3 Matrix3::operator* (const Vector3& v) const;
		 *
		 * \brief	Vector transformation operator (cross product).
		 *
		 * \param	v	The vector to be transformed.
		 *
		 * \return	The result of the operation.
		 */

		Vector3 operator* (const Vector3& v) const;

		//! matrix transpose
		Matrix3 transpose () const;			

		bool inverse (Matrix3& rkInverse, float fTolerance = 1e-06) const;
		Matrix3 inverse (float fTolerance = 1e-06) const;

		/**
		 * \fn	float Matrix3::determinant () const;
		 *
		 * \brief	computes the determinant of the matrix.
		 *
		 * \return	The result of the operation.
		 */

		float determinant () const;

		// singular value decomposition

		/**
		 * \fn	void Matrix3::singularValueDecomposition (Matrix3& rkL, Vector3& rkS, Matrix3& rkR) const;
		 *
		 * \brief	Singular value decomposition (m = L x S x R).
		 *
		 * \param [out]	rkL	The matrix L.
		 * \param [out]	rkS	The matrix S.
		 * \param [out]	rkR	The matrix R.
		 */

		void singularValueDecomposition (Matrix3& rkL, Vector3& rkS, Matrix3& rkR) const;

		/**
		 * \fn	void Matrix3::singularValueComposition (const Matrix3& rkL, const Vector3& rkS,
		 * 		const Matrix3& rkR);
		 *
		 * \brief	Singular value composition.
		 *
		 * \param 	rkL	The matrix L.
		 * \param 	rkS	The matrix S.
		 * \param 	rkR	The matrix R.
		 */

		void singularValueComposition (const Matrix3& rkL,	const Vector3& rkS, const Matrix3& rkR);

		// Gram-Schmidt orthonormalization (applied to columns of rotation matrix)

		/**
		 * \fn	void Matrix3::orthonormalize ();
		 *
		 * \brief	Gram-Schmidt orthonormalization (applied to columns of rotation matrix).
		 */

		void orthonormalize ();

		// orthogonal Q, diagonal D, upper triangular U stored as (u01,u02,u12)

		/**
		 * \fn	void Matrix3::QDUDecomposition (Matrix3& rkQ, Vector3& rkD, Vector3& rkU) const;
		 *
		 * \brief	QDU decomposition.
		 *
		 * \param [out]	rkQ	The matrix Q.
		 * \param [out]	rkD	The vector d.
		 * \param [out]	rkU	The vector u.
		 */

		void QDUDecomposition (Matrix3& rkQ, Vector3& rkD,
			Vector3& rkU) const;

		/**
		 * \fn	float Matrix3::spectralNorm () const;
		 *
		 * \brief	Gets the spectral norm.
		 *
		 * \return	The result of the operation.
		 */

		float spectralNorm () const;

		//*********** Type conversion ***********

		/**
		 * \fn	void Matrix3::fromMatrix4(const Matrix4& m4x4);
		 *
		 * \brief	Initializes this object from the given matrix 4.
		 *
		 * \param	m4x4	The Matrix4.
		 */

		void fromMatrix4(const Matrix4& m4x4);

		/**
		 * \fn	void Matrix3::fromQuaternion(const Quaternion &rot);
		 *
		 * \brief	Initializes this object from the given quaternion.
		 *
		 * \param	rot	The quaternion.
		 */

		void fromQuaternion(const Quaternion &rot);

		/**
		 * \fn	void Matrix3::fromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);
		 *
		 * \brief	Initializes this object from the given orthogonal axes.
		 *
		 * \param	xAxis	The x coordinate axis.
		 * \param	yAxis	The y coordinate axis.
		 * \param	zAxis	The z coordinate axis.
		 */

		void fromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);

		/**
		 * \fn	void Matrix3::fromRotationVector(const Vector3 &rotVec);
		 *
		 * \brief	Initializes this object from the given rotation vector.
		 *
		 * \param	rotVec	The rotation vector.
		 */

		void fromRotationVector(const Vector3 &rotVec);

		/**
		 * \fn	void Matrix3::fromAxisAngle (const Vector3& rkAxis, float fRadians);
		 *
		 * \brief	Initializes this object from the given rotation axis and rotation angle.
		 *
		 * \param	rkAxis  	The rotation axis.
		 * \param	fRadians	The angle (radians).
		 */

		void fromAxisAngle (const Vector3& rkAxis, float fRadians);

		/**
		 * \fn	void Matrix3::toMatrix4(Matrix4& m4x4) const;
		 *
		 * \brief	Converts to a Matrix4.
		 *
		 * \param [out]	m4x4	The Matrix4.
		 */

		void toMatrix4(Matrix4& m4x4) const;

		/**
		 * \fn	void Matrix3::toQuaternion(Quaternion& quat) const;
		 *
		 * \brief	Converts a quat to a quaternion.
		 *
		 * \param [out]	quat	The quaternion.
		 */

		void toQuaternion(Quaternion& quat) const;

		/**
		 * \fn	void Matrix3::toAxes(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const;
		 *
		 * \brief	Converts this object to the orthogonal axes.
		 *
		 * \param [out]	xAxis	The x coordinate axis.
		 * \param [out]	yAxis	The y coordinate axis.
		 * \param [out]	zAxis	The z coordinate axis.
		 */

		void toAxes(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const;

		/**
		 * \fn	void Matrix3::toRotationVector(Vector3 &rotVec) const;
		 *
		 * \brief	Converts this object to a rotation vector.
		 *
		 * \param [out]	rotVec	The rotation vector.
		 */

		void toRotationVector(Vector3 &rotVec) const;

		/**
		 * \fn	void Matrix3::toAxisAngle (Vector3& rkAxis, float& rfRadians) const;
		 *
		 * \brief	Converts this object to rotation axis and angle.
		 *
		 * \param [out]	rkAxis   	The rotation axis.
		 * \param [out]	rfRadians	The angle in radians.
		 */

		void toAxisAngle (Vector3& rkAxis, float& rfRadians) const;

		/**
		 * \fn	Matrix4 Matrix3::toMatrix4() const;
		 *
		 * \brief	Converts this object to a matrix 4.
		 *
		 * \return	The Matrix4.
		 */

		Matrix4 toMatrix4() const;

		/**
		 * \fn	Quaternion Matrix3::toQuaternion() const;
		 *
		 * \brief	Converts this object to a quaternion.
		 *
		 * \return	The Quaternion.
		 */

		Quaternion toQuaternion() const;

		/**
		 * \fn	Vector3 Matrix3::toRotationVector() const;
		 *
		 * \brief	Converts this object to a rotation vector.
		 *
		 * \return	The Vector3.
		 */

		Vector3 toRotationVector() const;

		/**
		 * \fn	float Matrix3::extractAngle (int32_t i) const;
		 *
		 * \brief	Extracts the angle.
		 *
		 * \param	i	index of the.
		 *
		 * \return	The angle.
		 */

		float extractAngle (int32_t i) const;

		// The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
		// where yaw is rotation about the Up vector, pitch is rotation about the
		// Right axis, and roll is rotation about the Direction axis.

		/**
		 * \fn	bool Matrix3::toEulerAnglesXYZ (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;
		 *
		 * \brief	Converts to Euler angles (XYZ convention).
		 *
		 * \param [out]	rfYAngle	The Yaw angle.
		 * \param [out]	rfPAngle	The Pitch angle.
		 * \param [out]	rfRAngle	The Roll angle.
		 *
		 * \return	true if solution is unique, false if not.
		 */

		bool toEulerAnglesXYZ (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;

		/**
		 * \fn	bool Matrix3::toEulerAnglesXZY (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;
		 *
		 * \brief	Converts to Euler angles (XZY convention).
		 *
		 * \param [out]	rfYAngle	The Yaw angle.
		 * \param [out]	rfPAngle	The Pitch angle.
		 * \param [out]	rfRAngle	The Roll angle.
		 *
		 * \return	true if solution is unique, false if not.
		 */

		bool toEulerAnglesXZY (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;

		/**
		 * \fn	bool Matrix3::toEulerAnglesYXZ (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;
		 *
		 * \brief	Converts to Euler angles (YXZ convention).
		 *
		 * \param [out]	rfYAngle	The Yaw angle.
		 * \param [out]	rfPAngle	The Pitch angle.
		 * \param [out]	rfRAngle	The Roll angle.
		 *
		 * \return	true if solution is unique, false if not.
		 */

		bool toEulerAnglesYXZ (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;

		/**
		 * \fn	bool Matrix3::toEulerAnglesYZX (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;
		 *
		 * \brief	Converts to Euler angles (YZX convention).
		 *
		 * \param [out]	rfYAngle	The Yaw angle.
		 * \param [out]	rfPAngle	The Pitch angle.
		 * \param [out]	rfRAngle	The Roll angle.
		 *
		 * \return	true if solution is unique, false if not.
		 */

		bool toEulerAnglesYZX (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;

		/**
		 * \fn	bool Matrix3::toEulerAnglesZXY (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;
		 *
		 * \brief	Converts to Euler angles (ZXY convention).
		 *
		 * \param [out]	rfYAngle	The Yaw angle.
		 * \param [out]	rfPAngle	The Pitch angle.
		 * \param [out]	rfRAngle	The Roll angle.
		 *
		 * \return	true if solution is unique, false if not.
		 */

		bool toEulerAnglesZXY (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;

		/**
		 * \fn	bool Matrix3::toEulerAnglesZYX (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;
		 *
		 * \brief	Converts to Euler angles (ZYX convention).
		 *
		 * \param [out]	rfYAngle	The Yaw angle.
		 * \param [out]	rfPAngle	The Pitch angle.
		 * \param [out]	rfRAngle	The Roll angle.
		 *
		 * \return	true if solution is unique, false if not.
		 */

		bool toEulerAnglesZYX (float& rfYAngle, float& rfPAngle, float& rfRAngle) const;

		/**
		 * \fn	void Matrix3::fromEulerAnglesXYZ (float fYAngle, float fPAngle, float fRAngle);
		 *
		 * \brief	Initializes to three rotations XYZ.
		 *
		 * \param	fYAngle	The Yaw angle.
		 * \param	fPAngle	The Pitch angle.
		 * \param	fRAngle	The Roll angle.
		 */

		void fromEulerAnglesXYZ (float fYAngle, float fPAngle, float fRAngle);

		/**
		 * \fn	void Matrix3::fromEulerAnglesXZY (float fYAngle, float fPAngle, float fRAngle);
		 *
		 * \brief	Initializes to three rotations XZY.
		 *
		 * \param	fYAngle	The Yaw angle.
		 * \param	fPAngle	The Pitch angle.
		 * \param	fRAngle	The Roll angle.
		 */

		void fromEulerAnglesXZY (float fYAngle, float fPAngle, float fRAngle);

		/**
		 * \fn	void Matrix3::fromEulerAnglesYXZ (float fYAngle, float fPAngle, float fRAngle);
		 *
		 * \brief	Initializes to three rotations YXZ.
		 *
		 * \param	fYAngle	The Yaw angle.
		 * \param	fPAngle	The Pitch angle.
		 * \param	fRAngle	The Roll angle.
		 */

		void fromEulerAnglesYXZ (float fYAngle, float fPAngle, float fRAngle);

		/**
		 * \fn	void Matrix3::fromEulerAnglesYZX (float fYAngle, float fPAngle, float fRAngle);
		 *
		 * \brief	Initializes to three rotations YZX.
		 *
		 * \param	fYAngle	The Yaw angle.
		 * \param	fPAngle	The Pitch angle.
		 * \param	fRAngle	The Roll angle.
		 */

		void fromEulerAnglesYZX (float fYAngle, float fPAngle, float fRAngle);

		/**
		 * \fn	void Matrix3::fromEulerAnglesZXY (float fYAngle, float fPAngle, float fRAngle);
		 *
		 * \brief	Initializes to three rotations ZXY.
		 *
		 * \param	fYAngle	The Yaw angle.
		 * \param	fPAngle	The Pitch angle.
		 * \param	fRAngle	The Roll angle.
		 */

		void fromEulerAnglesZXY (float fYAngle, float fPAngle, float fRAngle);

		/**
		 * \fn	void Matrix3::fromEulerAnglesZYX (float fYAngle, float fPAngle, float fRAngle);
		 *
		 * \brief	Initializes to three rotations ZYX.
		 *
		 * \param	fYAngle	The Yaw angle.
		 * \param	fPAngle	The Pitch angle.
		 * \param	fRAngle	The Roll angle.
		 */

		void fromEulerAnglesZYX (float fYAngle, float fPAngle, float fRAngle);

		// Geometric operations

		/**
		 * \fn	void Matrix3::initRotateX(const float&);
		 *
		 * \brief	Initializes to a rotation around the x axis of an angle fAngle.
		 *
		 * \param	fAngle	The angle.
		 */

		void initRotateX(const float& fAngle);

		/**
		 * \fn	void Matrix3::initRotateY(const float&);
		 *
		 * \brief	Initializes to a rotation around the y axis of an angle fAngle.
		 *
		 * \param	fAngle	The angle.
		 */

		void initRotateY(const float& fAngle);

		/**
		 * \fn	void Matrix3::initRotateZ(const float&);
		 *
		 * \brief	Initializes to a rotation around the z axis of an angle fAngle.
		 *
		 * \param	fAngle	The angle.
		 */

		void initRotateZ(const float& fAngle);

		/**
		 * \fn	void Matrix3::initRotate(const float& fAngle, const float& fx, const float& fy,
		 * 		const float& fz, const bool& bnorm=true);
		 *
		 * \brief	Initializes to a rotation axis of angle fAngle.
		 *
		 * \param	fAngle	The angle.
		 * \param	fx	  	The x coordinate of the rotation axis.
		 * \param	fy	  	The y coordinate of the rotation axis.
		 * \param	fz	  	The z coordinate of the rotation axis.
		 * \param	bnorm 	(optional) flag indicating the axis must be normalized.
		 */

		void initRotate(const float& fAngle, const float& fx, const float& fy, const float& fz, const bool& bnorm=true);

		/**
		 * \fn	void Matrix3::rotateX(const float&);
		 *
		 * \brief	Rotate around y axis.
		 *
		 * \param	fAngle	The angle of rotation (radians).
		 */

		void rotateX(const float& fAngle);

		/**
		 * \fn	void Matrix3::rotateY(const float&);
		 *
		 * \brief	Rotate around the y axis.
		 *
		 * \param	fAngle	The angle of rotation (radians).
		 */

		void rotateY(const float& fAngle);

		/**
		 * \fn	void Matrix3::rotateZ(const float&);
		 *
		 * \brief	Rotate around z axis.
		 *
		 * \param	fAngle	The angle of rotation (radians).
		 */

		void rotateZ(const float& fAngle);

		/**
		 * \fn	void Matrix3::scale(const float& fSx,const float& fSy,const float& fSz);
		 *
		 * \brief	Scales the rotation axes.
		 *
		 * \param	fSx	The scale factor for the x axis.
		 * \param	fSy	The scale factor for the y axis.
		 * \param	fSz	The scale factor for the z axis.
		 */

		void scale(const float& fSx,const float& fSy,const float& fSz);

		// eigensolver, matrix must be symmetric

		/**
		 * \fn	void Matrix3::eigenSolveSymmetric (float afEigenvalue[3], Vector3 akEigenvector[3]) const;
		 *
		 * \brief	Eigen solver (matrix is supposed to be symmetric).
		 *
		 * \param	afEigenvalue 	The eigenvalues.
		 * \param	akEigenvector	The eigenvectors.
		 */

		void eigenSolveSymmetric (float afEigenvalue[3],
			Vector3 akEigenvector[3]) const;

		/**
		 * \fn	static void Matrix3::tensorProduct (const Vector3& rkU, const Vector3& rkV,
		 * 		Matrix3& rkProduct);
		 *
		 * \brief	Tensor product.
		 *
		 * \param	rkU				 	The first vector.
		 * \param	rkV				 	The second vector.
		 * \param [out]	rkProduct	The result of the operation.
		 */

		static void tensorProduct (const Vector3& rkU, const Vector3& rkV,
			Matrix3& rkProduct);

		/**
		 * \fn	inline friend std::ostream& Matrix3::operator<< (std::ostream& o, const Matrix3& m )
		 *
		 * \brief	Stream output operator.
		 *
		 * \param [in,out]	o	The output stream.
		 * \param	m		 	The matrix.
		 *
		 * \return	The updated output stream.
		 */

		inline friend std::ostream& operator << (std::ostream& o, const Matrix3& m ) 	
		{
			o << "Matrix3(";
			for (size_t i = 0; i < 3; ++i)
			{
				o << " row" << (unsigned)i << "{";
				for(size_t j = 0; j < 3; ++j)
				{
					o << m(i, j) << " ";
				}
				o << "}";
			}
			o << ")";
			return o;
		}

		// support for eigensolver
		void tridiagonal (float afDiag[3], float afSubDiag[3]);
		bool QLAlgorithm (float afDiag[3], float afSubDiag[3]);
	protected:
		

		// support for singular value decomposition
		static const float ms_fSvdEpsilon;
		static const int32_t ms_iSvdMaxIterations;
		static void bidiagonalize (Matrix3& kA, Matrix3& kL,
			Matrix3& kR);
		static void golubKahanStep (Matrix3& kA, Matrix3& kL,
			Matrix3& kR);

		// support for spectral norm
		static float maxCubicRoot (float afCoeff[3]);

	public: 
		static const float EPSILON;
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;
	};


}//end of namespace SK

#ifndef SK_DEBUG
#include "Matrix3.inl"
#endif
