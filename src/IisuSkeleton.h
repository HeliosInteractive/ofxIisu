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

		virtual void setup ( ) ; 
		virtual void update ( ) ; 
		virtual void draw ( ) ; 
		virtual void debugDraw( ) ; 

		bool getIsTracked( ) { return bTracked ; } 
		bool bTracked ;			//If the skeleton is being tracked 
		bool bDebugRender ;		

		ofRectangle bounds ;
		
		ofPoint offset ; 
		ofPoint scale ; 
		ofVec3f centroid ; 
		bool bFlipX , bFlipY ; 
		bool bEqualScaling ; 
		vector<ofPoint> rawPositions ;		//RAW iisu positions ( y + Z are switched ) they are in meters from the world center 
											//the world center is wherever you calibrated your t-stance post in playzone setup
		vector<ofPoint> positions ;			//offset + scaled positions , y + z back to normal
		vector<float> jointSizes ;			
		vector<ofColor> jointColors ;
};