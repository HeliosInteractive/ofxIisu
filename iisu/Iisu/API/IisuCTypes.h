//*****************************************************************************
//
//  Softkinetic iisu SDK
//
//  Copyright (C) 2006-2010 by Softkinetic SA/NV
//  All rights reserved.
//
//  Version           : 2.6
//
//  File Name         : iisu_defs.h
//  Description       : Iisu C interface definiton.
//
//  $Date: 2011-01-17 18:31:07 +0100 (Mon, 17 Jan 2011) $
//  $Revision: 12995 $
//
//*****************************************************************************

#pragma once
/*! \file iisu_defs.h
\brief Iisu C data types definition.
*/

// 
#include <Platform/SkPlatform.h>  
#include <Framework/Errors/Return.h>
#include <Foundation/Services/Types/TypeInfo.h>

#if (SK_PLATFORM == SK_PLATFORM_WIN32)
#pragma managed(push, off)
#pragma warning( push )
#pragma warning( disable : 4996 ) //CRT SECURE DEPRECATE
#endif

typedef int32_t SkBool;

extern "C" {

#define OUT
#define INOUT
#define IN

// opaque types
typedef void* SkContext_C;
typedef void* SkIisuHandle_C;
typedef void* SkDevice_C;
typedef void* SkEventManager_C;
typedef void (SK_SDK_DECL *SkEventListenerStdCallFunction_C)();
typedef void (SK_SDK_CDECL *SkEventListenerCDeclFunction_C)();
typedef void* SkImageInfos_C;
typedef void* SkString_C;
typedef void* SkImage_C;
typedef void* SkCommandManager_C;
typedef void* SkEventManager_C;
typedef void* SkIisuHandleConfig_C; // FIX THIS
typedef void* SkDeviceConfig_C; // FIX THIS
typedef void* SkApplicationConfigurator_C 
;
typedef void* SkRawData_C ;
typedef uint32_t   SkTypeInfo_C;
typedef uint32_t   SkFunctionTypeInfo_C;
typedef void* SkMetaInfo_C;
typedef uint32_t SkAttributes;
typedef void* SkEnumMapper_C;
typedef void* SkResult_C;
typedef void* SkDataFrame_C;

/**
 * \struct	SkEnumValue_C
 *
 * \brief	An enum map item.
 * 			 
 * It contains a id and the corresponding string. This is a C proxy for EnumValue obtained through EnumMapper.
 */

struct SkEnumValue_C 
{
	uint32_t id;
	SK::String name;
};
 ;

/**
 * \struct	SkError_C
 *
 * \brief	Error code of iisu and its corresponding message.
 * 			
 * This class is a proxy of SK::Return<X> class for the C API. 
 */

typedef struct SkError_C
{
	uint32_t errorCode;
	int32_t moduleID ;
	char message[1024];
}SkError_C;
static SkError_C resultOK_C = {0, 0};

namespace SK
{
	/**
	 * \fn	static struct SkError_C errorToCAPI(const SK::ReturnBase& result)
	 *
	 * \brief	Convert a SK::Return<X> into a SkError_C. 
	 * 			
	 * \param	result	the SK::Return<X>
	 * 					
	 * \return	the corresponding SkError_C
	 */

	inline struct SkError_C errorToCAPI(const SK::ReturnBase& result)
	{
		struct SkError_C res;
		// check to avoid assert
		SK::Error err =	result.getError();
		res.errorCode= err.getCode();
		res.moduleID = err.getModuleID();
//		int32_t level = 0;
		//crop message if too int32_t (max size is 1023)
		std::string last_description,description = err.getMessage().ptr();
		uint32_t size = description.size();
		const SK::Error* curErr = err.getChild();
		std::string crop_string = "...";
		uint32_t maxSize = 1024-1-crop_string.size()-1; //last -1 is for counting for \n if stack has multiple levels
		while(size <= maxSize && curErr)
		{
			last_description = description;
			description += "\n   >> "+std::string(curErr->getMessage().ptr());
			size+=description.size();
			curErr = curErr->getChild();
		}
		if (size > maxSize) 
		{
			if (last_description==description) 
			{
				description = description.replace(maxSize,1022,crop_string);			
				size=1022;
			}
			else 
			{
				description = last_description + "\n" + crop_string;
				size = 1023; 
			}
		}
		strncpy(res.message, description.c_str(),size);
		res.message[size] = 0;
		result.ignoreError();
		return res;
	}
}


}



#if (SK_PLATFORM == SK_PLATFORM_WIN32)
#pragma managed(pop)
#pragma warning(pop)
#endif

