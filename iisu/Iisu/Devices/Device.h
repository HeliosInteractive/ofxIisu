
#pragma once


#ifdef __cplusplus

#include <Foundation/DataTypes/String/String.h>
#include <Framework/Errors/Return.h>
#include <cstddef>

#include <Foundation/Services/Types/TypeInfo.h>
#include <Foundation/Services/Types/FunctionTypeInfo.h>
#include <Foundation/Services/Types/RawData.h>
#include <Foundation/Services/Events/EventManager.h>
#include <Foundation/Services/Commands/CommandManager.h>
#include <Foundation/Services/Types/RawData.h>
#include <Foundation/DataTypes/MetaInformation/MetaInfo.h>
#include <Foundation/DataTypes/MetaInformation/Attributes.h>
#include <Iisu/Devices/DataFrame.h>

extern "C" 
{
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getMetaInfo				(IN SkDevice_C device, IN SkString_C dataPath, OUT SkMetaInfo_C* metainfo);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_setParameter				(IN SkDevice_C device, IN int32_t paramID, IN const void* dataSent, IN SkTypeInfo_C type);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_getParameter				(IN SkDevice_C device, IN int32_t paramID, IN SkTypeInfo_C type, OUT void* parameterReturned);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_registerParameter		(IN SkDevice_C device, IN SkString_C path, IN SkTypeInfo_C typeInfo, OUT int32_t* paramID);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_unregisterParameter		( IN SkDevice_C device, IN int32_t paramID );
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_registerData				(IN SkDevice_C device, IN SkString_C path, IN SkTypeInfo_C type, OUT int* dataID);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_unregisterData			(IN SkDevice_C device, IN int dataID);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_setDataAutoUpdateFlag	(IN SkDevice_C device, IN int32_t dataID, IN bool autoUpdate);
	IISUSDK_API SkError_C SK_SDK_DECL SkDevice_isDataAutoUpdated		(IN SkDevice_C device, IN int32_t dataID, OUT SkBool* isAutoUpdated);
}

namespace SK {


template <typename T> class DataHandle;
template <typename T> class ParameterHandle;

	/**
	 * \struct	Device
	 *
	 * \brief	iisu main communication abstract class. The SK::Device is an abstract object that hide the entire iisu processing. 
	 */
	struct Device
	{


	public:

		/**
		 * \enum	StatusMask
		 *
		 * \brief	Values that represent device status bits. 
		 */

		enum StatusMask
		{
			INVALID = 0,
			INITIALIZED = 1,	/*!< Get the initialization state of the device. */
			DATAVALID = 2,		/*!< Get the data validity state of the device. */
			PLAYING = 4,		/*!< Get the play execution state of the device. */
			FINISHED = 8,		/*!< Get the device destruction state of the device. (Used for device destruction notification) */
			ERRORSTATE = 16		/*!< Get the error state of the device. */
		};

		/**
		 * \struct	Configuration
		 *
		 * \brief	The device configuration structure. 
		 */

		struct Configuration 
		{
			/**
			 * \fn	Configuration()
			 *
			 * \brief	Default constructor.
			 */

			Configuration():
			m_cameraDriven(true),
			m_startServer(false),
			m_needExtraBuffer(false)
			{
			} ;

			///< switch the execution mode between camera driven and application driven mode (cf. Execution Model in Developer guide for more details)
			bool m_cameraDriven;
			///< set to true to start a server
			bool m_startServer;
			///< true to add and extra buffer between the iisu processing and the device. 
			bool m_needExtraBuffer;
			///< specifies a movie file that will override the one declared in the configuration file
			SK::String m_moviePath ;
			///< specifies a camera name that will override the source declared in the configuration file
			SK::String m_cameraName ;
		};

	public:
		/*!
			
		*/
		//! ...

		/**
		 * \fn	virtual SK::Device::StatusMask getStatus() const = 0;
		 *
		 * \brief	Get the status of the device.  Use \sa StatusMask bit mask to get a specific device state value.
		 *
		 * \return	The combined status mask representing the state.
		 */

