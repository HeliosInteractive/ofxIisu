#pragma once

#include "ofMain.h"
#include "IisuEvents.h" 
#include "Events.h"
#include "ofxIisu.h"
#include "HeliosDebug.h" 
#include "InstructionsScreen.h"

class InteractionManager
{

	public : 

		InteractionManager ( )
		{
			lastStatus = -4 ; 
			user.bActive = false ; 
			idleTime = -2 ; 
			idleDelay = 60.0f ;		//second delay for screensaver to come on
			bMouseDebug = true ; 
			instructionsNoCursor = false;
			cursorExists = false;
		} 

		InstructionsScreen instructions ; 
		int lastStatus ; 
		IisuServer * iisu ; 
		

//	float cursorDamping ; 
//		float inactiveDamping ; 
//		float interactiveDamping ; 

		struct User
		{
			float startInteraction ; 
			float endInteraction ;
			float interactionTime ;
			bool bActive ; 
		};

		bool bMouseDebug ; 

		float idleTime ; 
		float idleDelay ;
		
		bool instructionsNoCursor;
		bool cursorExists;
		ofSoundPlayer cursorFound ; 

		static InteractionManager* Instance()
        {
            static InteractionManager inst ; 
            return &inst ; 
        }

		/*
		void changeDampingInteractiveHandler ( float &newDamping ) 
		{
			Tweenzor::add( &cursorDamping , cursorDamping,  interactiveDamping , 0.0f , 0.05f ) ; 
		}

		void changeDampingInactiveHandler ( float &newDamping )
		{
			Tweenzor::add( &cursorDamping , cursorDamping,  inactiveDamping , 0.0f , 0.05f ) ; 
		}*/

		User user ; 
		int currentMenuIndex ; 
		

		void setup ( ) 
		{
			user.startInteraction = -2 ; 
			user.endInteraction= -3 ; 
			lastStatus = -4 ; 
			user.bActive = false ; 
			idleTime = -2 ; 
			timeSinceInstructionStarted = -2;
			//idleDelay = 30.0f ;		//second delay for screensaver to come on
			bMouseDebug = true ;  
		
			//ofAddListener( IisuEvents::Instance()->CURSOR_DETECTED , this , &InteractionManager::cursorFoundHandler ) ; 
			//ofAddListener( IisuEvents::Instance()->CURSOR_LOST , this , &InteractionManager::cursorLostHandler ) ; 
			//ofAddListener( IisuEvents::Instance()->CURSOR_DESTROYED , this , &InteractionManager::cursorDestroyedHandler ) ; 
			currentMenuIndex = -78 ; 

			//Get our references for sending debug info to our on-screen console
			idleTimeDebugRef = HeliosDebug::Instance()->createTexRef() ; 
			menuIndexDebugRef = HeliosDebug::Instance()->createTexRef() ; 
			instructionsStartRef = HeliosDebug::Instance()->createTexRef() ; 
			cursorExistsRef = HeliosDebug::Instance()->createTexRef() ; 
			cursorFound.loadSound( "sounds/cursorFound.wav") ; 
		}

		
		int idleTimeDebugRef ; 
		int menuIndexDebugRef ; 
		int instructionsStartRef ; 
		int cursorExistsRef ; 

