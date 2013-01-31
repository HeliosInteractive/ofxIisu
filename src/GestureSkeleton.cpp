#include "GestureSkeleton.h"

void GestureSkeleton::setup ( ) 
{
	IisuSkeleton::setup() ;

	jointSizes[SK::SkeletonEnum::RIGHT_HAND ] = 12.0f ; 
	jointColors[SK::SkeletonEnum::RIGHT_HAND ] = ofColor( 255 , 212 , 0 ) ; 

	jointSizes[SK::SkeletonEnum::LEFT_HAND ] = 12.0f ; 
	jointColors[SK::SkeletonEnum::LEFT_HAND ] = ofColor( 255 , 212 , 0 ) ;

	bClapped = false ; 
	bRaisedHand = false ; 

	bSendHandsUp = false ;  
	bSendHandsDown = false ;  
	bSendClapIn = false ; 
	bSendClapOut = false ; 

	bMultiTouchActive = false ; 

	gestureAngle = 0.0f ;  
	gestureScale = 1.0f ; 
	XZAngle = 0.0f ; 
	YZAngle = 0.0f ; 

	yRotation = 0.0f ; 
	xRotation = 0.0f ;  
	
	planeSize = 4000 ; 
	//slows down the rotation 1 = 1 degree per pixel
	dampenTime = 0.12f ;
}

void GestureSkeleton::update ( ) 
{
	IisuSkeleton::update( ) ; 
	bool isTracked = iisu->m_skeletonStatus ; 
	//cout << "gestureSkeleton :: update ! " << endl ;
	if ( positions.size() > 0 ) //IisuSkeleton::getIsTracked() == true ) //IisuSkeleton::bTracked == true ) 
	{
		//cout << "!!!!!!!!!!!!!!! agestureSkeleton :: update ! " << endl ;
		//Get our two hands
		ofVec3f rightHand = positions[SK::SkeletonEnum::RIGHT_HAND ] ; 
		ofVec3f leftHand = positions[SK::SkeletonEnum::LEFT_HAND ] ; 
		//Check for "hands up" and "hands down" gesture
		ofVec3f collar = positions [SK::SkeletonEnum::COLLAR ] ;

		if ( rightHand.y < collar.y && leftHand.y < collar.y ) 
		{
			if ( bRaisedHand == false ) 
			{
				bRaisedHand = true ; 
				bSendHandsUp = true ; 
				//cout << "HANDS UP ! " << endl ; 
			}
		}
		if ( rightHand.y > collar.y && leftHand.y > collar.y ) 
		{
			if ( bRaisedHand == true ) 
			{
				bRaisedHand = false; 
				bSendHandsDown = true ; 
				//cout << "HANDS DOWN ! " << endl ; 
			}
		}

		//Check for "hands up" and "hands down" gesture
		ofVec3f rightShoulder = positions[ SK::SkeletonEnum::RIGHT_SHOULDER ] ;
		ofVec3f leftShoulder = positions[ SK::SkeletonEnum::LEFT_SHOULDER ] ;

		if ( rightHand.x < rightShoulder.x && leftHand.x > leftShoulder.x ) 
		{
			if ( bClapped == false )
			{
				bClapped = true ; 
				bSendClapIn = true ; 
				//cout << "send a clap IN! " << endl ; 
			}
		}

		if ( rightHand.x > rightShoulder.x && leftHand.x < leftShoulder.x ) 
		{
			if ( bClapped == true )
			{
				bClapped = false ; 
				bSendClapOut = true ; 
				//cout << "send a clap OUT! " << endl ; 
			}
		}
    
		//Simple distance between the right and left hand
        handDistance = rightHand.distance( leftHand ) ;
		//Keep it simple with a 2D angle between your hands
        handAngle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.x - leftHand.x ) ) ;

		ofPoint multiTouchThreshold = positions[ SK::SkeletonEnum::WAIST ] ; 
		multiTouchThreshold.z += ( zPlane * scale.z )  ;

		if ( rightHand.z < multiTouchThreshold.z && leftHand.z < multiTouchThreshold.z ) 
		{
			//Only want to set original values when first crossing the threshold
			if ( bMultiTouchActive == false ) 
			{
				bMultiTouchActive = true ; 
				startRightHand = rightHand ; 
				startLeftHand = leftHand ;
	
				startDistance = rightHand.distance( leftHand ) ; 
				startCentroid = ( startRightHand + startLeftHand ) / 2 ;
				startAngle = handAngle ; 

				startXRot = ofRadToDeg( atan2( rightHand.x - leftHand.x, rightHand.z - leftHand.z ) ) ; 
				
				/*
				if( startXRot > 180.0f ) 
					startXRot -= 360.0f ; 
					*/
				startYRot = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.x - leftHand.x ) ) ;

				startY = ( rightHand.y + leftHand.y ) / 2 ; 
				//if ( startYRot > 180.0f )   
				//	startYRot -= 360.0f ; 
			}
		}
		else
		{
			bMultiTouchActive = false ; 
		}
	}

	if ( bMultiTouchActive == true ) 
		calcGestureValues() ; 
}

