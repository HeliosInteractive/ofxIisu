#ifndef IISU_API_HELPERS_H
#define IISU_API_HELPERS_H

#include <Iisu/API/IisuCTypes.h>	// for Iisu C types manipulations

extern "C" {

// error 

/**
 * \fn	IISUSDK_API struct SkError_C SK_SDK_DECL iisu_resultToError(IN const SkResult_C resultPtr);
 *
 * \brief	Retrieves the error part of a result.
 *
 * \param	resultPtr	The result .
 *
 * \return	The error part of the result
 */

IISUSDK_API struct SkError_C SK_SDK_DECL iisu_resultToError(IN const SkResult_C resultPtr);


/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkTypeInfo_getTypeID(IN SkTypeInfo_C type);
 *
 * \brief	Retrieves the ID of a TypeInfo structure.
 *
 * \param	type	The type.
 *
 * \return	the type ID
 */

IISUSDK_API uint32_t	SK_SDK_DECL SkTypeInfo_getTypeID(IN SkTypeInfo_C type); 

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkTypeInfo_getName(IN SkTypeInfo_C type,
 * 		OUT SkString_C name);
 *
 * \brief	Retrieves the name part of a TypeInfo struct
 *
 * \param	type	The type.
 * \param	name	a string to be filled with the type's name.
 *
 */

IISUSDK_API void		SK_SDK_DECL SkTypeInfo_getName(IN SkTypeInfo_C type, OUT SkString_C name);

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkTypeInfo_getCharacteristics(IN SkTypeInfo_C type);
 *
 * \brief	Sk type information get characteristics.
 *
 * \param	give additional iformation about the TypeInfo struct. \sa TypeInfoCharacteristic
 *
 * \return	the typeinfo characteristic
 */

IISUSDK_API uint32_t	SK_SDK_DECL SkTypeInfo_getCharacteristics(IN SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkTypeInfo_removeReturn(IN SkTypeInfo_C type);
 *
 * \brief	If the passed TypeInfo is a Return<T>, returns the TypeInfo of T. Otherwise returns the original TypeInfo
 *
 * \param	type	The type to be converted
 *
 * \return	the converted type
 */

IISUSDK_API SkTypeInfo_C  SK_SDK_DECL SkTypeInfo_removeReturn(IN SkTypeInfo_C type) ;

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkTypeInfo_removeArray(IN SkTypeInfo_C type);
 *
 * \brief	If the passed TypeInfo is a Array<T>, returns the TypeInfo of T. Otherwise returns the original TypeInfo
 *
 * \param	type	The type to be converted
 *
 * \return	the converted type
 */

IISUSDK_API SkTypeInfo_C  SK_SDK_DECL SkTypeInfo_removeArray(IN SkTypeInfo_C type) ;

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkTypeInfo_removeConstRef(IN SkTypeInfo_C type);
 *
 * \brief	If the passed TypeInfo is const &T, returns the TypeInfo of T. Otherwise returns the original TypeInfo
 *
 * \param	type	The type to be converted
 *
 * \return	the converted type
 */

IISUSDK_API SkTypeInfo_C  SK_SDK_DECL SkTypeInfo_removeConstRef(IN SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkFunctionTypeInfo_getReturnTypeInfo(IN SkFunctionTypeInfo_C type);
 *
 * \brief	Returns the TypeInfo of the return value for the given FunctionTypeInfo.
 *
 * \param	type	The function type.
 *
 * \return	the type for the return value
 */

IISUSDK_API SkTypeInfo_C	SK_SDK_DECL SkFunctionTypeInfo_getReturnTypeInfo(IN SkFunctionTypeInfo_C type);

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkFunctionTypeInfo_getNumberOfParameter(IN SkFunctionTypeInfo_C type);
 *
 * \brief	Returns the number of parameter needed to call a function with the specified FunctionTypeInfo.
 *
 * \param	type	The function type.
 *
 * \return	the number of parameter for the function type
 */

IISUSDK_API uint32_t		SK_SDK_DECL SkFunctionTypeInfo_getNumberOfParameter(IN SkFunctionTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkFunctionTypeInfo_getParameterTypeInfo(IN SkFunctionTypeInfo_C type,
 * 		IN uint32_t paramID);
 *
 * \brief	Returns the typeinfo of the index-th parameter.
 *
 * \param	type   	The type.
 * \param	index	The zero-based index of the parameter.
 *
 * \return	the typeinfo of the parameter
 */

IISUSDK_API SkTypeInfo_C	SK_SDK_DECL SkFunctionTypeInfo_getParameterTypeInfo(IN SkFunctionTypeInfo_C type, IN uint32_t index);

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkFunctionTypeInfo_getTypeID(IN SkFunctionTypeInfo_C type);
 *
 * \brief	returns the TypeID of the specified function typeinfo
 *
 * \param	type	The typeinfo.
 *
 * \return	the type ID
 */

IISUSDK_API uint32_t		SK_SDK_DECL SkFunctionTypeInfo_getTypeID(IN SkFunctionTypeInfo_C type);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkFunctionTypeInfo_getName(IN SkFunctionTypeInfo_C type,
 * 		OUT SkString_C name);
 *
 * \brief	returns the name of the specified function typeinfo
 *
 * \param	type	The typeinfo.
 * \param	name	A string to store the name.
 *
 */

IISUSDK_API void			SK_SDK_DECL SkFunctionTypeInfo_getName(IN SkFunctionTypeInfo_C type, OUT SkString_C name);

/**
 * \fn	IISUSDK_API SkString_C SK_SDK_DECL iisu_createString();
 *
 * \brief	Create a SkString
 *
 * \return	a SkString opaque pointer
 */

IISUSDK_API SkString_C			SK_SDK_DECL iisu_createString();

/**
 * \fn	IISUSDK_API void SK_SDK_DECL iisu_destroyString(SkString_C ptr);
 *
 * \brief	Destroys an SkString.
 *
 * \param	ptr	The opaque pointer to the string.
 */

IISUSDK_API void			SK_SDK_DECL iisu_destroyString(SkString_C ptr);

/**
 * \fn	IISUSDK_API char* SK_SDK_DECL SkString_ptr(SkString_C str);
 *
 * \brief	Returns the pointer to the string held by the opaque string pointer
 *
 * \param	str	the opaque string pointer.
 *
 * \return	the pointer to the string
 */

IISUSDK_API char*			SK_SDK_DECL SkString_ptr(SkString_C str);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkString_resize(SkString_C str, uint32_t n);
 *
 * \brief	Resizes a SkString 
 *
 * \param	str	the opaque string pointer.
 * \param	n  	The new size of the string.
 */

IISUSDK_API void			SK_SDK_DECL SkString_resize(SkString_C str, uint32_t n);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkString_copyFrom(SkString_C str, const char* ptr,
 * 		int32_t n);
 *
 * \brief	Initialize a SkString from a char * and a size
 *
 * \param	str	The opaque string.
 * \param	ptr	The pointer of the string to initialize it from.
 * \param	n  	The size of the string to initialize it from.
 *
 * \return	.
 */

IISUSDK_API void			SK_SDK_DECL SkString_copyFrom(SkString_C str, const char* ptr, int32_t n);

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkString_size(SkString_C str);
 *
 * \brief	Returns the size of the string .
 *
 * \param	str	The opaque string pointer.
 *
 * \return	the size of the string
 */

IISUSDK_API uint32_t		SK_SDK_DECL SkString_size(SkString_C str);

/**
 * \fn	IISUSDK_API SkImage_C SK_SDK_DECL iisu_createImage();
 *
 * \brief	Creates an SkImage
 *
 * \return	an opaque pointer to a SkImage
 */

IISUSDK_API SkImage_C			SK_SDK_DECL iisu_createImage();

/**
 * \fn	IISUSDK_API void SK_SDK_DECL iisu_destroyImage(SkImage_C img);
 *
 * \brief	Destroys a SkImage.
 *
 * \param	img	The opque image pointer.
 *
 * \return	.
 */

IISUSDK_API void			SK_SDK_DECL iisu_destroyImage(SkImage_C img);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkImage_getImageInfos(SkImage_C img, SkImageInfos_C infos);
 *
 * \brief	Gets the ImageInfo associated to the SkImage.
 *
 * \param	img  	The opaque image pointer.
 * \param	infos	An opque image infos ptr to be filler with the informations.
 *
 * \return	.
 */

IISUSDK_API void			SK_SDK_DECL SkImage_getImageInfos(SkImage_C img, SkImageInfos_C infos);

/**
 * \fn	IISUSDK_API void * SK_SDK_DECL SkImage_getRAW(SkImage_C img);
 *
 * \brief	Returns a pointer to the raw image buffer.
 *
 * \param	img	The opaque image ptr.
 *
 * \return	a pointer to the raw image data buffer
 */

IISUSDK_API void *			SK_SDK_DECL SkImage_getRAW(SkImage_C img);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkImage_resize(SkImage_C img, SkImageInfos_C infos,
 * 		SkBool forceReallocation);
 *
 * \brief	Resize the image.
 *
 * \param	img				 	The image opaque ptr.
 * \param	infos			 	The image info specifying the image's new dimension.
 * \param	forceReallocation	to force buffer reallocation.
 *
 * \return	.
 */

IISUSDK_API void			SK_SDK_DECL SkImage_resize(SkImage_C img, SkImageInfos_C infos, SkBool forceReallocation);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkImage_copyImage(SkImage_C pSource,
 * 		SkImage_C pDestination);
 *
 * \brief	Copies an image to another image.
 *
 * \param	pSource			the opaque pointer to the source image.
 * \param	pDestination	the opaque pointer to the destination image.
 *
 * \return	.
 */

IISUSDK_API void			SK_SDK_DECL SkImage_copyImage(SkImage_C pSource, SkImage_C pDestination);

/**
 * \fn	IISUSDK_API SkImage_C SK_SDK_DECL iisu_createArray(SkTypeInfo_C type);
 *
 * \brief	Creates a SkArray.
 *
 * \param	type	A typeinfo struct specifying the type of data contained in the array
 *
 * \return	An opaque pointer to the SkImage 
 */

IISUSDK_API SkImage_C			SK_SDK_DECL iisu_createArray(SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL iisu_destroyArray(SkImage_C array, SkTypeInfo_C type);
 *
 * \brief	Destroys an SkArray (and it's content).
 *
 * \param	array	The array.
 * \param	type 	The type of element contained by the array.
 */

IISUSDK_API void			SK_SDK_DECL iisu_destroyArray(SkImage_C array, SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkArray_getSize(SkImage_C array, SkTypeInfo_C type);
 *
 * \brief	Gets the array size.
 *
 * \param	array	The array.
 * \param	type 	The type of element contained by the array.
 *
 * \return	the size of the array
 */

IISUSDK_API uint32_t		SK_SDK_DECL SkArray_getSize(SkImage_C array, SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API void* SK_SDK_DECL SkArray_getPtr(SkImage_C array, SkTypeInfo_C type);
 *
 * \brief	Gets access to the internal pointer to the array content.
 *
 * \param	array	The array.
 * \param	type 	The type of elements contained by the array.
 *
 * \return	a pointer to the internal array data structure
 */

IISUSDK_API void*			SK_SDK_DECL SkArray_getPtr(SkImage_C array, SkTypeInfo_C type);

/**
 * \fn	IISUSDK_API SkMetaInfo_C SK_SDK_DECL iisu_createMetaInfo(IN SkTypeInfo_C typeInfo);
 *
 * \brief	Iisu creates meta information opaque object.
 *
 * \param	typeInfo	A TypeInfo structure describing the type on which the meta info applies.
 *
 * \return	an opaque pointer to the meta info
 */

IISUSDK_API SkMetaInfo_C	SK_SDK_DECL iisu_createMetaInfo(IN SkTypeInfo_C typeInfo);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL iisu_destroyMetaInfo(IN SkMetaInfo_C metainfo);
 *
 * \brief	Destroys a meta info opaque object.
 *
 * \param	metainfo	The metainfo.
 */

IISUSDK_API void			SK_SDK_DECL iisu_destroyMetaInfo(IN SkMetaInfo_C metainfo);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkMetaInfo_getDescription(IN SkMetaInfo_C metainfo ,
 * 		OUT SkString_C* descr);
 *
 * \brief	Returns the meta info's description
 *
 * \param	metainfo	 	The metainfo.
 * \param [out]	descr	a pointer that will be filled with an opaque string pointer containing the description.
 *
 */

IISUSDK_API void			SK_SDK_DECL SkMetaInfo_getDescription(IN SkMetaInfo_C metainfo , OUT SkString_C* descr) ; // FIXME: SAFE ?


IISUSDK_API SkBool			SK_SDK_DECL SkMetaInfo_supportDefaultValue (IN SkTypeInfo_C type ); // FIXME: Pq typeinfo ? - see C# function calls 2 parameters

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkMetaInfo_getNumberOfAttributes(IN SkMetaInfo_C metainfo);
 *
 * \brief	Returns the number of attributes this meta info has.
 *
 * \param	metainfo	The metainfo.
 *
 * \return	the number of attributes
 */

IISUSDK_API uint32_t		SK_SDK_DECL SkMetaInfo_getNumberOfAttributes(IN  SkMetaInfo_C metainfo);

/**
 * \fn	IISUSDK_API SkString_C SK_SDK_DECL SkMetaInfo_getAttributeName(IN SkMetaInfo_C metainfo,
 * 		IN uint32_t id);
 *
 * \brief	Gets the name of the index-th attribute of the meta info.
 *
 * \param	metainfo	The metainfo.
 * \param	index		The index of the meta info.
 *
 * \return	the String containing the name
 */

IISUSDK_API SkString_C		SK_SDK_DECL SkMetaInfo_getAttributeName(IN  SkMetaInfo_C metainfo, IN uint32_t index); // is it internal or freed by the user ?

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkMetaInfo_getAttributeTypeFromID(IN SkMetaInfo_C metainfo,
 * 		IN uint32_t id);
 *
 * \brief	Return the type of the index-th attribute of the meta info.
 *
 * \param	metainfo	The metainfo.
 * \param	index		The index of the attribute.
 *
 * \return	a typeinfo
 */

IISUSDK_API SkTypeInfo_C	SK_SDK_DECL SkMetaInfo_getAttributeTypeFromID(IN  SkMetaInfo_C metainfo, IN uint32_t index);

/**
 * \fn	IISUSDK_API SkTypeInfo_C SK_SDK_DECL SkMetaInfo_getAttributeType(IN SkMetaInfo_C metainfo,
 * 		IN SkString_C name);
 *
 * \brief	Returns the type of a meta info from it's name
 *
 * \param	metainfo	The metainfo.
 * \param	name		The name of the attribute.
 *
 * \return	a type info
 */

IISUSDK_API SkTypeInfo_C	SK_SDK_DECL SkMetaInfo_getAttributeType(IN  SkMetaInfo_C metainfo, IN SkString_C name);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkMetaInfo_getAttribute( IN SkMetaInfo_C metainfo,
 * 		IN SkString_C name, IN SkTypeInfo_C typeInfo, OUT void* returnValue );
 *
 * \brief	copies the binary value of the meta info attribute into the specified buffer
 *
 * \param	metainfo		   	The metainfo.
 * \param	name			   	The name of the attribute.
 * \param	typeInfo		   	The expected type of the attribute.
 * \param [out]	returnValue	a pre-allocated buffer that can hold the binary value of the attribute
 *
 * \return	whether the call was successful or not
 */

IISUSDK_API SkError_C 		SK_SDK_DECL SkMetaInfo_getAttribute( IN SkMetaInfo_C metainfo, IN SkString_C name, IN SkTypeInfo_C typeInfo, OUT void* returnValue );

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkMetaInfo_getAttributeFromID(IN SkMetaInfo_C metainfo,
 * 		IN uint32_t id, IN SkTypeInfo_C typeInfo, OUT void* returnValue );
 *
 * \brief	copies the binary value of the meta info attribute into the specified buffer (indexed based)
 *
 * \param	metainfo		   	The metainfo.
 * \param	index				The index of the attribute.
 * \param	typeInfo		   	The expected type of the attribute.
 * \param [out]	returnValue	a pre-allocated buffer that can hold the binary value of the attribute
 *
 * \return	whether the call was successful or not
 */

IISUSDK_API SkError_C 		SK_SDK_DECL SkMetaInfo_getAttributeFromID(IN  SkMetaInfo_C metainfo, IN uint32_t id, IN SkTypeInfo_C typeInfo, OUT void* returnValue );

/**
 * \fn	IISUSDK_API SkEnumMapper_C SK_SDK_DECL iisu_createEnumMapper();
 *
 * \brief	Creates a new enum mapper.
 *
 * \return	an opaque pointer to an SkEnumMapper object
 */

IISUSDK_API SkEnumMapper_C	SK_SDK_DECL iisu_createEnumMapper();

/**
 * \fn	IISUSDK_API void SK_SDK_DECL iisu_destroyEnumMapper(IN SkEnumMapper_C enumMapper);
 *
 * \brief	Destroys an enum mapper.
 *
 * \param	enumMapper	The enum mapper.
 */

IISUSDK_API void			SK_SDK_DECL iisu_destroyEnumMapper(IN SkEnumMapper_C enumMapper);

/**
 * \fn	IISUSDK_API uint32_t SK_SDK_DECL SkEnumMapper_getNumID(IN SkEnumMapper_C enumMapper);
 *
 * \brief	Gets the number of entries in the enum mapper
 *
 * \param	enumMapper	The enum mapper.
 *
 * \return	the number of entries in the mapper
 */

IISUSDK_API uint32_t		SK_SDK_DECL SkEnumMapper_getNumID(IN SkEnumMapper_C enumMapper);
/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEnumMapper_getName(IN SkEnumMapper_C enumMapper,
 * 		IN uint32_t id, OUT SkString_C name);
 *
 * \brief	gets the name associated to a value of the enumeration
 *
 * \param	enumMapper	The enum mapper.
 * \param	index	  	The index of the value.
 * \param	name	  	A string to be filled with the name of the value.
 *
  * \return	whether the call was successful or not
 */

IISUSDK_API SkError_C		SK_SDK_DECL SkEnumMapper_getName(IN SkEnumMapper_C enumMapper, IN uint32_t index, OUT SkString_C name);

/**
 * \fn	IISUSDK_API SkError_C SK_SDK_DECL SkEnumMapper_getID(IN SkEnumMapper_C enumMapper,
 * 		IN SkString_C name, OUT uint32_t* id);
 *
 * \brief	Gets the integer value associated to the specified name.
 *
 * \param	enumMapper	The enum mapper.
 * \param	name	  	The name of the value.
 * \param [out]	id	The enum value.
 *
 * \return	whether the call was successful or not
 */

IISUSDK_API SkError_C		SK_SDK_DECL SkEnumMapper_getID(IN SkEnumMapper_C enumMapper, IN SkString_C name, OUT uint32_t* id);

/**
 * \fn	IISUSDK_API void SK_SDK_DECL SkEnumMapper_add(IN SkEnumMapper_C enumMapper,
 * 		IN uint32_t id, IN SkString_C name);
 *
 * \brief	Adds an entry in the enum mapper.
 *
 * \param	enumMapper	The enum mapper.
 * \param	id		  	The value of the entry.
 * \param	name	  	The name of the entry.
 *
 * \return	whether the call was successful or not
 */

IISUSDK_API void			SK_SDK_DECL SkEnumMapper_add(IN SkEnumMapper_C enumMapper, IN uint32_t value, IN SkString_C name);

/**
 * \fn	IISUSDK_API SkEnumValue_C* SK_SDK_DECL SkEnumMapper_getEnum(IN SkEnumMapper_C enumMapper,
 * 		IN uint32_t id);
 *
 * \brief	Get a pointer to an enum mapper entry.
 *
 * \param	enumMapper	The enum mapper.
 * \param	index		The  zero-based index of the entry.
 *
 * \return	a pointer to the entry
 */

IISUSDK_API SkEnumValue_C*	SK_SDK_DECL SkEnumMapper_getEnum(IN SkEnumMapper_C enumMapper, IN uint32_t index);


} // extern C


#endif // IISU_API_HELPERS_H
