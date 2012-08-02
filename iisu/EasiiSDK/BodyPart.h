/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates a human body part (c.f. user
//                      skeleton), including it's position and it's
//                      confidence.
//
// COPYRIGHT AND CONFIDENTIALITY NOTICE - SOFTKINETIC CONFIDENTIAL
// INFORMATION All rights reserved to SOFTKINETIC SOFTWARE SA (a
// company incorporated and existing under the laws of Belgium, with
// its principal place of business at Boulevard de la Plainelaan 15,
// 1050 Brussels (Belgium), registered with the Crossroads bank for
// enterprises under company number 0890 705 864 - "Softkinetic
// Software")
//
// The source code of the SoftKinetic iisu SDK is proprietary and
// confidential information of Softkinetic Software SA
// For any question about terms and conditions, please contact: info@softkinetic.com
// Copyright (c) 2002-2012 Softkinetic Software SA
/****************************************************************************************/

#pragma once

#include <Iisu/Devices/Device.h>
#include <Foundation/DataTypes/Skeleton/KeyPoints.h>
#include <Iisu/Devices/DataExtractor.h>

namespace SK {
namespace Easii {
namespace BodyPartEnum = SK::SkeletonEnum;

/**
 * \ingroup SKELETON
 * \class BodyPart BodyPart.h EasiiSDK/Iisu.h

 * \brief A class encapsulating the data associated to a particular
 *        part of the User's skeleton.
 *
 * When the skeleton computation is enabled, each User detected has a
 * set of body parts available representing the spatial position of
 * the skeleton elements (head, hands, hips, and so on).
 *
 * \code
 * using namespace SK::Easii;
 *
 * User &user = iisu.getScene().getUser(0);
 * if (user.isActive() && user.hasSkeleton())
 * {
 *     BodyPart &head = user.getBodyPart(BodyPart::HEAD);
 *     ...
 * }
 * \endcode
 */
class BodyPart
{
public:

	/**
	 * \enum KeyPoint
	 * Identifies the body parts of the skeleton.
	 */
	enum KeyPoint
	{
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
		PELVIS = SK::SkeletonEnum::PELVIS,
		WAIST = SK::SkeletonEnum::WAIST,
		COLLAR = SK::SkeletonEnum::COLLAR,
		NECK = SK::SkeletonEnum::NECK,
		HEAD = SK::SkeletonEnum::HEAD,

		RIGHT_SHOULDER = SK::SkeletonEnum::RIGHT_SHOULDER,
		RIGHT_ELBOW = SK::SkeletonEnum::RIGHT_ELBOW,
		RIGHT_WRIST = SK::SkeletonEnum::RIGHT_WRIST,
		RIGHT_HAND = SK::SkeletonEnum::RIGHT_HAND,

		RIGHT_HIP = SK::SkeletonEnum::RIGHT_HIP,
		RIGHT_KNEE = SK::SkeletonEnum::RIGHT_KNEE,
		RIGHT_ANKLE = SK::SkeletonEnum::RIGHT_ANKLE,
		RIGHT_FOOT = SK::SkeletonEnum::RIGHT_FOOT,

		LEFT_SHOULDER = SK::SkeletonEnum::LEFT_SHOULDER,
		LEFT_ELBOW = SK::SkeletonEnum::LEFT_ELBOW,
		LEFT_WRIST = SK::SkeletonEnum::LEFT_WRIST,
		LEFT_HAND = SK::SkeletonEnum::LEFT_HAND,

		LEFT_HIP = SK::SkeletonEnum::LEFT_HIP,
		LEFT_KNEE = SK::SkeletonEnum::LEFT_KNEE,
		LEFT_ANKLE = SK::SkeletonEnum::LEFT_ANKLE,
		LEFT_FOOT = SK::SkeletonEnum::LEFT_FOOT,

		_COUNT,
#else
		PELVIS, /*!< The pelvis. */
		WAIST, /*!< The waist. */
		COLLAR, /*!< The collar. */
		NECK, /*!< The neck. */
		HEAD, /*!< The head. */

		RIGHT_SHOULDER, /*!< The right shoulder. */
		RIGHT_ELBOW, /*!< The right elbow. */
		RIGHT_WRIST, /*!< The right wrist. */
		RIGHT_HAND, /*!< The right hand. */

		RIGHT_HIP, /*!< The right hip. */
		RIGHT_KNEE, /*!< The right knee. */
		RIGHT_ANKLE, /*!< The right ankle. */
		RIGHT_FOOT, /*!< The right foot. */

		LEFT_SHOULDER, /*!< The left shoulder. */
		LEFT_ELBOW, /*!< The left elbow. */
		LEFT_WRIST, /*!< The left wrist. */
		LEFT_HAND, /*!< The left hand. */

		LEFT_HIP, /*!< The left hip. */
		LEFT_KNEE, /*!< The left knee. */
		LEFT_ANKLE, /*!< The left ankle. */
		LEFT_FOOT, /*!< The left foot. */
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
	};

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	BodyPart();

	/**
	 * \brief Destructor.
	 */
	virtual ~BodyPart();
	// \endcond

	// \cond IGNORE_DOXYGEN
	void init(Device& device,
			  uint32_t index,
			  DataHandle<SK::Array<SK::Vector3> >& bodyPartArray,
			  DataHandle<SK::Array<float> >& bodyPartConfidenceArray);
	// \endcond

	/**
	 * \brief Returns the coordinates of the body part.
	 * \return a Vector3 containing the position.
	 */
	virtual SK::Vector3 getPosition() const;

	/**
	 * \brief Returns the body part confidence.
	 *
	 * \return A float indicating how accurately the body part is
	 *         found (1 - found, 0 not found)
	 */
	virtual float getConfidence() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
