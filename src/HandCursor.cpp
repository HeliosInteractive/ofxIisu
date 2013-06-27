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
	if ( iisu->getHandStatus( cursorID ) > 0 ) 
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
		openAmount =  ofLerp( openAmount , iisu->getHandsOpenAmount( cursorID ) , 0.5f ) ; 

		bActive = true ;

		float xSensitivity = 1.0f ; 
		float ySensitivity = 2.0f ; 

		//Calculate the palm position
		ofVec2f desiredLoc =  IisuUtils::Instance()->Vector2DToPoint( IisuUtils::Instance()->normalize2DPoint( iisu->getHandPalmPosition2D( cursorID ) , 320 , 240 , true ) ) ;
		desiredLoc.x *= ofGetWidth() ; 
		desiredLoc.y *= ofGetHeight() ; 

		//Calculate the hand tip
		ofVec2f desiredHandTip = IisuUtils::Instance()->Vector2DToPoint( IisuUtils::Instance()->normalize2DPoint( iisu->getHandTipPosition2D( cursorID ) , 320 , 240 , true ) ) ;
		desiredHandTip.x *= ofGetWidth() ; 
		desiredHandTip.y *= ofGetHeight() ; 

		position = desiredLoc ;
		handTipPosition = desiredHandTip ; 

		if ( fingers.size() > 0 ) 
		{
			SK::Array<int32_t> fingerStatus = iisu->getHandsFingerTipsStatus( cursorID ) ; 
			SK::Array<Vector2> fingerPositions2D = iisu->getHandsFingerTips2D( cursorID ) ;

			if ( fingerStatus.size() == 0 && fingerPositions2D.size() == 0 ) 
				return ; 

			
			for ( int f = 0 ; f < fingers.size() ; f++ ) 
			{ 
				int lastStatus = (fingers[f])->status ;
				int newStatus = fingerStatus[ f ] ; 
				
				(fingers[f])->status = newStatus ;
				
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
					
				ofVec2f desiredFingerLoc = IisuUtils::Instance()->Vector2DToPoint( fingerPositions2D[ f ] ) ;
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
	}
	else
	{
		bActive = false ; 
	}
}

void HandCursor::draw ( ) 
{
	if ( iisu->getHandStatus( cursorID ) < 1 ) 
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


	if ( iisu->getHandStatus( cursorID ) < 1 )  
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