		virtual SK::Device::StatusMask getStatus() const = 0;


		/**
		 * \fn	virtual int32_t getFrameId() const = 0;
		 *
		 * \brief	Gets the frame identifier of the \sa DataFrame held by the device.
		 *
		 * \return	The frame identifier.
		 */

		virtual int32_t getFrameId() const = 0;

		/**
		 * \fn	virtual SK::Result updateFrame(bool waitForNewFrame = false,
		 * 		uint32_t timeout = 2000) = 0;
		 *
		 * \brief	Ask iisu for the last available processed data frame
		 *
		 * \param	waitForNewFrame	(optional) specifies if the call should wait for a new incoming frame.
		 * \param	timeout		   	(optional) the time to wait for a frame before returning (in millisecond).
		 *
		 * \return	a \sa SK::Result that specifies if the call was successful or not
		 */
		virtual SK::Result updateFrame(bool waitForNewFrame = false, uint32_t timeout = 2000) = 0;

		/**
		 * \fn	virtual void lockFrame() = 0;
		 *
		 * \brief	Locks the frame.
		 * 			
		 *  The frame is locked and can be used by get function (through DataHandle). This lock will only block the 
		 *  updateFrame function. The next time releaseFrame is called it will remove any previous lock.
		 */
		virtual void lockFrame() = 0;

		/**
		 * \fn	virtual void releaseFrame() = 0;
		 *
		 * \brief	Releases the frame. This tells the device you don't need to do any data reading and the frame can
		 * 			be updated on next updateFrame. Failing to call this will lead the device to timeout on updateFrame
		 */

		virtual void releaseFrame() = 0;

		/**
		 * \fn	virtual DataFrame& getDataFrame() = 0;
		 *
		 * \brief	Gets the current data frame.
		 *
		 * \return	a reference to the current data frame.
		 */

		virtual DataFrame& getDataFrame() = 0;


		/**
		 * \fn	virtual SK::Return<SK::String> getDataName(uint32_t index,
		 * 		bool onlyRegistredData = false) const = 0;
		 *
		 * \brief	Retrieve the name of the data identified by the index
		 *
		 * \param	index the position in the list of data (use the getDataCount() method to know the number of list items)
		 * \param	onlyRegistredData	(optional) flag can be used if the user wishes to list only the data he registered
		 *
		 * \return	the name of the data associated to the index, if successful
		 */

		virtual SK::Return<SK::String> getDataName(uint32_t index, bool onlyRegistredData = false) const = 0;

		/**
		 * \fn	virtual SK::Return<uint32_t> getDataCount(bool onlyRegistredData = false) const = 0;
		 *
		 * \brief	Retrieve the number of data items in the list.
		 *
		 * \param	onlyRegistredData	(optional) flag that can be used if the user wishes to list only the data he registered.
		 *
		 * \return	an integer containing the number of available data, if successful
		 */

		virtual SK::Return<uint32_t> getDataCount(bool onlyRegistredData = false) const = 0;

		//! ...

		/**
		 * \fn	virtual SK::Return<SK::String> getParameterName(uint32_t index) const = 0;
		 *
		 * \brief	Retrieve the parameter indexed by the parameter index.
		 *
		 * \param	index	the position in the list of data (use the getParameterCount() method to know the number of list items)
		 *
		 * \return	the name of the parameter associated to the index, if successful
		 */

		virtual SK::Return<SK::String> getParameterName(uint32_t index) const = 0;

		/**
		 * \fn	virtual SK::Return<int32_t> getParameterCount() const = 0;
		 *
		 * \brief	Retrieve the number of available parameters

		 *
		 * \return	an integer containing the number of parameter items in the list, if successful.
		 */

		virtual SK::Return<int32_t> getParameterCount() const = 0;

		/**
		 * \fn	virtual SK::Result start() = 0;
		 *
		 * \brief	Starts the device.
		 *
		 * \return	a Result specifying if the call was successful or not.
		 */

		virtual SK::Result start() = 0; 

