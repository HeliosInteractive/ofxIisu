#pragma once

#include <System/Math/Math.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Geometry/Vector4.h>
#include <Foundation/DataTypes/Geometry/Matrix3.h>
#include <Foundation/DataTypes/Geometry/Quaternion.h>
#include <Foundation/DataTypes/Geometry/Frame.h>
#include <ostream>


namespace SK 
{


   /**
	* \class	Matrix4
	* \brief    4x4 homogeneous matrix.
	* 
	* If the equation system is written like this : <br/>
	*
	*   <code>
	* 	Xo = A*Xi + B*Yi + C*Zi + D*Wi  <br/>
	* 	Yo = E*Xi + F*Yi + G*Zi + H*Wi  <br/>
	*   Zo = J*Xi + K*Yi + L*Zi + M*Wi  <br/>
	*   Wo = N*Xi + O*Yi + P*Zi + Q*Wi  <br/>
	*   </code>
	*	
	*  (I is intentionally ommited to avoid confusion with Xi, Yi, Zi and Wi)
    *
	*   Our typesetting notation follows the mathematical standard notation:
	*   aka COLUMN VECTOR NOTATION (this notation is also used in the opengl manuals and most technical papers BUT is the opposite of DirectX notation)
	*   please use this notation when you write papers or documentation.
	*	
	*   <code>
	*   |X0| &nbsp; |A B C D| &nbsp; |Xi|  <br/>
	*   |Y0|   =    |E F G H|    *   |Yi|  <br/>
	*   |Z0| &nbsp; |J K L M| &nbsp; |Zi|  <br/>
	*   |W0| &nbsp; |N O P Q| &nbsp; |Wi|  <br/>
	* </code>
	*	
	*	Using standard indexed matrix notation:
	*	
    *   <code>
	*   |X0| &nbsp; |M11 M12 M13 M14| &nbsp; |Xi|  <br/>
	*   |Y0|   =    |M21 M22 M23 M24|    *   |Yi|  <br/>
	*   |Z0| &nbsp; |M31 M32 M33 M34| &nbsp; |Zi|  <br/>
	*   |W0| &nbsp; |M41 M42 M43 M44| &nbsp; |Wi|  <br/>
	*  </code>
	*	
	*   But, for efficiency reason (mainly SSE) and to be compatible with opengl AND DirectX,
	*   we store the coefficients in a COLUMN MAJOR LAYOUT !
	*   That mean the matrix is stored like this: (This is for implementation only !)
	*	
	*	<code>
	*   |M11 M21 M31 M41|  <br/>
	*   |M12 M22 M32 M42|  <br/>
	*	|M13 M23 M33 M43|  <br/>
	*	|M14 M24 M34 M44|  <br/>
	*</code>
	*	
	*	TRANSLATION IS STORED IN _14, _24, _34
	*  
	*   To reflect this, data on matrix are only accessible via  _IJ member variable !
	*/

	class IISUSDK_API Matrix4
	{
	

	public:
		//*********** Constructor and access ***********

		/**
		 * \fn	Matrix4::Matrix4()
		 *
		 * \brief	Default constructor.
		 *
		 *	Initializes the matrix to IDENTITY
		 */

		Matrix4() { operator=(IDENTITY); }
		/**
		 * \fn	Matrix4::Matrix4( float m11, float m12, float m13, float m14, float m21, float m22,
		 * 		float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42,
		 * 		float m43, float m44 );
		 *
		 * \brief	Explicit complete constructor in ROW MAJOR LAYOUT.
		 *
		 */

		Matrix4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44 );

		/**
		 * \fn	explicit Matrix4::Matrix4(const Vector3& xAxis, const Vector3& yAxis,
		 * 		const Vector3& zAxis);
		 *
		 * \brief	Constructor from the 3 axes of the frame.
		 *
		 * \param	xAxis	The x coordinate axis.
		 * \param	yAxis	The y coordinate axis.
		 * \param	zAxis	The z coordinate axis.
		 */

		explicit Matrix4(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Vector3& xAxis, const Vector3& yAxis,
		 * 		const Vector3& zAxis, const Vector3& translation);
		 *
		 * \brief	Constructor from the 3 axes of the frame and a translation.

		 *
		 * \param	xAxis	   	The x coordinate axis.
		 * \param	yAxis	   	The y coordinate axis.
		 * \param	zAxis	   	The z coordinate axis.
		 * \param	translation	The translation.
		 */

