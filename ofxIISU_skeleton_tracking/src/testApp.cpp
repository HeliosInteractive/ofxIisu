#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

#ifndef MOUSE_DEBUG
	ofAddListener ( IisuEvents::Instance()->exitApplication , this , &testApp::exitEventHandler ) ; 

	//Setup IISU server
	iisuServer = new IisuServer() ; 
	iisuServer->setup() ; 
	iisuServer->initIisu() ; 

	userRep = IisuUserRepresentation() ; 
	userRep.iisu = iisuServer ; 
	userRep.setup( ) ; 

	iisuSkeleton.iisu = iisuServer ; 
	iisuSkeleton.setup( ) ; 

#endif

	Tweenzor::init() ; 
	ofSetVerticalSync( true ) ; 
	ofSetFrameRate( 60 ) ; 

	//hand = HandCursor() ; 
	//hand.setup( ) ; 

#ifndef MOUSE_DEBUG
	//hand.iisu = &iisuServer ; 
#endif

	float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 

    drawPadding = false; 
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());

    gui->addWidgetDown(new ofxUILabel("IISU SKELETON PARAMETERS", OFX_UI_FONT_LARGE));         
	//gui->addWidgetDown(new ofxUILabel("NORMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0 , ofGetWidth() * 2 ,  iisuSkeleton.bounds.x , "BOUNDS X")); 
	gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0 , ofGetWidth() * 2 ,  iisuSkeleton.bounds.y , "BOUNDS Y")); 
	gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0 , ofGetWidth() ,  iisuSkeleton.bounds.width , "BOUNDS WIDTH")); 
	gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0 , ofGetWidth() ,  iisuSkeleton.bounds.height , "BOUNDS HEIGHT")); 
	gui->addWidgetDown(new ofxUILabelToggle( iisuSkeleton.bFlipX, "FLIP X", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUILabelToggle( iisuSkeleton.bFlipY, "FLIP Y", OFX_UI_FONT_MEDIUM)); 

	ofAddListener( gui->newGUIEvent,this,&testApp::guiEvent );	

	gui->loadSettings( "GUI/iisuSkeleton.xml" ) ; 

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

		iisuSkeleton.update ( ) ; 
		userRep.update() ; 
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground ( 125 , 125 , 125 ) ; 
	ofSetColor( 255 , 255 , 255 ) ; 
	userRep.draw( ofGetWidth() - 170 , ofGetHeight() - 130 , 160 , 120 ) ; 

	ofSetColor ( 255 , 255 , 255 ) ;
	iisuSkeleton.draw( ) ;
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 

	if(name == "BOUNDS X" )
	{
		iisuSkeleton.bounds.x = ((ofxUISlider *) e.widget)->getScaledValue() ; 
	}

	if(name == "BOUNDS Y" )
	{
		iisuSkeleton.bounds.y = ((ofxUISlider *) e.widget)->getScaledValue() ; 
	}

	if(name == "BOUNDS WIDTH" )
	{
		iisuSkeleton.bounds.width = ((ofxUISlider *) e.widget)->getScaledValue() ; 
	}

	if(name == "BOUNDS HEIGHT" )
	{
		iisuSkeleton.bounds.height = ((ofxUISlider *) e.widget)->getScaledValue() ; 
	}

	if(name ==  "FLIP X" )
	{
		iisuSkeleton.bFlipX = ((ofxUILabelToggle *) e.widget)->getValue() ; 
	}

	if(name ==  "FLIP Y" )
	{
		iisuSkeleton.bFlipY = ((ofxUILabelToggle *) e.widget)->getValue() ; 
	}

	gui->saveSettings( "GUI/iisuSkeleton.xml" ) ; 

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