		/**
		 * \fn	virtual SK::Result start() = 0;
		 *
		 * \brief	Stops the device.
		 *
		 * \return	a Result specifying if the call was successful or not.
		 */

		virtual SK::Result stop(bool waitForStopped = true) = 0;

		/**
		 * \fn	virtual SK::CommandManager& getCommandManager() =0;
		 *
		 * \brief	Gets the command manager.
		 *
		 * \return	a reference to the command manager.
		 */

		virtual SK::CommandManager& getCommandManager() =0 ; 

		/**
		 * \fn	virtual SK::EventManager& getEventManager() =0;
		 *
		 * \brief	Gets the event manager.
		 *
		 * \return	a reference to the event manager.
		 */

		virtual SK::EventManager& getEventManager() =0 ;

		/**
		 * \fn	DataHandle<T> registerDataHandle(const SK::String& dataPath, bool autoUpdate = true)
		 *
		 * \brief	Registers a data handle.
		 *
		 * \param	dataPath  	The iisu path of the data.
		 * \param	autoUpdate	(optional) sets if the data should automatically be updated at each frame.
		 *
		 * \return	a DataHandle allowing to query the data
		 */

		template<typename T>
		DataHandle<T> registerDataHandle(const SK::String& dataPath, bool autoUpdate = true)
		{
			DataHandle<T> myData(*this, dataPath.ptr(), autoUpdate);
			return myData;
		}

		/**
		 * \fn	ParameterHandle<T> registerParameterHandle(const SK::String& paramPath)
		 *
		 * \brief	Registers the parameter handle described by paramPath.
		 *
		 * \param	paramPath	The iisu path of the parameter
		 *
		 * \return	a ParameterHandle allowing to interact with the parameter
		 */

		template<typename T>
		ParameterHandle<T>  registerParameterHandle(const SK::String& paramPath)
		{
			ParameterHandle<T> myParameter(*this, paramPath.ptr());
			return myParameter;
		}

	   /**
		 * \fn	void unregisterDataHandle(const DataHandle<T>& handle)
		 *
		 * \brief	Unregisters a data handle.
		 *
		 * \param	handle  	a DataHandle
		 *
		 */

		template<typename T>
		void unregisterDataHandle(DataHandle<T>& handle)
		{
			handle.unregister();
		}

	   /**
		 * \fn	void unregisterParameterHandle(const ParameterHandle<T>& handle)
		 *
		 * \brief	Unregisters a parameter handle.
		 *
		 * \param	handle  	a ParameterHandle
		 *
		 */

		template<typename T>
		void unregisterParameterHandle(ParameterHandle<T>& handle)
		{
			handle.unregister();
		}

		

		/**
		 * \fn	SK::Return< SK::MetaInfo<T> > getMetaInfo(const SK::String& dataPath)
		 *
		 * \brief	Gets the meta information associated to a given path (data/parameter).
		 *
		 * \param	dataPath	The iisu path of the parameter/data.
		 *
		 * \return	The meta information associated with the given path, if successful.
		 */

		template<typename T>
		SK::Return< SK::MetaInfo<T> > getMetaInfo(const SK::String& dataPath)
		{
			SK::Return<SK::RawData> res = getMetaInfoImpl(dataPath, SK::Type< SK::MetaInfo<T> >::INFO);
			RETURN_IF_FAILED(res) ;
			SK::RawData rd = res.get();
			SK::Return< SK::MetaInfo<T> > ret = rd.getRef< SK::MetaInfo<T> >();
			return ret;
		}

		/**
		 * \fn	virtual SK::Return<SK::Attributes> getAttributes(const SK::String& dataPath)const=0;
		 *
		 * \brief	Gets the attributes of the parameter/data associated to the given iisu path
		 *
		 * \param	dataPath	The iisu path of the parameter/data.
		 *
		 * \return	The attributes associated with the parameter/data, if successful.
		 */

		virtual SK::Return<SK::Attributes> getAttributes(const SK::String& dataPath)const=0;


