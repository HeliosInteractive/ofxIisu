#pragma once

#include <Foundation/Services/Types/RawData.h>
#include <Foundation/Services/Types/FunctionTypeInfo.h>
#include <Foundation/Services/Commands/Command.h>

extern "C" 
{
	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_getMetaInfo(IN SkCommandManager_C manager, IN SkString_C commandName, OUT SkMetaInfo_C* metainfo); 
	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_waitForReturnValue (IN SkCommandManager_C manager, IN SkTypeInfo_C type, INOUT unsigned long long* commandCallerID, OUT void* returnValue);
	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_waitForReturnValueTimed ( IN SkCommandManager_C manager, IN SkTypeInfo_C type, IN int32_t timeout, INOUT uint64_t* commandCallerID, OUT void* returnValue );
	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_isReturnValueReady (IN SkCommandManager_C manager, IN unsigned long long commandCallerID, OUT SkBool* isReady);
	IISUSDK_API SkError_C SK_SDK_DECL SkCommandManager_tryGetReturnValue (IN SkCommandManager_C manager, IN SkTypeInfo_C type, INOUT unsigned long long* commandCallerID, OUT void* returnValue);
}
template<typename T> struct CommandCallerFactory;

namespace SK {

	/**
	 * \class	CommandManager
	 *
	 * \brief	Manager for commands controlling iisu processing. 
	 */

	class CommandManager 
	{
		friend SkError_C (::SkCommandManager_getMetaInfo) (IN SkCommandManager_C manager, IN SkString_C commandName, OUT SkMetaInfo_C* metainfo);
		friend SkError_C (::SkCommandManager_waitForReturnValue) (IN SkCommandManager_C manager, IN SkTypeInfo_C type, INOUT unsigned long long* commandCallerID, OUT void* returnValue);
		friend SkError_C (::SkCommandManager_waitForReturnValueTimed) ( IN SkCommandManager_C manager, IN SkTypeInfo_C type, IN int32_t timeout, INOUT uint64_t* commandCallerID, OUT void* returnValue );
		friend SkError_C (::SkCommandManager_isReturnValueReady) (IN SkCommandManager_C manager, IN unsigned long long commandCallerID, OUT SkBool* isReady);
		friend SkError_C (::SkCommandManager_tryGetReturnValue) (IN SkCommandManager_C manager, IN SkTypeInfo_C type, INOUT unsigned long long* commandCallerID, OUT void* returnValue);

		
		friend class SK::CommandManagerProxy;
		template<typename T> friend struct ::CommandCallerFactory;
	public:

		/**
		 * \fn	virtual SK::Return<bool> CommandManager::commandIsRegistered(const SK::String& commandName)const=0;
		 *
		 * \brief	Returns if a command is registered.
		 *
		 * \param	commandName	Name of the command.
		 *
		 * \return	true if the command is registered, if successful
		 */

		virtual SK::Return<bool> commandIsRegistered(const SK::String& commandName)const=0;


		/**
		 * \fn	SK::CommandHandle<T> CommandManager::registerCommandHandle(const SK::String& name)
		 *
		 * \brief	Creates a command handle associated to the specified command.
		 *
		 * \param	name	The name of the command.
		 *
		 * \return	a CommandHandle to the command, if successful
		 */

		template<typename T>
		SK::CommandHandle<T> registerCommandHandle(const SK::String& name)
		{
			return SK::CommandHandle<T>(*this, name.ptr());
		}

		/**
		 * \fn	virtual SK::Return<SK::FunctionTypeInfo> CommandManager::getCommandType(const SK::String& commandName)const=0;
		 *
		 * \brief	Gets a command type.
		 *
		 * \param	commandName	Name of the command.
		 *
		 * \return	The command type, if successful
		 */

		virtual SK::Return<SK::FunctionTypeInfo> getCommandType(const SK::String& commandName)const=0;

		/**
		 * \fn	virtual SK::Return<SK::TypeInfo> CommandManager::getMetaInfoType(const SK::String& commandName)const=0;
		 *
		 * \brief	Gets the type of the MetaInfo associated to a command
		 *
		 * \param	commandName	Name of the command.
		 *
		 * \return	The meta information type, if successful
		 */

		virtual SK::Return<SK::TypeInfo> getMetaInfoType(const SK::String& commandName)const=0;

		/**
		 * \fn	virtual SK::Return<SK::Attributes> CommandManager::getAttributes(const SK::String& commandName)const=0;
		 *
		 * \brief	Gets the command attributes.
		 *
		 * \param	commandName	Name of the command.
		 *
		 * \return	The attributes, if successful.
		 */

		virtual SK::Return<SK::Attributes> getAttributes(const SK::String& commandName)const=0;

		/**
		 * \fn	SK::Return< SK::MetaInfo<T> > CommandManager::getMetaInfo(const SK::String& commandName)const
		 *
		 * \brief	Gets the meta information associated to a command.
		 *
		 * \param	commandName	Name of the command.
		 *
		 * \return	The meta information, if successful.
		 */

		template<typename T>
		SK::Return< SK::MetaInfo<T> > getMetaInfo(const SK::String& commandName)const
		{
			SK::Return<SK::RawData> res = getMetaInfoImpl(commandName, SK::Type< SK::MetaInfo<T> >::INFO);
			RETURN_IF_FAILED(res) ;
			return res.get().getRef< SK::MetaInfo<T> >();
		}

		/**
		 * \fn	virtual SK::Return<SK::String> CommandManager::getCommandName(uint32_t index) = 0;
		 *
		 * \brief	Retrieve the Command name indexed by the parameter index
		 *
		 * \param	index	Zero-based index of the.
		 *
		 * \return	the name of the command associated to the index, if successful
		 */

		virtual SK::Return<SK::String> getCommandName(uint32_t index)  = 0;


		/**
		 * \fn	virtual SK::Return<uint32_t> CommandManager::getCommandCount() = 0;
		 *
		 * \brief	Retrieve the number of available commands
		 *
		 * \return	 an integer containing the number of commands items in the list.
		 */

		virtual SK::Return<uint32_t> getCommandCount()  = 0;

	protected:
		virtual SK::Return<SK::RawData> getMetaInfoImpl(const SK::String& commandName, const SK::TypeInfo& typeInfo)const=0;
		virtual ~CommandManager() {} ;
		virtual SK::Result sendCommand(const SK::String&  sCmd, const SK::Array<SK::RawData>& params, const SK::FunctionTypeInfo& typeInfo, uint64_t& commandCallerID, bool dropReturn = false) = 0 ;
		virtual SK::Result waitForReturnValue(uint64_t& commandCallerID, SK::RawData &returnValue, int32_t timeout = 0) =0 ;
		virtual SK::Return<bool> isReturnValueReady(uint64_t commandCallerID) = 0 ;
		virtual SK::Result tryGetReturnValue(uint64_t& commandCallerID, SK::RawData& returnValue) = 0 ;

	};
} 
