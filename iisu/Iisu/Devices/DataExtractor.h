
#ifndef DATA_EXTRACTOR_H
#define DATA_EXTRACTOR_H

#ifdef __cplusplus

#include <Foundation/DataTypes/String/String.h>
#include <Framework/Instances/SharedPtr.h>
#include <Iisu/Devices/Device.h>
#include <Framework/Errors/Error.h>

#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <Foundation/DataTypes/Geometry/Matrix3.h>
#include <Foundation/DataTypes/Geometry/Matrix4.h>
#include <Foundation/DataTypes/Color/Color.h>
#include <Foundation/DataTypes/String/String.h>
#include <Platform/CompileTimeUtils.h>
#include <Iisu/Devices/Device.h>
#include <Foundation/Services/Types/TypeInfo.h>
#include <Foundation/Services/Events/DeviceEvent.h>

namespace SK {

	/**
	 * \class	IIisuDataExtractor
	 *
	 * \brief	Common base interface for \sa ParameterHandle & \sa DataHandle 
	 */

	class IIisuDataExtractor
	{
	public:

		/**
		 * \fn	virtual IIisuDataExtractor::~IIisuDataExtractor()
		 *
		 * \brief	Destructor.
		 */

		virtual ~IIisuDataExtractor() {}
		//! ...

		/**
		 * \fn	virtual bool IIisuDataExtractor::isValid() const = 0;
		 *
		 * \brief	Query if this object is valid.
		 *
		 * \return	true if valid, false if not.
		 */

		virtual bool isValid() const = 0 ;
		//! ...

		/**
		 * \fn	virtual SK::String DataHandle::getErrorDescription() const = 0;
		 *
		 * \brief	Gets the error description (in case the object is invalid).
		 *
		 * \return	The error description.
		 */

		virtual SK::String getErrorDescription() const = 0 ;
		//! ...

		/**
		 * \fn	virtual SK::String DataHandle::getIisuPath() const = 0;
		 *
		 * \brief	Gets the path of the data.
		 *
		 * \return	The data path.
		 */

		virtual SK::String getIisuPath() const = 0;

		/**
		 * \fn	virtual SK::Return<SK::Attributes> DataHandle::getAttributes() const=0;
		 *
		 * \brief	Gets the object's attributes.
		 *
		 * \return	The attribute set of the object.
		 */

		virtual SK::Return<SK::Attributes> getAttributes() const=0;

		virtual void unregister()=0;

	};



	/**
	 * \class	DataHandle
	 *
	 * \brief	Data handle. It is used to connect to data computed by iisu at every frame and get their value
	 */

	template <typename T>
	class DataHandle : public IIisuDataExtractor
	{
	public:

		/**
		 * \fn	DataHandle::DataHandle()
		 *
		 * \brief	Default constructor.
		 */

		DataHandle():m_dataInfo(NULL)
		{
			// Forbid Non Iisu Data
			SK::Type<T>::IISU_DATA_TYPE;
		}

		/**
		 * \fn	DataHandle::DataHandle(SK::Device* m_device, const SK::String& m_path,
		 * 		bool autoUpdate = true)
		 *
		 * \brief	Constructor.
		 *
		 * \param 	m_device			The device we register this data on.
		 * \param	m_path				The iisu path of the data
		 * \param	autoUpdate			tells wheter the data has to be updated at every frame
		 */

		DataHandle(SK::Device& m_device, const SK::String& m_path, bool autoUpdate = true)
		{
			// Forbid Non Iisu Data
			SK::Type<T>::IISU_DATA_TYPE;
			m_dataInfo = SK::SharedPtr<DataInfo>(new DataInfo(m_device, m_path, autoUpdate));
		}

		/**
		 * \fn	const T& DataHandle::get()
		 *
		 * \brief	Gets a reference to the data stored in the handle.
		 *
		 * \return	a reference to the data
		 */

		const T& get()
		{
			
			if (hasData())
			{
				SK::Return<SK::DataFrame&> dataFrame = m_dataInfo->m_device->getDataFrame();
				if (dataFrame.succeeded())
				{
					SK::Return<SK::DataFrame::Handle> res = dataFrame.get().get(m_dataInfo->m_dataID, DataInfo::type::INFO);

					if (res.succeeded())
					{
						SK::DataFrame::Handle handle = res.get();
						return handle.data.getRef<T>();
					}
				}
			}

			// failsafe return value
			static T defaultTValue; // declared as static because we return a reference.
			return defaultTValue;
		}

		/**
		 * \fn	SK::Return< SK::MetaInfo<T> > DataHandle::getMetaInfo() const
		 *
		 * \brief	Gets the meta information available on the data referred to by the data handle.
		 *
		 * \return	The data's meta information, if successful.
		 */

