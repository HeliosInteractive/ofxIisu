#pragma once

#include <System/Math/Math.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Geometry/Quaternion.h>
#include <Platform/SkPlatform.h>
#include <ostream>


//////////////////////////////////////////////////////////////////////////
namespace SK
{

class Matrix4;

/**
 * \class	Frame
 *
 * \brief	This class stands for 6D frames. It is equivalent to Matrix4 but more stable numerically speaking.
 */

class IISUSDK_API Frame
{
public:

	/**
	 * \fn	Frame::Frame();
	 *
	 * \brief	Default constructor.
	 *	 * initializes to Frame::IDENTITY
	 */

	Frame();

	/**
	 * \fn	Frame::Frame(const Quaternion& quat, const Vector3& pos);
	 *
	 * \brief	Constructor from quaternion and position.
	 *
	 * \param	quat	The quaternion.
	 * \param	pos 	The position.
	 */

	Frame(const Quaternion& quat, const Vector3& pos);

	/**
	 * \fn	Frame::Frame(float quatW, float quatX, float quatY, float quatZ, float posX, float posY,
	 * 		float posZ);
	 *
	 * \brief	Constructor from quaternion and position components.
	 *
	 * \param	quatW	The quaternion w.
	 * \param	quatX	The quaternion x coordinate.
	 * \param	quatY	The quaternion y coordinate.
	 * \param	quatZ	The quaternion z coordinate.
	 * \param	posX 	The position x coordinate.
	 * \param	posY 	The position y coordinate.
	 * \param	posZ 	The position z coordinate.
	 */

	Frame(float quatW, float quatX, float quatY, float quatZ, float posX, float posY, float posZ);

	/**
	 * \fn	explicit Frame::Frame(const Matrix4& m4x4);
	 *
	 * \brief	Constructor from matrix4.
	 *
	 * \param	m4x4	The matrix4.
	 *
	 * initializes the position to Vector3::ZERO
	 */

	explicit Frame(const Matrix4& m4x4);

	/**
	 * \fn	explicit Frame::Frame(const Matrix3& m3x3);
	 *
	 * \brief	Constructor from matrix3.
	 *
	 * \param	m3x3	The matrix3.
	 *
	 * initializes the position to Vector3::ZERO
	 */

	explicit Frame(const Matrix3& m3x3);

	/**
	 * \fn	explicit Frame::Frame(const Quaternion& quat);
	 *
	 * \brief	Constructor from quaternion.
	 *
	 * \param	quat	The quaternion.
	 *
	 * initializes the position to Vector3::ZERO
	 */

	explicit Frame(const Quaternion& quat);

	/**
	 * \fn	Frame::Frame(const float& angle, const Vector3& axis);
	 *
	 * \brief	Constructor from rotation angle and axis.
	 *
	 * \param	angle	The angle.
	 * \param	axis 	The axis.
	 */

	Frame(const float& angle, const Vector3& axis);

	/**
	 * \fn	Frame::Frame(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
	 *
	 * \brief	Constructor from orthogonal coordinate axes.
	 *
	 * \param	xAxis	The x coordinate axis.
	 * \param	yAxis	The y coordinate axis.
	 * \param	zAxis	The z coordinate axis.
	 *
	 * initializes the position to Vector3::ZERO
	 */

