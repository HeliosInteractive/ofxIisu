#pragma once


/*
Written by Ben McChesney
Base


*/
// iisu
#include <SDK/iisuSDK.h>
#include "ofMain.h"
#include "IisuServer.h"

class IisuSkeleton
{
	public : 
		
		IisuSkeleton ( ) { } 
		~IisuSkeleton ( ) { } 
		
		IisuServer * iisu ; 

		bool	m_userManagementEnabled;

		void setup ( ) ; 
		void update ( ) ; 
		void draw ( ) ; 

		bool bTracked ; 
		bool bDebugRender ; 

		ofRectangle bounds ;
		ofVec3f centroid ; 
		bool bFlipX , bFlipY ; 
};