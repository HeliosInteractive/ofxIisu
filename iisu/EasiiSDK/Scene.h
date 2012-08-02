/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates the 3D scene.
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

#include "User.h"
#include "Source.h"
#include "UIController.h"
#include "UserController.h"
#include "Recorder.h"
#include "Calibration.h"
#include "Background.h"
#include "Hand.h"

namespace SK
{
struct Device;

namespace Easii
{
/**
 * \ingroup SCENE
 * \class Scene Scene.h EasiiSDK/Iisu.h
 * \brief Encapsulates the elements of a 3D scene.
 *
 * The Scene object contains information about the scene data (for
 * example, the list of 3D points) and other objects (such as the
 * source object that contains information about the source of data
 * that iisu™ is currently processing).
 *
 * You can access the scene from the Iisu object like so:
 *
 * \code
 * using namespace SK::Easii;
 *
 * Iisu &iisu = Iisu::instance();
 * Scene &scene = iisu.getScene();
 * \endcode
 */
class Scene
{
private:

	Scene(const Scene &);
	Scene &operator = (const Scene &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Constructor.
	 */
	Scene();

	/**
	 * \brief Destructor.
	 */
	virtual ~Scene();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the maximum possible number of users.
	 * \return the maximum number of users.
	 * \deprecated
	 */
	int getMaxUserCount() const;
	// \endcond

	/**
	 * \brief Gets the maximum possible number of users.
	 * \return The maximum number of users.
	 */
	virtual int getMaximumUserCount() const;

	/**
	 * \brief Sets the number of tracked users.
	 * \param userCount The number of users to track.
	 * \post getUserCount() <= getMaxUserCount()
	 */
	virtual void setUserCount(int userCount);

	/**
	 * \brief Gets the number of tracked users.
	 * \return The number of tracked users.
	 */
	virtual int getUserCount() const;

	/**
	 * \brief Gets a reference to the User.
	 *
	 * \param index The user index.
	 * \return A reference to the User object.
	 * \pre (index >= 0) && (index < getUserCount())
	 */
	User &getUser(int index);

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the maximum number of controllers.
	 * \return The maximum number of controllers.
	 * \deprecated
	 */
	int getMaxControllerCount() const;
	// \endcond

	/**
	 * \brief Gets the maximum number of controllers.
	 * \return The maximum number of controllers.
	 */
	virtual int getMaximumControllerCount() const;

	/**
	 * \brief Sets the number of tracked controllers.
	 * \param controllerCount The number of controllers to track.
	 * \post getControllerCount() <= getMaxControllerCount()
	 */
	virtual void setControllerCount(int controllerCount);

	/**
	 * \brief Gets the number of tracked controllers.
	 * \return The number of tracked controllers.
	 */
	virtual int getControllerCount() const;

	/**
	 * \brief Gets a reference to the Controller.
	 *
	 * \param index The controller index.
	 * \return A reference to the Controller object.
	 * \pre (index >= 0) && (index < getControllerCount())
	 */
	Controller &getController(int index);

	/**
	 * \brief Gets the maximum number of hands.
	 * \return The maximum number of hands.
	 */
	virtual int getMaximumHandCount() const;

	/**
	 * \brief Gets the number of tracked hands.
	 * \return The number of hands to track.
	 */
	virtual int getHandCount() const;

	/**
	 * \brief Gets a reference to the Hand.
	 *
	 * \param index The hand index.
	 * \return A reference to the Hand object.
	 * \pre (index >= 0) && (index < getHandCount())
	 */
	Hand &getHand(int index);

	/**
	 * \brief Gets a reference to the scene's source object.
	 * \return A reference to the source.
	*/
	virtual Source &getSource();

	/**
	 * \brief Gets a reference to the scene's background.
	 * \return A reference to the background.
	 */
	virtual Background &getBackground();

	/**
	 * \brief Gets a reference to the scene's calibration.
	 * \return A reference to the calibration.
	 */
	virtual Calibration &getCalibration();

	/**
	 * \brief Gets a reference to the scene's recorder.
	 * \return A reference to the recorder.
	 */
	virtual Recorder &getRecorder();

	/**
	 * \brief Gets an array of 3D cloud points.
	 *
	 * The vertex list contains a set of points computed from the
	 * depth image.
	 *
	 * \return A reference to the image object containing the 3D cloud
	 *         point.
	 */
	virtual const SK::Array<SK::Vertex> &getCloud() const;

	/**
	 * \brief Gets the scene label image.
	 * \return The label image.
	 */
	virtual const SK::Image &getLabelImage() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
