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

#include <map>
#include <string>
#include <fstream>
#include <new>
#include <assert.h>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#ifdef __unix__
#include <alloca.h>
#endif
#ifdef _WIN32
#include <malloc.h>
#endif
#include "static_assert.h"
#include "fast_mutex.h"

#include "defs.h"




#undef  _OVERRIDE_NEW_EMULATE_MALLOC
#undef  _OVERRIDE_NEW_REDEFINE_NEW
/**
 * Macro to indicate whether redefinition of \c new is wanted.  Here it
 * is defined to \c 0 to disable the redefinition of \c new.
 */
#define _OVERRIDE_NEW_REDEFINE_NEW 0
#include "memory_allocation.h"

/**
 * Gets the aligned value of memory block size.
 */
#define align(s) \
        (((s) + _OVERRIDE_NEW_ALIGNMENT - 1) & ~(_OVERRIDE_NEW_ALIGNMENT - 1))

#include "StackWalker.h"

namespace SK
{


	/**
	 * Structure to store the position information where \c new occurs.
	 */
	struct new_ptr_list_t
	{
#ifndef MINIMAL_INFO
		new_ptr_list_t*     next;
		new_ptr_list_t*     prev;
#endif
		size_t              size;
#ifndef MINIMAL_INFO
		union
		{
	#if _OVERRIDE_NEW_FILENAME_LEN == 0
		const char*         file;
	#else
		char                file[_OVERRIDE_NEW_FILENAME_LEN];
	#endif
		void*               addr;
		};
#endif
		char                project[_OVERRIDE_NEW_FILENAME_LEN];
#ifndef MINIMAL_INFO
		unsigned            line      :31;
		unsigned            is_array  :1;
		unsigned            magic;
		char                module[_OVERRIDE_NEW_FILENAME_LEN];
		char                function[_OVERRIDE_NEW_FILENAME_LEN];
#endif
	};

//	static std::map<std::string,unsigned int> memory_per_project = std::map<std::string,unsigned int>();


//	typedef memoryMap_t::iterator memoryMapIter_t;

	static memoryMap_t memory_per_project;


	/**
	 * Magic number for error detection.
	 */
	const unsigned MAGIC = 0x4442474E;


	/**
	 * The extra memory allocated by <code>operator new</code>.
	 */
	const int ALIGNED_LIST_ITEM_SIZE = align(sizeof(new_ptr_list_t));

	/**
	 * List of all new'd pointers.
	 */
	static new_ptr_list_t new_ptr_list = {
#ifndef MINIMAL_INFO
		&new_ptr_list,
		&new_ptr_list,
#endif
		0,
#ifndef MINIMAL_INFO
		{
	#if _OVERRIDE_NEW_FILENAME_LEN == 0
			NULL
	#else
			""
	#endif
		},
#endif
		"",
#ifndef MINIMAL_INFO
		0,
		0,
		MAGIC
#endif
	};

	/**
	 * The mutex guard to protect simultaneous access to the pointer list.
	 */
	fast_mutex new_ptr_lock;

	/**
	 * The mutex guard to protect simultaneous output to #new_output_fp.
	 */
	fast_mutex new_output_lock;

	/**
	 * Total memory allocated in bytes.
	 */
	size_t total_mem_alloc = 0;

	/**
	 * Flag to control whether #check_leaks will be automatically called on
	 * program exit.
	 */
	bool new_autocheck_flag = true;

	/**
	 * Flag to control whether verbose messages are output.
	 */
	bool new_verbose_flag = false;

	/**
	 * Pointer to the output stream.  The default output is \e stderr, and
	 * one may change it to a user stream if needed (say, #new_verbose_flag
	 * is \c true and there are a lot of (de)allocations).
	 */
	FILE* new_output_fp = stderr;//fopen("d:\\memory_log.txt","w");

	/**
	 * Pointer to the program name.  Its initial value is the macro
	 * #_OVERRIDE_NEW_PROGNAME.  You should try to assign the program path to
	 * it early in your application.  Assigning <code>argv[0]</code> to it
	 * in \e main is one way.  If you use \e bash or \e ksh (or similar),
	 * the following statement is probably what you want:
	 * `<code>new_progname = getenv("_");</code>'.
	 */
	const char* new_progname = _OVERRIDE_NEW_PROGNAME;

