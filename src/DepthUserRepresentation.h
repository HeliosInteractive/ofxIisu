#pragma once


#include "IisuServer.h" 
#include "ofMain.h" 
#include "ofxTextSuite.h"
#include "FontManager.h"
#include "ofVideoPlayer_alpha.h"
#include "InteractionManager.h"
#include "CrossFadeImage.h"


enum POINTER_STATUS
{
	POINTER_STATUS_NOT_DETECTED = 0,
	POINTER_STATUS_ACTIVE = 1,
	POINTER_STATUS_STILL = 2,
	POINTER_STATUS_OUT_OF_BOX = 3,

};

class DepthUserRepresentation
{
	public : 
		DepthUserRepresentation( ) { } 

		IisuServer * iisu ; 
		
		ofImage sceneImage ; 
		ofImage userImage ; 

		unsigned char rawPixels[120 * 160];

		int lastUserID ; 
		//ofImage waveToActivate ; 

		string status ; 
		string instructions ; 

		ofImage activateBG ; 
	//	ofVideoPlayer circleActivation ; 
		
		ofxTextBlock statusBlock ;
		ofxTextBlock instructionsBlock ; 
		TextBlockAlignment textAlignment ; 

		ofVideoPlayer_alpha activeMovie ;  ; 
		ofVideoPlayer_alpha warningMovie ; 
		ofVideoPlayer_alpha lostMovie ; 

		ofVideoPlayer_alpha * curVideo ;
		int lastFrame ; 

		//User status are shown with images, no longer text
		ofImage * curStatusImage ; 

		ofImage engagedMain ; 
		ofImage engagedMap ; 
		ofImage engagedNews ; 
		//ofImage lostConnection ; 
		//ofImage outOfBounds ; 

		CrossFadeImage crossFade ;

		int minMappedBrightness ; 
		int maxMappedBrightness ; 

		CrossFadeImage outOfBounds ; 
		CrossFadeImage lostConnection ; 

		int pPointerStatus ; 
		

		void setup ( ) 
		{
			pPointerStatus = -3 ; 
			curVideo = NULL ; 
			lastFrame= -4 ; 
			sceneImage.allocate( 160 , 120 , OF_IMAGE_GRAYSCALE ) ; 
			userImage.allocate ( 160 , 120 , OF_IMAGE_GRAYSCALE ) ; 
///			waveToActivate.loadImage ( "waveToActivate.png" ) ; 

			activeMovie.loadMovie( "cta/RingSpinWhite_1.mov" ) ; 
			activeMovie.setAnchorPercent( 0.5f , 0.5f ) ;
			activeMovie.setPosition ( 0.0f ) ; 

			warningMovie.loadMovie( "cta/RingSpinFlash.mov" ) ; 
			warningMovie.setAnchorPercent( 0.5f , 0.5f ) ;
			warningMovie.setPosition ( 0.0f ) ; 

			lostMovie.loadMovie( "cta/RingSpinRed.mov" ) ; 
			lostMovie.setAnchorPercent( 0.5f , 0.5f ) ;
			lostMovie.setPosition ( 0.0f ) ;

			curVideo = &warningMovie ; 
			//activeMovie.play() ; 
			activateBG.loadImage ( "cta/ringStatic.png" ) ; 
			activateBG.setAnchorPercent( 0.5 , 0.5 ) ; 
			lastUserID = 0 ; 
			curStatusImage = NULL ; 
			
			statusBlock.init ( FontManager::Instance()->getFontByName( FontList::Instance()->NEOSANS_INTEL_MEDIUM ).path , 28  ) ; 
			instructionsBlock.init ( FontManager::Instance()->getFontByName( FontList::Instance()->NEOSANS_INTEL ).path , 18 ) ; 

			statusBlock.setText( "USER REP NOT INITIATED" ) ; 
			instructionsBlock.setText( "NO INSTRUCTIONS" ) ; 

			statusBlock.wrapTextX( 250 ) ; 
			instructionsBlock.wrapTextX( 250 ) ;

			ofAddListener ( Events::Instance()->UPDATE_INSTRUCTIONS , this , &DepthUserRepresentation::updateInstructionsHandler ) ; 
			engagedMain.loadImage( "User/Engaged_Main.png" ) ; 
			engagedMap.loadImage( "User/Engaged_Map.png" ) ; 
			engagedNews.loadImage( "User/Engaged_News.png" ) ; 
			lostConnection.loadPresetImages( "User/Out_Of_Bounds_1.png" , "User/Out_Of_Bounds_2.png" ); 
			outOfBounds.loadPresetImages( "User/Lost_Connection_1.png" ,  "User/Lost_Connection_2.png" ) ;

			outOfBounds.bLooping = true ; 
			lostConnection.bLooping = true ; 
				//.loadImage( "User/Lost_Connection.png" ) ; 
			//outOfBounds.( "User/Out_Of_Bounds.png" ) ; 

			curStatusImage = &outOfBounds.preset1 ; 

			minMappedBrightness = 1 ; 
			maxMappedBrightness = 255 ; 

		} 

