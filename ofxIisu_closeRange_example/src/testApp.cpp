#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	iisuServer = IisuServer() ; 
	iisuServer.setup( true ) ; 

	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 

	hand = HandCursor() ; 
	hand.setup( &iisuServer , 0 , ofColor::fromHsb( ofRandom( 255 ) , 255 , 255 ) ) ; 

	hand.iisu = &iisuServer ; 
	bEnableDebug = false ; 

}

//--------------------------------------------------------------
void testApp::update(){

	if ( iisuServer.m_device==NULL || iisuServer.m_iisuHandle==NULL)
	{
		cout << "Iisu is not initialized !!" <<endl;
		return ; 
	}

	hand.update( ) ;
	ofSetWindowTitle( "ofxIisu CloseRange Example - fps - " + ofToString( ofGetFrameRate() ) ) ; 
	//iisuUserRep.update( ) ; 
}

//--------------------------------------------------------------
void testApp::draw(){

	hand.draw( ) ; 
	if ( bEnableDebug == true ) 
		hand.debugDraw() ; 

	string debugCTA = "hit D to toggle debug drawing" ; 
	ofDrawBitmapStringHighlight ( debugCTA , 25 , ofGetHeight() - 45 ) ; 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch ( key ) 
	{
		case 'd':
		case 'D':
			bEnableDebug = !bEnableDebug ; 
			cout << "bDebugEnabled is now : " << bEnableDebug << endl ; 
			break ;
	}
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
			cout << "Failed to destroy handle!" << endl
				<< "Error " << res.getErrorCode() << ": " << res.getDescription().ptr() << endl;
		}
		// cleat the iisu handle
		iisuServer.m_iisuHandle = NULL;
	}

	// finalize context
	Context::Instance().finalize();
	//Leave the final readout on for 10 seconds in case there's an error
	ofSleepMillis( 10000 ) ; 
}