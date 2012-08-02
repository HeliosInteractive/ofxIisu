#ifndef HandPosingGestureEvent_h__
#define HandPosingGestureEvent_h__

#pragma once

#include <Foundation/Services/Events/Event.h>

namespace SK
{

	class HandPosingGestureEvent : public Event<void (int32_t, int32_t, uint32_t)>
	{
	private:
		typedef Event<void (int32_t, int32_t, uint32_t)> base_t;

	public:
		HandPosingGestureEvent(const SK::String& name, int32_t handID1, int32_t handID2, uint32_t gestureID):base_t(name,  handID1, handID2, gestureID){}
		int32_t getFirstHandID() const {return m_p1;}
		int32_t getSecondHandID() const {return m_p2;}
		uint32_t getGestureTypeID() const {return m_p3;}

	};
}
#endif // HandPosingGestureEvent_h__+
