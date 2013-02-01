#pragma once

#include "DepthCursor.h"
#include "HandCursorFinger.h"

//#define MOUSE_DEBUG 1

class HandCursor : public DepthCursor
{
	public :
		HandCursor( ) { }

		void setup ( IisuServer * _iisu , int _cursorID , ofColor _color ) ; 
		void update ( ) ; 
		void draw ( ) ; 
		void debugDraw( ) ; 

		vector<HandCursorFinger*> fingers ;   
		ofVec3f fingerCentroid ; 
		
		float zFactor ; 

		int activeFingers ; 
		float palmWeighting ;


		bool bOpen ; 
		float openAmount ; 
		float handOpenThreshold ; 
};