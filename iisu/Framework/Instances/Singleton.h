#pragma once

#include <Platform/SkPlatform.h>
#include <vector>

#include <cstddef>

 namespace SK
 {


	/**
	 * \class	Singleton
	 *
	 * \brief	A Singleton implementation. 
	 * 			
	 * 			A class T need to use the SINGLETON(T); macro inside the class and make its constructor/destructors private and it will become a signleton. This macro will give 
	 * 			an access to the singleton through T::Instance() call. This is call to the constructor of this class which will manage the singleton.
	 */
 	template <class T>
	class Singleton
 	{
 	public:

		/**
		 * \fn	Singleton::Singleton()
		 *
		 * \brief	Default constructor.
		 * 			
		 * 			Create the unique instance if this is the first call to the constructor for a type T.
		 */

		Singleton(){
			if(m_instance == NULL) {
				m_instance = new T();
			}
		}
 		virtual ~Singleton() {} ;

 		/**
 		 * \fn	T* Singleton::operator->()
 		 *
 		 * \brief	This operator allow the Singleton object to be used as a pointer to the singleton object.
 		 *
 		 * \return	A pointer to the singleton object.
 		 */

 		T* operator->(){return m_instance;}

		/**
		 * \fn	operator Singleton::T*()const
		 *
		 * \brief	A conversion operator to T*.
		 * 			
		 * 			Allows implicit conversion from the singleton to a pointer of the singleton object.
		 */

		operator T*()const{return m_instance;}

		/**
		 * \fn	operator Singleton::T*()const
		 *
		 * \brief	A conversion operator to T&.
		 * 			
		 * 			Allows implicit conversion from the singleton to a reference of the singleton object.
		 */
		operator T&()const{return *m_instance;}

		/**
		 * \fn	T* Singleton::operator&()const
		 *
		 * \brief	Reference operator, gets a pointer to the singleton object.
		 *
		 * \return	A pointer to the singleton object.
		 */

		T* operator&()const{return m_instance;}

		/**
		 * \fn	T& Singleton::operator*()const
		 *
		 * \brief	Dereference operator, gets a reference to the singleton object.
		 *
		 * \return	A reference to the singleton object.
		 */

		T& operator*()const{return *m_instance;}

 	private:
 		static T* m_instance;
 	};
 
 	template <class T>
 	T* Singleton<T>::m_instance=NULL;
 }

/**
 * \def	SINGLETON(X) template<class T> friend class SK::Singleton;
 *
 * \brief	This macro must be used inside a class to provide access to the private constructor of the class to the Singleton class.
 *
 * \param	X	The class.
 */

#define SINGLETON(X) \
	template<class T>\
	friend class SK::Singleton;\
	public : \
			 typedef SK::Singleton< X > Instance;\
	private:

