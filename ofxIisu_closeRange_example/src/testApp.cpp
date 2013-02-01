#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

#ifndef MOUSE_DEBUG
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	iisuServer = IisuServer() ; 
	iisuServer.setup( true ) ; 
#endif

	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 

	hand = HandCursor() ; 
	hand.setup( &iisuServer , 0 , ofColor::fromHsb( ofRandom( 255 ) , 255 , 255 ) ) ; 

#ifndef MOUSE_DEBUG
	hand.iisu = &iisuServer ; 
#endif 

	iisuUserRep.setup( &iisuServer ) ; 

}

//--------------------------------------------------------------
void testApp::update(){

	hand.update( ) ;
	iisuUserRep.update( ) ; 
}

//--------------------------------------------------------------
void testApp::draw(){

	hand.draw( ) ; 
	iisuUserRep.draw( 15 , 15 , 160 , 120 ) ;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


void testApp::exitEventHandler ( int &exitCode ) 
{
	exit() ; 
}

void testApp::exit( ) 
{
	#ifndef MOUSE_DEBUG
		cout << "testApp::exit" << endl ; 
		// if we have iisu device
		if ( iisuServer.m_device )
		{
			// clear the device pointer
			iisuServer.m_device = NULL;
		}

		// if we have iisu handle
		if ( iisuServer.m_iisuHandle )
		{
			// destroy the iisu handle
			SK::Result res = Context::Instance().destroyHandle( *iisuServer.m_iisuHandle );
			if(res.failed())
			{
				cerr << "Failed to destroy handle!" << endl
					<< "Error " << res.getErrorCode() << ": " << res.getDescription().ptr() << endl;
				getchar();
			}
			// cleat the iisu handle
			iisuServer.m_iisuHandle = NULL;
		}

		// finalize context
		Context::Instance().finalize();
		ofSleepMillis( 5000 ) ; 
	#endif
}