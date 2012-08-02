/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Simple adapter around iisu's background
//                      learning data.
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
#include <Foundation/Services/Commands/Command.h>
#include <Foundation/Services/Commands/BackgroundSnapshotType.h>
#include <Iisu/Devices/DataExtractor.h>

namespace SK {
namespace Easii {
/**
 * \ingroup UM
 * \class Background Background.h EasiiSDK/Iisu.h
 * \brief This class is provided to control the scene background
 *        removal.
 *
 * <b>Background learning</b> is the process that learns the static
 * content of a scene to remove all these objects (chairs, sofas,
 * lamps, and so on) in the future.
 *
 * <b>Background removal</b> is the process of removing the background
 * of a scene (that is, the learned static content that takes no
 * active part in the scene) in order to keep only the useful
 * information (that is, the Users and/or some specific objects in the
 * scene); and improving the quality of the user/background
 * separation.
 */
class Background
{
	Background(const Background &);
	Background &operator = (const Background &);

public:

/**
 * \enum RemovalMode
 *
 * \brief Values that represent the background learning mode.
 */
	enum RemovalMode
	{
		STATIC = 0,  /*!< Static background learning. */
		DYNAMIC = 1, /*!< Dynamic background learning. */
	};

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Default constructor.
	 */
	Background();

	/**
	 * \brief Destructor.
	 */
	virtual ~Background();
	// \endcond

	// \cond IGNORE_DOXYGEN
	SK::Result init(SK::Device &device);
	// \endcond

	/**
	 * \brief Enables background learning.
	 * \param enabled Enables (or disables) background learning.
	 */
	virtual void setEnabled(bool enabled);

	/**
	 * \brief Checks whether the background removal mode is enabled.
	 *
	 * Enabling background removal dynamically can be expensive.
	 *
	 * \return \c true if the background removal mode is set, \c false
	 *         otherwise.
	 */
	virtual bool isEnabled() const;

	/**
	 * \brief Sets the background removal mode.
	 *
	 * Applies background learning to the current scene (if any).  If
	 * background removal is disabled, the value is not set.
	 *
	 * \param mode may be set to STATIC or DYNAMIC
	 */
	virtual void setRemovalMode(RemovalMode mode);

	/**
	 * \brief Gets the background removal mode.
	 *
	 * \return STATIC or DYNAMIC.
	 */
	virtual RemovalMode getRemovalMode() const;

	/**
	 * \brief Takes snapshot of the background image.
	 *
	 * The process takes approximately 30 frames to complete.  If
	 * background removal is not enabled, then this operation will fail.
	 *
	 * \return An error if the operation failed.
	 * \sa isTakingSnapshot()
	 */
	virtual SK::Result takeSnapshot();

	/**
	 * \brief Checks if iisu is in the process of taking a snapshot of
	 *        a background image.
	 *
	 * \return \c true if a background image snapshot has been
	 *         requested and has not yet completed.
	*/
	virtual bool isTakingSnapshot() const;

private:

	struct Impl;
	Impl *m_pimpl;

};

// \cond IGNORE_DOXYGEN
typedef Background::RemovalMode BackgroundMode;
// \endcond
} // namespace Easii
} // namespace SK
