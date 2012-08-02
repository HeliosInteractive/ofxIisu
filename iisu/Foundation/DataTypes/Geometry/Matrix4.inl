namespace SK 
{
	//----------------------------- CONSTRUCTOR -----------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4 (
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44 )
	{
		_11 = m11;
		_12 = m12;
		_13 = m13;
		_14 = m14;

		_21 = m21;
		_22 = m22;
		_23 = m23;
		_24 = m24;

		_31 = m31;
		_32 = m32;
		_33 = m33;
		_34 = m34;

		_41 = m41;
		_42 = m42;
		_43 = m43;
		_44 = m44;

	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis)
	{
		fromAxes(xAxis, yAxis, zAxis);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis, const Vector3 &translation)
	{
		fromAxes(xAxis, yAxis, zAxis);
		
		_14 = translation.x;
		_24 = translation.y;
		_34 = translation.z;
		_44 = 1.0f;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Vector3 &rotVec)
	{
		fromRotationVector(rotVec);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Vector3 &rotVec, const Vector3 &translation)
	{
		Quaternion tmp(rotVec);
		tmp.toMatrix4(*this);

		_14 = translation.x;
		_24 = translation.y;
		_34 = translation.z;
		_44 = 1.0f;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Matrix3& m3x3)
	{
		fromMatrix3(m3x3);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Matrix3& m3x3, const Vector3& translation)
	{
		fromMatrix3(m3x3);

		_14 = translation.x;
		_24 = translation.y;
		_34 = translation.z;
		_44 = 1.0f;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Quaternion &rot)
	{
		fromQuaternion(rot);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Quaternion& rot, const Vector3& translation)
	{
		fromQuaternion(rot);

		_14 = translation.x;
		_24 = translation.y;
		_34 = translation.z;
		_44 = 1.0f;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4::Matrix4(const Frame& frame)
	{
		fromFrame(frame);
	}

	//----------------------------- MEMBER ACCESS  -----------------------------------------------
	SK_FORCE_INLINE float&	Matrix4::operator()(uint32_t row, uint32_t col)
	{
		return (&_11)[4*col + row];

	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE float Matrix4::operator()(uint32_t row, uint32_t col) const
	{
		return (&_11)[4*col + row];

	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Matrix4::getColumn (int32_t colId) const
	{
		return Vector4( operator()(0, colId), operator()(1, colId), operator()(2, colId), operator()(3, colId) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector4 Matrix4::getRow (int32_t rowId) const
	{
		return Vector4( operator()(rowId, 0), operator()(rowId, 1), operator()(rowId, 2), operator()(rowId, 3) );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::setColumn (int32_t colId, Vector4 vector)
	{
		(Vector4&)operator()(0, colId) = vector;
	}
	//----------------------------- assignment and comparison BEGIN -----------------------------------------------

	SK_FORCE_INLINE Matrix4& Matrix4::operator = ( const Matrix4& m2 )
	{
		_11 = m2._11;
		_21 = m2._21;
		_31 = m2._31;
		_41 = m2._41;
		_12 = m2._12;
		_22 = m2._22;
		_32 = m2._32;
		_42 = m2._42;
		_13 = m2._13;
		_23 = m2._23;
		_33 = m2._33;
		_43 = m2._43;
		_14 = m2._14;
		_24 = m2._24;
		_34 = m2._34;
		_44 = m2._44;
		return *this;
	}
	SK_FORCE_INLINE bool Matrix4::operator == ( const Matrix4& m2 ) const
	{
		if(
			_11 != m2._11 || _21 != m2._21 || _31 != m2._31 || _41 != m2._41 ||
			_12 != m2._12 || _22 != m2._22 || _32 != m2._32 || _42 != m2._42 ||
			_13 != m2._13 || _23 != m2._23 || _33 != m2._33 || _43 != m2._43 ||
			_14 != m2._14 || _24 != m2._24 || _34 != m2._34 || _44 != m2._44 
			) return false;
		return true;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Matrix4::operator != ( const Matrix4& m2 ) const
	{
		return !(operator==(m2));
	}
	//----------------------------- arithmetic operations BEGIN --------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::operator + ( const Matrix4 &m2 ) const
	{
		return Matrix4(
			_11 + m2._11,
			_12 + m2._12,
			_13 + m2._13,
			_14 + m2._14,

			_21 + m2._21,
			_22 + m2._22,
			_23 + m2._23,
			_24 + m2._24,

			_31 + m2._31,
			_32 + m2._32,
			_33 + m2._33,
			_34 + m2._34,

			_41 + m2._41,
			_42 + m2._42,
			_43 + m2._43,
			_44 + m2._44 
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::operator - ( const Matrix4 &m2 ) const
	{
		return Matrix4(
			_11 - m2._11,
			_12 - m2._12,
			_13 - m2._13,
			_14 - m2._14,

			_21 - m2._21,
			_22 - m2._22,
			_23 - m2._23,
			_24 - m2._24,

			_31 - m2._31,
			_32 - m2._32,
			_33 - m2._33,
			_34 - m2._34,

			_41 - m2._41,
			_42 - m2._42,
			_43 - m2._43,
			_44 - m2._44 
			);
	}
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE Matrix4 Matrix4::operator * ( float scalar ) const
	{
		return Matrix4(
			_11 * scalar,
			_12 * scalar,
			_13 * scalar,
			_14 * scalar,

			_21 * scalar,
			_22 * scalar,
			_23 * scalar,
			_24 * scalar,

			_31 * scalar,
			_32 * scalar,
			_33 * scalar,
			_34 * scalar,

			_41 * scalar,
			_42 * scalar,
			_43 * scalar,
			_44 * scalar 
			);
	}		
	SK_FORCE_INLINE Matrix4 operator * (float scalar, const Matrix4& other)
	{
		return Matrix4(
			other._11 * scalar,
			other._12 * scalar,
			other._13 * scalar,
			other._14 * scalar,

			other._21 * scalar,
			other._22 * scalar,
			other._23 * scalar,
			other._24 * scalar,

			other._31 * scalar,
			other._32 * scalar,
			other._33 * scalar,
			other._34 * scalar,

			other._41 * scalar,
			other._42 * scalar,
			other._43 * scalar,
			other._44 * scalar 
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::operator/ ( float scalar ) const
	{
		return Matrix4(
			_11 / scalar,
			_12 / scalar,
			_13 / scalar,
			_14 / scalar,

			_21 / scalar,
			_22 / scalar,
			_23 / scalar,
			_24 / scalar,

			_31 / scalar,
			_32 / scalar,
			_33 / scalar,
			_34 / scalar,

			_41 / scalar,
			_42 / scalar,
			_43 / scalar,
			_44 / scalar 
			);			
	}
// 	SK_FORCE_INLINE Matrix4& Matrix4::operator/= ( float scalar )
// 	{
// 		_11 /= scalar;
// 		_12 /= scalar;
// 		_13 /= scalar;
// 		_14 /= scalar;
// 
// 		_21 /= scalar;
// 		_22 /= scalar;
// 		_23 /= scalar;
// 		_24 /= scalar;
// 
// 		_31 /= scalar;
// 		_32 /= scalar;
// 		_33 /= scalar;
// 		_34 /= scalar;
// 
// 		_41 /= scalar;
// 		_42 /= scalar;
// 		_43 /= scalar;
// 		_44 /= scalar;
// 
// 		return *this;
// 	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::operator- () const
	{
		return Matrix4(
			-_11 ,
			-_12 ,
			-_13 ,
			-_14 ,

			-_21 ,
			-_22 ,
			-_23 ,
			-_24 ,

			-_31 ,
			-_32 ,
			-_33 ,
			-_34 ,

			-_41 ,
			-_42 ,
			-_43 ,
			-_44  
			);
	}		
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::concatenate(const Matrix4 &m2) const
	{
		return Matrix4(
			_11 * m2._11 + _12 * m2._21 + _13 * m2._31 + _14 * m2._41,
			_11 * m2._12 + _12 * m2._22 + _13 * m2._32 + _14 * m2._42,
			_11 * m2._13 + _12 * m2._23 + _13 * m2._33 + _14 * m2._43,
			_11 * m2._14 + _12 * m2._24 + _13 * m2._34 + _14 * m2._44,

			_21 * m2._11 + _22 * m2._21 + _23 * m2._31 + _24 * m2._41,
			_21 * m2._12 + _22 * m2._22 + _23 * m2._32 + _24 * m2._42,
			_21 * m2._13 + _22 * m2._23 + _23 * m2._33 + _24 * m2._43,
			_21 * m2._14 + _22 * m2._24 + _23 * m2._34 + _24 * m2._44,

			_31 * m2._11 + _32 * m2._21 + _33 * m2._31 + _34 * m2._41,
			_31 * m2._12 + _32 * m2._22 + _33 * m2._32 + _34 * m2._42,
			_31 * m2._13 + _32 * m2._23 + _33 * m2._33 + _34 * m2._43,
			_31 * m2._14 + _32 * m2._24 + _33 * m2._34 + _34 * m2._44,

			_41 * m2._11 + _42 * m2._21 + _43 * m2._31 + _44 * m2._41,
			_41 * m2._12 + _42 * m2._22 + _43 * m2._32 + _44 * m2._42,
			_41 * m2._13 + _42 * m2._23 + _43 * m2._33 + _44 * m2._43,
			_41 * m2._14 + _42 * m2._24 + _43 * m2._34 + _44 * m2._44
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::operator * ( const Matrix4 &m2 ) const
	{
		return concatenate( m2 );
	}		

	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Matrix4::getTranslation() const
	{
		return Vector3(_14, _24, _34);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::setTranslation(const Vector3 &v)
	{
		_14 = v.x;
		_24 = v.y;
		_34 = v.z;
	}			
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE Vector3 Matrix4::getScale() const
	{
		return Vector3( _11, _22, _33);
	}
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE void  Matrix4::setScale( const Vector3& v )
	{
		_11 = v.x;
		_22 = v.y;
		_33 = v.z;
	}
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE bool Matrix4::hasScale() const
	{
		// check magnitude of column vectors (==local axes)
		float t = _11 * _11 + _21 * _21 + _31 * _31;
		if (!Math::equal(t, (float) 1.0, (float) 1e-04))
			return true;
		t = _12 * _12 + _22 * _22 + _32 * _32;
		if (!Math::equal(t, (float) 1.0, (float) 1e-04))
			return true;
		t = _13 * _13 + _23 * _23 + _33 * _33;
		if (!Math::equal(t, (float) 1.0, (float) 1e-04))
			return true;

		return false;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::rotateX(const float& fAngle)
	{
		float cs, sn;
		cs = SK::Math::cos( fAngle );
		sn = SK::Math::sin( fAngle );
		SK::Vector4 tmp = getColumn(1);
		_12 = cs * _12 + sn * _13;
		_22 = cs * _22 + sn * _23;
		_32 = cs * _32 + sn * _33;
		_42 = cs * _42 + sn * _43;
		_13 = - sn * tmp[0] + cs * _13;
		_23 = - sn * tmp[1] + cs * _23;
		_33 = - sn * tmp[2] + cs * _33;
		_43 = - sn * tmp[3] + cs * _43;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::rotateY(const float& fAngle)
	{
		float cs, sn;
		cs = SK::Math::cos( fAngle );
		sn = SK::Math::sin( fAngle );
		SK::Vector4 tmp = getColumn(0);
		_11 = cs * _11 - sn * _13;
		_21 = cs * _21 - sn * _23;
		_31 = cs * _31 - sn * _33;
		_41 = cs * _41 - sn * _43;		
		_13 = sn * tmp[0] + cs * _13;
		_23 = sn * tmp[1] + cs * _23;
		_33 = sn * tmp[2] + cs * _33;
		_43 = sn * tmp[3] + cs * _43;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::rotateZ(const float& fAngle)
	{
		float cs, sn;
		cs = SK::Math::cos( fAngle );
		sn = SK::Math::sin( fAngle );
		SK::Vector4 tmp = getColumn(0);
		_11 = cs * _11 + sn * _12;
		_21 = cs * _21 + sn * _22;
		_31 = cs * _31 + sn * _32;
		_41 = cs * _41 + sn * _42;
		_12 = -sn * tmp[0] + cs *_12;
		_22 = -sn * tmp[1] + cs *_22;
		_32 = -sn * tmp[2] + cs *_32;
		_42 = -sn * tmp[3] + cs *_42;
	}

	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::getTranspose(void) const
	{
		return Matrix4(
			_11, _21, _31, _41,
			_12, _22, _32, _42,
			_13, _23, _33, _43,
			_14, _24, _34, _44);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE bool Matrix4::isAffine(void) const
	{
		return Math::equal(_41, 0, 0.000001f) && 
			   Math::equal(_42, 0, 0.000001f) && 
			   Math::equal(_43, 0, 0.000001f) &&
		       Math::equal(_44, 1, 0.000001f);
	}
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE Matrix4 Matrix4::getInverse(void) const
	{		
		float m00 = _11, m01 = _12, m02 = _13, m03 = _14;
		float m10 = _21, m11 = _22, m12 = _23, m13 = _24;
		float m20 = _31, m21 = _32, m22 = _33, m23 = _34;
		float m30 = _41, m31 = _42, m32 = _43, m33 = _44;

		float v0 = m20 * m31 - m21 * m30;
		float v1 = m20 * m32 - m22 * m30;
		float v2 = m20 * m33 - m23 * m30;
		float v3 = m21 * m32 - m22 * m31;
		float v4 = m21 * m33 - m23 * m31;
		float v5 = m22 * m33 - m23 * m32;

		float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
		float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
		float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
		float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

		float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

		float d00 = t00 * invDet;
		float d10 = t10 * invDet;
		float d20 = t20 * invDet;
		float d30 = t30 * invDet;

		float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		return Matrix4(
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33);
	}
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE Matrix4 Matrix4::getInverseAffine(void) const
	{
		assert(isAffine());

		float m10 = _21, m11 = _22, m12 = _23;
		float m20 = _31, m21 = _32, m22 = _33;

		float t00 = m22 * m11 - m21 * m12;
		float t10 = m20 * m12 - m22 * m10;
		float t20 = m21 * m10 - m20 * m11;

		float m00 = _11, m01 = _12, m02 = _13;

		float invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

		t00 *= invDet; t10 *= invDet; t20 *= invDet;

		m00 *= invDet; m01 *= invDet; m02 *= invDet;

		float r00 = t00;
		float r01 = m02 * m21 - m01 * m22;
		float r02 = m01 * m12 - m02 * m11;

		float r10 = t10;
		float r11 = m00 * m22 - m02 * m20;
		float r12 = m02 * m10 - m00 * m12;

		float r20 = t20;
		float r21 = m01 * m20 - m00 * m21;
		float r22 = m00 * m11 - m01 * m10;

		float m03 = _14, m13 = _24, m23 = _34;

		float r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
		float r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
		float r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

		return Matrix4(
			r00, r01, r02, r03,
			r10, r11, r12, r13,
			r20, r21, r22, r23,
			0,   0,   0,   1);
	}
	//----------------------------------------------------------------------------		
	SK_FORCE_INLINE Matrix4 Matrix4::getInverseOrtho(void) const
	{
		//transpose
		return Matrix4(
			_11, _21, _31, -((_11*_14 + _21*_24 + _31*_34)),
			_12, _22, _32, -((_12*_14 + _22*_24 + _32*_34)),
			_13, _23, _33, -((_13*_14 + _23*_24 + _33*_34)),
			0,   0,   0,   1);
	}		
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Matrix4::multiplyByPoint(const Vector3& v) const
	{
		// Special version with
		// V.W = 1.0f
		return Vector3(
			_11 * v.x + _12 * v.y + _13 * v.z + _14 ,
			_21 * v.x + _22 * v.y + _23 * v.z + _24 ,
			_31 * v.x + _32 * v.y + _33 * v.z + _34
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Matrix4::multiplyByVector(const Vector3& v) const
	{
		// Special version with
		// V.W = 0.0f
		return Vector3(
			_11 * v.x + _12 * v.y + _13 * v.z , 
			_21 * v.x + _22 * v.y + _23 * v.z ,
			_31 * v.x + _32 * v.y + _33 * v.z 
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Matrix4::inverseMultiplyByPoint(const Vector3& v) const
	{
		// Special version with
		// V.W = 1.0f
		return Vector3(
			_11 * (v.x - _14) + _21 * (v.y - _24) + _31 * (v.z - _34) ,
			_12 * (v.x - _14) + _22 * (v.y - _24) + _32 * (v.z - _34) ,
			_13 * (v.x - _14) + _23 * (v.y - _24) + _33 * (v.z - _34)
			);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Matrix4::inverseMultiplyByVector(const Vector3& v) const
	{
		// Special version with
		// V.W = 0.0f
		return Vector3(
			_11 * v.x + _21 * v.y + _31 * v.z  ,
			_12 * v.x + _22 * v.y + _32 * v.z  ,
			_13 * v.x + _23 * v.y + _33 * v.z 
			);
	}
	//----------------------------------------------------------------------------
// 	SK_FORCE_INLINE Vector4 Matrix4::operator * (const Vector4& v) const
// 	{
// 		return Vector4(
// 			_11 * v.x + _12 * v.y + _13 * v.z + _14 * v.w, 
// 			_21 * v.x + _22 * v.y + _23 * v.z + _24 * v.w,
// 			_31 * v.x + _32 * v.y + _33 * v.z + _34 * v.w,
// 			_41 * v.x + _42 * v.y + _43 * v.z + _44 * v.w
// 			);
// 	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::createScaleMatrix(const Vector3& v)
	{
		return Matrix4(
			v.x, 0.0,  0.0,  0.0,
			0.0, v.y,  0.0,  0.0,
			0.0, 0.0,  v.z,  0.0,
			0.0, 0.0,  0.0,  1.0 );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::createScaleMatrix(float s) 
	{
		return Matrix4(
			s, 0.0,  0.0,  0.0,
			0.0,   s,  0.0,  0.0,
			0.0, 0.0,    s,  0.0,
			0.0, 0.0,  0.0,  1.0 );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix4 Matrix4::createTranslationMatrix(const Vector3& v) 
	{
		return Matrix4(
			1.0, 0.0,  0.0,  v.x,
			0.0, 1.0,  0.0,  v.y,
			0.0, 0.0,  1.0,  v.z,
			0.0, 0.0,  0.0,  1.0 );
	}
	//----------------------------------------------------------------------------
	//Matrix4CheckFlag
	SK_FORCE_INLINE bool Matrix4::toEulerAnglesZYX (float& rfZAngle, float& rfYAngle, float& rfXAngle)
	{
		// rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
		//        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
		//       -sy              cy*sx           cx*cy

		if (operator()(2, 0) <1.0f)
		{
			if (operator()(2, 0) > -1.0f)
			{
				rfZAngle = SK::Math::aTan2(operator()(1, 0), operator()(0, 0));
				rfYAngle = SK::Math::aSin(-operator()(2, 0));
				rfXAngle = SK::Math::aTan2(operator()(2, 1),operator()(2, 2));
				return true;
			}
			else
			{
				// WARNING.  Not unique.  ZA - XA = -atan2(r01,r02)
				rfZAngle = -SK::Math::aTan2(operator()(0, 1),operator()(0, 2));
				rfYAngle = SK::Math::HALF_PI;
				rfXAngle = 0.0f;
				return false;
			}
		}
		else
		{
			// WARNING.  Not unique.  ZA + XA = atan2(-r01,-r02)
			rfZAngle = SK::Math::aTan2(-operator()(0, 1),-operator()(0, 2));
			rfYAngle = -SK::Math::HALF_PI;
			rfXAngle = 0.0f;
			return false;
		}
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::fromFrame(const Frame& frame)
	{
		fromQuaternion(frame.m_quat);
		setTranslation(frame.m_pos);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::fromMatrix3(const Matrix3& m3x3)
	{
		_11 = m3x3._11 ; _21 = m3x3._21 ; _31 = m3x3._31 ; _41 = 0 ;
		_12 = m3x3._12 ; _22 = m3x3._22 ; _32 = m3x3._32 ; _42 = 0 ;
		_13 = m3x3._13 ; _23 = m3x3._23 ; _33 = m3x3._33 ; _43 = 0 ;
		_14 = 0        ; _24 = 0        ; _34 = 0        ; _44 = 1 ;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::fromQuaternion(const Quaternion &quat)
	{
		Matrix3 m3x3;
		quat.toMatrix3(m3x3);
		fromMatrix3(m3x3);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::fromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis)
	{
		_11 = xAxis.x;
		_21 = xAxis.y;
		_31 = xAxis.z;
		_41 = 0.0f;

		_12 = yAxis.x;
		_22 = yAxis.y;
		_32 = yAxis.z;
		_42 = 0.0f;

		_13 = zAxis.x;
		_23 = zAxis.y;
		_33 = zAxis.z;
		_43 = 0.0f;

		_14 = 0.0f;
		_24 = 0.0f;
		_34 = 0.0f;
		_44 = 1.0f;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::fromRotationVector(const Vector3 &rotVec)
	{
		Quaternion tmp(rotVec);
		tmp.toMatrix4(*this);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::toFrame(Frame& frame) const
	{
		frame.m_quat = toQuaternion();
		frame.m_pos = getTranslation();
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Frame Matrix4::toFrame() const
	{
		Frame frame;
		frame.m_quat = toQuaternion();
		frame.m_pos = getTranslation();

		return frame;
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Matrix3 Matrix4::toMatrix3() const
	{
		return Matrix3(
			_11, _12, _13,
			_21, _22, _23,
			_31, _32, _33 );
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Matrix4::toQuaternion() const
	{			
		return Quaternion(*this);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::toAxes(Vector3 &xAxis, Vector3 &yAxis, Vector3 &zAxis) const
	{
		xAxis.x = (*this)(0,0);
		xAxis.y = (*this)(1,0);
		xAxis.z = (*this)(2,0);

		yAxis.x = (*this)(0,1);
		yAxis.y = (*this)(1,1);
		yAxis.z = (*this)(2,1);

		zAxis.x = (*this)(0,2);
		zAxis.y = (*this)(1,2);
		zAxis.z = (*this)(2,2);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE void Matrix4::toRotationVector(Vector3 &rotVec) const
	{
		rotVec.fromMatrix4(*this);
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Matrix4::toRotationVector() const
	{
		Vector3 rotVec;
		rotVec.fromMatrix4(*this);

		return rotVec;
	}

}//end of namespace SK

