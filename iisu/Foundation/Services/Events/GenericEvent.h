#pragma once

#include <Foundation/Services/Events/Event.h>
#include <Foundation/DataTypes/Array/Array.h>
#include <Foundation/Services/Types/RawData.h>
#include <Foundation/Services/Types/FunctionTypeInfo.h>

namespace SK
{

	/**
	 * \class	GenericEvent
	 *
	 * \brief	A Generic class event. Allows to handle all events with a single callback
	 */

	class GenericEvent : public Event<void (const SK::String&, const SK::Array<SK::RawData>&, const SK::FunctionTypeInfo&)>
	{
	private:
		typedef Event<void (const SK::String&, const SK::Array<SK::RawData>&, const SK::FunctionTypeInfo&)> base_t;

	public:
		GenericEvent(const SK::String& name, const SK::String& eventName, const SK::Array<SK::RawData>& params, const SK::FunctionTypeInfo& functionTypeInfo):
		base_t(name, eventName, params, functionTypeInfo){}

		/**
		 * \fn	const SK::String& GenericEvent::getEventName()const
		 *
		 * \brief	Gets the event name.
		 *
		 * \return	The event name.
		 */

		const SK::String& getEventName()const {return m_p1;}

		/**
		 * \fn	const SK::Array<SK::RawData>& GenericEvent::getParameters()const
		 *
		 * \brief	Gets an array containng the event's parameters.
		 *
		 * \return	The parameter array.
		 */

		const SK::Array<SK::RawData>& getParameters()const {return m_p2;}

		/**
		 * \fn	const SK::FunctionTypeInfo& GenericEvent::getFunctionTypeInfo()const
		 *
		 * \brief	Gets the function type information of the event, allowing to get the information about every parameter
		 *
		 * \return	The function type information.
		 */

		const SK::FunctionTypeInfo& getFunctionTypeInfo()const {return m_p3;}
	};
}
