#pragma once

#include <Framework/Functor/Function.h>
#include <Foundation/Services/Events/EventListenerProxy.h>
#include <Foundation/Services/Types/RawData.h>
#include <cstdlib>
#include <Foundation/Services/Types/FunctionTypeInfo.h>
#include <Framework/Types/FunctionTypeTrait.h>
#include <Framework/Functor/CallingConventionConverter.h>
#include <Iisu/API/IisuCTypes.h>
template<typename T>
struct EventManager_C;

struct EventManagerAll_C;
extern "C" {
	IISUSDK_API SkError_C SK_SDK_DECL SkEventManager_getMetaInfo(IN SkEventManager_C manager, IN SkString_C eventName, OUT SkMetaInfo_C* metainfo) ; 
}

namespace SK {
	//! \cond EVENT_LISTENER_CALLER_MANAGER
	class IEventListenerCallerManager
	{
	public:
		virtual IEventListenerCaller* createProxy(const SK::String& name, const IFunction& function, const SK::TypeInfo& eventType)=0;
		virtual IEventListenerCaller* removeProxy(const SK::String& name, const SK::IFunction& function, const SK::TypeInfo& eventType)=0;
		virtual void destroyProxy(IEventListenerCaller* elc)=0;

		virtual ~IEventListenerCallerManager(){}
	};
	//! \endcond

	/**
	 * \class	EventManager
	 *
	 * \brief	The Event Manager class. 
	 */

	class EventManager {
		friend class IEventThrower;
		friend SkError_C (::SkEventManager_getMetaInfo)  (IN SkEventManager_C manager, IN SkString_C eventName, OUT SkMetaInfo_C* metainfo) ;
	protected:
		EventManager();
		virtual ~EventManager();


	public:

		/**
		 * \fn	virtual SK::Return<bool> EventManager::isSystemEvent(const SK::String& eventName)const=0;
		 *
		 * \brief	Tells if an event is a system event or not.
		 *
		 * \param	eventName	Name of the event.
		 *
		 * \return	true if the event is a system event, if successful
		 */

		virtual SK::Return<bool> isSystemEvent(const SK::String& eventName)const=0;

		/**
		 * \fn	virtual SK::Return<uint32_t> EventManager::getEventCount() const=0;
		 *
		 * \brief	Gets how many event are registered.
		 *
		 * \return	The number of event registered.
		 */

		virtual SK::Return<uint32_t> getEventCount() const=0;

		/**
		 * \fn	virtual SK::Return<SK::String> EventManager::getEventName(uint32_t index)const=0;
		 *
		 * \brief	Gets an event name of the index-th event.
		 *
		 * \param	index	Zero-based index of the event.
		 *
		 * \return	The event name, if successful.
		 */

		virtual SK::Return<SK::String> getEventName(uint32_t index)const=0;

		/**
		 * \fn	virtual SK::Return<bool> EventManager::eventIsRegistered(const SK::String& evtName)const=0;
		 *
		 * \brief	Tells if the event is registered.
		 *
		 * \param	the event name.
		 *
		 * \return	true if the event is registered, if successful
		 */

		virtual SK::Return<bool> eventIsRegistered(const SK::String& evtName)const=0;

		/**
		 * \fn	virtual SK::Result EventManager::throwEvent(const SK::String& sCmd,
		 * 		const std::vector<SK::RawData>& params, const SK::FunctionTypeInfo& typeInfo)=0;
		 *
		 * \brief	Throws an event.
		 *
		 * \param	sCmd		The event name.
		 * \param	params  	An array containing the parameters of the event.
		 * \param	typeInfo	A TypeInfo describing the event type.
		 *
		 * \return	a result specifying if the event could be thrown or not
		 */

		virtual SK::Result throwEvent(const SK::String&  sCmd, const SK::Array<SK::RawData>& params, const SK::FunctionTypeInfo& typeInfo)=0;

	public:

		/**
		 * \fn	virtual SK::Return<SK::FunctionTypeInfo> EventManager::getEventType(const SK::String& eventName)const=0;
		 *
		 * \brief	Gets the function type of the event.
		 *
		 * \param	eventName	Name of the event.
		 *
		 * \return	The event type, if successful
		 */

		virtual SK::Return<SK::FunctionTypeInfo> getEventType(const SK::String& eventName)const=0;

		/**
		 * \fn	virtual SK::Return<SK::Attributes> EventManager::getAttributes(const SK::String& eventName)const=0;
		 *
		 * \brief	Gets the attributes.
		 *
		 * \param	eventName	Name of the event.
		 *
		 * \return	The attributes, if successful
		 */

