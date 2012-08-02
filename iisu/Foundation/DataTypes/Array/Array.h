#pragma once

#include <math.h>
#include <assert.h>
#include <vector>
#include <bitset>
#include <Platform/SkPlatform.h>

namespace SK
{
	template<typename T>

	/**
	* \class	Array
	*
	* \brief	class representing an array with variable capacity. 
	*	  
	*  	
	*/

	class Array
	{
	
	private:

		/**
		* \typedef	Array self_t
		*
		* \brief	Defines an alias representing the array type. 
		*/

		typedef Array self_t;

	public:

		/**
		* \typedef	T type_t
		*
		* \brief	Defines an alias representing the content type. 
		*/

		typedef T type_t;

		/**
		* \typedef	uint32_t size_t
		*
		* \brief	Defines an alias representing the size type. 
		*/

		typedef uint32_t size_t;

		/**
		* \typedef	const T* const_iterator
		*
		* \brief	Defines an alias representing the constant iterator. 
		*/

		typedef const T* const_iterator;

		/**
		* \typedef	T* iterator
		*
		* \brief	Defines an alias representing the iterator. 
		*/

		typedef T* iterator;

	public:

		/**
		* \fn	Array::Array()
		*
		* \brief	Default constructor.
		*		 
		* Initialize values array to null pointer, size and capacity to 0 
		*/

		Array():m_values(NULL),m_size(0),m_capacity(0){}

		/**
		* \fn	explicit Array::Array(size_t size)
		*
		* \brief	Constructor.
		*
		* \param	size	The size.
		*	
		*	Initializes size and capacity to the specified size
		*/

		explicit Array(size_t size):m_values(new T[size]), m_size(size), m_capacity(size){}

		/**
		* \fn	Array::Array(const std::vector<T>& vect)
		*
		* \brief	Conversion constructor from standard vector.
		*
		* \param	vect	The vect.
		*		 
		*	Copy the content of vect
		*/

		Array(const std::vector<T>& vect):m_values(NULL), m_size(vect.size()), m_capacity(m_size)
		{
			if(m_capacity != 0) 
			{
				m_values = new T[m_capacity];
				for(size_t i = 0; i < m_size; ++i) m_values[i] = vect[i];
			}
		}

		/**
		* \fn	Array::Array(const self_t& other)
		*
		* \brief	Copy constructor.
		*
		* \param	other	The other array.
		*/

		Array(const self_t& other):m_values(NULL), m_size(other.m_size), m_capacity(other.m_capacity)
		{
			if(m_capacity != 0) 
			{
				m_values = new T[m_capacity];
				for(size_t i = 0; i < m_size; ++i) m_values[i] = other.m_values[i];
			}
		}

		/**
		* \fn	Array::~Array()
		*
		* \brief	Destructor.
		*
		* Frees memory of internal array
		*/

		~Array()
		{
			destroy();
		}

		/**
		* \fn	Array& Array::operator=(const self_t& other)
		*
		* \brief	Assignment operator.
		*
		* \param	other	The array to be copied.
		*
		* \return	A shallow copy of this object.
		*/

		Array& operator=(const self_t& other)
		{
			Array tmp = other;
			swap(tmp);
			return *this;
		}

		/**
		* \fn	Array& Array::operator=(const std::vector<T>& vect)
		*
		* \brief	Assignment operator from standard vector.
		*
		* \param	vect	The vector to be copied.
		*
		* \return	A shallow copy of this vector.
		*/

		Array& operator=(const std::vector<T>& vect)
		{
			Array tmp = vect;
			swap(tmp);
			return *this;
		}

		/**
		* \fn	T& Array::operator[](size_t i)
		*
		* \brief	Array indexer operator.
		*
		* \param	i	index of the value.
		*
		* \return	The indexed value.
		*/

		T& operator[](size_t i)
		{
			assert(i<m_size);
			return m_values[i];
		}

		/**
		* \fn	const T& Array::operator[](size_t i)const
		*
		* \brief	Array indexer operator.
		*
		* \param	i	index of the value.
		*
		* \return	The indexed value.
		*/

		const T& operator[](size_t i)const
		{
			assert(i<m_size);
			return m_values[i];
		}

		/**
		* \fn	size_t Array::size()const
		*
		* \brief	Gets the size.
		*
		* \return	The size.
		*/

