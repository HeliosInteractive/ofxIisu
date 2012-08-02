#pragma once

#include <Iisu/Devices/Device.h>
#include <Framework/Errors/Return.h>
#include <Platform/SkPlatform.h>

namespace SK
{
	class ApplicationConfigurator ;  

	/**
	 * \class	IisuHandle
	 *
	 * \brief	Iisu handle reprensenting the connection to either a local or a remote iisu. 
	 */

	class IisuHandle
	{
	public:

		/**
		 * \struct	Configuration
		 *
		 * \brief	Iisu Handle Configuration structure. 
		 */

		struct Configuration
		{
			///< true if we want to run local instance of iisu. False if we connect to a remote iisu
			bool isLocal;
			///< The ip of the remote iisu we connect to
			SK::String remoteIP ;
			///< The port of the remote iisu we connect to
			uint16_t remotePort ;

			///< Filename of the iisu configuration file
			SK::String configFileName ;
			///< The iisu bin dir where the dll is going to be loaded from
			SK::String iisuBinDir ;
			///< Allows to load a specifi parameter setting file
			SK::String paramSettingFile ;
			///< List of comma-separated list of layers to load
			SK::String layersToLoad;
			///< true to log to stdout
			bool logToStdout ;
			///< Specify where to the log should be written to
			SK::String logFileName ;

			/**
			 * \fn	Configuration()
			 *
			 * \brief	Default empty constructor.
			 */

			Configuration() {} 

			/**
			 * \fn	IisuHandle::Configuration(SK::String p_ip,uint16_t p_port)
			 *
			 * \brief	Constructor for using iisu in remote.
			 *
			 * \param	p_ip  	The ip.
			 * \param	p_port	The port.
			 */

			Configuration(SK::String p_ip,uint16_t p_port)
			:isLocal(false)
			,remotePort(p_port)
			,remoteIP(p_ip)
			{
			}



			/**
			 * \fn	IisuHandle::Configuration(SK::String p_iisuBinDir,
			 * 		SK::String p_configFileName="iisu_config.xml",
			 * 		SK::String p_paramSettingsFile="param_settings.xml", SK::String p_layersToLoad="",
			 * 		bool p_logToStdout = true,SK::String p_logFileName ="")
			 *
			 * \brief	Constructor for using iisu in local.
			 *
			 * \param	p_iisuBinDir	   	The iisu bin dir where the dll has to be loaded from.
			 * \param	p_configFileName   	(optional) the name of the configuration file.
			 * \param	p_paramSettingsFile	(optional) the parameter settings file.
			 * \param	p_layersToLoad	   	(optional) the layers to load.
			 * \param	p_logToStdout	   	(optional) log to stdout.
			 * \param	p_logFileName	   	(optional) filename of the log file.
			 */

			Configuration(SK::String p_iisuBinDir,SK::String p_configFileName="iisu_config.xml",SK::String p_paramSettingsFile="param_settings.xml", SK::String p_layersToLoad="",bool  p_logToStdout = true,SK::String p_logFileName ="")
			:isLocal(true)
			,iisuBinDir(p_iisuBinDir)
			,configFileName(p_configFileName)
			,paramSettingFile(p_paramSettingsFile)
			,layersToLoad(p_layersToLoad)
			,logToStdout(p_logToStdout)
			,logFileName(p_logFileName)
			{
			}
		};

	protected:

		/**
		 * \fn	IisuHandle::IisuHandle()
		 *
		 * \brief	Default constructor.
		 */

		IisuHandle() {};

	public:

		/**
		 * \fn	virtual IisuHandle::~IisuHandle()
		 *
		 * \brief	Destructor.
		 */

		virtual ~IisuHandle() {};

		/**
		 * \fn	virtual SK::Return<SK::Device *> IisuHandle::initializeDevice(SK::Device::Configuration &) =0;
		 *
		 * \brief	Initializes a new device from a Device::Configuration.
		 *
		 * \param 	A device configuration structure.
		 *
		 * \return	A return object containing the device pointer if the call succeeded.
		 */

