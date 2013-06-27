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

		void setup ( int _w = 160 , int _h = 120 ) ;
		void update ( ) ;
		void drawVectorUserRep ( float x , float y , float width , float height , float simplify  ) ;
		void draw ( float x , float y , float width , float height ) ;
			
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

		
		
};