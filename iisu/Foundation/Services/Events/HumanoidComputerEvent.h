#pragma once

#include <Foundation/Services/Events/Event.h>

namespace SK
{
	/**
	 * \class	UserStartsMovingEvent
	 *
	 * \brief	Event notifying that a user has started moving. 
	 */

	class UserStartsMovingEvent : public Event<void (int8_t)>
	{
	private:
		typedef Event<void (int8_t)> base_t;

	public:
		UserStartsMovingEvent(const SK::String& name, int8_t humanoidID):base_t(name, humanoidID){}

	public:

		/**
		 * \fn	int8_t UserStartsMovingEvent::getHumanoidID()const
		 *
		 * \brief	Gets the humanoid identifier.
		 *
		 * \return	The humanoid identifier.
		 */

		int8_t getHumanoidID()const {return m_p1;}
	};


	/**
	 * \class	UserStopsMovingEvent
	 *
	 * \brief	Event notifying that a user has stopped moving. 
	 */

	class UserStopsMovingEvent : public Event<void (int8_t)>
	{
	private:
		typedef Event<void (int8_t)> base_t;

	public:
		UserStopsMovingEvent(const SK::String& name, int8_t humanoidID):base_t(name, humanoidID){}

	public:

		/**
		 * \fn	int8_t UserStopsMovingEvent::getHumanoidID()const
		 *
		 * \brief	Gets the humanoid identifier.
		 *
		 * \return	The humanoid identifier.
		 */

		int8_t getHumanoidID()const {return m_p1;}
	};

	/**
	 * \class	UsersStartTouchingEvent
	 *
	 * \brief	Notifies that two users are in contact 
	 */

	class UsersStartTouchingEvent : public Event<void (int8_t, int8_t)>
	{
	private:
		typedef Event<void (int8_t, int8_t)> base_t;

	public:
		UsersStartTouchingEvent(const SK::String& name, int8_t firstHumanoidID, int8_t secondHumanoidID):base_t(name, firstHumanoidID, secondHumanoidID){}

	public:

		/**
		 * \fn	int8_t UsersStartTouchingEvent::getFirstHumanoidID()const
		 *
		 * \brief	Gets the first humanoid identifier.
		 *
		 * \return	The first humanoid identifier.
		 */

		int8_t getFirstHumanoidID()const {return m_p1;}

		/**
		 * \fn	int8_t UsersStartTouchingEvent::getSecondHumanoidID()const
		 *
		 * \brief	Gets the second humanoid identifier.
		 *
		 * \return	The second humanoid identifier.
		 */

		int8_t getSecondHumanoidID()const {return m_p2;}
	};

	/**
	 * \class	UsersStopTouchingEvent
	 *
	 * \brief	Users stop touching event. 
	 */

	class UsersStopTouchingEvent : public Event<void (int8_t, int8_t)>
	{
	private:
		typedef Event<void (int8_t, int8_t)> base_t;

	public:
		UsersStopTouchingEvent(const SK::String& name, int8_t firstHumanoidID, int8_t secondHumanoidID):base_t(name, firstHumanoidID, secondHumanoidID){}

	public:

		/**
		 * \fn	int8_t UsersStopTouchingEvent::getFirstHumanoidID()const
		 *
		 * \brief	Gets the first humanoid identifier.
		 *
		 * \return	The first humanoid identifier.
		 */

		int8_t getFirstHumanoidID()const {return m_p1;}

		/**
		 * \fn	int8_t UsersStopTouchingEvent::getSecondHumanoidID()const
		 *
		 * \brief	Gets the second humanoid identifier.
		 *
		 * \return	The second humanoid identifier.
		 */

		int8_t getSecondHumanoidID()const {return m_p2;}
	};
}
