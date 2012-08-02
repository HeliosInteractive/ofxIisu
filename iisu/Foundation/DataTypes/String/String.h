#pragma once
/*! \file String.h
\brief Header file defining the iisu's SDK string type.
*/
#include <string.h>
#include <Platform/SkPlatform.h>
#include <ostream>
#include <istream>
#include <string>

namespace SK
{

	/**
	 * \class	String
	 *
	 * \brief	Basic String implementation
	 *	 
	 */

	class IISUSDK_API String
	{
	public:

		/**
		 * \fn	String::String();
		 *
		 * \brief	Default constructor.
		 *  
		 */

		String();

		/**
		 * \fn	String::String(const char *str);
		 *
		 * \brief	Constructor from character string.
		 *
		 * \param	str	The character string.
		 */

		String(const char *str);

		/**
		 * \fn	explicit String::String(uint32_t n);
		 *
		 * \brief	Constructor with size.
		 *
		 * \param	n	The size.
		 */

		explicit String(uint32_t n);

		/**
		 * \fn	String::String(const String &s);
		 *
		 * \brief	Copy constructor.
		 *
		 * \param	s	The string.
		 */

		String(const String &s);

		/**
		 * \fn	String& String::operator= (const String &s);
		 *
		 * \brief	Assignment operator.
		 *
		 * \param	s	The sstring.
		 *
		 * \return	A shallow copy of this object.
		 */

		String& operator= (const String &s);

		/**
		 * \fn	String::~String();
		 *
		 * \brief	Destructor.
		 */

		~String();

		/**
		 * \fn	void String::resize(uint32_t n);
		 *
		 * \brief	Resizes (keep content).
		 *
		 * \param	n	The new size.
		 */

		void resize(uint32_t n);

	public:

		/**
		 * \fn	char * String::ptr();
		 *
		 * \brief	Gets the data pointer .
		 *
		 * \return	the pointer to the internal data.
		 */

		char * ptr();

		/**
		 * \fn	const char * String::ptr() const;
		 *
		 * \brief	Gets the data pointer .
		 *
		 * \return	the pointer to the internal data.
		 */

		const char * ptr() const;

		/**
		 * \fn	void String::copyFrom(const char * ptr, int32_t n);
		 *
		 * \brief	Copies n chars from a given char string.
		 *
		 * \param	ptr	The pointer to the data to be copied.
		 * \param	n  	The number of chars to be copied.
		 */

		void copyFrom(const char * ptr, int32_t n);

		/**
		 * \fn	uint32_t String::size() const;
		 *
		 * \brief	Gets the size.
		 *
		 * \return	the size.
		 */

		uint32_t size() const;

		/**
		 * \fn	char& String::operator[] (uint32_t index);
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	index	index of the character.
		 *
		 * \return	The character.
		 */

		char& operator[] (uint32_t index);

		/**
		 * \fn	const char& String::operator[] (uint32_t index) const;
		 *
		 * \brief	Array indexer operator.
		 *
		 * \param	index	index of the character.
		 *
		 * \return	The character.
		 */
		const char& operator[] (uint32_t index) const;

		/**
		 * \fn	friend IISUSDK_API String String::operator+(const SK::String& lhs, const String& rhs);
		 *
		 * \brief	Addition operator.
		 *
		 * \param	lhs	The first string.
		 * \param	rhs	The second string.
		 *
		 * \return	The concatenation of both strings.
		 */

		friend IISUSDK_API String operator+(const SK::String& lhs, const String& rhs);

		/**
		 * \fn	friend IISUSDK_API String String::operator+(const SK::String& lhs, const char* rhs);
		 *
		 * \brief	Addition operator.
		 *
		 * \param	lhs	The first string.
		 * \param	rhs	The second string.
		 *
		 * \return	The concatenation of both strings.
		 */

		friend IISUSDK_API String operator+(const SK::String& lhs, const char* rhs);

		/**
		 * \fn	friend IISUSDK_API String String::operator+(const char* lhs, const String& rhs);
		 *
		 * \brief	Addition operator.
		 *
		 * \param	lhs	The first string.
		 * \param	rhs	The second string.
		 *
		 * \return	The concatenation of both strings.
		 */

		friend IISUSDK_API String operator+(const char* lhs, const String& rhs);

		/**
		 * \fn	SK::String& String::operator+=(const SK::String& str);
		 *
		 * \brief	Addition assignment operator.
		 *
		 * \param	str	The string.
		 *
		 * \return	The result of the operation.
		 */

		SK::String& operator+=(const SK::String& str);

		/**
		 * \fn	SK::String& String::operator+=(const char* str);
		 *
		 * \brief	Addition assignment operator.
		 *
		 * \param	str	The string.
		 *
		 * \return	The result of the operation.
		 */

		SK::String& operator+=(const char* str);

	public:

		/**
		 * \fn	friend bool String::operator==(const SK::String& lhs, const SK::String& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the strings are considered equivalent.
		 */

		friend bool operator==(const SK::String& lhs, const SK::String& rhs)
		{
			return (strcmp(lhs.ptr(), rhs.ptr()) == 0);
		}

		/**
		 * \fn	friend bool String::operator==(const char* lhs, const SK::String& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */

		friend bool operator==(const char* lhs, const SK::String& rhs)
		{
			return (strcmp(lhs, rhs.ptr()) == 0);
		}

		/**
		 * \fn	friend bool String::operator==(const SK::String& lhs, const char*& rhs)
		 *
		 * \brief	Equality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */

		friend bool operator==(const SK::String& lhs, const char*& rhs)
		{
			return (strcmp(lhs.ptr(), rhs) == 0);
		}

		/**
		 * \fn	friend bool String::operator!=(const SK::String& lhs, const SK::String& rhs)
		 *
		 * \brief	Inequality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */

		friend bool operator!=(const SK::String& lhs, const SK::String& rhs)
		{
			return !(lhs == rhs);
		}

		/**
		 * \fn	friend bool String::operator!=(const char* lhs, const SK::String& rhs)
		 *
		 * \brief	Inequality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */

		friend bool operator!=(const char* lhs, const SK::String& rhs)
		{
			return !(lhs == rhs);
		}

		/**
		 * \fn	friend bool String::operator!=(const SK::String& lhs, const char*& rhs)
		 *
		 * \brief	Inequality operator.
		 *
		 * \param	lhs	The first instance to compare.
		 * \param	rhs	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */

		friend bool operator!=(const SK::String& lhs, const char*& rhs)	
		{
			return !(lhs == rhs);
		}

		/**
		 * \fn	friend std::ostream& String::operator<<(std::ostream& out, const SK::String& str)
		 *
		 * \brief	Output stream operator.
		 *
		 * \param [in,out]	out	The output stream.
		 * \param	str		   	The string.
		 *
		 * \return	The updated output stream.
		 */

		friend std::ostream& operator<<(std::ostream& out, const SK::String& str)
		{
			out<<str.ptr();
			return out;
		}

		/**
		 * \fn	friend std::istream& String::operator>>(std::istream& in, SK::String& str)
		 *
		 * \brief	Input stream operator.
		 *
		 * \param [in,out]	out	The input stream.
		 * \param [out]     str		   	The string.
		 *
		 * \return	The input stream.
		 */

		friend std::istream& operator>>(std::istream& in, SK::String& str)
		{
			std::string tmp;
			in >> tmp;
			str = tmp.c_str();
			return in;
		}

	private:
		void swap(SK::String& str);

	private:
		uint32_t m_size;
		char* m_ptr;
	};


}
