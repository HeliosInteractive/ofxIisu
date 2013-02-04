#include "HandCursorFinger.h"

void HandCursorFinger::setup ( int _id , float _radius , ofColor _color ) 
{
	id = _id ; 
	radius = _radius ; 
	status = 0 ; 
	position = ofVec3f( ) ; 
	color = _color ; 
}

void HandCursorFinger::update ( ) 
{
	
}

void HandCursorFinger::draw ( ) 
{
	float alpha = 15.0f ; 
	if ( status == 1 ) 
		alpha = 120 ; 
	if ( status == 2 ) 
		alpha = 255 ; 
	if ( status > 0 ) 
	{
		ofEnableSmoothing( ) ; 
		ofSetColor ( color , alpha ) ; 
		ofCircle( position , radius ) ; 
	}
}

void HandCursorFinger::debugDraw( ) 
{
	if ( status > 0 ) 
	{
		string fingerStatus = "not active" ; 
		if ( status == 1 ) 
			fingerStatus = "not tracked" ; 
		if ( status == 2 ) 
			fingerStatus = "tracked" ;
		string _status = "# " + ofToString( id ) + " : " + fingerStatus ; 
		//cout << "deubgDraw @ " << position << endl ; 
		ofDrawBitmapStringHighlight( _status , position.x , position.y +- radius * 2.0f ) ; 
	}
}