		virtual SK::Return<SK::Attributes> getAttributes(const SK::String& eventName)const=0;

		/**
		 * \fn	virtual SK::Return<SK::TypeInfo> EventManager::getMetaInfoType(const SK::String& eventName)const=0;
		 *
		 * \brief	Gets the TypeInfo of the meta information associated to an event.
		 *
		 * \param	eventName	The name of the event.
		 *
		 * \return	The meta information type, if successful
		 */

		virtual SK::Return<SK::TypeInfo> getMetaInfoType(const SK::String& eventName)const=0;

		/**
		 * \fn	SK::Return< SK::MetaInfo<T> > EventManager::getMetaInfo(const SK::String& eventName)const
		 *
		 * \brief	Gets the meta information associated to an event.
		 *
		 * \param	eventName	The name of the event.
		 *
		 * \return	The meta information.
		 */

		template<typename T>
		SK::Return< SK::MetaInfo<T> > getMetaInfo(const SK::String& eventName)const
		{
			SK::Return<SK::RawData> res = getMetaInfoImpl(eventName, SK::Type<SK::MetaInfo<T> >::INFO);
			RETURN_IF_FAILED(res) ;
			return res.get().getRef< SK::MetaInfo<T> >();
		}

	public:
		template<typename T>
		SK::Result registerRawEventListener(const SK::String&  name, T eventListener)
		{
			return registerRawEventListenerImpl(name, SK::Function<typename SK::FunctionTypeTrait<T>::function_t>(eventListener));
		}
		template<class C, typename T>
		SK::Result registerRawEventListener(const SK::String&  name, C& obj, T eventListener)
		{
			return registerRawEventListenerImpl(name, SK::Function<typename SK::MethodTypeTrait<C, T>::method_t>(obj, eventListener));
		}

		template<typename T>
		SK::Result unregisterRawEventListener(const SK::String&  name, T eventListener)
		{
			return unregisterRawEventListenerImpl(name, SK::Function<typename SK::FunctionTypeTrait<T>::function_t>(eventListener));
		}
		template<class C, typename T>
		SK::Result unregisterRawEventListener(const SK::String&  name, C& obj, T const eventListener)
		{
			return unregisterRawEventListenerImpl(name, SK::Function<typename SK::MethodTypeTrait<C, T>::method_t>(obj, eventListener));
		}

	public:
		template<typename P1>
		SK::Result registerEventListener(const SK::String&  name, void(*eventListener)(P1))
		{
			TypeInfo typeInfo=SK::Type<P1>::INFO;//typename RefTypeTrait<P1>::remove_const_ref_t>::INFO ;
			SK::EventListenerProxy<P1>* elp = static_cast<SK::EventListenerProxy<P1>*>(m_eventListenerCallerManager->createProxy(name, SK::Function<void(P1)>(eventListener), typeInfo));
			return registerRawEventListenerImpl(name, elp->getProxyFunction());
		}

		template<class C, typename P1>
		SK::Result registerEventListener(const SK::String&  name, C& obj, void(C::*eventListener)(P1))
		{
			SK::EventListenerProxy<P1>* elp = static_cast<SK::EventListenerProxy<P1>*>(m_eventListenerCallerManager->createProxy(name, SK::Function<void(P1)>(obj, eventListener), SK::Type<P1>::INFO/*typename RefTypeTrait<P1>::remove_const_ref_t>::INFO*/));
			return registerRawEventListenerImpl(name, elp->getProxyFunction());
		}

		template<typename P1>
		SK::Result unregisterEventListener(const SK::String&  name, void(*eventListener)(P1))
		{
			IEventListenerCaller* ptr = m_eventListenerCallerManager->removeProxy(name, SK::Function<void(P1)>(eventListener), SK::Type<P1>::INFO/*typename RefTypeTrait<P1>::remove_const_ref_t>::INFO*/);
			if(ptr == NULL) return SK::Result::NoError;
			SK::EventListenerProxy<P1>* elp = static_cast<SK::EventListenerProxy<P1>*>(ptr);
			SK::Result res = unregisterRawEventListenerImpl(name, elp->getProxyFunction());
			m_eventListenerCallerManager->destroyProxy(elp);
			return res;
		}


