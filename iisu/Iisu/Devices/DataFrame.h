#pragma once
#include <Foundation/Services/Types/RawData.h>
#include <Foundation/Services/Types/TypeInfo.h>
#include <Framework/Errors/Return.h>

namespace SK
{
	/**
	 * \class	DataFrame
	 *
	 * \brief	Class containing a snapshot of the data computed by iisu at one given time. 
	 */

	class DataFrame
	{
	public:

		/**
		 * \struct	Handle
		 *
		 * \brief	Handle used for internal storage. 
		 */

		struct Handle 
		{
			SK::RawData data;
			bool isValid;

			explicit Handle(const SK::RawData& p_data, bool m_isValid = true):data(p_data), isValid(m_isValid){}
			Handle():isValid(false){}
		};

	public:

		/**
		 * \fn	virtual DataFrame::~DataFrame()
		 *
		 * \brief	Destructor.
		 */

		virtual ~DataFrame() {}

		/**
		 * \fn	Return<T> DataFrame::get(int32_t dataID)const
		 *
		 * \brief	Gets the data of type <T> associated to the specified dataID.
		 *
		 * \param	dataID	The identifier of the data to get.
		 *
		 * \return	A Return containing either the associated value or an error.
		 */

		template <typename T>
		Return<T> get(int32_t dataID)const
		{
			SK::Return<SK::DataFrame::Handle> ret =  get(dataID, SK::Type<T>::INFO);
			if(ret.failed()) return ret.toResult();
			DataFrame::Handle dh = ret.get();
			if(!dh.isValid || !dh.data.isValid()) return SK::Result("Invalid data frame handle", SK::INVALID_HANDLE);
			return dh.data.getRef<T>();
		}

		/**
		 * \fn	virtual SK::Result DataFrame::lock()const = 0;
		 *
		 * \brief	Locks the DataFrame
		 *
		 * \return	a \sa Result specifying if the operation was successful or not
		 */

		virtual SK::Result lock()const = 0;

		/**
		 * \fn	virtual SK::Result DataFrame::unlock()const = 0;
		 *
		 * \brief	Unocks the DataFrame
		 *
		 * \return	a \sa Result specifying if the operation was successful or not
		 */		

		virtual SK::Result unlock()const = 0;

		/**
		 * \fn	virtual int32_t DataFrame::getFrameID()const = 0;
		 *
		 * \brief	Gets the frame identifier.
		 *
		 * \return	The frame identifier.
		 */

		virtual int32_t getFrameID()const = 0;

		/**
		 * \fn	virtual void DataFrame::setFrameID(uint32_t)const = 0;
		 *
		 * \brief	Sets the frame identifier.
		 *
		 * \param	The frame identifier.
		 */

		virtual void setFrameID(int32_t) = 0;



		virtual Return<DataFrame::Handle> get(int32_t dataID, const TypeInfo &typeinfo)const = 0;

		/**
		 * \fn	virtual SK::Return<bool> DataFrame::isValid(int32_t dataID)const = 0;
		 *
		 * \brief	Returns wheter the data associated to the given dataID is valid or not.
		 *
		 * \param	dataID	Identifier for the data.
		 *
		 * \return	a Return containing the validity of the data if successful
		 */

		virtual SK::Return<bool> isValid(int32_t dataID)const = 0;

		/**
		 * \fn	virtual SK::Array<DataFrame::Handle>& DataFrame::getAll()=0;
		 *
		 * \brief	Returns a reference to the internal array containing all of the datas contained by the frame.
		 *
		 * \return	a reference to the array of handles.
		 */

		virtual SK::Array<DataFrame::Handle>& getAll()=0;
		virtual const SK::Array<DataFrame::Handle>& getAll()const=0;
	};
}
