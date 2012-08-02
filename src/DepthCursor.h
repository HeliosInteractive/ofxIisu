#pragma once

#include "ofMain.h" 
class DepthCursor 
{
	public :
		DepthCursor()
		{
			bHoverFlag = false ; 
			hoverDelay = 1.75f ; 
			interactionStart = -2 ; 
			interactionRatio = 0.0f ; 
			color = ofColor ( 255 , 255 , 255 ) ; 
			highlightColor = ofColor ( 255 , 105 , 180 ) ; 

			ofAddListener ( IisuEvents::Instance()->CURSOR_HOVER_START , this , &DepthCursor::cursorHoverStartHandler ) ; 
			ofAddListener ( IisuEvents::Instance()->CURSOR_HOVER_FINISHED , this , &DepthCursor::cursorHoverFinishedHandler ) ; 
			ofAddListener ( IisuEvents::Instance()->CURSOR_HOVER_INTERRUPTED , this , &DepthCursor::cursorHoverInterruptedHandler ) ; 

		} 

		ofVec2f position ; 

		float hoverDelay ; 

		float interactionStart ; 
		float interactionRatio ;			//Calculates the normalized interpolation for the hover state
		bool bHoverFlag ; 

		ofColor color ; 
		ofColor highlightColor ;

		int lastInputHex ; 


		void cursorHoverStartHandler ( const void * sender , IisuEventArgs &args )
		{
			hoverDelay = args.holdDelay ; 
			startHover ( args.inputHex ) ; 
		}

		void cursorHoverFinishedHandler ( const void * sender , int &hexColor )
		{
			cancelHover() ; 
			cout << "Hover was interrupted! " << endl ; 
			//Hover lost sound effect
		}

		void cursorHoverInterruptedHandler ( const void * sender , int &hexColor ) 
		{

			cancelHover() ;
		}

	

		void update( ) 
		{
			if ( interactionStart > 0 )
			{
				interactionRatio = ( ofGetElapsedTimef() - interactionStart ) / hoverDelay ; 
			}

			if ( interactionRatio >= 1.0f ) 
			{
				bHoverFlag = true ; 
				interactionRatio = 1.0f ; 
			}


		}

		void draw ( ) 
		{
			glDisable ( GL_DEPTH_TEST ) ; 
			ofSetColor ( color ) ; 
			ofCircle ( position.x , position.y , 25.0f ) ; 
			ofSetColor ( highlightColor ) ; 
			ofCircle ( position.x , position.y , 25.0f * abs(interactionRatio) ) ; 
			ofSetColor ( 255 , 255 , 255 ) ; 
			ofDrawBitmapString ( ofToString( interactionRatio ) , position.x , position.y + 55 ) ; 
		}

		void startHover ( int hexColor ) 
		{
			if ( hexColor == lastInputHex ) 
				return ; 

			lastInputHex = hexColor ; 
			interactionStart = ofGetElapsedTimef() ; 
		}

		void cancelHover ( ) 
		{
			if ( interactionStart > 0 ) 
			{
				//cout << "cancel hover! " << endl ; 
				//highlightColor = ofColor ( ofRandom ( 255 ) , ofRandom ( 255 ) , ofRandom ( 255 ) ) ; 
				interactionStart = -2 ; 
				bHoverFlag = false ; 
				interactionRatio = 0.0f  ; 
				lastInputHex = 0x000000 ; 
			}
		}

		bool hitTest ( ofRectangle bounds ) 
		{
			if ( position.x > bounds.x &&
				 position.x < bounds.width + bounds.x &&
				 position.y > bounds.y &&
				 position.y < bounds.y + bounds.height ) 
			{
				return true ; 
			}
			else
				return false ; 
		}

};