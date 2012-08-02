#pragma once

#include <Foundation/Services/Events/Event.h>
namespace SK
{
	/**
	 * \class	ErrorEvent
	 *
	 * \brief	The Error event.  
	 */

	class ErrorEvent : public Event<void (const SK::Error&, bool)>
	{
	private:
		typedef Event<void (const SK::Error&, bool)> base_t;

	public:
		ErrorEvent(const SK::String& name, const SK::Error& error, bool isFatal):base_t(name, error, isFatal){}

	public:

		/**
		 * \fn	const SK::Error& ErrorEvent::getError() const
		 *
		 * \brief	Gets the error reported by the event.
		 *
		 * \return	The error.
		 */

		const SK::Error& getError() const{return m_p1;}

		/**
		 * \fn	bool ErrorEvent::isFatal() const
		 *
		 * \brief	Query if the error is fatal and the application should quit gravefully.
		 *
		 * \return	true if fatal, false if not.
		 */

		bool isFatal() const{return m_p2;}
	};
}
