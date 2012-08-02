#pragma once

#include <Foundation/Services/Types/TypeInfoImpl.h>

#include <Platform/SkPlatform.h>

#include <iostream>
#include <memory>

#include <Framework/Types/RefTypeTrait.h>

namespace SK
{
	/**
	 * \class	RawData
	 *
	 * \brief	Raw data represent a typeless representation of any serializable data of iisu. 
	 * 			
	 * The raw data contains a void* as an abstract pointer to any data and a TypeInfo that indicates it original type.
	 * The raw data can be responsible for managing the data it contains or not. If the raw data is responsible for its 
	 * internal data it acts like a shared pointer, meaning that when the raw data get copied the copy will share the 
	 * pointer with the original and the last raw data to get destroyed is responsible for the clean up of the internal 
	 * data.
	 */

	class IISUSDK_API RawData
	{
	public:
		/**
		 * \fn	template <typename T> explicit RawData::RawData(const T& data, bool manageContent = false)
		 *
		 * \brief	Constructor from a typed data.
		 *
		 * \param	data		 	The data to abstract inside the raw data.
		 * \param	manageContent	(optional) if true, the raw data is responsible of the life cycle of the 
		 * 							internal data.
		 * 							
		 * This constructor deduce the type info from the template parameter (type = SK::Type<T>::INFO).
		 */		
		template<typename T>
		explicit RawData(const T& data, bool manageContent = false): m_counter(NULL)
		{
			m_data = const_cast<T*>(&data);
			m_type = SK::Type<T>::INFO;
			if(manageContent) acquireImpl();
		}
		/**
		 * \fn	template <typename T> RawData::RawData(const T& data, const SK::TypeInfo& info, bool manageContent = false)
		 *
		 * \brief	Constructor from a typed data and a manually specified TypeInfo.
		 *
		 * \param	data		 	The data to abstract inside the raw data.
		 * \param	info		 	The TypeInfo.
		 * \param	manageContent	(optional) if true, the raw data is responsible of the life cycle of the 
		 * 							internal data.
		 * This constructor is used when the automatically deduced type needs to be overrided. 
		 * \warning Giving the wrong Type Info can lead to serious problem and/or crash, use this only if you 
		 * know what you're doing.
		 */
		template<typename T>
		RawData(const T& data, const SK::TypeInfo& info, bool manageContent = false): m_counter(NULL)
		{
			m_data = const_cast<T*>(&data);
			m_type = info;
			if(manageContent) acquireImpl();
		}

		/**
		 * \fn	RawData::RawData(void* data, const SK::TypeInfo& type, bool manageContent = false);
		 *
		 * \brief	Constructor from a generic pointer and a TypeInfo specifying the type of the object pointed by 
		 * 			this pointer.
		 *
		 * \param 	data 			Generic pointer to the data.
		 * \param	type		 	The TypeInfo.
		 * \param	manageContent	(optional) if true, the raw data is responsible of the life cycle of the 
		 * 							internal data.
		 * This constructor is used when a type internal data is not available.							
		 * \warning Giving the wrong Type Info can lead to serious problem and/or crash, use this only if you 
		 * know what you're doing.
		 */
		RawData(void* data, const SK::TypeInfo& type, bool manageContent = false);

		/**
		 * \fn	RawData::RawData();
		 *
		 * \brief	Default constructor.
		 * 			
		 * This constructor construct an invalid RawData with a SK::UnknownType as TypeInfo
		 */
		RawData();

		/**
		 * \fn	RawData::~RawData();
		 *
		 * \brief	Destructor.
		 * 			
		 * This destructor does nothing except if the RawData was responsible for its internal data in which case its
		 *  will destroy the internal data. This destruction occurs only if this RawData is the last one pointing to 
		 *  the internal data.
		 */
		~RawData();

		/**
		 * \fn	RawData::RawData(const RawData& other);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	other	The original RawData.
		 * 					
		 * This all the new	RawData to share the same internal data as the original one. If the original RawData was 
		 * responsible for managing its content then this RawData shares that responsibility.
		 */
		RawData(const RawData& other);

		/**
		 * \fn	RawData& RawData::operator= (const RawData& other);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	other	The original RawData.
		 *
		 * \return	A shallow copy of this object. 
		 * 			
		 * See the copy constructor for more detail
		 * \sa RawData::RawData(const RawData& other);
		 */
		RawData& operator= (const RawData& other);

		/**
		 * \fn	void RawData::copyTo(void* target)const;
		 *
		 * \brief	Copies the internal data to the object pointed by target.
		 *
		 * \param [in,out]	target	target for the copy.
		 * 			
		 * target must be a pointer to a valid object of the proper type that match the TypeInfo of the RawData
		 */
		void copyTo(void* target)const;

		/**
		 * \fn	void* RawData::copyContent()const;
		 *
		 * \brief	Copies the content.
		 *
		 * \return	null if it fails, else a pointer to a copy of the internal data.
		 * 
		 * The newly created data's life cycle is the responsibility of the RawData and the user must take care of its 
		 * destruction.
		 */
		void* copyContent()const;

