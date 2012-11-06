#pragma once


/*
Written by Ben McChesney
Base




*/
// iisu
#include <SDK/iisuSDK.h>
#include "ofMain.h"
#include "IisuServer.h"
//3D stuff
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ApplicationEvents.h"
#include "Instructions.h"
class IisuSkeleton
{
	public : 



		IisuServer * iisu ; 

		IisuSkeleton ( ) { } 
		~IisuSkeleton ( ) { } 
		
		//Universal access to the same event type
		static IisuSkeleton* Instance()
        {
            static IisuSkeleton inst;
            return &inst;
        }

		void setLightPosition ( ) ; 
		

		bool isTracked ;
		int nCentroids ; 
		void setCentroids ( int _newCentroids ) ; 

		ofVec3f serveTarget ; 
		ofVec3f victoryTarget ; 

		bool bDebug  ; 
		/* IISU BUBBLEMAN REP */
	//	ofFbo fbo ;  

		bool bTrackBall ; 

		ofLight pointLight;
		ofVec3f lightPosition ;
		float sphereRadius;
    
		ofColor lightColor;
		float colorHue;
		ofColor materialColor;
    
		ofMaterial sphereMaterial;
		float specularAlpha ; 
		float ambientAlpha ; 
		float shininess ; 
		
		string beginInstructionsHandle ; 
		string handTrackInstructionsHandle ; 
		string raiseBallInstructionsHandle ;

		bool	m_userManagementEnabled;

		void setup ( ) ; 
		void update ( ) ; 
		void draw ( ) ; 

		bool bTracked ; 
		bool bDebugRender ; 

		ofRectangle bounds ; 
		bool bFlipX , bFlipY ; 

		//Specific
		bool bCalibrateHand ;	//If the hand calibration is on
		bool bHandTracked ;		//If a hand has been placed and a threshold selected
		float calibrationStatus ; //How long the user has held their hand up to calibrate ( between 0 and 1 ) 
		ofVec3f primaryHand ; 
		ofVec3f secondaryHand ;


		float lastServeCross ;	//Last time ( in seconds ) hand crossed for threshold
		bool bTrackServe ; 
		bool bTrackServeComplete ; 
		ofVec3f servePosition ; 
		float serveCalibrationStatus ; 
		float serveThresholdDuration ; 

		float lastThresholdCross ;		//Last time ( in seconds of app ) that a hand crossed the threshold.
		bool bRightHanded ;			//Is our tracked hand on the users right hand ?
		float thresholdCrossDuration ;	//How long is the countdown for that threshold

	
		ofVec3f rawCentroid ;
		//Racket Model
        ofxAssimpModelLoader model;
        ofVboMesh mesh;
        ofPoint position;
        float normScale;
        ofPoint scale;
        ofPoint sceneCenter;
        ofMaterial material;
        ofTexture tex;
       // ofLight	light;

		ofVec3f modelRotationOffset ; 

		void rotateToNormal(ofVec3f normal) ;

		void drawTennisBall ( ) ; 
		//Ball Model
		ofxAssimpModelLoader ballModel ;
        ofVboMesh ballMesh ;
        ofMaterial ballMaterial;
        ofTexture ballTexture;
		ofVec3f centroid ;
		float ballAlpha ; 


		ofVec3f racketTranslate ; 
		ofEvent<int> BALL_SERVED ; 
		int numServes ; 

		void transitionOut ( ) ; 
		void transitionIn (  ) ; 

		//void practiceResetComplete ( float * args ) ; 
		void practiceServeComplete ( float * args  ) ;
		void practiceServeDelayComplete ( float * args ) ; 
		float serveDistance ; 

		float alpha ; 

		void loopStart ( float * args ) ; 
		void loopEnd ( float * args ) ;

		float tennisColorLerp ; 
		ofColor tennisBallColor ; 

		void drawFBO( ) ; 
		void drawUserRepBubbles ( ) ; 
		float fboAlpha ; 

		vector<ofVec3f> lerpCentroids ; 

		ofVec3f tweenRacketPosition ;
		ofVec3f tweenBallPosition ; 

		
		float zRange ; 
		float globalJointTween ; 


		float centroidLerpAmount ; 

		void drawHandProps( ) ; 

		ofVec3f minRacketRotation ; 
		ofVec3f maxRacketRotation ; 

		ofVec3f ballHitCenter ;
		ofVec3f combinedHitCenter ; 

		ofColor combinedHitColor ; 

		float minimumHandConfidence ; 
		float primaryHandConfidence ; 
		float secondayHandConfidence ; 

		float ballServeYOffset ; 
		float racketTweenTime ; 
		float skeletonTweenTime ; 

		void serveBallYComplete ( float * args ) ; 
		float endY ; 

		float ballFallTime ; 
		float ballArcHeight ; 
		ofVec3f headPosition ; 

		void ballFallComplete ( float * args ) ; 
		void ballResetToHandComplete ( float * args ) ; 
};