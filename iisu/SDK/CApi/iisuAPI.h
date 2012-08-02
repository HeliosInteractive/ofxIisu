#ifndef IISU_SDK_API_H
#define IISU_SDK_API_H

#include <Iisu/API/IisuCTypes.h>	// for Iisu C types manipulations

#include <Foundation/DataTypes/Image/Image.h>
#include <Foundation/Services/Types/TypeInfo.h>

//using namespace SK ;

extern "C" {


/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisu_getContext(OUT SkContext_C* context);
 *
 * \brief	Gets a pointer to the opaque "C" context
 *
 * \param	context	the context's pointer
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisu_getContext(OUT SkContext_C* context);


/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisu_createConfigurator(IN SkString_C * applicationConfigFile,
 * 		OUT SkApplicationConfigurator_C* configurator);
 *
 * \brief	creates and return a new configurator helper for the application.
 *
 * \param 	applicationConfigFile	the application configuration file path.
 * \param [out]	configurator		 	a pointer to an opaque ApplicationConfigurator object.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisu_createConfigurator(IN SkString_C * applicationConfigFile, OUT SkApplicationConfigurator_C* configurator);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisu_destroyConfigurator(IN SkApplicationConfigurator_C configurator);
 *
 * \brief	deletes the configurator object.
 *
 * \param	configurator	The opaque configurator pointer to delete.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisu_destroyConfigurator(IN SkApplicationConfigurator_C configurator);


IISUSDK_API SkError_C SK_SDK_DECL SkApplicationConfigurator_createIisuHandleConfiguration(IN SkApplicationConfigurator_C configurator, OUT SkIisuHandleConfig_C* iisuHandleConfig);
IISUSDK_API SkError_C SK_SDK_DECL SkApplicationConfigurator_createDeviceConfiguration(IN SkApplicationConfigurator_C configurator, OUT SkDeviceConfig_C* deviceConfig);


// Context

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_createHandle(IN SkContext_C context,
 * 		IN SkIisuHandleConfig_C iisuHandleConfig, OUT SkIisuHandle_C* handle);
 *
 * \brief	creates a new handle from a configuration structure
 *
 * \param	context				The context.
 * \param	iisuHandleConfig	The iisu handle configuration structure.
 * \param [out]	handle  	A pointer to be filled with the handle object
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_createHandle(IN SkContext_C context, IN SkIisuHandleConfig_C iisuHandleConfig, OUT SkIisuHandle_C* handle);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_createHandleFromConfig(IN SkContext_C context,
 * 		IN SkApplicationConfigurator_C configurator, OUT SkIisuHandle_C* handle);
 *
 * \brief	Create a new handle from an applicatoin configurator object.
 *
 * \param	context		  	The context.
 * \param	configurator  	The configurator.
 * \param [out]	handle	a pointer to be filled with the handle object
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_createHandleFromConfig(IN SkContext_C context, IN SkApplicationConfigurator_C configurator, OUT SkIisuHandle_C* handle);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_destroyHandle(IN SkContext_C context,
 * 		IN SkIisuHandle_C handle);
 *
 * \brief	Destroys a handle.
 *
 * \param	context	The context.
 * \param	handle 	The handle to be destroyed
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_destroyHandle(IN SkContext_C context, IN SkIisuHandle_C handle);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_destroyHandle(IN SkContext_C context,
 * 		IN SkIisuHandle_C handle);
 *
 * \brief	Destroys a handle and free the library.
 *
 * \param	context	The context.
 * \param	handle 	The handle to be destroyed
 *
 * \return	a SkError_C specifying if the call was successful or not
 * 			
 * \warning when calling this method the system will crash if any object of the library is still on stack.
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_destroyHandleAndFreeLibrary(IN SkContext_C context, IN SkIisuHandle_C handle);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_flushLogs(IN SkContext_C context);
 *
 * \brief	Flush the logs
 *
 * \param	context	The context.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_flushLogs(IN SkContext_C context);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_finalize(IN SkContext_C context);
 *
 * \brief	Finalise the context, destroying all open handles and devices.
 *
 * \param	context	The context.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_finalize(IN SkContext_C context);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkContext_registerHandle(IN SkContext_C context,
 * 		IN SkIisuHandle_C handle);
 *
 * \brief	Registers a data handle
 *
 * \param	context	The context.
 * \param	handle 	The handle to register.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkContext_registerHandle(IN SkContext_C context, IN SkIisuHandle_C handle);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_initializeDevice(IN SkIisuHandle_C handle,
 * 		IN SkDeviceConfig_C deviceConfig, OUT SkDevice_C* device);
 *
 * \brief	initialises a device from a device configuration structure
 *
 * \param	handle		  	The handle.
 * \param	deviceConfig  	The device configuration structure.
 * \param [out]	device	a pointer to be filled with the device.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_initializeDevice(IN SkIisuHandle_C handle, IN SkDeviceConfig_C deviceConfig, OUT SkDevice_C* device);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_initializeDeviceFromConfig(IN SkIisuHandle_C handle,
 * 		IN SkApplicationConfigurator_C configurator, OUT SkDevice_C* device);
 *
 * \brief	Initialises a device from an application configurator.
 *
 * \param	handle		  	The handle.
 * \param	configurator  	The configurator.
 * \param [out]	device		a pointer to be filled with the device.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_initializeDeviceFromConfig(IN SkIisuHandle_C handle, IN SkApplicationConfigurator_C configurator, OUT SkDevice_C* device);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getVersion(IN SkIisuHandle_C handle,
 * 		OUT SkString_C version);
 *
 * \brief	Get the running iisu version.
 *
 * \param	handle 	The handle.
 * \param	[out]	version. The string to be filled with the version.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getVersion(IN SkIisuHandle_C handle, OUT SkString_C version);


/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getCommandManager(IN SkIisuHandle_C handle,
 * 		OUT SkCommandManager_C* commandManager);
 *
 * \brief	Get hold of the command manager.
 *
 * \param	handle				  	The handle.
 * \param [out]	commandManager		a pointer to be filled with the command manager.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getCommandManager(IN SkIisuHandle_C handle, OUT SkCommandManager_C* commandManager);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getEventManager(IN SkIisuHandle_C handle,
 * 		OUT SkEventManager_C* eventManager);
 *
 * \brief	Get hold of the event manager.
 *
 * \param	handle					The handle.
 * \param [in,out]	eventManager	a pointer to be filled with the event manager.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getEventManager(IN SkIisuHandle_C handle, OUT SkEventManager_C* eventManager);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_shareHandle(IN SkIisuHandle_C handle,
 * 		OUT SkIisuHandle_C* sharedHandle);
 *
 * \brief	Creates a shared handle that allows several application to work on the same iisu engine
 *
 * \param	handle					The source handle.
 * \param [out]	sharedHandle	a pointer to be filled with the shared handle.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_shareHandle(IN SkIisuHandle_C handle, OUT SkIisuHandle_C* sharedHandle);
// Device
// config

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_setConfigString(IN SkIisuHandle_C handle,
 * 		IN SkString_C xpath, IN SkString_C value, IN bool updateConfigFile);
 *
 * \brief	sets the value of a configuration value through it's xpath (see the iisu configuration file)
 *
 * \param	handle				The handle.
 * \param	xpath				The xpath of the configuration value to change.
 * \param	value				The value.
 * \param	updateConfigFile	a boolean stating if the value change has to be reported to the iisu config file.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_setConfigString(IN SkIisuHandle_C handle, IN SkString_C xpath, IN SkString_C value, IN bool updateConfigFile);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getConfigString(IN SkIisuHandle_C handle,
 * 		IN SkString_C xpath, OUT SkString_C value);
 *
 * \brief	Gets the value of a configuration value, accessed through a xpath
 *
 * \param	handle	The handle.
 * \param	xpath 	The xpath.
 * \param [out]	value 	The returned value.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getConfigString(IN SkIisuHandle_C handle, IN SkString_C xpath, OUT SkString_C value);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getConfigPathCount(IN SkIisuHandle_C handle,
 * 		OUT int32_t* count);
 *
 * \brief	Gets the number of configuration path currently defined (loaded from the iisu configuration file).
 *
 * \param	handle		 	The handle.
 * \param [out]	count	The returned number of configuration files
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getConfigPathCount(IN SkIisuHandle_C handle, OUT int32_t* count);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getConfigPath(IN SkIisuHandle_C handle,
 * 		IN int32_t index, OUT SkString_C path);
 *
 * \brief	Get the xpath of the indexth configuration value.
 *
 * \param	handle	The handle.
 * \param	index 	Zero-based index of the path.
 * \param	path [out] 	The string of the value's xpath.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getConfigPath(IN SkIisuHandle_C handle, IN int32_t index, OUT SkString_C path);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_saveConfigFile(IN SkIisuHandle_C handle);
 *
 * \brief	Save the configuration file, including any changes that might have been done through iisuHandle_setConfigString specifying updateConfigFile=true ;
 *
 * \param	handle	The handle.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_saveConfigFile(IN SkIisuHandle_C handle);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_isDeviceInitialized(IN SkIisuHandle_C handle,
 * 		OUT SkBool* status);
 *
 * \brief	Returns if the handle has a correctly intialised device
 *
 * \param	handle		  	The handle.
 * \param [out]	status	a pointer to a boolean receiving true or false
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_isDeviceInitialized(IN SkIisuHandle_C handle, OUT SkBool* status);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getDevice(IN SkIisuHandle_C handle,
 * 		OUT SkDevice_C* device);
 *
 * \brief	Gets the device associated to a handle
 *
 * \param	handle		  	The handle.
 * \param [out]	device	a pointer to be filled with the device
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL iisuHandle_getDevice(IN SkIisuHandle_C handle, OUT SkDevice_C* device);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getCommandManager(IN SkDevice_C device,
 * 		OUT SkCommandManager_C* commandManager);
 *
 * \brief	Get the command manager from a device.
 *
 * \param	device				  	The device.
 * \param [out]	commandManager	a pointer to be filled with the command manager.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getCommandManager(IN SkDevice_C device, OUT SkCommandManager_C* commandManager);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getEventManager(IN SkDevice_C device,
 * 		OUT SkEventManager_C* eventManager);
 *
 * \brief	Get the event manager from a device
 *
 * \param	device					The device.
 * \param [out]	eventManager	a pointer to be filled with the command manager.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getEventManager(IN SkDevice_C device, OUT SkEventManager_C* eventManager);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_start(IN SkDevice_C device);
 *
 * \brief	Start the device and iisu processing
 *
 * \param	device	The device.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_start(IN SkDevice_C device);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_stop(IN SkDevice_C device,
 * 		IN SkBool waitForStopped);
 *
 * \brief	Sk device stop.
 *
 * \param	device		  	The device.
 * \param	waitForStopped	The wait for stopped.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_stop(IN SkDevice_C device, IN SkBool waitForStopped);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getStatus(IN SkDevice_C device,
 * 		OUT int32_t* status);
 *
 * \brief	Gets the status of the device.
 *
 * \param	device		  	The device.
 * \param [out]	status	The status bit set of the device.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getStatus(IN SkDevice_C device, OUT int32_t* status);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getFrameId(IN SkDevice_C device,
 * 		OUT int32_t* frameID);
 *
 * \brief	Gets the current frame ID.
 *
 * \param	device		   	The device.
 * \param [out]	the frame ID of the current data set.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getFrameId(IN SkDevice_C device, OUT int32_t* frameID);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_updateFrame(IN SkDevice_C device,
 * 		IN SkBool waitForNewFrame);
 *
 * \brief	Updates the data set computed from iisu.
 *
 * \param	device		   	The device.
 * \param	waitForNewFrame	Tells if the update process should wait for a new frame to complete or not.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_updateFrame(IN SkDevice_C device, IN SkBool waitForNewFrame);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_lockFrame(IN SkDevice_C device);
 *
 * \brief	Lock the frame currently held by the device. No SkDevice_updateFrame will be possible until
 * 			the dataframe has been unlocked
 *
 * \param	device	The device.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_lockFrame(IN SkDevice_C device);


/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_releaseFrame(IN SkDevice_C device);
 *
 * \brief	Release the data set allowing the update frame to be processed if called
 *
 * \param	device	The device.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_releaseFrame(IN SkDevice_C device);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataFrame(IN SkDevice_C device,
 * 		OUT SkDataFrame_C* dataFrame );
 *
 * \brief	Gets the current data frame.
 *
 * \param	device			 	The device.
 * \param [out]	dataFrame	The current data frame
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataFrame(IN SkDevice_C device, OUT SkDataFrame_C* dataFrame );

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_registerData(IN SkDevice_C device,
 * 		IN SkString_C path, IN SkTypeInfo_C type, OUT int32_t* dataID);
 *
 * \brief	Register a data to be accessed.
 *
 * \param	device		  	The device.
 * \param	path		  	The path to the iisu data.
 * \param	type		  	The type ID of the data.
 * \param [out]	dataID	The ID of the data, used later to get it's value.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_registerData(IN SkDevice_C device, IN SkString_C path, IN SkTypeInfo_C type, OUT int32_t* dataID);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_unregisterData(IN SkDevice_C device,
 * 		IN int32_t dataID);
 *
 * \brief	Unregister a data so it's not updated anymore.
 *
 * \param	device	The device.
 * \param	dataID	Identifier for the data.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_unregisterData(IN SkDevice_C device, IN int32_t dataID);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_setDataAutoUpdateFlag(IN SkDevice_C device,
 * 		IN int32_t dataID, IN bool autoUpdate);
 *
 * \brief	Tells whether the data needs to be updated at every frame or not.
 *
 * \param	device	  	The device.
 * \param	dataID	  	The data ID
 * \param	autoUpdate	set to true to get the data updated at every frame and false to freeze the data update.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_setDataAutoUpdateFlag(IN SkDevice_C device, IN int32_t dataID, IN bool autoUpdate);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_isDataAutoUpdated(IN SkDevice_C device,
 * 		IN int32_t dataID, OUT SkBool* isAutoUpdated);
 *
 * \brief	Says if the data is automatically updated at every frame or not.
 *
 * \param	device				 	The device.
 * \param	dataID				 	Identifier for the data.
 * \param [in,out]	isAutoUpdated	the update flag of the data.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_isDataAutoUpdated(IN SkDevice_C device, IN int32_t dataID, OUT SkBool* isAutoUpdated);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getData(IN SkDevice_C device,
 * 		IN int32_t dataID, IN SkTypeInfo_C type, OUT void** data);
 *
 * \brief	Gets the data value.
 *
 * \param	device			The device.
 * \param	dataID			Identifier for the data.
 * \param	type			The data type ID.
 * \param [out]	data	A buffer pointer that will hold the data in binary form.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getData(IN SkDevice_C device, IN int32_t dataID, IN SkTypeInfo_C type, OUT void** data);