		void update ( ) 
		{
			if ( curVideo != NULL && curVideo->isPlaying() == true ) 
			{
				curVideo->update() ; 
			}


			setStatusImage( iisu->m_pointerStatus ) ; 
			getStatusString( iisu->m_pointerStatus ) ; 
			if ( iisu->sceneImageHandle.isValid() == 1 )
			{
				if ( lastFrame == iisu->m_lastFrameID )
				{
					cout << "repeat frame! " << endl ; 
					return ; 
				}

				int totalPixels = 160 * 120 ; 
				unsigned char * pRawPixels = iisu->sceneImage.getRAW() ; 
				memcpy(rawPixels, pRawPixels, totalPixels);

				int userValue = iisu->user1SceneID ; 
				//if ( userValue > 250 ) 
				//	return ; 
				sceneImage.setFromPixels( rawPixels, sceneImage.width , sceneImage.height , OF_IMAGE_GRAYSCALE , true ) ;
				sceneImage.mirror( false , true ) ; 
//				sceneImage.update() ; 
		

				int maxBrightness = 255; 
				int minBrightness = 1 ; 

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
						//{
							/*
							//rawPixels[i] = 255 - rawPixels[i] ;
							if ( value > maxBrightness ) 
								maxBrightness = value ; 

							if ( value < minBrightness )
								minBrightness = value ; 
							//maxBrightness = ( value > maxBrightness ) ? rawPixels[i] : maxBrightness ; 
							//minBrightness = ( value < minBrightness ) ? rawPixels[i] : minBrightness ; 
							*/
						//}
						//	 
					}

					/*
					cout << "minBrightness : " << ofToString(minBrightness) << " <-> " << ofToString(maxBrightness) << endl ; 
					
					if ( minBrightness < maxBrightness )
					{
						//Map the colors to somethign that looks cooler
						for ( int p = 0 ; p < totalPixels ; p++ ) 
						{
							rawPixels[p] = ofMap( rawPixels[p] , minBrightness , maxBrightness  , minMappedBrightness , maxMappedBrightness ) ; 
						}
					}*/
				}
				else
				{
					for ( int i = 0 ; i < totalPixels ; i++ ) 
					{
						rawPixels[i] = 0 ;
					}
				}

				//cout << "user Pixels are between : " << 
				//sceneImage.allocate( 160 , 120 , OF_IMAGE_GRAYSCALE ) ; 
				userImage.setFromPixels( rawPixels, sceneImage.width , sceneImage.height , OF_IMAGE_GRAYSCALE , true ) ;
				userImage.mirror( false , true ) ; 
//x				userImage.update() ; 
	
