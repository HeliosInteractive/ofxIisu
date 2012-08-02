/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates iisu's scene calibration.
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
#include <Foundation/DataTypes/Geometry/Matrix4.h>

namespace SK {
namespace Easii {
/**
 * \ingroup SCENE
 * \class Calibration Calibration.h EasiiSDK/Iisu.h
 * \brief This class is used to access the camera calibration.
 *
 * SCENE.CALIBRATION provides a set of parameters for controlling the
 * iisu calibration, that is, the process that makes it possible to
 * setup the position and orientation of the scene center.
 *
 *
 * There are three calibration modes available, chosen by using the
 * SCENE.CALIBRATION.MODE parameter. These calibration modes are
 * described below. Whenever SCENE.CALIBRATION.MODE is enabled (that
 * is, when it has a value that is NOT zero) the normal iisu
 * processing pipeline becomes disabled. Data under the SCENE layer is
 * therefore not available, but the INFO.FEEDBACK.Image gives an
 * overview of what happens during the calibration phase.
 *
 * There are three different scene calibration modes in iisu:
 *
 * <h3>T-Stance based mode (SCENE.CALIBRATION.T-STANCE)</h3>

 * In this mode, the User must stand at the center of the scene,
 * facing the camera, with their arms extended in a T-position for a
 * few seconds. After the calibration has been performed and saved,
 * the calibration data is stored along with other iisu parameters,
 * and is automatically reloaded by iisu at application startup.
 *
 * <h3>Floor based mode (SCENE.CALIBRATION.FLOOR)</h3>
 *
 * This mode does not depend on any user interaction. The floor (if
 * visible) is automatically detected and this data is used to compute
 * an accurate 3D scene center orientation.
 *
 * <h3>Editing mode (SCENE.CALIBRATION.EDITING)</h3>
 *
 * Regardless of which calibration mode has been used, iisu supports
 * a manual correction of the calibration matrix resulting from one of
 * the previous steps. This correction can be achieved through
 * adjustment of six parameters: the camera position X, Y, and Z; and
 * the camera orientation Yaw, Pitch and Roll in the scene reference.
 */
class Calibration
{
	Calibration(const Calibration &);
	Calibration &operator = (const Calibration &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	Calibration();

	/**
	 * \brief Destructor.
	 */
	virtual ~Calibration();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the matrix used to convert camera view points to
	 *        world coordinates.
	 *
	 * \return A 4x4 matrix representing the transformation matrix from
	 *         camera coordinates to world coordinates
	 * \deprecated See getCameraToWorldMatrix
	 * \sa getCameraToWorldMatrix
	 */
	SK::Matrix4 getCam2WorldMatrix() const;
	// \endcond

	/**
	 * \brief Gets the matrix used to convert camera view points to
	 *        world coordinates.
	 *
	 * \return A 4x4 matrix representing the transformation matrix from
	 *         camera coordinates to world coordinates.
	 */
	virtual SK::Matrix4 getCameraToWorldMatrix() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Transforms a point from world coordinates to camera
	 *        coordinates.
	 *
	 * \return The same point in the camera coordinate system.
	 * \deprecated
	 * \sa worldToCamera
	 */
	SK::Vector3 world2Cam(const SK::Vector3 &v) const;
	// \endcond

	/**
	 * \brief Transforms a point from world coordinates to camera
	 *        coordinates.
	 *
	 * \return The same point in the camera coordinate system.
	 * \sa cameraToWorld
	 */
	virtual SK::Vector3 worldToCamera(const SK::Vector3 &v) const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Transforms a point from camer coordinates to world
	 *        coordinates.
	 *
	 * \return The same point in the world coordinate system.
	 * \deprecated
	 * \sa cameraToWorld
	 */
	SK::Vector3 cam2World(const SK::Vector3 &v) const;
	// \endcond

	/**
	 * \brief Transforms a point from camera coordinates to world
	 *        coordinates.
	 *
	 * \return The same point in the world coordinate system.
	 * \sa worldToCamera
	 */
	virtual SK::Vector3 cameraToWorld(const SK::Vector3 &v) const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
