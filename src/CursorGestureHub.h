#pragma once
#include "ofMain.h"
#include "ofxIisu.h"

class CursorGestureHub
{
public : 
	CursorGestureHub() { } 
	~CursorGestureHub() { } 


	void setup ( IisuServer * iisu ) ; 
	void update ( ) ;
	void draw ( ) ; 
	void debugDraw( ) ; 
	void calcGestureValues ( ) ; 
	void applyObjectTransformation( ) ; 

	IisuServer * iisu ; 
	bool bMultiTouchActive ; 
	ofPoint startRightHand ; 
	ofPoint startLeftHand ; 
	float startAngle ; 
	float startDistance ; 
	ofPoint startCentroid ; 

	float gestureScale, gestureAngle ; 
	ofPoint gestureTranslate  ; 

	float handAngle ;		//2D angle between right and left hands
	float handDistance ;	//3D distance between right and left hands
	ofPoint handTranslate ; //Translation from initial point

	//current state of the rotation  
	ofQuaternion curRot;  
	float XZAngle ; 
	float YZAngle ;

	float lastXZAngle ; 
	float lastYZAngle ;
		
	float yRotation ; 
	float xRotation ; 

	float startY ; 
	float yOffset ; 

	ofVec2f minMaxScale ;
	ofVec2f minMaxXRotation ; 
		
	float startXRot ; 
	float startYRot ; 
	
	float dampenTime ; 
	float maxRotation ; 

	DepthCursor hand1 ; 
	DepthCursor hand2 ;

	void cameraDraw( ) ; 

	float worldScaling ; 
	ofPoint worldOffset ; 

	ofPoint rightHand ; 
	ofPoint leftHand ; 

	string generateKaonString() ; 
	
};