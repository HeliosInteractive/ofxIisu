/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates information about the camera in
//                      use.
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
#include <Iisu/Devices/DataExtractor.h>

namespace SK
{
namespace Easii
{
/**
 * \ingroup SOURCE
 * \class CameraInfo CameraInfo.h EasiiSDK/Iisu.h
 * \brief This class encapsulates information about the camera.
 */
class CameraInfo
{
	CameraInfo(const CameraInfo &);
	CameraInfo &operator = (const CameraInfo &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	CameraInfo();

	/**
	 * \brief Destructor.
	 */
	virtual ~CameraInfo();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	/**
	 * \brief Gets the camera's name.
	 * \return The name of the camera.
	 */
	virtual SK::String getName() const;

	/**
	 * \brief Gets the position of the camera in the world coordinate
	 *        system.
	 *
	 * \return The position of the camera.
	 */
	virtual SK::Vector3 getPosition() const;

	/**
	 * \brief Gets the up vector of the camera in world coordinates.
	 *
	 * \return The up vector of the camera.
	 */
	virtual SK::Vector3 getUp() const;

	/**
	 * \brief Gets the left vector of the camera in world coordinates.
	 *
	 * \return The left vector of the camera.
	 */
	virtual SK::Vector3 getLeft() const;

	/**
	 * \brief Gets the front vector of the camera in world coordinates.
	 *
	 * \return The front vector of the camera.
	 */
	virtual SK::Vector3 getFront() const;

	/**
	 * \brief Gets the horizontal field of view.
	 * \return The horizontal field of view of the camera.
	 */
	virtual float getHorizontalFOV() const;

	/**
	 * \brief Gets the vertical field of view.
	 * \return The vertical field of view of the camera.
	 */
	virtual float getVerticalFOV() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
