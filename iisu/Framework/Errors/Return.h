#pragma once

#include <iostream>
#include <assert.h>

#include <Framework/Errors/Error.h>
#include <Framework/Instances/SharedPtr.h>
#include <Framework/Types/RefTypeTrait.h>

#include <Platform/SkPlatform.h>

class INE_Deserializer ;

namespace SK {

	/**
	 * \class	ReturnBase
	 *
	 * \brief	Base class for all Return classes. 
	 */

	class IISUSDK_API ReturnBase {
	protected:
		template<class> friend class Return ;
		ReturnBase():m_checked(false) {} ;
		ReturnBase(const SK::String &explanation,Error::Code errorCode,Error::ModuleID module) ;
		ReturnBase(const Error &cause,const SK::String &explanation,Error::ModuleID module,Error::Code errorCode) ;
		explicit ReturnBase(const ReturnBase &other) ;
		virtual ~ReturnBase() {
#ifdef SK_RETURN_CHECK
			assert(m_checked) ; // If you get here, you probably did not use the return value of last operation!!
#endif
		} ;
	public:

		/**
		 * \fn	bool ReturnBase::succeeded() const;
		 *
		 * \brief	tells if the return value represents a successful call.
		 *
		 * \return	true if the return is valid and contains a return value.
		 */

		bool succeeded() const ;

		/**
		 * \fn	bool ReturnBase::failed() const;
		 *
		 * \brief	tells if the return value represents a failed call.
		 *
		 * \return	true if it the return represent an error.
		 */

		bool failed() const ;

		/**
		 * \fn	SK::String ReturnBase::getDescription() const;
		 *
		 * \brief	Returns the error description associated to the Return value.
		 *
		 * \return	The description of the error.
		 */

		SK::String getDescription() const ;

		/**
		 * \fn	Error::Code ReturnBase::getErrorCode() const;
		 *
		 * \brief	Returns the error code associated to the Return value.
		 *
		 * \return	The error code of the error.
		 */

		Error::Code getErrorCode() const ;

		/**
		 * \fn	Error::ModuleID ReturnBase::getModuleID() const;
		 *
		 * \brief	Gets the module identifier of the module from which the error originates. Currently always 0.
		 *
		 * \return	The module identifier.
		 */

		Error::ModuleID getModuleID() const ;

		/**
		 * \fn	Error ReturnBase::getError() const;
		 *
		 * \brief	Gets the error object associated to this object.
		 *
		 * \return	The error.
		 */

		Error getError() const ;

		void ignoreError() const ;
	protected:
		Error m_error ;
		mutable bool m_checked ;
	private:
		ReturnBase &operator =(const ReturnBase &other) ;

	} ;

	//! \cond RETURN_TRAIT
	template <typename T>
	struct ReturnTrait
	{
		typedef typename SK::RefTypeTrait<T>::add_const_ref_t return_t;
		typedef SharedPtr<typename SK::RefTypeTrait<T>::remove_const_ref_t> container_t;
		static container_t createContainer(return_t in) {return container_t(new typename SK::RefTypeTrait<T>::remove_const_ref_t(in));}
		static bool check(container_t in) {return (in.get() != NULL);}
		static return_t returnValue(const container_t& in){return *in;}
	};

	template <typename T>
	struct ReturnTrait<T&>
	{
		typedef T& return_t;
		typedef T* container_t;
		static container_t createContainer(return_t in) {return &in;}
		static bool check(container_t in) {return (in != NULL);}
		static return_t returnValue(const container_t& in){return *in;}
	};

	template <typename T>
	struct ReturnTrait<T*>
	{
		typedef T* return_t;
		typedef T* container_t;
		static container_t createContainer(return_t in) {return in;}
		static bool check(container_t in) {return (in != NULL);}
		static return_t returnValue(const container_t& in){return in;}
	};

	//! \endcond
	