				if ( userValue != lastUserID ) 
				{
					//cout << "lastValue : " << lastUserID << endl ; 
					//cout << "userValue : " << userValue << endl ; 
					lastUserID = userValue ; 
				}
			}
		}

		void updateInstructionsHandler ( string &args ) 
		{
			instructionsBlock.setText( args ) ; 
	
			instructionsBlock.wrapTextX( 250 ) ;
		}

		void draw ( ) 
		{
			ofEnableAlphaBlending() ; 
			ofPushMatrix() ; 

			ofSetColor ( 255 , 255 , 255 ) ;
			
			/*
			ofPushMatrix() ; 
				ofTranslate( -160 , -5 , 0 ) ; 
				crossFade.draw( ) ; 
			ofPopMatrix( ) ; 
			*/
			if ( curStatusImage != NULL ) 
				curStatusImage->draw ( -160 , -30 ) ; 
			else
			{
				int pointerStatus = iisu->m_pointerStatus ; 
				if ( pointerStatus == 0 ) 
				{
					ofPushMatrix() ;
					ofTranslate (-160 , -30 , 0 ) ; 
					lostConnection.draw() ; 
					ofPopMatrix() ;
					if( pointerStatus != pPointerStatus ) 
						lostConnection.startLoop() ; 
				}
				if ( pointerStatus == 2 ) 
				{
					//cout << "out of bounds" << endl; 
					ofPushMatrix() ;
					ofTranslate ( -160 , -30 , 0 ) ; 
					outOfBounds.draw() ; 
					ofPopMatrix() ;
					if ( pointerStatus != pPointerStatus ) 
						outOfBounds.startLoop() ; 
				}

				pPointerStatus = pointerStatus ; 
			}
			/*
				
				statusBlock.setText(  getStatusString ( iisu->m_pointerStatus ) ) ; // .draw( idealSize.width + 2 , 0 ) ; 
					statusBlock.wrapTextX( 250 ) ; 
				statusBlock.drawCenter ( 0 , 10 ) ;
				//ofDrawBitmapString ( , 0 , 50 )  ;

				*/
				
				ofEnableAlphaBlending( ) ; 
				ofSetColor ( 255 , 255 , 255 , 125 ) ; 
				//sceneImage.draw( -70 , 220 , 140 , 120 ) ; 
				ofEnableBlendMode( OF_BLENDMODE_ADD ) ; 
					userImage.draw ( -80 , 200 , 140 , 120 ) ;
					ofPushMatrix() ; 
						ofTranslate ( 0 , 290 , 0 ) ; 
						activateBG.draw ( 0 , -20 ) ;
						ofSetColor ( 239 , 2 , 2 ) ; 
					ofPopMatrix() ; 
				ofDisableBlendMode( ) ; 
				ofEnableAlphaBlending( ) ; 

			
		
				if ( curVideo != NULL ) 
				{
					ofPushMatrix( ) ; 
						ofTranslate( 0 , 290 , 0 ) ;
						ofSetColor ( 255 , 255 , 255 ) ;
						curVideo->draw( 0 , -20 ) ; 
					ofPopMatrix() ; 
				}
				/*
				if ( iisu->m_pointerStatus == 0 ) 
				{
					ofPushMatrix() ; 
						ofTranslate ( 0 , 290 , 0 ) ; 
						ofSetColor ( 255 , 255 , 255 ) ; 
						circleActivation.draw ( 0 , 0 ) ; 
					ofPopMatrix() ;
				}*/
				//alphaVideo.draw ( 0 , 0 ) ; 
				//ofEnableAlphaBlending() ; 
				//ofSetColor ( 156 , 185 , 251 ) ;
				//instructionsBlock.drawCenter ( 0 , 450 ) ; 
				//ofDrawBitmapString( instructions , 0 , 44 ) ; 
			ofPopMatrix() ; 
		}

		void setStatusImage ( int pointerStatus ) 
		{
			int menuIndex = InteractionManager::Instance()->currentMenuIndex ; 
//			cout << "currentMenu : " << menuIndex << endl; 
			ofImage * newImage = NULL ;  


			float position = curVideo->getPosition() ; 
			if ( pointerStatus == 3 || 1) 
			{
			//	cout << "cursor active! " << endl ; 
				if ( menuIndex == 0 ) 
					newImage = &engagedMap ; 
				if ( menuIndex == 1 ) 
					newImage = &engagedNews ; 
				if ( menuIndex == 2 ) 
					newImage = &engagedMain ; 

				if ( newImage == NULL ) 
					newImage = &engagedMain ; 

				curVideo = &activeMovie ; 
			}
			if ( pointerStatus == 0 ) 
			{
				//cout << "cursorLost" << endl; 
				newImage = NULL ; &lostConnection ; 
				curVideo = &lostMovie ; 
			}
			if ( pointerStatus == 2 ) 
			{
				//cout << "out of bounds" << endl; 
				newImage = NULL ; &outOfBounds ; 
				curVideo = &warningMovie ; 
			}

			curStatusImage = newImage ; 

			curVideo->setPosition( position ) ; 
			curVideo->play( ) ; 
			//return ; 

			if ( curStatusImage == NULL || newImage == NULL ) 
				return ; 

			return ; 
			if ( newImage != curStatusImage ) 
			{
				//cout << " new image being made! " << endl ; 
				crossFade.fadeImages( newImage , curStatusImage , 0.5 , 0.0f ) ; 
			}

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

		//	cout << status << endl ; 

		return status ; 
	}

};