		explicit Matrix4(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& translation);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Vector3& rotVec);
		 *
		 * \brief	Constructor from a rotation vector.
		 *
		 * \param	rotVec	The rotation vector.
		 */

		explicit Matrix4(const Vector3& rotVec);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Vector3& rotVec, const Vector3& translation);
		 *
		 * \brief	Constructor from a rotation vector and a translation.
		 *
		 * \param	rotVec	   	The rotation vector.
		 * \param	translation	The translation.
		 */

		explicit Matrix4(const Vector3& rotVec, const Vector3& translation);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Matrix3& m3x3);
		 *
		 * \brief	Constructor from a 3x3 matrix.
		 *
		 * \param	m3x3	The 3x3 matrix.
		 */

		explicit Matrix4(const Matrix3& m3x3);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Matrix3& m3x3, const Vector3& translation);
		 *
		 * \brief	Constructor from a 3x3 matrix and a translation.
		 *
		 * \param	m3x3	The 3x3 matrix.
		 * \param	translation	The translation.
		 */

		explicit Matrix4(const Matrix3& m3x3, const Vector3& translation);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Quaternion& rot);
		 *
		 * \brief	Constructor from a quaternion.
		 *
		 * \param	rot	The quaternion.
		 */

		explicit Matrix4(const Quaternion& rot);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Quaternion& rot, const Vector3& translation);
		 *
		 * \brief	Constructor from a quaternion and a translation.
		 *
		 * \param	rot		   	The rot.
		 * \param	translation	The translation.
		 */

		explicit Matrix4(const Quaternion& rot, const Vector3& translation);

		/**
		 * \fn	explicit Matrix4::Matrix4(const Frame& frame);
		 *
		 * \brief	Constructor from a frame.
		 *
		 * \param	frame	The frame.
		 */

		explicit Matrix4(const Frame& frame);

		/**
		 * \fn	inline float& Matrix4::operator()(uint32_t row, uint32_t col);
		 *
		 * \brief	Accessor.
		 *		
		 * \param   row The row index
		 * \param   col The column index
		 */

		float& operator()(uint32_t row, uint32_t col);

		/**
		 * \fn	inline float Matrix4::operator()(uint32_t row, uint32_t col) const;
		 *
		 * \brief	Accessor.
		 *		
		 * \param   row The row index
		 * \param   col The column index
		 */

		float operator()(uint32_t row, uint32_t col) const;

		/**
		 * \fn	Vector4 Matrix4::getColumn (int32_t colId) const;
		 *
		 * \brief	Gets a column (matrix is considered in COLUMN VECTOR NOTATION)
		 *
		 * \param	colId	Identifier for the col.
		 *
		 * \return	The column.
		 */

		Vector4 getColumn (int32_t colId) const;

		/**
		 * \fn	void Matrix4::setColumn (int32_t colId, Vector4 vector);
		 *
		 * \brief	Sets a column.
		 *
		 * \param	colId 	Identifier for the col.
		 * \param	vector	The vector.
		 */

		void setColumn (int32_t colId, Vector4 vector);		

		/**
		 * \fn	Vector4 Matrix4::getRow (int32_t rowId) const;
		 *
		 * \brief	Gets a row.
		 *
		 * \param	rowId	Identifier for the row.
		 *
		 * \return	The row.
		 */

		Vector4 getRow (int32_t rowId) const;

		//*********** Assignment and comparison ***********

		/**
		 * \fn	Matrix4& Matrix4::operator= (const Matrix4& other);
		 *
		 * \brief	Assignment operator.
		 * 		 
		 * \param	other	The other matrix.
		 * 	
		 * \return	A shallow copy of this object.
		 *
		 */
		 
		Matrix4& operator= (const Matrix4& other);

		/**
		 * \fn	bool Matrix4::operator== (const Matrix4& other) const;
		 *
		 * \brief	Strict equality operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */

		bool operator== (const Matrix4& other) const;

		/**
		 * \fn	bool Matrix4::operator!= (const Matrix4& other) const;
		 *
		 * \brief	Strict inequality operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */

		bool operator!= (const Matrix4& other) const;	

		//*********** Algebra an sub items operations ***********

		/**
		 * \fn	Matrix4 Matrix4::operator+ (const Matrix4& other) const;
		 *
		 * \brief	Addition operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 operator+ (const Matrix4& other) const;

		/**
		 * \fn	Matrix4 Matrix4::operator- (const Matrix4& other) const;
		 *
		 * \brief	Subtraction operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 operator- (const Matrix4& other) const;	

		/**
		 * \fn	Matrix4 Matrix4::operator* (float scalar) const;
		 *
		 * \brief	Scalar multiplication operator.
		 *
		 * \param	scalar	The scale factor.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 operator* (float scalar) const;
		//! scalar multiplication

		/**
		 * \fn	friend Matrix4 Matrix4::operator* (float scalar, const Matrix4& other);
		 *
		 * \brief	Scalar  multiplication operator.
		 *
		 * \param	scalar	The scale factor.
		 * \param	other 	The matrix to multiply.
		 *
		 * \return	The result of the operation.
		 */

		friend Matrix4 operator* (float scalar, const Matrix4& other);

		/**
		 * \fn	Matrix4 Matrix4::operator/ (float scalar) const;
		 *
		 * \brief	Scalar division operator.
		 *
		 * \param	scalar	The scale factor.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 operator/ (float scalar) const;		

		/**
		 * \fn	Matrix4 Matrix4::operator- () const;
		 *
		 * \brief	Negation operator.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 operator- () const;

		/**
		 * \fn	Matrix4 Matrix4::concatenate(const Matrix4 &m2) const;
		 *
		 * \brief	Matrix multiplication (cross product).
		 *
		 * \param	m2	The second matrix.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 concatenate(const Matrix4 &m2) const;

		/**
		 * \fn	Matrix4 Matrix4::operator* ( const Matrix4& other ) const;
		 *
		 * \brief	Matrix multiplication operator (cross product).
		 *
		 * \param	m2	The second matrix.
		 *
		 * \return	The result of the operation.
		 */

		Matrix4 operator * ( const Matrix4& other ) const;		

		/**
		 * \fn	Vector3 Matrix4::getTranslation() const;
		 *
		 * \brief	Extracts the translation part of the matrix.
		 *
		 * \return	The translation.
		 */

		Vector3 getTranslation() const;
	
		/**
		 * \fn	void Matrix4::setTranslation( const Vector3 &v );
		 *
		 * \brief	Sets the translation part of the matrix.
		 *
		 * \param	v	The translation vector.
		 */

		void setTranslation( const Vector3 &v );

		/**
		 * \fn	Vector3 Matrix4::getScale() const;
		 *
		 * \brief	Gets the scale part of the matrix.
		 *
		 * \return	The scale vector.
		 */

		Vector3 getScale() const;

		/**
		 * \fn	void Matrix4::setScale( const Vector3& v );
		 *
		 * \brief	Sets the scale part of the matrix.
		 *
		 * \param	v	The scale vector.
		 */

		void setScale( const Vector3& v );
		//! Determines if this matrix involves a scaling.

		/**
		 * \fn	bool Matrix4::hasScale() const;
		 *
		 * \brief	Determines if this matrix involves a scaling.
		 *
		 * \return	true if matrix has a scaling, false if not.
		 */

		bool hasScale() const;			

		/**
		 * \fn	void Matrix4::rotateX(const float& fAngle);
		 *
		 * \brief	Rotates the matrix along X axis with Euler angle.
		 *
		 * \param	fAngle	The angle.
		 */

		void rotateX(const float& fAngle);

		/**
		 * \fn	void Matrix4::rotateY(const float& fAngle);
		 *
		 * \brief	Rotates the matrix along Y axis with Euler angle.
		 *
		 * \param	fAngle	The angle.
		 */

		void rotateY(const float& fAngle);

		/**
		 * \fn	void Matrix4::rotateZ(const float& fAngle);
		 *
		 * \brief	Rotates the matrix along Z axis with Euler angle.
		 *
		 * \param	fAngle	The angle.
		 */

		void rotateZ(const float& fAngle);

		/**
		 * \fn	Matrix4 Matrix4::getTranspose(void) const;
		 *
		 * \brief	Gets the transpose.
		 *
		 * \return	The transpose.
		 */

		Matrix4 getTranspose(void) const;

		/**
		 * \fn	bool Matrix4::isAffine(void) const;
		 *
		 * \brief	Check whether or not the matrix is affine matrix (row 3 equal to [0, 0, 0, 1])
		 *
		 * \return	true if affine, false if not.
		 */

		bool isAffine(void) const;

		/**
		 * \fn	Matrix4 Matrix4::getInverse(void) const;
		 *
		 * \brief	Gets the inverse.
		 *
		 * \return	The inverse.
		 */

		Matrix4 getInverse(void) const;

		//! Returns the inverse of the matrix (assume the matrix is affine) -- FAST

		/**
		 * \fn	Matrix4 Matrix4::getInverseAffine(void) const;
		 *
		 * \brief	Gets the inverse (assume the matrix is affine) -- FAST
		 *
		 * \return	The inverse.
		 */

		Matrix4 getInverseAffine(void) const;

		//! Returns the inverse of the matrix (assume the matrix is orthonormal) -- FASTER

		/**
		 * \fn	Matrix4 Matrix4::getInverseOrtho(void) const;
		 *
		 * \brief	Gets the inverse of the matrix (assume the matrix is orthonormal) -- FASTER
		 *
		 * \return	The inverse.
		 */

		Matrix4 getInverseOrtho(void) const;

		//*********** Transformation ***********

		/**
		 * \fn	Vector3 Matrix4::multiplyByPoint(const Vector3& v) const;
		 *
		 * \brief	Point transformation (assume V.W = 1)
		 *
		 * \param	v	The point.
		 *
		 * \return	The result of the operation.
		 */

		Vector3 multiplyByPoint(const Vector3& v) const;

		/**
		 * \fn	Vector3 Matrix4::multiplyByVector(const Vector3& v) const;
		 *
		 * \brief	Vector transformation (assume V.W = 0).
		 *
		 * \param	v	The vector.
		 *
		 * \return	The result of the operation.
		 */

		Vector3 multiplyByVector(const Vector3& v) const;

		/**
		 * \fn	Vector3 Matrix4::inverseMultiplyByPoint(const Vector3& v) const;
		 *
		 * \brief	Inverse point transformation (assume V.W = 1)
		 *
		 * \param	v	The point.
		 *
		 * \return	The result of the operation.
		 */

		Vector3 inverseMultiplyByPoint(const Vector3& v) const;
		//! Vector transformation (assume V.W = 0)

		/**
		 * \fn	Vector3 Matrix4::inverseMultiplyByVector(const Vector3& v) const;
		 *
		 * \brief	Inverse vector transformation (assume V.W = 0).
		 *
		 * \param	v	The vector.
		 *
		 * \return	The result of the operation.
		 */

		Vector3 inverseMultiplyByVector(const Vector3& v) const;

