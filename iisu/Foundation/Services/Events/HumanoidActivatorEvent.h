#pragma once

#include <Foundation/Services/Events/Event.h>

namespace SK
{
	/**
	 * \class	UserActivatedEvent
	 *
	 * \brief	Notifies that a user has been activated 
	 */

	class UserActivatedEvent : public Event<void (int8_t)>
	{
	private:
		typedef Event<void (int8_t)> base_t;

	public:
		UserActivatedEvent(const SK::String& name, int8_t humanoidID):base_t(name, humanoidID){}

	public:

		/**
		 * \fn	int8_t UserActivatedEvent::getHumanoidID()const
		 *
		 * \brief	Gets the humanoid identifier.
		 *
		 * \return	The humanoid identifier.
		 */

		int8_t getHumanoidID()const {return m_p1;}
	};

	/**
	 * \class	UserDeactivatedEvent
	 *
	 * \brief	Notifies a user is no longer activated. 
	 */

	class UserDeactivatedEvent : public Event<void (int8_t)>
	{
	private:
		typedef Event<void (int8_t)> base_t;

	public:
		UserDeactivatedEvent(const SK::String& name, int8_t humanoidID):base_t(name, humanoidID){}

	public:

		/**
		 * \fn	int8_t UserDeactivatedEvent::getHumanoidID()const
		 *
		 * \brief	Gets the humanoid identifier.
		 *
		 * \return	The humanoid identifier.
		 */

		int8_t getHumanoidID()const {return m_p1;}
	};

	/**
	 * \class	UserTransferedEvent
	 *
	 * \brief	Specifies that a new user has been associated to an active user. 
	 */

	class UserTransferedEvent : public Event<void (int8_t)>
	{
	private:
		typedef Event<void (int8_t)> base_t;

	public:
		UserTransferedEvent(const SK::String& name, int8_t humanoidID):base_t(name, humanoidID){}

	public:

		/**
		 * \fn	int8_t UserTransferedEvent::getHumanoidID()const
		 *
		 * \brief	Gets the humanoid identifier.
		 *
		 * \return	The humanoid identifier.
		 */

		int8_t getHumanoidID()const {return m_p1;}
	};

}
