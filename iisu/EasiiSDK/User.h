/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates user data.
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
#include <Iisu/Devices/DataExtractor.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/3D/Vertex.h>

#include "UserController.h"
#include "BoundingBox.h"
#include "BodyPart.h"

namespace SK {
namespace Easii {
/**
 * \ingroup UM
 * \ingroup SKELETON
 * \ingroup SHAPE
 * \class User User.h EasiiSDK/Iisu.h
 * \brief Encapsulates information about a user in the scene.
 *
 * The User object collects data about a user that has been detected
 * in the scene. There can be more than one user (depending on the
 * scene content and on your iisu™ configuration). The User object
 * allows you to retrieve information such as the user’s center of
 * mass, the bounding box or a mask delimiting the user in the image.
 *
 * There will always be as many User objects in the vector as the
 * maximum number of users that can be treated by iisu™. Each element
 * of the vector can either be ‘active’ (so that it maps to a User
 * that has been detected in the scene) or not (in which case the data
 * it contains is irrelevant).
 *
 * You can access the users through the Scene object:
 *
 * \code
 * using namespace SK::Easii;
 *
 * Iisu &iisu = Iisu::instance();
 * int userCount = iisu.getScene().getUserCount();
 * for (int i = 0; i < userCount; ++i)
 * {
 *     User &user = iisu.getScene().getUser(i);
 *     if (user.isActive())
 *     {
 *         ...
 *     }
 * }
 * \endcode
 */
class User
{
	User(const User &);
	User &operator = (const User &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	User();

	/**
	 * \brief Destructor.
	 */
	virtual ~User();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(int index, SK::Device &device);
	// \endcond

	/**
	 * \brief Checks whether the user is active or not.
	 * \return \c true if the user is currently being tracked in the
	 *         scene.
	 */
	virtual bool isActive() const;

	/**
	 * \brief Gets a list of positions of the user's centroids.
	 *\return A reference to the vector of points containing the list
	 *        of centroid positions associated to the tracked user.
	*/
	virtual const SK::Array<SK::Vector3> &getCentroids() const;

	/**
	 * \brief Gets the user's center of mass estimation.
	 * \return the user's center of mass in 3D space.
	 */
	virtual SK::Vector3 getMassCenter() const;

	/**
	 * \brief Gets the user's height estimate.
	 * \return An estimate of the user's height.
	 */
	virtual float getHeight() const;

	/**
	 * \brief Gets the user's main direction.
	 * \return The user's main direction.
	 */
	virtual SK::Vector3 getMainDirection() const;

	/**
	 * \brief Gets the label identifier of this user in the scene.
	 * \return The label identifier of this user in the scene.
	 */
	virtual int32_t getLabelID() const;

	/**
	 * \brief Gets the user's bounding box.
	 * \return the bounding box surrounding the user
	 */
	virtual SK::Easii::BoundingBox getBoundingBox() const;

	/**
	 * \brief Gets A list of vertices that are detected by isu to be a
	 *        part of the user.
	 *
	 * \return A reference to the list of 3D vertices belonging to the
	 *         user.
	 */
	virtual const SK::Array<SK::Vertex> &getVertices() const;

	/**
	 * \brief Checks whether this user's skeleton data is available.
	 * \return \c true if the user's skeleton data is computed,
	 *         \c false otherwise.
	*/
	virtual bool hasSkeleton() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets a particular body part.
	 * \param part An enum value indicating the user's body part.
	 * \return a reference to the specified body part object of the user
	 */
	BodyPart &getBodyPart(BodyPartEnum::KeyPoints part);
	// \endcond

	/**
	 * \brief Gets a particular body part.
	 * \param part An enum value indicating the user's body part.
	 * \return a reference to the specified body part object of the user
	 */
	virtual BodyPart &getBodyPart(BodyPart::KeyPoint part);

	/**
	 * \brief Gets a reference to the User's controller.
	 * \return A controller based on the user detection.
	 */
	virtual UserController &getController();

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
