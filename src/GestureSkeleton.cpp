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
}

void GestureSkeleton::update ( ) 
{
	IisuSkeleton::update( ) ; 

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
				cout << "Put your fucking hands up! ! " << endl ; 
			}
		}
		if ( rightHand.y > collar.y && leftHand.y > collar.y ) 
		{
			if ( bRaisedHand == true ) 
			{
				bRaisedHand = false; 
				bSendHandsDown = true ; 
				cout << "Down to the ground! " << endl ; 
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
				cout << "send a clap IN! " << endl ; 
			}
		}

		if ( rightHand.x > rightShoulder.x && leftHand.x < leftShoulder.x ) 
		{
			if ( bClapped == true )
			{
				bClapped = false ; 
				bSendClapOut = true ; 
				cout << "send a clap OUT! " << endl ; 
			}
		}
    
		//Simple distance between the right and left hand
        handDistance = rightHand.distance( leftHand ) ;
		//Keep it simple with a 2D angle between your hands
        handAngle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.x - leftHand.x ) ) ;

		ofPoint multiTouchThreshold = positions[ SK::SkeletonEnum::WAIST ] ; 
		multiTouchThreshold.z += ( zPlane * scale.z )  ;

		cout << "r.z" << rightHand.z << " , l.z" << leftHand.z << " | z : " << multiTouchThreshold.z << endl ; 
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

		if ( gestureScale > 2.0f ) 
			gestureScale = 2.0f ; 
		if ( gestureScale < 0.35f ) 
			gestureScale = 0.35f ; 
}

void GestureSkeleton::draw ( ) 
{
	IisuSkeleton::draw( ) ; 

	if ( positions.size() > 0 ) 
	{
		//Get our two hands
		ofVec3f rightHand = positions[ SK::SkeletonEnum::RIGHT_HAND ] ; 
		ofVec3f leftHand = positions[ SK::SkeletonEnum::LEFT_HAND ] ;

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


		ofPoint multiTouchThreshold = positions[ SK::SkeletonEnum::WAIST ] ; 
		multiTouchThreshold.z += ( zPlane * scale.z )  ;

		ofEnableAlphaBlending( ) ; 
		ofPushMatrix() ; 
			ofSetColor( 255 , 65 , 65 , 125 ) ;
			if ( bMultiTouchActive == true ) 
				ofSetColor( 65 , 255 , 65 , 125 ) ;
			//cout << "multitTOuchThreshold.z " << multiTouchThreshold.z << " zPlane : " << zPlane << endl ; 
			ofTranslate( multiTouchThreshold ) ; 

			ofScale( gestureScale , gestureScale , 1 ) ; 
			ofRotateZ( gestureAngle ) ; 
			ofTranslate( gestureTranslate.x , gestureTranslate.y , 0 ) ; 
			//ofScale( 100.0f , 100.0f , 1.0f ) ; 
			ofRect( -planeSize/2 , -planeSize/2 , planeSize , planeSize ) ; 
		ofPopMatrix() ; 	
	}
}

void GestureSkeleton::debugDraw( ) 
{
	IisuSkeleton::debugDraw( ) ; 
}