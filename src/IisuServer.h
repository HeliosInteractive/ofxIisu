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

class IisuServer 
{
	public :
		IisuServer () 
		{
			//Explicity set to NULL before initialization
			m_iisuHandle = NULL ; 
			m_device = NULL ; 
		}

		IisuHandle *	m_iisuHandle;		// iisu handle
		Device *		m_device;			// pointer to the iisu device

		//Data Handles
		DataHandle<bool>						m_controllerIsActiveData;
		DataHandle<SK::Vector3>					m_pointerCoordinatesData;
		DataHandle<int32_t>						m_pointerStatusData;
		ParameterHandle<int32_t>				m_centroidCountParameter ; 
		DataHandle<SK::Array<SK::Vector3>>		m_centroidPositionsData ; 
		DataHandle< SK::Image > sceneImageHandle ;
		SK::Image sceneImage ; 


		/*		Skeleton Stuff		*/
		SK::DataHandle<int>				m_skeletonStatusData;
		SK::DataHandle<SK::Array<SK::Vector3> > m_keyPointsData;
		SK::DataHandle<SK::Array<float> > m_keyPointsConfidenceData;

		//Trying this out : 
		DataHandle < int32_t >					m_user1SceneID ; 

		int32_t									user1SceneID ; 
		int32_t									m_lastFrameID;		//ID of the last Frame
		bool									m_controllerIsActive ;
		int32_t									m_pointerStatus ;
		SK::Vector3								m_pointerPosition ;
		int32_t									m_centroidCount ; 
		SK::Array<SK::Vector3>					m_centroidPositions ; 

		int32_t									m_skeletonStatus ; 
		SK::Array<SK::Vector3> m_keyPoints ;
		SK::Array<float> m_keyPointsConfidence;
		

		// events callbacks
		void onError(const ErrorEvent& event);
		void onDataFrame(const DataFrameEvent& event)	; 
		void registerEvents() ; 

		void setup() ; 
		void initIisu() ; 
		void exit( int exitCode = -1 ) ; 
		void onControllerCreated(SK::ControllerCreationEvent event);
		void onCircleGesture(SK::CircleGestureEvent event);

		ofVec3f iisuPointToOF( Vector3 point ) ; 
		ofVec3f IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofRectangle bounds , bool mirrorX = false , bool mirrorY = false ) ; 
};


