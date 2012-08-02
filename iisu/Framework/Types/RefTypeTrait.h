#pragma once

#include <Platform/SkPlatform.h>


namespace SK
{
	/**
	 * \struct	RefTypeTrait
	 *
	 * \brief	Reference type trait. 
	 * 			
	 * 			This trait allows (given a type T) to add or remove const and & to the type. It also provide it equivalent type inside a varg.
	 */
	
	template <typename T> struct RefTypeTrait
	{
		typedef const T& add_const_ref_t;
		typedef const T add_const_t;
		typedef T& add_ref_t;
		typedef T remove_const_ref_t;
		typedef T remove_const_t;
		typedef T remove_ref_t;
		typedef T varg_t;

		static T& convert(T& t){return t;}
	};
	
	//! \cond REF_TYPE_TRAITS_SPECS
	template <typename T> struct RefTypeTrait<const T&>
	{
		typedef const T& add_const_ref_t;
		typedef const T add_const_t;
		typedef T& add_ref_t;
		typedef T remove_const_ref_t;
		typedef T& remove_const_t;
		typedef const T remove_ref_t;
		typedef T* varg_t;

		static T& convert(T* t){return *t;}
	};

	template <typename T> struct RefTypeTrait<const T>
	{
		typedef const T& add_const_ref_t;
		typedef const T add_const_t;
		typedef const T& add_ref_t;
		typedef T remove_const_ref_t;
		typedef T remove_const_t;
		typedef const T remove_ref_t;
		typedef T varg_t;

		static T& convert(T& t){return t;}
	};

	template <typename T> struct RefTypeTrait<T&>
	{
		typedef const T& add_const_ref_t;
		typedef const T& add_const_t;
		typedef T& add_ref_t;
		typedef T remove_const_ref_t;
		typedef T& remove_const_t;
		typedef T remove_ref_t;
		typedef T* varg_t;

		static T& convert(T* t){return *t;}
	};

	template <> struct RefTypeTrait<void>
	{
		typedef void add_const_ref_t;
		typedef void add_const_t;
		typedef void add_ref_t;
		typedef void remove_const_ref_t;
		typedef void remove_const_t;
		typedef void remove_ref_t;
		typedef void* varg_t;


//		static void& convert(T* t){return *t;}
	};


	template <typename R> struct RefTypeTrait<R()>
	{
		typedef R(add_const_ref_t)();
		typedef R(add_const_t)();
		typedef R(add_ref_t)();
		typedef R(remove_const_ref_t)();
		typedef R(remove_const_t)();
		typedef R(remove_ref_t)();
	};
	template <typename R, typename P1> struct RefTypeTrait<R(P1)>
	{
		typedef R(add_const_ref_t)(P1);
		typedef R(add_const_t)(P1);
		typedef R(add_ref_t)(P1);
		typedef R(remove_const_ref_t)(P1);
		typedef R(remove_const_t)(P1);
		typedef R(remove_ref_t)(P1);
	};
	template <typename R, typename P1, typename P2> struct RefTypeTrait<R(P1, P2)>
	{
		typedef R(add_const_ref_t)(P1, P2);
		typedef R(add_const_t)(P1, P2);
		typedef R(add_ref_t)(P1, P2);
		typedef R(remove_const_ref_t)(P1, P2);
		typedef R(remove_const_t)(P1, P2);
		typedef R(remove_ref_t)(P1, P2);
	};
	template <typename R, typename P1, typename P2, typename P3> struct RefTypeTrait<R(P1, P2, P3)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3);
		typedef R(add_const_t)(P1, P2, P3);
		typedef R(add_ref_t)(P1, P2, P3);
		typedef R(remove_const_ref_t)(P1, P2, P3);
		typedef R(remove_const_t)(P1, P2, P3);
		typedef R(remove_ref_t)(P1, P2, P3);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4> struct RefTypeTrait<R(P1, P2, P3, P4)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3, P4);
		typedef R(add_const_t)(P1, P2, P3, P4);
		typedef R(add_ref_t)(P1, P2, P3, P4);
		typedef R(remove_const_ref_t)(P1, P2, P3, P4);
		typedef R(remove_const_t)(P1, P2, P3, P4);
		typedef R(remove_ref_t)(P1, P2, P3, P4);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> struct RefTypeTrait<R(P1, P2, P3, P4, P5)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3, P4, P5);
		typedef R(add_const_t)(P1, P2, P3, P4, P5);
		typedef R(add_ref_t)(P1, P2, P3, P4, P5);
		typedef R(remove_const_ref_t)(P1, P2, P3, P4, P5);
		typedef R(remove_const_t)(P1, P2, P3, P4, P5);
		typedef R(remove_ref_t)(P1, P2, P3, P4, P5);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> struct RefTypeTrait<R(P1, P2, P3, P4, P5, P6)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3, P4, P5, P6);
		typedef R(add_const_t)(P1, P2, P3, P4, P5, P6);
		typedef R(add_ref_t)(P1, P2, P3, P4, P5, P6);
		typedef R(remove_const_ref_t)(P1, P2, P3, P4, P5, P6);
		typedef R(remove_const_t)(P1, P2, P3, P4, P5, P6);
		typedef R(remove_ref_t)(P1, P2, P3, P4, P5, P6);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> struct RefTypeTrait<R(P1, P2, P3, P4, P5, P6, P7)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(add_const_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(add_ref_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(remove_const_ref_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(remove_const_t)(P1, P2, P3, P4, P5, P6, P7);
		typedef R(remove_ref_t)(P1, P2, P3, P4, P5, P6, P7);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> struct RefTypeTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(add_const_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(add_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(remove_const_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(remove_const_t)(P1, P2, P3, P4, P5, P6, P7, P8);
		typedef R(remove_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8);
	};
	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> struct RefTypeTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>
	{
		typedef R(add_const_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(add_const_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(add_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(remove_const_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(remove_const_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
		typedef R(remove_ref_t)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	};

	//! \endcond
	
}
