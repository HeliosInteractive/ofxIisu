/* Version: $Id: platform.h 7287 2010-01-19 22:25:05Z jeremie $ */
// Copyright (C) 2006-2010 by Softkinetic SA/NV
// All rights reserved.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#ifdef _WIN32
#pragma warning (push, 0)
#endif

//common std include
#include <assert.h>
#include <limits>
#include <stdexcept>


// Supported compiler
#define SK_COMPILER_MSVC 1
#define SK_COMPILER_GCC  2
#define SK_COMPILER_INTEL 3
#define SK_COMPILER_ARMCC 4

// -- unsupported yet
// #define SK_COMPILER_BORLAND 3
// #define SK_COMPILER_CWCC    4

// Supported platform
#define SK_PLATFORM_WIN32       	1
#define SK_PLATFORM_LINUX_x86   	2
#define SK_PLATFORM_LINUX_ARMv5 	3
#define SK_PLATFORM_LINUX_ARMv7	4
// -- unsupported yet
//SK_PLATFORM_LINUX_x86_64
//SK_PLATFORM_WIN64
//SK_PLATFORM_PS3
//SK_PLATFORM_X360
//SK_PLATFORM_FREEBSD
//SK_PLATFORM_OSX


//------------------NO RETURN ATTRIBUTE-------------------------------------

#ifdef _WIN32 // FIX THIS
	#define SK_NO_RETURN __declspec(noreturn)
#else
	#define SK_NO_RETURN __attribute__ ((noreturn))
#endif

/* Finds the compiler type and version.
*/
//TODO manage minimal compiler version supported
#if defined( _MSC_VER )
	#define SK_COMPILER SK_COMPILER_MSVC
	#define SK_COMPILER_VERSION _MSC_VER
#elif defined(__arm__) && defined(__ARMCC_VERSION)
	#define SK_COMPILER SK_COMPILER_ARMCC
	/* the format is PVbbbb - P is the major version, V is the minor version,
 	 bbbb is the build number*/
	#define SK_COMPILER_VERSION (__ARMCC_VERSION)
#elif defined( __GNUC__ )
	#define SK_COMPILER SK_COMPILER_GCC
	#define SK_COMPILER_VERSION (((__GNUC__)*100) + \
		(__GNUC_MINOR__*10) + \
		__GNUC_PATCHLEVEL__)
#else
	#error "Compilation error: Unsupported compiler."
#endif

/* Finds the platform - architecture
*/
#if defined( __WIN32__ ) || defined( _WIN32 )
	#define SK_PLATFORM SK_PLATFORM_WIN32
	#define SK_ENABLE_SSE
#elif defined(__linux__) || defined(__LINUX__)
	#define SK_PLATFORM_LINUX (1)

	#if (__TARGET_ARCH_ARM == 5 || __ARM_ARCH_5TEJ__ == 1 || __ARM_ARCH_5TE__ == 1 || __ARM_ARCH_5T__ == 1)
		#define SK_PLATFORM SK_PLATFORM_LINUX_ARMv5
	#elif (__TARGET_ARCH_ARM == 7 || __ARM_ARCH_7A__ == 1)
		#define SK_PLATFORM SK_PLATFORM_LINUX_ARMv7
	#elif defined(__x86) || defined(__x86__) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
		#define SK_PLATFORM SK_PLATFORM_LINUX_x86
		#define SK_ENABLE_SSE
	#else
		#error "Compilation error: Unsupported version of Linux platform."
	#endif
#else
	#error "Compilation error: Unsupported platform."
#endif

/* Finds the compilation mode
*/
#ifdef _DEBUG
	#define SK_DEBUG 1
#endif


//-------------------COMPILER SPECIFIC ---------------------------------------

// inlining
#if (SK_COMPILER == SK_COMPILER_MSVC)
	#if (SK_COMPILER_VERSION >= 1200)
		#define SK_ALWAYS_INLINE __forceinline
	#else
		#error "Compilation error: Unsupported compiler. Version must be >= VS 2005"
	#endif
#else
	#define SK_ALWAYS_INLINE __inline
#endif

#ifdef SK_DEBUG
	// no inline in debug excepted for SK_ALWAYS_INLINE
	#define	SK_INLINE
	#define	SK_FORCE_INLINE
	
	#if SK_COMPILER == SK_COMPILER_MSVC
		#if SK_COMPILER_VERSION >= 1200
			#define SK_ALWAYS_INLINE __forceinline
		#else
			#error "Compilation error: Unsupported compiler. Version must be >= VS 2005"
		#endif
	#else
		#define SK_ALWAYS_INLINE __inline
	#endif

#else

	#define	SK_INLINE inline
	/* See if we can use __forceinline or if we need to use __inline instead */
	#if (SK_COMPILER == SK_COMPILER_MSVC)
		#if (SK_COMPILER_VERSION >= 1200)
			#define SK_FORCE_INLINE __forceinline
		#else
			#error "Compilation error: Unsupported compiler. Version must be >= VS 2005"
		#endif
	#else
		#define SK_FORCE_INLINE __inline
	#endif
#endif

// pointer aliasing
#define SK_RESTRICT __restrict

