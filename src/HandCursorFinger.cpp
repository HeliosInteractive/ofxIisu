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
	if ( status > 0 ) 
	{
		ofEnableSmoothing( ) ; 
		ofSetColor ( color ) ; 
		ofCircle( position , radius ) ; 
	}
}