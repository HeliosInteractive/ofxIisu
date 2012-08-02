#pragma once
#include <Foundation/DataTypes/Enumeration/Enum.h>
#include <Foundation/DataTypes/String/String.h>
#include <Framework/Types/RefTypeTrait.h>

namespace SK
{
	/**
	 * \class	IEvent
	 *
	 * \brief	Event interface. 
	 */

	class IEvent
	{
	protected:
		IEvent(const SK::String& name):m_name(name){}
		virtual ~IEvent(){}

	public:

		/**
		 * \fn	SK::String IEvent::getName()const
		 *
		 * \brief	Gets the name of the event.
		 *
		 * \return	The name.
		 */

		SK::String getName()const{return m_name;}

	protected:
		SK::String m_name;
	};
	
	//! \cond EVENTS
	
	template <typename R>
	class Event;
	
	template <>
	class Event<void()> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		virtual ~Event(){}
	};
	template <typename P1>
	class Event<void(P1)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1);

	private:
		typedef IEvent base_t;

	protected:	
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1):base_t(name), m_p1(p1){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
	};
	template <typename P1, typename P2>
	class Event<void(P1, P2)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2):base_t(name), m_p1(p1), m_p2(p2){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
	};
	template <typename P1, typename P2, typename P3>
	class Event<void(P1, P2, P3)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2, P3);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2,typename SK::RefTypeTrait<P3>::add_const_ref_t p3):base_t(name), m_p1(p1), m_p2(p2), m_p3(p3){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
		typename SK::RefTypeTrait<P3>::remove_const_ref_t m_p3;
	};
	template <typename P1, typename P2, typename P3, typename P4>
	class Event<void(P1, P2, P3, P4)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2, P3, P4);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2,typename SK::RefTypeTrait<P3>::add_const_ref_t p3,typename SK::RefTypeTrait<P4>::add_const_ref_t p4):base_t(name), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
		typename SK::RefTypeTrait<P3>::remove_const_ref_t m_p3;
		typename SK::RefTypeTrait<P4>::remove_const_ref_t m_p4;
	};
	template <typename P1, typename P2, typename P3, typename P4, typename P5>
	class Event<void(P1, P2, P3, P4, P5)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2, P3, P4, P5);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2,typename SK::RefTypeTrait<P3>::add_const_ref_t p3,typename SK::RefTypeTrait<P4>::add_const_ref_t p4,typename SK::RefTypeTrait<P5>::add_const_ref_t p5):base_t(name), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
		typename SK::RefTypeTrait<P3>::remove_const_ref_t m_p3;
		typename SK::RefTypeTrait<P4>::remove_const_ref_t m_p4;
		typename SK::RefTypeTrait<P5>::remove_const_ref_t m_p5;
	};
	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class Event<void(P1, P2, P3, P4, P5, P6)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2, P3, P4, P5, P6);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2,typename SK::RefTypeTrait<P3>::add_const_ref_t p3,typename SK::RefTypeTrait<P4>::add_const_ref_t p4,typename SK::RefTypeTrait<P5>::add_const_ref_t p5,typename SK::RefTypeTrait<P6>::add_const_ref_t p6):base_t(name), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5), m_p6(p6){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
		typename SK::RefTypeTrait<P3>::remove_const_ref_t m_p3;
		typename SK::RefTypeTrait<P4>::remove_const_ref_t m_p4;
		typename SK::RefTypeTrait<P5>::remove_const_ref_t m_p5;
		typename SK::RefTypeTrait<P6>::remove_const_ref_t m_p6;
	};
	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class Event<void(P1, P2, P3, P4, P5, P6, P7)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2, P3, P4, P5, P6, P7);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2,typename SK::RefTypeTrait<P3>::add_const_ref_t p3,typename SK::RefTypeTrait<P4>::add_const_ref_t p4,typename SK::RefTypeTrait<P5>::add_const_ref_t p5,typename SK::RefTypeTrait<P6>::add_const_ref_t p6,typename SK::RefTypeTrait<P7>::add_const_ref_t p7):base_t(name), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5), m_p6(p6), m_p7(p7){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
		typename SK::RefTypeTrait<P3>::remove_const_ref_t m_p3;
		typename SK::RefTypeTrait<P4>::remove_const_ref_t m_p4;
		typename SK::RefTypeTrait<P5>::remove_const_ref_t m_p5;
		typename SK::RefTypeTrait<P6>::remove_const_ref_t m_p6;
		typename SK::RefTypeTrait<P7>::remove_const_ref_t m_p7;
	};
	//! \endcond
	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class Event<void(P1, P2, P3, P4, P5, P6, P7, P8)> : public IEvent
	{
	public:
		typedef void functionType_t (const SK::String&, P1, P2, P3, P4, P5, P6, P7, P8);

	private:
		typedef IEvent base_t;

	protected:
		Event(const SK::String& name):base_t(name){}
		Event(const SK::String& name,typename SK::RefTypeTrait<P1>::add_const_ref_t p1,typename SK::RefTypeTrait<P2>::add_const_ref_t p2,typename SK::RefTypeTrait<P3>::add_const_ref_t p3,typename SK::RefTypeTrait<P4>::add_const_ref_t p4,typename SK::RefTypeTrait<P5>::add_const_ref_t p5,typename SK::RefTypeTrait<P6>::add_const_ref_t p6,typename SK::RefTypeTrait<P7>::add_const_ref_t p7,typename SK::RefTypeTrait<P8>::add_const_ref_t p8):base_t(name), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5), m_p6(p6), m_p7(p7), m_p8(p8){}
		virtual ~Event(){}

	protected:
		typename SK::RefTypeTrait<P1>::remove_const_ref_t m_p1;
		typename SK::RefTypeTrait<P2>::remove_const_ref_t m_p2;
		typename SK::RefTypeTrait<P3>::remove_const_ref_t m_p3;
		typename SK::RefTypeTrait<P4>::remove_const_ref_t m_p4;
		typename SK::RefTypeTrait<P5>::remove_const_ref_t m_p5;
		typename SK::RefTypeTrait<P6>::remove_const_ref_t m_p6;
		typename SK::RefTypeTrait<P7>::remove_const_ref_t m_p7;
		typename SK::RefTypeTrait<P8>::remove_const_ref_t m_p8;
	};

//#define CustomEvent(...) SK::Event<void(__VA_ARGS__)>

}
