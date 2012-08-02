#pragma once

#include <Foundation/Services/Events/Event.h>
#include <Foundation/Services/Events/ActivationGestureEvent.h>

namespace SK
{
	/**
	 * \class	ControllerCreationEvent
	 *
	 * \brief	Notifies that a UI controller has been created. 
	 */

	class ControllerCreationEvent : public Event<void (int32_t, const SK::Enum&)>
	{
 	private:
		typedef Event<void (int32_t, const SK::Enum&)> base_t;

	public:
		ControllerCreationEvent(const SK::String& name, int32_t roiID, const SK::Enum& type):base_t(name, roiID, type){}

	public:

		/**
		 * \fn	int32_t ControllerCreationEvent::getRoiID()const
		 *
		 * \brief	Gets the roi identifier.
		 *
		 * \return	The roi identifier.
		 */

		int32_t getRoiID()const {return m_p1;}

		/**
		 * \fn	const SK::Enum& ControllerCreationEvent::getGestureType()const
		 *
		 * \brief	Gets the gesture type that triggered the creation of the controller.
		 *
		 * \return	The gesture type.
		 */

		const SK::Enum& getGestureType()const {return m_p2;}
	};

	/**
	 * \class	ControllerDestructionEvent
	 *
	 * \brief	Notifies the destruction of a UM controller
	 */

	class ControllerDestructionEvent : public Event<void (int32_t)>
	{
	private:
		typedef Event<void (int32_t)> base_t;

	public:
		ControllerDestructionEvent(const SK::String& name, int32_t roiID):base_t(name, roiID){}

	public:

		/**
		 * \fn	int32_t ControllerDestructionEvent::getRoiID()const
		 *
		 * \brief	Gets the roi identifier.
		 *
		 * \return	The roi identifier.
		 */

		int32_t getRoiID()const {return m_p1;}
	};
}
