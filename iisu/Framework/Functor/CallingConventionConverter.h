#pragma once

#ifdef _WIN32

namespace SK
{

	/**
	 * \struct	template<typename R> struct CallingConventionTrait
	 *
	 * \brief	This trait class takes a function signature as a template argument and gives its cdecl and stdcall signature as typedef
	 */

	template<typename R = void()>
	struct CallingConventionTrait;

	template<typename R>
	struct CallingConventionTrait<R()>
	{
		typedef R(__stdcall *stdcall_funcType_t)();
		typedef R(__cdecl *cdecl_funcType_t)();
	};

	template<typename R, typename P1>
	struct CallingConventionTrait<R(P1)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1);
		typedef R(__cdecl *cdecl_funcType_t)(P1);
	};

	template<typename R, typename P1, typename P2>
	struct CallingConventionTrait<R(P1, P2)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2);
	};

	template<typename R, typename P1, typename P2, typename P3>
	struct CallingConventionTrait<R(P1, P2, P3)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3);
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4>
	struct CallingConventionTrait<R(P1, P2, P3, P4)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4);
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct CallingConventionTrait<R(P1, P2, P3, P4, P5)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5);
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	struct CallingConventionTrait<R(P1, P2, P3, P4, P5, P6)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6);
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	struct CallingConventionTrait<R(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6, P7);
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	struct CallingConventionTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8);
	};

	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	struct CallingConventionTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	};

	// -----------------------------------------------

	struct ICallingConventionMapper
	{
		virtual void* rawPtr()const =0;
	};

	template<typename R = void()>
	struct CallingConventionMapper;

	template<typename R>
	struct CallingConventionMapper<R ()> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)();
		typedef R(__cdecl *cdecl_funcType_t)();

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()() { return m_listener();}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1>
	struct CallingConventionMapper<R (P1)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1);
		typedef R(__cdecl *cdecl_funcType_t)(P1);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1) { return m_listener(p1);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2>
	struct CallingConventionMapper<R (P1, P2)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2) { return m_listener(p1, p2);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3>
	struct CallingConventionMapper<R (P1, P2, P3)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3) { return m_listener(p1, p2, p3);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	struct CallingConventionMapper<R (P1, P2, P3, P4)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4) { return m_listener(p1, p2, p3, p4);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct CallingConventionMapper<R (P1, P2, P3, P4, P5)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) { return m_listener(p1, p2, p3, p4, p5);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	struct CallingConventionMapper<R (P1, P2, P3, P4, P5, P6)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) { return m_listener(p1, p2, p3, p4, p5, p6);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	struct CallingConventionMapper<R (P1, P2, P3, P4, P5, P6, P7)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6, P7);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) { return m_listener(p1, p2, p3, p4, p5, p6, p7);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	struct CallingConventionMapper<R (P1, P2, P3, P4, P5, P6, P7, P8)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) { return m_listener(p1, p2, p3, p4, p5, p6, p7, p8);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	struct CallingConventionMapper<R (P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public ICallingConventionMapper
	{
		typedef R(__stdcall *stdcall_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(__cdecl *cdecl_funcType_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

		CallingConventionMapper(stdcall_funcType_t listener):m_listener(listener) {}
		R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) { return m_listener(p1, p2, p3, p4, p5, p6, p7, p8, p9);}
		virtual void* rawPtr()const {return m_listener;}

	private:
		stdcall_funcType_t m_listener;
	};

}

#endif
