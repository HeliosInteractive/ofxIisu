/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates user or UI pointer data.
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

#include <Foundation/DataTypes/Geometry/Vector3.h>

namespace SK {
namespace Easii {
/**
 * \class Pointer Pointer.h EasiiSDK/Iisu.h
 * \brief This class defines an interface for a 3D pointer.
 *
 * \sa UIPointer
 * \sa UserPointer
 * \sa HandPointer
 */
class Pointer
{

public:

	/**
	 * \brief Destructor.
	 */
	virtual ~Pointer() = 0;

	/**
	 * \brief Gets the pointer's position.
	 * \return The 3D position of the pointer.
	 */
	virtual SK::Vector3 getPosition() const = 0;

	/**
	 * \brief Gets the pointer's status.
	 * \return A value representing the status of the pointer.
	 */
	virtual int getStatus() const = 0;

};
} // namespace Easii
} // namespace SK
