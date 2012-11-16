#include "IisuSkeleton.h"
#include "Tweenzor.h"

void IisuSkeleton::setup ( )
{
	bTracked  = false ;  
	bDebugRender = true  ; 
	bFlipX = false ; 
	bFlipY = false ;

	glEnable(GL_DEPTH_TEST);

	bClapped = false ; 
	bRaisedHand = false ; 

	int totalJoints = 21 ; 
	for ( int i = 0 ; i < totalJoints ; i++ ) 
	{
		jointSizes.push_back( 4 ) ; 
		jointColors.push_back( ofColor( ofColor::white ) ) ; 
	}

	jointSizes[SK::SkeletonEnum::RIGHT_WRIST ] = 12.0f ; 
	jointColors[SK::SkeletonEnum::RIGHT_WRIST ] = ofColor( 255 , 212 , 0 ) ; 

	jointSizes[SK::SkeletonEnum::LEFT_WRIST ] = 12.0f ; 
	jointColors[SK::SkeletonEnum::LEFT_WRIST ] = ofColor( 255 , 212 , 0 ) ;

}


void IisuSkeleton::update ( ) 
{
	bool isTracked = iisu->m_skeletonStatus ; 
	if ( isTracked != 0 ) 
	{		
		SK::Array<SK::Vector3> keyPoints = iisu->m_keyPoints ; 		
		SK::Array<float> keyPointsConfidence = iisu->m_keyPointsConfidence ; 


		rawPositions.clear( ) ; 
		positions.clear( ) ; 
		for ( int i = 0 ; i < keyPoints.size() ; i++ ) 
		{
			//Use the helper function to get the right coordinate spaces
			ofPoint _p = ofPoint ( keyPoints[i].x , keyPoints[i].y , keyPoints[i].z ) + offset ; 
			rawPositions.push_back ( _p ) ;
			//ofVec3f IIsuPosition3DToOfxScreen( Vector3 IisuPosition ,  ofPoint offset , ofPoint scale , bool mirrorX = false , bool mirrorY = false ) ; 
			Vector3 keyP = keyPoints[i] ; 
			keyP.x += offset.x ; 
			keyP.y += offset.z ; 
			keyP.z += offset.y ; 
			ofVec3f p = IisuUtils::Instance()->IIsuPosition3DToOfxScreen( keyP , scale , bFlipX , bFlipY ) ; 
			positions.push_back( p ) ; 
		}

		centroid = positions[ SK::SkeletonEnum::WAIST ] ; //, bounds , bFlipX , bFlipY ) ;  

		//Get our two hands
		ofVec2f rightHand = positions[SK::SkeletonEnum::RIGHT_WRIST ] ; 
		ofVec2f leftHand = positions[SK::SkeletonEnum::LEFT_WRIST ] ; 

		//centroid = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::WAIST ] , bounds , bFlipX , bFlipY ) ; 

		//Check for "hands up" and "hands down" gesture
		ofVec2f collar = positions [SK::SkeletonEnum::COLLAR ] ;

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
		ofVec2f rightShoulder = positions[ SK::SkeletonEnum::RIGHT_SHOULDER ] ;
		ofVec2f leftShoulder = positions[ SK::SkeletonEnum::LEFT_SHOULDER ] ;

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
    
        handDistance = rightHand.distance( leftHand ) ;
        handAngle = ofRadToDeg( atan2( rightHand.y - leftHand.y, rightHand.x - leftHand.x ) ) ;
	}
	else
	{

		bTracked  = false ;  
	}
}

void IisuSkeleton::draw ( ) 
{

	bool isTracked = iisu->m_skeletonStatus ; 

	if ( isTracked != 0 ) 
	{		
		ofSetColor ( ofColor::red ) ; 
		for ( int i = 0 ; i < positions.size() ; i++ ) 
		{
			//Use the helper function to get the right coordinate spaces
			ofPushMatrix() ; 
				ofTranslate( positions[i].x , positions[i].y , positions[i].z ) ; 
				ofSetColor( jointColors[ i ] ) ; 
				ofSphere( 0 , 0 , 0, jointSizes[ i ] ) ; 
			ofPopMatrix() ; 
		}

		//Get our two hands
		ofVec3f rightHand = positions[ SK::SkeletonEnum::RIGHT_WRIST ] ; 
		ofVec3f leftHand = positions[ SK::SkeletonEnum::LEFT_WRIST ] ;

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
		multiTouchThreshold.z += ( scale.z * zPlane ) ; 

		ofPushMatrix() ; 
			ofSetColor( 255 , 125 , 125 ) ;
			ofBox( multiTouchThreshold ,300 ) ; 
		ofPopMatrix() ; 
		
		
	}
}

void IisuSkeleton::debugDraw( ) 
{
	if( positions.size() > 0 ) 
	{
		ofVec3f rightHand = positions[SK::SkeletonEnum::RIGHT_WRIST ] ; 
		ofVec3f leftHand = positions[SK::SkeletonEnum::LEFT_WRIST ] ;
		string status = " x :" + ofToString ( rightHand.x ) + ",y:"+ofToString( rightHand.y) +",z:"+ofToString(rightHand.z ) ; 
		ofDrawBitmapStringHighlight( status , 15 , ofGetHeight() - 60 ) ; 
	}
}
