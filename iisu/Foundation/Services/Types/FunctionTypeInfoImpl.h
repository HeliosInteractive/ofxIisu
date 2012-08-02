#pragma once

#include <Foundation/DataTypes/Enumeration/Enum.h>
#include <Foundation/DataTypes/MetaInformation/Attributes.h>
#include <Foundation/Services/Types/TypeInfoDefinition.h>
#include <Platform/SkPlatform.h>
#include <iostream>
#include <memory>
#include <Foundation/Services/Types/TypeInfoImpl.h>



namespace SK
{
	class TypeInfo;

	namespace {template<typename T> struct FunctionType;}

	namespace details {using SK::FunctionType;}

  #define SK_FUNC_TYPE_DEFINITION \
		template<uint32_t N> \
		struct enumerator {static const uint32_t value=N; typedef enumerator<N+1> next;};\

	#define SK_FUNC_TYPE_DEF(X) \
		typedef enumerator< X##_ID > X##_T

	#define SK_FUNC_TYPE_ID(TYPE, X, NAME) \
		template<> const FunctionTypeInfo FunctionType< TYPE >::INFO = FunctionTypeInfo(FunctionTypeInfo::X##_T(), NAME); 

	#define SK_FUNC_TYPE_INJECT(X, NAME) \
		case SK::NAME##_ID: return (std::auto_ptr<TypelessInterface>)std::auto_ptr<TypedImplementation< X > >(new TypedImplementation< X >())

	#define SK_FUNC_TYPE_ID_SWITCH_CASE(X, NAME) \
		case SK::NAME##_ID : return SK::FunctionType< X >::INFO

	/**
	 * \class FunctionTypeInfo
	 *
	 * \brief	Describe a function type manipulated in iisu.
	 */

	class IISUSDK_API FunctionTypeInfo
	{
		template<typename T>
		friend struct SK::details::FunctionType;
	public:
		typedef uint32_t innerType_t;

	private:
		SK_FUNC_TYPE_DEFINITION	

	private:
		typedef FunctionTypeInfo self_t;

	public:
		/**
		 * \fn FunctionTypeInfo()
		 *
		 * \brief	Default Constructor, create the FunctionTypeInfo of a SK::UnknownType() function.
		 */

		FunctionTypeInfo();

		/**
		 * \fn template<uint32_t N> FunctionTypeInfo( const enumerator<N>&, const char* name)
		 *
		 * \brief	This constructor is used by the FunctionType class. You should never use this constructor directly.
		 */
		template<uint32_t N>
		FunctionTypeInfo( const enumerator<N>&, const char* name) :m_typeID(N), m_name(name)
		{
		}

	public:
		~FunctionTypeInfo();

	private:
			SK_FUNC_TYPE_DEF(FUNCTION_UNKNOWN_TYPE);
			SK_FUNC_TYPE_DEF(FUNCTION_INTERNAL_TYPE);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING);
			
			

			SK_FUNC_TYPE_DEF(FUNCTION_BOOL_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_BOOL_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_INT32T_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_UINT32T_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_INT32T_STRING_TYPEINFO);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNARRAYSTRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNARRAYSTRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNARRAYVECTOR2_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNARRAYVECTOR2I_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNATTRIBUTES_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNBOOL_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNBOOL_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNBOOL_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNFUNCTIONTYPEINFO_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNINT32T_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNINT32T_STRING_TYPEINFO);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNINT32T_STRING_TYPEINFO_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNRAWDATA_INT32T_TYPEINFO);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNSTRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNSTRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_ARRAYSTRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_INT32T_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_INT32T_RAWDATA);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_INT32T_TYPEINFO);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_STRING_STRING_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_STRING_STRING_FLOAT);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_STRING_STRING_VECTOR2I);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_STRING_STRING_VECTOR2);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_VOID);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNRAWDATA_STRING_TYPEINFO);
			SK_FUNC_TYPE_DEF(FUNCTION_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_STRING_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_STRING_UINT32T_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNTYPEINFO_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_UINT32T_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_UINT32T_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT32T_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT32T_VECTOR3);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT8T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT8T_INT8T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_ENUM);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_ENUM);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_ENUM_VECTOR3);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_STRING_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_STRING_ARRAYRAWDATA_FUNCTIONTYPEINFO);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_ERROR_BOOL);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT32T_ENUM);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT32T_VECTOR3);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT32T_VECTOR3_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT8T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT8T_INT8T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNSTRING_INT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNBOOL_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVECTOR2I_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNFLOAT_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVECTOR2_STRING_STRING);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT16T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_INT16T_VECTOR3);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_ENUM);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_ARRAYINT32T_ARRAYRAWDATA);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_ARRAYFRAME);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_FLOAT_ENUM_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_ENUM_INT32T_VECTOR3_VECTOR3);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_ENUM_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_VOID_STRING_INT32T_INT32T_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_UINT32T);
			SK_FUNC_TYPE_DEF(FUNCTION_RETURNVOID_ENUM_ARRAYINT16T);

	public:
		/**
		 * \fn		friend bool operator==(const self_t& lhs, const self_t& rhs)
		 *
		 * \brief	Compare two FunctionTypeInfo.
		 *
		 * \param	lhs		left hand side FunctionTypeInfo
		 * \param	rhs		right hand side FunctionTypeInfo
		 *
		 * \return	true if the two object are equals, false otherwise.
		 */

		friend bool operator==(const self_t& lhs, const self_t& rhs) { return (lhs.typeID()==rhs.typeID()); }

		/**
		 * \fn		friend bool operator!=(const self_t& lhs, const self_t& rhs)
		 *
		 * \brief	Compare two FunctionTypeInfo.
		 *
		 * \param	lhs		left hand side FunctionTypeInfo
		 * \param	rhs		right hand side FunctionTypeInfo
		 *
		 * \return	true if the two object are different, false otherwise.
		 */

		friend bool operator!=(const self_t& lhs, const self_t& rhs) { return !(lhs==rhs); }

	public:
		/**
		 * \fn innerType_t typeID() const
		 *
		 * \brief	Gets the integer corresponding to this FunctionTypeInfo.
		 * 
		 * \return	The integer corresponding to this FunctionTypeInfo.
		 *
		 * \sa	SKFunctionTypeInfoDefinition
		 */

		innerType_t typeID() const { return m_typeID; }

		/**
		 * \fn const char* name() const
		 *
		 * \brief	Gets a textual description of this FunctionTypeInfo.
		 * 
		 * \return	A textual description of this FunctionTypeInfo.
		 */

		const char* name() const { return m_name; }
		
	public:
		/**
		 * \fn	static std::auto_ptr<TypelessInterface> injectType(const FunctionTypeInfo& typeInfo);
		 *
		 * \brief	Inject back the C++ function type corresponding to the FunctionTypeInfo.
		 *
		 * \param	typeInfo	The FunctionTypeInfo.
		 *
		 * \return	A base pointer of the TypelessInterface pointing to a TypedImplementation instantiated with the proper C++ function type corresponding to the FunctionTypeInfo.
		 * The pointer is returned as a std::auto_ptr to automated the mememory management.
		 */		
		 
		 template<class TypelessInterface, template <typename T> class TypedImplementation>
		static std::auto_ptr<TypelessInterface> injectType(const FunctionTypeInfo& typeInfo);


		/**
		 * \fn	static std::auto_ptr<TypelessInterface> injectEventType(const FunctionTypeInfo& typeInfo);
		 *
		 * \brief	Inject back the C++ function type corresponding to the TypeInfo.
		 *
		 * \param	typeInfo	The FunctionTypeInfo.
		 *
		 * \return	A base pointer of the TypelessInterface pointing to a TypedImplementation instantiated with the proper C++ function type corresponding to the FunctionTypeInfo.
		 * The pointer is returned as a std::auto_ptr to automated the mememory management.
		 * \warning This function only handle the FunctionTypeInfo that return void. For all other function type it will return an empty auto_ptr.
		 */		

		template<class TypelessInterface, template <typename T> class TypedImplementation>
		static std::auto_ptr<TypelessInterface> injectEventType(const FunctionTypeInfo& typeInfo);

		/**
		 * \fn	static FunctionTypeInfo createFromID(innerType_t id);
		 *
		 * \brief	Create a FunctionTypeInfo from a unsigned interger
		 *
		 * \param	id	The FunctionTypeInfo id.
		 *
		 * \return	The FunctionTypeInfo
		 */		
		static FunctionTypeInfo createFromID(innerType_t id);

	private:
		innerType_t m_typeID;
		const char* m_name;
	};

	typedef UnknownType UnknownFunctionType() ;
	typedef InternalType InternalFunctionType() ;

	namespace 
	{	
		/**
		 * \struct	FunctionType
		 *
		 * \brief	A template class that is use to create the FunctionTypeInfo for the template argument. 
		 * 			
		 * 			For example, SK::FunctionTypeInfo<void(const SK::String&)>::INFO gives the TypeInfo for a function void(const SK::String&).
		 */

		template<typename T> struct FunctionType
		{
			///< The FunctionTypeInfo corresponding to T
			static const FunctionTypeInfo INFO;
		};
            SK_FUNC_TYPE_ID(UnknownFunctionType,															FUNCTION_UNKNOWN_TYPE,					  				"Unknown Function Type");
            SK_FUNC_TYPE_ID(InternalFunctionType,															FUNCTION_INTERNAL_TYPE,									"Internal Function Type");
            SK_FUNC_TYPE_ID(void(const SK::String&),FUNCTION_VOID_STRING,"FUNCTION: Void(String)");
			
		
			SK_FUNC_TYPE_ID(bool(bool)                                                      , FUNCTION_BOOL_BOOL                                                             , "FUNCTION : bool(bool)");                                                      
			SK_FUNC_TYPE_ID(bool(const SK::String&)                                         , FUNCTION_BOOL_STRING                                                           , "FUNCTION : bool(const String&)");                                             
			SK_FUNC_TYPE_ID(int32_t()                                                       , FUNCTION_INT32T                                                                , "FUNCTION : int32_t()");                                                       
			SK_FUNC_TYPE_ID(int32_t(bool)                                                   , FUNCTION_INT32T_BOOL                                                           , "FUNCTION : int32_t(bool)");                                                   
			SK_FUNC_TYPE_ID(uint32_t(bool)                                                  , FUNCTION_UINT32T_BOOL                                                          , "FUNCTION : uint32_t(bool)");                                                  
			SK_FUNC_TYPE_ID(int32_t(const SK::String&, const SK::TypeInfo&)                 , FUNCTION_INT32T_STRING_TYPEINFO                                                , "FUNCTION : int32_t(const String&, const TypeInfo&)");                         
			SK_FUNC_TYPE_ID(SK::Return< SK::Array<SK::String> >()                           , FUNCTION_RETURNARRAYSTRING                                                     , "FUNCTION : Return< Array<String> >()");                                       
			SK_FUNC_TYPE_ID(SK::Return< SK::Array<SK::String> >(const SK::String&)          , FUNCTION_RETURNARRAYSTRING_STRING                                              , "FUNCTION : Return< Array<String> >(const String&)");                          
			SK_FUNC_TYPE_ID(SK::Return< SK::Array<SK::Vector2> >(const SK::String&, const SK::String&)          , FUNCTION_RETURNARRAYVECTOR2_STRING_STRING                                                          , "FUNCTION : Return< Array<Vector2> >(const String&, const String&)");                              
			SK_FUNC_TYPE_ID(SK::Return< SK::Array<SK::Vector2i> >(const SK::String&, const SK::String&)         , FUNCTION_RETURNARRAYVECTOR2I_STRING_STRING                                                         , "FUNCTION : Return< Array<Vector2i> >(const String&, const String&)");                             
			SK_FUNC_TYPE_ID(SK::Return< SK::Attributes>(const SK::String&)                                      , FUNCTION_RETURNATTRIBUTES_STRING                                                                   , "FUNCTION : Return< Attributes>(const String&)");                                                  
			SK_FUNC_TYPE_ID(SK::Return<bool>(bool)                                                              , FUNCTION_RETURNBOOL_BOOL                                                                           , "FUNCTION : Return<bool>(bool)");                                                                  
			SK_FUNC_TYPE_ID(SK::Return<bool>(int32_t)                                                           , FUNCTION_RETURNBOOL_INT32T                                                                         , "FUNCTION : Return<bool>(int32_t)");                                                               
			SK_FUNC_TYPE_ID(SK::Return<bool>(const SK::String&)                                                 , FUNCTION_RETURNBOOL_STRING                                                                         , "FUNCTION : Return<bool>(const String&)");                                                         
			SK_FUNC_TYPE_ID(SK::Return<SK::FunctionTypeInfo>(const SK::String&)                                 , FUNCTION_RETURNFUNCTIONTYPEINFO_STRING                                                             , "FUNCTION : Return<FunctionTypeInfo>(const String&)");                                             
			SK_FUNC_TYPE_ID(SK::Return<int32_t>(const SK::String&)                                              , FUNCTION_RETURNINT32T_STRING                                                                       , "FUNCTION : Return<int32_t>(const String&)");                                                      
			SK_FUNC_TYPE_ID(SK::Return<int32_t>(const SK::String&, const SK::TypeInfo&)                         , FUNCTION_RETURNINT32T_STRING_TYPEINFO                                                              , "FUNCTION : Return<int32_t>(const String&, const TypeInfo&)");                                     
			SK_FUNC_TYPE_ID(SK::Return<int32_t>(const SK::String&, const SK::TypeInfo&, bool)                   , FUNCTION_RETURNINT32T_STRING_TYPEINFO_BOOL                                                         , "FUNCTION : Return<int32_t>(const String&, const TypeInfo&, bool)");                               
			SK_FUNC_TYPE_ID(SK::Return<SK::RawData>(int32_t,const SK::TypeInfo &)                               , FUNCTION_RETURNRAWDATA_INT32T_TYPEINFO                                                             , "FUNCTION : Return<RawData>(int32_t,const TypeInfo &)");                                           
			SK_FUNC_TYPE_ID(SK::Return<SK::String>()                                                            , FUNCTION_RETURNSTRING                                                                              , "FUNCTION : Return<String>()");                                                                    
			SK_FUNC_TYPE_ID(SK::Return<SK::String>(const SK::String&)                                           , FUNCTION_RETURNSTRING_STRING                                                                       , "FUNCTION : Return<String>(const String&)");                                                       
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::Array<SK::String>&,const SK::String &)                   , FUNCTION_RETURNVOID_ARRAYSTRING_STRING                                                             , "FUNCTION : Return<void>(const Array<String>&,const String &)");                                   
			SK_FUNC_TYPE_ID(SK::Return<void>(bool)                                                              , FUNCTION_RETURNVOID_BOOL                                                                           , "FUNCTION : Return<void>(bool)");                                                                  
			SK_FUNC_TYPE_ID(SK::Return<void>(int32_t, bool)                                                     , FUNCTION_RETURNVOID_INT32T_BOOL                                                                    , "FUNCTION : Return<void>(int32_t, bool)");                                                         
			SK_FUNC_TYPE_ID(SK::Return<void>(int32_t,const SK::RawData &)                                       , FUNCTION_RETURNVOID_INT32T_RAWDATA                                                                 , "FUNCTION : Return<void>(int32_t,const RawData &)");                                               
			SK_FUNC_TYPE_ID(SK::Return<void>(int32_t, const SK::TypeInfo&)                                      , FUNCTION_RETURNVOID_INT32T_TYPEINFO                                                                , "FUNCTION : Return<void>(int32_t, const TypeInfo&)");                                              
			SK_FUNC_TYPE_ID(SK::Return<void>(int32_t)                                                           , FUNCTION_RETURNVOID_INT32T                                                                         , "FUNCTION : Return<void>(int32_t)");                                                               
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::String&)                                                 , FUNCTION_RETURNVOID_STRING                                                                         , "FUNCTION : Return<void>(const String&)");                                                         
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::String&, const SK::String&)                              , FUNCTION_RETURNVOID_STRING_STRING                                                                  , "FUNCTION : Return<void>(const String&, const String&)");                                          
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::String&, const SK::String&, bool)                        , FUNCTION_RETURNVOID_STRING_STRING_BOOL                                                             , "FUNCTION : Return<void>(const String&, const String&, bool)");                                    
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::String&, const SK::String&, float)                       , FUNCTION_RETURNVOID_STRING_STRING_FLOAT                                                            , "FUNCTION : Return<void>(const String&, const String&, float)");                                   
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::String&, const SK::String&, const SK::Vector2i &)        , FUNCTION_RETURNVOID_STRING_STRING_VECTOR2I                                                         , "FUNCTION : Return<void>(const String&, const String&, const Vector2i &)");                        
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::String&, const SK::String&, const SK::Vector2 &)         , FUNCTION_RETURNVOID_STRING_STRING_VECTOR2                                                          , "FUNCTION : Return<void>(const String&, const String&, const Vector2 &)");                         
			SK_FUNC_TYPE_ID(SK::Return<void>(void)                                                              , FUNCTION_RETURNVOID_VOID                                                                           , "FUNCTION : Return<void>(void)");                                                                  
			SK_FUNC_TYPE_ID(SK::Return<SK::RawData>(const SK::String &,const SK::TypeInfo &)                    , FUNCTION_RETURNRAWDATA_STRING_TYPEINFO                                                             , "FUNCTION : Return<RawData>(const String &,const TypeInfo &)");                                    
			SK_FUNC_TYPE_ID(SK::String(const SK::String&)                                                       , FUNCTION_STRING_STRING                                                                             , "FUNCTION : String(const String&)");                                                               
			SK_FUNC_TYPE_ID(SK::String(uint32_t)                                                                , FUNCTION_STRING_UINT32T                                                                            , "FUNCTION : String(uint32_t)");                                                                    
			SK_FUNC_TYPE_ID(SK::String(uint32_t, bool)                                                          , FUNCTION_STRING_UINT32T_BOOL                                                                       , "FUNCTION : String(uint32_t, bool)");                                                              
			SK_FUNC_TYPE_ID(SK::Return<SK::TypeInfo>(const SK::String&)                                         , FUNCTION_RETURNTYPEINFO_STRING                                                                     , "FUNCTION : Return<TypeInfo>(const String&)");                                                     
			SK_FUNC_TYPE_ID(uint32_t()                                                                          , FUNCTION_UINT32T                                                                                   , "FUNCTION : uint32_t()");                                                                          
			SK_FUNC_TYPE_ID(uint32_t(const SK::String&)                                                         , FUNCTION_UINT32T_STRING                                                                            , "FUNCTION : uint32_t(const String&)");                                                             
			SK_FUNC_TYPE_ID(uint32_t(const SK::String&, const SK::String&)                                      , FUNCTION_UINT32T_STRING_STRING                                                                     , "FUNCTION : uint32_t(const String&, const String&)");                                              
			SK_FUNC_TYPE_ID(void()                                                                              , FUNCTION_VOID                                                                                      , "FUNCTION : void()");                                                                              
			SK_FUNC_TYPE_ID(void(bool)                                                                          , FUNCTION_VOID_BOOL                                                                                 , "FUNCTION : void(bool)");                                                                          
			SK_FUNC_TYPE_ID(void(int32_t)                                                                       , FUNCTION_VOID_INT32T                                                                               , "FUNCTION : void(int32_t)");                                                                       
			SK_FUNC_TYPE_ID(void(int32_t, int32_t)                                                              , FUNCTION_VOID_INT32T_INT32T                                                                        , "FUNCTION : void(int32_t, int32_t)");                                                              
			SK_FUNC_TYPE_ID(void(int32_t, const SK::Vector3&)                                                   , FUNCTION_VOID_INT32T_VECTOR3                                                                       , "FUNCTION : void(int32_t, const Vector3&)");                                                       
			SK_FUNC_TYPE_ID(void(int8_t)                                                                        , FUNCTION_VOID_INT8T                                                                                , "FUNCTION : void(int8_t)");                                                                        
			SK_FUNC_TYPE_ID(void(int8_t,int8_t)                                                                 , FUNCTION_VOID_INT8T_INT8T                                                                          , "FUNCTION : void(int8_t,int8_t)");                                                                 
			SK_FUNC_TYPE_ID(void(const SK::Enum&)                                                               , FUNCTION_VOID_ENUM                                                                                 , "FUNCTION : void(const Enum&)");                                                                   
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::Enum&)                                            , FUNCTION_VOID_STRING_ENUM                                                                          , "FUNCTION : void(const String&, const Enum&)");                                                    
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::Enum&, const SK::Vector3&)                        , FUNCTION_VOID_STRING_ENUM_VECTOR3                                                                  , "FUNCTION : void(const String&, const Enum&, const Vector3&)");                                    
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::String&, bool)                                    , FUNCTION_VOID_STRING_STRING_BOOL                                                                   , "FUNCTION : void(const String&, const String&, bool)");                                            
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::String&, const SK::Array<SK::RawData>&, const SK::FunctionTypeInfo&)  , FUNCTION_VOID_STRING_STRING_ARRAYRAWDATA_FUNCTIONTYPEINFO                                                              , "FUNCTION : void(const String&, const String&, const Array<RawData>&, const FunctionTypeInfo&)");                      
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::Error&, bool)                                                         , FUNCTION_VOID_STRING_ERROR_BOOL                                                                                        , "FUNCTION : void(const String&, const Error&, bool)");                                                                 
			SK_FUNC_TYPE_ID(void(const SK::String&, int32_t)                                                                        , FUNCTION_VOID_STRING_INT32T                                                                                            , "FUNCTION : void(const String&, int32_t)");                                                                            
			SK_FUNC_TYPE_ID(void(const SK::String&, int32_t, const SK::Enum&)                                                       , FUNCTION_VOID_STRING_INT32T_ENUM                                                                                       , "FUNCTION : void(const String&, int32_t, const Enum&)");                                                               
			SK_FUNC_TYPE_ID(void(const SK::String&, int32_t, const SK::Vector3&)                                                    , FUNCTION_VOID_STRING_INT32T_VECTOR3                                                                                    , "FUNCTION : void(const String&, int32_t, const Vector3&)");                                                            
			SK_FUNC_TYPE_ID(void(const SK::String&, int32_t, const SK::Vector3&, int32_t)                                           , FUNCTION_VOID_STRING_INT32T_VECTOR3_INT32T                                                                             , "FUNCTION : void(const String&, int32_t, const Vector3&, int32_t)");                                                   
			SK_FUNC_TYPE_ID(void(const SK::String&, int8_t)                                                                         , FUNCTION_VOID_STRING_INT8T                                                                                             , "FUNCTION : void(const String&, int8_t)");                                                                             
			SK_FUNC_TYPE_ID(void(const SK::String&, int8_t, int8_t)                                                                 , FUNCTION_VOID_STRING_INT8T_INT8T                                                                                       , "FUNCTION : void(const String&, int8_t, int8_t)");                                                                     
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::String&)                                                              , FUNCTION_VOID_STRING_STRING                                                                                            , "FUNCTION : void(const String&, const String&)");                                                                      
			SK_FUNC_TYPE_ID(void(const SK::String&, uint32_t)                                                                       , FUNCTION_VOID_STRING_UINT32T                                                                                           , "FUNCTION : void(const String&, uint32_t)");                                                                           
			SK_FUNC_TYPE_ID(SK::Return<SK::String>(int32_t)                                                                         , FUNCTION_RETURNSTRING_INT32T                                                                                           , "FUNCTION : Return<String>(int32_t)");                                                                                 
			SK_FUNC_TYPE_ID(SK::Return<int32_t>()                                                                                   , FUNCTION_RETURNINT32T                                                                                                  , "FUNCTION : Return<int32_t>()");                                                                                       
			SK_FUNC_TYPE_ID(SK::Return<bool>(const SK::String&, const SK::String&)                                                  , FUNCTION_RETURNBOOL_STRING_STRING                                                                                      , "FUNCTION : Return<bool>(const String&, const String&)");                                                              
			SK_FUNC_TYPE_ID(SK::Return<SK::Vector2i>(const SK::String&, const SK::String&)                                          , FUNCTION_RETURNVECTOR2I_STRING_STRING                                                                                  , "FUNCTION : Return<Vector2i>(const String&, const String&)");                                                          
			SK_FUNC_TYPE_ID(SK::Return<float>(const SK::String&, const SK::String&)                                                 , FUNCTION_RETURNFLOAT_STRING_STRING                                                                                     , "FUNCTION : Return<float>(const String&, const String&)");                                                             
			SK_FUNC_TYPE_ID(SK::Return<SK::Vector2 >(const SK::String&, const SK::String&)                                          , FUNCTION_RETURNVECTOR2_STRING_STRING                                                                                   , "FUNCTION : Return<Vector2 >(const String&, const String&)");                                                          
			SK_FUNC_TYPE_ID(void(int16_t)                                                                                           , FUNCTION_VOID_INT16T                                                                                                   , "FUNCTION : void(int16_t)");                                                                                           
			SK_FUNC_TYPE_ID(void(int16_t, const SK::Vector3&)                                                                       , FUNCTION_VOID_INT16T_VECTOR3                                                                                           , "FUNCTION : void(int16_t, const Vector3&)");                                                                           
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::Enum&)                                                                       , FUNCTION_RETURNVOID_ENUM                                                                                               , "FUNCTION : Return<void>(const Enum&)");                                                                               
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::Array<int32_t>&, const SK::Array<SK::RawData>&)                       , FUNCTION_VOID_STRING_ARRAYINT32T_ARRAYRAWDATA                                                                          , "FUNCTION : void(const String&, const Array<int32_t>&, const Array<RawData>&)");                                       
			SK_FUNC_TYPE_ID(void (const SK::Array<SK::Frame>&)                                                                      , FUNCTION_VOID_ARRAYFRAME                                                                                               , "FUNCTION : void (const Array<Frame>&)");                                                                              
			SK_FUNC_TYPE_ID(void(const SK::String&, float, const SK::Enum&, uint32_t)                                               , FUNCTION_VOID_STRING_FLOAT_ENUM_UINT32T                                                                                , "FUNCTION : void(const String&, float, const Enum&, uint32_t)");                                                       
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::Enum&, int32_t, const SK::Vector3&, const SK::Vector3&)               , FUNCTION_VOID_STRING_ENUM_INT32T_VECTOR3_VECTOR3                                                                       , "FUNCTION : void(const String&, const Enum&, int32_t, const Vector3&, const Vector3&)");                               
			SK_FUNC_TYPE_ID(void(const SK::String&, const SK::Enum&, uint32_t)                                                      , FUNCTION_VOID_STRING_ENUM_UINT32T                                                                                      , "FUNCTION : void(const String&, const Enum&, uint32_t)");                                                              
			SK_FUNC_TYPE_ID(void(const SK::String&, int32_t, int32_t, uint32_t)                                                     , FUNCTION_VOID_STRING_INT32T_INT32T_UINT32T                                                                             , "FUNCTION : void(const String&, int32_t, int32_t, uint32_t)");                                                         
			SK_FUNC_TYPE_ID(SK::Return<void>(uint32_t)                                                                              , FUNCTION_RETURNVOID_UINT32T                                                                                            , "FUNCTION : Return<void>(uint32_t)");                                                                                  
			SK_FUNC_TYPE_ID(SK::Return<void>(const SK::Enum&, const SK::Array<int16_t>&)                                            , FUNCTION_RETURNVOID_ENUM_ARRAYINT16T                                                                                   , "FUNCTION : Return<void>(const Enum&, const Array<int16_t>&)");                                                        

	}
}