		SK::Return< SK::MetaInfo<T> > getMetaInfo() const
		{
			if (m_dataInfo.get()) 
			{
				SK::Device* d = m_dataInfo->m_device;
				return d->getMetaInfo<T>(m_dataInfo->m_path);
			}
			return SK::Result("Invalid data handle",SK::INVALID_HANDLE);
		}

		/**
		 * \fn	SK::Return<SK::Attributes> DataHandle::getAttributes() const
		 *
		 * \brief	Gets the data's attributes.
		 *
		 * \return	The data's attributes, if successful.
		 */

		SK::Return<SK::Attributes> getAttributes() const
		{
			if (m_dataInfo.get()) 
			{
				SK::Device* d = m_dataInfo->m_device;
				return d->getAttributes(m_dataInfo->m_path);
			}
			return SK::Result("Invalid data handle",SK::INVALID_HANDLE);
		}

		/**
		 * \fn	bool DataHandle::isAutoUpdated()const
		 *
		 * \brief	Query if this object is automatically updated.
		 *
		 * \return	true if automatically updated at each frame.
		 */

		bool isAutoUpdated()const
		{
			if (m_dataInfo.get()) { 
				return m_dataInfo->isAutoUpdated();
			}
			return false ;
		}

		/**
		 * \fn	void DataHandle::setAutoUpdate(bool autoUpdate)
		 *
		 * \brief	Sets if the data associated to the handle has to be automatic updated at each frame.
		 *
		 * \param	autoUpdate	true to automatic update.
		 */

		void setAutoUpdate(bool autoUpdate)
		{
			if (m_dataInfo.get()) { 
				m_dataInfo->setAutoUpdate(autoUpdate);
			}
		}

		/**
		 * \fn	bool DataHandle::isValid() const
		 *
		 * \brief	Query if this object relates to data that is valid and available.
		 *
		 * \return	true if valid.
		 */

		bool isValid() const
		{
			if (!m_dataInfo.get()) return false ;

			m_dataInfo->validate();
			if(!m_dataInfo->isValid()) return false;
			SK::Return<SK::DataFrame&> dataFrame = m_dataInfo->m_device->getDataFrame();
			if (dataFrame.failed()) return false;

			SK::Return<bool> res = dataFrame.get().isValid(m_dataInfo->m_dataID);

			if (res.failed()) return false; 
			
			return res.get();
		}

		/**
		 * \fn	bool DataHandle::hasData() const
		 *
		 * \brief	Query if this object has data.
		 *
		 * \return	true if data, false if not.
		 */

		bool hasData() const
		{
			if (!isValid()) return false;
			SK::Return<SK::DataFrame&> dataFrame = m_dataInfo->m_device->getDataFrame();
			if (dataFrame.failed()) return false;

			SK::Return<SK::DataFrame::Handle> res = dataFrame.get().get(m_dataInfo->m_dataID, DataInfo::type::INFO);

			if (res.failed()) return false;
			if (!res.get().data.isValid()) return false;

			return true;
		}

		/**
		 * \fn	SK::String DataHandle::getErrorDescription() const
		 *
		 * \brief	Gets the error describing why the handle is invalid.
		 *
		 * \return	The error description.
		 */

		SK::String getErrorDescription() const
		{
			if (m_dataInfo.get()) { 
				return (m_dataInfo->getErrorDescription()) ;
			}
			return "No error description available" ;
		}

		/**
		 * \fn	SK::String DataHandle::getIisuPath() const
		 *
		 * \brief	Gets the iisu path of the datahandle
		 *
		 * \return	The iisu path
		 */

		SK::String getIisuPath() const { return m_dataInfo->m_path; }
		
		/**
		 * \fn	void unregister()
		 *
		 * \brief	unregister the data handle
		 *
		 * The data handle becomes invalid after this call, but any call to isValid or get will revalidate the handle (if possible).
		 */
		
		virtual void unregister()
		{
			m_dataInfo->unregister();
		}

	private:

		struct DataInfo 
		{
			const SK::String m_path;
			SK::Device* m_device;
			SK::Result m_status;
			int32_t m_dataID;
			bool m_autoUpdate;

			typedef SK::Type<T> type;
		public:

			DataInfo(SK::Device &pSkDevice, const SK::String& iisu_path, bool autoUpdate):
			m_path(iisu_path),
			m_device(&pSkDevice),
			m_status(Result::NoError),
			m_dataID(-1),
			m_autoUpdate(autoUpdate)
			{
				validate();
			}

			~DataInfo()
			{
				m_status.ignoreError();
//				unregister();
			}

