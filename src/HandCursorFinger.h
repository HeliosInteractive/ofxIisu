#pragma once

#include "ofMain.h"

class HandCursorFinger
{
public :
	HandCursorFinger() { } 
	~HandCursorFinger() { } 


	void setup ( int _id , float _radius , ofColor _color ) ; 
	void update ( ) ; 
	void draw ( ) ; 


	int id ; 
	int status ; 
	ofVec3f position ; 
	float radius ;
	ofColor color ;
};