		size_t size()const {return m_size;}

		/**
		* \fn	size_t Array::getCapacity()const
		*
		* \brief	Gets the capacity.
		*
		* \return	The capacity.
		*/

		size_t getCapacity()const {return m_capacity;}

		/**
		* \fn	void Array::resize(size_t size, bool preserve=true)
		*
		* \brief	Resizes the array.
		*
		* \param	size		The new size.
		* \param	preserve	(optional) Flag indicating if containing data must be preserved.
		*		                If set, a copy of all values will be performed into the new array.
		*/

		void resize(size_t size, bool preserve=true)
		{
			if (size == m_size) return;
			if (size > m_capacity) 
			{
				setCapacity(size, preserve);
				m_size = size;
			}
			else
			{
				m_size = size;
			}
		}

		/**
		* \fn	virtual void Array::setCapacity(size_t capacity, bool preserve=true)
		*
		* \brief	Sets the capacity.
		*
		* \param	capacity	The new capacity.
		* \param	preserve	(optional) Flag indicating if containing data must be preserved.
		*		                If set, a copy of all values will be performed into the new array.
		*/

		virtual void setCapacity(size_t capacity, bool preserve=true)
		{
			if(capacity == m_size)return;
			assert(capacity>m_size);
			T* values = NULL;
			if (capacity > 0)
			{
				values = new T[capacity];
				if (preserve)
				{
					for(size_t i = 0; i<m_size; ++i)
						values[i] = m_values[i];
				}
			}
			delete[] m_values;
			m_values = values;
			m_capacity = capacity;
		}

		/**
		* \fn	void Array::clear()
		*
		* \brief	Clears this object to its blank/initial state.
		*        
		*  Only sets the size to 0. capacity stays unchanged and content is not destroyed.
		*/

		void clear()
		{
			m_size=0 ;
		}

		/**
		* \fn	void Array::pushBack(const T& value)
		*
		* \brief	Pushes a value at the end of the array.
		*
		* \param	item	The value.
		*  
		* \warning if current capacity is not big enough, setCapacity() is called with a new capacity of 1.5*capacity
		*/

		void pushBack(const T& value) 
		{
			if (m_size==m_capacity) 
			{
				setCapacity((size_t) ceil(std::max(m_capacity*1.5f,1.0f)));
			}
			m_values[m_size]=value;
			m_size++;
		}

		/**
		* \fn	void Array::assign(size_t n, const T& value)
		*
		* \brief	Resizes the array to n, and assigns the value u to the whole array.
		*
		* \param	n	The new size.
		* \param	u	The value.
		*/

		void assign(size_t n, const T& value)
		{
			if (n > m_size)
			{
				resize(n);
			}
			for (size_t i = 0; i < m_size; ++i)
			{
				m_values[i] = value;
			}
		}

		/**
		* \fn	iterator Array::begin()
		*
		* \brief	Returns an iterator at the beginning of the array.
		*
		* \return	The iterator.
		*/

		iterator begin() { return m_values; }

		/**
		 * \fn	const_iterator Array::begin() const
		 *
		 * \brief	Returns an iterator at the beginning of the array.
		 *
		 * \return	The iterator.
		 */

		const_iterator begin() const { return m_values; }

		/**
		 * \fn	iterator Array::end()
		 *
		 * \brief	Returns an iterator at the end of the array.
		 *
		 * \return	The iterator.
		 */

		iterator end() { return m_values+m_size; }

		/**
		 * \fn	const_iterator Array::end() const
		 *
		 * \brief	Returns an iterator at the end of the array.
		 *
		 * \return	The iterator.
		 */

		const_iterator end() const { return m_values+m_size; }

		/**
		 * \fn	operator std::vector<T>()const
		 *
		 * \brief	Conversion operator to standard vector.
		 *
		 * \tparam	T	Type of the values.
		 */

		operator std::vector<T>()const
		{
			std::vector<T> ret(m_size);
			for(size_t i = 0; i < m_size; ++i) ret[i] = m_values[i];
			return ret;
		}

	private:
	
		void swap(self_t& other)
		{
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
			std::swap(m_values, other.m_values);
		}

		virtual void destroy() 
		{
			delete[] m_values;
		}

	private:

		///< The size
		size_t m_size;
		///< The capacity
		size_t m_capacity;
		///< The values
		T* m_values;
	};


}
