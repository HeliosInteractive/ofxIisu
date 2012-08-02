//#undef min
//#undef max

//
// 

#ifdef MANAGE_MEMORY
//#if !defined(SKLuaDll) && !defined(InteractionDesignerProcessing) && !defined(QTIISU)
#define _OVERRIDE_NEW_EMULATE_MALLOC
//#define _FAST_MUTEX_CHECK_INITIALIZATION 1
//#else
//#define _OVERRIDE_NEW_REDEFINE_NEW 0
//#endif
#include "new_override.h"
#else
//#define _FAST_MUTEX_CHECK_INITIALIZATION 0
#ifndef OVERRIDE_PROJECT_NAME
#define OVERRIDE_PROJECT_NAME(x) 
#define RESTORE_PROJECT_NAME();
#endif
#endif
