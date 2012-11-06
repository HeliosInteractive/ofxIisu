#include "IisuSkeleton.h"
#include "Tweenzor.h"

void IisuSkeleton::setup ( )
{
	bTracked  = false ;  
	bDebugRender = true  ; 
	bounds = ofRectangle ( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
	bFlipX = false ; 
	bFlipY = false ;

	glEnable(GL_DEPTH_TEST);
}


void IisuSkeleton::update ( ) 
{
	bool isTracked = iisu->m_skeletonStatus ; 
	if ( isTracked != 0 ) 
	{		
		SK::Array<SK::Vector3> keyPoints = iisu->m_keyPoints ; 		
		SK::Array<float> keyPointsConfidence = iisu->m_keyPointsConfidence ; 

		centroid = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::WAIST ] , bounds , bFlipX , bFlipY ) ;  

		//Get our two hands
		ofVec2f rightHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::RIGHT_WRIST ] , bounds , bFlipX , bFlipY ) ; 
		ofVec2f leftHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::LEFT_WRIST ] , bounds , bFlipX , bFlipY ) ; 

		centroid = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::WAIST ] , bounds , bFlipX , bFlipY ) ;  
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
		SK::Array<SK::Vector3> keyPoints = iisu->m_keyPoints ; 		
		SK::Array<float> keyPointsConfidence = iisu->m_keyPointsConfidence ; 
		ofSetColor ( ofColor::red ) ; 

		for ( int i = 0 ; i < keyPoints.size() ; i++ ) 
		{
			//Use the helper function to get the right coordinate spaces
			ofVec3f p = iisu->IIsuPosition3DToOfxScreen( keyPoints[i] , bounds , bFlipX , bFlipY ) ; 
			ofPushMatrix() ; 
				ofTranslate( p.x , p.y , p.z * 400 ) ; 
				ofSphere( 0 , 0 , 0, 8 ) ; 
			ofPopMatrix() ; 
 
		}

		//Get our two hands
		ofVec3f rightHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::RIGHT_WRIST ] , bounds , bFlipX , bFlipY ) ; 
		ofVec3f leftHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::LEFT_WRIST ] , bounds , bFlipX , bFlipY ) ;
		//Fake the Z a little bit, it comes in from IISU as between -1 and 1
		rightHand.z *= 400.0f ; 
		leftHand.z *= 400.0f ; 

		ofPushStyle() ; 
			ofNoFill() ; 
			ofSetColor( 0 , 255 , 0 ) ; 
			if ( rightHand.y > leftHand.y ) 
			{
				ofCircle( rightHand.x , rightHand.y , 25 ) ; 
			}
			else
			{
				ofCircle( leftHand.x , leftHand.y , 25 ) ; 
			}
		ofPopStyle() ; 
	}
}