		void update ( int status ) 
		{
			float instanceIdleTime ; 
			string idleTimeLog = "idle not being tracked" ; 
			
			string currentMenuLog = "currentMenuIndex : " + ofToString( currentMenuIndex ) ; 
			string instructStartTimeLog = "instructionsStartTime : " + ofToString( timeSinceInstructionStarted ) ; 
			string cursorExisistLog = "does a cursor exist ? " + ofToString ( cursorExists ) ; 

			if ( idleTime > 0 ) 
			{
				instanceIdleTime = ofGetElapsedTimef() - idleTime ;
				idleTimeLog = "timeIdle: " + ofToString( instanceIdleTime ) ; 
			}

			HeliosDebug::Instance()->setTextAt( idleTimeDebugRef , idleTimeLog ) ; 
			//HeliosDebug::Instance()->setTextAt( activeTimeDebugRef, activeTimeLog ) ; 
			HeliosDebug::Instance()->setTextAt( menuIndexDebugRef , currentMenuLog ) ; 
			HeliosDebug::Instance()->setTextAt( instructionsStartRef , instructStartTimeLog ) ; 
			HeliosDebug::Instance()->setTextAt( cursorExistsRef , cursorExisistLog ) ; 
			
			//IF the user is active idle time will be -2 and we can ignore all these checks
			if ( idleTime > 0 ) 
			{
				//If we have reached the halfway IdleTimer instructions should appear on the screen
				if ( ofGetElapsedTimef() > ( idleTime + (idleDelay /2 ) ) ) 
				{
					//Do this check to prevent the instructions from constantly toggeling on
					if ( timeSinceInstructionStarted < 0 ) 
					{
						//screensaver should start
						cout << "instructions should be out" << endl ; 
						timeSinceInstructionStarted = ofGetElapsedTimef() ; 
						//Force the instructions to come on
						instructionsNoCursor = false ; 
						InteractionManager::Instance()->instructions.forceChange( 1 , 0.0f , currentMenuIndex ) ; 
					}
				}

				//We have reached the total Idle Delay
				if ( ofGetElapsedTimef() > ( idleTime + idleDelay ) ) 
				{
					//If we are NOT ON THE SCREENSAVER ALREADY
					if ( currentMenuIndex != 3 ) 
					{
						//transition out instructions 
						InteractionManager::Instance()->instructions.forceChange( 0 , 0.0f , 3 ) ; 
						//reset times
						timeSinceInstructionStarted = -2 ; 
						idleTime = -2 ; 

						//Initiate the screensaver
						idleScreensaverStart ( ) ;
						//total delay has been active need to move to screensaver
						cout << "is : " << idleTime + idleDelay << " > " << ofGetElapsedTimef() << endl ; 
						cout << "Screensaver should be happening" << endl ;
					}
					else
					{
						//We ARE ON THE SCREENSAVER , we should reset these idle set
						cout << "idled out while on screensaver , resetting" << endl ; 
						timeSinceInstructionStarted = -2 ; 
						idleTime = -2 ; 
					}
				}
			}
			lastStatus = status ; 
		}

		void resetToActiveState( ) 
		{
			idleTime = -2 ; 
			timeSinceInstructionStarted = -2 ; 
		}

		void idleScreensaverStart( ) 
		{
				idleTime = -2 ; 
				cout << "user interaction has idled out! " << endl ; 
				int status = 0 ; //( bInstructionsIdle == true ) ? 1 : 0 ; 
				ofNotifyEvent( IisuEvents::Instance()->IDLE_INSTRUCTIONS , status ) ; 
				//MenuOptionEventArgs args = MenuOptionEventArgs( "STEP FORWARD TO INTERACT" ,  3 ) ; 
				user.bActive = false ; 
			// 	ofNotifyEvent( Events::Instance()->MENU_OPTION_SELECTED , args , this ) ; 
		}

		void forceIdleStart( ) 
		{
			idleTime = ofGetElapsedTimef( ) ; 
		//	cursorExists = false;
		}
		
		void cursorFoundHandler ( int &args ) 
		{
			cursorFound.play() ; 
			cursorExists = true;
			resetToActiveState( ) ; 
			if ( user.bActive == false ) 
			{
				user.startInteraction = ofGetElapsedTimef( ) ; 
				user.bActive = true ; 

				//bInstructionsIdle = false ; 
			//	cout << "cursor initiated for the first time!" << endl ; 
			}
			else
			{
			//	cout << "cursor found while user was still active" << endl ; 
			}
		}

		void cursorLostHandler ( int &args ) 
		{	
			//cout << "cursor Lost ! " << endl ; 
			idleTime = ofGetElapsedTimef( ) ; 
			cursorExists = false;
		}

		void cursorDestroyedHandler ( int &args ) 
		{
			
			if ( user.bActive == true ) 
			{
				if ( cursorExists == true ) 
				{
					idleTime = ofGetElapsedTimef( ) ; 	
				}

				user.endInteraction = ofGetElapsedTimef( ) ; 
				user.interactionTime = user.endInteraction - user.startInteraction ; 

				idleTime = ofGetElapsedTimef( ) ; 
				user.startInteraction = -2 ;  
				cursorExists = false;
				user.bActive = false ; 
			}
			else
			{
				cout << "destroyed called, but not user is active! " << endl ; 
			}
			cursorExists = false ; 
		}

		enum POINTER_STATUS
		{
			POINTER_STATUS_NOT_DETECTED = 0,
			POINTER_STATUS_ACTIVE = 1,
			POINTER_STATUS_STILL = 2,
			POINTER_STATUS_OUT_OF_BOX = 3,

		};

		enum PAGE_IDS
		{
			WAYFINDER = 0 , 
			EVENTS = 1 , 
			MAIN_MENU = 2 , 
			SCREENSAVER = 3 
		};

		float timeSinceInstructionStarted;
		void setTimeSinceInstructions ( float _value ) 
		{
			timeSinceInstructionStarted = _value ; 
		} ;

			

	
};