IISUSDK_API SkError_C SK_SDK_CDECL SkDevice_getMetaInfoType(IN SkDevice_C device, IN SkString_C path, OUT SkTypeInfo_C* type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataCount(IN SkDevice_C device,
 * 		IN SkBool onlyRegisteredData, OUT int32_t* count);
 *
 * \brief	Returns the number of data currently available from iisu.
 *
 * \param	device			  	The device.
 * \param	onlyRegisteredData	If true, returns only the currently registered data, otherwise, retruns all data available
 * \param [out]	count	  	the number of data available.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataCount(IN SkDevice_C device, IN SkBool onlyRegisteredData, OUT int32_t* count);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataName(IN SkDevice_C device,
 * 		IN int32_t i, IN SkBool onlyRegisteredData, OUT SkString_C name);
 *
 * \brief	returns the name (path) of the index based data available in iisu
 *
 * \param	device			  	The device.
 * \param	i				  	Zero-based index of the data .
 * \param	onlyRegisteredData	if true, considers only the already registered datas
 * \param	name			  	The path of the data.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataName(IN SkDevice_C device, IN int32_t i, IN SkBool onlyRegisteredData, OUT SkString_C name);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataType(IN SkDevice_C device,
 * 		IN SkString_C path, OUT SkTypeInfo_C* type);
 *
 * \brief	returns the type of a data.
 *
 * \param	device			The device.
 * \param	path			the iisu path of the data.
 * \param [out]	type	a structure describing the type of the data
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getDataType(IN SkDevice_C device, IN SkString_C path, OUT SkTypeInfo_C* type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_registerParameter(IN SkDevice_C device,
 * 		IN SkString_C path, IN SkTypeInfo_C typeInfo, OUT int32_t* paramID);
 *
 * \brief	Registers a parameter.
 *
 * \param	device		   	The device.
 * \param	path			The iisu path of the parameter
 * \param	typeInfo	   	The parameter type ID.
 * \param [out]		paramID	The parameter ID.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_registerParameter(IN SkDevice_C device, IN SkString_C path, IN SkTypeInfo_C typeInfo, OUT int32_t* paramID);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_unregisterParameter(IN SkDevice_C device,
 * 		IN int32_t dataID);
 *
 * \brief	Unregister a parameter so it's not updated anymore.
 *
 * \param	device	The device.
 * \param	paramID	Identifier for the parameter.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_unregisterParameter(IN SkDevice_C device, IN int32_t paramID);


/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameter(IN SkDevice_C device,
 * 		IN int32_t paramID, IN SkTypeInfo_C type, OUT void* parameterReturned);
 *
 * \brief	Gets the value of a parameter
 *
 * \param	device					 	The device.
 * \param	paramID					 	Identifier for the parameter.
 * \param	type					 	The parameter type ID.
 * \param [in,out]	parameterReturned		A buffer to be filled with the parameer's binary value. Should be pre-allocated to fit the data size.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameter(IN SkDevice_C device, IN int32_t paramID, IN SkTypeInfo_C type, OUT void* parameterReturned);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_setParameter(IN SkDevice_C device,
 * 		IN int32_t paramID, IN const void* dataSent, IN SkTypeInfo_C type);
 *
 * \brief	Sets a parameter value
 *
 * \param	device  	The device.
 * \param	paramID 	The parameter ID
 * \param	dataSent	A binary buffer containing the parameter value.
 * \param	type		The type ID of the parameter.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_setParameter(IN SkDevice_C device, IN int32_t paramID, IN const void* dataSent, IN SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameterCount(IN SkDevice_C device,
 * 		OUT int32_t* count);
 *
 * \brief	Returns the number of parameters available.
 *
 * \param	device		 	The device.
 * \param [out]	count	The number of parameters available
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameterCount(IN SkDevice_C device, OUT int32_t* count);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameterName(IN SkDevice_C device,
 * 		IN uint32_t index, OUT SkString_C name);
 *
 * \brief	Gets the name (path) of the index-based i th parameter.
 *
 * \param	device	The device.
 * \param	index 	Zero-based index of the parameter.
 * \param	name [out]	The path of the parameter.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameterName(IN SkDevice_C device, IN uint32_t index, OUT SkString_C name);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameterType(IN SkDevice_C device,
 * 		IN SkString_C path, OUT SkTypeInfo_C* type);
 *
 * \brief	Returns the type of the parameter.
 *
 * \param	device			The device.
 * \param	path			Full pathname of the file.
 * \param [out]	type	A struct describing the type of the parameter
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameterType(IN SkDevice_C device, IN SkString_C path, OUT SkTypeInfo_C* type);

//meta info

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getMetaInfo(IN SkDevice_C device,
 * 		IN SkString_C dataPath, OUT SkMetaInfo_C* metainfo);
 *
 * \brief	Gets meta information about a data or parameter.
 *
 * \param	device				The device.
 * \param	dataPath			The iisu path of the data/parameter.
 * \param [out]	metainfo	A pointer to a meta info struct
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getMetaInfo(IN SkDevice_C device, IN SkString_C dataPath, OUT SkMetaInfo_C* metainfo);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getAttributes(IN SkDevice_C device,
 * 		IN SkString_C dataPath, OUT SkAttributes* attributes);
 *
 * \brief	Sk device get the attribute of a data or parameter .
 *
 * \param	device			  	The device.
 * \param	dataPath			The iisu path of the data/parameter.
 * \param [out]	attributes	A pointer to an attribute field.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getAttributes(IN SkDevice_C device, IN SkString_C dataPath, OUT SkAttributes* attributes);


/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_isValid(IN SkDataFrame_C dataFrame,
 * 		IN int32_t dataID, OUT SkBool* isValid );
 *
 * \brief	Returns if a data is valid
 *
 * \param	dataFrame	   	The data frame.
 * \param	dataID		   	Identifier for the data.
 * \param [out]	isValid	a boolean specifying if the data is valid
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_isValid(IN SkDataFrame_C dataFrame, IN int32_t dataID, OUT SkBool* isValid );

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_lock(IN SkDataFrame_C dataFrame );
 *
 * \brief	Locks the dataframe so it can't be updated (until SkDataFrame_unlock is called).
 *
 * \param	dataFrame	The data frame.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_lock(IN SkDataFrame_C dataFrame );

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_unlock(IN SkDataFrame_C dataFrame );
 *
 * \brief	Unlocks the dataframe.
 *
 * \param	dataFrame	The data frame.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_unlock(IN SkDataFrame_C dataFrame );

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_getFrameID(IN SkDataFrame_C dataFrame,
 * 		OUT int32_t* frameID );
 *
 * \brief	Sk data frame get frame identifier.
 *
 * \param	dataFrame	   	The data frame.
 * \param [out]	the frameID of the dataframe
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_getFrameID(IN SkDataFrame_C dataFrame, OUT int32_t* frameID );

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_get(IN SkDataFrame_C dataFrame,
 * 		IN int32_t dataID, IN SkTypeInfo_C type, OUT void** data);
 *
 * \brief	Retrieves a data value directly from the data frame object
 *
 * \param	dataFrame   	The data frame.
 * \param	dataID			Identifier for the data.
 * \param	type			The type.
 * \param [in,out]	data	If non-null, the data.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_get(IN SkDataFrame_C dataFrame, IN int32_t dataID, IN SkTypeInfo_C type, OUT void** data);

IISUSDK_API SkError_C SK_SDK_DECL SkDataFrame_getAll(IN SkDataFrame_C dataFrame, OUT void** allData);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getCommandCount(IN SkCommandManager_C manager,
 * 		OUT int32_t* count);
 *
 * \brief	Gets the number of commands registered .
 *
 * \param	manager		 	The command manager.
 * \param [out]	count	The number of registered command.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getCommandCount(IN SkCommandManager_C manager, OUT int32_t* count);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getCommandName(IN SkCommandManager_C manager,
 * 		IN uint32_t index, OUT SkString_C name);
 *
 * \brief	Gets the name (path) of the index-th command registered
 *
 * \param	manager	The command manager.
 * \param	index  	Zero-based index of the command.
 * \param	name   	The command name.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getCommandName(IN SkCommandManager_C manager, IN uint32_t index, OUT SkString_C name);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getCommandType(IN SkCommandManager_C manager,
 * 		IN SkString_C path, OUT SkFunctionTypeInfo_C* type);
 *
 * \brief	Gets the type of the command whose name/path is given.
 *
 * \param	manager			The command manager.
 * \param	path			The path of the command.
 * \param [out]	type	The type of the function.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getCommandType(IN SkCommandManager_C manager, IN SkString_C path, OUT SkFunctionTypeInfo_C* type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getMetaInfoType(IN SkCommandManager_C manager,
 * 		IN SkString_C path, OUT SkTypeInfo_C* type);
 *
 * \brief	Gets the typeinfo of the metainfo associated to a command
 *
 * \param	manager			The manager.
 * \param	path			The path of the command
 * \param [out]	type	The command's metainfo type.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getMetaInfoType(IN SkCommandManager_C manager, IN SkString_C path, OUT SkTypeInfo_C* type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_sendCommand(IN SkCommandManager_C manager,
 * 		IN SkString_C sCmd, IN SkFunctionTypeInfo_C type, IN SkBool dropReturn,
 * 		OUT uint64_t* commandCallerID, IN ...);
 *
 * \brief	Invokes a command
 *
 * \param	manager				   	The command manager.
 * \param	sCmd				   	The command path.
 * \param	type				   	The function type.
 * \param	dropReturn			   	a boolean specifying if we should drop the return value (if true) or keep it for later retrieval by \sa SkCommandManager_waitForReturnValue.
 * \param [out]	commandCallerID	the commandID. To be used later to retrieve the return value
 * \param	params					The parameters for the commands in order
 *
 * \return	a SkError_C specifying if the call was successful or not
 */
IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_sendCommand(IN SkCommandManager_C manager, IN SkString_C sCmd, IN SkFunctionTypeInfo_C type, IN void** params, IN SkBool dropReturn, OUT uint64_t* commandCallerID); 

//IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_sendCommand(IN SkCommandManager_C manager, IN SkString_C sCmd, IN SkFunctionTypeInfo_C type, IN SkBool dropReturn, OUT uint64_t* commandCallerID, IN ...); 

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_waitForReturnValue(IN SkCommandManager_C manager,
 * 		IN SkTypeInfo_C type, INOUT uint64_t* commandCallerID, OUT void* returnValue);
 *
 * \brief	Try to get the return value for the command with the specified calledID.
 *
 * \param	manager				   	The command manager.
 * \param	type				   	The type of the return value expected.
 * \param [in,out]	commandCallerID	the command ID of the command we're trying to get the return value of. If the call was successful, will be set to zero
 * \param [out]	returnValue	   	A buffer to hold the return value. Must be pre-allocated so that it is ready to hold the value.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_waitForReturnValue(IN SkCommandManager_C manager, IN SkTypeInfo_C type, INOUT uint64_t* commandCallerID, OUT void* returnValue);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_waitForReturnValueTimed(IN SkCommandManager_C manager,
 * 		IN SkTypeInfo_C type, IN int32_t timeout, INOUT uint64_t* commandCallerID,
 * 		OUT void* returnValue);
 *
 * \brief	Try to get the return value for the command with the specified calledID but returns if it isn't available before the specified time
 *
 * \param	manager				   	The command manager.
 * \param	type				   	The type of the return value expected.
 * \param	timeout				   	The timeout (in milliseconds).
 * \param [in,out]	commandCallerID	The id of the command. will be set to zero if the call returned the value.
 * \param [in,out]	returnValue	   	A buffer to hold the return value. Must be pre-allocated so that it is ready to hold the value.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_waitForReturnValueTimed(IN SkCommandManager_C manager, IN SkTypeInfo_C type, IN int32_t timeout, INOUT uint64_t* commandCallerID, OUT void* returnValue);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_isReturnValueReady(IN SkCommandManager_C manager,
 * 		IN uint64_t commandCallerID, OUT SkBool* isReady);
 *
 * \brief	asks the command manager if the return value for the specified command is already available.
 *
 * \param	manager		   	The command manager.
 * \param	commandCallerID	The id of the command. will be set to zero if the call returned the value.
 * \param [out]	a boolean specifying if the command is ready or not
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_isReturnValueReady(IN SkCommandManager_C manager, IN uint64_t commandCallerID, OUT SkBool* isReady);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_tryGetReturnValue(IN SkCommandManager_C manager,
 * 		IN SkTypeInfo_C type, INOUT uint64_t* commandCallerID, OUT void* returnValue);
 *
 * \brief	Try getting the return value for the specified command but bails out directly if 
 *
 * \param	manager				   	The manager.
 * \param	type				   	The type of the return value expected.
 * \param [in,out]	commandCallerID	The id of the command. will be set to zero if the call returned the value.
 * \param [in,out]	returnValue	   	A buffer to hold the return value. Must be pre-allocated so that it is ready to hold the value.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_tryGetReturnValue(IN SkCommandManager_C manager, IN SkTypeInfo_C type, INOUT uint64_t* commandCallerID, OUT void* returnValue);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getMetaInfo(IN SkCommandManager_C manager,
 * 		IN SkString_C commandName, OUT SkMetaInfo_C* metainfo);
 *
 * \brief	Gets the meta information for a command.
 *
 * \param	manager				The command manager.
 * \param	commandName			Name/path of the command.
 * \param [out]	metainfo	A pointer to a MetaInfo struct to be filled.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getMetaInfo(IN SkCommandManager_C manager, IN SkString_C commandName, OUT SkMetaInfo_C* metainfo); 

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getAttributes(IN SkCommandManager_C manager,
 * 		IN SkString_C commandName, OUT SkAttributes* attributes);
 *
 * \brief	Gets the attributes for the specified command.
 *
 * \param	manager				The command manager.
 * \param	commandName			Name/path of the command.
 * \param [out]	attributes	A pointer to an attribute bitfield.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getAttributes(IN SkCommandManager_C manager, IN SkString_C commandName, OUT SkAttributes* attributes); 

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getEventCount(IN SkEventManager_C manager,
 * 		OUT int32_t* count);
 *
 * \brief	Returns the number of event available
 *
 * \param	manager		 	The event manager.
 * \param [out]	count	the number of event available.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getEventCount(IN SkEventManager_C manager, OUT int32_t* count);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getEventName(IN SkEventManager_C manager,
 * 		IN uint32_t index, OUT SkString_C name);
 *
 * \brief	returns the name/path of the zero-based index-th command
 *
 * \param	manager	The event manager.
 * \param	index  	Zero-based index of the command.
 * \param	name   	The name of the command.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getEventName(IN SkEventManager_C manager, IN uint32_t index, OUT SkString_C name);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getEventType(IN SkEventManager_C manager,
 * 		IN SkString_C name, OUT SkFunctionTypeInfo_C* type);
 *
 * \brief	Gets the type of the specified event
 *
 * \param	manager			The event manager.
 * \param	name			The name of the event.
 * \param [out]	type	The type of the event.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getEventType(IN SkEventManager_C manager, IN SkString_C name, OUT SkFunctionTypeInfo_C* type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getMetaInfoType(IN SkEventManager_C manager,
 * 		IN SkString_C name, OUT SkTypeInfo_C* type);
 *
 * \brief	Returns the type of the event's meta info.
 *
 * \param	manager			The event manager.
 * \param	name			The name of the event.
 * \param [out]	type	The type of the event's meta info.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getMetaInfoType(IN SkEventManager_C manager, IN SkString_C name, OUT SkTypeInfo_C* type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getMetaInfo(IN SkEventManager_C manager,
 * 		IN SkString_C eventName, OUT SkMetaInfo_C* metainfo);
 *
 * \brief	Gets the meta info of the event.
 *
 * \param	manager				The event manager.
 * \param	eventName			Name of the event.
 * \param [out]	metainfo	A pointer to a MetaInfo struct to be filled.
 *
 * \return	a SkError_C specifying if the call was successful or not
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getMetaInfo(IN SkEventManager_C manager, IN SkString_C eventName, OUT SkMetaInfo_C* metainfo);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getAttributes(IN SkEventManager_C manager,
 * 		IN SkString_C eventName, OUT SkAttributes* attributes);
 *
 * \brief	Get the attributes of an event.
 *
 * \param	manager			  	The event manager.
 * \param	eventName		  	Name of the event.
 * \param [in,out]	attributes	a pointer to an attribute bitfield
 *
 * \return	a SkError_C specifying if the call was successful or not.
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getAttributes(IN SkEventManager_C manager, IN SkString_C eventName, OUT SkAttributes* attributes);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_registerCDeclEventListener(IN SkEventManager_C manager,
 * 		IN SkString_C eventName, IN SkEventListenerCDeclFunction_C function,
 * 		IN SkFunctionTypeInfo_C type);
 *
 * \brief	Register a cdecl event listener.
 *
 * \param	manager  	The event manager.
 * \param	eventName	Name of the event.
 * \param	function 	The cdecl function.
 * \param	type	 	The function type.
 *
 * \return	a SkError_C specifying if the call was successful or not.
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_registerCDeclEventListener(IN SkEventManager_C manager, IN SkString_C eventName, IN SkEventListenerCDeclFunction_C function, IN SkFunctionTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_unregisterCDeclEventListener(IN SkEventManager_C manager,
 * 		IN SkString_C eventName, IN SkEventListenerCDeclFunction_C function,
 * 		IN SkFunctionTypeInfo_C type);
 *
 * \brief	Unregister cdecl event listener.
 *
 * \param	manager  	The event manager.
 * \param	eventName	Name of the event.
 * \param	function 	The cdecl function.
 * \param	type	 	The function type.
 *
 * \return	a SkError_C specifying if the call was successful or not.
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_unregisterCDeclEventListener(IN SkEventManager_C manager, IN SkString_C eventName, IN SkEventListenerCDeclFunction_C function, IN SkFunctionTypeInfo_C type);

#ifdef WIN32

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_registerStdCallEventListener(IN SkEventManager_C manager,
 * 		IN SkString_C eventName, IN SkEventListenerStdCallFunction_C function,
 * 		IN SkFunctionTypeInfo_C type);
 *
 * \brief	Register a stdcall event listener.
 *
 * \param	manager  	The event manager.
 * \param	eventName	Name of the event.
 * \param	function 	The stdcall function.
 * \param	type	 	The function type.
 *
 * \return	a SkError_C specifying if the call was successful or not.
 * \warning Windows only
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_registerStdCallEventListener(IN SkEventManager_C manager, IN SkString_C eventName, IN SkEventListenerStdCallFunction_C function, IN SkFunctionTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_unregisterStdCallEventListener(IN SkEventManager_C manager,
 * 		IN SkString_C eventName, IN SkEventListenerStdCallFunction_C function,
 * 		IN SkFunctionTypeInfo_C type);
 *
 * \brief	Unregister a stdcall event listener.
 *
 * \param	manager  	The event manager.
 * \param	eventName	Name of the event.
 * \param	function 	The stdcall function.
 * \param	type	 	The function type.
 *
 * \return	a SkError_C specifying if the call was successful or not.
 * \warning Windows only
 */

IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_unregisterStdCallEventListener(IN SkEventManager_C manager, IN SkString_C eventName, IN SkEventListenerStdCallFunction_C function, IN SkFunctionTypeInfo_C type);
#endif

} // extern C

#endif // IISU_SDK_API_H
