#pragma once


#include "IisuServer.h" 
#include "ofMain.h" 
#include "InteractionManager.h"
//#include "CrossFadeImage.h"


enum POINTER_STATUS
{
	POINTER_STATUS_NOT_DETECTED = 0,
	POINTER_STATUS_ACTIVE = 1,
	POINTER_STATUS_STILL = 2,
	POINTER_STATUS_OUT_OF_BOX = 3,

};

class IisuUserRepresentation
{
	public : 
		IisuUserRepresentation( ) { } 

		IisuServer * iisu ; 
		
		ofImage sceneImage ; 
		ofImage userImage ; 

		unsigned char rawPixels[120 * 160];

		int lastUserID ; 

		string status ; 
		string instructions ; 

		int lastFrame ; 
		
		int minMappedBrightness ; 
		int maxMappedBrightness ; 

		int pPointerStatus ; 
		
		float width , height ; 
		bool bMirrorX , bMirrorY ; 

		void setup ( float _width , float _height , bool _bMirrorX = false , bool _bMirrorY = false ) 
		{
			width = _width ; 
			height = _height ; 
			bMirrorX = _bMirrorX ; 
			bMirrorY = _bMirrorY ; 
			
			pPointerStatus = -3 ; 
			lastFrame= -4 ; 
			sceneImage.allocate( width , height , OF_IMAGE_GRAYSCALE ) ; 
			userImage.allocate ( width , height , OF_IMAGE_GRAYSCALE ) ; 

			lastUserID = 0 ; 
		
			minMappedBrightness = 1 ; 
			maxMappedBrightness = 255 ; 

		} 

		void update ( ) 
		{
			//Get our status
			getStatusString( iisu->m_pointerStatus ) ; 

			//Make sure that the sceneImage is initialized and working correctly
			if ( iisu->sceneImageHandle.isValid() == 1 )
			{
				//Check frame overlap
				if ( lastFrame == iisu->m_lastFrameID )
				{
					cout << "repeat frame! " << endl ; 
					return ; 
				}

				int totalPixels = 160 * 120 ; 
				//Awesomely added by Andy Warner ; 
				unsigned char * pRawPixels = iisu->sceneImage.getRAW() ;
				//memcpy prevents it from having read/write at the same time issues
				memcpy(rawPixels, pRawPixels, totalPixels);

				int userValue = iisu->user1SceneID ; 
				sceneImage.setFromPixels( rawPixels, sceneImage.width , sceneImage.height , OF_IMAGE_GRAYSCALE , true ) ;
				sceneImage.mirror( bMirrorX , bMirrorY ) ; 

				//If over 250 then the user rep is not valid.
				if ( userValue < 250 ) 
				{
					for ( int i = 0 ; i < totalPixels ; i++ ) 
					{
						unsigned char value = rawPixels[i] ; 
						if ( value != userValue && value != lastUserID ) 
						{
							rawPixels[i] = 0 ;
						}
						else
							rawPixels[i] = 255 ; 
					}


					/* 
					//Trying to map the depth map of a user to have some dimensions
			
					int maxBrightness = 255; 
					int minBrightness = 1 ; 

					//rawPixels[i] = 255 - rawPixels[i] ;
					if ( value > maxBrightness ) 
						maxBrightness = value ; 

					if ( value < minBrightness )
						minBrightness = value ; 
					//maxBrightness = ( value > maxBrightness ) ? rawPixels[i] : maxBrightness ; 
					//minBrightness = ( value < minBrightness ) ? rawPixels[i] : minBrightness ; 
					
					cout << "minBrightness : " << ofToString(minBrightness) << " <-> " << ofToString(maxBrightness) << endl ; 
					
					if ( minBrightness < maxBrightness )
					{
						//Map the colors to somethign that looks cooler
						for ( int p = 0 ; p < totalPixels ; p++ ) 
						{
							rawPixels[p] = ofMap( rawPixels[p] , minBrightness , maxBrightness  , minMappedBrightness , maxMappedBrightness ) ; 
						}
					}
					*/
					
				}
				else
				{
					for ( int i = 0 ; i < totalPixels ; i++ ) 
					{
						rawPixels[i] = 0 ;
					}
				}

				userImage.setFromPixels( rawPixels, sceneImage.width , sceneImage.height , OF_IMAGE_GRAYSCALE , true ) ;
				userImage.mirror( bMirrorX , bMirrorY ) ; 
	
				if ( userValue != lastUserID ) 
				{
					lastUserID = userValue ; 
				}
			}
		}

		void draw ( float x , float y , float width , float height ) 
		{
			ofEnableAlphaBlending() ; 
			ofPushMatrix() ; 

			ofSetColor ( 255 , 255 , 255 ) ;
				ofEnableAlphaBlending( ) ; 
				ofPushStyle() ; 
					ofSetColor( 15 , 15 , 15 ) ; 
					ofNoFill( ) ; 
					ofSetRectMode( OF_RECTMODE_CORNER ) ;
					ofRect( x , y , width , height ) ; 
				ofPopStyle() ; 
				
				ofSetColor ( 255 , 255 , 255 , 25 ) ; 
				sceneImage.draw(  x , y , width , height  ) ; 
				ofSetColor ( 0 , 255 , 0 , 195 ) ; 
				ofPushStyle() ; 
					ofEnableBlendMode( OF_BLENDMODE_ADD ) ; 
						userImage.draw ( x , y , width , height ) ;
					ofDisableBlendMode( ) ; 
				ofPopStyle() ; 

			ofPopMatrix() ; 
		}
			
	

		string getStatusString ( int pointerStatus ) 
		{
			string status = "" ; 
			switch ( pointerStatus ) 
			{
				case 0 : 
					status = "CIRCLE TO\n ACTIVATE" ; 
					break ; 

				case 3 : 
					status = "USER ENGAGED" ; 
					break ; 

				case 1 : 
					status = "HAND STILL" ; 
					break ; 

				case 2 : 
					status = "OUT OF\n BOUNDS" ; 
					break ;
		}

		return status ; 
	}

};