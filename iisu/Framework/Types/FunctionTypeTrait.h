#pragma once

namespace SK
{
	//! \cond FUNCTION_TYPE_TRAITS
	template <typename T> 
	struct FunctionTypeTrait;

	template <typename R> 
	struct FunctionTypeTrait<R()>
	{
		typedef R (*functionPtr_t)();
		typedef R (function_t)();
	};
	template <typename R, typename P1> 
	struct FunctionTypeTrait<R(P1)>
	{
		typedef R (*functionPtr_t)(P1);
		typedef R (function_t)(P1);
	};
	template <typename R, typename P1, typename P2> 
	struct FunctionTypeTrait<R(P1, P2)>
	{
		typedef R (*functionPtr_t)(P1, P2);
		typedef R (function_t)(P1, P2);
	};
	template <typename R, typename P1, typename P2, typename P3> 
	struct FunctionTypeTrait<R(P1, P2, P3)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3);
		typedef R (function_t)(P1, P2, P3);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4> 
	struct FunctionTypeTrait<R(P1, P2, P3, P4)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4);
		typedef R (function_t)(P1, P2, P3, P4);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> 
	struct FunctionTypeTrait<R(P1, P2, P3, P4, P5)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5);
		typedef R (function_t)(P1, P2, P3, P4, P5);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> 
	struct FunctionTypeTrait<R(P1, P2, P3, P4, P5, P6)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> 
	struct FunctionTypeTrait<R(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6, P7);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> 
	struct FunctionTypeTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6, P7, P8);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> 
	struct FunctionTypeTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R (*function_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	};
	template <typename R> 
	struct FunctionTypeTrait<R(*)()>
	{
		typedef R (*functionPtr_t)();
		typedef R (function_t)();
	};
	template <typename R, typename P1> 
	struct FunctionTypeTrait<R(*)(P1)>
	{
		typedef R (*functionPtr_t)(P1);
		typedef R (function_t)(P1);
	};
	template <typename R, typename P1, typename P2> 
	struct FunctionTypeTrait<R(*)(P1, P2)>
	{
		typedef R (*functionPtr_t)(P1, P2);
		typedef R (function_t)(P1, P2);
	};
	template <typename R, typename P1, typename P2, typename P3> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3);
		typedef R (function_t)(P1, P2, P3);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3, P4)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4);
		typedef R (function_t)(P1, P2, P3, P4);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3, P4, P5)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5);
		typedef R (function_t)(P1, P2, P3, P4, P5);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3, P4, P5, P6)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6, P7);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6, P7, P8);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> 
	struct FunctionTypeTrait<R(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R (*function_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	};

#if defined(_WIN32)
	template <typename R> 
	struct FunctionTypeTrait<R(__stdcall*)()>
	{
		typedef R (*functionPtr_t)();
		typedef R (function_t)();
	};
	template <typename R, typename P1> 
	struct FunctionTypeTrait<R(__stdcall*)(P1)>
	{
		typedef R (*functionPtr_t)(P1);
		typedef R (function_t)(P1);
	};
	template <typename R, typename P1, typename P2> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2)>
	{
		typedef R (*functionPtr_t)(P1, P2);
		typedef R (function_t)(P1, P2);
	};
	template <typename R, typename P1, typename P2, typename P3> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3);
		typedef R (function_t)(P1, P2, P3);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3, P4)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4);
		typedef R (function_t)(P1, P2, P3, P4);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3, P4, P5)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5);
		typedef R (function_t)(P1, P2, P3, P4, P5);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3, P4, P5, P6)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6, P7);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R (function_t)(P1, P2, P3, P4, P5, P6, P7, P8);
	};
	
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> 
	struct FunctionTypeTrait<R(__stdcall*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef R (*functionPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R (*function_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	};
//! \endcond
	
#endif
	//! \cond METHOD_TYPE_TRAITS
 	template<class C, class R>
	class MemberFunctor;
	template<class C, class R>
	class ConstMemberFunctor;

	
	template <class C, typename T> 
	struct MethodTypeTrait;

	template <class C, typename R> 
 	struct MethodTypeTrait<C, R()>
 	{
 		typedef R (C::*methodPtr_t)();
 		typedef R (method_t)();
		typedef MemberFunctor<C, R()> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1> 
 	struct MethodTypeTrait<C, R(P1)>
 	{
 		typedef R (C::*methodPtr_t)(P1);
 		typedef R (method_t)(P1);
		typedef MemberFunctor<C, R(P1)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2> 
 	struct MethodTypeTrait<C, R(P1, P2)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2);
 		typedef R (method_t)(P1, P2);
		typedef MemberFunctor<C, R(P1, P2)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3> 
 	struct MethodTypeTrait<C, R(P1, P2, P3)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3);
 		typedef R (method_t)(P1, P2, P3);
		typedef MemberFunctor<C, R(P1, P2, P3)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4> 
 	struct MethodTypeTrait<C, R(P1, P2, P3, P4)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4);
 		typedef R (method_t)(P1, P2, P3, P4);
		typedef MemberFunctor<C, R(P1, P2, P3, P4)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5> 
 	struct MethodTypeTrait<C, R(P1, P2, P3, P4, P5)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5);
 		typedef R (method_t)(P1, P2, P3, P4, P5);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> 
 	struct MethodTypeTrait<C, R(P1, P2, P3, P4, P5, P6)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6);
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> 
 	struct MethodTypeTrait<C, R(P1, P2, P3, P4, P5, P6, P7)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7);
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> 
 	struct MethodTypeTrait<C, R(P1, P2, P3, P4, P5, P6, P7, P8)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8);
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> 
 	struct MethodTypeTrait<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> memberFunctor_t;
 	};
	template <class C, typename R> 
	struct MethodTypeTrait<C, R(C::*)()>
	{
		typedef R (C::*methodPtr_t)();
		typedef R (method_t)();
		typedef MemberFunctor<C, R()> memberFunctor_t;
	};
	template <class C, typename R, typename P1> 
	struct MethodTypeTrait<C, R(C::*)(P1)>
	{
		typedef R (C::*methodPtr_t)(P1);
		typedef R (method_t)(P1);
		typedef MemberFunctor<C, R(P1)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2)>
	{
		typedef R (C::*methodPtr_t)(P1, P2);
		typedef R (method_t)(P1, P2);
		typedef MemberFunctor<C, R(P1, P2)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3);
		typedef R (method_t)(P1, P2, P3);
		typedef MemberFunctor<C, R(P1, P2, P3)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3, typename P4> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3, P4);
		typedef R (method_t)(P1, P2, P3, P4);
		typedef MemberFunctor<C, R(P1, P2, P3, P4)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5);
		typedef R (method_t)(P1, P2, P3, P4, P5);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6);
		typedef R (method_t)(P1, P2, P3, P4, P5, P6);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)> memberFunctor_t;
	};
	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> 
	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef MemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> memberFunctor_t;
	};
	template <class C, typename R> 
 	struct MethodTypeTrait<C, R(C::*)()const>
 	{
 		typedef R (C::*methodPtr_t)()const;
 		typedef R (method_t)();
		typedef ConstMemberFunctor<C, R()> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1> 
 	struct MethodTypeTrait<C, R(C::*)(P1)const>
 	{
 		typedef R (C::*methodPtr_t)(P1)const;
 		typedef R (method_t)(P1);
		typedef ConstMemberFunctor<C, R(P1)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2)const;
 		typedef R (method_t)(P1, P2);
		typedef ConstMemberFunctor<C, R(P1, P2)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3)const;
 		typedef R (method_t)(P1, P2, P3);
		typedef ConstMemberFunctor<C, R(P1, P2, P3)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4)const;
 		typedef R (method_t)(P1, P2, P3, P4);
		typedef ConstMemberFunctor<C, R(P1, P2, P3, P4)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5)const;
 		typedef R (method_t)(P1, P2, P3, P4, P5);
		typedef ConstMemberFunctor<C, R(P1, P2, P3, P4, P5)> memberFunctor_t;
	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6)const;
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6);
		typedef ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6, P7)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7)const;
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6, P7, P8)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8)const;
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8)> memberFunctor_t;
 	};
 	template <class C, typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> 
 	struct MethodTypeTrait<C, R(C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)const>
 	{
 		typedef R (C::*methodPtr_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9)const;
 		typedef R (method_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef ConstMemberFunctor<C, R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> memberFunctor_t;
 	};
	//! \endcond
 	

}