		/**
		 * \fn	template <typename T> typename SK::RefTypeTrait<T>::add_const_ref_t RawData::getRef()const
		 *
		 * \brief	Gets a typed reference to the internal data.
		 *
		 * \return	A reference to the internal data.
		 * 			
		 * 	This is just a casting of the void* to a T* and dereferences it so the casting must be valid. To make sure 
		 * 	of that the method asserts that the TypeInfo deduce from the template parameter T is equal to the one in the 
		 * 	RawData.
		 */
		template <typename T>
		typename SK::RefTypeTrait<T>::add_const_ref_t getRef()const
		{
			assert(SK::Type<T>::INFO == m_type);
			return  *static_cast<typename SK::RefTypeTrait<T>::remove_ref_t*>(m_data);
		}
		/**
		 * \fn	template <typename T> typename SK::RefTypeTrait<T>::add_const_ref_t RawData::getRef()const
		 *
		 * \brief	Gets a typed reference to the internal data.
		 *
		 * \return	A reference to the internal data.
		 * 			
		 * 	This is just a casting of the void* to a T* and dereferences it so the casting must be valid. To make sure 
		 * 	of that the method asserts that the TypeInfo deduce from the template parameter T is equal to the one in the 
		 * 	RawData.
		 */
		template <typename T>
		typename SK::RefTypeTrait<T>::add_ref_t getRef()
		{
			assert(SK::Type<T>::INFO == m_type);
			return  *static_cast<typename SK::RefTypeTrait<T>::remove_ref_t*>(m_data);
		}
		/**
		 * \fn	template <typename T> typename SK::RefTypeTrait<T>::add_const_ref_t RawData::getRef()const
		 *
		 * \brief	Gets a typed copy of the internal data.
		 *
		 * \return	A copy of the internal data.
		 * 			
		 * 	This is just a casting of the void* to a T*, dereferencing and implicitly calling of the copy constructor 
		 * 	of the class T. So the casting must be valid. To make sure of that the method asserts that the TypeInfo 
		 * 	deduce from the template parameter T is equal to the one in the RawData.
		 */
		template <typename T>
		typename SK::RefTypeTrait<T>::remove_const_ref_t getCopy()
		{
			assert(SK::Type<T>::INFO == m_type);
			return *static_cast<typename SK::RefTypeTrait<T>::remove_const_ref_t*>(m_data);
		}

		/**
		 * \fn	bool RawData::isUnique()const;
		 *
		 * \brief	Query if this object is unique.
		 *
		 * \return	true if unique, false if not.
		 * 			
		 * A RawData is unique if either it does not manage its content or if it is the only RawData currently managing 
		 * the content.
		 */
		bool isUnique()const;

		/**
		 * \fn	bool RawData::hasManagedContent()const;
		 *
		 * \brief	Query if this object has managed content.
		 *
		 * \return	true if managed content, false if not.
		 * 			
		 * This is used to know if the RawData is responsible of the life cycle of the internal data in contains.
		 */
		bool hasManagedContent()const;

		/**
		 * \fn	bool RawData::isValid()const;
		 *
		 * \brief	Query if this object is valid.
		 *
		 * \return	true if valid, false if not.
		 * 			
		 * A RawData is valid it contains a valid pointer to a internal data.
		 */
		bool isValid()const;

		/**
		 * \fn	SK::RawData RawData::clone() const;
		 *
		 * \brief	Makes a deep copy of this object. 
		 *
		 * \return	A copy of this object.
		 * 			
		 * \warning The new RawData is always managing its new content.
		 */
		SK::RawData clone() const;	

		/**
		 * \fn	void RawData::release();
		 *
		 * \brief	Releases the inner data.
		 * 
		 * If the data was not managed this method does nothing
		 * \warning if this RawData is the last handle to the shared internal data, the internal data will get deleted.
		 */

		void release();

		/**
		 * \fn	void RawData::acquire();
		 *
		 * \brief	Acquires the internal data's ownership.
		 * 
		 * This make this RawData responsible for its internal data.
		 * \warning If the RawData was already responsible this method does nothing.
		 */

		void acquire();

		/**
		 * \fn	inline void* RawData::getData()const
		 *
		 * \brief	Gets the internal data.
		 *
		 * \return	the internal data, null if the RawData was invalid.
		 */

		inline void* getData()const{return m_data;}

		/**
		 * \fn	const SK::TypeInfo& RawData::getType()const;
		 *
		 * \brief	Gets the type of the internal data.
		 *
		 * \return	The type of the internal data, this is the TypeInfo of SK::UnknownType.
		 * 
		 */

		const SK::TypeInfo& getType()const;

	private:
		void acquireImpl();

		void swap(RawData& other);

		void destroy();


	private:
		void* m_data; 
		SK::TypeInfo m_type;
		uint32_t* m_counter;

	};
}
