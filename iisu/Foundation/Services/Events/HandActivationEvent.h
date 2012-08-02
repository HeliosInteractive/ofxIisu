#pragma once

#include <Foundation/Services/Events/Event.h>

namespace SK
{
	/**
	 * \class	HandActivatedEvent
	 *
	 * \brief	Notifies that a hand has been activated 
	 */

	class HandActivatedEvent : public Event<void (int32_t)>
	{
	private:
		typedef Event<void (int32_t)> base_t;

	public:
		HandActivatedEvent(const SK::String& name, int32_t handID):base_t(name, handID){}

	public:

		/**
		 * \fn	int32_t HandActivatedEvent::getHandID()const
		 *
		 * \brief	Gets the hand identifier.
		 *
		 * \return	The hand identifier.
		 */

		int32_t getHandID()const {return m_p1;}
	};

	/**
	 * \class	HandDeactivatedEvent
	 *
	 * \brief	Notifies a hand is no longer activated. 
	 */

	class HandDeactivatedEvent : public Event<void (int32_t)>
	{
	private:
		typedef Event<void (int32_t)> base_t;

	public:
		HandDeactivatedEvent(const SK::String& name, int32_t handID):base_t(name, handID){}

	public:

		/**
		 * \fn	int32_t HandDeactivatedEvent::getHandID()const
		 *
		 * \brief	Gets the hand identifier.
		 *
		 * \return	The hand identifier.
		 */

		int32_t getHandID()const {return m_p1;}
	};

	

}
