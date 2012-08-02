#pragma once

#include <Platform/SkPlatform.h>
#include <Foundation/DataTypes/String/String.h>
#include <Framework/Errors/Return.h>
#include <Foundation/DataTypes/Array/Array.h>

#if (SK_COMPILER == SK_COMPILER_MSVC)
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif


namespace SK
{
	/**
	 * \struct	Enum
	 *
	 * \brief	Structure representing an enum value.
	 */

	struct IISUSDK_API Enum
	{
		///< The enum value
		uint32_t value;

		/**
		 * \fn	Enum& operator=(uint32_t id);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	id	The enum value.
		 *
		 * \return	A copy of this object.
		 */

		Enum& operator=(uint32_t id);

		/**
		 * \fn	operator uint32_t&();
		 *
		 * \brief	Conversion operator.
		 */

		operator uint32_t&();

		/**
		 * \fn	operator uint32_t()const;
		 *
		 * \brief	Conversion operator.
		 */

		operator uint32_t()const;

		/**
		 * \fn	Enum(uint32_t v=0);
		 *
		 * \brief	Constructor.
		 *
		 * \param	v	(optional) the enum value.
		 */

		Enum(uint32_t v=0);
	};

	/**
	 * \struct	EnumMapper
	 *
	 * \brief	class representing a mapper between enumerate values and corresponding string names. 
	 */

	struct IISUSDK_API EnumMapper
	{
	public:

		/**
		 * \struct	EnumValue
		 *
		 * \brief	An enumeration entry with its integer id and the corresponding string. 
		 */

		struct IISUSDK_API EnumValue
		{
			///< The enum value
			uint32_t id;
			///< The name
			SK::String name;

			/**
			 * \fn	EnumValue(uint32_t id_, SK::String name_)
			 *
			 * \brief	Constructor.
			 *
			 * \param	id_  	The enum value.
			 * \param	name_	The name.
			 */

			EnumValue(uint32_t id_, SK::String name_):id(id_), name(name_){}

			/**
			 * \fn	EnumValue()
			 *
			 * \brief	Default constructor.
			 */

			EnumValue(){}
		};

	public:

		/**
		 * \fn	SK::Return<SK::String> operator[](uint32_t id) const
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	id	The enum value.
		 *
		 * \return	The associated name.
		 */

		SK::Return<SK::String> operator[](uint32_t id) const
		{
			for(uint32_t i = 0, size = m_enumValues.size(); i < size; ++i)
			{
				if(m_enumValues[i].id == id) return m_enumValues[i].name;
			}
			return SK::Result("Id not found", SK::INVALID_INDEX);
		}

		/**
		 * \fn	SK::Return<uint32_t> operator[](const SK::String& name) const
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	name	The name.
		 *
		 * \return	The associated enum value.
		 */

		SK::Return<uint32_t> operator[](const SK::String& name) const
		{
			for(uint32_t i = 0, size = m_enumValues.size(); i < size; ++i)
			{
				if(m_enumValues[i].name == name) return m_enumValues[i].id;
			}
			return SK::Result("Name not found", SK::INVALID_INDEX);
		}

		/**
		 * \fn	void add(uint32_t id, const SK::String& name)
		 *
		 * \brief	Adds association of enum value, name to the mapper.
		 *
		 * \param	id  	The enum value.
		 * \param	name	The name.
		 */

		void add(uint32_t id, const SK::String& name)
		{
			for(uint32_t i = 0, size = m_enumValues.size(); i < size; ++i)
			{
				if(m_enumValues[i].id == id) 
				{
					m_enumValues[i].name = name;
					return;
				}
			}

			m_enumValues.pushBack(EnumValue(id, name));
		}

		/**
		 * \fn	EnumValue& getEnum(uint32_t idx)
		 *
		 * \brief	Gets an enum value from index.
		 *
		 * \param	index of the enum value.
		 *
		 * \return	The enum value.
		 */

		EnumValue& getEnum(uint32_t idx)
		{
			assert(idx<numID());
			return m_enumValues[idx];
		}

		/**
		 * \fn	const EnumValue& getEnum(uint32_t idx)const
		 *
		 * \brief	Gets an enum value from index.
		 *
		 * \param	index of the enum value.
		 *
		 * \return	The enum value.
		 */

		const EnumValue& getEnum(uint32_t idx)const
		{
			assert(idx<numID());
			return m_enumValues[idx];
		}

		/**
		 * \fn	uint32_t numID()const
		 *
		 * \brief	Gets the number of enum/name associations.
		 *
		 * \return	The total number of enum/name associations.
		 */

		uint32_t numID()const {return m_enumValues.size();}

	private:
		SK::Array<EnumValue> m_enumValues;
	};


}


#if (SK_COMPILER == SK_COMPILER_MSVC)
#pragma warning( pop )
#endif