			void unregister()
			{
				if(-1 != m_dataID) m_device->unregisterData(m_dataID).ignoreError();
				m_dataID = -1;
			}
		private:
			DataInfo(const DataInfo& other);
			DataInfo& operator=(const DataInfo& other);

		public:

 			bool isValid() {
 				return (m_status.succeeded()) ;
 			} ;

			void validate()
			{
				if(-1 != m_dataID) return;

				if (!m_device) 
				{
					m_status = SK::Result("Invalid device",SK::INVALID_DEVICE) ;
					return ;
				} 

				SK::Return<int32_t> retval =  m_device->registerData(m_path.ptr(), type::INFO, m_autoUpdate);
				m_status  = retval.toResult();
				if (retval.failed()) 
				{
					m_status = SK::Result(retval,ErrorMessage() << "Failed to register m_path " << m_path.ptr()) ;
				}
				else 
				{
					m_dataID = retval.get() ;
				} 
			}

			SK::String getErrorDescription() const
			{
				return m_status.getDescription() ;
			}

			bool isAutoUpdated()const
			{
				SK::Return<bool> res = m_device->isDataAutoUpdated(m_dataID);
				if(res.succeeded()) return res.get();
				return m_autoUpdate; 
			}

			void setAutoUpdate(bool autoUpdate)
			{
				m_device->setDataAutoUpdateFlag(m_dataID, autoUpdate).ignoreError();
				m_autoUpdate = autoUpdate;
			}
		};

		SK::SharedPtr<DataInfo> m_dataInfo;
	};



	template <typename T>

	/**
	 * \class	ParameterHandle
	 *
	 * \brief	Handle to a iisu Parameter. 
	 */

	class ParameterHandle : public IIisuDataExtractor
	{

	public:

		/**
		 * \fn	ParameterHandle::ParameterHandle()
		 *
		 * \brief	Default constructor.
		 */

		ParameterHandle()
			:m_parameterInfo(NULL)
		{
			// Forbid Non Iisu Data
			SK::Type<T>::IISU_DATA_TYPE;
		}

		/**
		 * \fn	ParameterHandle::ParameterHandle(SK::Device& m_device, const SK::String& m_path)
		 *
		 * \brief	Constructor.
		 *
		 * \param	m_device	The device we register the parameter on.
		 * \param	m_path		the iisu path of the parameter this parameter handle will be connected to.
		 */

		ParameterHandle(SK::Device& m_device, const SK::String& m_path)
		{
			// Forbid Non Iisu Data
			SK::Type<T>::IISU_DATA_TYPE;
			m_parameterInfo = SK::SharedPtr<ParameterInfo>(new ParameterInfo(m_device,m_path));
		}

		/**
		 * \fn	SK::Return< SK::MetaInfo<T> > ParameterHandle::getMetaInfo() const
		 *
		 * \brief	Gets the meta informations about the parameter mapped to the handle.
		 *
		 * \return	If successful, the meta information.
		 */

		SK::Return< SK::MetaInfo<T> > getMetaInfo() const
		{
			if (m_parameterInfo.get()) 
			{
				SK::Device* d = m_parameterInfo->m_device;
				return d->getMetaInfo<T>(m_parameterInfo->m_path);
			}
			return SK::Result("Invalid data handle",SK::INVALID_HANDLE);
		}

		/**
		 * \fn	SK::Return<SK::Attributes> ParameterHandle::getAttributes() const
		 *
		 * \brief	Gets the attributes of the data pointed to by the handle.
		 *
		 * \return	The attributes, if successful.
		 */

		SK::Return<SK::Attributes> getAttributes() const
		{
			if (m_parameterInfo.get()) 
			{
				SK::Device* d = m_parameterInfo->m_device;
				return d->getAttributes(m_parameterInfo->m_path);
			}
			return SK::Result("Invalid data handle",SK::INVALID_HANDLE);
		}

		/**
		 * \fn	T ParameterHandle::get()
		 *
		 * \brief	Gets the value of the parameter (assuming it is valid).
		 *
		 * \return	the value of the parameter
		 */

		T get()
		{
			if(isValid())
			{
				SK::Device *d = m_parameterInfo->m_device ;
				SK::Return<T> res = d->getParameter<T>(m_parameterInfo->m_parameterID);
				if(res.succeeded())
				{
					return res.get();
				}
			} 
			// failsafe return value
			static T defaultTValue; // declared as static because we return a reference.
			return defaultTValue;
		}

		/**
		 * \fn	SK::Result ParameterHandle::set(const T &parameter)
		 *
		 * \brief	Set the parameter value.
		 *
		 * \param	value the value to be taken by the associated parameter
		 *
		 * \return	.
		 */

