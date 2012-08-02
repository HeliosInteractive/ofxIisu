/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates information about the current
//                      movie.
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

namespace SK {
namespace Easii {
/**
 * \ingroup SOURCE
 * \class MovieInfo MovieInfo.h EasiiSDK/Iisu.h
 * \brief This class encapsulates information about a movie.
 */
class MovieInfo
{
	MovieInfo(const MovieInfo &);
	MovieInfo &operator = (const MovieInfo &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Constructor.
	 */
	MovieInfo();

	/**
	 * \brief Destructor.
	 */
	virtual ~MovieInfo();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	/**
	 * \brief Gets the name of the current movie.
	 * \return The movie filename.
	 */
	virtual SK::String getName() const;

	/**
	 * \brief Gets the total number of frames in the current movie.
	 * \return The total number of frames.
	 */
	virtual int32_t getFrameCount() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
