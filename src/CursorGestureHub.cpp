#include "CursorGestureHub.h"

void CursorGestureHub::setup ( IisuServer * _iisu ) 
{
	iisu = _iisu ; 
	int hand1Index = iisu->addController() ; 
	hand1.setup( iisu , hand1Index , ofColor( 0 , 255 , 125 ) ) ; 

	int hand2Index = iisu->addController() ; 
	hand2.setup( iisu , hand2Index , ofColor( 0 , 125, 255 ) ) ; 

	bMultiTouchActive = false ; 

	gestureAngle = 0.0f ;  
	gestureScale = 1.0f ; 
	XZAngle = 0.0f ; 
	YZAngle = 0.0f ; 

	yRotation = 0.0f ; 
	xRotation = 0.0f ;  

	dampenTime = 0.12f ;

		worldScaling = 1.0f ; 
	worldOffset = ofPoint ( ) ; 
}

void CursorGestureHub::update ( )
{
	hand1.update() ; 
	hand2.update() ;

	if ( bMultiTouchActive == false ) 
	{
		if ( hand1.cursorStatus > 0 && hand2.cursorStatus > 0 )
		{
			cout << "Multitouch session started @" << ofGetElapsedTimef() << " elapsed seconds." << endl; 
			bMultiTouchActive = true ; 
			rightHand = IisuUtils::Instance()->VectorToPoint( iisu->getWorldCursorPosition( hand1.cursorID ) ) * worldScaling + worldOffset ; 
			leftHand = IisuUtils::Instance()->VectorToPoint( iisu->getWorldCursorPosition( hand2.cursorID ) ) * worldScaling + worldOffset ;  
			//cout << "right Hand : " << rightHand.x << " , " << rightHand.y << " , " << rightHand.z << endl ;
			//cout << "left hand : " << leftHand.x << " , " << leftHand.y << " , " << leftHand.z << endl ; 

			
			XZAngle = ofRadToDeg( atan2( rightHand.x - leftHand.x, rightHand.z - leftHand.z ) ) ;// - 90.0f ; //- startXRot ;
			//cout << "startXZ angle " << XZAngle << endl ; 
	//	YZAngle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.z - leftHand.z ) ) ; // 90.0f ; // - startYRot ;

			startRightHand = rightHand ;
			startLeftHand = leftHand ;
	
			startDistance = rightHand.distance( leftHand ) ; 
			startCentroid = ( startRightHand + startLeftHand ) / 2 ;
			startAngle = handAngle ; 

			startXRot = ofRadToDeg( atan2( rightHand.x - leftHand.x, rightHand.z - leftHand.z ) ) ; 
			startYRot = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.x - leftHand.x ) ) ;
			startY = ( rightHand.y + leftHand.y ) / 2 ; 
		}
	}
	if ( bMultiTouchActive == true ) 
	{
		if ( hand1.cursorStatus < 1 || hand2.cursorStatus < 1 )
		{
			bMultiTouchActive = false ; 
			cout << "Multitouch session ended @" << ofGetElapsedTimef() << " elapsed seconds." << endl; 
		}
		else
		{
			calcGestureValues( ) ; 
		}
	}
}

void CursorGestureHub::draw ( ) 
{
	//hand1.draw() ; 
	//hand2.draw() ;
}

void CursorGestureHub::debugDraw ( ) 
{
	hand1.debugDraw() ; 
	hand2.debugDraw() ;
}

