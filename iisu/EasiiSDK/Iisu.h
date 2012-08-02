/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : The main controller object.
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

#include <SDK/iisuSDK.h>
#include "ConfigEditor.h"
#include "Scene.h"

//! The main SoftKinetic namespace.
namespace SK
{

//! The main Easii namespace.
namespace Easii
{
/**
 * \class Iisu Iisu.h EasiiSDK/Iisu.h
 *
 * \brief The main easii object.
 *
 * The Iisu object is the starting point of the hierarchy. It is
 * mainly used to initialize and close the connection to iisu™ and to
 * trigger data update.
 *
 * \code
 * using namespace SK::Easii;
 *
 * Iisu &iisu = Iisu::instance();
 *
 * SK::Result initialized = iisu.init();
 * if (initialized.succeeded())
 * {
 *     SK::Result started = iisu.start();
 *     if (started.succeeded())
 *     {
 *         while (...)
 *         {
 *             if (iisu.update())
 *             {
 *                 iisu.acquire();
 *
 *                 ...
 *
 *                 iisu.release();
 *             }
 *         }
 *
 *         iisu.stop();
 *     }
 *     iisu.shutdown();
 * }
 * \endcode
 */
class Iisu
{
private:

	Iisu(const Iisu &);
	Iisu &operator = (const Iisu &);

public:

	/**
	 * \brief Constructor.
	 */
	Iisu();

	/**
	 * \brief Destructor.
	 */
	virtual ~Iisu();

	/**
	 * \brief Gets the instance of the Iisu object.
	 */
	static Iisu& instance();

	/**
	 * \brief Initializes the iisu object around an existing device
	 *        using the default configuration file.
	 * \return the result of the operation.
	 *
	 * \pre getHandle() == NULL
	 * \pre getDevice() == NULL
	 */
	virtual SK::Result init();

	/**
	 * \brief Initializes the iisu object around an existing device.
	 * \param configFilePath the path of where the config file for the application is located
	 * \return the result of the operation.
	 *
	 * \pre getHandle() == NULL
	 * \pre getDevice() == NULL
	 */
	virtual SK::Result init(const char *configFilePath);

	/**
	 * \brief Initializes the iisu object.
	 * \param iisuBinDir The directory where the iisu shared library and the iisu config file are located
	 * \param iisuConfigFilePath the path of where the config file for the application is located
	 * \return the result of the operation.
	 *
	 * \pre getHandle() == NULL
	 * \pre getDevice() == NULL
	 */
	virtual SK::Result init(const char *iisuBinDir, const char *iisuConfigFilePath);

	/**
	 * \brief Initializes the iisu object around an existing handle.
	 *
	 * \param handle An existing iisu handle.
	 * \param isSlave Tells iisu that it shouldn't clean up the handle.
	 * \return the result of the operation.
	 *
	 * \pre getHandle() == NULL
	 * \pre getDevice() == NULL
	 */
	virtual SK::Result initFromHandle(SK::IisuHandle &handle, bool isSlave = false);

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Closes the iisu handle.
	 *
	 * Closes the underlying handle and frees all resources.
	 *
	 * \post getHandle() == NULL
	 * \post getDevice() == NULL
	 * \deprecated Use shutdown
	 * \sa shutdown
	 */
	void close();
	// \endcond

	/**
	 * \brief Shuts down the iisu handle.
	 *
	 * Closes the underlying handle and frees all resources.
	 *
	 * \post getHandle() == NULL
	 * \post getDevice() == NULL
	 */
	virtual void shutdown();

	/**
	 * \brief Gets the current version if iisu.
	 * \return The full iisu version.
	 */
	virtual SK::String getVersion() const;

	/**
	 * \brief Checks whether the given layer is enabled in this
	 *        configuration.
	 * \return \c true if the layer is enabled, \c false if it isn't or
	 *         if it doesn't exist.
	 */
	virtual bool isLayerEnabled(const char *layerName) const;

	/**
	 * \brief Starts iisu.
	 * \return the result of the operation.
	 */
	virtual SK::Result start();

	/**
	 * \brief Stops iisu.
	 *
	 * Tells iisu to stop processing data. Data won't be released
	 * until shutdown() is called.
	 */
	virtual void stop();

	/**
	 * \brief Updates all internal data handles at the next frame.
	 *
	 * This operation will wait until the next available frame.
	 *
	 * This operation can timeout without updating.  In this case, it
	 * will return \c false.
	 *
	 * In application-driven mode, the following idiom should be used:
	 *
	 * \code
	 * SK::Easii::Iisu &iisu = ...
	 * if (iisu.update())
	 * {
	 *     iisu.acquire();
	 *     // Use data
	 *     iisu.release();
	 * }
	 * \endcode
	 *
	 * \return \c true if the data was updated, \c false otherwise.
	 * \sa updateAndAcquire
	 * \pre getDevice() != NULL
	 */
	virtual bool update();

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Tells iisu to update all internal data handles at the
	 *        next frame.
	 *
	 * This operation will wait until the next available frame.  At
	 * the next frame, the data is updated and locks acquired.
	 * releaseData() must be called to release the locks and allow
	 * iisu to continue processing.
	 *
	 * \code
	 * SK::Easii::Iisu &iisu = ...
	 * if (iisu.updateData())
	 * {
	 *     // Use data
	 *     iisu.releaseData();
	 * }
	 * \endcode
	 *
	 * \return \c true if the data was updated, \c false otherwise.
	 * \sa releaseData
	 * \pre getDevice() != NULL
	 * \deprecated Use updateAndAcquire
	 */
	bool updateData();
	// \endcond

