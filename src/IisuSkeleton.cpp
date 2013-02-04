#include "IisuSkeleton.h"
void IisuSkeleton::setup ( )
{
	bTracked  = false ;  
	bDebugRender = true  ; 
	bFlipX = false ; 
	bFlipY = false ;

	glEnable(GL_DEPTH_TEST);

	int totalJoints = 21 ; 
	for ( int i = 0 ; i < totalJoints ; i++ ) 
	{
		jointSizes.push_back( 4 ) ; 
		jointColors.push_back( ofColor( ofColor::white ) ) ; 
	}
}


void IisuSkeleton::update ( ) 
{
	bTracked = iisu->m_skeletonStatus ; 
	if ( bTracked != 0 ) 
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
			Vector3 keyP = keyPoints[i] ; 
			keyP.x += offset.x ; 
			keyP.y += offset.z ; 
			keyP.z += offset.y ; 
			ofVec3f _scale = ofVec3f( scale.x , scale.x , scale.x ) ; 
			ofVec3f p = IisuUtils::Instance()->iisuPosition3DToOfxScreen( keyP , _scale , bFlipX , bFlipY ) ; 
			positions.push_back( p ) ; 
		}

		centroid = positions[ SK::SkeletonEnum::WAIST ] ;   
	}
	else
	{
		bTracked  = false ;  
	}
}

void IisuSkeleton::draw ( ) 
{

	//bool isTracked = iisu->m_skeletonStatus ; 

	if ( bTracked != false ) 
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
	}
}

void IisuSkeleton::debugDraw( ) 
{
	if( positions.size() > 0 ) 
	{
		ofVec3f rightHand = positions[SK::SkeletonEnum::RIGHT_WRIST ] ; 
		ofVec3f leftHand = positions[SK::SkeletonEnum::LEFT_WRIST ] ;
		//string status = " x :" + ofToString ( rightHand.x ) + ",y:"+ofToString( rightHand.y) +",z:"+ofToString(rightHand.z ) ; 
		//ofDrawBitmapStringHighlight( status , 15 , ofGetHeight() - 60 ) ; 
	}
}