	Frame(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

	/**
	 * \fn	explicit Frame::Frame(const Vector3& rotVec);
	 *
	 * \brief	Constructor from rotation vector.
	 *
	 * \param	rotVec	The rotation vector.
	 *
	 * initializes the position to Vector3::ZERO
	 */

	explicit Frame(const Vector3& rotVec);

	/// \name Operators.
	//@{

	/**
	 * \fn	bool Frame::operator==(const Frame& rhs) const;
	 *
	 * \brief	Equality operator.
	 *
	 * \param	rhs	The right hand side.
	 *
	 * \return	true if the parameters are considered equivalent.
	 */

	bool operator==(const Frame& rhs) const;

	/**
	 * \fn	bool Frame::operator!=(const Frame& rhs) const;
	 *
	 * \brief	Finaliser.
	 *
	 * \param	rhs	The right hand side.
	 *	 
	 * \return	true if the parameters are not considered equivalent.
	 */

	bool operator!=(const Frame& rhs) const;

	/**
	 * \fn	bool Frame::equals(const Frame& rhs, float epsilon = 1e-04f) const;
	 *
	 * \brief	Tests if Frame is equal to another Frame, considering tolerance (in angle and position)
	 *
	 * \param	rhs	   	Frame to be compared.
	 * \param	epsilon	(optional) tolerance to be considered for comparison.
	 *
	 * \return	true if the objects are considered equal considering tolerance (in angle and position), false if they are not.
	 */

	bool equals(const Frame& rhs, float epsilon = 1e-04f) const; ///< Equality with tolerance.

	/**
	 * \fn	bool Frame::isIdentity(float epsilon = 1e-04f) const;
	 *
	 * \brief	Query if Frame is equal to identity (Quaternion identity and ZERO position) considering tolerance.
	 *
	 * \param	epsilon	(optional) the tolerance.
	 *
	 * \return	true if identity, false if not.
	 */

	bool isIdentity(float epsilon = 1e-04f) const;

	/**
	 * \fn	Frame& Frame::operator=(const Frame& rhs);
	 *
	 * \brief	Assignment operator.
	 *
	 * \param	rhs	The right hand side.
	 *
	 * \return	A shallow copy of This  frame.
	 */

	Frame& operator=(const Frame& rhs);

	/**
	 * \fn	Frame Frame::operator*(const Frame& rhs) const;
	 *
	 * \brief	Multiplication operator.
	 *
	 * \param	rhs	The right hand side.
	 *
	 * \return	The result of the operation.
	 */

	Frame operator*(const Frame& rhs) const;

	/**
	 * \fn	Frame& Frame::operator*=(const Frame& rhs);
	 *
	 * \brief	Multiplication assignment operator.
	 *
	 * \param	rhs	The right hand side.
	 *
	 * \return	The result of the operation.
	 */

	Frame& operator*=(const Frame& rhs);
	//@}

	/// \name Set the frame.
	//@{

	/**
	 * \fn	Frame& Frame::set(const Quaternion& quat, const Vector3& pos);
	 *
	 * \brief	Sets quaternion and position.
	 *
	 * \param	quat	The quaternion.
	 * \param	pos 	The position.
	 *
	 * \return	This  frame.
	 */

	Frame& set(const Quaternion& quat, const Vector3& pos);

	/**
	 * \fn	Frame& Frame::setWXYZ(float quatW, float quatX, float quatY, float quatZ, float posX,
	 * 		float posY, float posZ);
	 *
	 * \brief	Sets quaternion and position from their components.
	 *
	 * \param	quatW	The quaternion w.
	 * \param	quatX	The quaternion x coordinate.
	 * \param	quatY	The quaternion y coordinate.
	 * \param	quatZ	The quaternion z coordinate.
	 * \param	posX 	The position x coordinate.
	 * \param	posY 	The position y coordinate.
	 * \param	posZ 	The position z coordinate.
	 *
	 * \return	This  frame.
	 */

	Frame& setWXYZ(float quatW, float quatX, float quatY, float quatZ, float posX, float posY, float posZ);
	//@}

	/**
	 * \fn	Frame& Frame::inverse();
	 *
	 * \brief	Inverse the frame.
	 *
	 * \return	This  frame.
	 */

	Frame& inverse();

	/**
	 * \fn	Frame& Frame::inverse(const Frame& frame);
	 *
	 * \brief	Set content to the inverse of frame.
	 *
	 * \param	frame	The frame to be inversed.
	 *
	 * \return	This  frame.
	 */

	Frame& inverse(const Frame& frame);

	/**
	 * \fn	Frame Frame::getInverse() const;
	 *
	 * \brief	Gets the inverse.
	 *
	 * \return	The inverse.
	 */

	Frame  getInverse() const;

	/**
	 * \fn	Frame& Frame::compose(const Frame& frame);
	 *
	 * \brief	Composes frames.
	 *
	 * \param	frame	The frame.
	 *
	 * \return	This  frame.
	 */

	Frame& compose(const Frame& frame);

	/**
	 * \fn	Frame& Frame::compose(const Frame& frame1, const Frame& frame2);
	 *
	 * \brief	Composes two frames and assigns to This  frame.
	 *
	 * \param	frame1	The first frame.
	 * \param	frame2	The second frame.
	 *
	 * \return	This  frame.
	 */

	Frame& compose(const Frame& frame1, const Frame& frame2);

	/**
	 * \fn	Frame Frame::scale(float factor) const;
	 *
	 * \brief	Scales the position.
	 *
	 * \param	factor	The factor.
	 *
	 * \return	The scaled frame.
	 */

	Frame  scale(float factor) const;

	/**
	 * \fn	Frame& Frame::lerp(const Frame& srcFrame, const Frame& destFrame, float weight);
	 *
	 * \brief	Linear interpolation with assignation between source and destination frame.
	 *
	 * \param	srcFrame 	Source frame.
	 * \param	destFrame	Destination frame.
	 * \param	weight   	The weight.
	 *
	 * \return	This  frame.
	 */

	Frame& lerp(const Frame& srcFrame, const Frame& destFrame, float weight);

	/**
	 * \fn	Frame& Frame::lerp(const Frame& destFrame, float weight);
	 *
	 * \brief	Linear interpolation with assignation between this frame and destination frame.
	 *
	 * \param	destFrame	Destination frame.
	 * \param	weight   	The weight.
	 *
	 * \return	This  frame.
	 */

	Frame& lerp(const Frame& destFrame, float weight);

	/**
	 * \fn	Frame& Frame::slerp(const Frame& srcFrame, const Frame& destFrame, float weight);
	 *
	 * \brief	Spherical linear interpolation with assignation between source and destination frame.
	 *
	 * \param	srcFrame 	Source frame.
	 * \param	destFrame	Destination frame.
	 * \param	weight   	The weight.
	 *
	 * \return	This  frame.
	 */

	Frame& slerp(const Frame& srcFrame, const Frame& destFrame, float weight);

	/**
	 * \fn	Frame& Frame::slerp(const Frame& destFrame, float weight);
	 *
	 * \brief	Spherical linear interpolation with assignation between this frame and destination frame.
	 *
	 * \param	destFrame	Destination frame.
	 * \param	weight   	The weight.
	 *
	 * \return	This  frame.
	 */

	Frame& slerp(const Frame& destFrame, float weight);
	//@}

	/// Special values.
	static const Frame IDENTITY;

	/// Components.
	//@{
	Quaternion m_quat;
	Vector3 m_pos;
	//@}
};

/**
 * \fn	inline std::ostream& operator<< (std::ostream& o, const Frame& frame)
 *
 * \brief	Output stream operator.
 *
 * \param [in,out]	o	The ooutput stream.
 * \param	frame	 	The frame.
 *
 * \return	The updated output stream.
 */

inline std::ostream& operator << (std::ostream& o, const Frame& frame)
{
	o << "Frame(" << frame.m_quat.w << ", " << frame.m_quat.x << ", " << frame.m_quat.y << ", " << frame.m_quat.z << ", " << frame.m_pos.x << ", " << frame.m_pos.y << ", " << frame.m_pos.z << ")";
	return o;
}

} // namespace SK.

#ifndef SK_DEBUG
#include "Frame.inl"
#endif // SK_DEBUG.

