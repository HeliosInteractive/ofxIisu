/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : A simple buffer.
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

#include <Foundation/DataTypes/Array/Array.h>

namespace SK {
namespace Easii {
namespace Utils {
/**
 * \brief A double buffered array.
 *
 * \code
 * \endcode
 *
 */
template <typename T>
class BufferedVector
{
public:

	/**
	 * \brief Default constructor.
	 */
	BufferedVector()
	{
	}

	/**
	 * \brief Destructor.
	 */
	~BufferedVector()
	{
	}

	/**
	 * \brief Pushes an element onto the buffer.
	 * \param value The value.
	 */
	void pushBack(const T &value)
	{
		m_writeArray.pushBack(value);
	}

	/**
	 * \brief Flips the two buffers.
	 */
	void flip()
	{
		m_readArray = m_writeArray;
		m_writeArray.clear();
	}

	/**
	 * \brief Gets the read buffer array.
	 * \return The read buffer array.
	 */
	const SK::Array<T> &getReadArray() const
	{
		return m_readArray;
	}

private:

	SK::Array<T> m_readArray;
	SK::Array<T> m_writeArray;

};
} // namespace Utils
} // namespace Easii
} // namespace SK
