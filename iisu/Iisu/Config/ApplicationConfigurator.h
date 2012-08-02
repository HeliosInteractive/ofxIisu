#pragma once

#include <Iisu/Handles/IisuHandle.h>
#include <Iisu/Devices/Device.h>


namespace SK {
	class ConfigFile ;

	/**
	 * \class	ApplicationConfigurator
	 *
	 * \brief	Helper class to construct the IisuHandle::Configuration and Device::Configuration from an xml file. 
	 */

	class IISUSDK_API ApplicationConfigurator {
	public:

		/**
		 * \fn	static SK::Return<ApplicationConfigurator>create(const char *configurationFile);
		 *
		 * \brief	Creates an application configurator by parsing the configuration file.
		 *
		 * \param	configurationFile	The configuration file path.
		 */

		static SK::Return<ApplicationConfigurator>create(const char *configurationFile) ;

		/**
		 * \fn	ApplicationConfigurator::~ApplicationConfigurator();
		 *
		 * \brief	Destructor.
		 */

		~ApplicationConfigurator() ;
	private:
		ApplicationConfigurator() ;
	public:

		/**
		 * \fn	SK::Return<SK::IisuHandle::Configuration> ApplicationConfigurator::getHandleConfiguration() const;
		 *
		 * \brief	Gets the handle configuration structure filled with the data from the configuration file.
		 *
		 * \return	The handle configuration, if successful.
		 */

		SK::Return<SK::IisuHandle::Configuration> getHandleConfiguration() const ;

		/**
		 * \fn	SK::Return<SK::Device::Configuration> ApplicationConfigurator::getDeviceConfiguration() const;
		 *
		 * \brief	Gets the device configuration structure filled with the data from the configuration file.
		 *
		 * \return	The device configuration, if successful.
		 */

		SK::Return<SK::Device::Configuration> getDeviceConfiguration() const ;
	private:
		SK::ConfigFile *m_configFile ;
	} ;
}