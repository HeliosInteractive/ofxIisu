namespace SK 
{	

	SK_FORCE_INLINE Matrix3::Matrix3 (
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33
		)
	{
		_11 = m11;
		_12 = m12;
		_13 = m13;
		_21 = m21;
		_22 = m22;
		_23 = m23;
		_31 = m31;
		_32 = m32;
		_33 = m33;
	}

	SK_FORCE_INLINE Matrix3::Matrix3 (const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis)
	{
		fromAxes(xAxis, yAxis, zAxis);
	}

	SK_FORCE_INLINE float&	Matrix3::operator()(uint32_t row, uint32_t col)
	{
		return (&_11)[col + 3*row];

	}

	SK_FORCE_INLINE float Matrix3::operator()(uint32_t row, uint32_t col) const
	{
		return (&_11)[col + 3*row];

	}

	SK_FORCE_INLINE Vector3 Matrix3::getColumn (int32_t colId) const
	{
		return Vector3( operator()(0, colId), operator()(1, colId), operator()(2, colId) );
	}

	SK_FORCE_INLINE bool Matrix3::operator== (const Matrix3& m2) const
	{
		if(
			_11 != m2._11 || _21 != m2._21 || _31 != m2._31 || 
			_12 != m2._12 || _22 != m2._22 || _32 != m2._32 || 
			_13 != m2._13 || _23 != m2._23 || _33 != m2._33 				
			) return false;
		return true;
	}

	SK_FORCE_INLINE bool Matrix3::operator!= (const Matrix3& other) const
	{
		return !(operator==(other));
	}

	SK_FORCE_INLINE Matrix3 Matrix3::operator+ (const Matrix3& m2) const
	{
		return Matrix3(
			_11 + m2._11,
			_12 + m2._12,
			_13 + m2._13,

			_21 + m2._21,
			_22 + m2._22,
			_23 + m2._23,

			_31 + m2._31,
			_32 + m2._32,
			_33 + m2._33
			);
	}

	SK_FORCE_INLINE Matrix3 Matrix3::operator- (const Matrix3& m2) const
	{
		return Matrix3(
			_11 - m2._11,
			_12 - m2._12,
			_13 - m2._13,

			_21 - m2._21,
			_22 - m2._22,
			_23 - m2._23,

			_31 - m2._31,
			_32 - m2._32,
			_33 - m2._33
			);			
	}

	SK_FORCE_INLINE Matrix3 Matrix3::operator * ( float scalar ) const
	{
		return Matrix3(
			_11 * scalar,
			_12 * scalar,
			_13 * scalar,

			_21 * scalar,
			_22 * scalar,
			_23 * scalar,

			_31 * scalar,
			_32 * scalar,
			_33 * scalar 
			);
	}

	SK_FORCE_INLINE Matrix3 operator * (float scalar, const Matrix3& other)
	{
		return Matrix3(
			other._11 * scalar,
			other._12 * scalar,
			other._13 * scalar,

			other._21 * scalar,
			other._22 * scalar,
			other._23 * scalar,

			other._31 * scalar,
			other._32 * scalar,
			other._33 * scalar 
			);
	}

	SK_FORCE_INLINE Matrix3 Matrix3::operator/ ( float scalar ) const
	{
		return Matrix3(
			_11 / scalar,
			_12 / scalar,
			_13 / scalar,

			_21 / scalar,
			_22 / scalar,
			_23 / scalar,

			_31 / scalar,
			_32 / scalar,
			_33 / scalar 
			);
	}

	SK_FORCE_INLINE Matrix3 Matrix3::operator- () const
	{
		return Matrix3(
			-_11 ,
			-_12 ,
			-_13 ,

			-_21 ,
			-_22 ,
			-_23 ,

			-_31 ,
			-_32 ,
			-_33 
			);
	}

	SK_FORCE_INLINE Matrix3 Matrix3::concatenate(const Matrix3 &m2) const
	{
		Matrix3 r;
		r._11 = _11 * m2._11 + _12 * m2._21 + _13 * m2._31 ;
		r._12 = _11 * m2._12 + _12 * m2._22 + _13 * m2._32 ;
		r._13 = _11 * m2._13 + _12 * m2._23 + _13 * m2._33 ;

		r._21 = _21 * m2._11 + _22 * m2._21 + _23 * m2._31 ;
		r._22 = _21 * m2._12 + _22 * m2._22 + _23 * m2._32 ;
		r._23 = _21 * m2._13 + _22 * m2._23 + _23 * m2._33 ;

		r._31 = _31 * m2._11 + _32 * m2._21 + _33 * m2._31 ;
		r._32 = _31 * m2._12 + _32 * m2._22 + _33 * m2._32 ;
		r._33 = _31 * m2._13 + _32 * m2._23 + _33 * m2._33 ;			


		return r;
	}

	SK_FORCE_INLINE Matrix3 Matrix3::operator * ( const Matrix3 &m2 ) const
	{
		return concatenate( m2 );
	}

	SK_FORCE_INLINE Vector3 Matrix3::operator* (const Vector3& v) const
	{
		return Vector3(
			_11 * v.x + _12 * v.y + _13 * v.z , 
			_21 * v.x + _22 * v.y + _23 * v.z ,
			_31 * v.x + _32 * v.y + _33 * v.z 
			);
	}

	SK_FORCE_INLINE Matrix3 Matrix3::transpose () const
	{
		return Matrix3(
			_11, _21, _31, 
			_12, _22, _32, 
			_13, _23, _33 );
	}

	SK_FORCE_INLINE bool Matrix3::inverse (Matrix3& rkInverse, float fTolerance) const
	{
		// Invert a 3x3 using cofactors.  This is about 8 times faster than
		// the Numerical Recipes code which uses Gaussian elimination.

		rkInverse._11 = _22*_33  -	_23*_32;
		rkInverse._12 = _13*_32  -	_12*_33;
		rkInverse._13 = _12*_23  -	_13*_22;
		rkInverse._21 = _23*_31  -	_21*_33;
		rkInverse._22 = _11*_33  -	_13*_31;
		rkInverse._23 = _13*_21  -	_11*_23;
		rkInverse._31 = _21*_32  -	_22*_31;
		rkInverse._32 = _12*_31  -	_11*_32;
		rkInverse._33 = _11*_22  -	_12*_21;

		float fDet =
			_11*rkInverse._11 +
			_12*rkInverse._21 +
			_13*rkInverse._31;

		if ( Math::abs(fDet) <= fTolerance )
			return false;

		float fInvDet = 1.f/fDet;

		rkInverse._11 *= fInvDet;
		rkInverse._12 *= fInvDet;
		rkInverse._13 *= fInvDet;

		rkInverse._21 *= fInvDet;
		rkInverse._22 *= fInvDet;
		rkInverse._23 *= fInvDet;

		rkInverse._31 *= fInvDet;
		rkInverse._32 *= fInvDet;
		rkInverse._33 *= fInvDet;

		return true;
	}

	SK_FORCE_INLINE Matrix3 Matrix3::inverse (float fTolerance) const
	{
		Matrix3 kInverse = Matrix3::ZERO;
		inverse(kInverse,fTolerance);
		return kInverse;
	}

	SK_FORCE_INLINE float Matrix3::determinant () const
	{
		float fCofactor00 = _22*_33 -	_23*_32;
		float fCofactor10 = _23*_31 -	_21*_33;
		float fCofactor20 = _21*_32 -	_22*_31;

		float fDet =
			_11*fCofactor00 +
			_12*fCofactor10 +
			_13*fCofactor20;

		return fDet;
	}

	SK_FORCE_INLINE void Matrix3::initRotateX(const float& fAngle)
	{
		float cs,sn;
		cs=Math::cos(fAngle);
		sn=Math::sin(fAngle);
		*this = IDENTITY;			
		_22=cs;
		_23=-sn;
		_32=sn;
		_33=cs;
	}

	SK_FORCE_INLINE void Matrix3::initRotateY(const float& fAngle)
	{
		float cs,sn;
		cs=Math::cos(fAngle);
		sn=Math::sin(fAngle);
		*this = IDENTITY;
		_11=cs;
		_13=sn;
		_31=-sn;
		_33=cs;
	}

	SK_FORCE_INLINE void Matrix3::initRotateZ(const float& fAngle)
	{
		float cs,sn;
		cs=Math::cos(fAngle);
		sn=Math::sin(fAngle);
		*this = IDENTITY;
		_11=cs;
		_12=-sn;
		_21=sn;
		_22=cs;
	}

	SK_FORCE_INLINE void Matrix3::initRotate(const float& fAngle, const float& fx, const float& fy,
		const float& fz, const bool& bnorm)
	{
		//  Rotation autour d'un axe quelconque à l'aide de quaternions
		float csdemi,sndemi;
		csdemi=Math::cos(fAngle*.5f);
		sndemi=Math::sin(fAngle*.5f);
		Vector3 u(fx,fy,fz);
		if (!bnorm) u.normalize();
		float wq=csdemi,xq=sndemi*u[0],yq=sndemi*u[1],zq=sndemi*u[2];
		_11=wq*wq+xq*xq-yq*yq-zq*zq;
		_21=2*(xq*yq+wq*zq);
		_31=2*(xq*zq-wq*yq);
		_12=2*(xq*yq-wq*zq);
		_22=wq*wq-xq*xq+yq*yq-zq*zq;
		_32=2*(yq*zq+wq*xq);
		_13=2*(xq*zq+wq*yq);
		_23=2*(yq*zq-wq*xq);
		_33=wq*wq-xq*xq-yq*yq+zq*zq;
	}

	SK_FORCE_INLINE void Matrix3::rotateX(const float& fAngle)
	{
		if ((float)fAngle)
		{
			float cs,sn;
			cs=Math::cos(fAngle);
			sn=Math::sin(fAngle);

			float fTmp=_12;
			_12=cs*fTmp+sn*_13;
			_13=-sn*fTmp+cs*_13;

			fTmp=_22;
			_22=cs*fTmp+sn*_23;
			_23=-sn*fTmp+cs*_23;

			fTmp=_32;
			_32=cs*fTmp+sn*_33;
			_33=-sn*fTmp+cs*_33;
		}
	}

	SK_FORCE_INLINE void Matrix3::rotateY(const float& fAngle)
	{
		if ((float)fAngle)
		{	
			float cs,sn;
			cs=Math::cos(fAngle);
			sn=Math::sin(fAngle);

			float fTmp=_11;
			_11=cs*fTmp-sn*_13;
			_13=sn*fTmp+cs*_13;

			fTmp=_21;
			_21=cs*fTmp-sn*_23;
			_23=sn*fTmp+cs*_23;

			fTmp=_31;
			_31=cs*fTmp-sn*_33;
			_33=sn*fTmp+cs*_33;
		}
	}

	SK_FORCE_INLINE void Matrix3::rotateZ(const float& fAngle)
	{
		if ((float)fAngle)
		{
			float cs,sn;
			cs=Math::cos(fAngle);
			sn=Math::sin(fAngle);

			float fTmp=_11;
			_11=cs*fTmp+sn*_12;
			_12=-sn*fTmp+cs*_12;

			fTmp=_21;
			_21=cs*fTmp+sn*_22;
			_22=-sn*fTmp+cs*_22;

			fTmp=_31;
			_31=cs*fTmp+sn*_32;
			_32=-sn*fTmp+cs*_32;
		}
	}

	SK_FORCE_INLINE void Matrix3::scale(const float& fSx,const float& fSy,const float& fSz)
	{
		_11*=fSx;
		_21*=fSx;
		_31*=fSx;
		_11*=fSy;
		_21*=fSy;
		_31*=fSy;
		_11*=fSz;
		_21*=fSz;
		_31*=fSz;
	}

}//end of namespace SK

