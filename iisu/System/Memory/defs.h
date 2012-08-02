#pragma once

#include "fast_mutex.h"
#include "static_assert.h"

/**
 * @def HAVE_PLACEMENT_DELETE
 *
 * Macro to indicate whether placement delete operators are supported on
 * a certain compiler.  Some compilers, like Borland C++ Compiler 5.5.1
 * and Digital Mars Compiler 8.42, do not support them, and the user
 * must define this macro to \c 0 to make the program compile.  Also
 * note that in that case memory leakage will occur if an exception is
 * thrown in the initialization (constructor) of a dynamically created
 * object.
 */
#ifndef HAVE_PLACEMENT_DELETE
#define HAVE_PLACEMENT_DELETE 1
#endif


#if !_FAST_MUTEX_CHECK_INITIALIZATION && !defined(_NOTHREADS)
#error "_FAST_MUTEX_CHECK_INITIALIZATION not set: check_leaks may not work"
#endif

/**
 * @def _OVERRIDE_NEW_ALIGNMENT
 *
 * The alignment requirement of allocated memory blocks.  It must be a
 * power of two.
 */
#ifndef _OVERRIDE_NEW_ALIGNMENT
#define _OVERRIDE_NEW_ALIGNMENT 16
#endif

/**
 * @def _OVERRIDE_NEW_CALLER_ADDRESS
 *
 * The expression to return the caller address.  #print_position will
 * later on use this address to print the position information of memory
 * operation points.
 */
#ifndef _OVERRIDE_NEW_CALLER_ADDRESS
#ifdef __GNUC__
#define _OVERRIDE_NEW_CALLER_ADDRESS __builtin_return_address(0)
#else
#define _OVERRIDE_NEW_CALLER_ADDRESS NULL
#endif
#endif

/**
 * @def _OVERRIDE_NEW_ERROR_ACTION
 *
 * The action to take when an error occurs.  The default behaviour is to
 * call \e abort, unless \c _OVERRIDE_NEW_ERROR_CRASH is defined, in which
 * case a segmentation fault will be triggered instead (which can be
 * useful on platforms like Windows that do not generate a core dump
 * when \e abort is called).
 */
#ifndef _OVERRIDE_NEW_ERROR_ACTION
#ifndef _OVERRIDE_NEW_ERROR_CRASH
#define _OVERRIDE_NEW_ERROR_ACTION abort()
#else
#define _OVERRIDE_NEW_ERROR_ACTION do { *((char*)0) = 0; abort(); } while (0)
#endif
#endif

/**
 * @def _OVERRIDE_NEW_FILENAME_LEN
 *
 * The length of file name stored if greater than zero.  If it is zero,
 * only a const char pointer will be stored.  Currently the default
 * behaviour is to copy the file name, because I found that the exit
 * leakage check cannot access the address of the file name sometimes
 * (in my case, a core dump will occur when trying to access the file
 * name in a shared library after a \c SIGINT).  The current default
 * value makes the size of new_ptr_list_t 64 on 32-bit platforms.
 */
#ifndef _OVERRIDE_NEW_FILENAME_LEN
#define _OVERRIDE_NEW_FILENAME_LEN 256
#endif

/**
 * @def _OVERRIDE_NEW_PROGNAME
 *
 * The program (executable) name to be set at compile time.  It is
 * better to assign the full program path to #new_progname in \e main
 * (at run time) than to use this (compile-time) macro, but this macro
 * serves well as a quick hack.  Note also that double quotation marks
 * need to be used around the program name, i.e., one should specify a
 * command-line option like <code>-D_OVERRIDE_NEW_PROGNAME=\"a.out\"</code>
 * in \e bash, or <code>-D_OVERRIDE_NEW_PROGNAME=\"a.exe\"</code> in the
 * Windows command prompt.
 */
#ifndef _OVERRIDE_NEW_PROGNAME
#define _OVERRIDE_NEW_PROGNAME NULL
#endif

/**
 * @def _OVERRIDE_NEW_STD_OPER_NEW
 *
 * Macro to indicate whether the standard-conformant behaviour of
 * <code>operator new</code> is wanted.  It is on by default now, but
 * the user may set it to \c 0 to revert to the old behaviour.
 */
#ifndef _OVERRIDE_NEW_STD_OPER_NEW
#define _OVERRIDE_NEW_STD_OPER_NEW 1
#endif

/**
 * @def _OVERRIDE_NEW_TAILCHECK
 *
 * Macro to indicate whether a writing-past-end check will be performed.
 * Define it to a positive integer as the number of padding bytes at the
 * end of a memory block for checking.
 */
#ifndef _OVERRIDE_NEW_TAILCHECK
#define _OVERRIDE_NEW_TAILCHECK 0
#endif

/**
 * @def _OVERRIDE_NEW_TAILCHECK_CHAR
 *
 * Value of the padding bytes at the end of a memory block.
 */
#ifndef _OVERRIDE_NEW_TAILCHECK_CHAR
#define _OVERRIDE_NEW_TAILCHECK_CHAR 0xCC
#endif

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

#ifdef _MSC_VER
#pragma warning(disable: 4073)  // #pragma init_seg(lib) used
#pragma warning(disable: 4290)  // C++ exception specification ignored
#pragma init_seg(lib)
#endif
