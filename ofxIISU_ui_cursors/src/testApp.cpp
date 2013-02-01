#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	bDrawDebug = false ; 
#ifndef MOUSE_DEBUG
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	//Setup IISU server
	iisuServer = new IisuServer() ; 
	iisuServer->setup() ; 

	cursor0.setup( iisuServer , iisuServer->addController() , ofColor( 0 , 255 , 0 ) ) ; 
	cursor1.setup( iisuServer , iisuServer->addController() , ofColor( 0 , 0 , 255 ) ) ; 

	iisuServer->initIisu() ; 
#endif

	Tweenzor::init() ; 
	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 
	ofBackground( 45 ); 

}

//--------------------------------------------------------------
void testApp::update(){

	ofSetWindowTitle( "FPS:" + ofToString( ofGetFrameRate() ) ) ; 
	Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
		
	if ( iisuServer->m_device==NULL || iisuServer->m_iisuHandle==NULL )
	{
		cout << "Iisu is not initialized" <<endl;
		//getchar();
		return ; 
	}

	cursor0.update( ) ; 
	cursor1.update( ) ; 



}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground( 128 ); 
	ofSetColor( 255 , 255 , 255 ) ; 

	cursor0.draw( ) ; 
	cursor1.draw( ) ; 
	

	if ( bDrawDebug == true ) 
	{
		cursor0.debugDraw( ) ;
		cursor1.debugDraw( ) ;
	}

	ofDrawBitmapString ( "'D' to toggle debug mode" , 25 , 25 ) ; 

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch ( key ) 
	{
		case 'd':
		case 'D':
			bDrawDebug = !bDrawDebug ; 
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
				cout << "Failed to destroy handle!" << endl
					<< "Error " << res.getErrorCode() << ": " << res.getDescription().ptr() << endl;
				//getchar();
			}
			// cleat the iisu handle
			iisuServer->m_iisuHandle = NULL;
		}

		// finalize context
		Context::Instance().finalize();
		ofSleepMillis( 5000 ) ; 
	#endif
	*/
}