	bool get_new_autocheck_flag(){return new_autocheck_flag;}
	bool get_new_verbose_flag(){return new_verbose_flag;}
	FILE* get_new_output_fp(){return new_output_fp;}
	const char* get_new_progname(){return new_progname;}

	void set_new_autocheck_flag(bool flag){new_autocheck_flag=flag;}
	void set_new_verbose_flag(bool flag){new_verbose_flag=flag;}
	void set_new_output_fp(FILE* output){new_output_fp=output;}
	void set_new_progname(const char* progname){new_progname=progname;}

	std::string project_name_override = "";


	void override_project_name(std::string name)
	{
		project_name_override=name;
	}

	void restore_project_name()
	{
		project_name_override="";
	}


	#if _OVERRIDE_NEW_USE_ADDR2LINE
	/**
	 * Tries printing the position information from an instruction address.
	 * This is the version that uses \e addr2line.
	 *
	 * @param addr  the instruction address to convert and print
	 * @return      \c true if the address is converted successfully (and
	 *              the result is printed); \c false if no useful
	 *              information is got (and nothing is printed)
	 */
	bool print_position_from_addr(const void* addr)
	{
		static const void* last_addr = NULL;
		static char last_info[256] = "";
		if (addr == last_addr)
		{
			if (last_info[0] == '\0')
				return false;
			fprintf(new_output_fp, "%s", last_info);
			return true;
		}
		if (new_progname)
		{
			const char addr2line_cmd[] = "addr2line -e ";
	#if   defined(__CYGWIN__) || defined(_WIN32)
			const int  exeext_len = 4;
	#else
			const int  exeext_len = 0;
	#endif
	#if  !defined(__CYGWIN__) && defined(__unix__)
			const char ignore_err[] = " 2>/dev/null";
	#elif defined(__CYGWIN__) || \
			(defined(_WIN32) && defined(WINVER) && WINVER >= 0x0500)
			const char ignore_err[] = " 2>nul";
	#else
			const char ignore_err[] = "";
	#endif
			char* cmd = (char*)alloca(strlen(new_progname)
									  + exeext_len
									  + sizeof addr2line_cmd - 1
									  + sizeof ignore_err - 1
									  + sizeof(void*) * 2
									  + 4 /* SP + "0x" + null */);
			strcpy(cmd, addr2line_cmd);
			strcpy(cmd + sizeof addr2line_cmd - 1, new_progname);
			size_t len = strlen(cmd);
	#if   defined(__CYGWIN__) || defined(_WIN32)
			if (len <= 4
					|| (strcmp(cmd + len - 4, ".exe") != 0 &&
						strcmp(cmd + len - 4, ".EXE") != 0))
			{
				strcpy(cmd + len, ".exe");
				len += 4;
			}
	#endif
			sprintf(cmd + len, " %p%s", addr, ignore_err);
			FILE* fp = popen(cmd, "r");
			if (fp)
			{
				char buffer[sizeof last_info] = "";
				len = 0;
				if (fgets(buffer, sizeof buffer, fp))
				{
					len = strlen(buffer);
					if (buffer[len - 1] == '\n')
						buffer[--len] = '\0';
				}
				int res = pclose(fp);
				// Display the file/line information only if the command
				// is executed successfully and the output points to a
				// valid position, but the result will be cached if only
				// the command is executed successfully.
				if (res == 0 && len > 0)
				{
					last_addr = addr;
					if (buffer[len - 1] == '0' && buffer[len - 2] == ':')
						last_info[0] = '\0';
					else
					{
						fprintf(new_output_fp, "%s", buffer);
						strcpy(last_info, buffer);
						return true;
					}
				}
			}
		}
		return false;
	}
	#else
	/**
	 * Tries printing the position information from an instruction address.
	 * This is the stub version that does nothing at all.
	 *
	 * @return      \c false always
	 */
	bool print_position_from_addr(const void*)
	{
		return false;
	}
	#endif // _OVERRIDE_NEW_USE_ADDR2LINE

