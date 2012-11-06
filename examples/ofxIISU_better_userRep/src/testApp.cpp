#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

#ifndef MOUSE_DEBUG
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	//Setup IISU server
	iisuServer = new IisuServer() ; 
	iisuServer->setup() ; 
	iisuServer->initIisu( ) ; 
	
	userRep = IisuUserRepresentation() ; 
	userRep.iisu = iisuServer ; 
	userRep.setup( ) ; 

	depthCursor.setup( iisuServer , 0 ) ; 

#endif

	Tweenzor::init() ; 
	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 
	ofBackground( 128 ); 

	//hand = HandCursor() ; 
	//hand.setup( ) ; 

#ifndef MOUSE_DEBUG
	//hand.iisu = &iisuServer ; 
#endif

}

//--------------------------------------------------------------
void testApp::update(){

	Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
	
	if ( ofGetElapsedTimef() > 6.0f ) 
	{
		if ( iisuServer->m_device==NULL || iisuServer->m_iisuHandle==NULL )
		{
			cout << "Iisu is not initialized" <<endl;
			getchar();
			return ; 
		}
		depthCursor.update( ) ; 
		userRep.update() ; 
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground( 128 ); 
	ofSetColor( 255 , 255 , 255 ) ; 
	userRep.draw( 25 , 25 , 320 , 240 ) ; 
	depthCursor.draw( ) ; 
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
	/*
	#ifndef MOUSE_DEBUG
		cout << "testApp::exit" << endl ; 
		// if we have iisu device
		if ( iisuServer->m_device )
		{
			// clear the device pointer
			iisuServer->m_device = NULL;
		

		// if we have iisu handle
		if ( iisuServer->m_iisuHandle )
		{
			// destroy the iisu handle
			SK::Result res = Context::Instance().destroyHandle( *iisuServer->m_iisuHandle );
			if(res.failed())
			{
				cerr << "Failed to destroy handle!" << endl
					<< "Error " << res.getErrorCode() << ": " << res.getDescription().ptr() << endl;
				getchar();
			}
			// cleat the iisu handle
			iisuServer->m_iisuHandle = NULL;
		}

		// finalize context
		Context::Instance().finalize();
		ofSleepMillis( 5000 ) ; 
	#endif*/
}