	/**
	 * \class	Return
	 *
	 * \brief	Templatized class representing the return value of a function that can fail.
	 * 			
	 * 			the return value can be tested for success or failure
	 * 			in the case of success, you can call get() to grab the value encapsulated in the Return object
	 * 			in the case of failure, you can get an error description and code describing the reason why the function failed
	 * 			
	 * 			E.G.
	 * 			
	 * 			SK::Return<SK::Device *> result = m_iisuHandle ->initializeDevice(deviceConfig);
	 * 			if (result.succeeded()) {
	 * 				SK::Device *device = result.get() ;
	 * 				// proceed
	 * 			}
	 */


	template <typename X>
	class Return:public ReturnBase {
	public:

		/**
		 * \fn	Return::Return();
		 *
		 * \brief	Default constructor.
		 */

		Return() ;

		/**
		 * \fn	Return::Return(typename SK::ReturnTrait<X>::return_t value);
		 *
		 * \brief	Constructor taking a return value. Use this one to return a value (i.e. a 'successful' return)
		 *
		 * \param	value	the value to return.
		 */

		Return(typename SK::ReturnTrait<X>::return_t value) ;

		/**
		 * \fn	Return::Return(const Return<X> &other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	the Return to construct from.
		 */

		Return(const Return<X> &other) ;

		/**
		 * \fn	Return::Return(const Return<void> &other);
		 *
		 * \brief	Initialise a typed return (e.g. Return<int>) from specialized version of return (Return<void> - also called result) 
		 * 			
		 * 			This is used to allow to carry error recursively. The construction should only be done in the case that the 'other' has
		 * 			a failed status, otherwise the Return<X> would be flagged as succeeded but wouldn't carry any value to get().
		 *
		 * \param	other	The Return<void> & to be constructed from.
		 */

		Return(const Return<void> &other) ;

		/**
		 * \fn	virtual Return::~Return();
		 *
		 * \brief	Destructor.
		 */

		virtual ~Return() ;

		/**
		 * \fn	typename<X> Return::get() const;
		 *
		 * \brief	returns the value encapsulated in the object. Only valid if succeeded() = true ;
		 *
		 * \return	the encapsulated return value. 
		 * 			
		 * 			The type of this return is conditioned by the template parameter of the class 
		 * 			(hence the ReturnTrait). here is the different signature of the function: <br>
		 * 			- if X is a reference: the return type is X&  
		 * 			- if X is a pointer: the return type is X*  
		 * 			- otherwise the return is const X&  
		 */

		typename SK::ReturnTrait<X>::return_t get() const;

		/**
		 * \fn	friend std::ostream& Return::operator<<(const std::ostream& oo, const Return<X>& ret)
		 *
		 * \brief	streaming operator for Return classes
		 *
		 * \param	oo 	the output stream.
		 * \param	ret	The return value to be streamed.
		 *
		 * \return	the output stream.
		 */

		friend std::ostream& operator<<(std::ostream& oo, const Return<X>& ret)
		{
			if(ret.m_value.get() != NULL)
				oo<<*ret.m_value.get();
			else
				oo<<ret.m_error;
			return oo;
		}

		/**
		 * \fn	Return<X> Return::&operator=(const Return<X> &other);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A shallow copy of this object.
		 */

		Return<X> &operator =(const Return<X> &other) ;

		/**
		 * \fn	Return<void> Return::toResult();
		 *
		 * \brief	Converts this object to a rResult.
		 *
		 * \return	This object as a Return<void>
		 */

		Return<void> toResult() ;

	private:
		typename SK::ReturnTrait<X>::container_t m_value ;

	} ;

	/**
	 * \class	Return<void> (a.k.a) Result
	 *
	 * \brief	Specialized version of Return for when there is no 'value' to return.
	 * 			
	 * 			the result value can be tested for success or failure
	 * 			in the case of success, you can call get to grab the typed data returned by the function
	 * 			in the case of failure, you can get an error description and code describing the reason why the function failed
	 * 			
	 * 			E.G.
	 * 			
	 * 			SK::Return<SK::Device *> result = m_iisuHandle ->initializeDevice(deviceConfig);
	 * 			if (result.succeeded()) {
	 * 				SK::Device *device = result.get() ;
	 * 			}
	 */

