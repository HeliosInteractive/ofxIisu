#pragma once

#include <Foundation/Services/Events/Event.h>
#include "EventEnum.h"

namespace SK
{
	/**
	 * \class	DataFrameEvent
	 *
	 * \brief	Data frame event. Notifies that there is a new frame available.
	 */

	class DataFrameEvent : public SK::Event<void (uint32_t)>
	{
	private:
		typedef Event<void (uint32_t)> base_t;

	public:
		DataFrameEvent(const SK::String& name, uint32_t frameID):base_t(name, frameID){}

	public:

		/**
		 * \fn	uint32_t DataFrameEvent::getFrameID() const
		 *
		 * \brief	Gets the frame identifier.
		 *
		 * \return	The frame identifier.
		 */

		uint32_t getFrameID() const{return m_p1;}
	};

	/**
	 * \class	StatusEvent
	 *
	 * \brief	Status event. Notifies that the device changed status
	 */

	class StatusEvent : public Event<void (const SK::Enum&)>
	{
	private:
		typedef Event<void (const SK::Enum&)> base_t;

	public:
		StatusEvent(const SK::String& name, const SK::Enum& result):base_t(name, result){}

	public:

		/**
		 * \fn	SK::DeviceStatus::Status StatusEvent::getDeviceStatus() const
		 *
		 * \brief	Gets the current device status.
		 *
		 * \return	The device status.
		 */

		SK::DeviceStatus::Status getDeviceStatus() const{return (SK::DeviceStatus::Status)m_p1.value;}
	};


	class UserDataListUpdatedEvent : public Event<void ()>
	{
	private:
		typedef Event<void ()> base_t;

	public:
		UserDataListUpdatedEvent(const SK::String& name):base_t(name){}
	};

}
