#pragma once
#include "Foundation/DataTypes/String/String.h"

namespace SK {

	namespace SkeletonEnum {

		/**
		 * \enum	KeyPoints
		 *
		 * \brief	Values that represent Skeleton KeyPoints. 
		 */

		enum KeyPoints
		{
			PELVIS, // 0.
			WAIST, // 1.
			COLLAR, // 2.
			NECK, // 3.
			HEAD, // 4.

			RIGHT_SHOULDER, // 5.
			RIGHT_ELBOW, // 6.
			RIGHT_WRIST, // 7.
			RIGHT_HAND, // 8.

			RIGHT_HIP, // 9.
			RIGHT_KNEE, // 10.
			RIGHT_ANKLE, // 11.
			RIGHT_FOOT, // 12.

			LEFT_SHOULDER, // 13.
			LEFT_ELBOW, // 14.
			LEFT_WRIST, // 15.
			LEFT_HAND, // 16.

			LEFT_HIP, // 17.
			LEFT_KNEE, // 18.
			LEFT_ANKLE, // 19.
			LEFT_FOOT, // 20.

			_COUNT // 21.
		} ;

		/**
		 * \name	KeyPointsLabels
		 *
		 * \brief	KeyPoints enum labels. 
		 */

		static const SK::String KeyPointsLabels[_COUNT] =
		{
			"Pelvis",
			"Waist",
			"Collar",
			"Neck",
			"Head",

			"RightShoulder",
			"RightElbow",
			"RightWrist",
			"RightHand",

			"RightHip",
			"RightKnee",
			"RightAnkle",
			"RightFoot",

			"LeftShoulder",
			"LeftElbow",
			"LeftWrist",
			"LeftHand",

			"LeftHip",
			"LeftKnee",
			"LeftAnkle",
			"LeftFoot"
		};

	} ;
} ;
