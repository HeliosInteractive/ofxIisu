#pragma once

#include "ofMain.h"
#include "ofxIisu.h"
#include "DepthCursor.h"

//#define MOUSE_DEBUG 1

class HandCursor
{
	public :
		HandCursor( ) { } 

		struct Finger
		{
			int status ; 
			ofVec2f pt ; 
			float radius ; 
		};

		IisuServer * iisu ; 

		void setup ( ) ; 
		void update ( ) ; 
		void updateIisu ( ) ;
		void draw ( ) ; 
		void debugDraw( ) ; 

		vector<Finger*> fingers ;  
		ofVec3f palmPosition ; 
		ofVec3f fingerCentroid ; 
		
		float zFactor ; 

		int activeFingers ; 
		float palmWeighting ;

		bool bTracked ; 


		bool bOpen ; 
		float openAmount ; 
		float handOpenThreshold ; 
};