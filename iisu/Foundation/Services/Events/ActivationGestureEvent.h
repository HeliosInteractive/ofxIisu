#pragma once

#include <Foundation/Services/Events/Event.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Enumeration/Enum.h>
#include "EventEnum.h"

namespace SK
{
	/**
	 * \class	ActivationGestureEvent
	 *
	 * \brief	Activation gesture event. 
	 * 			
	 * This event is thrown when an Activation Gesture occurs
	 */

	class ActivationGestureEvent : public Event<void (const SK::Enum&, const SK::Vector3&)>
	{
	private:
		typedef Event<void (const SK::Enum&, const SK::Vector3&)> base_t;

	public:
		ActivationGestureEvent(const SK::String& name, const SK::Enum& type, const SK::Vector3& position):base_t(name, type, position){}

	public:
		/**
		 * \fn	const SK::Enum& ActivationGestureEvent::getType()const
		 *
		 * \brief	Gets the type of Activation Gesture of this event.
		 *
		 * \return	The type of the activation gesture, this SK::Enum is a SK::ActivationGestureEnum::Type.
		 */
		const SK::Enum& getType()const {return m_p1;}

		/**
		 * \fn	const SK::Vector3& ActivationGestureEvent::getPosition()const
		 *
		 * \brief	Gets the position of the activation gesture.
		 *
		 * \return	The position.
		 */
		const SK::Vector3& getPosition()const {return m_p2;}
	};
}
