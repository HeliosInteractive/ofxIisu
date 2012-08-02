namespace SK 
{

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame()
{
	*this = IDENTITY;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(const Quaternion& quat, const Vector3& pos)
{
	m_quat = quat;
	m_pos = pos;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(float quatW, float quatX, float quatY, float quatZ, float posX, float posY, float posZ)
{
	m_quat.setWXYZ(quatW, quatX, quatY, quatZ);
	m_pos.set(posX, posY, posZ);
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(const Quaternion& quat)
{
	m_quat = quat;
	m_pos = Vector3::ZERO;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(const Matrix3& m3x3)
{
	m_quat.fromMatrix3(m3x3);
	m_pos = Vector3::ZERO;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(const float& angle, const Vector3& axis)
{
	m_quat.fromAngleAxis(angle, axis);
	m_pos = Vector3::ZERO;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
	m_quat.fromAxes(xAxis, yAxis, zAxis);
	m_pos = Vector3::ZERO;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame::Frame(const Vector3& rotVec)
{
	m_quat.fromRotationVector(rotVec);
	m_pos = Vector3::ZERO;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE bool Frame::operator==(const Frame& frame) const
{
	if (m_quat == frame.m_quat && m_pos == frame.m_pos)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE bool Frame::operator!=(const Frame& frame) const
{
	if (m_quat != frame.m_quat || m_pos != frame.m_pos)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE bool Frame::equals(const Frame& frame, float epsilon) const
{
	if (m_quat.equals(frame.m_quat, epsilon) && m_pos.distance(frame.m_pos) < epsilon)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE bool Frame::isIdentity(float epsilon) const
{
	if (m_quat.isIdentity(epsilon) && m_pos.length() < epsilon)
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::operator=(const Frame& frame)
{
	m_quat = frame.m_quat;
	m_pos = frame.m_pos;

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame Frame::operator*(const Frame& frame) const
{
	Frame tmp;
	return tmp.compose(*this, frame);
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::operator*=(const Frame& frame)
{
	return compose(frame);
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::set(const Quaternion& quat, const Vector3& pos)
{
	m_quat = quat;
	m_pos = pos;

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::setWXYZ(float quatW, float quatX, float quatY, float quatZ, float posX, float posY, float posZ)
{
	m_quat.setWXYZ(quatW, quatX, quatY, quatZ);
	m_pos.set(posX, posY, posZ);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::inverse()
{
	m_quat.conjugate();
	m_pos = -(m_quat * m_pos);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::inverse(const Frame& frame)
{
	m_quat = frame.m_quat.getConjugate();
	m_pos = -(m_quat * frame.m_pos);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame Frame::getInverse() const
{
	Frame frame = *this;

	return frame.inverse();
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::compose(const Frame& frame)
{
	// WARNING: m_pos needs to be computed before m_quat as its computation
	//          requires the value of m_quat before the operation.
	m_pos = m_quat * frame.m_pos + m_pos;
	m_quat = m_quat * frame.m_quat;

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::compose(const Frame& frame1, const Frame& frame2)
{
	m_quat = frame1.m_quat * frame2.m_quat;
	m_pos = frame1.m_quat * frame2.m_pos + frame1.m_pos;

	return *this;
}


//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame Frame::scale(float factor) const
{
	Frame frame = *this;
	frame.m_pos*=factor;
	return frame;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::lerp(const Frame& srcFrame, const Frame& destFrame, float weight)
{
	m_quat = Quaternion::NLerp(weight, srcFrame.m_quat, destFrame.m_quat, true);
	m_pos = srcFrame.m_pos + weight * (destFrame.m_pos - srcFrame.m_pos);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::lerp(const Frame& destFrame, float weight)
{
	m_quat = Quaternion::NLerp(weight, m_quat, destFrame.m_quat, true);
	m_pos = m_pos + weight * (destFrame.m_pos - m_pos);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::slerp(const Frame& srcFrame, const Frame& destFrame, float weight)
{
	m_quat = Quaternion::Slerp(weight, srcFrame.m_quat, destFrame.m_quat, true);
	m_pos = srcFrame.m_pos + weight * (destFrame.m_pos - srcFrame.m_pos);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
SK_FORCE_INLINE Frame& Frame::slerp(const Frame& destFrame, float weight)
{
	m_quat = Quaternion::Slerp(weight, m_quat, destFrame.m_quat, true);
	m_pos = m_pos + weight * (destFrame.m_pos - m_pos);

	return *this;
}

} // namespace SK.

