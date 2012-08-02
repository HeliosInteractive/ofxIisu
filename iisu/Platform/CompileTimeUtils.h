#pragma once

//-------------- ASSERT AND ERRORS -------------
#include <assert.h>

/** 
  @def SK_STR(expression)
  Creates a string from the expression. 

  <CODE>STR(this becomes a string)\verbatim<PRE>\endverbatim evaluates the same as \verbatim<CODE>\endverbatim"this becomes a string"</CODE>
 */
#define SK_STR(x) # x
 /** 
  @def SK_QUOTE(expression)
  Creates a string from the expression but evaluate any nested macro before
  then
  #define ONE 1
  SK_STR(ONE) = "ONE"
  SK_QUOTE(ONE) = "1"

 */
#define SK_QUOTE(x) SK_STR(x)

//! Macro to get file name and line number. ex: "Vector3.h(133) : "
#define SK_FILE_LINE __FILE__ "(" SK_QUOTE(__LINE__) ") : "

#ifdef __cplusplus
template <bool ON_CONSTRAINT> struct SK_STATIC_ASSERT_FAILED;
template <> struct SK_STATIC_ASSERT_FAILED<true> { enum { value = 1 }; };

//! check assertion at compile time
#define SK_STATIC_ASSERT(expr) typedef char __static_assert_t_ ## __LINE__ [ SK_STATIC_ASSERT_FAILED<(expr)?true:false>::value ]


//-------------- COMPILE-TIME PROGRAMMING -------------

//////////////////////////////////////////////////////////////////////////
/// Check if D inherits from B.
///
/// There are two ways to check whether D inherits from B. The first one is to test the
/// compile-time variable SK_IsClassDerivedFrom::value. The second one enforces the
/// inheritance (thus it is not a test) via inheriting from SK_IsClassDerivedFrom<D, B>,
/// where D would typically be a template argument T and B a concrete class.
template <class D, class B>
class SK_IsClassDerivedFrom
{
private:
	class Yes { char a[1]; };
	class No { char a[10]; };

	static Yes Test( B* ); // undefined
	static No Test( ... ); // undefined

	//		static void Constraints(D* p) {B* pb = p; pb = p;}

public:
	static const bool value = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes);

	//		SK_IsClassDerivedFrom() {void(*p)(D*) = Constraints;}
};

// Specialization for pointers.
template <class D, class B>
class SK_IsClassDerivedFrom<D*, B>
{
private:
	class Yes { char a[1]; };
	class No { char a[10]; };

	static Yes Test( B* ); // undefined
	static No Test( ... ); // undefined

	//		static void Constraints(D* p) {B* pb = p; pb = p;} // FIX THIS

public:
	static const bool value = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes);

	//		SK_IsClassDerivedFrom() {void(*p)(D*) = Constraints;} // FIX THIS
};

#define SK_IS_CLASS_DERIVED_FROM(B, D) (SK_IsClassDerivedFrom< D, B >::value) 

//////////////////////////////////////////////////////////////////////////
/// Compare 2 types.
template<typename A, typename B> struct SK_IsType { static const bool value = false; };
template<typename A> struct SK_IsType<A,A> { static const bool value = true; };

#define SK_IS_TYPE(A, B) (SK_IsType< A, B >::value)

#endif
