#pragma once


#include "IisuServer.h" 
#include "ofMain.h" 

//Still working on the openCV stuff
//#include "ofxOpenCv.h"

#include "ofThread.h"

static ofMutex myMutex ;

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
		virtual ~IisuUserRepresentation( ) { } 

		
		IisuServer * iisu ; 
		
		ofImage sceneImage ; 
		ofImage userImage ; 

		unsigned char rawPixels[120 * 160];
		unsigned char grayPixels[120 * 160];

		int lastUserID ; 

		string status ; 
		string instructions ; 

		int lastFrame ; 
		
		int minMappedBrightness ; 
		int maxMappedBrightness ; 

		int pPointerStatus ; 
 
		//OpenCV to get vector outlines
		//ofxCvGrayscaleImage 	grayImage;
		//ofxCvContourFinder 		contourFinder;
		
		int imageWidth , imageHeight ; 

		void setup ( IisuServer * _iisu , int _w = 160 , int _h = 120 ) 
		{
			imageWidth = _w ; 
			imageHeight = _h ; 
			iisu = _iisu ; 
			pPointerStatus = -3 ; 
			lastFrame= -4 ; 
			sceneImage.allocate( imageWidth , imageHeight , OF_IMAGE_GRAYSCALE ) ; 
			userImage.allocate ( imageWidth , imageHeight , OF_IMAGE_GRAYSCALE ) ; 

			//grayImage.allocate( imageWidth , imageHeight );
			//grayImage.setUseTexture( false ) ; 
			lastUserID = 0 ; 
		
			minMappedBrightness = 1 ; 
			maxMappedBrightness = 255 ; 
		}

		void update ( ) 
		{
//			getStatusString( iisu->m_pointerStatus ) ; 
			//cout << "iisu user rep update! " << endl ; 

			if ( iisu->sceneImageHandle.isValid() == 1 )
			{

				cout << "VALID! " << endl ;
				int totalPixels = imageWidth * imageHeight ;

				//Awesomely added by Andy Warner
				unsigned char * pRawPixels = iisu->sceneImage.getRAW() ; 
				memcpy(rawPixels, pRawPixels, totalPixels);

				int userValue = iisu->user1SceneID ; 
				
				sceneImage.setFromPixels( rawPixels, sceneImage.width , sceneImage.height , OF_IMAGE_GRAYSCALE , true ) ;
				sceneImage.mirror( false , true ) ; 

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

				userImage.setFromPixels( rawPixels, sceneImage.width , sceneImage.height , OF_IMAGE_GRAYSCALE , true ) ;
				userImage.mirror( false , true ) ; 
	
				if ( userValue != lastUserID ) 
				{
					lastUserID = userValue ; 
				}


			//	int totalPixels = imageWidth * imageHeight ;
			//memcpy(grayPixels , rawPixels, totalPixels );
				//mutex.lock( ) ; 
			//grayImage.setFromPixels( rawPixels ,  sceneImage.width , sceneImage.height ) ; 
			//grayImage.mirror( false , true ) ; 
			//grayImage.blurGaussian( 11 ) ;
			//grayImage.flagImageChanged();
			//contourFinder.findContours( grayImage, 100 , (imageWidth*imageHeight)/3, 1 , true , true );	// find holes
					
			}
		}


		void drawVectorUserRep ( float x , float y , float width , float height , float simplify  ) 
		{
			ofPushMatrix() ; 
				ofPushStyle() ; 
				ofTranslate( x , y ) ; 
				
				/*
				if ( contourFinder.nBlobs > 0 ) 
				{
					ofNoFill ( ) ; 
					int nBlobs = contourFinder.blobs.size() ; 
					vector<ofxCvBlob>  blobs = contourFinder.blobs ; 
					ofRectangle bounds ; 

					for( int i=0; i< nBlobs ; i++ ) {

						bounds = blobs[i].boundingRect ; 
					}
					
					float xRatio = bounds.x / imageWidth ; 
					float yRatio = bounds.y / imageHeight ; 
					float wRatio = bounds.width / imageWidth ; 
					float hRatio = bounds.height / imageHeight ; 

		
					ofPath path ; 
					float userRepAlpha = 80 ; 
					path.setFillColor( ofColor( 0 , 0 , 0 , userRepAlpha ) ) ; 
					path.setStrokeColor( ofColor ( EmiratesGlobal::Instance()->EMIRATES_RED ,  255 ) ) ;
					path.setStrokeWidth( 4 ) ; 

					//Convert all openCV points to normalized coordinates within the texture,
					//this is done so we can scale the points position and place them larger on the screen.

					for( int i=0; i< nBlobs ; i++ ) {
						ofNoFill();
				
						vector<ofPoint> normalizedPoints ; 
						
						for( int j=1; j<blobs[i].nPts; j++ )
						{
							ofPoint p = ofPoint ( blobs[i].pts[j].x, blobs[i].pts[j].y  ) ; 

							p.x /= imageWidth ;  
							p.y /= imageHeight ; 
							normalizedPoints.push_back( p ) ; 
						}
					}


						//>>>>>>>>>>>>>>>>>>>>>>>BEGIN
					//ofPath outlinePath ; 
					ofPolyline line ; 
					//ofPath path ; 

						for( int i=0; i< nBlobs ; i++ ) {
						ofNoFill();

						vector<ofPoint> normalizedPoints ; 

						for( int j=1; j<blobs[i].nPts; j++ )
						{
							ofPoint p = ofPoint ( blobs[i].pts[j].x, blobs[i].pts[j].y  ) ; 

							p.x /= imageWidth ;  
							p.y /= imageHeight ; 
							normalizedPoints.push_back( p ) ; 
						}

						for( int i = 0 ; i < normalizedPoints.size() ; i++ )
						{
							//ofPoint nPoint1 = normalizedPoints[ i - 1 ] ; 
							ofPoint nPoint1 = normalizedPoints[ i ] ; 
							nPoint1.x *= width ; 
							nPoint1.y *= height ; 
							//nPoint2.x *= width ; 
							//nPoint2.y *= height ; 

							//ofPoint mid = ( nPoint1 + nPoint2 ) / 2 ;  
						//	line.bezierTo( nPoint1 , nPoint2 , mid , 16 ) ; 
							line.lineTo( nPoint1.x , nPoint1.y  ) ;   
						}

						line.close( ) ; 
						//line.close( ) ;
						

					}
				
					
					ofSetColor ( EmiratesGlobal::Instance()->EMIRATES_RED , 165 ) ; 
					ofSetLineWidth( 6 ) ; 
					ofFill ( ) ; 
			
					ofPushMatrix( ) ;
						line.getSmoothed( simplify ).draw( ) ;
					ofPopMatrix( ) ; 
					glPopMatrix();
					ofPopStyle();
						
				}*/
				ofPopStyle( ) ; 

			ofPopMatrix() ; 
		}

		void draw ( float x , float y , float width , float height ) 
		{
			ofEnableAlphaBlending() ; 
			ofPushMatrix() ; 

				ofSetColor ( 255 , 255 , 255 ) ;
				ofPushStyle() ; 
				//ofEnableBlendMode( OF_BLENDMODE_ADD ) ; 
				ofSetColor( 255 , 255 , 255 ) ; 
					ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ; 
						sceneImage.draw ( x , y , width , height ) ;
					ofDisableBlendMode( ) ; 
				ofPopStyle() ;

			ofPopMatrix() ; 
		}

};