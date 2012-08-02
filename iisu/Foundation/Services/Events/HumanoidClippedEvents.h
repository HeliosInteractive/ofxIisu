#pragma once

#include <Foundation/Services/Events/Event.h>

namespace SK
{
	/**
	 * \class UserClippedByFrustumEvent
	 *
	 * \brief Event when user is too close to camera
	 */

	class UserClippedByFrustumEvent : public Event<void (int32_t, const SK::Enum&)>
	{
	private:
		typedef Event<void (int32_t, const SK::Enum&)> base_t;

	public:
		UserClippedByFrustumEvent(const SK::String& name, int32_t userID, const SK::Enum& location) : base_t(name, userID, location){}

	public:
		/**
		* \fn int32_t UserClippedByFrustumEvent::getUserID() const
		*
		* \brief Gets the user identifier
		*
		* \return The user identifier
		*/
		int32_t getUserID() const { return m_p1; }

		/**
		* \fn SK::Enum UserClippedByFrustumEvent::getLocation() const
		*
		* \brief Gets the general location of the cut
		*
		* \return The general location of where the cut happened, represented by an integer value: 0 = front, 1 = back, 2 = left, 3 = right
		*/
		SK::Enum getLocation() const { return m_p2; }
	};

	/**
	 * \class LowerBodyNotDetectedEvent
	 *
	 * \brief Event when the lower body is not detected (e.g. when
	 *        wearing dark trousers).
	 */

	class LowerBodyNotDetectedEvent : public Event<void (int32_t)>
	{
	private:
		typedef Event<void (int32_t)> base_t;

	public:
		LowerBodyNotDetectedEvent(const SK::String &name, int32_t userId)
			: base_t(name, userId)
		{
		}

		int32_t getUserID() const
		{
			return m_p1;
		}
	};

	/**
	 * \class UserNotClippedEvent
	 *
	 * \brief Event when the full humanoid form is detected again.
	 */

	class UserNotClippedEvent : public Event<void (int32_t)>
	{
	private:
		typedef Event<void (int32_t)> base_t;

	public:
		UserNotClippedEvent(const SK::String &name, int32_t userId)
			: base_t(name, userId)
		{
		}

		int32_t getUserID() const
		{
			return m_p1;
		}
	};
}