void GestureSkeleton::calcGestureValues ( ) 
{

	//Get our two hands
		ofVec3f rightHand = positions[SK::SkeletonEnum::RIGHT_HAND ] ; 
		ofVec3f leftHand = positions[SK::SkeletonEnum::LEFT_HAND ] ; 

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

		//float XZAngle ; 
		//float YZAngle ;

		XZAngle = ofRadToDeg( atan2( rightHand.x - leftHand.x, rightHand.z - leftHand.z ) )  - 90.0f ; //- startXRot ;
		YZAngle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.z - leftHand.z ) ) ; // 90.0f ; // - startYRot ;

		//if ( _xAngle > 180.0f ) 
		//	_xAngle -= 360.0f ;

		//if ( _yAngle > 180.0f ) 
		//	_yAngle -= 360.0f ; 

		//yAngle = _yAngle ; //- startYRot ; 
		//xAngle = _xAngle ; //- startXRot ; 

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

		//float rotateSensitivity ;
		//float maxRotation ; 
		yRotation += ( _newAngle  ) ; 
		xRotation = ( YZAngle ) ; 
		//Tweenzor::add( &xAngle , xAngle , _xAngle , 0.0f , dampenTime, EASE_OUT_QUAD ) ; 
		//Tweenzor::add( &yAngle , yAngle , _yAngle , 0.0f , dampenTime , EASE_OUT_QUAD ) ; 
		ofQuaternion xRot( yOffset , ofVec3f(1,0,0));  
		ofQuaternion yRot( yRotation , ofVec3f(0,1,0));  

		//xRot *
		curRot =  yRot * xRot  ;  

		lastXZAngle = XZAngle ;
		lastYZAngle = YZAngle ; 
}

void GestureSkeleton::draw ( ) 
{
	IisuSkeleton::draw( ) ; 

	if ( positions.size() > 0 ) 
	{
		//Get our two hands
		ofVec3f rightHand = positions[ SK::SkeletonEnum::RIGHT_HAND ] ; 
		ofVec3f leftHand = positions[ SK::SkeletonEnum::LEFT_HAND ] ;


		if ( bMultiTouchActive == true ) 
		{
			ofSetColor( 0 , 212 , 212 ) ; 
			ofLine ( rightHand , leftHand ) ; 

			ofPushStyle() ; 
				ofNoFill() ; 
				ofSetLineWidth( 3 ) ; 
				ofPushMatrix() ; 
					ofTranslate(rightHand ) ; 
					ofCircle( 0 , 0 , 25 ) ;
				ofPopMatrix() ; 

				ofPushMatrix() ; 
					ofTranslate( leftHand ) ; 
					ofCircle( 0 , 0 , 25 ) ;
				ofPopMatrix( ) ; 
	
			ofPopStyle() ; 
		}

		ofPoint multiTouchThreshold = positions[ SK::SkeletonEnum::WAIST ] ; 
		multiTouchThreshold.z += ( zPlane * scale.x )  ;

		ofEnableAlphaBlending( ) ; 
		ofPushMatrix() ; 
			ofSetColor( 255 , 65 , 65 , 125 ) ;
			if ( bMultiTouchActive == true ) 
				ofSetColor( 65 , 255 , 65 , 125 ) ;
			//cout << "multitTOuchThreshold.z " << multiTouchThreshold.z << " zPlane : " << zPlane << endl ; 
			//ofTranslate( multiTouchThreshold ) ; 

			//ofScale( gestureScale , gestureScale , 1 ) ; 
			//ofRotateZ( gestureAngle ) ; 
			ofRect( -planeSize/2 , -planeSize/2 , planeSize , planeSize ) ; 
		ofPopMatrix() ; 
	ofPopStyle( ) ;  
	}
}

void GestureSkeleton::applyObjectTransformation( ) 
{
	//Extract the rotation from the current rotation
	ofVec3f axis;  
	float angle;  
	curRot.getRotate(angle, axis);  
	
	//apply the quaternion's rotation to the viewport and draw the sphere
	ofRotate(angle, axis.x, axis.y, axis.z);  
	ofScale( gestureScale , gestureScale , gestureScale ) ; 
}

void GestureSkeleton::debugDraw( ) 
{
	IisuSkeleton::debugDraw( ) ; 
}

string GestureSkeleton::generateKaonString( ) 
{
	//Generate the string to send to KAON !!!!!
	//Cursor1 [ bool isTrackedWell , float x , float y , float z ] 
	//Cursor2 [ bool isTrackedWell , float x , float y , float z ] 
	//Gesture[ bool isActive , float scale, float xAngle , float yAngle , float translateX , float translateY ] 
	//"gesture([0,0,0,0,0])" 

	string kaonString = "gesture(["+ofToString( bMultiTouchActive )+","+ofToString(gestureScale)+","+ofToString(xRotation)+","+ofToString(yRotation)+","+ofToString(gestureTranslate.x)+","+ofToString(gestureTranslate.y)+"])" ; 
	return kaonString ; 
}