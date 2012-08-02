#pragma once

#include <Framework/Instances/Singleton.h>
#include <Framework/Instances/SharedPtr.h>
#include <Framework/Errors/Return.h>
#include <Iisu/Config/ApplicationConfigurator.h>
#include <Iisu/Handles/IisuHandle.h>
#include <Iisu/Devices/Device.h>

#include <iostream>
#include <sstream>


namespace SK
{
	class ContextImpl;

	/**
	 * \class	Context class.
	 *
	 * \brief	Context. 
	 */

	class IISUSDK_API Context
	{
	public:

		/**
		 * \fn	static Context& Context::Instance();
		 *
		 * \brief	Gets the context instance.
		 *
		 * \return	the context instance
		 */

		static Context& Instance();
	private:
		Context();
		~Context();
	public:

		/**
		 * \fn	SK::Return<SK::IisuHandle *> Context::createHandle(const SK::IisuHandle::Configuration& config);
		 *
		 * \brief	Creates a handle using the parameters defined in the given configuration structure.
		 *
		 * \param	config	The configuration structure.
		 *
		 * \return	a pointer to the created handle, if successful
		 */

		SK::Return<SK::IisuHandle *>  createHandle(const SK::IisuHandle::Configuration& config);

		/**
		 * \fn	SK::Return<SK::IisuHandle *> Context::createHandle(const SK::ApplicationConfigurator& configurator);
		 *
		 * \brief	Creates a handle using the parameters defined in the given configuration structure.
		 *
		 * \param	configurator	A reference to an application configurator.
		 *
		 * \return	a pointer to the created handle, if successful.
		 */

		SK::Return<SK::IisuHandle *>  createHandle(const SK::ApplicationConfigurator& configurator);

		/**
		 * \fn	void Context::registerHandle(SK::IisuHandle& handle);
		 *
		 * \brief	Registers the handle described by handle.
		 *
		 * \param 	handle	The handle.
		 * 				
		 * This method is used to register a shared handle received from another application.
		 */

		void registerHandle(SK::IisuHandle& handle);
		/**
		 * \fn	SK::Result Context::destroyHandle(SK::IisuHandle& handle);
		 *
		 * \brief	Destroys the handle.
		 *
		 * \param 	handle	The handle.
		 *
		 * \return	the result of the call.
		 */

		SK::Result destroyHandle(SK::IisuHandle& handle);

		/**
		 * \fn	SK::Result Context::destroyHandleAndFreeLibrary( SK::IisuHandle& handle );
		 *
		 * \brief	Destroys the handle and free library described by handle.
		 *
		 * \param	handle	The handle.
		 *
		 * \return	the result of the call.
		 */

		SK::Result destroyHandleAndFreeLibrary( SK::IisuHandle& handle );
		class Logger ;

		/**
		 * \fn	static SK::Context::Logger Context::log();
		 *
		 * \brief	Gets a log object to be able to log through iisu's loggin mechanism
		 * 			ex: Context::log() << "Initializing iisu" << endl ;
		 *
		 * \return	The Logger.
		 */

		static SK::Context::Logger log() ;

		/**
		 * \fn	void Context::flushLogs();
		 *
		 * \brief	Flushes the logs.
		 */

		void flushLogs() ;

		/**
		 * \fn	void Context::finalize();
		 *
		 * \brief	Finalizes all activity. This function will cleanup all handles and devices that have been allocated
		 */

		void finalize() ;
	protected:
		void addLog(const char *) ;
	private:
		Context& operator=(const Context &);
		Context (const Context &);

	private:
		ContextImpl* m_pimpl;
		static Context instance;

		/* Public Application Logging */
	
	public:

		/**
		 * \class	Logger
		 *
		 * \brief	This class is used for logging. See Context::log() for more information.
		 * 			
		 * \sa Context::log()
		 */

		class Logger
		{
		public:
			Logger()
			{
				SK::SharedPtr<std::ostringstream> tmp(new std::ostringstream());
				m_s = tmp;
			}
			~Logger()
			{
				Context::Instance().addLog(m_s->str().c_str());
			}

			template <typename T>
			std::basic_ostream<char> & operator<<(T t)
			{
				return ((*m_s) << t);
			}

			std::basic_ostream<char> & operator<<(std::basic_ios<char, std::char_traits<char> >& (*_Pfn)(std::basic_ios<char, std::char_traits<char> >&)) { return ((*m_s) << _Pfn);	}
			std::basic_ostream<char> & operator<<(std::ios_base& (*_Pfn)(std::ios_base&)) { return ((*m_s) << _Pfn); }

		private:
			SK::SharedPtr<std::ostringstream> m_s;

		};
	};



}