// 		//! Vector4 transformation using '*'
// 		Vector4 operator * ( const Vector4 &v ) const;

		//*********** Transformation matrix creation ***********

		/**
		 * \fn	static Matrix4 Matrix4::createScaleMatrix(const Vector3& v);
		 *
		 * \brief	Creates a 3D scale matrix.
		 *
		 * \param	v	The scaling vector.
		 *
		 * \return	The matrix.
		 */

		static Matrix4 createScaleMatrix(const Vector3& v);

		/**
		 * \fn	static Matrix4 Matrix4::createScaleMatrix(float s);
		 *
		 * \brief	Creates a scale matrix.
		 *
		 * \param	s	The scaling.
		 *
		 * \return	The matrix.
		 */

		static Matrix4 createScaleMatrix(float s);
		//! 3D translation matrix 

		/**
		 * \fn	static Matrix4 Matrix4::createTranslationMatrix(const Vector3& v);
		 *
		 * \brief	Creates a translation matrix.
		 *
		 * \param	v	The translation.
		 *
		 * \return	The matrix.
		 */

		static Matrix4 createTranslationMatrix(const Vector3& v);			


		//*********** Type conversion ***********

		/**
		 * \fn	void Matrix4::fromFrame(const Frame& frame);
		 *
		 * \brief	Initializes this matrix from a frame.
		 *
		 * \param	frame	The frame.
		 */

		void fromFrame(const Frame& frame);

		/**
		 * \fn	void Matrix4::fromMatrix3(const Matrix3& m3x3);
		 *
		 * \brief	Initializes this matrix from a 3x3 matrix.
		 *
		 * \param	m3x3	The 3x3 matrix.
		 */

		void fromMatrix3(const Matrix3& m3x3);

		/**
		 * \fn	void Matrix4::fromQuaternion(const Quaternion &quat);
		 *
		 * \brief	Initializes this matrix from a quaternion.
		 *
		 * \param	quat	The quaternion.
		 */

		void fromQuaternion(const Quaternion &quat);

		/**
		 * \fn	void Matrix4::fromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);
		 *
		 * \brief	Initializes this matrix from the 3 axes of the frame.
		 *
		 * \param	xAxis	The x coordinate axis.
		 * \param	yAxis	The y coordinate axis.
		 * \param	zAxis	The z coordinate axis.
		 */

		void fromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);

		/**
		 * \fn	void Matrix4::fromRotationVector(const Vector3 &rotVec);
		 *
		 * \brief	Initializes this object from a rotation vector.
		 *
		 * \param	rotVec	The rotation vector.
		 */

		void fromRotationVector(const Vector3 &rotVec);

		/**
		 * \fn	void Matrix4::toFrame(Frame& frame) const;
		 *
		 * \brief	Converts this object to a frame.
		 *
		 * \param [out]	frame	The frame.
		 */

		void toFrame(Frame& frame) const;

		/**
		 * \fn	Frame Matrix4::toFrame() const;
		 *
		 * \brief	Converts this object to a frame.
		 *
		 * \return	This object as a Frame.
		 */

		Frame toFrame() const;

		/**
		 * \fn	Matrix3 Matrix4::toMatrix3() const;
		 *
		 * \brief	Converts this object to a 3x3 matrix.
		 *
		 * \return	This object as a Matrix3.
		 */

		Matrix3 toMatrix3() const;

		/**
		 * \fn	Quaternion Matrix4::toQuaternion() const;
		 *
		 * \brief	Converts this object to a quaternion.
		 *
		 * \return	This object as a Quaternion.
		 */

		Quaternion toQuaternion() const;

		/**
		 * \fn	void Matrix4::toAxes(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const;
		 *
		 * \brief	Converts this object to the 3 axes of the frame.
		 *
		 * \param [out]	xAxis	The x coordinate axis.
		 * \param [out]	yAxis	The y coordinate axis.
		 * \param [out]	zAxis	The z coordinate axis.
		 */

		void toAxes(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const;
		//! Convert from a rotation vector.

		/**
		 * \fn	void Matrix4::toRotationVector(Vector3 &rotVec) const;
		 *
		 * \brief	Converts this object to a rotation vector.
		 *
		 * \param [out]	rotVec	The rotation vector.
		 */

		void toRotationVector(Vector3 &rotVec) const;

		/**
		 * \fn	Vector3 Matrix4::toRotationVector() const;
		 *
		 * \brief	Converts this object to a rotation vector.
		 *
		 * \return	This rotation vector.
		 */

		Vector3 toRotationVector() const;

		/**
		 * \fn	bool Matrix4::toEulerAnglesZYX (float& rfZAngle, float& rfYAngle, float& rfXAngle);
		 *
		 * \brief	Converts this matrix to an euler angles zyx.
		 *
		 * \param [out]	rfZAngle	The z coordinate angle.
		 * \param [out]	rfYAngle	The y coordinate angle.
		 * \param [out]	rfXAngle	The x coordinate angle.
		 *
		 * \return	true if it succeeds, false if the convertion is not unique.
		 */

		bool toEulerAnglesZYX (float& rfZAngle, float& rfYAngle, float& rfXAngle);
// 		void tred2(float d[], float e[], float a[4][4]);
// 		bool eigenSolveSymmetric(float d[], float e[], float z[4][4]);

		///< The identity matrix
		static const Matrix4 IDENTITY;
		///< The zero matrix
		static const Matrix4 ZERO;

		/**
		 * \fn	inline friend std::ostream& Matrix4::operator<< ( std::ostream& o, const Matrix4& m )
		 *
		 * \brief	Output stream operator.
		 *
		 * \param [in,out]	o	The out put stream.
		 * \param	m		 	The matrix.
		 *
		 * \return	The updated output stream.
		 */

		inline friend std::ostream& operator <<
			(  std::ostream& o, const Matrix4& m )
		{
			o << "Matrix4(\n";
			for (size_t row = 0; row < 4; ++row)
			{	
				for(size_t col = 0; col < 4; ++col)
				{
					o << m(row, col) << " ";
				}
				o << "\n";
			}
			o << ")";
			return o;
		}

	public:

		//! Members are stored and only stored in COLUMN MAJOR LAYOUT.
		float	_11, _21, _31, _41;
		float	_12, _22, _32, _42;
		float	_13, _23, _33, _43;
		float	_14, _24, _34, _44;
	};

}//end of namespace SK

#ifndef SK_DEBUG
#include "Matrix4.inl"
#endif

