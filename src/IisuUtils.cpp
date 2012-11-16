#include "IisuUtils.h"


ofVec3f IisuUtils::iisuPointToOF( Vector3 point )
{
	ofVec3f vector = ofVec3f( (( point.x +1.0f )/2.0f ) * ofGetWidth() ,ofGetHeight() +- ( ( point.z +1.0f ) /2.0f ) * ofGetHeight() ,  point.y ) ; 
	return vector ; 
}

ofVec3f IisuUtils::iisuPointToOF( Vector3 point , ofVec3f range ) 
{
	ofVec3f vector = ofVec3f( (( point.x +1.0f )/2.0f ) * range.x , ( ( point.z +1.0f ) /2.0f ) * range.y ,  point.y * range.z ) ; 
	return vector ; 
}

ofVec3f IisuUtils::IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofRectangle bounds , bool mirrorX , bool mirrorY )
{
	ofVec3f screenPosition ; 
	float factorX = ( mirrorX == true ) ? -2 : 2 ; 
	float factorY = ( mirrorY == true ) ? -2 : 2 ; 
		
	screenPosition.x = bounds.x + ( ( ( IisuPosition.x + 1 ) / factorX ) * bounds.width );
	screenPosition.y = bounds.y + ( bounds.height -( ( IisuPosition.z + 1 ) / factorY ) * bounds.height ) ; 
	screenPosition.z = IisuPosition.y; 
		
	return screenPosition ;
}

ofVec3f IisuUtils::IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofPoint scale , bool mirrorX , bool mirrorY )
{
	ofVec3f screenPosition ; 
	float factorX = ( mirrorX == true ) ? -1 : 1 ; 
	float factorY = ( mirrorY == true ) ? -1 : 1 ; 
		
	screenPosition.x = ( IisuPosition.x * factorX ) * scale.x ;
	screenPosition.y = ( IisuPosition.z * factorY ) * scale.y ;  
	screenPosition.z = IisuPosition.y * scale.z ; 
		
	return screenPosition ;
}