		virtual SK::Return<SK::Device *> initializeDevice(const SK::Device::Configuration &) =0;

		/**
		 * \fn	virtual SK::Return<SK::Device *> IisuHandle::initializeDevice(const SK::ApplicationConfigurator &) =0;
		 *
		 * \brief	Initializes the device from an Application configurator.
		 *
		 * \param	An application configurator.
		 *
		 * \return	A return object containing the device pointer if the call succeeded.
		 */

		virtual SK::Return<SK::Device *> initializeDevice(const SK::ApplicationConfigurator &) =0 ;

		/**
		 * \fn	virtual bool IisuHandle::isDeviceInitialized() =0;
		 *
		 * \brief	Query if the device associated to this handle is properly initialized.
		 *
		 * \return	true if device is initialized, false if not.
		 */

		virtual bool isDeviceInitialized() =0 ;

		/**
		 * \fn	virtual SK::Return<SK::Device*> IisuHandle::getDevice() = 0;
		 *
		 * \brief	Gets the device associated with the handle.
		 *
		 * \return	A return object containing the device pointer if present.
		 */

		virtual SK::Return<SK::Device*> getDevice() = 0 ;

		/**
		 * \fn	virtual SK::Return<SK::String> IisuHandle::getVersion()const=0;
		 *
		 * \brief	Gets the version of the iisu engine running.
		 *
		 * \return	The iisu version.
		 */

		virtual SK::Return<SK::String> getVersion()const=0;

		/**
		 * \fn	virtual SK::CommandManager IisuHandle::&getCommandManager() = 0;
		 *
		 * \brief	Gets the command manager.
		 *
		 * \return	The command manager.
		 */

		virtual SK::CommandManager &getCommandManager() = 0 ;

		/**
		 * \fn	virtual SK::EventManager IisuHandle::&getEventManager() = 0;
		 *
		 * \brief	Gets the event manager.
		 *
		 * \return	The event manager.
		 */

		virtual SK::EventManager &getEventManager() = 0 ;

		/**
		 * \fn	virtual SK::Result IisuHandle::setConfigString(const SK::String &xpath,
		 * 		const SK::String &value,bool copyToConfigFile = false)=0;
		 *
		 * \brief	Sets a configuration string (internal equivalent of the values stored in the iisu configuration file)
		 *
		 * \param	xpath				The xpath of the configuration item to change.
		 * \param	value				Its value.
		 * \param	copyToConfigFile	(optional) the copy the value to configuration file (you need to explicitely call saveConfigFile() to commit the changes to the actual file).
		 *
		 * \return	.
		 */

		virtual SK::Result setConfigString(const SK::String &xpath,const SK::String &value,bool copyToConfigFile = false)=0 ;

		/**
		 * \fn	virtual SK::Return<SK::String> IisuHandle::getConfigString(const SK::String &xpath)=0;
		 *
		 * \brief	Gets a configuration string.
		 *
		 * \param	xpath	The xpath of the configuration item.
		 *
		 * \return	The configuration string.
		 */

		virtual SK::Return<SK::String> getConfigString(const SK::String &xpath)=0 ;

		/**
		 * \fn	virtual SK::Return<int> IisuHandle::getConfigPathCount()=0;
		 *
		 * \brief	Gets how many xpath are contained in the current configuration
		 *
		 * \return	The configuration path count.
		 */

		virtual SK::Return<int> getConfigPathCount()=0 ;

		/**
		 * \fn	virtual SK::Return<SK::String> IisuHandle::getConfigPath(int index)=0;
		 *
		 * \brief	Gets the configuration path of an item.
		 *
		 * \param	index	Zero-based index of the configuration item.
		 *
		 * \return	The configuration path.
		 */

		virtual SK::Return<SK::String> getConfigPath(int index)=0 ;

		/**
		 * \fn	virtual SK::Result IisuHandle::saveConfigFile()=0;
		 *
		 * \brief	Saves the state of the configuration file.
		 *
		 * \return	.
		 */

		virtual SK::Result saveConfigFile()=0 ;
		virtual SK::IisuHandle* shareHandle()=0;
	};
}
