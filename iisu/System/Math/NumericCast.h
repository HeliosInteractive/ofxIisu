#pragma once

#include <limits>


//! \cond NUMERIC_INFO

///< Provide a min and a max function for any numeric type. Those represent the smallest and largest number for that type.
template <typename Type_T, bool isInteger = std::numeric_limits<Type_T>::is_integer> struct numeric_info;

template <typename Type_T> 
struct numeric_info<Type_T, true>
{
	static Type_T min()
	{
		return std::numeric_limits<Type_T>::min();
	}
	static Type_T max()
	{
		return std::numeric_limits<Type_T>::max();
	}
};
template <typename Type_T> 
struct numeric_info<Type_T, false>
{
	static Type_T min()
	{
		return -std::numeric_limits<Type_T>::max();
	}
	static Type_T max()
	{
		return std::numeric_limits<Type_T>::max();
	}
};

//! \endcond
/**
 * \fn	bool is_in_range(const From_T& from)
 *
 * \brief	Query if 'from' is in range of the first template parameter limits.
 *
 * \param	from	Source for the test.
 *
 * \return	true if in range, false if not.
 */

template<typename To_T, typename From_T>
bool is_in_range(const From_T& from)
{
	return (from <= numeric_info<To_T>::max() && from >= numeric_info<To_T>::min());
}

/**
 * \fn	To_T numeric_cast(const From_T& from)
 *
 * \brief	Safe cast a numeric type into another numeric type.
 *
 * \param	from	Source for the cast.
 *
 * \return	the result after a static_cast of the parameter into a To_T type.
 * 			
 * 			This function basically is just a static_cast to convert from one numeric type to another. The only difference is in debug mode where this function will assert 
 * 			that the source of the conversion is in the range of the new type it is cast into. For instance, when casting a float into a int the float can be larger than the maximum 
 * 			representable int and if it is the case this function assert.
 */

template<typename To_T, typename From_T>
To_T numeric_cast(const From_T& from)
{
	assert(is_in_range<To_T>(from));

	return static_cast<To_T>(from);
}

