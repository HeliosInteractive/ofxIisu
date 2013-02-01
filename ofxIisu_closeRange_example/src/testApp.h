#pragma once

#include "ofMain.h"
#include "ofxIisu.h"
#include "HandCursor.h"

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
		IisuServer iisuServer ; 
#endif
		
		HandCursor hand ; 
		//IisuUserRepresentation iisuUserRep ;


};