void CursorGestureHub::calcGestureValues ( ) 
{
	//Get our two hands
	rightHand = IisuUtils::Instance()->VectorToPoint( iisu->getWorldCursorPosition( hand1.cursorID ) ) * worldScaling + worldOffset ; 
	leftHand = IisuUtils::Instance()->VectorToPoint( iisu->getWorldCursorPosition( hand2.cursorID ) ) * worldScaling + worldOffset ;  
			
	float dist = rightHand.distance( leftHand ) ;
    float angle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.x - leftHand.x ) ) ; 
	ofVec3f centroid = ( rightHand + leftHand ) / 2 ; 

	gestureAngle = angle - startAngle ; 
	gestureScale = dist / startDistance ;
	gestureTranslate = centroid - startCentroid ; 

	if ( gestureScale > minMaxScale.y ) 
		gestureScale = minMaxScale.y  ; 
	if ( gestureScale < minMaxScale.x ) 
		gestureScale = minMaxScale.x ; 

	XZAngle = ofRadToDeg( atan2( rightHand.x - leftHand.x, rightHand.z - leftHand.z ) ) + 90.0f ; //- startXRot ;
	YZAngle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.z - leftHand.z ) ) ; // 90.0f ; // - startYRot ;

	yOffset = (( rightHand.y + leftHand.y ) / 2 ) - startY ; 
	yOffset *= dampenTime ;
	if ( yOffset < minMaxXRotation.x ) 
		yOffset = minMaxXRotation.x ; 
	if ( yOffset > minMaxXRotation.y ) 
		yOffset = minMaxXRotation.y ; 

	
	float _newAngle =  ( XZAngle ) ; 
	if ( _newAngle > maxRotation ) 
		_newAngle = maxRotation; 
	if ( _newAngle < -maxRotation ) 
		_newAngle =- maxRotation; 

	yRotation += ( _newAngle  ) ; 
	xRotation = ( YZAngle ) ; 
	ofQuaternion xRot( yOffset , ofVec3f(1,0,0));  
	ofQuaternion yRot( yRotation , ofVec3f(0,1,0));  

	curRot =  yRot * xRot  ;  

	lastXZAngle = XZAngle ;
	lastYZAngle = YZAngle ; 
}

void CursorGestureHub::cameraDraw( ) 
{
	//Get our two hands
	ofPoint rightHand = IisuUtils::Instance()->VectorToPoint( iisu->getWorldCursorPosition( hand1.cursorID ) ) * worldScaling + worldOffset ; 
	ofPoint leftHand = IisuUtils::Instance()->VectorToPoint( iisu->getWorldCursorPosition( hand2.cursorID ) ) * worldScaling + worldOffset ;  

	//cout << "right Hand : " << rightHand.x << " , " << rightHand.y << endl ;
	//cout << "left hand : " << leftHand.x << " , " << leftHand.y << endl ; 
	
	float hand1Alpha = 255 ; 
	if ( hand1.cursorStatus < 2 ) hand1Alpha = 125 ; 
	ofSetColor( hand1.color , hand1Alpha ) ; 
	ofSphere( rightHand  , 25 ) ; 

	float hand2Alpha = 255 ; 
	if ( hand2.cursorStatus < 2 ) hand2Alpha = 125 ; 
	ofSetColor( hand2.color , hand2Alpha ) ; 
	ofSphere( leftHand   , 25 ) ; 
}

void CursorGestureHub::applyObjectTransformation( ) 
{
	//Extract the rotation from the current rotation
	ofVec3f axis;  
	float angle;  
	curRot.getRotate(angle, axis);  
	
	//apply the quaternion's rotation to the viewport and draw the sphere
	ofRotate(angle, axis.x, axis.y, axis.z);  
	ofScale( gestureScale , gestureScale , gestureScale ) ; 
}

string CursorGestureHub::generateKaonString( ) 
{
	//Generate the string to send to KAON !!!!!
	//Cursor1 [ bool isTrackedWell , float x , float y , float z ] 
	//Cursor2 [ bool isTrackedWell , float x , float y , float z ] 
	//Gesture[ bool isActive , float scale, float xAngle , float yAngle , float translateX , float translateY ] 
	//"gesture([0,0,0,0,0])" 

	string kaonString = "gesture(["+ofToString( bMultiTouchActive )+","+ofToString(gestureScale)+","+ofToString(xRotation)+","+ofToString(yRotation)+","+ofToString(gestureTranslate.x)+","+ofToString(gestureTranslate.y)+"])" ; 
	return kaonString ; 
}