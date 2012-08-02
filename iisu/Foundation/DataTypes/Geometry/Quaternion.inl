namespace SK 
{

	SK_FORCE_INLINE Quaternion::Quaternion ()
	{
		w = 1.0f;
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( float fW, float fX, float fY, float fZ )
	{
		w = fW;
		x = fX;
		y = fY;
		z = fZ;
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( const Quaternion& quat )
	{
		w = quat.w;
		x = quat.x;
		y = quat.y;
		z = quat.z;
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( const Matrix3& m3x3 )
	{
		fromMatrix3( m3x3 );
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( const Matrix4& m4x4 )
	{
		fromMatrix4( m4x4 );
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( float angle, const Vector3& axis )
	{
		fromAngleAxis ( angle, axis );
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis  )
	{
		fromAxes ( xAxis, yAxis, zAxis );
	}

	SK_FORCE_INLINE Quaternion::Quaternion ( const Vector3& rotVec )
	{
		fromRotationVector ( rotVec );
	}

	/*	
	SK_FORCE_INLINE Quaternion ( const Vector3* akAxis )
	{
	this->FromAxes ( akAxis );
	}		

	explicit SK_FORCE_INLINE Quaternion ( float* valptr )
	{
	memcpy ( val, valptr, sizeof ( float ) *4 );
	}		

	SK_FORCE_INLINE const float& Quaternion::operator [] ( const size_t i ) const
	{
	assert ( i < 4 );

	return * ( &w+i );
	}

	SK_FORCE_INLINE float& Quaternion::operator [] ( const size_t i )
	{
	assert ( i < 4 );

	return * ( &w+i );
	}
	*/
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE float* Quaternion::ptr()
	{
		return &x;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE const float* Quaternion::ptr() const
	{
		return &x;
	}
	//-----------------------------------------------------------------------

	SK_FORCE_INLINE void Quaternion::fromRotationVector(const Vector3& rotVec)
	{
		float sqrAngle = rotVec.x * rotVec.x + rotVec.y * rotVec.y + rotVec.z * rotVec.z;
		float angle = SK::Math::sqrt(sqrAngle);

		if (Math::abs(angle) < ms_fEpsilon)
		{
			w = 1.0f;
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		else
		{
			float halfAngle = 0.5f * angle;
			float sinHalfAngle = Math::sin(halfAngle);

			w = Math::cos(halfAngle);
			x = sinHalfAngle * rotVec.x / angle;
			y = sinHalfAngle * rotVec.y / angle;
			z = sinHalfAngle * rotVec.z / angle;
		}

	}

	SK_FORCE_INLINE void Quaternion::fromAngleAxis(const float& angle, const Vector3& axis)
	{
		float axisNorm = axis.length();

		if (Math::abs(angle) < ms_fEpsilon || axisNorm < ms_fEpsilon)
		{
			w = 1.0f;
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		else
		{	
			float halfAngle = 0.5f * angle;
			float sinHalfAngle = Math::sin(halfAngle);

			w = Math::cos(halfAngle);
			x = sinHalfAngle * axis.x / axisNorm;
			y = sinHalfAngle * axis.y / axisNorm;
			z = sinHalfAngle * axis.z / axisNorm;
		}
	}

	SK_FORCE_INLINE void Quaternion::toAngleAxis(float& angle, Vector3& axis) const
	{
		float absSinHalfAngle = Math::sqrt(x * x + y * y + z * z);

		if (absSinHalfAngle < ms_fEpsilon || Math::abs(w) >= 1.0f)
		{
			angle = 0.0f;

			axis.x = 1.0f;
			axis.y = 0.0f;
			axis.z = 0.0f;
		}
		else
		{
			if (w >= 0.0f)
			{
				angle = 2.0f * Math::aTan2(absSinHalfAngle, w);
			}
			else
			{
				angle = -2.0f * Math::aTan2(absSinHalfAngle, -w);
			}

			axis.x = x / absSinHalfAngle;
			axis.y = y / absSinHalfAngle;
			axis.z = z / absSinHalfAngle;
		}
	}



	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Quaternion::xAxis(void) const
	{
		//float fTx  = 2.0f*x;
		float fTy  = 2.0f*y;
		float fTz  = 2.0f*z;
		float fTwy = fTy*w;
		float fTwz = fTz*w;
		float fTxy = fTy*x;
		float fTxz = fTz*x;
		float fTyy = fTy*y;
		float fTzz = fTz*z;

		return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Quaternion::yAxis(void) const
	{
		float fTx  = 2.0f*x;
		float fTy  = 2.0f*y;
		float fTz  = 2.0f*z;
		float fTwx = fTx*w;
		float fTwz = fTz*w;
		float fTxx = fTx*x;
		float fTxy = fTy*x;
		float fTyz = fTz*y;
		float fTzz = fTz*z;

		return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Quaternion::zAxis(void) const
	{
		float fTx  = 2.0f*x;
		float fTy  = 2.0f*y;
		float fTz  = 2.0f*z;
		float fTwx = fTx*w;
		float fTwy = fTy*w;
		float fTxx = fTx*x;
		float fTxz = fTz*x;
		float fTyy = fTy*y;
		float fTyz = fTz*y;

		return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
	}

	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Quaternion::rAxis ( float tolerance ) const
	{
		if ((this->hasAxes(tolerance))==true)
		{
			Vector3 axis=Vector3(x,y,z); // its length is multiplied by sin(theta/2)
			axis.normalize(tolerance);
			return axis;
		}
		else
		{
			return Vector3::ZERO;
		}
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE bool Quaternion::equals ( const Quaternion& rhs, const float tolerance ) const
	{
		if ( getAngleTo(rhs) > tolerance)
		{
			return false;
		}
		return true;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::getAngleTo ( const Quaternion& rhs ) const
	{
		Quaternion rhs_inv = rhs.getConjugate();
		Quaternion thisInRhs = rhs_inv * *this;
		float thisInRhs_angle; 
		Vector3 thisInRhs_axis;
		thisInRhs.toAngleAxis(thisInRhs_angle, thisInRhs_axis);

		return Math::abs(thisInRhs_angle);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE bool Quaternion::operator== ( const Quaternion& rhs ) const
	{
		return ( rhs.x == x ) && ( rhs.y == y ) &&
			( rhs.z == z ) && ( rhs.w == w );
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE bool Quaternion::operator!= ( const Quaternion& rhs ) const
	{
		return !operator== ( rhs );
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE bool Quaternion::isIdentity ( float tolerance ) const
	{
		return equals(IDENTITY, tolerance);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
	{
		return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::operator- (const Quaternion& rkQ) const
	{
		return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::operator* (const Quaternion& rkQ) const
	{
		// NOTE:  Multiplication is not generally commutative, so in most
		// cases p*q != q*p.

		return Quaternion
			(
			w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
			w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
			w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
			w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
			);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::operator* (float fScalar) const
	{
		return Quaternion(w * fScalar, x * fScalar,y * fScalar,z * fScalar);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::operator/ (float fScalar) const
	{
		return Quaternion(w / fScalar, x / fScalar,y / fScalar,z / fScalar);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion operator* (float fScalar, const Quaternion& rkQ)
	{
		return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
			fScalar*rkQ.z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion & Quaternion::operator +=( const Quaternion& q )
	{
		w += q.w;
		x += q.x;
		y += q.z;
		z += q.z;
		return *this;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion & Quaternion::operator -=( const Quaternion& q)
	{
		w -= q.w;
		x -= q.x;
		y -= q.z;
		z -= q.z;
		return *this;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion & Quaternion::operator *=( const Quaternion& q )
	{
		*this = (*this*q);
		return *this;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion & Quaternion::operator *=( float scalar  )
	{
		w *= scalar;
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion & Quaternion::operator /=( float scalar  )
	{
		w /= scalar;
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::operator- () const
	{
		return Quaternion(-w,-x,-y,-z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::dot (const Quaternion& rkQ) const
	{
		return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::length () const
	{
		return Math::sqrt(w*w+x*x+y*y+z*z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::squaredLength() const
	{
		return w*w+x*x+y*y+z*z;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE bool Quaternion::hasAxes (float tolerance) const
	{
		if ((x*x+y*y+z*z)>tolerance)
		{
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::normalize(void)
	{
		float len = length();
		float factor = 1.0f / len;
		*this = (*this) * factor;
		return len;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE void Quaternion::normalizeIfNeeded ( void )
	{
		float sqLen = squaredLength();
		if(Math::equal(sqLen, 1.0f, 1e-06f) == false)
		{
			float len = Math::sqrt(sqLen);
			float factor = 1.0f / len ;
			*this = *this * factor;
		}
	}
	//----------------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::getNormalized(void) const
	{
		Quaternion ret = *this;
		ret.normalize();
		return ret;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::getInverse () const
	{
		float fNorm = w*w+x*x+y*y+z*z;
		if ( Math::abs((float)(float)fNorm) > 1E-6 )
		{
			float fInvNorm = 1.0f/fNorm;
			return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
		}
		else
		{
			// return an invalid result to flag the error
			return Quaternion(1.f, 0.f, 0.f, 0.f);
		}
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::getUnitInverse () const
	{
		// assert:  'this' is unit length
		return Quaternion(w,-x,-y,-z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion& Quaternion::conjugate()
	{
		// w left unchanged.
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::getConjugate() const
	{
		return Quaternion(w,-x,-y,-z);
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::getExp () const
	{
		// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
		// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
		// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

		float fAngle ( Math::sqrt(x*x+y*y+z*z) );
		float fSin = Math::sin(fAngle);

		SK::Quaternion kResult;
		kResult.w = Math::cos(fAngle);

		if ( Math::abs(fSin) >= ms_fEpsilon )
		{
			float fCoeff = fSin/(fAngle);
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
		}
		else
		{
			kResult.x = x;
			kResult.y = y;
			kResult.z = z;
		}

		return kResult;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::getLog () const
	{
		// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
		// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
		// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

		SK::Quaternion kResult;
		kResult.w = 0.0;

		if ( Math::abs(w) < 1.0 )
		{
			float fAngle ( Math::aCos(w) );
			float fSin = Math::sin(fAngle);
			if ( Math::abs(fSin) >= ms_fEpsilon )
			{
				float fCoeff = fAngle/fSin;
				kResult.x = fCoeff*x;
				kResult.y = fCoeff*y;
				kResult.z = fCoeff*z;
				return kResult;
			}
		}

		kResult.x = x;
		kResult.y = y;
		kResult.z = z;

		return kResult;
	}
	/*
	Vector3 Quaternion::RotateVector(const Quaternion & q, const Vector3 & v)
	{
	// the quaternion rotation operator is defined as follow (QRS, B. Kuipers, P58) :
	// w (rotated vector) = q (input quaternion) v (input vector) q* (quaternion complex conjugate)
	// --> w = QvQ*

	//const Quaternion vp = q * Quaternion(0, v[0], v[1], v[2]) * Conjugate(q);
	//return Vector3(vp[1], vp[2], vp[3]);
	}*/

	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Vector3 Quaternion::operator* (const Vector3& v) const
	{		

		// nVidia SDK implementation
		Vector3 uv, uuv;
		Vector3 qvec(x, y, z);
		uv = qvec.cross(v);
		uuv = qvec.cross(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return v + uv + uuv;

	}


	//--Get Yaw returns a rotation around the z axis----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::getZYXYaw(void) const
	{
		return float(Math::aTan2(2*(w*z + x*y), 1 - 2 * (y*y + z*z)));
	}
	//--Get Roll in zyx-----------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::getZYXRoll(void) const
	{
		return float(Math::aTan2(2*(y*z + w*x), 1 - 2 * (x*x + y*y)));
	}
	//--Get Pitch in zyx ---------------------------------------------------------------------
	SK_FORCE_INLINE float Quaternion::getZYXPitch(void) const 
	{
		return float(Math::aSin(2*(w*y-z*x)));
	}
	
	//-----------------------------------------------------------------------	
	SK_FORCE_INLINE Quaternion Quaternion::GetRotationBetween ( const Vector3& source, const Vector3& destination, const Vector3& fallbackAxis)
	{
		// Based on Stan Melax's article in Game Programming Gems

		/// Gets the shortest arc quaternion to rotate this vector to the destination
		///    vector.
		///
		///    If you call this with a dest vector that is close to the inverse
		///    of this vector, we will rotate 180 degrees around the 'fallbackAxis'
		///    (if specified, or a generated axis if not) since in this case
		///    ANY axis of rotation is valid.

		SK::Quaternion q;
		// Copy, since cannot modify local
		Vector3 v0 = source;
		Vector3 v1 = destination;
		v0.normalize();
		v1.normalize();

		float d = v0.dot( v1 );
		
		//To avoid float processing imprecisions
		if (d<-1) 
		{
			d = -1;
		}

		// If dot == 1, vectors are the same
		if ( d >= 1.0f )
		{
			return Quaternion::IDENTITY;
		}
		float s = Math::sqrt ( ( 1+d ) *2 );
		if ( s < 1e-6f )
		{
			if ( fallbackAxis != Vector3::ZERO )
			{
				// rotate 180 degrees about the fallback axis
				q.fromAngleAxis ( Math::PI, fallbackAxis );
			}
			else
			{
				// Generate an axis
				Vector3 axis = Vector3::UNIT_X.cross( source );
				if ( axis.isZeroLength() ) // pick another if colinear
					axis = Vector3::UNIT_Y.cross ( source );
				axis.normalize();
				q.fromAngleAxis ( Math::PI, axis );
			}
		}
		else
		{
			float invs = 1 / s;

			Vector3 c = v0.cross ( v1 );

			q.x = c.x * invs;
			q.y = c.y * invs;
			q.z = c.z * invs;
			q.w = s * 0.5f;
			q.normalize();
		}
		return q;
	}

	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::Slerp (float fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath)
	{
		float fCos = rkP.dot(rkQ);
		SK::Quaternion rkT;

		// Do we need to invert rotation?
		if (fCos < 0.0f && shortestPath)
		{
			fCos = -fCos;
			rkT = -rkQ;
		}
		else
		{
			rkT = rkQ;
		}

		if (Math::abs(fCos) < 1 - ms_fEpsilon)
		{
			// Standard case (slerp)
			float fSin = Math::sqrt(1 - Math::sqr(fCos));
			float fAngle = Math::aTan2(fSin, fCos);
			float fInvSin = 1.0f / fSin;
			float fCoeff0 = Math::sin((1.0f - fT) * fAngle) * fInvSin;
			float fCoeff1 = Math::sin(fT * fAngle) * fInvSin;
			return fCoeff0 * rkP + fCoeff1 * rkT;
		}
		else
		{
			// There are two situations:
			// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			SK::Quaternion t = (1.0f - fT) * rkP + fT * rkT;
			// taking the complement requires renormalisation
			t.normalize();
			return t;
		}
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::SlerpExtraSpins (float fT,
		const Quaternion& rkP, const Quaternion& rkQ, int32_t iExtraSpins)
	{
		float fCos = rkP.dot(rkQ);
		float fAngle ( Math::aCos(fCos) );

		if ( Math::abs(fAngle) < ms_fEpsilon )
			return rkP;

		float fSin = Math::sin(fAngle);
		float fPhase ( Math::PI*iExtraSpins*fT );
		float fInvSin = 1.0f/fSin;
		float fCoeff0 = Math::sin((1.0f-fT)*fAngle - fPhase)*fInvSin;
		float fCoeff1 = Math::sin(fT*fAngle + fPhase)*fInvSin;
		return fCoeff0*rkP + fCoeff1*rkQ;
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE void Quaternion::Intermediate (const Quaternion& rkQ0,
		const Quaternion& rkQ1, const Quaternion& rkQ2,
		SK::Quaternion& rkA, Quaternion& rkB)
	{
		// assert:  q0, q1, q2 are unit quaternions

		SK::Quaternion kQ0inv = rkQ0.getUnitInverse();
		SK::Quaternion kQ1inv = rkQ1.getUnitInverse();
		SK::Quaternion rkP0 = kQ0inv*rkQ1;
		SK::Quaternion rkP1 = kQ1inv*rkQ2;
		SK::Quaternion kArg = 0.25*(rkP0.getLog()-rkP1.getLog());
		SK::Quaternion kMinusArg = -kArg;

		rkA = rkQ1*kArg.getExp();
		rkB = rkQ1*kMinusArg.getExp();
	}
	//-----------------------------------------------------------------------
	SK_FORCE_INLINE Quaternion Quaternion::Squad (float fT,
		const Quaternion& rkP, const Quaternion& rkA,
		const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath)
	{
		float fSlerpT = 2.0f*fT*(1.0f-fT);
		SK::Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
		SK::Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
		return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
	}
	//-----------------------------------------------------------------------	
	SK_FORCE_INLINE Quaternion Quaternion::NLerp(float fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath)
	{
		SK::Quaternion result;
		float fCos = rkP.dot(rkQ);
		if (fCos < 0.0f && shortestPath)
		{
			result = rkP + fT * ((-rkQ) - rkP);
		}
		else
		{
			result = rkP + fT * (rkQ - rkP);
		}
		result.normalize();
		return result;
	}
	//-----------------------------------------------------------------------	
	SK_FORCE_INLINE Quaternion Quaternion::clamp(const Quaternion& limitFrame, const SK::Vector2& swingLimit, const SK::Vector2& twistLimit)
	{
		// Express the rotation in limitFrame0.
		// NOTE: the limit frame is used as the reference frame for the rotation and thus we must
		//       express the rotation in this frame in order to clamp it.
		SK::Quaternion this_inLimitFrame0_quat = limitFrame.getConjugate() * *this * limitFrame;
		SK::Vector3 this_inLimitFrame0_st;
		this_inLimitFrame0_quat.toSwingTwist(this_inLimitFrame0_st);

		SK::Vector3 swing(this_inLimitFrame0_st.x, this_inLimitFrame0_st.y, 0.0f);

		// Limit swing.
		SK::Vector3 swing_normalized(swing.x / swingLimit.x, swing.y / swingLimit.y, 0.0f);
		float swing_normalized_length = swing_normalized.length();

		SK::Vector3 swing_clamped = swing;
		if (swing_normalized_length > 1.0f)
		{
			swing_clamped = (1.0f / swing_normalized_length) * swing;
		}

		// Limit twist.
		float twist_clamped = SK::Math::clamp(this_inLimitFrame0_st.z, twistLimit.x, twistLimit.y);

		// Put twist and swing_clamped back together and express the rotation as a quaternion
		// in the same reference frame as this'.
		SK::Quaternion this_clamped_inLimitFrame0_quat;
		this_clamped_inLimitFrame0_quat.fromSwingTwist(SK::Vector3(swing_clamped.x, swing_clamped.y, twist_clamped));

		SK::Quaternion this_clamped = limitFrame * this_clamped_inLimitFrame0_quat * limitFrame.getConjugate();

		return this_clamped;
	}

}


