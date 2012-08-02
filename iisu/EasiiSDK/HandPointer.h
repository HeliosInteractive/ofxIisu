/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.5
//  Date              : 2012/02/20
//  Module Name       : Easii
//  Description       : Encapsulates the data to model a hand pointer.
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

namespace SK {
namespace Easii {
class Hand;

/**
 * \ingroup CI
 * \class HandPointer HandPointer.h EasiiSDK/Iisu.h
 * \brief This class uses iisu's near mode for the pointer.
 * \sa UserPointer
 * \sa UIPointer
 * \sa HandController
 * \sa Hand
 */
class HandPointer : public Pointer
{
	HandPointer(const HandPointer &);
	HandPointer &operator = (const HandPointer &);

public:

	// \cond IGNORE_DOXYGEN
	HandPointer();

	virtual ~HandPointer();

	void init(Hand &hand);
	// \endcond

	virtual SK::Vector3 getPosition() const;

	virtual int getStatus() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
