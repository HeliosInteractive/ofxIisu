/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Defines the parameters of a bounding box in 3D
//                      space.
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

#include <Foundation/DataTypes/Geometry/Vector3.h>

namespace SK {
namespace Easii {
/**
 * \class BoundingBox BoundingBox.h EasiiSDK/Iisu.h
 * \brief A simple bounding box class.
 * The bounding box is a simple object allowing to represent the a
 * volume limited by two points (opposite min and max corners)
 */
class BoundingBox
{
public:
	/**
	 * \brief Constructor.
	 *
	 * \param min The minimum corner coordinates of the bounding box.
	 * \param max The maximum corner coordinates of the bounding box.
	 */
	BoundingBox(const SK::Vector3 &min, const SK::Vector3 &max);

	/**
	 * \brief Copy constructor.
	 *
	 * \param other The other BoundingBox object.
	 */
	BoundingBox(const BoundingBox &other);

	/**
	 * \brief Assignment operator.
	 *
	 * \param other The other BoundingBox object.
	 */
	BoundingBox &operator = (const BoundingBox &other);

	/**
	 * \brief Destructor.
	 */
	~BoundingBox();

	/**
	 * \brief Swaps this BoundingBox object with another.
	 *
	 * \param other The other BoundingBox to swap.
	 */
	void swap(BoundingBox &other);

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the minimum corner coordinates.
	 *
	 * \return The coordinates.
	 * \deprecated use getMinimum()
	 * \sa getMinimum()
	 */
	SK::Vector3 getMin() const;
	// \endcond

	/**
	 * \brief Gets the minimum corner coordinates.
	 *
	 * \return The coordinates.
	 * \sa getMaximum()
	 */
	SK::Vector3 getMinimum() const;

	// \cond IGNORE_DOXYGEN
	/**
	 * \brief Gets the maximum corner coordinates.
	 *
	 * \return The coordinates.
	 * \deprecated use getMaximum()
	 * \sa getMaximum()
	 */
	SK::Vector3 getMax() const;
	// \endcond

	/**
	 * \brief Gets the maximum corner coordinates.
	 *
	 * \return The coordinates.
	 * \sa getMinimum()
	 */
	SK::Vector3 getMaximum() const;

private:

	SK::Vector3 m_min;
	SK::Vector3 m_max;

};
} // namespace Easii
} // namespace SK
