#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

#ifndef MOUSE_DEBUG
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	//Setup IISU server
	iisuServer = new IisuServer() ; 
	iisuServer->setup() ; 

	userRep = IisuUserRepresentation() ; 
	userRep.iisu = iisuServer ; 
	userRep.setup( 160 , 120 , false , true ) ; 
#endif

	Tweenzor::init() ; 
	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 
}

//--------------------------------------------------------------
void testApp::update(){

	Tweenzor::update( ofGetElapsedTimeMillis() ) ; 

	if ( ofGetElapsedTimef() > 6 ) 
	{
		//Make sure that iisu is up and running 
		if ( iisuServer->m_device==NULL || iisuServer->m_iisuHandle==NULL )
		{
			cout << "Iisu is not initialized" <<endl;
			getchar();
			return ; 	
		}

		//Update our user rep
		userRep.update() ; 
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground( 125 , 125 , 125 ) ; 
	
	ofSetColor( 255 , 255 , 255 ) ; 
	userRep.draw( 10 , 10 , 160 , 120 ) ; 
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
	//Some exit code to close out the streams
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