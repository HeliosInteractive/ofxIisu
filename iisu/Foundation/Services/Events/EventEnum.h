#pragma once

namespace SK {

	namespace ActivationGestureEnum
	{
		/**
		 * \enum	Type
		 *
		 * \brief	Specifies the various types of activation gestures
		 */

		enum Type
		{
			WAVE = 0,			
			CIRCLE = 1,
			PUSH = 2,
			STILL_HAND = 3,
			ENTER_BOX = 4,

			NB_GESTURE_TYPE
		};
	}



	namespace BackgroundSnapshotResultEnum
	{
		/**
		 * \enum	Type
		 *
		 * \brief	Possible results for a background snapshot request. 
		 */

		enum Type
		{
			FAILED = 0,
			SUCCESS = 1
		};
	}

	namespace CalibrationResultEnum
	{
		/**
		 * \enum	Type
		 *
		 * \brief	Values that represents the possible result for a calibration event. 
		 */

		enum Type
		{
			FAILED = 0,
			SUCCEEDED_FLOOR_AND_T_STANCE_BASED,
			SUCCEEDED_FLOOR_BASED,
			SUCCEEDED_T_STANCE_BASED
		};	
	}


	namespace DeviceStatus
	{
		/**
		 * \enum	Status
		 *
		 * \brief	Possible bitfield for a Device status. 
		 */

		enum Status
		{
			INVALID = 0,
			INITIALIZED = 1, /*!< Get the initialization state of the device. */
			DATAVALID = 2, /*!< Get the data validity state of the device. */
			PLAYING = 4, /*!< Get the play execution state of the device. */
			FINISHED = 8, /*!< Get the device destruction state of the device. (Used for device destruction notification) */
			ERRORSTATE = 16 /*!< Get the error state of the device. */
		};
	}

			
}
