#pragma once

#include "ofMain.h"

#include "ofxIisu.h"
#include "IisuServer.h"
#include "Tweenzor.h" 
#include "IisuUserRepresentation.h"

//iisuSDK global header (includes all iisu functionalities)
#include <SDK/iisuSDK.h>
#include <iostream>
#include "IisuSkeleton.h"

#include <windows.h>

using namespace SK;
using namespace std;


#include "ofxUI.h"

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

		//Iisu
		IisuServer * iisuServer ; 
		IisuUserRepresentation userRep ; 
		IisuSkeleton iisuSkeleton ; 

		ofxUICanvas *gui;   	
		void guiEvent(ofxUIEventArgs &e);
		bool drawPadding; 



};
