#include "HandCursor.h"

void HandCursor::setup( IisuServer * iisu , int cursorID , ofColor _color ) 
{
	//Initialize everything the same as DepthCursor
	DepthCursor::setup( iisu , cursorID , _color ) ; 
	palmWeighting = 1.25 ; 
	int numFingers = 5 ; 
	activeFingers = 0 ; 

	for ( int i = 0 ; i < numFingers ; i++ ) 
	{
		HandCursorFinger * finger = new HandCursorFinger() ; 
		finger->setup( i , 5 , ofColor::fromHsb( i * .25f * 255.0f , 255 , 255 ) ) ; 
		fingers.push_back( finger ) ; 
	}

	bOpen = false ; 
	openAmount = 1.0f ; 
	zFactor = 500.0f ; 
	handOpenThreshold = 0.2f ; 
}

void HandCursor::update ( ) 
{
	
#ifndef MOUSE_DEBUG
	if ( iisu->m_device==NULL || iisu->m_iisuHandle==NULL)
	{
		cout << "Iisu is not initialized" <<endl;
		bActive = false ; 
		//getchar();
		return ; 
	}

	activeFingers = 0 ; 
	if ( iisu->m_hand1_status > 0 ) 
	{
		bool lastOpen = bOpen ; 
		bOpen = ( openAmount > handOpenThreshold ) ;

		//change in openness !
		if ( bOpen != lastOpen )
		{
			int args = -1 ; 
			if ( bOpen == true ) 
			{
				ofNotifyEvent( IisuEvents::Instance()->HAND_OPEN , args ) ; 
			}
			else
			{
				ofNotifyEvent( IisuEvents::Instance()->HAND_CLOSE , args ) ; 
			}
		}

		//Interpolate it just a little bit
		openAmount = ofLerp( openAmount , iisu->m_hand1_openAmount , 0.5f ) ; 

		//openAmount = iisu->m_hand1_openAmount ; 
		ofVec3f _fingerCentroid = ofVec3f() ; 
		bActive = true ; 
		//Calculate the palm position
		
		ofVec3f desiredLoc = IisuUtils::Instance()->VectorToPoint(iisu->m_hand1_palmPosition) * 300.0f ; //IisuUtils::Instance()->IIsuPosition3DToOfxScreen( iisu->m_hand1_palmPosition , 0.25 , true , true ) ; 
		//ofVec3f desiredLoc =IisuUtils::Instance()->IIsuPosition3DToOfxScreen( iisu->m_hand1_palmPosition , 0.25 , true , true ) ; 

		//Normalized : 
		ofVec3f normalized = desiredLoc ; 
		normalized.x = (desiredLoc.x / (float)ofGetWidth())  + -0.5f ; 
		normalized.y = (desiredLoc.y / (float)ofGetHeight())  + -0.5f ; 
		//normalized.z = 0 ; 

		float xSensitivity = 1.0f ; 
		float ySensitivity = 2.0f ; 
		float zSensitivity = 1.0f ; 
		normalized.x *= xSensitivity ; 
		normalized.y *= ySensitivity ; 
		normalized.z *= zSensitivity ; 

		normalized += ( ofVec2f( 0.5 , 0.5 ) ) ; 
		desiredLoc.x = normalized.x * (float)ofGetWidth() ; 
		desiredLoc.y = normalized.y * (float)ofGetHeight() ; 
		desiredLoc.z = normalized.z * 50 ; 
		position = position.interpolate( desiredLoc , 0.5f ) ; 
		
		if ( fingers.size() > 0 ) 
		{
			for ( int f = 0 ; f < fingers.size() ; f++ ) 
			{ 
				(fingers[f])->status = iisu->m_hand1_fingerTipsStatus[ f ] ; 
				if ( (fingers[f])->status > 0 ) 
				{
					activeFingers++ ; 
					ofVec3f desiredLoc = IisuUtils::Instance()->IIsuPosition3DToOfxScreen(  iisu->m_hand1_fingerTips[f]  ,0.25  , true , true ) ;
					float normalZ = ofMap( iisu->m_hand1_fingerTips[f].y , 0.2f , 0.9f , 0.0f , 1.0 , true ) ; 
					(fingers[f])->radius = ( 0.9f - normalZ ) * 40.0f ; 
					(fingers[f])->position = desiredLoc ; 
					_fingerCentroid += desiredLoc ; 
				
				}
			}

			//Add the palm and give it a little more weight
			_fingerCentroid += position ;
			_fingerCentroid /= ( float ) ( activeFingers + 1 )  ; 
			fingerCentroid.interpolate( _fingerCentroid , 0.5f ) ; 
		}
		else
		{
			fingerCentroid = position ; 
		}

		fingerCentroid = position ; 

		
	}
	else
	{
		bActive = false ; 
	}

	//cout << "updating IISU! " << endl ; 
#endif
#ifdef MOUSE_DEBUG

	activeFingers = 0 ; 
	

#endif
}

void HandCursor::draw ( ) 
{
#ifndef MOUSE_DEBUG
	if ( iisu->m_hand1_status < 1 ) 
		return ; 

	ofPushMatrix()  ; 
		ofTranslate( fingerCentroid.x , fingerCentroid.y , fingerCentroid.z ) ; 
		ofPushStyle() ; 
			if ( bOpen )
			{
				ofSetLineWidth( 4 ) ; 
				ofSetColor ( 15 , 255 , 15 , 255 ) ; 
			}
			else
			{
				ofSetColor( 15 , 15 , 255 , 255 ) ; 
			}
			ofCircle( position , 25 + openAmount * 25.0f  ) ; 
		ofPopStyle() ; 
	ofPopMatrix() ; 

	for ( int f = 0  ; f < fingers.size() ; f++ ) 
	{
		fingers[f]->draw() ; 
	}
	

#endif


}	

void HandCursor::debugDraw( )
{

}