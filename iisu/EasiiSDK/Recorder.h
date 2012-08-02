/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Provides a simplified mechanism to stop and
//                      start recording movies.
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
 * \class Recorder Recorder.h EasiiSDK/Iisu.h
 * \brief This class encapsulates the operations to record a movie.
 */
class Recorder
{
	Recorder(const Recorder &);
	Recorder &operator = (const Recorder &);

public:

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Constructor.
	 */
	Recorder();

	/**
	 * \brief Destructor.
	 */
	~Recorder();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	/**
	 * \brief Sets the path of the movie file.
	 * \param path the path of the file to be recorded.
	 */
	virtual void setPath(const SK::String &path);

	/**
	 * \brief Starts recording.
	 * \return An error if the movie recording could not be started.
	 */
	virtual SK::Result start();

	/**
	 * \brief Starts recording.
	 * \param fileName The name of the movie file.
	 * \return An error if the movie recording could not be started.
	 */
	virtual SK::Result start(const SK::String &fileName);

	/**
	 * \brief Stops recording.
	 * \return An error if this operation failed.
	 */
	virtual SK::Result stop();

	/**
 	 * \brief Checks if a movie is currently being recorded.
	 * \return \c true if a movie is being recorder, \c false
	 *         otherwise.
	 */
	virtual bool isRecording() const;

private:

	struct Impl;
	Impl *m_pimpl;

};
} // namespace Easii
} // namespace SK
