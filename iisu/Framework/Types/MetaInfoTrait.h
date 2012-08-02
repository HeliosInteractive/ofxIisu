#pragma once

#include <Platform/SkPlatform.h>
#include <Platform/CompileTimeUtils.h>

namespace SK
{
	class IEvent;

	namespace MetaInfoClass
	{
		enum Enum
		{
			GENERIC = 0,
			RANGE_BASED = 1,
			NATIVE_DEFAULT_VALUE =4,
			EVENT = 8,
			FUNCTION = 16
		};
	}
	//! \cond METAINFO_CLASS_EXTRACTOR_TRAITS
	template <typename T, bool isEvent = SK_IS_CLASS_DERIVED_FROM(SK::IEvent, typename SK::RefTypeTrait<T>::remove_const_ref_t)> struct MetaInfoClassExtractorTrait;


	template <typename T> struct MetaInfoClassExtractorTrait<T, false> 
	{
		typedef T DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::GENERIC;
	};

	template <typename T> struct MetaInfoClassExtractorTrait< SK::Return<T>, false> 
	{
		typedef typename MetaInfoClassExtractorTrait<T>::DataType_T DataType_T;
		static const uint32_t DataTypeID = MetaInfoClassExtractorTrait<T>::DataTypeID;
	};


	template <typename T> struct MetaInfoClassExtractorTrait<T, true> 
	{
		typedef SK::IEvent DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::EVENT;
	};

	template <> struct MetaInfoClassExtractorTrait<bool, false> 
	{
		typedef bool DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::NATIVE_DEFAULT_VALUE;
	};
	template <> struct MetaInfoClassExtractorTrait<SK::Array<bool>, false> 
	{
		typedef SK::Array<bool> DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::NATIVE_DEFAULT_VALUE;
	};

	template <> struct MetaInfoClassExtractorTrait<float, false> 
	{
		typedef float DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<int8_t, false> 
	{
		typedef int8_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<int16_t, false> 
	{
		typedef int16_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<int32_t, false> 
	{
		typedef int32_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<int64_t, false> 
	{
		typedef int64_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<uint8_t, false> 
	{
		typedef uint8_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<uint16_t, false> 
	{
		typedef uint16_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<uint32_t, false> 
	{
		typedef uint32_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait<uint64_t, false> 
	{
		typedef uint64_t DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};

	template <> struct MetaInfoClassExtractorTrait< SK::Array<float>, false > 
	{
		typedef SK::Array<float> DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<int8_t>, false > 
	{
		typedef  SK::Array<int8_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<int16_t>, false > 
	{
		typedef  SK::Array<int16_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<int32_t>, false > 
	{
		typedef  SK::Array<int32_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<int64_t>, false > 
	{
		typedef  SK::Array<int64_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<uint8_t>, false > 
	{
		typedef  SK::Array<uint8_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<uint16_t>, false > 
	{
		typedef  SK::Array<uint16_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<uint32_t>, false > 
	{
		typedef  SK::Array<uint32_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};
	template <> struct MetaInfoClassExtractorTrait< SK::Array<uint64_t>, false > 
	{
		typedef  SK::Array<uint64_t>  DataType_T;
		static const uint32_t DataTypeID = SK::MetaInfoClass::RANGE_BASED;
	};

	template <typename R> struct MetaInfoClassExtractorTrait< R(), false> 
	{
		typedef R(DataType_T)() ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1> struct MetaInfoClassExtractorTrait< R(P1), false> 
	{
		typedef R(DataType_T)(P1) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2> struct MetaInfoClassExtractorTrait< R(P1, P2), false> 
	{
		typedef R(DataType_T)(P1, P2) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3> struct MetaInfoClassExtractorTrait< R(P1, P2, P3), false> 
	{
		typedef R(DataType_T)(P1, P2, P3) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4> struct MetaInfoClassExtractorTrait< R(P1, P2, P3, P4), false> 
	{
		typedef R(DataType_T)(P1, P2, P3, P4) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> struct MetaInfoClassExtractorTrait< R(P1, P2, P3, P4, P5), false> 
	{
		typedef R(DataType_T)(P1, P2, P3, P4, P5) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> struct MetaInfoClassExtractorTrait< R(P1, P2, P3, P4, P5, P6), false> 
	{
		typedef R(DataType_T)(P1, P2, P3, P4, P5, P6) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> struct MetaInfoClassExtractorTrait< R(P1, P2, P3, P4, P5, P6, P7), false> 
	{
		typedef R(DataType_T)(P1, P2, P3, P4, P5, P6, P7) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> struct MetaInfoClassExtractorTrait< R(P1, P2, P3, P4, P5, P6, P7, P8), false> 
	{
		typedef R(DataType_T)(P1, P2, P3, P4, P5, P6, P7, P8) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> struct MetaInfoClassExtractorTrait< R(P1, P2, P3, P4, P5, P6, P7, P8, P9), false> 
	{
		typedef R(DataType_T)(P1, P2, P3, P4, P5, P6, P7, P8, P9) ;
		static const uint32_t DataTypeID = SK::MetaInfoClass::FUNCTION;
	};
	//! \endcond
}
