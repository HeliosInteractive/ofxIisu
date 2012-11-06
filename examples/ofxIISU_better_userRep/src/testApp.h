#pragma once

#include "ofMain.h"

#include "ofxIisu.h"
#include "IisuServer.h"
#include "Tweenzor.h" 
#include "IisuUserRepresentation.h"
#include "DepthCursor.h"

#ifndef MOUSE_DEBUG
//iisuSDK global header (includes all iisu functionalities)
#include <SDK/iisuSDK.h>
#include <iostream>
#endif

#ifdef WIN32
#include <windows.h>
#endif

#ifndef MOUSE_DEBUG
using namespace SK;
using namespace std;
#endif

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void exit();
		void exitEventHandler ( int &exitCode ) ; 

#ifndef MOUSE_DEBUG
		//Iisu
		IisuServer * iisuServer ; 
		IisuUserRepresentation userRep ; 

		DepthCursor depthCursor ; 
#endif



};
