#include "HandCursor.h"
#include "ofxTweenzor.h"

void HandCursor::setup( ) 
{
	
	palmWeighting = 1.25 ; 
	int numFingers = 5 ; 
	activeFingers = 0 ; 

	for ( int i = 0 ; i < numFingers ; i++ ) 
	{
		Finger * finger = new Finger() ; ; 
		finger->status = 0 ; 
		finger->radius = 12 ; 
		finger->pt = ofVec2f() ; 
		fingers.push_back( finger ) ; 
	}

	bTracked = false ; 

	bOpen = false ; 
	openAmount = 1.0f ; 
	zFactor = 500.0f ; 
}

void HandCursor::update ( ) 
{

}

void HandCursor::updateIisu ( )
{

#ifndef MOUSE_DEBUG
	if ( iisu->m_device==NULL || iisu->m_iisuHandle==NULL)
	{
		cout << "Iisu is not initialized" <<endl;
		bTracked = false ; 
		//getchar();
		return ; 
	}

	activeFingers = 0 ; 
	if ( iisu->m_hand1_status > 0 ) 
	{
		bool lastOpen = bOpen ; 
		bOpen = ( openAmount > .2f ) ; //iisu->m_hand1_open ; 

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

		Tweenzor::add( &openAmount , openAmount ,iisu->m_hand1_openAmount  , 0.0f , 0.001f , EASE_OUT_QUAD ) ; 

		//openAmount = iisu->m_hand1_openAmount ; 
		ofVec3f _fingerCentroid = ofVec3f() ; 
		bTracked = true ; 
		//Calculate the palm position
		ofVec3f desiredLoc = iisu->Iisu3DtoStage( iisu->m_hand1_palmPosition , 0.25 , true , true ) ; 

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
		//desiredLoc.z = 0 ; 


		//cout << "Normalized : " << normalized.x << " , " << normalized.y << endl ; 
		Tweenzor::add ( &palmPosition.x , palmPosition.x , desiredLoc.x , 0.0f , 0.2f , EASE_OUT_QUAD ) ; 
		Tweenzor::add ( &palmPosition.y , palmPosition.y , desiredLoc.y , 0.0f , 0.2f , EASE_OUT_QUAD ) ; 
		Tweenzor::add ( &palmPosition.z , palmPosition.z , desiredLoc.z , 0.0f , 0.2f , EASE_OUT_QUAD ) ; 

		//vector<Finger*>::iterator finger ; 
		/*
		if ( fingers.size() > 0 ) 
		{
			for ( int f = 0 ; f < fingers.size() ; f++ ) 
			{ 
				(fingers[f])->status = iisu->m_hand1_fingerTipsStatus[ f ] ; 
				if ( (fingers[f])->status > 0 ) 
				{
					activeFingers++ ; 
					ofVec2f desiredLoc = iisu->Iisu3DtoStage(  iisu->m_hand1_fingerTips[f] , 0.25f , true , true ) ; 
					//if ( count == 0 ) 
					//	cout << " z : " <<  iisu->m_hand1_fingerTips[count].y << endl ; 
					float normalZ = ofMap( iisu->m_hand1_fingerTips[f].y , 0.2f , 0.9f , 0.0f , 1.0 , true ) ; 
					(fingers[f])->radius = ( 0.9f - normalZ ) * 40.0f ; 
					(fingers[f])->pt = desiredLoc ; 
					_fingerCentroid += desiredLoc ; 
				
				}
			}
			//Add the palm and give it a little more weight
			_fingerCentroid += palmPosition ;
			_fingerCentroid /= ( float ) ( activeFingers + 1 )  ; 
			//fingerCentroid = _fingerCentroid ; 
			Tweenzor::add( &fingerCentroid.x , fingerCentroid.x , _fingerCentroid.x , 0.00f , 0.2f , EASE_OUT_QUAD ) ; 
			Tweenzor::add( &fingerCentroid.y , fingerCentroid.y , _fingerCentroid.y , 0.00f , 0.2f , EASE_OUT_QUAD ) ; 
		}
		else
		{
			fingerCentroid = palmPosition ; 
		}*/

		fingerCentroid = palmPosition ; 

		
	}
	else
	{
		bTracked = false ; 
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
				ofNoFill() ; 
			}
			else
			{
				ofSetColor( 15 , 15 , 255 , 255 ) ; 
				ofFill() ; 
			}
			ofCircle( 0 , 0 , 25 + openAmount * 25.0f );
		ofPopStyle() ; 
	ofPopMatrix() ; 

	/*
	//vector<Finger*>::iterator finger ; 
	for ( int f = 0  ; f < fingers.size() ; f++ ) 
	{
		if ( (fingers[f])->status > 0 ) 
		{
			ofCircle( (fingers[f])->pt , (fingers[f])->radius ) ; 
			ofPushStyle( ) ; 
				ofSetColor ( 125 , 125 , 125 , 145 ) ; 
				ofLine ( (fingers[f])->pt , palmPosition ) ; 
			ofPopStyle( ) ; 
		}
	}
	*/

#endif
	/*
	ofPushStyle( ) ;
		ofSetLineWidth( 3 ) ; 
		ofNoFill ( ) ; 
		ofSetColor ( 125 , 125 , 125 , 175 ) ; 
		ofCircle( fingerCentroid , 25 ) ; 
	ofPopStyle( ) ; 
	*/
}	

void HandCursor::debugDraw( )
{

}