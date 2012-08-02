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
 *Taken and modified from Stones of Nvwa:
 *      http://sourceforge.net/projects/nvwa
 *
 */


#pragma once

#include <new>
#include <stdio.h>
#include "dll_interface.h"
//#include "..\fast_mutex.h"


/**
 * @def _OVERRIDE_NEW_USE_ADDR2LINE
 *
 * Whether to use \e addr2line to convert a caller address to file/line
 * information.  Defining it to a non-zero value will enable the
 * conversion (automatically done if GCC is detected).  Defining it to
 * zero will disable the conversion.
 */
#ifndef _OVERRIDE_NEW_USE_ADDR2LINE
#ifdef __GNUC__
#define _OVERRIDE_NEW_USE_ADDR2LINE 1
#else
#define _OVERRIDE_NEW_USE_ADDR2LINE 0
#endif
#endif

#define OVERRIDE_NEW_NUM_PROJECT 100

//#define MINIMAL_INFO

namespace SK
{
	struct OVERRIDE_NEW_API Pair
	{
		std::string name;
		int size;

		Pair(std::string name_="", int size_=0);
	};
	class OVERRIDE_NEW_API MemoryMap
	{
	public:
		MemoryMap();

	public:
		Pair* find(std::string name);
		void add(const Pair& p);
		Pair& operator[](unsigned int i);
		const Pair& operator[](unsigned int i) const;
		Pair& at(unsigned int i);
		const Pair& at(unsigned int i) const;
		unsigned int size() const;

	private:
		Pair m_map[OVERRIDE_NEW_NUM_PROJECT];
		unsigned int m_size;
	};

	typedef MemoryMap memoryMap_t;
	typedef Pair pair_t;

	/* Prototypes */
	OVERRIDE_NEW_CAPI int check_leaks();
	OVERRIDE_NEW_CAPI int check_mem_corruption();
	OVERRIDE_NEW_CAPI unsigned int total_memory_usage();
	OVERRIDE_NEW_CAPI void log_memory_usage(const char* fileName);
	OVERRIDE_NEW_CAPI void* alloc_mem(size_t size, const char* project_name, const char* file, int line, bool is_array);
	OVERRIDE_NEW_CAPI void free_pointer(void* pointer, void* addr, bool is_array);
	OVERRIDE_NEW_CAPI void free_pointer_verbose(void* pointer, const char* file, int line);
	OVERRIDE_NEW_CAPI void print_position(const void* ptr, int line);
	#if _OVERRIDE_NEW_USE_ADDR2LINE
	OVERRIDE_NEW_CAPI bool print_position_from_addr(const void* addr);
	#endif
	OVERRIDE_NEW_CAPI bool print_position_from_addr(const void*);

	OVERRIDE_NEW_CAPI void process( void* pointer, const char* _M_project_name, const char* _M_file, const int _M_line);

	OVERRIDE_NEW_CAPI bool get_new_autocheck_flag();
	OVERRIDE_NEW_CAPI bool get_new_verbose_flag();
	OVERRIDE_NEW_CAPI FILE* get_new_output_fp();
	OVERRIDE_NEW_CAPI const char* get_new_progname();

	OVERRIDE_NEW_CAPI void set_new_autocheck_flag(bool flag);
	OVERRIDE_NEW_CAPI void set_new_verbose_flag(bool flag);
	OVERRIDE_NEW_CAPI void set_new_output_fp(FILE* output);
	OVERRIDE_NEW_CAPI void set_new_progname(const char* progname);
	OVERRIDE_NEW_CAPI void override_project_name(std::string name);
	OVERRIDE_NEW_CAPI void restore_project_name();

	OVERRIDE_NEW_CAPI int memory_usage_of(std::string project_name);
	OVERRIDE_NEW_CAPI memoryMap_t& memory_map();


	/**
	 * Counter class for on-exit leakage check.
	 *
	 * This technique is learnt from <em>The C++ Programming Language</em> by
	 * Bjarne Stroustup.
	 */
	class OVERRIDE_NEW_API __debug_new_counter
	{
		static int _S_count;
	public:
		__debug_new_counter();
		~__debug_new_counter();
	};
	/** Counting object for each file including memory_allocation.h. */
	static __debug_new_counter __debug_new_count;

}


