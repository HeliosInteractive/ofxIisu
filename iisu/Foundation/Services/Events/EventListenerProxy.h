#pragma once

#include <Framework/Functor/Function.h>
#include <Framework/Types/RefTypeTrait.h>

#include <Foundation/Services/Events/ActivationGestureEvent.h>
#include <Foundation/Services/Events/BackgroundLearningEvent.h>
#include <Foundation/Services/Events/CalibrationEvent.h>
#include <Foundation/Services/Events/ControllerEvents.h>
#include <Foundation/Services/Events/DeviceEvent.h>
#include <Foundation/Services/Events/ErrorEvent.h>
#include <Foundation/Services/Events/GenericEvent.h>
#include <Foundation/Services/Events/GestureEvent.h>
#include <Foundation/Services/Events/HumanoidActivatorEvent.h>
#include <Foundation/Services/Events/HumanoidComputerEvent.h>
#include <Foundation/Services/Events/ActivationGestureEvent.h>
#include <Foundation/Services/Events/DeviceEvent.h>
#include <Foundation/Services/Events/BackgroundLearningEvent.h>
#include <Foundation/Services/Events/CalibrationEvent.h>
#include <Foundation/Services/Events/ActivationGestureEvent.h>
#include <Foundation/Services/Events/DeviceEvent.h>
#include <Foundation/Services/Events/HandPosingGestureEvent.h>
#include <Foundation/Services/Events/HandMovingGestureEvent.h>
#include <Foundation/Services/Events/HumanoidClippedEvents.h>
#include <Foundation/Services/Events/HandActivationEvent.h>

namespace SK
{
	//! \cond EVENT_LISTENER_CALLERS
	
	class IEventListenerCaller
	{
	public:
		virtual ~IEventListenerCaller(){}
	};

	template<class T,  typename R>
	class EventListenerCaller;

	template<class T, typename P1>
	class EventListenerCaller<T, void(P1)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1) 
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2>
	class EventListenerCaller<T, void(P1, P2)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2) 
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2, typename P3>
	class EventListenerCaller<T, void(P1, P2, P3)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3) 
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2, typename P3, typename P4>
	class EventListenerCaller<T, void(P1, P2, P3, P4)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4) 
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3, p4));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2, typename P3, typename P4, typename P5>
	class EventListenerCaller<T, void(P1, P2, P3, P4, P5)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) 
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3, p4, p5));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class EventListenerCaller<T, void(P1, P2, P3, P4, P5, P6)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3, p4, p5, p6));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class EventListenerCaller<T, void(P1, P2, P3, P4, P5, P6, P7)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3, p4, p5, p6, p7));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class EventListenerCaller<T, void(P1, P2, P3, P4, P5, P6, P7, P8)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3, p4, p5, p6, p7, p8));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};
	
	template<class T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class EventListenerCaller<T, void(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public IEventListenerCaller
	{
	private:
		typedef IEventListenerCaller base_t;

	protected:
		EventListenerCaller(const SK::Function<void (T)>& function): m_function(function){} 		
		virtual ~EventListenerCaller(){}

	public:
		void operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
		{
			m_function(typename RefTypeTrait<T>::remove_const_ref_t(p1, p2, p3, p4, p5, p6, p7, p8, p9));
		}

	protected:
		SK::Function<void(T)> m_function; 
	};

	template<class T>
	class EventListenerProxy : public EventListenerCaller<T, typename RefTypeTrait<T>::remove_const_ref_t::functionType_t>
	{
	private:
		typedef typename RefTypeTrait<T>::remove_const_ref_t::functionType_t functionType_t;
		typedef EventListenerCaller<T,functionType_t> base_t;

	public:
		EventListenerProxy(const SK::Function<void (T)>& function): base_t(function)
		{
			m_proxyFunction = Function<functionType_t>(*static_cast<base_t*>(this), &base_t::operator());
		} 		
		~EventListenerProxy(){}

	public:
		SK::Function<functionType_t>& getProxyFunction() { return m_proxyFunction;}

	private:
		SK::Function<functionType_t> m_proxyFunction;
	};
	//! \endcond
	
}
