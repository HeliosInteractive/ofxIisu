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
#include "IisuUtils.h"
#include "IisuEvents.h" 

class IisuServer 
{
	public :
		IisuServer () 
		{
			//Explicity set to NULL before initialization
			m_iisuHandle = NULL ; 
			m_device = NULL ; 
		}


		bool bConnected ; 
		bool getIsConnected() { return bConnected ; } 
		IisuHandle *	m_iisuHandle;		// iisu handle
		Device *		m_device;			// pointer to the iisu device

		//Data Handles
		//User
		DataHandle<SK::Vector3>					m_user1MassCenterData ; 
		DataHandle<bool>						m_userIsActiveData ; 
		DataHandle < int32_t >					m_user1SceneID ; 

		//UI Pointers
		vector<DataHandle<bool>>				controllerIsActiveData ; 
		vector<DataHandle<SK::Vector3>>			pointerNormalizedCoordinatesData ; 
		vector<DataHandle<int32_t>>				pointerStatusData ; 
		vector<DataHandle<SK::Vector3>>			pointerGlobalCoordinatesData ; 
		
		//Camera
		DataHandle< SK::Image >					sceneImageHandle ;

		//Skeleton Stuff + Volume
		SK::DataHandle<int>						m_skeletonStatusData;
		SK::DataHandle<SK::Array<SK::Vector3> >	m_keyPointsData;
		SK::DataHandle<SK::Array<float> >		m_keyPointsConfidenceData;

		ParameterHandle<int32_t>				m_centroidCountParameter ; 
		DataHandle<SK::Array<SK::Vector3>>		m_centroidPositionsData ; 
		DataHandle< SK::Array<int> >			m_centroidsJumpStatusHandle ;
		
		//Data
		//USER
		SK::Vector3								m_user1MassCenter ; 
		int32_t									user1SceneID ; 
		int32_t									m_lastFrameID;		//ID of the last Frame
		bool									m_userIsActive ;

		//UI Pointers
		vector<bool>							controllerIsActive ; 
		vector<int32_t>							pointerStatus ; 
		vector<Vector3>							pointerNormalizedCoordinates ; 
		vector<Vector3>							pointerGlobalCoordinates ; 
	
		//Skeleton + Volume
		int32_t									m_skeletonStatus ; 
		SK::Array<SK::Vector3>					m_keyPoints ;
		SK::Array<float>						m_keyPointsConfidence;
		int32_t									last_skeletonStatus ;
		int32_t									m_centroidCount ; 
		SK::Array<SK::Vector3>					m_centroidPositions ; 
		SK::Array<int>							m_centroidJumpStatus ; 

		//Camera
		SK::Image								sceneImage ; 
	
		//Two modes for the camera close / far
		bool bCloseInteraction ;		

		//Close Range Interaction
		ParameterHandle<bool>						m_CI_EnabledHandle ; 

		vector<DataHandle<int32_t>>					handStatusesHandle ; 
		vector<DataHandle<Vector2>>					handPalmPositions2DHandle ;
		vector<DataHandle<Vector2>>					handTipPositions2DHandle ; 
		vector<DataHandle<SK::Array<Vector2>>>		handFingerTips2DHandle ;
		vector<DataHandle<SK::Array<int32_t>>>		handFingerTipsStatusHandle ; 
		vector<DataHandle<bool>>					handsOpenHandle ; 
		vector<DataHandle<float>>					handsOpenAmountHandle ; 

		int numHands ; 
		vector<int32_t>								handStatuses; 
		vector<Vector2>								handPalmPositions2D ;
		vector<Vector2>								handTipPositions2D; 
		vector<SK::Array<Vector2>>					handFingerTips2D ;
		vector<SK::Array<int32_t>>					handFingerTipsStatus ; 
		vector<bool>								handsOpen ; 
		vector<float>								handsOpenAmount ; 					

		int getHandStatus ( int handID ) ; 
		Vector2 getHandPalmPosition2D ( int handID ) ; 
		Vector2 getHandTipPosition2D( int handID ) ; 
		bool getHandsOpen( int handID ) ; 
		float getHandsOpenAmount ( int handID ) ; 
		SK::Array<int32_t> getHandsFingerTipsStatus ( int handID ) ;
		SK::Array<Vector2> getHandsFingerTips2D ( int handID ) ;

		bool									m_CI_Enabled ; 

		void handPoseGestureHandler ( SK::HandPosingGestureEvent e ) ;  
		void handActivatedHandler( SK::HandActivatedEvent ) ; 
		void handDeactivatedHandler( SK::HandDeactivatedEvent ) ;

		// events callbacks
		void onError(const ErrorEvent& event);
		void onDataFrame(const DataFrameEvent& event)	; 
		void registerEvents() ; 

		void setup( bool _bCloseInteraction ) ; 
		void initIisu() ; 
		int addController( ) ;
		int addCloseInteractionHand ( ) ;
		void exit( int exitCode = -1 ) ; 
		void onControllerCreated(SK::ControllerCreationEvent event);
		void onCircleGesture(SK::CircleGestureEvent event);

		int getCursorStatus ( int cursorID ) ; 
		Vector3 getNormalizedCursorCoordinates ( int cursorID ) ; 
		Vector3 getWorldCursorPosition( int cursorID ) ; 
};


