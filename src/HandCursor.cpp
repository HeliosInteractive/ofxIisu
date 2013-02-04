#include "HandCursor.h"

void HandCursor::setup( IisuServer * iisu , int cursorID , ofColor _color ) 
{
	//Initialize everything the same as DepthCursor
	DepthCursor::setup( iisu , cursorID , _color ) ; 
	int numFingers = 5 ; 
	activeFingers = 0 ; 

	for ( int i = 0 ; i < numFingers ; i++ ) 
	{
		HandCursorFinger * finger = new HandCursorFinger() ; 
		finger->setup( i , 3 , ofColor::fromHsb( i * .2f * 255.0f , 255 , 255 ) ) ; 
		fingers.push_back( finger ) ; 
	}

	bOpen = false ; 
	openAmount = 1.0f ; 
	zFactor = 500.0f ; 
	handOpenThreshold = 0.2f ; 
}

void HandCursor::update ( ) 
{
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

		bActive = true ;

		float xSensitivity = 1.0f ; 
		float ySensitivity = 2.0f ; 

		//Calculate the palm position
		ofVec2f desiredLoc =  ofVec2f(iisu->m_hand1_palmPosition.x , iisu->m_hand1_palmPosition.y ) ; 
		desiredLoc.x = ( 1.0f - ( desiredLoc.x / 320.0f ) ) * ofGetWidth() ; 
		desiredLoc.y = ( ( desiredLoc.y / 240.0f ) ) * ofGetHeight() ; 

		//Calculate the hand tip
		ofVec2f desiredHandTip =  ofVec2f( iisu->m_hand1_tipPosition2D.x , iisu->m_hand1_tipPosition2D.y  )  ; 
		desiredHandTip.x = ( 1.0f - ( desiredHandTip.x / 320.0f )) * ofGetWidth() ; 
		desiredHandTip.y = ( ( desiredHandTip.y / 240.0f )) * ofGetHeight() ; 

		position = desiredLoc ;
		handTipPosition = desiredHandTip ; 

		if ( fingers.size() > 0 ) 
		{
			for ( int f = 0 ; f < fingers.size() ; f++ ) 
			{ 
				int lastStatus = (fingers[f])->status ;
				int newStatus = iisu->m_hand1_fingerTipsStatus[ f ] ; 
				
				(fingers[f])->status = newStatus ; //iisu->m_hand1_fingerTipsStatus[ f ] ; 
				
				if ( lastStatus != newStatus ) 
				{
					string lastStatusString = " inactive " ; 
					if ( lastStatus == 1 ) 
						lastStatusString = " detected " ; 
					if ( lastStatus == 2 ) 
						lastStatusString = " tracked " ; 

					string newStatusString = " inactive " ;
					if ( newStatus == 1 ) 
						newStatusString == " detected " ; 
					if ( newStatus == 1 ) 
						newStatusString == " tracked " ; 

					
					ofLog( OF_LOG_VERBOSE,  " finger# " + ofToString( f ) + " was : " + lastStatusString + " is now : " + newStatusString ) ;  
				}
					
				ofVec2f desiredFingerLoc = ofVec2f( iisu->m_hand1_fingerTips[f].x , iisu->m_hand1_fingerTips[f].y ) ;
				desiredFingerLoc.x = ( 1.0f - ( desiredFingerLoc.x / 320.0f ) ) * ofGetWidth() ; 
				desiredFingerLoc.y = ( ( desiredFingerLoc.y / 240.0f ) ) * ofGetHeight() ; 

				(fingers[f])->radius = 8.0f ; // ( 0.9f - normalZ ) * 40.0f ; 
				(fingers[f])->position = desiredFingerLoc ; 

				if ( (fingers[f])->status > 0 )  
				{
					activeFingers++ ; 
				}
								
			}
		}
		else
		{

		}
	}
	else
	{
		bActive = false ; 
	}
}

void HandCursor::draw ( ) 
{
	if ( iisu->m_hand1_status < 1 ) 
		return ; 


	//cout << "position: " << position << " , handTipPosition " << handTipPosition << endl ; 
	for ( int f = 0  ; f < fingers.size() ; f++ ) 
	{
		fingers[f]->draw() ; 
	}

	ofFill();
	if ( bOpen )
		ofSetColor ( color ) ; 
	else
		ofSetColor( color , 125 ) ; 
	ofCircle( position.x , position.y , 25 + openAmount * 25.0f  ) ;
	ofCircle( handTipPosition.x , handTipPosition.y , 20.0f  ) ;

	ofSetColor( 255 , 255 , 255 ) ; 
	ofPushStyle() ; 
		ofEnableSmoothing();
		ofSetColor( color ) ; 

		float maxLineWidth = 15.0f ;
		float nSegments = maxLineWidth ; //15.0f ; 
		ofVec2f lastPoint ; 
		for ( int i = 0 ; i < nSegments ; i++ ) 
		{
			float ratio = ( (float ) i / ( nSegments ) ) ; 
			ofVec2f p = position.interpolate( handTipPosition ,ratio ) ; 

			if ( i > 0 ) 
			{
				ofSetLineWidth ( ( 1.0f - ratio )  * maxLineWidth ) ; 
				ofLine ( p , lastPoint ) ; 
			}

			lastPoint = p ; 

		}
		//ofLine ( position , handTipPosition ) ; 
	ofPopStyle( ) ; 

	
}	

void HandCursor::debugDraw( )
{


	if ( iisu->m_hand1_status < 1 ) 
		return ; 
	
	string status = "Hand #" + ofToString ( cursorID ) + " #"+ofToString( activeFingers ) + " fingers " ; 
	ofDrawBitmapStringHighlight( status , position.x , position.y) ; 
	ofPushMatrix() ; 
		//ofTranslate( fingerCentroid.x , fingerCentroid.y , 0 ) ; // fingerCentroid.z ) ; 
		for ( int f = 0  ; f < fingers.size() ; f++ ) 
		{
			fingers[f]->debugDraw() ; 
		}
	ofPopMatrix() ;
}