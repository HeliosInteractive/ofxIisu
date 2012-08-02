#pragma once

#include <Foundation/Services/Events/Event.h>
#include "EventEnum.h"

namespace SK
{
	/**
	 * \class	CalibrationResultEvent
	 *
	 * \brief	Calibration result event. Specifies a calibration command has ended
	 */

	class CalibrationResultEvent : public Event<void (const SK::Enum&)>
	{
	private:
		typedef Event<void (const SK::Enum&)> base_t;

	public:
		CalibrationResultEvent(const SK::String& name, const SK::Enum& result):base_t(name, result){}

		/**
		 * \fn	const SK::Enum& CalibrationResultEvent::getResult()const
		 *
		 * \brief	Gets the result of the calibration.
		 *
		 * \return	The result, this SK::Enum is a SK::CalibrationResultEnum::Type.
		 */

		const SK::Enum& getResult()const {return m_p1;}
	};


}
