#pragma once

namespace SK {

	namespace SideEnum
	{
		/**
		 * \enum	Type
		 *
		 * \brief	Specifies the side of a part of the body
		 */

		enum Type
		{
			UNKNOWN = 0,
			RIGHT = 1,
			LEFT = 2
		};
	}


	namespace FingerEnum
	{
		/**
		 * \enum	Type
		 *
		 * \brief	Enumerates the different fingers
		 */

		enum Type
		{
			UNKNOWN  = 0,
			THUMB    = 1,
			INDEX    = 2,
			MIDDLE   = 4,
			RING     = 8,
			PINKY    = 16
		};
	};

	namespace DirectionEnum
	{
		/**
		* \enum	Type
		*
		* \brief	Enumerates the different movement directions
		*/

		enum Type		// directions when facing camera
		{
			UNKNOWN,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			TYPECOUNT
		};
	}

} // namespace SK