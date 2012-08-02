// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2004-2008 Wu Yongwei <adah at users dot sourceforge dot net>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 *    not claim that you wrote the original software.  If you use this
 *    software in a product, an acknowledgement in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must
 *    not be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 * Taken and modified from Stones of Nvwa:
 *      http://sourceforge.net/projects/nvwa
 *
 */

#pragma once

#include <new>
#include <stdio.h>
#include <assert.h>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#ifdef __unix__
#include <alloca.h>
#endif
#ifdef _WIN32
#include <malloc.h>
#endif

//#define _WINSOCKAPI_    // stops windows.h including winsock.h

#include "fast_mutex.h"
#include "static_assert.h"

#include <tchar.h>
#include <windows.h>

#include "defs.h"

#undef min
#undef max

#ifndef PROJECT_NAME
#define PROJECT_NAME ""
#endif


#define IMPORT_OVERRIDE_NEW_FUNCTION(A) \
	A##_func =(A##_func_t) GetProcAddress(debugNewDll, #A ); \
	if( ! A##_func ) \
{ \
	assert(0); \
	FreeLibrary(debugNewDll); \
	return false; \
}

namespace
{
	typedef void* (*alloc_mem_func_t)(size_t, const char*, const char*, int, bool);
	typedef void (*free_pointer_func_t)(void* pointer, void* addr, bool is_array);
	typedef void (*free_pointer_verbose_func_t)(void*, const char*, int);
	typedef void (*process_func_t)(void*, const char*, const char*, int);
	typedef void (*override_project_name_func_t)(std::string);
	typedef void (*restore_project_name_func_t)();

	alloc_mem_func_t alloc_mem_func;
	free_pointer_func_t free_pointer_func;
	free_pointer_verbose_func_t free_pointer_verbose_func;
	process_func_t process_func;
	override_project_name_func_t override_project_name_func;
	restore_project_name_func_t restore_project_name_func;

	inline bool loadFunc()
	{
		if(alloc_mem_func == 0)
		{
			HMODULE debugNewDll = LoadLibrary(_T("memory_manager-d.dll"));
			if( !debugNewDll ) {return 0;}

			IMPORT_OVERRIDE_NEW_FUNCTION(alloc_mem);
			IMPORT_OVERRIDE_NEW_FUNCTION(free_pointer);
			IMPORT_OVERRIDE_NEW_FUNCTION(free_pointer_verbose);
			IMPORT_OVERRIDE_NEW_FUNCTION(process);
			IMPORT_OVERRIDE_NEW_FUNCTION(override_project_name);
			IMPORT_OVERRIDE_NEW_FUNCTION(restore_project_name);
		}
		return true;
	}

	static const struct _Init 
	{
		_Init() 
		{
			if(!loadFunc())  
				std::cout<<"Error: cannot load memory_manager-d.dll"<<std::endl;
		}
	}_init;
}


inline void* operator new(size_t size, const char* file, int line)
{
//	if(!loadFunc())return 0;
    void* ptr = alloc_mem_func(size, PROJECT_NAME, file, line, false);
#if _OVERRIDE_NEW_STD_OPER_NEW
    if (ptr)
        return ptr;
    else
        throw std::bad_alloc();
#else
    return ptr;
#endif
}

inline void* operator new[](size_t size, const char* file, int line)
{
//	if(!loadFunc())return 0;

    void* ptr = alloc_mem_func(size, PROJECT_NAME, file, line, true);
#if _OVERRIDE_NEW_STD_OPER_NEW
    if (ptr)
        return ptr;
    else
        throw std::bad_alloc();
#else
    return ptr;
#endif
}

inline void* operator new(size_t size) throw(std::bad_alloc)
{
    return operator new(size, (char*)_OVERRIDE_NEW_CALLER_ADDRESS, 0);
}

inline void* operator new[](size_t size) throw(std::bad_alloc)
{
    return operator new[](size, (char*)_OVERRIDE_NEW_CALLER_ADDRESS, 0);
}

#if !defined(__BORLANDC__) || __BORLANDC__ > 0x551
inline void* operator new(size_t size, const std::nothrow_t&) throw()
{
	return alloc_mem_func(size, PROJECT_NAME, (char*)_OVERRIDE_NEW_CALLER_ADDRESS, 0, false);
}

inline void* operator new[](size_t size, const std::nothrow_t&) throw()
{
    return alloc_mem_func(size, PROJECT_NAME, (char*)_OVERRIDE_NEW_CALLER_ADDRESS, 0, true);
}
#endif

inline void operator delete(void* pointer) throw()
{
    free_pointer_func(pointer, _OVERRIDE_NEW_CALLER_ADDRESS, false);
}

inline void operator delete[](void* pointer) throw()
{
    free_pointer_func(pointer, _OVERRIDE_NEW_CALLER_ADDRESS, true);
}

#if HAVE_PLACEMENT_DELETE
inline void operator delete(void* pointer, const char* file, int line) throw()
{
	free_pointer_verbose_func(pointer, file, line);
    operator delete(pointer);
}

inline void operator delete[](void* pointer, const char* file, int line) throw()
{
	free_pointer_verbose_func(pointer, file, line);
	operator delete[](pointer);
}

inline void operator delete(void* pointer, const std::nothrow_t&) throw()
{
    operator delete(pointer, (char*)_OVERRIDE_NEW_CALLER_ADDRESS, 0);
}

inline void operator delete[](void* pointer, const std::nothrow_t&) throw()
{
    operator delete[](pointer, (char*)_OVERRIDE_NEW_CALLER_ADDRESS, 0);
}
#endif // HAVE_PLACEMENT_DELETE
#if defined(_MSC_VER) && _MSC_VER < 1300
// MSVC 6 requires the following declarations; or the non-placement
// new[]/delete[] will not compile.
void* operator new[](size_t) throw(std::bad_alloc);
void operator delete[](void*) throw();
#endif





/**
 * @def _OVERRIDE_NEW_REDEFINE_NEW
 *
 * Macro to indicate whether redefinition of \c new is wanted.  If one
 * wants to define one's own <code>operator new</code>, to call
 * <code>operator new</code> directly, or to call placement \c new, it
 * should be defined to \c 0 to alter the default behaviour.  Unless, of
 * course, one is willing to take the trouble to write something like:
 * @code
 * # ifdef new
 * #   define _NEW_REDEFINED
 * #   undef new
 * # endif
 *
 * // Code that uses new is here
 *
 * # ifdef _NEW_REDEFINED
 * #   ifdef OVERRIDE_NEW
 * #     define new OVERRIDE_NEW
 * #   endif
 * #   undef _NEW_REDEFINED
 * # endif
 * @endcode
 */
#ifndef _OVERRIDE_NEW_REDEFINE_NEW
#define _OVERRIDE_NEW_REDEFINE_NEW 1
#endif


/**
 * @def OVERRIDE_NEW
 *
 * Macro to catch file/line information on allocation.  If
 * #_OVERRIDE_NEW_REDEFINE_NEW is \c 0, one can use this macro directly;
 * otherwise \c new will be defined to it, and one must use \c new
 * instead.
 */
#define OVERRIDE_NEW __debug_new_recorder(PROJECT_NAME, __FILE__, __LINE__) ->* new

# if _OVERRIDE_NEW_REDEFINE_NEW
#   define new OVERRIDE_NEW
# endif
# ifdef _OVERRIDE_NEW_EMULATE_MALLOC
#   include <stdlib.h>
#   ifdef new
#     define malloc(s) ((void*)(new char[s]))
#   else
#     define malloc(s) ((void*)(OVERRIDE_NEW char[s]))
#   endif
#   define free(p) delete[] (char*)(p)
# endif



/**
 * Recorder class to remember the call context.
 *
 * The idea comes from <a href="http://groups.google.com/group/comp.lang.c++.moderated/browse_thread/thread/7089382e3bc1c489/85f9107a1dc79ee9?#85f9107a1dc79ee9">Greg Herlihy's post</a> in comp.lang.c++.moderated.
 */
class __debug_new_recorder
{
	const char* _M_project_name;
	const char* _M_file;
    const int   _M_line;
    void _M_process(void* pointer);

public:
    /**
     * Constructor to remember the call context.  The information will
     * be used in __debug_new_recorder::operator->*.
     */
    __debug_new_recorder(const char* project_name, const char* file, int line)
        : _M_project_name(project_name),_M_file(file), _M_line(line) {}
    /**
     * Operator to write the context information to memory.
     * <code>operator->*</code> is chosen because it has the right
     * precedence, it is rarely used, and it looks good: so people can
     * tell the special usage more quickly.
     */
    template <class _Tp> _Tp* operator->*(_Tp* pointer)
    {
		process_func(pointer, _M_project_name, _M_file, _M_line); 
		return pointer; 
	}
private:
    __debug_new_recorder(const __debug_new_recorder&);
    __debug_new_recorder& operator=(const __debug_new_recorder&);
};


#define OVERRIDE_PROJECT_NAME(x) override_project_name_func(x)
#define RESTORE_PROJECT_NAME() restore_project_name_func()