//////////////////////////////////////////////////////////////////////////
// override is a non standard extension to the C++. It triggers warning
// 4481 when using warning level 4. In order not to get the warning we
// prevent it with a pragma.
#if (SK_COMPILER == SK_COMPILER_MSVC)
	#define SK_OVERRIDE \
		override \
	__pragma(warning(disable: 4481))
#else
	#define SK_OVERRIDE
#endif

// ---------- FLOATING POINT MIN / MAX ----------------

#include <float.h>

typedef float float32_t;
typedef double float64_t;

#define SK_REAL_MAX          3.402823466e+38F        /* max positive value */
#define SK_REAL_MIN          1.175494351e-38F        /* min positive value */
#define SK_REAL_EPSILON      1.192092896e-07F        /* smallest such that 1.0+REAL_EPSILON != 1.0 */
#if SK_PLATFORM == SK_PLATFORM_WIN32
	#define SK_REAL_IS_VALID(x)  ( _finite(x) && !_isnan(x) )
#else
	#include <math.h>
	#define SK_REAL_IS_VALID(x)  ( finite(x) && !isnan(x) )
#endif

// -------- CALLING CONVENTIONS ------------------------

#if defined(_WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
	#define SK_SDK_DECL  __stdcall
	#define SK_SDK_CDECL  __cdecl
#else 
	#define SK_SDK_DECL
	#define SK_SDK_CDECL
#endif

//-------------- DLL Export DEFINITIONS ------------
#if (SK_COMPILER == SK_COMPILER_MSVC) && !defined(STATIC_LIB)
	#define SK_DLL_EXPORT __declspec(dllexport)
	#define SK_DLL_IMPORT __declspec(dllimport)
	#define SK_DLL_LOCAL
	#define SK_DLL_PROTECTED
#elif (SK_COMPILER == SK_COMPILER_GCC || SK_COMPILER == SK_COMPILER_ARMCC)
	#if (SK_COMPILER_VERSION >= ((__GNUC__) * 100)) || (SK_COMPILER_VERSION >= (500000))
		#define SK_DLL_EXPORT 		__attribute__ ((visibility ("default")))
		#define SK_DLL_IMPORT 		__attribute__ ((visibility ("default")))
		#define SK_DLL_LOCAL 		__attribute__ ((visibility ("hidden")))
		#define SK_DLL_PROTECTED 	__attribute__ ((visibility ("protected")))
	#else
		#define SK_DLL_EXPORT
		#define SK_DLL_IMPORT
		#define SK_DLL_LOCAL
		#define SK_DLL_PROTECTED
	#endif
#else
	#define SK_DLL_EXPORT
	#define SK_DLL_IMPORT
	#define SK_DLL_LOCAL
	#define SK_DLL_PROTECTED
#endif

// TODO this is kind of broken here; FIX
// is seems that for the Win32 build this is not actually used
// it needs support for building dll vs. using dll
#if defined(DLL_EXPORT)
	#define SK_DLL_API SK_DLL_EXPORT
#elif defined(SK_HIDE_SYMBOLS)
	#define SK_DLL_API
#else
	#define SK_DLL_API SK_DLL_IMPORT
#endif

#define IISUSDK_API SK_DLL_API

// TODO FIX this as it does not seem to be proper at all and it's kind of bogus
// how should we treat that?
#ifndef PRODUCTION
	#define FOR_QTIISU_API SK_DLL_API
#else
	#define FOR_QTIISU_API
#endif

#define FOR_SKMOVIE_API SK_DLL_API

#if SK_PLATFORM == SK_PLATFORM_WIN32
	#define CAMERA_DLL_EXPORT SK_DLL_EXPORT
#else
#if defined(CAMERA_EXPORT)
	#define CAMERA_DLL_EXPORT SK_DLL_EXPORT
#else
	#define CAMERA_DLL_EXPORT SK_DLL_IMPORT
#endif
#endif // SK_PLATFORM == SK_PLATFORM_WIN32


#if SK_PLATFORM == SK_PLATFORM_WIN32

#ifdef CUSTOM_STD_INT
	#include CUSTOM_STD_INT
#else
	#include "SkIntTypes.h"
#endif // CUSTOM_STD_INT

#elif defined(SK_PLATFORM_LINUX)
	#include <stdint.h>
	#include <limits.h>
	#define INT32_MAX      (2147483647)
	#define UINT32_MAX     (4294967295U)
    typedef unsigned char   uchar;
    typedef unsigned short  ushort;
    typedef unsigned int    uint;
#else
    // what else is to do?
#endif // SK_PLATFORM == SK_PLATFORM_WIN32

#if defined(SK_ENABLE_SSE)
	#include <emmintrin.h>
	#include <xmmintrin.h>

	inline __m128i SK_mm_abs_epi16(__m128i a)
	{
		__m128i negative = _mm_cmplt_epi16(a, _mm_setzero_si128());
		return _mm_add_epi16(_mm_xor_si128(a, negative), _mm_srli_epi16(negative, 15));
	}

#endif


#ifdef __cplusplus
	#ifndef SK_TRACE
		#define SK_TRACE(X) throw std::runtime_error(X);
	#endif
#else
	#ifndef SK_TRACE
		#define SK_TRACE(X) printf(X);
	#endif
#endif

#ifdef _WIN32
#pragma warning (pop)
#endif

