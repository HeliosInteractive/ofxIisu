
#pragma once

#include <Foundation/Services/Types/FunctionTypeInfoImpl.h>


namespace SK
{

	template<class TypelessInterface, template <typename T> class TypedImplementation>
	std::auto_ptr<TypelessInterface> FunctionTypeInfo::injectType(const SK::FunctionTypeInfo& typeInfo)
	{
		switch(typeInfo.typeID())
		{
	        SK_FUNC_TYPE_INJECT(SK::UnknownFunctionType, FUNCTION_UNKNOWN_TYPE);
		    SK_FUNC_TYPE_INJECT(SK::InternalFunctionType, FUNCTION_INTERNAL_TYPE);
		    SK_FUNC_TYPE_INJECT(void(const SK::String&), FUNCTION_VOID_STRING);
			SK_FUNC_TYPE_INJECT(bool(bool), FUNCTION_BOOL_BOOL);
			SK_FUNC_TYPE_INJECT(bool(const SK::String&), FUNCTION_BOOL_STRING);
			SK_FUNC_TYPE_INJECT(int32_t(), FUNCTION_INT32T);
			SK_FUNC_TYPE_INJECT(int32_t(bool), FUNCTION_INT32T_BOOL);
			SK_FUNC_TYPE_INJECT(uint32_t(bool), FUNCTION_UINT32T_BOOL);
			SK_FUNC_TYPE_INJECT(int32_t(const SK::String&, const SK::TypeInfo&), FUNCTION_INT32T_STRING_TYPEINFO);
			SK_FUNC_TYPE_INJECT(SK::Return< SK::Array<SK::String> >(), FUNCTION_RETURNARRAYSTRING);
			SK_FUNC_TYPE_INJECT(SK::Return< SK::Array<SK::String> >(const SK::String&), FUNCTION_RETURNARRAYSTRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return< SK::Array<SK::Vector2> >(const SK::String&, const SK::String&), FUNCTION_RETURNARRAYVECTOR2_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return< SK::Array<SK::Vector2i> >(const SK::String&, const SK::String&), FUNCTION_RETURNARRAYVECTOR2I_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return< SK::Attributes>(const SK::String&), FUNCTION_RETURNATTRIBUTES_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<bool>(bool), FUNCTION_RETURNBOOL_BOOL);
			SK_FUNC_TYPE_INJECT(SK::Return<bool>(int32_t), FUNCTION_RETURNBOOL_INT32T);
			SK_FUNC_TYPE_INJECT(SK::Return<bool>(const SK::String&), FUNCTION_RETURNBOOL_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::FunctionTypeInfo>(const SK::String&), FUNCTION_RETURNFUNCTIONTYPEINFO_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<int32_t>(const SK::String&), FUNCTION_RETURNINT32T_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<int32_t>(const SK::String&, const SK::TypeInfo&), FUNCTION_RETURNINT32T_STRING_TYPEINFO);
			SK_FUNC_TYPE_INJECT(SK::Return<int32_t>(const SK::String&, const SK::TypeInfo&, bool), FUNCTION_RETURNINT32T_STRING_TYPEINFO_BOOL);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::RawData>(int32_t,const SK::TypeInfo &), FUNCTION_RETURNRAWDATA_INT32T_TYPEINFO);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::String>(), FUNCTION_RETURNSTRING);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::String>(const SK::String&), FUNCTION_RETURNSTRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::Array<SK::String>&,const SK::String &), FUNCTION_RETURNVOID_ARRAYSTRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(bool), FUNCTION_RETURNVOID_BOOL);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(int32_t, bool), FUNCTION_RETURNVOID_INT32T_BOOL);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(int32_t,const SK::RawData &), FUNCTION_RETURNVOID_INT32T_RAWDATA);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(int32_t, const SK::TypeInfo&), FUNCTION_RETURNVOID_INT32T_TYPEINFO);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(int32_t), FUNCTION_RETURNVOID_INT32T);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::String&), FUNCTION_RETURNVOID_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::String&, const SK::String&), FUNCTION_RETURNVOID_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::String&, const SK::String&, bool), FUNCTION_RETURNVOID_STRING_STRING_BOOL);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::String&, const SK::String&, float), FUNCTION_RETURNVOID_STRING_STRING_FLOAT);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::String&, const SK::String&, const SK::Vector2i &), FUNCTION_RETURNVOID_STRING_STRING_VECTOR2I);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::String&, const SK::String&, const SK::Vector2 &), FUNCTION_RETURNVOID_STRING_STRING_VECTOR2);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(void), FUNCTION_RETURNVOID_VOID);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::RawData>(const SK::String &,const SK::TypeInfo &), FUNCTION_RETURNRAWDATA_STRING_TYPEINFO);
			SK_FUNC_TYPE_INJECT(SK::String(const SK::String&), FUNCTION_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::String(uint32_t), FUNCTION_STRING_UINT32T);
			SK_FUNC_TYPE_INJECT(SK::String(uint32_t, bool), FUNCTION_STRING_UINT32T_BOOL);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::TypeInfo>(const SK::String&), FUNCTION_RETURNTYPEINFO_STRING);
			SK_FUNC_TYPE_INJECT(uint32_t(), FUNCTION_UINT32T);
			SK_FUNC_TYPE_INJECT(uint32_t(const SK::String&), FUNCTION_UINT32T_STRING);
			SK_FUNC_TYPE_INJECT(uint32_t(const SK::String&, const SK::String&), FUNCTION_UINT32T_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::String>(int32_t), FUNCTION_RETURNSTRING_INT32T);
			SK_FUNC_TYPE_INJECT(SK::Return<int32_t>(), FUNCTION_RETURNINT32T);
			SK_FUNC_TYPE_INJECT(SK::Return<bool>(const SK::String&, const SK::String&), FUNCTION_RETURNBOOL_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::Vector2i>(const SK::String&, const SK::String&), FUNCTION_RETURNVECTOR2I_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<float>(const SK::String&, const SK::String&), FUNCTION_RETURNFLOAT_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<SK::Vector2 >(const SK::String&, const SK::String&), FUNCTION_RETURNVECTOR2_STRING_STRING);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::Enum&), FUNCTION_RETURNVOID_ENUM);
			SK_FUNC_TYPE_INJECT(void (const SK::Array<SK::Frame>&), FUNCTION_VOID_ARRAYFRAME);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(uint32_t), FUNCTION_RETURNVOID_UINT32T);
			SK_FUNC_TYPE_INJECT(SK::Return<void>(const SK::Enum&, const SK::Array<int16_t>&), FUNCTION_RETURNVOID_ENUM_ARRAYINT16T);
			SK_FUNC_TYPE_INJECT(void(), FUNCTION_VOID);
			SK_FUNC_TYPE_INJECT(void(bool), FUNCTION_VOID_BOOL);
			SK_FUNC_TYPE_INJECT(void(int32_t), FUNCTION_VOID_INT32T);
			SK_FUNC_TYPE_INJECT(void(int32_t, int32_t), FUNCTION_VOID_INT32T_INT32T);
			SK_FUNC_TYPE_INJECT(void(int32_t, const SK::Vector3&), FUNCTION_VOID_INT32T_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(int8_t), FUNCTION_VOID_INT8T);
			SK_FUNC_TYPE_INJECT(void(int8_t,int8_t), FUNCTION_VOID_INT8T_INT8T);
			SK_FUNC_TYPE_INJECT(void(const SK::Enum&), FUNCTION_VOID_ENUM);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&), FUNCTION_VOID_STRING_ENUM);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&, const SK::Vector3&), FUNCTION_VOID_STRING_ENUM_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::String&, bool), FUNCTION_VOID_STRING_STRING_BOOL);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::String&, const SK::Array<SK::RawData>&, const SK::FunctionTypeInfo&), FUNCTION_VOID_STRING_STRING_ARRAYRAWDATA_FUNCTIONTYPEINFO);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Error&, bool), FUNCTION_VOID_STRING_ERROR_BOOL);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t), FUNCTION_VOID_STRING_INT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, const SK::Enum&), FUNCTION_VOID_STRING_INT32T_ENUM);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, const SK::Vector3&), FUNCTION_VOID_STRING_INT32T_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, const SK::Vector3&, int32_t), FUNCTION_VOID_STRING_INT32T_VECTOR3_INT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int8_t), FUNCTION_VOID_STRING_INT8T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int8_t, int8_t), FUNCTION_VOID_STRING_INT8T_INT8T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::String&), FUNCTION_VOID_STRING_STRING);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, uint32_t), FUNCTION_VOID_STRING_UINT32T);
			SK_FUNC_TYPE_INJECT(void(int16_t), FUNCTION_VOID_INT16T);
			SK_FUNC_TYPE_INJECT(void(int16_t, const SK::Vector3&), FUNCTION_VOID_INT16T_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Array<int32_t>&, const SK::Array<SK::RawData>&), FUNCTION_VOID_STRING_ARRAYINT32T_ARRAYRAWDATA);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, float, const SK::Enum&, uint32_t), FUNCTION_VOID_STRING_FLOAT_ENUM_UINT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&, int32_t, const SK::Vector3&, const SK::Vector3&), FUNCTION_VOID_STRING_ENUM_INT32T_VECTOR3_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&, uint32_t), FUNCTION_VOID_STRING_ENUM_UINT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, int32_t, uint32_t), FUNCTION_VOID_STRING_INT32T_INT32T_UINT32T);
		
		default: 
			assert(false);
			return std::auto_ptr<TypelessInterface>();
		}
	}

	template<class TypelessInterface, template <typename T> class TypedImplementation>
	std::auto_ptr<TypelessInterface> FunctionTypeInfo::injectEventType(const SK::FunctionTypeInfo& typeInfo)
	{
		switch(typeInfo.typeID())
		{
    	    SK_FUNC_TYPE_INJECT(void(const SK::String&), FUNCTION_VOID_STRING);
			SK_FUNC_TYPE_INJECT(void(), FUNCTION_VOID);
			SK_FUNC_TYPE_INJECT(void(bool), FUNCTION_VOID_BOOL);
			SK_FUNC_TYPE_INJECT(void(int32_t), FUNCTION_VOID_INT32T);
			SK_FUNC_TYPE_INJECT(void(int32_t, int32_t), FUNCTION_VOID_INT32T_INT32T);
			SK_FUNC_TYPE_INJECT(void(int32_t, const SK::Vector3&), FUNCTION_VOID_INT32T_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(int8_t), FUNCTION_VOID_INT8T);
			SK_FUNC_TYPE_INJECT(void(int8_t,int8_t), FUNCTION_VOID_INT8T_INT8T);
			SK_FUNC_TYPE_INJECT(void(const SK::Enum&), FUNCTION_VOID_ENUM);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&), FUNCTION_VOID_STRING_ENUM);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&, const SK::Vector3&), FUNCTION_VOID_STRING_ENUM_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::String&, bool), FUNCTION_VOID_STRING_STRING_BOOL);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::String&, const SK::Array<SK::RawData>&, const SK::FunctionTypeInfo&), FUNCTION_VOID_STRING_STRING_ARRAYRAWDATA_FUNCTIONTYPEINFO);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Error&, bool), FUNCTION_VOID_STRING_ERROR_BOOL);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t), FUNCTION_VOID_STRING_INT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, const SK::Enum&), FUNCTION_VOID_STRING_INT32T_ENUM);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, const SK::Vector3&), FUNCTION_VOID_STRING_INT32T_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, const SK::Vector3&, int32_t), FUNCTION_VOID_STRING_INT32T_VECTOR3_INT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int8_t), FUNCTION_VOID_STRING_INT8T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int8_t, int8_t), FUNCTION_VOID_STRING_INT8T_INT8T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::String&), FUNCTION_VOID_STRING_STRING);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, uint32_t), FUNCTION_VOID_STRING_UINT32T);
			SK_FUNC_TYPE_INJECT(void(int16_t), FUNCTION_VOID_INT16T);
			SK_FUNC_TYPE_INJECT(void(int16_t, const SK::Vector3&), FUNCTION_VOID_INT16T_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Array<int32_t>&, const SK::Array<SK::RawData>&), FUNCTION_VOID_STRING_ARRAYINT32T_ARRAYRAWDATA);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, float, const SK::Enum&, uint32_t), FUNCTION_VOID_STRING_FLOAT_ENUM_UINT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&, int32_t, const SK::Vector3&, const SK::Vector3&), FUNCTION_VOID_STRING_ENUM_INT32T_VECTOR3_VECTOR3);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, const SK::Enum&, uint32_t), FUNCTION_VOID_STRING_ENUM_UINT32T);
			SK_FUNC_TYPE_INJECT(void(const SK::String&, int32_t, int32_t, uint32_t), FUNCTION_VOID_STRING_INT32T_INT32T_UINT32T);
			
		default:
			assert(false);
			return std::auto_ptr<TypelessInterface>();
		}
	}


	/**
	 * \struct	BaseFunctionTypeExtractor
	 *
	 * \brief	This class is the interface for extracting information about a functions signature.
	 * 			 
	 * 			It is has different implementation (see FunctionTypeExtractor). This classes are mainly used when 
	 * 			dealing with FunctionTypeInfo. <br>
	 * 			For instance, SK::FunctionTypeInfo::injectType<BaseFunctionTypeExtractor, FunctionTypeExtractor>(info) 
	 * 			will provide a auto_ptr to a BaseFunctionTypeExtractor which points to an object of type 
	 * 			FunctionTypeExtractor<T> where T is the C++ function type corresponding to 'info'.
	 */
	 struct BaseFunctionTypeExtractor
	{
		/**
		 * \fn	virtual const SK::TypeInfo& getReturnTypeInfo()=0;
		 *
		 * \brief	Gets the TypeInfo for the return type of the function.
		 *
		 * \return	The TypeInfo of the return.
		 */

		virtual const SK::TypeInfo& getReturnTypeInfo()=0;

		/**
		 * \fn	virtual uint32_t getNumberOfParameter()=0;
		 *
		 * \brief	Gets the number of parameters of the function.
		 *
		 * \return	The number of parameters.
		 */

		virtual uint32_t getNumberOfParameter()=0;

		/**
		 * \fn	virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID)=0;
		 *
		 * \brief	Gets the TypeInfo of the ith parameter.
		 *
		 * \param	paramID	Identifier for the parameter.
		 *
		 * \return	The TypeInfo of the parameter.
		 */

		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID)=0;
	};
	/**
	 * \struct	FunctionTypeExtractor
	 *
	 * \brief	Concrete implementation of BaseFunctionTypeExtractor where the template parameter is the C++ function type
	 */
	template<typename R>
	struct FunctionTypeExtractor;

	//! \cond FUNCTION_TYPE_EXTRACTORS
	template<typename R>
	struct FunctionTypeExtractor<R()> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 0;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t /*paramID*/) 
		{
			//assert(paramID < getNumberOfParameter()); 
			return SK::Type<SK::UnknownType>::INFO;
		}
	};
	template<typename R, typename P1>
	struct FunctionTypeExtractor<R(P1)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 1;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2>
	struct FunctionTypeExtractor<R(P1, P2)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 2;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2, typename P3>
	struct FunctionTypeExtractor<R(P1, P2, P3)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 3;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4>
	struct FunctionTypeExtractor<R(P1, P2, P3, P4)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 4;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			case 3: return SK::Type<P4>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct FunctionTypeExtractor<R(P1, P2, P3, P4, P5)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 5;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			case 3: return SK::Type<P4>::INFO;
			case 4: return SK::Type<P5>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	struct FunctionTypeExtractor<R(P1, P2, P3, P4, P5, P6)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 6;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			case 3: return SK::Type<P4>::INFO;
			case 4: return SK::Type<P5>::INFO;
			case 5: return SK::Type<P6>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	struct FunctionTypeExtractor<R(P1, P2, P3, P4, P5, P6, P7)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 7;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			case 3: return SK::Type<P4>::INFO;
			case 4: return SK::Type<P5>::INFO;
			case 5: return SK::Type<P6>::INFO;
			case 6: return SK::Type<P7>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	struct FunctionTypeExtractor<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 8;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			case 3: return SK::Type<P4>::INFO;
			case 4: return SK::Type<P5>::INFO;
			case 5: return SK::Type<P6>::INFO;
			case 6: return SK::Type<P7>::INFO;
			case 7: return SK::Type<P8>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}
	};
	//! \endcond
	
	template<typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	struct FunctionTypeExtractor<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public BaseFunctionTypeExtractor
	{
		virtual const SK::TypeInfo& getReturnTypeInfo() {return SK::Type<R>::INFO;}
		virtual uint32_t getNumberOfParameter() {return 9;}
		virtual const SK::TypeInfo& getParameterTypeInfo(uint32_t paramID) 
		{
			assert(paramID < getNumberOfParameter()); 
			switch(paramID)
			{
			case 0: return SK::Type<P1>::INFO;
			case 1: return SK::Type<P2>::INFO;
			case 2: return SK::Type<P3>::INFO;
			case 3: return SK::Type<P4>::INFO;
			case 4: return SK::Type<P5>::INFO;
			case 5: return SK::Type<P6>::INFO;
			case 6: return SK::Type<P7>::INFO;
			case 7: return SK::Type<P8>::INFO;
			case 8: return SK::Type<P9>::INFO;
			default: return SK::Type<SK::UnknownType>::INFO;
			}
		}	
	};

}
