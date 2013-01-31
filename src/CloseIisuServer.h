#pragma once

//IISU includes
//iisuSDK global header (includes all iisu functionalities)
#include <SDK/iisuSDK.h>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

using namespace SK;
using namespace std;

#include "ofMain.h" 
#include "IisuEvents.h" 

class CloseIisuServer 
{
	public :
		CloseIisuServer () 
		{
			//Explicity set to NULL before initialization
			m_iisuHandle = NULL ; 
			m_device = NULL ; 
		}

		IisuHandle *	m_iisuHandle;		// iisu handle
		Device *		m_device;			// pointer to the iisu device

		DataHandle<int32_t>							m_hand1_statusHandle ; 
		ParameterHandle<bool>						m_CI_EnabledHandle ; 
		DataHandle<Vector3>							m_hand1_palmPositionHandle ; 
		DataHandle<SK::Array<Vector3>>				m_hand1_fingerTipsHandle ; 
		DataHandle<SK::Array<int32_t>>				m_hand1_fingerTipsStatusHandle ; 
		DataHandle<bool>							m_hand1_openHandle ; 
		DataHandle<float>							m_hand1_openAmountHandle ; 
		

		int32_t									m_lastFrameID;		//ID of the last Frame
		bool									m_CI_Enabled ; 
		int32_t									m_hand1_status ; 
		Vector3									m_hand1_palmPosition ; 
		SK::Array<Vector3>						m_hand1_fingerTips ; 
		SK::Array<int32_t>						m_hand1_fingerTipsStatus ; 
		bool									m_hand1_open ; 
		float									m_hand1_openAmount ; 

		void handPoseGestureHandler ( SK::HandPosingGestureEvent e ) ;  

		// events callbacks
		void onError(const ErrorEvent& event);
		void onDataFrame(const DataFrameEvent& event)	; 
		void registerEvents() ; 

		void setup() ; 
		void initIisu() ; 
		void exit( int exitCode = -1 ) ; 
		
		void handActivatedHandler( SK::HandActivatedEvent ) ; 
		void handDeactivatedHandler( SK::HandDeactivatedEvent ) ;

		ofVec3f iisuPointToOF( Vector3 point ) ; 
		ofVec3f IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofRectangle bounds , bool mirrorX = false ) ; 

		ofVec3f Iisu3DtoStage ( Vector3 iisuPosition , float paddingRatio = 0.0f , bool bMirror = true , bool bKeepWithinBounds = true )
		{
			ofVec3f loc = ofVec3f ( iisuPosition.x , iisuPosition.y , iisuPosition.z ) ; 
			float mirrorFactor = 1 ; 
			if ( bMirror == true ) 
				mirrorFactor = -1 ; 


			ofVec3f desiredLoc = ofVec3f ( ofMap( mirrorFactor * loc.x , -.25 , .25 , ofGetWidth() * -paddingRatio , ofGetWidth() * ( 1 + paddingRatio ) ) , 
										   ofMap( mirrorFactor * loc.z , -.25 , .25 , ofGetHeight() * -paddingRatio , ofGetHeight() * ( 1 + paddingRatio ) ) ,
										   iisuPosition.y ) ; 

			if ( bKeepWithinBounds )
			{
				if ( desiredLoc.x > ofGetWidth() ) 
					desiredLoc.x = ofGetWidth() ; 
				if ( desiredLoc.x < 0 ) 
					desiredLoc.x = 0 ; 
				if ( desiredLoc.y < 0 ) 
					desiredLoc.y = 0 ; 
				if ( desiredLoc.y > ofGetHeight() ) 
					desiredLoc.y = ofGetHeight() ; 
			}

			return desiredLoc ; 
		}

		/*
		public static function IIsuPosition3DToScreenPosition(IisuPosition:CIisuVector3,MainStage:Stage):CIisuVector3
		{
			var _ScreenPosition:CIisuVector3;
			_ScreenPosition = new CIisuVector3();
			
			_ScreenPosition.x = ( ( IisuPosition.x + 1 ) / 2 ) * MainStage.stageWidth ;
			_ScreenPosition.y = MainStage.stageHeight -( ( IisuPosition.z + 1 ) / 2 ) * MainStage.stageHeight ; 
			_ScreenPosition.z = IisuPosition.y; 
			
			return _ScreenPosition;
		}
		//////////////////////////////////////////////////////////////////////////
		public static function IIsuPosition2DToScreenPosition(IisuPosition:CIisuVector2,MainStage:Stage):CIisuVector2
		{
			var _ScreenPosition:CIisuVector2;
			_ScreenPosition = new CIisuVector2();
			
			_ScreenPosition.x = ( ( IisuPosition.x + 1 ) / 2 ) * MainStage.stageWidth ;
			_ScreenPosition.y = MainStage.stageHeight -( ( IisuPosition.y + 1 ) / 2 ) * MainStage.stageHeight ; 
			
			return _ScreenPosition;
		}*/

};


