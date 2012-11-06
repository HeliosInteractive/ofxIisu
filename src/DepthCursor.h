#pragma once

#include "ofMain.h" 
#include "IisuServer.h"
#include "IisuEvents.h"
#include "ofxTweenzor.h" 

class DepthCursor 
{
	public :
		DepthCursor() {
			iisu = NULL ; 
		}
		
		void setup ( IisuServer * _iisu , int _cursorID , ofColor _color ) ;
		void update( ) ;
		void draw ( ) ;
		void debugDraw( ) ; 

		//Iisu cursor changes
		void cursorFoundHandler ( int &args ) ;
		void cursorLostHandler ( int &args ) ;
		void cursorDestroyedHandler ( int &args ) ; 
		
		bool bActive ; 
		int cursorID ;			//iisu ID
		int cursorStatus ;		//found, lost, out of bounds  // LOOK UP ENUM VALUES
		ofVec2f position ;		//Screen / Window Coordinates	
		ofColor color ;			

		IisuServer * iisu ; 
		

};