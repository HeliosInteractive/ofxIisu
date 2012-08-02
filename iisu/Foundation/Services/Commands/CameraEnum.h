#pragma once

namespace SK {

	namespace ImageTypeEnum
	{
		/**
		 * \enum	Type
		 *
		 * \brief	Specifies the various types images that can be fed to the command "SOURCE.SendData"
		 */

		enum Type
		{
			DEPTH = 0,
			COLOR = 1,
			CONFIDENCE = 2,
			IR = 3,
			MATCHING_COLOR = 4,


			IMAGE_TYPE_COUNT
		};
	}
}