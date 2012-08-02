#pragma once

#include <Foundation/DataTypes/String/String.h>
#include <Framework/Errors/Return.h>
#include <Foundation/Services/Types/RawData.h>
#include <Iisu/API/IisuCTypes.h>
#include <SDK/CApi/iisuAPIHelpers.h>

namespace SK
{
	/**
	 * \class	MetaInfoBase
	 *
	 * \brief	Generic class for meta-information. 
	 */

	class MetaInfoBase 
	{
		friend SkError_C (::SkMetaInfo_getAttributeFromID)	( IN SkMetaInfo_C metainfo, IN uint32_t id, IN SkTypeInfo_C typeInfo, OUT void* returnValue );
		friend SkError_C (::SkMetaInfo_getAttribute)		( IN SkMetaInfo_C metainfo, IN SkString_C name, IN SkTypeInfo_C typeInfo, OUT void* returnValue );

	public:

		/**
		 * \fn	explicit MetaInfoBase::MetaInfoBase(const SK::String& description = "")
		 *
		 * \brief	Constructor.
		 *
		 * \param	description	(optional) the description.
		 */

		explicit MetaInfoBase(const SK::String& description = ""): m_description(description){};
		virtual ~MetaInfoBase(){};

	public:

		/**
		 * \fn	const SK::String& MetaInfoBase::getDescription()const
		 *
		 * \brief	Gets the description.
		 *
		 * \return	The description.
		 */

		const SK::String& getDescription()const {return m_description;}

		/**
		 * \fn	void MetaInfoBase::setDescription(const SK::String& description)
		 *
		 * \brief	Sets a description.
		 *
		 * \param	description	The description.
		 */

		void setDescription(const SK::String& description) {m_description = description;}

		template <typename T>

		/**
		 * \fn	SK::Return<T> MetaInfoBase::getAttribute(const SK::String& name)const
		 *
		 * \brief	Gets an attribute.
		 *
		 * \param	name	The name.
		 *
		 * \return	The attribute.
		 */

		SK::Return<T> getAttribute(const SK::String& name)const
		{
			SK::Return<SK::RawData> res = getAttributeImpl(name, SK::Type<T>::INFO);
			if(res.failed()) return res.toResult();
			SK::RawData rd = res.get();
			SK::Return<T> ret = rd.getRef<T>();
			return ret;
		}
		template <typename T>

		/**
		 * \fn	SK::Result MetaInfoImpl::setAttribute(const SK::String& name, const T& value)
		 *
		 * \brief	Sets an attribute.
		 *
		 * \param	name 	The name.
		 * \param	value	The value.
		 *
		 * \return	.
		 */

		SK::Result setAttribute(const SK::String& name, const T& value)
		{
			return setAttributeImpl(name, &value, SK::Type<T>::INFO);
		}

		/**
		 * \fn	virtual uint32_t MetaInfoImpl::getNumberOfAttributes()const=0;
		 *
		 * \brief	Gets the number of attributes.
		 *
		 * \return	The number of attributes.
		 */

		virtual uint32_t getNumberOfAttributes()const=0;

		/**
		 * \fn	virtual SK::String MetaInfoImpl::getAttributeName(uint32_t id)const=0;
		 *
		 * \brief	Gets an attribute name.
		 *
		 * \param	id	The identifier.
		 *
		 * \return	The attribute name.
		 */

		virtual SK::String getAttributeName(uint32_t id)const=0;

		/**
		 * \fn	virtual SK::TypeInfo MetaInfoImpl::getAttributeType(uint32_t id)const=0;
		 *
		 * \brief	Gets an attribute type.
		 *
		 * \param	id	The identifier.
		 *
		 * \return	The attribute type.
		 */

		virtual SK::TypeInfo getAttributeType(uint32_t id)const=0;

		/**
		 * \fn	virtual SK::TypeInfo MetaInfoImpl::getAttributeType(const SK::String& name)const=0;
		 *
		 * \brief	Gets an attribute type.
		 *
		 * \param	name	The attribute name.
		 *
		 * \return	The attribute type.
		 */

		virtual SK::TypeInfo getAttributeType(const SK::String& name)const=0;

		/**
		 * \fn	virtual SK::Return<SK::RawData> MetaInfoImpl::getAttribute(uint32_t id)const=0;
		 *
		 * \brief	Templateless version for getting an attribute.
		 *
		 * \param	id	The identifier.
		 *
		 * \return	The attribute.
		 */

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const=0;

		/**
		 * \fn	virtual SK::Result MetaInfoImpl::setAttribute(uint32_t id, const SK::RawData& value)=0;
		 *
		 * \brief	Templateless version for setting an attribute.
		 *
		 * \param	id   	The identifier.
		 * \param	value	The value.
		 *
		 * \return	Result of the operation.
		 */

		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)=0;

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const=0;
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)=0;

	protected:
		SK::String m_description;
	};

}