	/**
	 * Prints the position information of a memory operation point.  When \c
	 * _OVERRIDE_NEW_USE_ADDR2LINE is defined to a non-zero value, this
	 * function will try to convert a given caller address to file/line
	 * information with \e addr2line.
	 *
	 * @param ptr   source file name if \e line is non-zero; caller address
	 *              otherwise
	 * @param line  source line number if non-zero; indication that \e ptr
	 *              is the caller address otherwise
	 */
	void print_position(const void* ptr, int line)
	{
		if (line != 0)          // Is file/line information present?
		{
			fprintf(new_output_fp, "%s:%d", (const char*)ptr, line);
		}
		else if (ptr != NULL)   // Is caller address present?
		{
			if (!print_position_from_addr(ptr)) // Fail to get source position?
				fprintf(new_output_fp, "%p", ptr);
		}
		else                    // No information is present
		{
			fprintf(new_output_fp, "<Unknown>");
		}
	}

	#if _OVERRIDE_NEW_TAILCHECK
	/**
	 * Checks whether the padding bytes at the end of a memory block is
	 * tampered with.
	 *
	 * @param ptr   pointer to a new_ptr_list_t struct
	 * @return      \c true if the padding bytes are untouched; \c false
	 *              otherwise
	 */
	static bool check_tail(new_ptr_list_t* ptr)
	{
		const unsigned char* const pointer = (unsigned char*)ptr +
								ALIGNED_LIST_ITEM_SIZE + ptr->size;
		for (int i = 0; i < _OVERRIDE_NEW_TAILCHECK; ++i)
			if (pointer[i] != _OVERRIDE_NEW_TAILCHECK_CHAR)
				return false;
		return true;
	}
	#endif

	StackWalker sw;

	StackWalker::Trace* get_real_trace()
	{
		StackWalker::Trace* full_trace = sw.GetCallStack();

		if(full_trace == NULL) return NULL;
		if(0 != strcmp(full_trace->entry.name, ""))
		{
			delete full_trace;
			return NULL;
		}
		// remove stack trace of stack walker and this fuction
		StackWalker::Trace* realTrace = full_trace->next->next->next;
		full_trace->next->next->next = NULL;
		delete full_trace;

		return realTrace;
	}



