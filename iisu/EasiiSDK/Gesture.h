/***************************************************************************************/
//  SoftKinetic iisu SDK
//  Project Name      : iisu SDK
//  Revision          : 3.0.2
//  Date              : 2012/01/31
//  Module Name       : Easii
//  Description       : Encapsulates a UI gesture.
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
 * \class Gesture Gesture.h EasiiSDK/Iisu.h
 * \brief Simple object that encapsulates a user, hand or UI gesture.
 */
class Gesture
{

public:

    /**
     * \enum Type
     * \brief Identifies different types of UI gesture.
     */
	enum Type
	{
		UNKNOWN,   /*!< Unknown gesture. */
		CIRCLE,    /*!< Indicates a circle gesture. */
		WAVE,      /*!< Indicates a wave gesture. */
		CLICK,     /*!< Indicates a click gesture. */
		SWIPE,     /*!< Indicates a swipe gesture. */
		NUMBER,    /*!< Indicates a number gesture. */
	};

	/**
	 * \brief Default constructor.
	 */
	Gesture()
		: m_type(UNKNOWN)
		, m_position(SK::Vector3::ZERO)
	{
	}

	/**
	 * \brief Constructor.
	 *
	 * \param type The gesture type.
	 * \param position The position.
	 */
	Gesture(Type type, const SK::Vector3 &position)
		: m_type(type)
		, m_position(position)
	{
	}

	/**
	 * \brief Gets the type of gesture that was performed.
	 *
	 * Currently, this is only limited to UI gestures.
	 *
	 * \return The gesture type (CIRCLE, WAVE, CLICK, SWIPE, NUMBER).
	 */
	Type getType() const
	{
		return m_type;
	}

	/**
	 * \brief Gets the position at which the gesture was performed.
	 *
	 * \return The position world coordinates.
	 */
	SK::Vector3 getPosition() const
	{
		return m_position;
	}

private:

	Type m_type;
	SK::Vector3 m_position;

};
} // namespace Easii
} // namespace SK
