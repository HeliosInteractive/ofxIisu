#pragma once


/*
Written by Ben McChesney
Base


*/
// iisu
#include <SDK/iisuSDK.h>
#include "ofMain.h"
#include "IisuServer.h"
#include "IisuUtils.h"


class IisuSkeleton
{
	public : 

		IisuSkeleton ( ) { } 
		~IisuSkeleton ( ) { } 

		IisuServer * iisu ; 

		bool	m_userManagementEnabled;

		void setup ( ) ; 
		void update ( ) ; 
		void draw ( ) ; 
		void debugDraw( ) ; 

		
		bool bTracked ;			//If the skeleton is being tracked 
		bool bDebugRender ;		

		//ofRectangle bounds ;
		
		ofPoint offset ; 
		ofPoint scale ; 
		ofVec3f centroid ; 
		bool bFlipX , bFlipY ; 

		vector<ofPoint> rawPositions ;
		vector<ofPoint> positions ; 
		vector<float> jointSizes ; 
		vector<ofColor> jointColors ; 

		float handAngle ; 
		float handDistance ; 

		bool bRaisedHand ; 
		bool bClapped ; 

		bool bSendHandsUp ; 
		bool bSendHandsDown ; 
		bool bSendClapIn ;
		bool bSendClapOut ; 

		float zPlane ; 
		
};