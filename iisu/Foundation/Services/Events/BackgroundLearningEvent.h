#pragma once

#include <Foundation/Services/Events/Event.h>
#include "EventEnum.h"

namespace SK
{
	/**
	 * \class	CameraDeocclusionEvent
	 *
	 * \brief	This event is thrown when the camera get de-occluded.
	 */

	class CameraDeocclusionEvent : public Event<void ()>
	{
	private:
		typedef Event<void ()> base_t;

	public:
		CameraDeocclusionEvent(const SK::String& name):base_t(name){}
	};

	/**
	 * \class	CameraOcclusionEvent
	 *
	 * \brief	This event is thrown when the camera get occluded. 
	 */

	class CameraOcclusionEvent : public Event<void ()>
	{
	private:
		typedef Event<void ()> base_t;

	public:
		CameraOcclusionEvent(const SK::String& name):base_t(name){}
	};



	/**
	 * \class	BackgroundSnapshotResultEvent
	 *
	 * \brief	Event that is thrown when a Background Snapshot is taken. 
	 */

	class BackgroundSnapshotResultEvent : public Event<void (const SK::Enum&)>
	{
	private:
		typedef Event<void (const SK::Enum&)> base_t;

	public:
		BackgroundSnapshotResultEvent(const SK::String& name, const SK::Enum& result):base_t(name, result){}

		/**
		 * \fn	const SK::Enum& BackgroundSnapshotResultEvent::getResult()const
		 *
		 * \brief	Get the result of the Background Snapshot.
		 *
		 * \return	The result of the background snapshot, this SK::Enum is a SK::BackgroundSnapshotResultEnum::Type.
		 */

		const SK::Enum& getResult()const {return m_p1;}
	};


}