	/**
	 * \brief Updates all internal data handles at the next frame.
	 *
	 * This operation will wait until the next available frame.  At
	 * the next frame, the data is updated and locks acquired.
	 * release() must be called to release the locks.
	 *
	 * This operation can timeout without updating.  In this case, it
	 * will return \c false.
	 *
	 * In application-driven mode, the following idiom should be used:
	 *
	 * \code
	 * SK::Easii::Iisu &iisu = ...
	 * if (iisu.updateAndAcquire())
	 * {
	 *     // Use data
	 *     iisu.release();
	 * }
	 * \endcode
	 *
	 * updateAndAcquire() will also compute the frame before updating the
	 * data handles.
	 *
	 * \return \c true if the data was updated, \c false otherwise.
	 * \sa update
	 * \sa acquire
	 * \sa release
	 * \pre getDevice() != NULL
	 */
	virtual bool updateAndAcquire();

	/**
	 * \brief Locks the data so it remains in a consistent state.
	 * \return \c true if the acquisition succeeded.
	 */
	virtual bool acquire();

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Releases the data to unlock the next updateData.
	 * \deprecated Use release
	 * \sa updateData
	 * \pre getDevice() != NULL
	 */
	void releaseData();
	// \endcond

	/**
	 * \brief Releases any data handles that were acquired in
	 *        \c updateAndAcquire or \c lock.
	 * \sa updateAndAcquire
	 * \sa acquire
	 * \pre getDevice() != NULL
	 */
	virtual void release();

	/**
	 * \brief Gets a stack of errors accumulated through the last
	 *        update call.
	 *
	 * \return a list of all errors reported during the last update.
	 */
	virtual const SK::Array<SK::Error> &getErrors() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets a stack of errors accumulated through the last
	 *        update call.
	 *
	 * \return a list of all errors reported during the last update.
	 * \deprecated
	 */
	const SK::Array<SK::Error> &getErrorStack() const;
	// \endcond

	/*!
	 * \brief Accessor for the Scene object.
	 * \return a reference to the Scene object.
	 * \sa Scene
	 * \pre getDevice() != NULL
	 */
	virtual Scene& getScene();

	/**
	 * \brief Gets a reference to the iisu scene.
	 * \return a reference to the scene object.
	 * \pre getDevice() != NULL
	 */
	virtual ConfigEditor& getConfigEditor();

	/**
	 * \brief Gets a handle to an iisu parameter.
	 * \param path The path to the parameter.
	 * \return A ParameterHandle object allowing access to the parameter.
	 * \pre getDevice() != NULL
	 * \deprecated This was only put here to make it convenient for
	 *             the Toolbox during development. Use SK::Device.
	 */
	template <typename T>
	SK::ParameterHandle<T> getParameter(const char *path) const;

	/**
	 * \brief Gets a handle to an iisu data object.
	 * \param path A path to the data.
	 * \return a DataHandle object allowing access to the data
	 *         value(s).
	 *
	 * \pre getDevice() != NULL
	 * \deprecated This was only put here to make it convenient for
	 *             the Toolbox during development. Use SK::Device.
	 */
	template <typename T>
	SK::DataHandle<T> getData(const char *path) const;

	/**
	 * \brief Gets the underlying iisu device.
	 *
	 * \return A pointer to the device.
	 */
	virtual SK::Device* getDevice();

	/**
	 * \brief Gets the underlying iisu device.
	 *
	 * \return A const pointer to the device.
	 */
	virtual const SK::Device* getDevice() const;

	/**
	 * \brief Gets the underlying iisu handle.
	 *
	 * \return A pointer to the handle.
	 */
	virtual SK::IisuHandle* getHandle();

	/**
	 * \brief Gets the underlying iisu handle.
	 *
	 * \return A const pointer to the handle.
	 */
	virtual const SK::IisuHandle* getHandle() const;

	/**
	 * \brief Checks if a fatal error occurred.
	 * \return \c true if a fatal error occurred, \c false if no error
	 *         occurred, or if a non-fatal error occurred.
	 */
	virtual bool hasFatalError() const;

	/**
	 * \brief Gets the last fatal error that occurred.
	 *
	 * If hasFatalError() is \c false, then this
	 * <code>iisu.getFatalError().hasError()</code> is \c false.
	 *
	 * \return An error object
	 */
	virtual SK::Error getFatalError() const;

private:

	struct Impl;
	Impl *m_pimpl;

};

template<typename T>
SK::ParameterHandle<T> Iisu::getParameter(const char *path) const
{
	return const_cast<Device *>(getDevice())->registerParameterHandle<T>(path);
}

template<typename T>
SK::DataHandle<T> Iisu::getData(const char *path) const
{
	return const_cast<Device *>(getDevice())->registerDataHandle<T>(path);
}
} // namespace Easii
} // namespace SK
