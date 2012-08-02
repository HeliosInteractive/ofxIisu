#pragma once

#include <Foundation/Services/Events/Event.h>
namespace SK
{

	/**
	 * \class	GestureEvent
	 *
	 * \brief	Generic gesture event. 
	 */

	class GestureEvent : public Event<void (int32_t, const SK::Vector3&)>
	{
	private:
		typedef Event<void (int32_t, const SK::Vector3&)> base_t;

	public:
		GestureEvent(const SK::String& name, int32_t roiID, const SK::Vector3& position):base_t(name, roiID, position){}

	public:

		/**
		 * \fn	int32_t GestureEvent::getRoiID()const
		 *
		 * \brief	Gets the roi identifier.
		 *
		 * \return	The roi identifier.
		 */

		int32_t getRoiID()const {return m_p1;}

		/**
		 * \fn	const SK::Vector3& GestureEvent::getPosition()const
		 *
		 * \brief	Gets the position.
		 *
		 * \return	The 3D position of where then event happened.
		 */

		const SK::Vector3& getPosition()const {return m_p2;}
	};

	/**
	 * \class	CircleGestureEvent
	 *
	 * \brief	The Circle gesture event. 
	 */

	class CircleGestureEvent : public Event<void (int32_t, const SK::Vector3&, int32_t)> 
	{
	private:
		typedef Event<void (int32_t, const SK::Vector3&, int32_t)> base_t;

	public:
		CircleGestureEvent(const SK::String& name, int32_t roiID, const SK::Vector3& position, int32_t direction):base_t(name, roiID, position, direction){}

	public:

		/**
		 * \fn	int32_t CircleGestureEvent::getRoiID()const
		 *
		 * \brief	Gets the roi identifier.
		 *
		 * \return	The roi identifier.
		 */

		int32_t getRoiID()const {return m_p1;}

		/**
		 * \fn	const SK::Vector3& CircleGestureEvent::getPosition()const
		 *
		 * \brief	Gets the position.
		 *
		 * \return	The 3D position where the event happened.
		 */

		const SK::Vector3& getPosition()const {return m_p2;}

		/**
		 * \fn	int32_t CircleGestureEvent::getDirection()const
		 *
		 * \brief	Gets the direction of the event (+1/-1).
		 *
		 * \return	The direction.
		 */

		int32_t getDirection()const {return m_p3;}
	};

	/**
	 * \class	ClickGestureEvent
	 *
	 * \brief	The Click gesture event. 
	 */

	class ClickGestureEvent : public GestureEvent 
	{
	private:
		typedef GestureEvent base_t;

	public:
		ClickGestureEvent(const SK::String& name, int32_t roiID, const SK::Vector3& position):base_t(name, roiID, position){}
	};

	/**
	 * \class	WaveGestureEvent
	 *
	 * \brief	The Wave gesture event. 
	 */

	class WaveGestureEvent : public GestureEvent 
	{
	private:
		typedef GestureEvent base_t;

	public:
		WaveGestureEvent(const SK::String& name, int32_t roiID, const SK::Vector3& position):base_t(name, roiID, position){}
	};

	/**
	 * \class	SwipeGestureEvent
	 *
	 * \brief	The Swipe gesture event. 
	 */

	class SwipeGestureEvent : public Event<void (int32_t, const SK::Vector3&, int32_t)> 
	{
	private:
		typedef Event<void (int32_t, const SK::Vector3&, int32_t)> base_t;

	public:
		SwipeGestureEvent(const SK::String& name, int32_t roiID, const SK::Vector3& position, int32_t direction):base_t(name, roiID, position, direction){}
	
	public:

		/**
		 * \fn	int32_t SwipeGestureEvent::getRoiID()const
		 *
		 * \brief	Gets the roi identifier.
		 *
		 * \return	The roi identifier.
		 */

		int32_t getRoiID()const {return m_p1;}

		/**
		 * \fn	const SK::Vector3& SwipeGestureEvent::getPosition()const
		 *
		 * \brief	Gets the position.
		 *
		 * \return	The position.
		 */

		const SK::Vector3& getPosition()const {return m_p2;}

		/**
		 * \fn	int32_t SwipeGestureEvent::getDirection()const
		 *
		 * \brief	Gets the direction of the swipe (+1/-1).
		 *
		 * \return	The direction.
		 */

		int32_t getDirection()const {return m_p3;}
	};	

	/**
	 * \class	NumberGestureEvent
	 *
	 * \brief	The Number gesture event. The user has done a number-shaped gesture
	 */

	class NumberGestureEvent : public Event<void (int32_t, const SK::Vector3&, int32_t)> 
	{
	private:
		typedef Event<void (int32_t, const SK::Vector3&, int32_t)> base_t;

	public:
		NumberGestureEvent(const SK::String& name, int32_t roiID, const SK::Vector3& position, int32_t number):base_t(name, roiID, position, number){}

	public:

		/**
		 * \fn	int32_t NumberGestureEvent::getRoiID()const
		 *
		 * \brief	Gets the roi identifier.
		 *
		 * \return	The roi identifier.
		 */

		int32_t getRoiID()const {return m_p1;}

		/**
		 * \fn	const SK::Vector3& NumberGestureEvent::getPosition()const
		 *
		 * \brief	Gets the position.
		 *
		 * \return	The position.
		 */

		const SK::Vector3& getPosition()const {return m_p2;}

		/**
		 * \fn	int32_t NumberGestureEvent::getNumber()const
		 *
		 * \brief	Gets the number shaped by the user.
		 *
		 * \return	The number.
		 */

		int32_t getNumber()const {return m_p3;}
	};

}
