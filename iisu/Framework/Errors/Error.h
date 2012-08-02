#pragma once

#include <iostream>
#include <sstream>
#include <Foundation/DataTypes/String/String.h>
#include <Framework/Errors/ErrorCodes.h>
#include <Platform/SkPlatform.h>

class INE_Serializer;

namespace SK {

	/**
	 * \class	ErrorMessage
	 *
	 * \brief	Utility class to build error messages in a stream like fashion. 
	 */

	class IISUSDK_API ErrorMessage
	{
	public:

		/**
		 * \fn	ErrorMessage::ErrorMessage()
		 *
		 * \brief	Default constructor.
		 */

		ErrorMessage():m_description("") {
		} 

		/**
		 * \fn	ErrorMessage::ErrorMessage(const SK::String& message)
		 *
		 * \brief	Constructor.
		 *
		 * \param	message	The error message.
		 */

		ErrorMessage(const SK::String& message)
		{
			m_description = message ;
		}

		/**
		 * \fn	ErrorMessage::ErrorMessage(const char *message)
		 *
		 * \brief	Constructor.
		 *
		 * \param	message	The error message.
		 */

		ErrorMessage(const char *message)
		{
			m_description = message ;
		}

		/**
		 * \fn	ErrorMessage::~ErrorMessage()
		 *
		 * \brief	Destructor.
		 */

		~ErrorMessage()
		{
		}

		/**
		 * \fn	ErrorMessage::ErrorMessage(const ErrorMessage &other)
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		ErrorMessage(const ErrorMessage &other) {
			m_description=other.m_description ;
		} ;

		/**
		 * \fn	ErrorMessage ErrorMessage::&operator=(const ErrorMessage &other)
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A reference to this object.
		 */

		ErrorMessage &operator =(const ErrorMessage &other) {
			m_description=other.m_description ;
			return *this ;
		};

		
		/**
		 * \fn	ErrorMessage & ErrorMessage::operator<<(T t)
		 *
		 * \brief	Adds an object of type T to the error message.
		 *
		 * \param	t	The object.
		 *
		 * \return	A reference to this.
		 */

		template <typename T>
		ErrorMessage & operator<<(T t)
		{
			std::ostringstream o ;
			o << m_description.ptr() ;
			o << t ;
			m_description = o.str().c_str() ;
			return *this ;
		}

		/**
		 * \fn	ErrorMessage & ErrorMessage::operator<<(SK::String t)
		 *
		 * \brief	Adds a string to the error message.
		 *
		 * \param	t	The string to add
		 *
		 * \return	A Reference to this.
		 */

		ErrorMessage & operator<<(SK::String t)
		{
			std::ostringstream o ;
			o << m_description.ptr() ;
			o << t.ptr() ;
			m_description = o.str().c_str() ;
			return *this ;
		}

		/**
		 * \fn	operator SK::String() const
		 *
		 * \brief	Returns a SK::String with the full error message.
		 */

		operator SK::String() const {
			return m_description ;
		} ;

		/**
		 * \fn	operator const char ErrorMessage::*() const
		 *
		 * \brief	char* casting operator.
		 *
		 * \return	a char pointer to the error message.
		 */

		operator const char *() const {
			return m_description.ptr() ;
		} ;

	private:
		SK::String m_description;
	};

	//-----------------------------------------------------------------------

	/**
	 * \class	Error
	 *
	 * \brief	Generic class to describe an Error. 
	 */

	class IISUSDK_API Error {

	public:

		/**
		 * \typedef	uint32_t Code
		 *
		 * \brief	The error code.
		 */

		typedef uint32_t Code ;

		/**
		 * \typedef	uint32_t ModuleID
		 *
		 * \brief	The id of the module that has generated the error .
		 */

		typedef uint32_t ModuleID ;

		friend class ::INE_Serializer; 
	public:

		/**
		 * \fn	Error::Error();
		 *
		 * \brief	Default constructor.
		 */

		Error() ; 

		/**
		 * \fn	Error::Error(const ErrorMessage &message,Code errorCode = SK::INTERNAL,
		 * 		ModuleID module = 0);
		 *
		 * \brief	Constructor used to specify an error occured.
		 *
		 * \param	message  	The message.
		 * \param	errorCode	(optional) the error code.
		 * \param	module   	(optional) the module that issued the error.
		 */

		Error(const ErrorMessage &message,Code errorCode = SK::INTERNAL, ModuleID module = 0) ;

		/**
		 * \fn	Error::Error(const Error &child,const ErrorMessage &description,Code errorCode,
		 * 		ModuleID module);
		 *
		 * \brief	Constructor to specify an error occured by binding it to another error
		 *
		 * \param	child	   	The original error that lead to this one.
		 * \param	description	The description.
		 * \param	errorCode  	The error code.
		 * \param	module	   	The module that issued the error.
		 */

		Error(const Error &child,const ErrorMessage &description,Code errorCode,ModuleID module) ;

		/**
		 * \fn	Error::Error(const Error &other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The other.
		 */

		Error(const Error &other) ;

		/**
		 * \fn	Error Error::&operator=(const Error &other);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A reference to this object.
		 */

		Error &operator =(const Error &other) ;

		/**
		 * \fn	virtual Error::~Error();
		 *
		 * \brief	Destructor.
		 */

		virtual ~Error() ;

		/**
		 * \fn	SK::String Error::getDescription() const;
		 *
		 * \brief	Returns the error description. Will accumulate the error from this error plus all error collected from children recursively
		 *
		 * \return	The description.
		 */

		SK::String getDescription() const ;

		/**
		 * \fn	SK::String Error::getMessage() const;
		 *
		 * \brief	Gets the error message, but only specific to this error (not the ones from the childrens)
		 *
		 * \return	The message.
		 */

		SK::String getMessage() const ;

		/**
		 * \fn	Code Error::getCode() const;
		 *
		 * \brief	Gets the error code.
		 *
		 * \return	The code.
		 */

		Code getCode() const ;

		/**
		 * \fn	ModuleID Error::getModuleID() const;
		 *
		 * \brief	Gets the module identifier from which the error was issued.
		 *
		 * \return	The module identifier.
		 */

		ModuleID getModuleID() const ;

		/**
		 * \fn	bool Error::hasError() const;
		 *
		 * \brief	Queries if the error object has an error to report.
		 *
		 * \return	true if error, false if not.
		 */

		bool hasError() const ;

		/**
		 * \fn	const Error* Error::getChild()const;
		 *
		 * \brief	Gets the error child (the reason why this error occured).
		 *
		 * \return	A pointer to the child if any.
		 */

		const Error* getChild()const;

		/**
		 * \fn	friend std::ostream& Error::operator<<(std::ostream& oo, const Error& err)
		 *
		 * \brief	Writes the object on an output stream
		 *
		 * \param [in,out]	oo	The oo.
		 * \param	err		  	The error.
		 *
		 * \return	a reference to the original output stream
		 */

		friend std::ostream& operator<<(std::ostream& oo, const Error& err)
		{
			if(!err.m_success) oo<<(const char*)(err.m_message);
			return oo;
		}

	private:
		void addChild(const Error &child) ;

	protected:
		ErrorMessage m_message ;
		ModuleID m_module ;
		Code m_code ;
		bool m_success ;
		Error *m_child ;
	} ;

}
