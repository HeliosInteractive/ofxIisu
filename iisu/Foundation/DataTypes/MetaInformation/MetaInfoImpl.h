#pragma once

#include <Platform/SkPlatform.h>
#include <limits>
#include "MetaInfo.h"
#include <Foundation/DataTypes/Enumeration/Enum.h>
#include <Framework/Types/MetaInfoTrait.h>
#include <Foundation/DataTypes/Array/Array.h>
#include <Foundation/DataTypes/Image/Image.h>
#include <System/Math/NumericCast.h>

namespace SK {

	template <typename DataType_T, uint32_t MetaInfoClass_T>
	class MetaInfoImpl : public MetaInfoBase
	{
	public:
		static const bool supportDefaultValue = false;

	public:
		explicit MetaInfoImpl(const SK::String& description = ""):
		MetaInfoBase(description) 
		{
		}

	public:
		friend bool operator==(const SK::MetaInfoImpl<DataType_T, MetaInfoClass_T>& lhs, const SK::MetaInfoImpl<DataType_T, MetaInfoClass_T>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription());
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 0;}
		virtual SK::String getAttributeName(uint32_t /*id*/)const {assert(false); return "";}
		virtual SK::TypeInfo getAttributeType(uint32_t /*id*/)const {assert(false); return SK::Type<SK::UnknownType>::INFO;}
		virtual SK::TypeInfo getAttributeType(const SK::String& /*name*/)const {return SK::Type<SK::UnknownType>::INFO;}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t /*id*/)const
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttribute(uint32_t /*id*/, const SK::RawData& /*value*/)
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
	protected:

		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& /*name*/, const SK::TypeInfo& /*typeInfo*/)const 
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& /*name*/, const void* /*value*/, const SK::TypeInfo& /*typeInfo*/)
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
	};

	/**
	 * \anchor MetaInfoNative
	 * \brief	Common implementation for type that support default value. 
	 */
	template <typename DataType_T>
	class MetaInfoImpl<DataType_T, MetaInfoClass::NATIVE_DEFAULT_VALUE> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo support default value
		static const bool supportDefaultValue = true;

	public:
		explicit MetaInfoImpl(const DataType_T& defaultvalue, const SK::String& description = ""):
		MetaInfoBase(description), m_defaultvalue(defaultvalue), m_defaultIsValid(true)
		{
		}

		explicit MetaInfoImpl(const SK::String& description = ""):
		MetaInfoBase(description), m_defaultIsValid(false)
		{
		}

	public:

		/**
		 * \fn	friend bool MetaInfoImpl::operator==(const SK::MetaInfoImpl<DataType_T, MetaInfoClass::NATIVE_DEFAULT_VALUE>& lhs,
		 * 		const SK::MetaInfoImpl<DataType_T, MetaInfoClass::NATIVE_DEFAULT_VALUE>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the two MetaInfo share the same description.
		 */

		friend bool operator==(const SK::MetaInfoImpl<DataType_T, MetaInfoClass::NATIVE_DEFAULT_VALUE>& lhs, const SK::MetaInfoImpl<DataType_T, MetaInfoClass::NATIVE_DEFAULT_VALUE>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription());
		}

		/**
		 * \fn	virtual const DataType_T& MetaInfoImpl::getDefaultValue() const
		 *
		 * \brief	Gets the default value.
		 *
		 * \return	The default value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual const DataType_T& getDefaultValue() const { return m_defaultvalue; }

		/**
		 * \fn	virtual void MetaInfoImpl::setDefaultValue(const DataType_T& val)
		 *
		 * \brief	Sets a default value.
		 *
		 * \param	val	The value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual void setDefaultValue(const DataType_T& val)
		{ 
			m_defaultIsValid = true;
			m_defaultvalue = val; 
		}

		/**
		 * \fn	virtual bool MetaInfoImpl::hasDefaultValue()const
		 *
		 * \brief	Query if this object has default value.
		 *
		 * \return	true if default value, false if not.
		 * 			
		 * 			An MetaInfo of this type supports default value but does not necessarily have a default value.<br>
		 * 			corresponding attribute: "HAS_DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual bool hasDefaultValue()const { return m_defaultIsValid; }

	public:
		virtual uint32_t getNumberOfAttributes()const {return 2;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "DEFAULT_VALUE";
			case 1: return "HAS_DEFAULT_VALUE";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<DataType_T>::INFO;
			case 1: return SK::Type<bool>::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "DEFAULT_VALUE") return SK::Type<DataType_T>::INFO;
			if(name == "HAS_DEFAULT_VALUE") return SK::Type<bool>::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_defaultvalue);
			case 1: return SK::RawData(m_defaultIsValid);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = value.getRef<DataType_T>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<bool>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = value.getRef<bool>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:

		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultIsValid);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = *static_cast<const DataType_T*>(value);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = *static_cast<const bool*>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}


	private:
		DataType_T m_defaultvalue;
		bool m_defaultIsValid;
	};

	template <typename DataType_T>

	/**
	 * \brief	MetaInfo for function type. \anchor MetaInfoFunc
	 */

	class MetaInfoImpl<DataType_T, MetaInfoClass::FUNCTION> : public MetaInfoBase
	{
	public:
		///< Function type MetaInfo do not support default value.
		static const bool supportDefaultValue = false;

	public:
		explicit MetaInfoImpl(const SK::String& description = ""):
		MetaInfoBase(description)
		{
		}
	};


	/**
	 * \anchor MetaInfoNativeArray
	 * \brief	Common implementation for type that support array of default value
	 */
	template <typename DataType_T>
	class MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::NATIVE_DEFAULT_VALUE> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo support default value
		static const bool supportDefaultValue = true;

	public:
		explicit MetaInfoImpl(const DataType_T& defaultvalue, const SK::String& description = ""):
		MetaInfoBase(description), m_defaultvalue(defaultvalue), m_defaultIsValid(true)
		{
		}

		explicit MetaInfoImpl(const SK::String& description = ""):
		MetaInfoBase(description), m_defaultIsValid(false)
		{
		}

	public:
		/**
		 * \fn	friend bool operator==(const SK::MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::NATIVE_DEFAULT_VALUE>& lhs,
		 * 		 const SK::MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::NATIVE_DEFAULT_VALUE>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the two MetaInfo share the same description.
		 */

		friend bool operator==(const SK::MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::NATIVE_DEFAULT_VALUE>& lhs, const SK::MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::NATIVE_DEFAULT_VALUE>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription());
		}

		/**
		 * \fn	virtual const DataType_T& MetaInfoImpl::getDefaultValue() const
		 *
		 * \brief	Gets the default value.
		 *
		 * \return	The default value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 * 			
		 * 	\warning A default value for a Array<X> is of type X which is the value to assign all element of the array.
		 */

		virtual const DataType_T& getDefaultValue() const { return m_defaultvalue; }

		/**
		 * \fn	virtual void MetaInfoImpl::setDefaultValue(const DataType_T& val)
		 *
		 * \brief	Sets a default value.
		 *
		 * \param	val	The value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 * 			
		 * 	\warning A default value for a Array<X> is of type X which is the value to assign all element of the array.
		 */

		virtual void setDefaultValue(const DataType_T& val)
		{ 
			m_defaultIsValid = true;
			m_defaultvalue = val; 
		}

		/**
		 * \fn	virtual bool MetaInfoImpl::hasDefaultValue()const
		 *
		 * \brief	Query if this object has default value.
		 *
		 * \return	true if default value, false if not.
		 * 			
		 * 	corresponding attribute: "HAS_DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual bool hasDefaultValue()const { return m_defaultIsValid; }

	public:
		virtual uint32_t getNumberOfAttributes()const {return 2;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "DEFAULT_VALUE";
			case 1: return "HAS_DEFAULT_VALUE";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<DataType_T>::INFO;
			case 1: return SK::Type<bool>::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "DEFAULT_VALUE") return SK::Type<DataType_T>::INFO;
			if(name == "HAS_DEFAULT_VALUE") return SK::Type<bool>::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_defaultvalue);
			case 1: return SK::RawData(m_defaultIsValid);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = value.getRef<DataType_T>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<bool>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = value.getRef<bool>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = *static_cast<const DataType_T*>(value);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = *static_cast<const bool*>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		DataType_T m_defaultvalue;
		bool m_defaultIsValid;
	};



	/**
	 * \anchor MetaInfoRange
	 * \brief	Common implementation for type that have a range (i.e: integers, float, ...)
	 */
	template <typename DataType_T>
	class MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo support default value
		static const bool supportDefaultValue = true;

	public :
		explicit MetaInfoImpl(const DataType_T& defaultvalue, 
			const SK::String& description = "",  
			const DataType_T& min = numeric_info<DataType_T>::min(),  
			const DataType_T& max = numeric_info<DataType_T>::max()):
		MetaInfoBase(description), m_defaultvalue(defaultvalue), m_defaultIsValid(true), m_min(min), m_max(max)
		{
		}

		explicit MetaInfoImpl(const SK::String& description = "",  
			const DataType_T& min = numeric_info<DataType_T>::min(),  
			const DataType_T& max = numeric_info<DataType_T>::max()):
		MetaInfoBase(description), m_defaultIsValid(false), m_min(min), m_max(max)
		{
		}

	public:

		/**
		 * \fn	friend bool MetaInfoImpl::operator==(const SK::MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>& lhs,
		 * 		const SK::MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the two MetaInfo share the same description and the same range (min,max).
		 */

		friend bool operator==(const SK::MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>& lhs, const SK::MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription() && lhs.getMin() == rhs.getMin() && lhs.getMax() == rhs.getMax());
		}

		/**
		 * \fn	virtual const DataType_T& MetaInfoImpl::getDefaultValue() const
		 *
		 * \brief	Gets the default value.
		 *
		 * \return	The default value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual const DataType_T& getDefaultValue() const { return m_defaultvalue; }

		/**
		 * \fn	virtual void MetaInfoImpl::setDefaultValue(const DataType_T& val)
		 *
		 * \brief	Sets a default value.
		 *
		 * \param	val	The value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual void setDefaultValue(const DataType_T& val)
		{ 
			m_defaultIsValid = true;
			m_defaultvalue = val; 
		}

		/**
		 * \fn	virtual bool MetaInfoImpl::hasDefaultValue()const
		 *
		 * \brief	Query if this object has default value.
		 *
		 * \return	true if default value, false if not.
		 * 			
		 * 	corresponding attribute: "HAS_DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual bool hasDefaultValue()const { return m_defaultIsValid; }

		/**
		 * \fn	const DataType_T& MetaInfoImpl::getMin()const
		 *
		 * \brief	Gets the minimum.
		 *
		 * \return	The lower bound of the range.
		 * 			
		 * 	corresponding attribute: "RANGE_MIN" (see \MetaInfoBase)
		 */

		const DataType_T& getMin()const {return m_min;}

		/**
		 * \fn	const DataType_T& MetaInfoImpl::getMax()const
		 *
		 * \brief	Gets the maximum.
		 *
		 * \return	The upper bound of the range.
		 * 			
		 * 	corresponding attribute: "RANGE_MAX" (see \MetaInfoBase)
		 */

		const DataType_T& getMax()const {return m_max;}

		/**
		 * \fn	void MetaInfoImpl::setMin(const DataType_T& min)
		 *
		 * \brief	Sets the lower bound of the range.
		 *
		 * \param	min	The minimum.
		 * 			
		 * 	corresponding attribute: "RANGE_MIN" (see \MetaInfoBase)
		 */

		void setMin(const DataType_T& min) {m_min = min;}

		/**
		 * \fn	void MetaInfoImpl::setMax(const DataType_T& max)
		 *
		 * \brief	Sets the upper bound of the range.
		 *
		 * \param	max	The maximum.
		 * 			
		 * 	corresponding attribute: "RANGE_MAX" (see \MetaInfoBase)
		 */

		void setMax(const DataType_T& max) {m_max = max;}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 4;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "DEFAULT_VALUE";
			case 1: return "HAS_DEFAULT_VALUE";
			case 2: return "RANGE_MIN";
			case 3: return "RANGE_MAX";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<DataType_T>::INFO;
			case 1: return SK::Type<bool>::INFO;
			case 2: return SK::Type<DataType_T>::INFO;
			case 3: return SK::Type<DataType_T>::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "DEFAULT_VALUE") return SK::Type<DataType_T>::INFO;
			if(name == "HAS_DEFAULT_VALUE") return SK::Type<bool>::INFO;
			if(name == "RANGE_MIN") return SK::Type<DataType_T>::INFO;
			if(name == "RANGE_MAX") return SK::Type<DataType_T>::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_defaultvalue);
			case 1: return SK::RawData(m_defaultIsValid);
			case 2: return SK::RawData(m_min);
			case 3: return SK::RawData(m_max);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = value.getRef<DataType_T>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<bool>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = value.getRef<bool>();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_min = value.getRef<DataType_T>();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_max= value.getRef<DataType_T>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "RANGE_MIN") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_min);
			}
			if(name == "RANGE_MAX") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_max);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = *static_cast<const DataType_T*>(value);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = *static_cast<const bool*>(value);
			}
			if(name == "RANGE_MIN") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_min = *static_cast<const DataType_T*>(value);
			}
			if(name == "RANGE_MAX") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_max = *static_cast<const DataType_T*>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		DataType_T m_defaultvalue;
		bool m_defaultIsValid;
		DataType_T m_min;
		DataType_T m_max;

	};



	/**
	 * \anchor MetaInfoRangeArray
	 * \brief	Common implementation for array of type that have a range (i.e: integers, float, ...)
	 */
	template <typename DataType_T>
	class MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo support default value
		static const bool supportDefaultValue = true;

	public :
		explicit MetaInfoImpl(const DataType_T& defaultvalue, 
			const SK::String& description = "",  
			const DataType_T& min = numeric_info<DataType_T>::min(),  
			const DataType_T& max = numeric_info<DataType_T>::max()):
		MetaInfoBase(description), m_defaultvalue(defaultvalue), m_defaultIsValid(true), m_min(min), m_max(max)
		{
		}

		explicit MetaInfoImpl(const SK::String& description = "",  
			typename SK::RefTypeTrait<DataType_T>::add_const_ref_t min = numeric_info<DataType_T>::min(),  
			typename SK::RefTypeTrait<DataType_T>::add_const_ref_t max = numeric_info<DataType_T>::max()):
		MetaInfoBase(description), m_defaultIsValid(false), m_min(min), m_max(max)
		{
		}

	public:

		/**
		 * \fn	friend bool RANGE_BASED>::operator==(const SK::MetaInfoImpl<SK::Array<DataType_T>,
		 * 		MetaInfoClass::RANGE_BASED>& lhs, const SK::MetaInfoImpl<SK::Array<DataType_T>,
		 * 		MetaInfoClass::RANGE_BASED>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	SK::MetaInfoImpl<SK::Array<DataType_T>	The sk meta information
		 * 													impl< sk array< data type t>
		 * \param [in,out]	lhs							  	The left hand side.
		 * \param	SK::MetaInfoImpl<SK::Array<DataType_T>	The sk meta information
		 * 													impl< sk array< data type t>
		 * \param [in,out]	rhs							  	The right hand side.
		 *
		 * \return	true if the two MetaInfo share the same description and the same range (min,max).
		 */

		friend bool operator==(const SK::MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>& lhs, const SK::MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription() && lhs.getMin() == rhs.getMin() && lhs.getMax() == rhs.getMax());
		}

		/**
		 * \fn	virtual typename SK::RefTypeTrait<DataType_T>::add_const_ref_t RANGE_BASED>::getDefaultValue() const
		 *
		 * \brief	Gets the default value.
		 *
		 * \return	The default value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 * 			
		 * 	\warning A default value for a Array<X> is of type X which is the value to assign all element of the array.
		 */

		virtual typename SK::RefTypeTrait<DataType_T>::add_const_ref_t getDefaultValue() const { return m_defaultvalue; }

		/**
		 * \fn	virtual void MetaInfoImpl::setDefaultValue(typename SK::RefTypeTrait<DataType_T>::add_const_ref_t val)
		 *
		 * \brief	Sets a default value.
		 *
		 * \param	val	The value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 * 			
		 * 	\warning A default value for a Array<X> is of type X which is the value to assign all element of the array.
		 */

		virtual void setDefaultValue(typename SK::RefTypeTrait<DataType_T>::add_const_ref_t val)
		{ 
			m_defaultIsValid = true;
			m_defaultvalue = val; 
		}

		/**
		 * \fn	virtual bool MetaInfoImpl::hasDefaultValue()const
		 *
		 * \brief	Query if this object has default value.
		 *
		 * \return	true if default value, false if not.
		 * 			
		 * 	corresponding attribute: "HAS_DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual bool hasDefaultValue()const { return m_defaultIsValid; }

		/**
		 * \fn	const DataType_T& MetaInfoImpl::getMin()const
		 *
		 * \brief	Gets the minimum.
		 *
		 * \return	The lower bound of the range.
		 * 			
		 * 	corresponding attribute: "RANGE_MIN" (see \MetaInfoBase)
		 */

		const DataType_T& getMin()const {return m_min;}

		/**
		 * \fn	const DataType_T& MetaInfoImpl::getMax()const
		 *
		 * \brief	Gets the maximum.
		 *
		 * \return	The Upper bound of the range.
		 * 			
		 * 	corresponding attribute: "RANGE_MAX" (see \MetaInfoBase)
		 */

		const DataType_T& getMax()const {return m_max;}

		/**
		 * \fn	void MetaInfoImpl::setMin(const DataType_T& min)
		 *
		 * \brief	Sets the lower bound of the range.
		 *
		 * \param	min	The minimum.
		 * 			
		 * 	corresponding attribute: "RANGE_MIN" (see \MetaInfoBase)
		 */

		void setMin(const DataType_T& min) {m_min = min;}

		/**
		 * \fn	void MetaInfoImpl::setMax(const DataType_T& max)
		 *
		 * \brief	Sets the upper bound of the range.
		 *
		 * \param	max	The maximum.
		 * 			
		 * 	corresponding attribute: "RANGE_MAX" (see \MetaInfoBase)
		 */

		void setMax(const DataType_T& max) {m_max = max;}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 4;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "DEFAULT_VALUE";
			case 1: return "HAS_DEFAULT_VALUE";
			case 2: return "RANGE_MIN";
			case 3: return "RANGE_MAX";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<DataType_T>::INFO;
			case 1: return SK::Type<bool>::INFO;
			case 2: return SK::Type<DataType_T>::INFO;
			case 3: return SK::Type<DataType_T>::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "DEFAULT_VALUE") return SK::Type<DataType_T>::INFO;
			if(name == "HAS_DEFAULT_VALUE") return SK::Type<bool>::INFO;
			if(name == "RANGE_MIN") return SK::Type<DataType_T>::INFO;
			if(name == "RANGE_MAX") return SK::Type<DataType_T>::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_defaultvalue);
			case 1: return SK::RawData(m_defaultIsValid);
			case 2: return SK::RawData(m_min);
			case 3: return SK::RawData(m_max);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = value.getRef<DataType_T>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<bool>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = value.getRef<bool>();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_min = value.getRef<DataType_T>();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type<DataType_T>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_max= value.getRef<DataType_T>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "RANGE_MIN") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_min);
			}
			if(name == "RANGE_MAX") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_max);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = *static_cast<const DataType_T*>(value);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = *static_cast<const bool*>(value);
			}
			if(name == "RANGE_MIN") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_min = *static_cast<const DataType_T*>(value);
			}
			if(name == "RANGE_MAX") 
			{
				if(SK::Type<DataType_T>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_max = *static_cast<const DataType_T*>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		DataType_T m_defaultvalue;
		bool m_defaultIsValid;
		DataType_T m_min;
		DataType_T m_max;
	};

	/**
	 * \struct	SourceImageType
	 *
	 * \brief	Indicate to which source the image size is related. 
	 */

	struct SourceImageType
	{
		enum Enum {
			///< The image has a size related to the depth image. 
			SIZE_FROM_DEPTH,
			///< The image has a size related to the color image. 
			SIZE_FROM_COLOR,
			///< The image has a size related to the confidence image. 
			SIZE_FROM_CONFIDENCE,
			///< The image has a custom size. 
			SIZE_CUSTOM
		};
	};

	/**
	 * \struct	PixelRelation
	 *
	 * \brief	Indicates if the image's pixel are related or not. 
	 */

	struct PixelRelation
	{
		enum Enum {
			///< The pixel a re related and represent a continuous space. 
			CONTINUOUS,
			///< Represent a label image. 
			UNRELATED
		};
	};

	/**
	 * \brief	Small class providing new size function getters. Usually contained in an Image meta-information
	 */

	struct ImageSizer
	{
		typedef uint32_t (*getSizeFunctionPtr_t)(uint32_t,uint32_t);
		enum Type
		{
			///< Internal use. 
			INTERNAL	= 0,
			///< Keep the size of the image as is. 
			INDENTITY	= 1,
			///< Give half the size of the image. 
			HALF		= 2,
			///< Give quarter the size of the image. 
			QUARTER		= 4,
		};

		getSizeFunctionPtr_t func;
		Type type;

		/**
		 * \brief	Internal size.
		 *
		 * \return	null size.
		 */

		static uint32_t internal(uint32_t /*width*/, uint32_t /*height*/) {return 0;}

		/**
		 * \brief	Identities.
		 *
		 * \param	width 	The width.
		 * \param	height	The height.
		 *
		 * \return	The same size as provided by width and height.
		 */

		static uint32_t identity(uint32_t width, uint32_t height) {return width*height;}

		/**
		 * \brief	Half size (area/4).
		 *
		 * \param	width 	The width.
		 * \param	height	The height.
		 *
		 * \return	width*height/4.
		 */

		static uint32_t half(uint32_t width, uint32_t height) {return (width/2)*(height/2);}

		/**
		 * \brief	Quarters (arrea/16).
		 *
		 * \param	width 	The width.
		 * \param	height	The height.
		 *
		 * \return	width*height/16.
		 */

		static uint32_t quarter(uint32_t width, uint32_t height) {return (width/4)*(height/4);}

		/**
		 * \brief	Constructor.
		 *
		 * \param	p_type	(optional) the type.
		 */

		ImageSizer(Type p_type = INTERNAL):
		type(p_type)
		{
			switch(type)
			{
			case INTERNAL: func = &internal; break;
			case INDENTITY: func = &identity; break;
			case HALF: func = &half; break;
			case QUARTER: func = &quarter; break;
			}
		}

	};


	/**
	 * \brief	Base implementation for Image MetaInfo
	 */
	template <uint32_t MetaInfoClass_T>
	class MetaInfoImpl<SK::Image, MetaInfoClass_T> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo does not support default value
		static const bool supportDefaultValue = false;

	public :
		explicit MetaInfoImpl(const SK::String& description="", PixelRelation::Enum relation=PixelRelation::CONTINUOUS, SourceImageType::Enum sourceSizeImageType=SourceImageType::SIZE_CUSTOM, ImageSizer imageSizer = ImageSizer()):
		MetaInfoBase(description),
			m_sourceSizeImageType(sourceSizeImageType),
			m_pixelRelations(relation),
			m_imageSizer(imageSizer){
		}
	public:

		friend bool operator==(const SK::MetaInfoImpl< SK::Image, MetaInfoClass_T >& lhs, const SK::MetaInfoImpl< SK::Image, MetaInfoClass_T >& rhs)
		{
			if (lhs.getDescription() != rhs.getDescription()) return false;
			if (lhs.m_sourceSizeImageType != rhs.m_sourceSizeImageType) return false;
			if (lhs.m_imageSizer.type != rhs.m_imageSizer.type) return false;

			return true;
		}

		/**
		 * \fn	void MetaInfoClass_T>::setImageSizer(const ImageSizer& imageSizer)
		 *
		 * \brief	Sets an ImageSizer.
		 *
		 * \param	imageSizer	The ImageSizer.
		 * 			
		 * 	corresponding attribute: "IMAGE_SIZER" (see \MetaInfoBase)
		 */

		void setImageSizer(const ImageSizer& imageSizer){m_imageSizer = imageSizer;}

		/**
		 * \fn	const ImageSizer& MetaInfoClass_T>::getImageSizer()const
		 *
		 * \brief	Gets the ImageSizer.
		 *
		 * \return	The ImageSizer.
		 * 			
		 * 	corresponding attribute: "IMAGE_SIZER" (see \MetaInfoBase)
		 */

		const ImageSizer& getImageSizer()const{return m_imageSizer;}

		/**
		 * \fn	void MetaInfoClass_T>::setSourceSizeImageType(SourceImageType::Enum sourceImageType)
		 *
		 * \brief	Sets a SourceImageType.
		 *
		 * \param	sourceImageType	Type SourceImageType.
		 * 			
		 * 	corresponding attribute: "SOURCE_SIZE_IMAGE_TYPE" (see \MetaInfoBase)
		 */

		void setSourceSizeImageType(SourceImageType::Enum sourceImageType){m_sourceSizeImageType = sourceImageType;}

		/**
		 * \fn	SourceImageType::Enum MetaInfoClass_T>::getSourceSizeImageType()const
		 *
		 * \brief	Gets the SourceImageType.
		 *
		 * \return	The SourceImageType.
		 * 			
		 * 	corresponding attribute: "SOURCE_SIZE_IMAGE_TYPE" (see \MetaInfoBase)
		 */

		SourceImageType::Enum getSourceSizeImageType()const{return m_sourceSizeImageType;}

		/**
		 * \fn	void MetaInfoClass_T>::setPixelRelation(PixelRelation::Enum pixelRelationEnum)
		 *
		 * \brief	Sets a PixelRelation.
		 *
		 * \param	pixelRelationEnum	The PixelRelation.
		 * 			
		 * 	corresponding attribute: "PIXEL_RELATION_ENUM" (see \MetaInfoBase)
		 */

		void setPixelRelation(PixelRelation::Enum pixelRelationEnum){m_pixelRelations = pixelRelationEnum;}

		/**
		 * \fn	PixelRelation::Enum MetaInfoClass_T>::getPixelRelation()const
		 *
		 * \brief	Gets the PixelRelation.
		 *
		 * \return	The PixelRelation.
		 * 			
		 * 	corresponding attribute: "PIXEL_RELATION_ENUM" (see \MetaInfoBase)
		 */

		PixelRelation::Enum getPixelRelation()const{return m_pixelRelations;}
		
	protected:
		SourceImageType::Enum m_sourceSizeImageType;
		PixelRelation::Enum m_pixelRelations;
		ImageSizer m_imageSizer;
	};




	/**
	 * \brief	Base implementation for the MetaInfo of Enum
	 */
	template <uint32_t MetaInfoClass_T>
	class MetaInfoImpl<SK::Enum, MetaInfoClass_T> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo support default value
		static const bool supportDefaultValue = true;


	public:
		explicit MetaInfoImpl(const SK::Enum& defaultvalue, const SK::String& description ="", const SK::EnumMapper& map = SK::EnumMapper()):MetaInfoBase(description), m_map(map), m_defaultvalue(defaultvalue), m_defaultIsValid(true){}
		explicit MetaInfoImpl(const SK::String& description = "", const SK::EnumMapper& map = SK::EnumMapper()):MetaInfoBase(description), m_map(map), m_defaultIsValid(false){}

		/**
		 * \fn	const SK::EnumMapper& MetaInfoClass_T>::getEnumMapper()const
		 *
		 * \brief	Gets the EnumMapper.
		 *
		 * \return	The EnumNapper.
		 * 			
		 * 	corresponding attribute: "ENUM_MAPPER" (see \MetaInfoBase)
		 */

		const SK::EnumMapper& getEnumMapper()const {return m_map;}

		/**
		 * \fn	void MetaInfoClass_T>::setEnumMapper(const SK::EnumMapper& map)
		 *
		 * \brief	Sets an EnumMapper.
		 *
		 * \param	map	The EnumMapper.
		 * 			
		 * 	corresponding attribute: "ENUM_MAPPER" (see \MetaInfoBase)
		 */

		void setEnumMapper(const SK::EnumMapper& map){m_map = map;}

		/**
		 * \fn	SK::Enum MetaInfoClass_T>::getDefaultValue() const
		 *
		 * \brief	Gets the default value.
		 *
		 * \return	The default value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		SK::Enum getDefaultValue() const { return m_defaultvalue; }

		/**
		 * \fn	void MetaInfoClass_T>::setDefaultValue(const SK::Enum& val)
		 *
		 * \brief	Sets a default value.
		 *
		 * \param	val	The value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		void setDefaultValue(const SK::Enum& val)
		{ 
			m_defaultIsValid = true;
			m_defaultvalue = val; 
		}

		/**
		 * \fn	virtual bool MetaInfoClass_T>::hasDefaultValue()const
		 *
		 * \brief	Query if this object has default value.
		 *
		 * \return	true if default value, false if not.
		 * 			
		 * 	corresponding attribute: "HAS_DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual bool hasDefaultValue()const { return m_defaultIsValid; }

	public:

		/**
		 * \fn	friend bool MetaInfoClass_T>::operator==(const SK::MetaInfoImpl<SK::Enum, MetaInfoClass_T>& lhs,
		 * 		const SK::MetaInfoImpl<SK::Enum, MetaInfoClass_T>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the two MetaInfo share the same description and the same EnumMapper
		 */

		friend bool operator==(const SK::MetaInfoImpl<SK::Enum, MetaInfoClass_T>& lhs, const SK::MetaInfoImpl<SK::Enum, MetaInfoClass_T>& rhs)
		{
			if(lhs.getDescription() != rhs.getDescription()) return false;
			if(lhs.getEnumMapper().numID() != rhs.getEnumMapper().numID()) return false;
			for(uint32_t i = 0, size = lhs.getEnumMapper().numID(); i < size; ++i)
			{
				const SK::EnumMapper::EnumValue& evLhs = lhs.getEnumMapper().getEnum(i);
				const SK::EnumMapper::EnumValue& evRhs = rhs.getEnumMapper().getEnum(i);
				if(evLhs.id != evRhs.id || evLhs.name != evRhs.name) return false;
			}
			return true;
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 3;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "DEFAULT_VALUE";
			case 1: return "HAS_DEFAULT_VALUE";
			case 2: return "ENUM_MAPPER";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<SK::Enum>::INFO;
			case 1: return SK::Type<bool>::INFO;
			case 2: return SK::Type<SK::EnumMapper>::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "DEFAULT_VALUE") return SK::Type<SK::Enum>::INFO;
			if(name == "HAS_DEFAULT_VALUE") return SK::Type<bool>::INFO;
			if(name == "ENUM_MAPPER") return SK::Type<SK::EnumMapper>::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_defaultvalue);
			case 1: return SK::RawData(m_defaultIsValid);
			case 2: return SK::RawData(m_map);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<SK::Enum>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = value.getRef<SK::Enum>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<bool>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = value.getRef<bool>();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type<SK::EnumMapper>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_map = value.getRef<SK::EnumMapper>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<SK::Enum>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type<SK::EnumMapper>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_map);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<SK::Enum>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = *static_cast<const SK::Enum*>(value);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = *static_cast<const bool*>(value);
			}
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type<SK::EnumMapper>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_map = *static_cast<const SK::EnumMapper*>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		SK::EnumMapper m_map;
		SK::Enum m_defaultvalue;
		bool m_defaultIsValid;

	};

	/**
	 * \brief	Base implementation for MetaInfo of String
	 */
	template <uint32_t MetaInfoClass_T>
	class MetaInfoImpl<SK::String, MetaInfoClass_T> : public MetaInfoBase
	{
	public:
		///< Indicates that this MetaInfo support default value
		static const bool supportDefaultValue = true;

	public:
		explicit MetaInfoImpl(const SK::String& defaultvalue, const SK::String& description):MetaInfoBase(description), m_defaultvalue(defaultvalue), m_defaultIsValid(true){}
		explicit MetaInfoImpl(const SK::String& description = ""):MetaInfoBase(description), m_defaultIsValid(false){}

		/**
		 * \fn	SK::String MetaInfoClass_T>::getDefaultValue() const
		 *
		 * \brief	Gets the default value.
		 *
		 * \return	The default value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		SK::String getDefaultValue() const { return m_defaultvalue; }

		/**
		 * \fn	void MetaInfoClass_T>::setDefaultValue(const SK::String& val)
		 *
		 * \brief	Sets a default value.
		 *
		 * \param	val	The value.
		 * 			
		 * 	corresponding attribute: "DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		void setDefaultValue(const SK::String& val)
		{ 
			m_defaultIsValid = true;
			m_defaultvalue = val; 
		}

		/**
		 * \fn	virtual bool MetaInfoClass_T>::hasDefaultValue()const
		 *
		 * \brief	Query if this object has default value.
		 *
		 * \return	true if default value, false if not.
		 * 			
		 * 	corresponding attribute: "HAS_DEFAULT_VALUE" (see \MetaInfoBase)
		 */

		virtual bool hasDefaultValue()const { return m_defaultIsValid; }

	public:
		friend bool operator==(const SK::MetaInfoImpl<SK::String, MetaInfoClass_T>& lhs, const SK::MetaInfoImpl<SK::String, MetaInfoClass_T>& rhs)
		{
			if(lhs.getDescription() != rhs.getDescription()) return false;
			return true;
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 2;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "DEFAULT_VALUE";
			case 1: return "HAS_DEFAULT_VALUE";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<SK::String>::INFO;
			case 1: return SK::Type<bool>::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "DEFAULT_VALUE") return SK::Type<SK::String>::INFO;
			if(name == "HAS_DEFAULT_VALUE") return SK::Type<bool>::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_defaultvalue);
			case 1: return SK::RawData(m_defaultIsValid);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<SK::String>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = value.getRef<SK::String>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<bool>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = value.getRef<bool>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<SK::String>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_defaultvalue);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "DEFAULT_VALUE") 
			{
				if(SK::Type<SK::String>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultvalue = *static_cast<const SK::String*>(value);
			}
			if(name == "HAS_DEFAULT_VALUE") 
			{
				if(SK::Type<bool>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_defaultIsValid = *static_cast<const bool*>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		SK::String m_defaultvalue;
		bool m_defaultIsValid;

	};



	/**
	 * \brief	MetaInfo class. 
	 * 			
	 * 			This class will have a specific implementation depending on the type. For instance all integer share the same implementation while bool have another implementation.
	 * 			See MetaInfoImpl for more details.
	 */
	template <typename DataType_T> 
	class MetaInfo : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<DataType_T>::DataType_T, MetaInfoClassExtractorTrait<DataType_T>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<DataType_T>::DataType_T, MetaInfoClassExtractorTrait<DataType_T>::DataTypeID> base_t ;
	public :
		explicit MetaInfo(const SK::String& description = ""):
		base_t(description)
		{
		}
	};

	/**
	 * \brief	MetaInfo for bool. See \ref MetaInfoNative "MetaInfoImpl<DataType_T, MetaInfoClass::NATIVE_DEFAULT_VALUE>" for interface.
	 */
	template <> 
	class MetaInfo<bool> : public MetaInfoImpl<bool, SK::MetaInfoClass::NATIVE_DEFAULT_VALUE>
	{
		typedef MetaInfoImpl<bool, SK::MetaInfoClass::NATIVE_DEFAULT_VALUE> base_t;
	public :
		explicit MetaInfo(bool defaultValue, const SK::String& description = ""):
		base_t(defaultValue, description)
		{
		}
		explicit MetaInfo(const SK::String& description = ""):
		base_t(description)
		{
		}
		explicit MetaInfo(const char* description):
		base_t(SK::String(description))
		{
		}
	};

	/**
	* \brief	MetaInfo for array of bool. See \ref MetaInfoNativeArray "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::NATIVE_DEFAULT_VALUE>" for interface.
	 */
	template <> 
	class MetaInfo< SK::Array<bool> > : public MetaInfoImpl<SK::Array<bool>, SK::MetaInfoClass::NATIVE_DEFAULT_VALUE>
	{
		typedef MetaInfoImpl<SK::Array<bool>, SK::MetaInfoClass::NATIVE_DEFAULT_VALUE> base_t;
	public :
		explicit MetaInfo(bool defaultValue, const SK::String& description = ""):
		base_t(defaultValue, description)
		{
		}
		explicit MetaInfo(const SK::String& description = ""):
		base_t(description)
		{
		}
		explicit MetaInfo(const char* description):
		base_t(SK::String(description))
		{
		}
	};


#define META_INFO_RANGED_BASED_SPEC(X)\
	template <> \
	class MetaInfo< X > : public MetaInfoImpl<X, SK::MetaInfoClass::RANGE_BASED>\
	{\
	typedef MetaInfoImpl<X, SK::MetaInfoClass::RANGE_BASED> base_t;\
	public:\
	explicit MetaInfo(const X& defaultvalue,  const SK::String& description = "",  const X& min = numeric_info<X>::min(), const X& max = numeric_info<X>::max()):\
	base_t(defaultvalue, description, min, max)\
	{\
	}\
	\
	explicit MetaInfo(const SK::String& description = "",  const X& min = numeric_info<X>::min(), const X& max = numeric_info<X>::max()):\
	base_t(description, min, max)\
	{\
	}\
	}

#define META_INFO_RANGED_BASED_ARRAY_SPEC(X)\
	template <> \
	class MetaInfo< SK::Array< X > > : public MetaInfoImpl<SK::Array< X >, SK::MetaInfoClass::RANGE_BASED>\
	{\
	typedef MetaInfoImpl<SK::Array< X >, SK::MetaInfoClass::RANGE_BASED> base_t;\
	public:\
	explicit MetaInfo(const X& defaultvalue,  const SK::String& description = "",  const X& min = numeric_info<X>::min(), const X& max = numeric_info<X>::max()):\
	base_t(defaultvalue, description, min, max)\
	{\
	}\
	\
	explicit MetaInfo(const SK::String& description = "",  const X& min = numeric_info<X>::min(), const X& max = numeric_info<X>::max()):\
	base_t(description, min, max)\
	{\
	}\
	}\

	/**
	 * \brief	MetaInfo for int8_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(int8_t);
	/**
	 * \brief	MetaInfo for int16_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(int16_t);
	/**
	 * \brief	MetaInfo for int32_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(int32_t);
	/**
	 * \brief	MetaInfo for int64_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(int64_t);
	/**
	 * \brief	MetaInfo for uint8_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(uint8_t);
	/**
	 * \brief	MetaInfo for uint16_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(uint16_t);
	/**
	 * \brief	MetaInfo for uint32_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(uint32_t);
	/**
	 * \brief	MetaInfo for uint64_t. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(uint64_t);

	/**
	 * \brief	MetaInfo for float. See \ref MetaInfoRange "MetaInfoImpl<DataType_T, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_SPEC(float);

	/**
	* \brief	MetaInfo for array of int8_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(int8_t);
	/**
	* \brief	MetaInfo for array of int16_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(int16_t);
	/**
	* \brief	MetaInfo for array of int32_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(int32_t);
	/**
	* \brief	MetaInfo for array of int64_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(int64_t);
	/**
	* \brief	MetaInfo for array of uint8_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(uint8_t);
	/**
	* \brief	MetaInfo for array of uint16_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(uint16_t);
	/**
	* \brief	MetaInfo for array of uint32_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(uint32_t);
	/**
	* \brief	MetaInfo for array of uint64_t. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(uint64_t);

	/**
	* \brief	MetaInfo for array of float. See \ref MetaInfoRange "MetaInfoImpl<SK::Array<DataType_T>, MetaInfoClass::RANGE_BASED>" for interface.
	 */
	META_INFO_RANGED_BASED_ARRAY_SPEC(float);

	/**
	* \brief	MetaInfo for Image. 
	 */
	template <>
	class MetaInfo< SK::Image > : public MetaInfoImpl<SK::Image, SK::MetaInfoClass::GENERIC>
	{
		typedef MetaInfoImpl<SK::Image, SK::MetaInfoClass::GENERIC> base_t;
	public:
		explicit MetaInfo(const SK::String& description="" , SK::MetaInfo<int32_t> range = SK::MetaInfo<int32_t>(), SK::PixelRelation::Enum relation=PixelRelation::CONTINUOUS, SK::SourceImageType::Enum sourceSizeImageType=SourceImageType::SIZE_CUSTOM, ImageSizer imageSizer = ImageSizer()):
		base_t(description, relation, sourceSizeImageType, imageSizer),
			m_range(range)
		{
		}

		/**
		 * \fn	SK::MetaInfo<int32_t> :::getRange()const
		 *
		 * \brief	Gets the range of the image.
		 *
		 * \return	The range of the pixel of the image as a MetaInfo<int32_t>.
		 * 			
		 * 	corresponding attribute: "RANGE_META_INFO" (see \MetaInfoBase)
		 */

		SK::MetaInfo<int32_t> getRange()const{return m_range;}

		/**
		 * \fn	void :::setRange(const SK::MetaInfo<int32_t>& range)
		 *
		 * \brief	Sets a range of the image.
		 *
		 * \param	range	The range as a MetaInfo<int32_t>.
		 * 			
		 * 	corresponding attribute: "RANGE_META_INFO" (see \MetaInfoBase)
		 */

		void setRange(const SK::MetaInfo<int32_t>& range){m_range = range;}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 4;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "IMAGE_SIZER";
			case 1: return "SOURCE_SIZE_IMAGE_TYPE";
			case 2: return "PIXEL_RELATION_ENUM";
			case 3: return "RANGE_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type<ImageSizer>::INFO;
			case 1: return SK::Type<SK::Enum>::INFO;
			case 2: return SK::Type<SK::Enum>::INFO;
			case 3: return SK::Type< SK::MetaInfo<int32_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "IMAGE_SIZER") return SK::Type<ImageSizer>::INFO;
			if(name == "SOURCE_SIZE_IMAGE_TYPE") return SK::Type<SK::Enum>::INFO;
			if(name == "PIXEL_RELATION_ENUM") return SK::Type<SK::Enum>::INFO;
			if(name == "RANGE_META_INFO") return SK::Type< SK::MetaInfo<int32_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_imageSizer);
			case 1: return SK::RawData( (uint32_t) m_sourceSizeImageType ); // to check
			case 2: return SK::RawData( (uint32_t) m_pixelRelations );		//tocheck
			case 3: return SK::RawData(m_range);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<SK::ImageSizer>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_imageSizer = value.getRef<SK::ImageSizer>();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type<SK::Enum>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_sourceSizeImageType = static_cast<const SK::SourceImageType::Enum>(value.getRef<SK::Enum>().value);
				return SK::Result::NoError;
			case 2: 
				if(SK::Type<SK::Enum>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_pixelRelations = static_cast<const SK::PixelRelation::Enum>(value.getRef<SK::Enum>().value);
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< SK::MetaInfo<int32_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_range= value.getRef< SK::MetaInfo<int32_t> >();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "IMAGE_SIZER") 
			{
				if(SK::Type<ImageSizer>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_imageSizer);
			}
			if(name == "SOURCE_SIZE_IMAGE_TYPE") 
			{
				if(SK::Type<SK::Enum>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(SK::Enum(m_sourceSizeImageType));
			}
			if(name == "PIXEL_RELATION_ENUM") 
			{
				if(SK::Type<SK::Enum>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(SK::Enum(m_pixelRelations));
			}
			if(name == "RANGE_META_INFO") 
			{
				if(SK::Type<  SK::MetaInfo<int32_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_range);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "IMAGE_SIZER") 
			{
				if(SK::Type<ImageSizer>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_imageSizer = *static_cast<const ImageSizer*>(value);
			}
			if(name == "SOURCE_SIZE_IMAGE_TYPE") 
			{
				if(SK::Type<SK::Enum>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_sourceSizeImageType = *reinterpret_cast<const SK::SourceImageType::Enum*>(value);
			}
			if(name == "PIXEL_RELATION_ENUM") 
			{
				if(SK::Type<SK::Enum>::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_pixelRelations = *reinterpret_cast<const SK::PixelRelation::Enum*>(value);
			}
			if(name == "RANGE_META_INFO") 
			{
				if(SK::Type<  SK::MetaInfo<int32_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_range = *static_cast< const SK::MetaInfo<int32_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}

	private:
		SK::MetaInfo<int32_t> m_range;
	};

	/**
	 * \brief	MetaInfo for Enum. 
	 */
	template <> 
	class MetaInfo<SK::Enum> : public MetaInfoImpl<SK::Enum, SK::MetaInfoClass::GENERIC>
	{
		typedef MetaInfoImpl<SK::Enum, SK::MetaInfoClass::GENERIC> base_t;
	public:
		explicit MetaInfo(const SK::Enum& defaultvalue, const SK::String& description ="", const SK::EnumMapper& map = SK::EnumMapper()):base_t(defaultvalue, description, map){}
		explicit MetaInfo(const SK::String& description = "", const SK::EnumMapper& map = SK::EnumMapper()):base_t(description, map){}
	};

	/**
	 * \brief	MetaInfo for String. 
	 */
	template <> 
	class MetaInfo<SK::String> : public MetaInfoImpl<SK::String, SK::MetaInfoClass::GENERIC>
	{
		typedef MetaInfoImpl<SK::String, SK::MetaInfoClass::GENERIC> base_t;
	public:
		explicit MetaInfo(const SK::String& defaultvalue, const SK::String& description):base_t(defaultvalue, description){}
		explicit MetaInfo(const SK::String& description = ""):base_t(description){}
	};

	//! \cond METAINFO_FUNC
	template <typename R> 
	class MetaInfo<R()> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R()>::DataType_T, MetaInfoClassExtractorTrait<R()>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R()>::DataType_T, MetaInfoClassExtractorTrait<R()>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R()>& lhs, const SK::MetaInfo<R()>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 1;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
	};

	template <typename R, typename P1> 
	class MetaInfo<R(P1)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1)>::DataType_T, MetaInfoClassExtractorTrait<R(P1)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1)>::DataType_T, MetaInfoClassExtractorTrait<R(P1)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1)>& lhs, const SK::MetaInfo<R(P1)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 2;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
	};

	template <typename R, typename P1, typename P2> 
	class MetaInfo<R(P1, P2)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}


	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2)>& lhs, const SK::MetaInfo<R(P1, P2)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 3;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
	};

	template <typename R, typename P1, typename P2, typename P3> 
	class MetaInfo<R(P1, P2, P3)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3)>& lhs, const SK::MetaInfo<R(P1, P2, P3)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 4;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4>
	class MetaInfo<R(P1, P2, P3, P4)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 5;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			case 4: return "P4_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			case 4: return SK::RawData(m_p4MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
	};


	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
	class MetaInfo<R(P1, P2, P3, P4, P5)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 6;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			case 4: return "P4_META_INFO";
			case 5: return "P5_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			case 4: return SK::RawData(m_p4MetaInfo);
			case 5: return SK::RawData(m_p5MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	);
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
	};

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class MetaInfo<R(P1, P2, P3, P4, P5, P6)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 7;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			case 4: return "P4_META_INFO";
			case 5: return "P5_META_INFO";
			case 6: return "P6_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}


		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			case 4: return SK::RawData(m_p4MetaInfo);
			case 5: return SK::RawData(m_p5MetaInfo);
			case 6: return SK::RawData(m_p6MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
	};


	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class MetaInfo<R(P1, P2, P3, P4, P5, P6, P7)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 8;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			case 4: return "P4_META_INFO";
			case 5: return "P5_META_INFO";
			case 6: return "P6_META_INFO";
			case 7: return "P7_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			case 4: return SK::RawData(m_p4MetaInfo);
			case 5: return SK::RawData(m_p5MetaInfo);
			case 6: return SK::RawData(m_p6MetaInfo);
			case 7: return SK::RawData(m_p7MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
	};


	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo = MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo),
			m_p8MetaInfo(p8MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& getP8MetaInfo()const {return m_p8MetaInfo;}
		void setP8MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo) {m_p8MetaInfo = p8MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	) &&
				(lhs.m_p8MetaInfo	 == rhs.m_p8MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 9;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			case 4: return "P4_META_INFO";
			case 5: return "P5_META_INFO";
			case 6: return "P6_META_INFO";
			case 7: return "P7_META_INFO";
			case 8: return "P8_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			case 8: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			if(name == "P8_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}


		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			case 4: return SK::RawData(m_p4MetaInfo);
			case 5: return SK::RawData(m_p5MetaInfo);
			case 6: return SK::RawData(m_p6MetaInfo);
			case 7: return SK::RawData(m_p7MetaInfo);
			case 8: return SK::RawData(m_p8MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 8: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p8MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}
	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> m_p8MetaInfo;
	};
	//! \endcond

   /**
	 * 
	 * \brief	MetaInfo class for function type (i.e: Commands) 
	 * 			
	 *	        
	 *
	 * \tparam	R 		Type of the return value.
	 * \tparam	P1	    Type of the first parameter.
	 * \tparam	P2  	Type of the second parameter.
	 * \tparam	P3  	Type of the third parameter.
	 * \tparam	P4  	Type of the fourth parameter.
	 * \tparam	P5  	Type of the fifth parameter.
	 * \tparam	P6  	Type of the sixth parameter.
	 * \tparam	P7  	Type of the seventh parameter.
	 * \tparam	P8  	Type of the eighth parameter.
	 * \tparam	P9  	Type of the ninth parameter.
	 *	  
	 *	 	   
	 *	 
	 *	 This class is a specialization with a return type and 9 arguments. The number of arguments can vary from zero to nine.<br/>
	 * 	Only this specialization with 9 parameters is documented, the other specializations aren't but their documentation is very similar to this one.			
	 * 	For function with a return type SK::Result see \ref MetaInfoVoidFunc "MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>" for more details.
	 * 	This class inherits from \ref MetaInfoFunc "MetaInfoImpl<DataType_T, MetaInfoClass::FUNCTION>"
	 */

	template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataType_T, MetaInfoClassExtractorTrait<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo = MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo = MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& p9MetaInfo = MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>()
			):
		base_t(description), 
			m_returnMetaInfo(returnMetaInfo), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo),
			m_p8MetaInfo(p8MetaInfo),
			m_p9MetaInfo(p9MetaInfo)
		{
		}

	public:

		/**
		 * \brief	Gets the return's MetaInfo.
		 *
		 * \return	The return's MetaInfo.
		 * 			
		 * 	corresponding attribute: "RETURN_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& getReturnMetaInfo()const {return m_returnMetaInfo;}
		void setReturnMetaInfo(const MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t>& returnMetaInfo) {m_returnMetaInfo = returnMetaInfo;}


		/**
		 * \brief	Gets the first parameter's MetaInfo.
		 *
		 * \return	The first parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P1_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}

		/**
		 * \brief	Sets the first parameter's MetaInfo.
		 *
		 * \param p1MetaInfo	The first parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P1_META_INFO" (see \MetaInfoBase)
		 */

		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		/**
		 * \brief	Gets the second parameter's MetaInfo.
		 *
		 * \return	The second parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P2_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}

		/**
		 * \brief	Sets the second parameter's MetaInfo.
		 *
		 * \param p2MetaInfo	The second parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P2_META_INFO" (see \MetaInfoBase)
		 */

		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		/**
		 * \brief	Gets the third parameter's MetaInfo.
		 *
		 * \return	The third parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P3_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}

		/**
		 * \brief	Sets the third parameter's MetaInfo.
		 *
		 * \param p3MetaInfo	The third parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P3_META_INFO" (see \MetaInfoBase)
		 */

		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		/**
		 * \brief	Gets the fourth parameter's MetaInfo.
		 *
		 * \return	The fourth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P4_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}

		/**
		 * \brief	Sets the fourth parameter's MetaInfo.
		 *
		 * \param p4MetaInfo	The fourth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P4_META_INFO" (see \MetaInfoBase)
		 */

		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		/**
		 * \brief	Gets the fifth parameter's MetaInfo.
		 *
		 * \return	The fifth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P5_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}

		/**
		 * \brief	Sets the fifth parameter's MetaInfo.
		 *
		 * \param p5MetaInfo	The fifth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P5_META_INFO" (see \MetaInfoBase)
		 */

		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		/**
		 * \brief	Gets the sixth parameter's MetaInfo.
		 *
		 * \return	The sixth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P6_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}

		/**
		 * \brief	Sets the sixth parameter's MetaInfo.
		 *
		 * \param p6MetaInfo	The sixth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P6_META_INFO" (see \MetaInfoBase)
		 */

		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		/**
		 * \brief	Gets the seventh parameter's MetaInfo.
		 *
		 * \return	The seventh parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P7_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}

		/**
		 * \brief	Sets the seventh parameter's MetaInfo.
		 *
		 * \param p7MetaInfo	The seventh parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P7_META_INFO" (see \MetaInfoBase)
		 */

		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

	
		/**
		 * \brief	Gets the eighth parameter's MetaInfo.
		 *
		 * \return	The eighth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P8_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& getP8MetaInfo()const {return m_p8MetaInfo;}

		/**
		 * \brief	Sets the eighth parameter's MetaInfo.
		 *
		 * \param p1MetaInfo	The eighth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P8_META_INFO" (see \MetaInfoBase)
		 */

		void setP8MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo) {m_p8MetaInfo = p8MetaInfo;}

		/**
		 * \brief	Gets the ninth parameter's MetaInfo.
		 *
		 * \return	The ninth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P9_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& getP9MetaInfo()const {return m_p9MetaInfo;}

		/**
		 * \brief	Sets the ninth parameter's MetaInfo.
		 *
		 * \param p9MetaInfo	The ninth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P9_META_INFO" (see \MetaInfoBase)
		 */

		void setP9MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& p9MetaInfo) {m_p9MetaInfo = p9MetaInfo;}

	public:
		/**
		 * \fn	friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the two MetaInfo share the same description and all the subsequent MetaInfo are equivalent.
		 */
		friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_returnMetaInfo == rhs.m_returnMetaInfo) &&
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	) &&
				(lhs.m_p8MetaInfo	 == rhs.m_p8MetaInfo	) &&
				(lhs.m_p9MetaInfo	 == rhs.m_p9MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 10;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "RETURN_META_INFO";
			case 1: return "P1_META_INFO";
			case 2: return "P2_META_INFO";
			case 3: return "P3_META_INFO";
			case 4: return "P4_META_INFO";
			case 5: return "P5_META_INFO";
			case 6: return "P6_META_INFO";
			case 7: return "P7_META_INFO";
			case 8: return "P8_META_INFO";
			case 9: return "P9_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			case 8: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			case 9: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "RETURN_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO;
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			if(name == "P8_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			if(name == "P9_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}


		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_returnMetaInfo);
			case 1: return SK::RawData(m_p1MetaInfo);
			case 2: return SK::RawData(m_p2MetaInfo);
			case 3: return SK::RawData(m_p3MetaInfo);
			case 4: return SK::RawData(m_p4MetaInfo);
			case 5: return SK::RawData(m_p5MetaInfo);
			case 6: return SK::RawData(m_p6MetaInfo);
			case 7: return SK::RawData(m_p7MetaInfo);
			case 8: return SK::RawData(m_p8MetaInfo);
			case 9: return SK::RawData(m_p9MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 8: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 9: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p9MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_returnMetaInfo);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p8MetaInfo);
			}
			if(name == "P9_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p9MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "RETURN_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_returnMetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> *>(value);
			}
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> *>(value);
			}
			if(name == "P9_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p9MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<R>::remove_const_ref_t> m_returnMetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> m_p8MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> m_p9MetaInfo;
	};


	//! \cond METAINFO_FUNC_VOID

	template <> 
	class MetaInfo<void()> : public MetaInfoImpl<MetaInfoClassExtractorTrait<void()>::DataType_T, MetaInfoClassExtractorTrait<void()>::DataTypeID>
	{
		typedef MetaInfoImpl<MetaInfoClassExtractorTrait<void()>::DataType_T, MetaInfoClassExtractorTrait<void()>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "" 
			):
		base_t(description)
		{
		}

	public:

	public:
		friend bool operator==(const SK::MetaInfo<void()>& lhs, const SK::MetaInfo<void()>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription());
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 0;}
		virtual SK::String getAttributeName(uint32_t /*id*/)const 
		{
			assert(false); return "";
		}
		virtual SK::TypeInfo getAttributeType(uint32_t /*id*/)const 
		{
			assert(false); return SK::Type<SK::UnknownType>::INFO;
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& /*name*/) const
		{
			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t /*id*/)const
		{
			assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttribute(uint32_t /*id*/, const SK::RawData& /*value*/)
		{
			assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& /*name*/, const SK::TypeInfo& /*typeInfo*/)const 
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& /*name*/, const void* /*value*/, const SK::TypeInfo& /*typeInfo*/)
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
	};

	template <typename P1> 
	class MetaInfo<void(P1)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1)>::DataType_T, MetaInfoClassExtractorTrait<void(P1)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1)>::DataType_T, MetaInfoClassExtractorTrait<void(P1)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1)>& lhs, const SK::MetaInfo<void(P1)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	);
		}


	public:
		virtual uint32_t getNumberOfAttributes()const {return 1;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}


	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
	};

	template <typename P1, typename P2> 
	class MetaInfo<void(P1, P2)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2)>& lhs, const SK::MetaInfo<void(P1, P2)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 2;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}


		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}
	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
	};

	template <typename P1, typename P2, typename P3> 
	class MetaInfo<void(P1, P2, P3)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3)>& lhs, const SK::MetaInfo<void(P1, P2, P3)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 3;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
	};

	template <typename P1, typename P2, typename P3, typename P4>
	class MetaInfo<void(P1, P2, P3, P4)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3, P4)>& lhs, const SK::MetaInfo<void(P1, P2, P3, P4)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 4;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";

			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
	};


	template <typename P1, typename P2, typename P3, typename P4, typename P5>
	class MetaInfo<void(P1, P2, P3, P4, P5)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3, P4, P5)>& lhs, const SK::MetaInfo<void(P1, P2, P3, P4, P5)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	);
		}


	public:
		virtual uint32_t getNumberOfAttributes()const {return 5;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";

			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
	};

	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class MetaInfo<void(P1, P2, P3, P4, P5, P6)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6)>& lhs, const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 6;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
	};


	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class MetaInfo<void(P1, P2, P3, P4, P5, P6, P7)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6, P7)>& lhs, const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6, P7)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 7;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			case 6: return "P7_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);
			case 6: return SK::RawData(m_p7MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
	};


	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo = MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo),
			m_p8MetaInfo(p8MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& getP8MetaInfo()const {return m_p8MetaInfo;}
		void setP8MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo) {m_p8MetaInfo = p8MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8)>& lhs, const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	) &&
				(lhs.m_p8MetaInfo	 == rhs.m_p8MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 8;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			case 6: return "P7_META_INFO";
			case 7: return "P8_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			if(name == "P8_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);
			case 6: return SK::RawData(m_p7MetaInfo);
			case 7: return SK::RawData(m_p8MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p8MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> m_p8MetaInfo;
	};
	//! \endcond

	   /**
	 * 
	 * \brief	MetaInfo class for function type with void return (i.e: Commands) \anchor MetaInfoVoidFunc
	 * 			
	 *	        
	 *
	 * \tparam	P1	    Type of the first parameter.
	 * \tparam	P2  	Type of the second parameter.
	 * \tparam	P3  	Type of the third parameter.
	 * \tparam	P4  	Type of the fourth parameter.
	 * \tparam	P5  	Type of the fifth parameter.
	 * \tparam	P6  	Type of the sixth parameter.
	 * \tparam	P7  	Type of the seventh parameter.
	 * \tparam	P8  	Type of the eighth parameter.
	 * \tparam	P9  	Type of the ninth parameter.
	 *	  
	 *	 	   
	 *	 
	 *	 This class is a specialization with void return type and 9 arguments. The number of arguments can vary from zero to nine.<br/>
	 * 	Only this specialization with 9 parameters is documented, the other specializations aren't but their documentation is very similar to this one.		
	 * 	Also note that function with a return type of SK::Result behave the same one so the documentation that is presented here apply to those classes as well.
	 * 	This class inherits from \ref MetaInfoFunc "MetaInfoImpl<DataType_T, MetaInfoClass::FUNCTION>"
	 */

	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataType_T, MetaInfoClassExtractorTrait<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo = MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& p9MetaInfo = MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo),
			m_p8MetaInfo(p8MetaInfo),
			m_p9MetaInfo(p9MetaInfo)
		{
		}

	public:
		/**
		 * \brief	Gets the return's MetaInfo.
		 *
		 * \return	The return's MetaInfo.
		 * 			
		 * 	corresponding attribute: "RETURN_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}

		/**
		 * \brief	Sets the first parameter's MetaInfo.
		 *
		 * \param p1MetaInfo	The first parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P1_META_INFO" (see \MetaInfoBase)
		 */

		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}


		/**
		 * \brief	Gets the second parameter's MetaInfo.
		 *
		 * \return	The second parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P2_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}

		/**
		 * \brief	Sets the second parameter's MetaInfo.
		 *
		 * \param p2MetaInfo	The second parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P2_META_INFO" (see \MetaInfoBase)
		 */

		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}


		/**
		 * \brief	Gets the third parameter's MetaInfo.
		 *
		 * \return	The third parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P3_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}

		/**
		 * \brief	Sets the third parameter's MetaInfo.
		 *
		 * \param p3MetaInfo	The third parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P3_META_INFO" (see \MetaInfoBase)
		 */

		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}


		/**
		 * \brief	Gets the fourth parameter's MetaInfo.
		 *
		 * \return	The fourth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P4_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}

		/**
		 * \brief	Sets the fourth parameter's MetaInfo.
		 *
		 * \param p4MetaInfo	The fourth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P4_META_INFO" (see \MetaInfoBase)
		 */

		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}


		/**
		 * \brief	Gets the fifth parameter's MetaInfo.
		 *
		 * \return	The fifth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P5_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}

		/**
		 * \brief	Sets the fifth parameter's MetaInfo.
		 *
		 * \param p5MetaInfo	The fifth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P5_META_INFO" (see \MetaInfoBase)
		 */

		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}


		/**
		 * \brief	Gets the sixth parameter's MetaInfo.
		 *
		 * \return	The sixth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P6_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}

		/**
		 * \brief	Sets the sixth parameter's MetaInfo.
		 *
		 * \param p6MetaInfo	The sixth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P6_META_INFO" (see \MetaInfoBase)
		 */

		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}


		/**
		 * \brief	Gets the seventh parameter's MetaInfo.
		 *
		 * \return	The seventh parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P7_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}

		/**
		 * \brief	Sets the seventh parameter's MetaInfo.
		 *
		 * \param p7MetaInfo	The seventh parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P7_META_INFO" (see \MetaInfoBase)
		 */

		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

	
		/**
		 * \brief	Gets the eighth parameter's MetaInfo.
		 *
		 * \return	The eighth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P8_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& getP8MetaInfo()const {return m_p8MetaInfo;}

		/**
		 * \brief	Sets the eighth parameter's MetaInfo.
		 *
		 * \param p1MetaInfo	The eighth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P8_META_INFO" (see \MetaInfoBase)
		 */

		void setP8MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo) {m_p8MetaInfo = p8MetaInfo;}


		/**
		 * \brief	Gets the ninth parameter's MetaInfo.
		 *
		 * \return	The ninth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P9_META_INFO" (see \MetaInfoBase)
		 */

		const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& getP9MetaInfo()const {return m_p9MetaInfo;}

		/**
		 * \brief	Sets the ninth parameter's MetaInfo.
		 *
		 * \param p9MetaInfo	The ninth parameter's MetaInfo.
		 * 			
		 * 	corresponding attribute: "P9_META_INFO" (see \MetaInfoBase)
		 */

		void setP9MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& p9MetaInfo) {m_p9MetaInfo = p9MetaInfo;}

	public:

		/**
		 * \fn	friend bool operator==(const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& lhs, const SK::MetaInfo<R(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the two MetaInfo share the same description and all the subsequent MetaInfo are equivalent.
		 */

		friend bool operator==(const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& lhs, const SK::MetaInfo<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	) &&
				(lhs.m_p8MetaInfo	 == rhs.m_p8MetaInfo	) &&
				(lhs.m_p9MetaInfo	 == rhs.m_p9MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 9;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			case 6: return "P7_META_INFO";
			case 7: return "P8_META_INFO";
			case 8: return "P9_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			case 8: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			if(name == "P8_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			if(name == "P9_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);
			case 6: return SK::RawData(m_p7MetaInfo);
			case 7: return SK::RawData(m_p8MetaInfo);
			case 8: return SK::RawData(m_p9MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 8: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p9MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p8MetaInfo);
			}
			if(name == "P9_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p9MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> *>(value);
			}
			if(name == "P9_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p9MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> m_p8MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> m_p9MetaInfo;
	};

	//! \cond METAINFO_FUNC_RESULT

	template <> 
	class MetaInfo<SK::Result()> : public MetaInfoImpl<MetaInfoClassExtractorTrait<SK::Result()>::DataType_T, MetaInfoClassExtractorTrait<SK::Result()>::DataTypeID>
	{
		typedef MetaInfoImpl<MetaInfoClassExtractorTrait<SK::Result()>::DataType_T, MetaInfoClassExtractorTrait<SK::Result()>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = ""):
		base_t(description)
		{
		}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result()>& lhs, const SK::MetaInfo<SK::Result()>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription());
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 0;}
		virtual SK::String getAttributeName(uint32_t /*id*/)const 
		{
			assert(false); return "";
		}
		virtual SK::TypeInfo getAttributeType(uint32_t /*id*/)const 
		{
			assert(false); return SK::Type<SK::UnknownType>::INFO;
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& /*name*/) const
		{
			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t /*id*/)const
		{
			assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttribute(uint32_t /*id*/, const SK::RawData& /*value*/)
		{
			assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& /*name*/, const SK::TypeInfo& /*typeInfo*/)const 
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& /*name*/, const void* /*value*/, const SK::TypeInfo& /*typeInfo*/)
		{
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	};

	template <typename P1> 
	class MetaInfo<SK::Result(P1)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1)>& lhs, const SK::MetaInfo<SK::Result(P1)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 1;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
	};

	template <typename P1, typename P2> 
	class MetaInfo<SK::Result(P1, P2)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2)>& lhs, const SK::MetaInfo<SK::Result(P1, P2)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 2;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
	};

	template <typename P1, typename P2, typename P3> 
	class MetaInfo<SK::Result(P1, P2, P3)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 3;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
	};

	template <typename P1, typename P2, typename P3, typename P4>
	class MetaInfo<SK::Result(P1, P2, P3, P4)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3, P4)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3, P4)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 4;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
	};


	template <typename P1, typename P2, typename P3, typename P4, typename P5>
	class MetaInfo<SK::Result(P1, P2, P3, P4, P5)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 5;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
	};

	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 6;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
	};


	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 7;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			case 6: return "P7_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);
			case 6: return SK::RawData(m_p7MetaInfo);

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
	};


	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo = MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo),
			m_p8MetaInfo(p8MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& getP8MetaInfo()const {return m_p8MetaInfo;}
		void setP8MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo) {m_p8MetaInfo = p8MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	) &&
				(lhs.m_p8MetaInfo	 == rhs.m_p8MetaInfo	);
		}

	public:
		virtual uint32_t getNumberOfAttributes()const {return 8;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			case 6: return "P7_META_INFO";
			case 7: return "P8_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			if(name == "P8_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);
			case 6: return SK::RawData(m_p7MetaInfo);
			case 7: return SK::RawData(m_p8MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p8MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> m_p8MetaInfo;
	};
	template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)> : public MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataTypeID>
	{
		typedef MetaInfoImpl<typename MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataType_T, MetaInfoClassExtractorTrait<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", 
			const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo = MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo = MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo = MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo = MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo = MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo = MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo = MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo = MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>(),
			const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& p9MetaInfo = MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>()
			):
		base_t(description), 
			m_p1MetaInfo(p1MetaInfo), 
			m_p2MetaInfo(p2MetaInfo), 
			m_p3MetaInfo(p3MetaInfo), 
			m_p4MetaInfo(p4MetaInfo),
			m_p5MetaInfo(p5MetaInfo),
			m_p6MetaInfo(p6MetaInfo),
			m_p7MetaInfo(p7MetaInfo),
			m_p8MetaInfo(p8MetaInfo),
			m_p9MetaInfo(p9MetaInfo)
		{
		}

	public:
		const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& getP1MetaInfo()const {return m_p1MetaInfo;}
		void setP1MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t>& p1MetaInfo) {m_p1MetaInfo = p1MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& getP2MetaInfo()const {return m_p2MetaInfo;}
		void setP2MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t>& p2MetaInfo) {m_p2MetaInfo = p2MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& getP3MetaInfo()const {return m_p3MetaInfo;}
		void setP3MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t>& p3MetaInfo) {m_p3MetaInfo = p3MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& getP4MetaInfo()const {return m_p4MetaInfo;}
		void setP4MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t>& p4MetaInfo) {m_p4MetaInfo = p4MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& getP5MetaInfo()const {return m_p5MetaInfo;}
		void setP5MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t>& p5MetaInfo) {m_p5MetaInfo = p5MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& getP6MetaInfo()const {return m_p6MetaInfo;}
		void setP6MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t>& p6MetaInfo) {m_p6MetaInfo = p6MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& getP7MetaInfo()const {return m_p7MetaInfo;}
		void setP7MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t>& p7MetaInfo) {m_p7MetaInfo = p7MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& getP8MetaInfo()const {return m_p8MetaInfo;}
		void setP8MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t>& p8MetaInfo) {m_p8MetaInfo = p8MetaInfo;}

		const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& getP9MetaInfo()const {return m_p9MetaInfo;}
		void setP9MetaInfo(const MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t>& p9MetaInfo) {m_p9MetaInfo = p9MetaInfo;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& lhs, const SK::MetaInfo<SK::Result(P1, P2, P3, P4, P5, P6, P7, P8, P9)>& rhs)
		{
			return (lhs.getDescription() == rhs.getDescription()) && 
				(lhs.m_p1MetaInfo	 == rhs.m_p1MetaInfo	) &&
				(lhs.m_p2MetaInfo	 == rhs.m_p2MetaInfo	) &&
				(lhs.m_p3MetaInfo	 == rhs.m_p3MetaInfo	) &&
				(lhs.m_p4MetaInfo	 == rhs.m_p4MetaInfo	) &&
				(lhs.m_p5MetaInfo	 == rhs.m_p5MetaInfo	) &&
				(lhs.m_p6MetaInfo	 == rhs.m_p6MetaInfo	) &&
				(lhs.m_p7MetaInfo	 == rhs.m_p7MetaInfo	) &&
				(lhs.m_p8MetaInfo	 == rhs.m_p8MetaInfo	) &&
				(lhs.m_p9MetaInfo	 == rhs.m_p9MetaInfo	);
		}
	public:
		virtual uint32_t getNumberOfAttributes()const {return 9;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "P1_META_INFO";
			case 1: return "P2_META_INFO";
			case 2: return "P3_META_INFO";
			case 3: return "P4_META_INFO";
			case 4: return "P5_META_INFO";
			case 5: return "P6_META_INFO";
			case 6: return "P7_META_INFO";
			case 7: return "P8_META_INFO";
			case 8: return "P9_META_INFO";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			case 1: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			case 2: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			case 3: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			case 4: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			case 5: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			case 6: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			case 7: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			case 8: return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "P1_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO;
			if(name == "P2_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO;
			if(name == "P3_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO;
			if(name == "P4_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO;
			if(name == "P5_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO;
			if(name == "P6_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO;
			if(name == "P7_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO;
			if(name == "P8_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO;
			if(name == "P9_META_INFO") return SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_p1MetaInfo);
			case 1: return SK::RawData(m_p2MetaInfo);
			case 2: return SK::RawData(m_p3MetaInfo);
			case 3: return SK::RawData(m_p4MetaInfo);
			case 4: return SK::RawData(m_p5MetaInfo);
			case 5: return SK::RawData(m_p6MetaInfo);
			case 6: return SK::RawData(m_p7MetaInfo);
			case 7: return SK::RawData(m_p8MetaInfo);
			case 8: return SK::RawData(m_p9MetaInfo);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 1: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 2: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 3: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 4: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 5: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 6: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 7: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >();
				return SK::Result::NoError;
			case 8: 
				if(SK::Type< MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p9MetaInfo = value.getRef< MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >();
				return SK::Result::NoError;

			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}

	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p1MetaInfo);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p2MetaInfo);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p3MetaInfo);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p4MetaInfo);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p5MetaInfo);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p6MetaInfo);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p7MetaInfo);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p8MetaInfo);
			}
			if(name == "P9_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_p9MetaInfo);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "P1_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p1MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> *>(value);
			}
			if(name == "P2_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p2MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> *>(value);
			}
			if(name == "P3_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p3MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> *>(value);
			}
			if(name == "P4_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p4MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> *>(value);
			}
			if(name == "P5_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p5MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> *>(value);
			}
			if(name == "P6_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p6MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> *>(value);
			}
			if(name == "P7_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p7MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> *>(value);
			}
			if(name == "P8_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p8MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> *>(value);
			}
			if(name == "P9_META_INFO") 
			{
				if(SK::Type< SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_p9MetaInfo = *static_cast<const  SK::MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}

	private:
		MetaInfo<typename SK::RefTypeTrait<P1>::remove_const_ref_t> m_p1MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P2>::remove_const_ref_t> m_p2MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P3>::remove_const_ref_t> m_p3MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P4>::remove_const_ref_t> m_p4MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P5>::remove_const_ref_t> m_p5MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P6>::remove_const_ref_t> m_p6MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P7>::remove_const_ref_t> m_p7MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P8>::remove_const_ref_t> m_p8MetaInfo;
		MetaInfo<typename SK::RefTypeTrait<P9>::remove_const_ref_t> m_p9MetaInfo;
	};

	//! \endcond

	template<>
	class MetaInfo<SK::HandPosingGestureEvent> : public MetaInfoImpl<MetaInfoClassExtractorTrait<SK::HandPosingGestureEvent>::DataType_T, MetaInfoClassExtractorTrait<SK::HandPosingGestureEvent>::DataTypeID>
	{
		typedef MetaInfoImpl<MetaInfoClassExtractorTrait<SK::HandPosingGestureEvent>::DataType_T, MetaInfoClassExtractorTrait<SK::HandPosingGestureEvent>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", const SK::EnumMapper& enumMapper= SK::EnumMapper()):
		base_t(description), 
		m_enumMapper(enumMapper)
		{
		}

	public:
		const SK::EnumMapper& getEnumMapper()const {return m_enumMapper;}
		void setEnumMapper(const SK::EnumMapper& enumMapper) {m_enumMapper = enumMapper;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::HandPosingGestureEvent>& lhs, const SK::MetaInfo<SK::HandPosingGestureEvent>& rhs)
		{
			if(lhs.getDescription() != rhs.getDescription()) return false;
			if(lhs.getEnumMapper().numID() != rhs.getEnumMapper().numID()) return false;
			for(uint32_t i = 0, size = lhs.getEnumMapper().numID(); i < size; ++i)
			{
				const SK::EnumMapper::EnumValue& evLhs = lhs.getEnumMapper().getEnum(i);
				const SK::EnumMapper::EnumValue& evRhs = rhs.getEnumMapper().getEnum(i);
				if(evLhs.id != evRhs.id || evLhs.name != evRhs.name) return false;
			}
			return true;
		}


	public:
		virtual uint32_t getNumberOfAttributes()const {return 1;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "ENUM_MAPPER";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::EnumMapper >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "ENUM_MAPPER") return SK::Type< SK::EnumMapper >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_enumMapper);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<SK::EnumMapper>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_enumMapper = value.getRef<SK::EnumMapper>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type< SK::EnumMapper >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_enumMapper);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type< SK::EnumMapper >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_enumMapper = *static_cast<const  SK::EnumMapper *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}


	private:
		SK::EnumMapper m_enumMapper;
	};




	template<>
	class MetaInfo<SK::HandMovingGestureEvent> : public MetaInfoImpl<MetaInfoClassExtractorTrait<SK::HandMovingGestureEvent>::DataType_T, MetaInfoClassExtractorTrait<SK::HandMovingGestureEvent>::DataTypeID>
	{
		typedef MetaInfoImpl<MetaInfoClassExtractorTrait<SK::HandMovingGestureEvent>::DataType_T, MetaInfoClassExtractorTrait<SK::HandMovingGestureEvent>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", const SK::EnumMapper& enumMapper= SK::EnumMapper()):
		base_t(description), 
			m_enumMapper(enumMapper)
		{
		}

	public:
		const SK::EnumMapper& getEnumMapper()const {return m_enumMapper;}
		void setEnumMapper(const SK::EnumMapper& enumMapper) {m_enumMapper = enumMapper;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::HandMovingGestureEvent>& lhs, const SK::MetaInfo<SK::HandMovingGestureEvent>& rhs)
		{
			if(lhs.getDescription() != rhs.getDescription()) return false;
			if(lhs.getEnumMapper().numID() != rhs.getEnumMapper().numID()) return false;
			for(uint32_t i = 0, size = lhs.getEnumMapper().numID(); i < size; ++i)
			{
				const SK::EnumMapper::EnumValue& evLhs = lhs.getEnumMapper().getEnum(i);
				const SK::EnumMapper::EnumValue& evRhs = rhs.getEnumMapper().getEnum(i);
				if(evLhs.id != evRhs.id || evLhs.name != evRhs.name) return false;
			}
			return true;
		}


	public:
		virtual uint32_t getNumberOfAttributes()const {return 1;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "ENUM_MAPPER";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::EnumMapper >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "ENUM_MAPPER") return SK::Type< SK::EnumMapper >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_enumMapper);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<SK::EnumMapper>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_enumMapper = value.getRef<SK::EnumMapper>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type< SK::EnumMapper >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_enumMapper);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type< SK::EnumMapper >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_enumMapper = *static_cast<const  SK::EnumMapper *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}


	private:
		SK::EnumMapper m_enumMapper;
	};


	template<>
	class MetaInfo<SK::UserClippedByFrustumEvent> : public MetaInfoImpl<MetaInfoClassExtractorTrait<SK::UserClippedByFrustumEvent>::DataType_T, MetaInfoClassExtractorTrait<SK::UserClippedByFrustumEvent>::DataTypeID>
	{
		typedef MetaInfoImpl<MetaInfoClassExtractorTrait<SK::UserClippedByFrustumEvent>::DataType_T, MetaInfoClassExtractorTrait<SK::UserClippedByFrustumEvent>::DataTypeID> base_t;
	public:
		explicit MetaInfo(const SK::String& description = "", const SK::EnumMapper& enumMapper= SK::EnumMapper()):
		base_t(description), 
			m_enumMapper(enumMapper)
		{
		}

	public:
		const SK::EnumMapper& getEnumMapper()const {return m_enumMapper;}
		void setEnumMapper(const SK::EnumMapper& enumMapper) {m_enumMapper = enumMapper;}

	public:
		friend bool operator==(const SK::MetaInfo<SK::UserClippedByFrustumEvent>& lhs, const SK::MetaInfo<SK::UserClippedByFrustumEvent>& rhs)
		{
			if(lhs.getDescription() != rhs.getDescription()) return false;
			if(lhs.getEnumMapper().numID() != rhs.getEnumMapper().numID()) return false;
			for(uint32_t i = 0, size = lhs.getEnumMapper().numID(); i < size; ++i)
			{
				const SK::EnumMapper::EnumValue& evLhs = lhs.getEnumMapper().getEnum(i);
				const SK::EnumMapper::EnumValue& evRhs = rhs.getEnumMapper().getEnum(i);
				if(evLhs.id != evRhs.id || evLhs.name != evRhs.name) return false;
			}
			return true;
		}


	public:
		virtual uint32_t getNumberOfAttributes()const {return 1;}
		virtual SK::String getAttributeName(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return "ENUM_MAPPER";
			default: assert(false); return "";
			}
		}
		virtual SK::TypeInfo getAttributeType(uint32_t id)const 
		{
			switch(id)
			{
			case 0: return SK::Type< SK::EnumMapper >::INFO;
			default: assert(false); return SK::Type<SK::UnknownType>::INFO;
			}
		}
		virtual SK::TypeInfo getAttributeType(const SK::String& name) const
		{
			if(name == "ENUM_MAPPER") return SK::Type< SK::EnumMapper >::INFO;

			return SK::Type<SK::UnknownType>::INFO;
		}

		virtual SK::Return<SK::RawData> getAttribute(uint32_t id)const
		{
			switch(id)
			{
			case 0: return SK::RawData(m_enumMapper);
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}		
		}
		virtual SK::Result setAttribute(uint32_t id, const SK::RawData& value)
		{
			switch(id)
			{
			case 0: 
				if(SK::Type<SK::EnumMapper>::INFO != value.getType()) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_enumMapper = value.getRef<SK::EnumMapper>();
				return SK::Result::NoError;
			default: assert(false); return SK::Result("Invalid ID", INVALID_META_ATTRIBUTE);
			}
		}
	protected:
		virtual SK::Return<SK::RawData> getAttributeImpl(const SK::String& name, const SK::TypeInfo& typeInfo)const 
		{
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type< SK::EnumMapper >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				return SK::RawData(m_enumMapper);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);
		}
		virtual SK::Result setAttributeImpl(const SK::String& name, const void* value, const SK::TypeInfo& typeInfo)
		{
			if(name == "ENUM_MAPPER") 
			{
				if(SK::Type< SK::EnumMapper >::INFO != typeInfo) return SK::Result("Wrong attribute type", SK::INVALID_DATA_TYPE);
				m_enumMapper = *static_cast<const  SK::EnumMapper *>(value);
			}
			return SK::Result("No such attributes", INVALID_META_ATTRIBUTE);		
		}


	private:
		SK::EnumMapper m_enumMapper;
	};
}
