#pragma once

#include "ofMain.h"
#include "IisuSkeleton.h"

/* Doing some things with multitouch and I wanted to keep it seperate from the basic core skeleton */

class GestureSkeleton : public IisuSkeleton
{
	public :
		GestureSkeleton( ) { } 
		~GestureSkeleton( ) { } 

		virtual void setup ( ) ; 
		virtual void update ( ) ; 
		virtual void draw ( ) ; 
		virtual void debugDraw( ) ;  


		bool bMultiTouchActive ; 
		ofPoint startRightHand ; 
		ofPoint startLeftHand ; 
		float startAngle ; 
		float startDistance ; 
		ofPoint startCentroid ; 

		float gestureScale, gestureAngle ; 
		ofPoint gestureTranslate  ; 

		void calcGestureValues ( ) ; 

		float handAngle ;		//2D angle between right and left hands
		float handDistance ;	//3D distance between right and left hands
		ofPoint handTranslate ; //Translation from initial point

		bool bRaisedHand ;		//for detecting "hands up" and "hands down" gesture
		bool bClapped ;			//for "clapping" in and out gesture

		bool bSendHandsUp ; 
		bool bSendHandsDown ; 
		bool bSendClapIn ;
		bool bSendClapOut ; 

		float planeSize ;		//Debug size of the plane
		float zPlane ;			//Threshold for multitouch gestures
};