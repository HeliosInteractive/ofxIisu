#pragma once

#include <SDK/iisuSDK.h>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

using namespace SK;
using namespace std;

#include "ofMain.h" 

class IisuUtils 
{
	public : 
		
		IisuUtils( ) { } 

		//Universal access to the same event type
		static IisuUtils* Instance()
        {
            static IisuUtils inst;
            return &inst;
        }


		ofVec3f iisuPointToOF( Vector3 point ) ; 
		ofVec3f iisuPointToOF( Vector3 point , ofVec3f range ) ; 
		ofVec3f IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofPoint scale , bool mirrorX = false , bool mirrorY = false ) ; 
		ofVec3f IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofRectangle bounds , bool mirrorX = false , bool mirrorY = false ) ; 

};