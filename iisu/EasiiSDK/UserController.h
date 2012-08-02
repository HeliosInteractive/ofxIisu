/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates a user controller.
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
#include "Controller.h"
#include "UserPointer.h"
#include "BoundingBox.h"
#include "BodyPart.h"

namespace SK {
namespace Easii {
/**
 * \ingroup UM
 * \class UserController UserController.h EasiiSDK/Iisu.h
 * \brief Controller data derived by Easii from the user data.
 * \sa User
 */
class UserController : public Controller
{
	UserController(const UserController&);
	UserController &operator = (const UserController&);

public:

	// \cond IGNORE_DOXYGEN
	UserController();

	virtual ~UserController();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(int index, SK::Device &device, DataHandle<SK::Array<SK::Vector3> >& bodyPartArray);
	// \endcond

	virtual bool isActive() const;

	virtual UserPointer &getPointer();

	virtual const SK::Array<Gesture> &getGestures() const;

	virtual BoundingBox getBoundingBox() const;

	virtual SK::Vector3 getPosition() const;

	// \cond IGNORE_DOXYGEN
	SK::Vector3 normalizeCoordinates(const SK::Vector3 &coords) const;

	SK::Vector3 worldToController(const SK::Vector3 &coords) const;
	// \endcond

private:

	virtual void addGesture(const Gesture &gesture);

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