	/**
	  * \brief	This class is the specialization of SK::Return<X> for void. There is also a typedef that allows the 
	  * 			user to use SK::Result instead of SK::Return<void> 
	  *
	  */

	 template <>
	class IISUSDK_API Return<void>:public ReturnBase {
	public:

		/**
		 * \fn	Return<void>::Return();
		 *
		 * \brief	Default constructor.
		 */

		Return() ;

		/**
		 * \fn	explicit Return<void>::Return(const ReturnBase &cause);
		 *
		 * \brief	Constructor allowing to construct a Result from any type of Return<X>.
		 *
		 * \param	cause	The other error to construct from.
		 */

		explicit Return(const ReturnBase &cause) ;

		/**
		 * \fn	Return<void>::Return(const ErrorMessage &description,Error::Code errorCode = SK::INTERNAL,
		 * 		Error::ModuleID = 0);
		 *
		 * \brief	Constructor for signaling and error occured.
		 *
		 * \param	description	The error message to fill the error with.
		 * \param	errorCode  	(optional) the error code.
		 * \param			   	(optional) the module the error came from.
		 */

		Return(const ErrorMessage &description,Error::Code errorCode = SK::INTERNAL,Error::ModuleID = 0) ;

		/**
		 * \fn	Return<void>::Return(const ReturnBase &cause,const ErrorMessage &description,
		 * 		Error::Code errorCode = SK::INTERNAL,Error::ModuleID module = 0);
		 *
		 * \brief	Constructor for signaling and error occured, adding a 'cause' result as reference why the function failed.
		 *
		 * \param	cause	   	The cause why we're signalling this error.
		 * \param	description	The error message to fill the error with.
		 * \param	errorCode  	(optional) the error code.
		 * \param	module	   	(optional) the module.
		 */

		Return(const ReturnBase &cause,const ErrorMessage &description,Error::Code errorCode = SK::INTERNAL,Error::ModuleID module = 0) ;

		/**
		 * \fn	virtual Return<void>::~Return();
		 *
		 * \brief	Destructor.
		 */

		virtual ~Return() ;


		/**
		 * \fn	friend std::ostream& Return::operator<<(const std::ostream& oo, const Return<X>& ret)
		 *
		 * \brief	streaming operator for Return classes
		 *
		 * \param	oo 	the output stream.
		 * \param	ret	The return value to be streamed.
		 *
		 * \return	the output stream.
		 */

		friend std::ostream& operator<<(std::ostream& oo, const Return<void>& ret)
		{
			oo<<ret.m_error;
			return oo;
		}

		/**
		 * \fn	Return<void> Return<void>::&operator=(const Return<void> &other);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The other.
		 *
		 * \return	A shallow copy of this object.
		 */

		Return<void> &operator =(const Return<void> &other) ;

		/**
		 * \fn	Return<void> Return<void>::&toResult()
		 *
		 * \brief	Converts this object to a result. Not really needed implemented for symmetry with the generic case.
		 *
		 * \return	This object as a Return<void>&.
		 */

		Return<void> &toResult() { return *this ; }

	public:
		static Return<void> NoError ;
	private:
	protected:
		friend class ::INE_Deserializer ;
		Return(Error &cause) ;
		//! \cond ALLOW_NO_CHECK
		class AllowNoCheck {
		} ;
		Return(AllowNoCheck) ;
		//! \endcond

	} ;

	typedef Return<void> Result ;
} ;

#define RETURN_IF_FAILED(r) if (r.failed()) return r.toResult() 
#define RETURN_MESSAGE_IF_FAILED(r,m) if (r.failed()) return SK::Result(r,SK::ErrorMessage() << m) 
#define RETURN_MESSAGE_AND_CODE_IF_FAILED(r,m,c) if (r.failed()) return SK::Result(r,SK::ErrorMessage() << m,c) 

#include "Return.hpp"
