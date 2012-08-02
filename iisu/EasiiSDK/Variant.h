/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/02/29
//  Module Name       : Easii
//  Description       : A type safe variant.
//
// COPYRIGHT AND CONFIDENTIALITY NOTICE - SOFTKINETIC CONFIDENTIAL
// INFORMATION All rights reserved to SOFTKINETIC SOFTWARE SA (a
// company incorporated and existing under the laws of Belgium, with
// its principal place of business at Boulevard de la Plainelaan 15,
// 1050 Brussels (Belgium), registered with the Crossroads bank for
// enterprises under company number 0890 705 864 - "Softkinetic
// Software")
//
// The source code of the SoftKinetic iisu SDK is proprietary and
// confidential information of Softkinetic Software SA
// For any question about terms and conditions, please contact: info@softkinetic.com
// Copyright (c) 2002-2012 Softkinetic Software SA
/****************************************************************************************/

#pragma once

#include <Foundation/Services/Types/RawData.h>
#include <cassert>

namespace SK {
namespace Easii {
// \cond IGNORE_DOXYGEN
namespace Details {
struct ValueHolder
{
	virtual ~ValueHolder()
	{ }
	virtual ValueHolder *clone() const = 0;
	virtual const RawData &rawData() const = 0;
};

template <
	class T
	>
struct Holder : public ValueHolder
{
	Holder(const T &value)
		: m_value(value)
		, m_rawData(m_value)
	{ }

	virtual ~Holder()
	{ }

	virtual ValueHolder *clone() const
	{ return new Holder<T>(m_value); }

	virtual const RawData &rawData() const
	{ return m_rawData; }

	T m_value;
	RawData m_rawData;

};

struct NoneHolder : public ValueHolder
{
	NoneHolder()
	{ }

	virtual ~NoneHolder()
	{ }

	virtual ValueHolder *clone() const
	{ return new NoneHolder; }

	virtual const RawData &rawData() const
	{
		return m_rawData;
	}

	RawData m_rawData;

};
} // namespace Details
// \endcond

/**
 * \class Variant
 * \brief A type-safe variant encapsulating iisu data types.
 *
 * A \c Variant object can be constructed from any type supported by
 * iisu's type system (including primitive types). If an object of any
 * other type is used, the program will fail to link.
 */
class Variant
{
public:

	/**
	 * \brief Default constructor.
	 *
	 * \post !isValid()
	 */
	Variant();

	/**
	 * \brief Constructs a variant by value.
	 *
	 * \param value The variant value.
	 * \post (isValid() && is<T>())
	 */
	template <
		class T
		>
	Variant(const T &value)
		: m_valueHolder(new Details::Holder<T>(value))
	{ }

	/**
	 * \brief \c char array constructor.
	 *
	 * \param value A string (internally an \c SK::String).
	 * \post (isValid() && isString())
	 */
	Variant(const char *value);

	/**
	 * \brief Copy constructor.
	 *
	 * \param other The other variant object.
	 * \post (isValid() == other.isValid())
	 */
	Variant(const Variant &other);

	/**
	 * \brief Assignment operator.
	 *
	 * \param other The other variant ovject.
	 * \post (isValid() == other.isValid())
	 */
	Variant &operator = (const Variant &other);

	/**
	 * \brief Destructor.
	 */
	~Variant();

	/**
	 * \brief swaps two variant objects.
	 *
	 * \param other The other variant object.
	 */
	void swap(Variant &other);

	/**
	 * \brief Tests if this variant contains a valid value.
	 * \return \c true if the variant has a valid value, \c false
	 *         otherwise.
	 */
	bool isValid() const;

	/**
	 * \brief Gets the type info.
	 * \return A const reference to the underlying value's TypeInfo.
	 */
	const SK::TypeInfo &getType() const;

	/**
	 * \brief Tests if this variant is of type \c T.
	 * \return \c true if the variant value is an object of type \c T,
	 *         \c false otherwise.
	 */
	template <
		class T
		>
	bool is() const
	{
		return getType() == SK::Type<T>::INFO;
	}

	/**
	 * \brief Gets the variant's value.
	 *
	 * \return The value of the variant.
	 * \pre (isValid() && is<T>())
	 */
	template <
		class T
		>
	const T &get() const
	{
		assert(is<T>());
		return m_valueHolder->rawData().getRef<T>();
	}

private:

	// \cond IGNORE_DOXYGEN
	Details::ValueHolder *m_valueHolder;
	// \endcond
};
} // namespace Easii
} // namespace SK