		/**
		 * \fn	virtual SK::Return< SK::TypeInfo > getDataType(const SK::String &path) const = 0;
		 *
		 * \brief	Gets the type of the data associated to the given iisu path
		 *
		 * \param	path	The iisu path of the data.
		 *
		 * \return	The data type, if successful.
		 */

		virtual SK::Return< SK::TypeInfo > getDataType(const SK::String &path) const = 0;
  		

		/**
		 * \fn	virtual SK::Return<SK::TypeInfo> getParameterType(const SK::String &path) const = 0;
		 *
		 * \brief	Gets the type of the parameter associated to the given iisu path
		 *
		 * \param	path	The iisu path of the parameter.
		 *
		 * \return	The parameter type, if successful
		 */

		virtual SK::Return<SK::TypeInfo> getParameterType(const SK::String &path) const = 0;
		
	protected:
		virtual SK::Result setDataAutoUpdateFlag(int32_t dataID, bool autoUpdate) = 0;
		virtual SK::Return<bool> isDataAutoUpdated(int32_t dataID) const= 0;

		template<typename T>
		SK::Return<T> getParameter(int32_t paramID)
		{
			SK::Return<SK::RawData> res = getParameterImpl(paramID, SK::Type<T>::INFO);
			RETURN_IF_FAILED(res) ;
			SK::RawData rd = res.get();
			rd.acquire() ;
			T ret = rd.getCopy<T>();//SK::RawDataConverter<T>(rd).convert();
			//rd.destroyContent(); 
			return ret;
		}

		template<typename T>
		SK::Result setParameter(int32_t paramID,const T &value) {
			SK::RawData rd(value) ;
			return setParameterImpl(paramID,rd) ;
		} ;


		virtual SK::Return<int32_t> registerData(const SK::String &dataPath, const SK::TypeInfo& typeInfo, bool autoUpdate = true) = 0;

		virtual SK::Result unregisterData(int32_t dataID) = 0;
		virtual SK::Result unregisterParameter(int32_t parameterID) = 0;


		virtual  SK::Return<int32_t> registerParameter(const SK::String &path, const SK::TypeInfo& typeInfo)  = 0;

		virtual ~Device(){};

		virtual SK::Return<SK::RawData> getMetaInfoImpl(const SK::String& dataPath, const SK::TypeInfo& typeInfo)=0;

		virtual SK::Return<SK::RawData> getParameterImpl(int32_t paramID, const SK::TypeInfo& typeInfo) const=0 ;
		virtual SK::Result setParameterImpl(int32_t paramID,const SK::RawData &value) = 0 ;

		// Friend classes declaration

		template <typename T> friend class ParameterHandle;
		template <typename T> friend class DataHandle;
		friend SkError_C (::SkDevice_getMetaInfo)			(IN SkDevice_C device, IN SkString_C dataPath, OUT SkMetaInfo_C* metainfo);
		friend SkError_C (::SkDevice_setParameter)			(IN SkDevice_C device, IN int32_t paramID, IN const void* dataSent, IN SkTypeInfo_C type);
		friend SkError_C (::SkDevice_getParameter)			(IN SkDevice_C device, IN int32_t paramID, IN SkTypeInfo_C type, OUT void* parameterReturned);
		friend SkError_C (::SkDevice_registerParameter)		(IN SkDevice_C device, IN SkString_C path, IN SkTypeInfo_C typeInfo, OUT int32_t* paramID);
		friend SkError_C (::SkDevice_unregisterParameter)	(IN SkDevice_C device, IN int paramID);
		friend SkError_C (::SkDevice_registerData)			(IN SkDevice_C device, IN SkString_C path, IN SkTypeInfo_C type, OUT int* dataID);
		friend SkError_C (::SkDevice_unregisterData)		(IN SkDevice_C device, IN int dataID);
		friend SkError_C (::SkDevice_setDataAutoUpdateFlag)	(IN SkDevice_C device, IN int32_t dataID, IN bool autoUpdate);
		friend SkError_C (::SkDevice_isDataAutoUpdated)		(IN SkDevice_C device, IN int32_t dataID, OUT SkBool* isAutoUpdated);
	};

}


#endif //#ifdef __cplusplus