		SK::Result set(const T &value)
		{
			if(!isValid())
			{
				return SK::Result(ErrorMessage() << "m_path not registered properly " << m_parameterInfo->m_path.ptr(),SK::INVALID_HANDLE ) ;;
			}
			return m_parameterInfo->m_device->setParameter(m_parameterInfo->m_parameterID,value);
		}

		/**
		 * \fn	bool ParameterHandle::isValid() const
		 *
		 * \brief	Query if the handle is valid.
		 *
		 * \return	true if valid, false if not.
		 */

		bool isValid() const
		{
			if (!m_parameterInfo.get()) return false ;

			m_parameterInfo->validate();
			if(!m_parameterInfo->isValid()) return false;
			SK::Device* d = m_parameterInfo->m_device;
			SK::Return<T> res = d->getParameter<T>(m_parameterInfo->m_parameterID);
			if(res.succeeded()) return true;

			return false ;
		}

		/**
		 * \fn	SK::String ParameterHandle::getErrorDescription() const
		 *
		 * \brief	Gets the error description, in the case the parameter is invalid
		 *
		 * \return	A string containing the error description.
		 */

		SK::String getErrorDescription() const
		{
			if (m_parameterInfo.get()) { 
				return (m_parameterInfo->getErrorDescription()) ;
			}
			return "No error description available" ;
		}

		/**
		 * \fn	bool ParameterHandle::isEditable() const
		 *
		 * \brief	Query if the parameter mapped by this handle is editable.
		 *
		 * \return	true if editable, false if not.
		 */

		bool isEditable() const
		{
			SK::Return<SK::Attributes> res = getAttributes();
			if(res.failed()) return false;
			return (res.get() == SK::Permission::READ_WRITE);
		}

		/**
		 * \fn	bool ParameterHandle::isSerializable() const
		 *
		 * \brief	Query if the parameter mapped by this handle is serializable.
		 *
		 * \return	true if serializable, false if not.
		 */

		bool isSerializable() const 
		{
			SK::Return<SK::Attributes> res = getAttributes();
			if(res.failed()) return false;
			return (res.get() == SK::Lifecycle::SERIALIZABLE);
		} 

		/**
		 * \fn	SK::String ParameterHandle::getIisuPath() const
		 *
		 * \brief	Gets the iisu path of the parameter mapped by the handle.
		 *
		 * \return	The iisu path.
		 */

		SK::String getIisuPath() const { return m_parameterInfo->m_path; }

		/**
		 * \fn	void unregister()
		 *
		 * \brief	unregister the parameter handle
		 *
		 * The parameter handle becomes invalid after this call, but any call to isValid or get will revalidate the handle (if possible).
		 */

		virtual void unregister()
		{
			m_parameterInfo->unregister();
		}

	private:

		//****************************************************

		struct ParameterInfo 
		{
			SK::Device* m_device;
			int32_t m_parameterID;
			SK::String m_path;
			SK::Result m_status;

			typedef SK::Type<T> type;
		public:

			ParameterInfo(SK::Device& device, const SK::String& parameterPath): 
			  m_device(&device), 
				  m_parameterID(-1), 
				  m_path(parameterPath),
				  m_status(SK::Result::NoError)
			  {
				  validate();
			  }

			  ~ParameterInfo()
			  {
				  m_status.ignoreError() ;
//				  unregister();
			  }

			  void unregister()
			  {
				  if(-1 != m_parameterID) m_device->unregisterParameter(m_parameterID).ignoreError();
				  m_parameterID = -1;
			  }

		private:
			ParameterInfo(const ParameterInfo& other);
			ParameterInfo& operator=(const ParameterInfo& other);

		public:
			bool isValid() 
			{
				return m_status.succeeded() ;
			} ;
			void validate()
			{
				if(-1 != m_parameterID) return;

				if (!m_device) {
					m_status = SK::Result("Invalid device",SK::INVALID_DEVICE) ;
					return ;
				} 

				SK::Return<int32_t> result = m_device->registerParameter(m_path.ptr(), type::INFO);
				m_status = result.toResult();
				if (result.failed()) 
				{
					m_parameterID=-1 ;
					m_status = SK::Result(result,ErrorMessage() << "Failed to register m_path " << m_path) ;
				} 
				else 
				{
					m_parameterID = result.get() ;
				}
			}

			SK::String getErrorDescription() const
			{
				return (m_status.getDescription()) ;
			}
		};
		SK::SharedPtr<ParameterInfo> m_parameterInfo;
	};

}
#endif

#endif // DATA_EXTRACTOR_H