	/**
	 * Allocates memory and initializes control data.
	 *
	 * @param size      size of the required memory block
	 * @param file      null-terminated string of the file name
	 * @param line      line number
	 * @param is_array  boolean value whether this is an array operation
	 * @return          pointer to the user-requested memory area; \c NULL
	 *                  if memory allocation is not successful
	 */
	void* alloc_mem(size_t size, const char* project_name, const char* file, int line, bool is_array)
	{
		assert(line >= 0);

		// Check dll bounds
#ifndef MINIMAL_INFO
		StackWalker::Trace* trace = get_real_trace();

		if(NULL != trace)
		{
			std::string file_path(trace->entry.lineFileName);
			size_t found = file_path.find_last_of("/\\");

			std::string file_name = file_path.substr(found+1);

			if(file_name != "new_override.h")
			{
				assert(false);
			}
		}
#endif
		STATIC_ASSERT((_OVERRIDE_NEW_ALIGNMENT & (_OVERRIDE_NEW_ALIGNMENT - 1)) == 0,
					  Alignment_must_be_power_of_two);
		STATIC_ASSERT(_OVERRIDE_NEW_TAILCHECK >= 0, Invalid_tail_check_length);
		size_t s = size + ALIGNED_LIST_ITEM_SIZE + _OVERRIDE_NEW_TAILCHECK;
		new_ptr_list_t* ptr = (new_ptr_list_t*)malloc(s);
		if (ptr == NULL)
		{
	#if _OVERRIDE_NEW_STD_OPER_NEW
			return NULL;
	#else
			fast_mutex_autolock lock(new_output_lock);
			fprintf(new_output_fp,
					"Out of memory when allocating %u bytes\n",
					size);
			fflush(new_output_fp);
			_OVERRIDE_NEW_ERROR_ACTION;
	#endif
		}
		void* pointer = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
#ifndef MINIMAL_INFO
	#if _OVERRIDE_NEW_FILENAME_LEN == 0
		ptr->file = file;
	#else
		if (line)
			strncpy(ptr->file, file, _OVERRIDE_NEW_FILENAME_LEN - 1)
					[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';
		else
			ptr->addr = (void*)file;
	#endif
#endif
		if(project_name_override=="")
			strncpy(ptr->project, project_name, _OVERRIDE_NEW_FILENAME_LEN - 1)
			[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';
		else
			strncpy(ptr->project, project_name_override.c_str(), _OVERRIDE_NEW_FILENAME_LEN - 1)
			[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';
#ifndef MINIMAL_INFO
		ptr->line = line;
		ptr->is_array = is_array;
#endif
		ptr->size = size;
#ifndef MINIMAL_INFO
		ptr->magic = MAGIC;
		{
			fast_mutex_autolock lock(new_ptr_lock);
			ptr->prev = new_ptr_list.prev;
			ptr->next = &new_ptr_list;
			new_ptr_list.prev->next = ptr;
			new_ptr_list.prev = ptr;
		}

			ptr->module[0] = '\0';

		if(trace != NULL)
		{
			strncpy(ptr->module, trace->entry.moduleName, _OVERRIDE_NEW_FILENAME_LEN - 1)
				[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';

			StackWalker::Trace* it = trace->next;
			for(; it != NULL; it = it->next)
			{
				std::string s(it->entry.lineFileName);
				if(s.find("iisusdk") != std::string::npos)
					break;
			}
			if(NULL == it)
			{
				fast_mutex_autolock lock(new_output_lock);
				for(it = trace; it != NULL; it = it->next)
				{
					fprintf(new_output_fp, "\tmodule name: %s -- %s (%d): %s\n", it->entry.moduleName, it->entry.lineFileName, it->entry.lineNumber, it->entry.name);
				}
				fflush(new_output_fp);
				_OVERRIDE_NEW_ERROR_ACTION;
			}
			ptr->line = it->entry.lineNumber;
			strncpy(ptr->function, trace->entry.name, _OVERRIDE_NEW_FILENAME_LEN - 1)
				[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';

			std::string file_path(it->entry.lineFileName);

			size_t found = file_path.find_last_of("/\\");
			const char* file_name = file_path.substr(found+1).c_str();

			strncpy(ptr->file, file_name, _OVERRIDE_NEW_FILENAME_LEN - 1)
				[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';

			delete trace;
		}

#endif
	#if _OVERRIDE_NEW_TAILCHECK
		memset((char*)pointer + size, _OVERRIDE_NEW_TAILCHECK_CHAR,
									  _OVERRIDE_NEW_TAILCHECK);
	#endif
#ifndef MINIMAL_INFO
		if (new_verbose_flag)
		{
			fast_mutex_autolock lock(new_output_lock);
			fprintf(new_output_fp,
					"new%s: %s -> allocated %p (size %u, ",
					is_array ? "[]" : "",ptr->project,
					pointer, size);
			if (line != 0)
				print_position(ptr->file, ptr->line);
			else
				print_position(ptr->addr, ptr->line);
			fprintf(new_output_fp, ")\n");
		}
#endif
		total_mem_alloc += size;

		pair_t* f=memory_per_project.find(ptr->project);
		if(f==0) memory_per_project.add(pair_t(ptr->project,ptr->size));
		else f->size+=size;
		
		return pointer;
	}

	/**
	 * Frees memory and adjusts pointers.
	 *
	 * @param pointer   pointer to delete
	 * @param addr      pointer to the caller
	 * @param is_array  flag indicating whether it is invoked by a
	 *                  <code>delete[]</code> call
	 */
	void free_pointer(void* pointer, void* addr, bool is_array)
	{
		if (pointer == NULL)
			return;
		new_ptr_list_t* ptr =
				(new_ptr_list_t*)((char*)pointer - ALIGNED_LIST_ITEM_SIZE);
#ifndef MINIMAL_INFO
		if (ptr->magic != MAGIC)
		{
			{
				fast_mutex_autolock lock(new_output_lock);
				fprintf(new_output_fp, "delete%s: %s -> invalid pointer %p (",
						is_array ? "[]" : "",ptr->project, pointer);
				print_position(addr, 0);
				fprintf(new_output_fp, ")\n");
			}
			check_mem_corruption();
			fflush(new_output_fp);
			_OVERRIDE_NEW_ERROR_ACTION;
		}
		if (is_array != (bool)ptr->is_array)
		{
			const char* msg;
			if (is_array)
				msg = "delete[] after new";
			else
				msg = "delete after new[]";
			fast_mutex_autolock lock(new_output_lock);
			fprintf(new_output_fp,
					"%s: pointer %p (size %u)\n\tat ",
					msg,
					(char*)ptr + ALIGNED_LIST_ITEM_SIZE,
					ptr->size);
			print_position(addr, 0);
			fprintf(new_output_fp, "\n\toriginally allocated at ");
			if (ptr->line != 0)
				print_position(ptr->file, ptr->line);
			else
				print_position(ptr->addr, ptr->line);
			fprintf(new_output_fp, "by %s \n",ptr->project);
			fflush(new_output_fp);
			_OVERRIDE_NEW_ERROR_ACTION;
		}
	#if _OVERRIDE_NEW_TAILCHECK
		if (!check_tail(ptr))
		{
			check_mem_corruption();
			fflush(new_output_fp);
			_OVERRIDE_NEW_ERROR_ACTION;
		}
	#endif
#endif
		{
			fast_mutex_autolock lock(new_ptr_lock);

			pair_t* f=memory_per_project.find(ptr->project);
			if(f!=NULL) f->size-=ptr->size;

			total_mem_alloc -= ptr->size;
#ifndef MINIMAL_INFO
			ptr->magic = 0;
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
#endif
		}
#ifndef MINIMAL_INFO

		StackWalker::Trace* trace = get_real_trace();
		if(trace != NULL)
		{
		
			if(0 == strcmp("", ptr->module))
			{
				for(StackWalker::Trace* it = trace; NULL != it; it = it->next)
				{
					fprintf(new_output_fp, "\tmodule name: %s -- %s (%d): %s\n", it->entry.moduleName, it->entry.lineFileName, it->entry.lineNumber, it->entry.name);
				}
			}
			else
			{
				if(0 != strcmp(trace->entry.moduleName, ptr->module))
				{
					fast_mutex_autolock lock(new_output_lock);
					fprintf(new_output_fp,
						"delete%s: %s -> freed %p from %s while allocated from %s\n",
						is_array ? "[]" : "",ptr->project,
						(char*)ptr + ALIGNED_LIST_ITEM_SIZE,
						trace->entry.moduleName, ptr->module);

					for(StackWalker::Trace* it = trace; NULL != it; it = it->next)
					{
						fprintf(new_output_fp, "\tmodule name: %s -- %s (%d): %s\n", it->entry.moduleName, it->entry.lineFileName, it->entry.lineNumber, it->entry.name);
					}

					fflush(new_output_fp);
					_OVERRIDE_NEW_ERROR_ACTION;
				}
			}

			delete trace;
		}

		if (new_verbose_flag)
		{
			fast_mutex_autolock lock(new_output_lock);
			fprintf(new_output_fp,
					"delete%s: %s -> freed %p (size %u, %u bytes still allocated)\n",
					is_array ? "[]" : "",ptr->project,
					(char*)ptr + ALIGNED_LIST_ITEM_SIZE,
					ptr->size, total_mem_alloc);
		}
#endif
		free(ptr);
		return;
	}

	/**
	 * Checks for memory leaks.
	 *
	 * @return  zero if no leakage is found; the number of leaks otherwise
	 */
	int check_leaks()
	{
#ifndef MINIMAL_INFO
		int leak_cnt = 0;
		fast_mutex_autolock lock_ptr(new_ptr_lock);
		fast_mutex_autolock lock_output(new_output_lock);
		new_ptr_list_t* ptr = new_ptr_list.next;
		while (ptr != &new_ptr_list)
		{
			const char* const pointer = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
			if (ptr->magic != MAGIC)
			{
				fprintf(new_output_fp,
						"warning: heap data corrupt near %p\n",
						pointer);
			}
	#if _OVERRIDE_NEW_TAILCHECK
			if (!check_tail(ptr))
			{
				fprintf(new_output_fp,
						"warning: overwritten past end of object at %p\n",
						pointer);
			}
	#endif
			fprintf(new_output_fp,
					"Leaked object at %p (%s): %s-> (size %u, ",
					pointer, ptr->module, ptr->project,
					ptr->size);
			if (ptr->line != 0)
				print_position(ptr->file, ptr->line);
			else
				print_position(ptr->addr, ptr->line);
			fprintf(new_output_fp, ")\n");
			
//  			for(StackWalker::Trace* it = ptr->stack_trace; NULL != it; it = it->next)
//  			{
// 				fprintf(new_output_fp, "\tmodule name: %s -- %s (%s): %s\n", it->entry.moduleName, it->entry.lineFileName, it->entry.lineNumber, it->entry.name);
//  			}

			ptr = ptr->next;
			++leak_cnt;
		}
		if (new_verbose_flag || leak_cnt)
			fprintf(new_output_fp, "*** %d leaks found\n", leak_cnt);
		return leak_cnt;
#else
	fprintf(new_output_fp,"Memory leak checking is disabled, please disable MINIMAL_INFO macro in memory_allocation.h");
	return 0;
#endif

	}

	/**
	 * Checks for heap corruption.
	 *
	 * @return  zero if no problem is found; the number of found memory
	 *          corruptions otherwise
	 */
	int check_mem_corruption()
	{
#ifndef MINIMAL_INFO
		int corrupt_cnt = 0;
		fast_mutex_autolock lock_ptr(new_ptr_lock);
		fast_mutex_autolock lock_output(new_output_lock);
		fprintf(new_output_fp, "*** Checking for memory corruption: START\n");
		for (new_ptr_list_t* ptr = new_ptr_list.next;
				ptr != &new_ptr_list;
				ptr = ptr->next)
		{
			const char* const pointer = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
			if (ptr->magic == MAGIC
	#if _OVERRIDE_NEW_TAILCHECK
					&& check_tail(ptr)
	#endif
					)
				continue;
	#if _OVERRIDE_NEW_TAILCHECK
			if (ptr->magic != MAGIC)
			{
	#endif
				fprintf(new_output_fp,
						"Heap data corrupt near %p (size %u, ",
						pointer,
						ptr->size);
	#if _OVERRIDE_NEW_TAILCHECK
			}
			else
			{
				fprintf(new_output_fp,
						"Overwritten past end of object at %p (size %u, ",
						pointer,
						ptr->size);
			}
	#endif
			if (ptr->line != 0)
				print_position(ptr->file, ptr->line);
			else
				print_position(ptr->addr, ptr->line);
			fprintf(new_output_fp, ") in (%s) %s\n", ptr->module, ptr->project);
// 			for(StackWalker::Trace* it = ptr->stack_trace; NULL != it; it = it->next)
// 			{
// 				fprintf(new_output_fp, "\tmodule name: %s -- %s (%s): %s\n", it->entry.moduleName, it->entry.lineFileName, it->entry.lineNumber, it->entry.name);
// 			}
			++corrupt_cnt;
		}
		fprintf(new_output_fp, "*** Checking for memory corruption: %d FOUND\n",
				corrupt_cnt);
		return corrupt_cnt;
#else
		fprintf(new_output_fp,"Memory corruption checking is disabled, please disable MINIMAL_INFO macro in memory_allocation.h");
		return 0;
#endif	
	}

	unsigned int total_memory_usage()
	{
		return total_mem_alloc;
	}

	void log_memory_usage(const char* fileName)
	{
#ifndef MINIMAL_INFO
		std::ofstream out(fileName);
		out<<"project_name\tfile\tline\tsize"<<std::endl;

		for(new_ptr_list_t* it=new_ptr_list.next;it->size != 0;it=it->next)
		{
			out<<it->project<<"\t"<<it->file<<"\t"<<it->line<<"\t"<<it->size<<std::endl;
		}
		out.close();
#else
		fprintf(new_output_fp,"Memory loging is disabled, please disable MINIMAL_INFO macro in memory_allocation.h");
#endif
	}

	int memory_usage_of(std::string project_name )
	{
		pair_t* f=memory_per_project.find(project_name);
		if(f == NULL) return 0;
		return f->size;
	}

	void free_pointer_verbose(void* pointer, const char* file, int line)
	{
#ifndef MINIMAL_INFO
		if (new_verbose_flag)
		{
			fast_mutex_autolock lock(new_output_lock);
			fprintf(new_output_fp,
					"info: exception thrown on initializing object at %p (",
					pointer);
			print_position(file, line);
			fprintf(new_output_fp, ")\n");
		}
#endif
	}

	void process( void* pointer, const char* _M_project_name, const char* _M_file, const int _M_line)
	{
		if (pointer == NULL)
			return;
		new_ptr_list_t* ptr =
			(new_ptr_list_t*)((char*)pointer - ALIGNED_LIST_ITEM_SIZE);
#ifndef MINIMAL_INFO
		if (ptr->magic != MAGIC || ptr->addr != 0)
		{
			fast_mutex_autolock lock(new_output_lock);
			fprintf(new_output_fp,
				"warning: debug_new used with placement new (%s:%d)\n",
				_M_file, _M_line);
			return;
		}
	#if _OVERRIDE_NEW_FILENAME_LEN == 0
		ptr->file = _M_file;
	#else
		strncpy(ptr->file, _M_file, _OVERRIDE_NEW_FILENAME_LEN - 1)
			[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';
	#endif
		ptr->line = _M_line;
#endif
		if(project_name_override=="")
			strncpy(ptr->project, _M_project_name, _OVERRIDE_NEW_FILENAME_LEN - 1)
			[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';
		else
			strncpy(ptr->project, project_name_override.c_str(), _OVERRIDE_NEW_FILENAME_LEN - 1)
			[_OVERRIDE_NEW_FILENAME_LEN - 1] = '\0';
	}




	int __debug_new_counter::_S_count = 0;

	/**
	 * Constructor to increment the count.
	 */
	__debug_new_counter::__debug_new_counter()
	{
		++_S_count;
	}

	/**
	 * Destructor to decrement the count.  When the count is zero,
	 * #check_leaks will be called.
	 */
	__debug_new_counter::~__debug_new_counter()
	{
#ifndef MINIMAL_INFO
		if (--_S_count == 0 && new_autocheck_flag)
			if (check_leaks())
			{
				new_verbose_flag = true;
	#if defined(__GNUC__) && __GNUC__ >= 3
				if (!getenv("GLIBCPP_FORCE_NEW") && !getenv("GLIBCXX_FORCE_NEW"))
					fprintf(new_output_fp,
	"*** WARNING:  GCC 3 or later is detected, please make sure the\n"
	"    environment variable GLIBCPP_FORCE_NEW (GCC 3.2 and 3.3) or\n"
	"    GLIBCXX_FORCE_NEW (GCC 3.4 and later) is defined.  Check the\n"
	"    README file for details.\n");
	#endif
			}
#endif
	}

	memoryMap_t& memory_map()
	{
		return memory_per_project;
	}



	Pair::Pair( std::string name_/*=""*/, int size_/*=0*/ ) :name(name_),size(size_)
	{

	}


	MemoryMap::MemoryMap() :m_size(0)
	{

	}

	Pair* MemoryMap::find( std::string name )
	{
		for(unsigned int i=0;i<m_size;++i)
			if(name == m_map[i].name) return &m_map[i];
		return NULL;
	}

	void MemoryMap::add( const Pair& p )
	{
		m_map[m_size]=p;
		++m_size;
	}

	Pair& MemoryMap::operator[]( unsigned int i )
	{
		assert(i<m_size);
		return m_map[i];
	}

	const Pair& MemoryMap::operator[]( unsigned int i ) const
	{
		assert(i<m_size);
		return m_map[i];
	}

	Pair& MemoryMap::at( unsigned int i )
	{
		assert(i<m_size);
		return m_map[i];
	}

	const Pair& MemoryMap::at( unsigned int i ) const
	{
		assert(i<m_size);
		return m_map[i];
	}

	unsigned int MemoryMap::size() const
	{
		return m_size;
	}

}