		template<class C, typename P1>
		SK::Result unregisterEventListener(const SK::String&  name, C& obj, void(C::*eventListener)(P1))
		{
			IEventListenerCaller* ptr = m_eventListenerCallerManager->removeProxy(name, SK::Function<void(P1)>(obj, eventListener), SK::Type<P1>::INFO/*typename RefTypeTrait<P1>::remove_const_ref_t>::INFO*/);
			if(ptr == NULL) return SK::Result::NoError;
			SK::EventListenerProxy<P1>* elp = static_cast<SK::EventListenerProxy<P1>*>(ptr);
			SK::Result res = unregisterRawEventListenerImpl(name, elp->getProxyFunction());
			m_eventListenerCallerManager->destroyProxy(elp);
			return res;
		}
	private:
		virtual SK::Return<SK::RawData> getMetaInfoImpl(const SK::String& eventName, const SK::TypeInfo& typeInfo)const=0;

		virtual SK::Return<SK::String> translateAlias(const SK::String& name)const=0;

    private:
          template<typename T>                                                                        
          void* functionPtrToVoidPtr(T eventListener)
          {
             union
             {
               void* ptr;
               T memberPtr;
             }converter;
             converter.memberPtr = eventListener;
             return converter.ptr;
          }


	private:
		template<typename T>
		SK::Result registerRawEventListenerImpl(const SK::String&  name, const SK::Function<T>& eventListener)
		{
			return registerRawEventListenerImpl(name, eventListener, SK::FunctionType<T>::INFO);
		}
		template<typename T>
		SK::Result unregisterRawEventListenerImpl(const SK::String&  name, const SK::Function<T>& eventListener)
		{
			return unregisterRawEventListenerImpl(name, eventListener, SK::FunctionType<T>::INFO);
		}

	protected:
		virtual SK::Result registerRawEventListenerImpl(const SK::String& name, const SK::IFunction& eventListener, const SK::FunctionTypeInfo&)=0;
		virtual SK::Result unregisterRawEventListenerImpl(const SK::String& name, const SK::IFunction& eventListener, const SK::FunctionTypeInfo&)=0;

		IEventListenerCallerManager* m_eventListenerCallerManager;

	private:
		template<typename T>
		friend struct ::EventManager_C;
		friend struct ::EventManagerAll_C;

#ifdef WIN32
	public:
		template<typename T>
		SK::Result registerOuterListener( const char* name, T eventListener)
		{
			SK::CallingConventionMapper<typename FunctionTypeTrait<T>::function_t>* caller = new SK::CallingConventionMapper<typename FunctionTypeTrait<T>::function_t>(eventListener);
			SK::Result res = registerRawEventListener(name, *caller, &CallingConventionMapper<typename FunctionTypeTrait<T>::function_t>::operator());
			if(res.failed()) return res;
			return registerOuterListenerImpl(*caller);
		}

		template<typename T>
		SK::Result unregisterOuterListener(const char* name, T  eventListener)
		{
			SK::CallingConventionMapper<typename FunctionTypeTrait<T>::function_t>* caller = new SK::CallingConventionMapper<typename FunctionTypeTrait<T>::function_t>(eventListener);
			SK::Result res = unregisterRawEventListener(name, *caller, &CallingConventionMapper<typename FunctionTypeTrait<T>::function_t>::operator());
			if(res.failed()) return res;
			return unregisterOuterListenerImpl(*caller);
		}
// 		SK::Result registerOuterAllListener(void (__stdcall *eventListener)(const SK::String&))
// 		{
// 			SK::CallingConventionMapper<void (const SK::String&)>* caller = new SK::CallingConventionMapper<void (const SK::String&)>(eventListener);
// 			SK::Result res = registerAllRawEventListener(*caller, &CallingConventionMapper<void (const SK::String&)>::operator());
// 			if(res.failed()) return res;
// 			return registerOuterListenerImpl(*caller);
// 		}
// 		SK::Result unregisterOuterAllListener(void (__stdcall *eventListener)(const SK::String&))
// 		{
// 			SK::CallingConventionMapper<void (const SK::String&)>* caller = new SK::CallingConventionMapper<void (const SK::String&)>(eventListener);
// 			SK::Result res = unregisterAllRawEventListener(*caller, &CallingConventionMapper<void (const SK::String&)>::operator());
// 			if(res.failed()) return res;
// 			return registerOuterListenerImpl(*caller);
// 		}
// 		
	protected:
		virtual SK::Result registerOuterListenerImpl(ICallingConventionMapper& caller) = 0;
		virtual SK::Result unregisterOuterListenerImpl(ICallingConventionMapper& caller) = 0;
#endif
	} ;
} ;
