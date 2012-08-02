/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates a user pointer (see skeleton).
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

#include "Pointer.h"
#include <Iisu/Devices/Device.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Iisu/Devices/DataExtractor.h>


namespace SK {
namespace Easii {
class UserController;

/**
 * \ingroup UM
 * \class UserPointer UserPointer.h EasiiSDK/Iisu.h
 * \brief A pointer based on the user data.
 */
class UserPointer : public Pointer
{
	UserPointer(const UserPointer &);
	UserPointer &operator = (const UserPointer &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	UserPointer();

	/**
	 * \brief Destructor.
	 */
	virtual ~UserPointer();
	// \endcond

	// \cond IGNORE_DOXYGEN
	void init(UserController& controller, DataHandle<SK::Array<SK::Vector3> >& bodyPartArray);
	// \endcond

	virtual SK::Vector3 getPosition() const;

	virtual int getStatus() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
