#include "IisuSkeleton.h"
#include "ofQuaternion.h"
#include "Tweenzor.h"
#include "EmiratesGlobal.h"

//#define USE_LIGHTING 2
//#define TENNIS_BALL 3 
//#define RED_AND_WHITE 4 
#define FILLED 9

void IisuSkeleton::setup ( )
{
	racketTweenTime = 0.5f ; 
	ballServeYOffset = 50.0f ; 

	combinedHitColor = ofColor ( 255 , 0 , 255 ) ; 
//	bAutomateServe = false; 
	bDebug = false ; 
	centroidLerpAmount = 0.5f ; 
	bDebug = false ; 
	bTrackBall = false ; 
	numServes = 0 ; 
	bTracked  = false ;  
	bDebugRender = true  ;
	bounds = ofRectangle ( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
	bFlipX = false ; 
	bFlipY = false ;

	minRacketRotation = 0 ; 
	maxRacketRotation = 360 ; 

	//Specific
	bCalibrateHand = true ;
	lastThresholdCross = -1 ; 
	bRightHanded = false ; 
	bHandTracked = false ; 
	calibrationStatus = 0.0f ;
	serveCalibrationStatus = 0.0f ;
	lastServeCross = -1 ; 

	bTrackServe = false ; 
	bTrackServeComplete = false ; 
	ballAlpha = 0 ; 
	nCentroids = 0 ; 

	zRange = 0.0f ; 
	// we need GL_TEXTURE_2D for our models coords.
    //ofDisableArbTex();
	//tennis_racket.tennis_racket
    //if( model.loadModel("3d/tennis_racket.dae",true)){
	  if( model.loadModel("3d/tennis_racket.obj",true)){
    	model.setAnimation(0);
    	model.setPosition( 0 , 0 , 0);

    	mesh = model.getMesh(0);
    	position = ofVec3f( ) ; //model.getPosition();
    	normScale = model.getNormalizedScale();
    	scale = model.getScale();
		cout << "model scale : " << scale << endl ; 
		model.setScale( 2 , 2 , 2 ) ; 
		//model.setScale
    	sceneCenter = model.getSceneCenter();
		cout << "scene center : " << sceneCenter.x << " , " << sceneCenter.y << " , " << sceneCenter.z << " , " << endl ; 
    	material = model.getMaterialForMesh(0);
        tex = model.getTextureForMesh(0);
    }

	if ( ballModel.loadModel( "3d/tennis_ball.dae" , true ) )
	{
		ballModel.setAnimation( 0 ) ; 
		ballModel.setPosition ( 0 ,0 ,0 );
		ballMesh = ballModel.getMesh( 0 ) ;
	    ballMaterial = model.getMaterialForMesh(0);
        ballTexture = model.getTextureForMesh(0); 
		ballMaterial.setShininess( 0.1f ) ; 

		int color_ambient = 255 ; 
		ballMaterial.setAmbientColor( ofColor( color_ambient , color_ambient , color_ambient ) ) ; \

		//ballMaterial.set
	//	ballMaterial.setDiffuseColor( ofColor( 255 , 255 , 255 ) ) ;
	}

	tennisBallColor = ofColor( 255 , 255 , 255 ) ;  
	glEnable(GL_DEPTH_TEST);
	tennisColorLerp = 0 ; 
    //some model / light stuff
	glShadeModel(GL_SMOOTH);

	/*
	InstructionsData beginData ; 
	beginData.set( "instructionsData" , "instructions/01.png" ) ; 
	beginInstructionsHandle = Instructions::Instance()->addData( beginData ) ; 
	*/

	InstructionsData handTrackData ; 
	handTrackData.set( "handTrackData" , "instructions/02.png" ) ; 
	handTrackInstructionsHandle = Instructions::Instance()->addData( handTrackData ) ; 

	InstructionsData raiseBallData ; 
	raiseBallData.set( "raiseBallData" , "instructions/03.png" ) ; 
	raiseBallInstructionsHandle = Instructions::Instance()->addData( raiseBallData ) ; 

	//fbo.allocate( ofGetWidth() , ofGetHeight() ) ; 

	// turn on smooth lighting //
    ofSetSmoothLighting(true);

	  // lets make a sphere with more resolution than the default //
    // default is 20 //
    ofSetSphereResolution(20);

	// set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor( ofColor(255.0f , 255.0f , 255.0f ));
    
    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    //
	pointLight.setPosition( lightPosition );
	
	specularAlpha = 125 ; 
	ambientAlpha = 125 ; 
	shininess = 12 ; 
	ofColor lightColor = ofColor ( 255 , 255 , 255 ) ;
    sphereMaterial.setShininess( shininess ) ; 
	sphereMaterial.setSpecularColor( ofColor( 255 , 255 , 255 , specularAlpha ) ) ; 
	sphereMaterial.setAmbientColor( ofColor( 255 , 255 , 255 , ambientAlpha ) ) ; 
	sphereRadius = 15 ;	

}



void IisuSkeleton::transitionIn ( ) 
{
	//bAutomateServe = false ; 
	bTrackBall = false ;
	Tweenzor::add ( &ballAlpha , ballAlpha , 255.0f, 0.0f , 0.5f , EASE_OUT_QUAD ) ; 
	//numServes = 0 ; 
	Tweenzor::add( &alpha , alpha , 1.0f , 0.0f , 0.5 , EASE_OUT_QUAD ) ; 

	bTracked  = false ;  
	bCalibrateHand = false ;
	lastThresholdCross = -1 ; 
	bRightHanded = false ; 
	//thresholdCrossDuration = 8.0 ; 
	bHandTracked = false ; 
	calibrationStatus = 0.0f; 
	lastServeCross = -1 ; 
	bTrackServe = false ; 
	bTrackServeComplete = false ; 

	//Specific
	bCalibrateHand = true ;
	lastThresholdCross = -1 ; 
	bRightHanded = false ; 
	bHandTracked = false ; 
	calibrationStatus = 0.0f ;
	serveCalibrationStatus = 0.0f ;
	lastServeCross = -1 ; 

	bTrackServe = false ; 
	bTrackServeComplete = false ; 

	ballAlpha = 0 ; 
}

void IisuSkeleton::setCentroids ( int _newCentroids ) 
{
	lerpCentroids.clear( ) ; 
	iisu->m_centroidCountParameter.set( _newCentroids ) ; 
}

void IisuSkeleton::transitionOut ( ) 
{
	//numServes = 0 ; 
	//Tweenzor::add( &alpha , alpha , 0.0f , 0.0f , 0.5 , EASE_OUT_QUAD ) ; 
	//Tweenzor::add( &ballAlpha , ballAlpha , 0.0 , 0.0f , 0.5f , EASE_OUT_QUAD) ; 
}

 
void IisuSkeleton::update ( ) 
{
	//if ( ofGetElapsedTimef() < 5.0f ) 
	//	return ; 

	if ( alpha < .98 ) return ; 
	//return ; 

	isTracked = iisu->m_skeletonStatus ; 
	//cout << "isTracked : " << isTracked << endl ; 
	if ( isTracked != 0 ) 
	{		
		nCentroids = iisu->m_centroidCount ; 

		//ofNotifyEvent( Instructions::Instance()->CHANGE_INSTRUCTION , beginInstructionsHandle ) ; 
		SK::Array<SK::Vector3> keyPoints = iisu->m_keyPoints ; 		
		SK::Array<float> keyPointsConfidence = iisu->m_keyPointsConfidence ; 

		rawCentroid = ofVec3f ( keyPoints[SK::SkeletonEnum::WAIST ].x , keyPoints[SK::SkeletonEnum::WAIST ].y , keyPoints[SK::SkeletonEnum::WAIST ].z )  ; 
		centroid = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::WAIST ] , bounds , bFlipX , bFlipY ) ;  
		centroid *= zRange ; 
		//Get our two hands
		ofVec3f rightHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::RIGHT_WRIST ] , bounds , bFlipX , bFlipY ) ; 
		ofVec3f leftHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::LEFT_WRIST ] , bounds , bFlipX , bFlipY ) ; 
		//And a point to test against
		ofVec3f collar = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::COLLAR ] , bounds , bFlipX , bFlipY ) ;
	//	ofVec3f head = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::COLOR ] ,bounds , bFlipX , bFlipY ) ; 
		if ( bHandTracked == false ) 
		{

			if ( rightHand.y > collar.y || leftHand.y > collar.y ) 
			{

				
				if ( lastThresholdCross < 0.0f ) 
				{
					lastThresholdCross = ofGetElapsedTimef() ;
					//cout << "ABOVE THE FOLD!" << endl ; 
				}
				float adjustedMax = lastThresholdCross + thresholdCrossDuration ; 
				float adjutededCurrent = ofGetElapsedTimef() - lastThresholdCross ; 
				calibrationStatus = ofMap( ofGetElapsedTimef() , lastThresholdCross , lastThresholdCross + thresholdCrossDuration , 0.0f , 1.0f , true ) ; 


				if ( ofGetElapsedTimef() > ( lastThresholdCross + thresholdCrossDuration ) )
				{
					/*
					ofVec3f tweenRacketPosition ;
					ofVec3f tweenBallPosition ; 
					float minimumHandConfidence ; 
					*/

					if ( rightHand.y > leftHand.y ) 
					{
						bRightHanded = true ; 
						tweenRacketPosition = rightHand ; 
						tweenBallPosition = leftHand ; 
					}
					else
					{
						bRightHanded = false ; 
						tweenRacketPosition = leftHand ; 
						tweenBallPosition = rightHand ; 
					}	
				
					bHandTracked = true ; 
					calibrationStatus = 0.0f ; 
					//cout << "HAND IS LOCKED ON!" << endl ; 
					//Set page to go to stadium
					cout << "SHOULD BxE SENDING CALIBRATED EVENT!" << endl ;
					bTrackBall = true ; 
					ofNotifyEvent( Instructions::Instance()->CHANGE_INSTRUCTION , handTrackInstructionsHandle ) ;  
					int args = 2 ; 
					ofNotifyEvent ( IisuEvents::Instance()->HAND_CALIBRATED , args ) ;

					//IisuSkeleton::Instance()->minRacketRotation
				}
			}
			else
			{
				if ( lastThresholdCross > 0 ) 
				{
					calibrationStatus = 0.0f; 
					lastThresholdCross = -1 ; 
				}
			}					
		}
		else
		{

			if ( bTrackServeComplete == false && secondaryHand.y > collar.y ) 
			{
				bTrackServe = true ; 
			}

			//cout << "we have a dominant hand tracked" << endl ; 
			if ( secondaryHand.y > collar.y && bTrackServe == true ) 
			{
				if ( lastServeCross < 0 ) 
					lastServeCross = ofGetElapsedTimef() ; 
		
				if ( ofGetElapsedTimef() > ( lastServeCross + serveThresholdDuration ) )
				{
					lastServeCross = -1 ; 
					bTrackServeComplete = true ; 
					bTrackServe = false ; 
					servePosition = secondaryHand ; 
					bTrackServeComplete = true ; 
					Tweenzor::add( &tennisColorLerp , 0.0f , 1.0f , 0.0f , 1.0f , EASE_OUT_QUAD ) ; 
					Tweenzor::add( &ballAlpha , 0.0f , 255.0f , 0.0f , 0.5f , EASE_OUT_QUAD) ;
					bTrackBall = false ; 
					Tweenzor::addCompleteListener( Tweenzor::getTween( &tennisColorLerp ) , this , &IisuSkeleton::loopStart ) ; 
					//if ( numServes == 0 ) 
						ofNotifyEvent( Instructions::Instance()->CHANGE_INSTRUCTION , raiseBallInstructionsHandle ) ; 

					//This was way off before !
					Tweenzor::add( &servePosition.x , servePosition.x , collar.x , 0.0f , 0.4f , EASE_OUT_QUAD ) ; 
					Tweenzor::add( &servePosition.y , servePosition.y , collar.y + ballServeYOffset + 150.0f , 0.0f , 0.3f , EASE_OUT_QUAD ) ; 
					Tweenzor::addCompleteListener( Tweenzor::getTween( &servePosition.y ) , this , &IisuSkeleton::serveBallYComplete ) ; 
					//endY = collar.y + ballServeYOffset ; 

					Tweenzor::add( &servePosition.z , servePosition.z , collar.z , 0.0f , 0.4f , EASE_OUT_QUAD ) ; 
				}

				serveCalibrationStatus = ofMap ( ofGetElapsedTimef() , lastServeCross , lastServeCross + serveThresholdDuration , 0 , 1.0f , false ) ;  
			}
			else
			{
				lastServeCross = -2 ; 
			}

			centroid = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::WAIST ] , bounds , bFlipX , bFlipY ) ; 
			centroid *= zRange ; 
		}
		
		//ofSetColor ( 255 , 0 , 0 , 255 * keyPointsConfidence[i] ) ; 
		//ofVec2f p = iisu->IIsuPosition3DToOfxScreen( keyPoints[i] , bounds , bFlipX , bFlipY ) ; 
		//ofCircle(  p , 15 ) ; 

	}
	else
	{
		
		bTracked  = false ;  
		bCalibrateHand = false ;
		lastThresholdCross = -1 ; 
		bRightHanded = false ; 
		//thresholdCrossDuration = 8.0 ; 
		bHandTracked = false ; 
		calibrationStatus = 0.0f; 
		lastServeCross = -1 ; 
		bTrackServe = false ; 
		bTrackServeComplete = false ; 
		
#ifdef DEBUG_STADIUM
	numServes = 0 ; 
#endif

		if ( alpha > 0 ) 
		{
		//	ofNotifyEvent( Instructions::Instance()->CHANGE_INSTRUCTION , beginInstructionsHandle ) ; 
		}
	}
}

float endY ; 

void IisuSkeleton::serveBallYComplete ( float * args ) 
{
	Tweenzor::add( &servePosition.y , servePosition.y , headPosition.y , 0.0f , ballFallTime ) ;  
	Tweenzor::addCompleteListener( Tweenzor::getTween( &servePosition.y ) , this , &IisuSkeleton::ballFallComplete ) ; 
}

void IisuSkeleton::ballFallComplete ( float * args ) 
{
	/* ballFallComplete */
	Tweenzor::add( &servePosition.x , servePosition.x , secondaryHand.x , 0.0f , 0.35f , EASE_OUT_QUAD ) ;
	Tweenzor::add( &servePosition.y , servePosition.y , secondaryHand.y , 0.0f , 0.35f , EASE_OUT_QUAD ) ;
	Tweenzor::add( &servePosition.z , servePosition.z , secondaryHand.z , 0.0f , 0.35f , EASE_OUT_QUAD ) ;
	Tweenzor::addCompleteListener( Tweenzor::getTween( &servePosition.x ) , this , &IisuSkeleton::ballResetToHandComplete ) ; 
	cout << "BALL WAS NOT HIT OBVIOUSLY !!!!! " << endl ;
}

void IisuSkeleton::ballResetToHandComplete( float * args ) 
{
	cout << "total ball reset! " << endl ; 
	bTrackServeComplete = false ; 
	bTrackServe = true ; 
	lastServeCross = -2 ; 
	bTrackBall = true ; 
}

void IisuSkeleton::rotateToNormal(ofVec3f normal) {
	normal.normalize();
	
	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;
	
	ofVec3f axis( 0, 0, 1 );
	rotation.makeRotate( axis, normal );
	rotation.getRotate( rotationAmount , rotationAngle );
	ofRotate( rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z );
}

void IisuSkeleton::loopStart ( float * args )
{
	Tweenzor::add( &tennisColorLerp , 1.0f , 0.0f , 0.0f , 0.5f , EASE_IN_QUAD ) ; 
	Tweenzor::addCompleteListener( Tweenzor::getTween( &tennisColorLerp ) , this , &IisuSkeleton::loopEnd ) ; 
}

void IisuSkeleton::loopEnd ( float * args ) 
{
	if ( bTrackServeComplete == true ) 
	{
		Tweenzor::add( &tennisColorLerp , 0.0f , 1.0f , 0.0f , 0.2f , EASE_OUT_QUAD ) ; 
		Tweenzor::addCompleteListener( Tweenzor::getTween( &tennisColorLerp ) , this , &IisuSkeleton::loopStart ) ; 
	}
}

void IisuSkeleton::setLightPosition ( ) 
{
	//
	pointLight.setPosition ( lightPosition ) ; 
}
ofVec3f orientationAngle ; 

void IisuSkeleton::drawFBO( )
{
}

void IisuSkeleton::drawUserRepBubbles ( ) 
{

	bool isTracked = iisu->m_skeletonStatus ; 
	//cout << "isTracked : " << isTracked << endl ; 
	if ( isTracked != 0 ) 
	{	
		SK::Array<SK::Vector3> mPositions = iisu->m_centroidPositions ; 
		SK::Array<int> mJumpStatus = iisu->m_centroidJumpStatus ; 
#ifdef USE_LIGHTING
		//Draw ze bubble man !
		 ofSetSmoothLighting(true);
		ofEnableLighting( ) ; 
		pointLight.enable( ) ; 
		sphereMaterial.begin( ) ;
#endif
		
		#ifdef TENNIS_BALL 
			ofSetColor( 223 , 225 , 0 ) ; 
		#endif

		#ifdef FILLED
			ofSetColor( 255 , 255 , 255 ) ; 
		#endif

		//bAutomatedServe
		int nCentroids = iisu->m_centroidCount ; 
		if ( nCentroids != lerpCentroids.size() ) 
		{
			cout << "IISU CENTROIDS : " << nCentroids << " : myCentroids : " << lerpCentroids.size() << endl ; 
			lerpCentroids.clear( ) ; 
		}	
		//cout << "# centroids : " << nCentroids << endl ; 
		if ( nCentroids > 0 ) 
		{

			if ( lerpCentroids.size() > 0 ) 
			{
				//CENTROIDS HAVE BEEN RETREIVED

				for ( int i = 0 ; i < nCentroids ; i++ ) 
				{

				//#ifdef RED_AND_WHITE
					//if ( i % 2 == 0 ) 
					//	ofSetColor ( EmiratesGlobal::Instance()->EMIRATES_RED ) ; 
					//else
						ofSetColor( 255 , 255 , 255 ) ; 
				//#endif
					ofVec3f point = iisu->IIsuPosition3DToOfxScreen( mPositions[i] , bounds , bFlipX , bFlipY ) ;
					point.z *= zRange ; 
					int timeInterpolateStatus = mJumpStatus[ i ] ; 
					if ( timeInterpolateStatus == 0 ) 
					{
						//Same CENTROID
						ofVec3f newPoint = lerpCentroids[i].interpolate( point , centroidLerpAmount ) ; 
						//Tweenzor::add ( &lerpCentroids[ i ].x , lerpCentroids[ i ].x , point.x , 0.001 , EASE_OUT_QUAD ) ; 
						//Tweenzor::add ( &lerpCentroids[ i ].y , lerpCentroids[ i ].y , point.y , 0.001 , EASE_OUT_QUAD ) ; 
						//sTweenzor::add ( &lerpCentroids[ i ].z , lerpCentroids[ i ].z , point.z , 0.00 1 , EASE_OUT_QUAD ) ; 
					}
					if ( timeInterpolateStatus == 1 ) 
					{
						//CENTROID HAS JUMPED ! Just set it
						lerpCentroids[ i ] = point ; 
					}

					ofSphere( lerpCentroids[ i ] , sphereRadius ) ; 
					//lerpCentroids.push_back( point ) ;  
				}
			}
			else
			{
				lerpCentroids.clear( ) ; 
				//FIRST TIME GETTING CENTROIDS
				for ( int a = 0 ; a < nCentroids ; a++ ) 
				{
					//if ( i % 2 == 0 ) 
					//	ofSetColor ( EmiratesGlobal::Instance()->EMIRATES_RED ) ; 
					//else
					//	ofSetColor( 255 , 255 , 255 ) ; 

					ofVec3f point = iisu->IIsuPosition3DToOfxScreen( mPositions[a] , bounds , bFlipX , bFlipY ) ;
					point.z *= zRange ; 
					lerpCentroids.push_back( point ) ; 
					ofSphere( point ,  sphereRadius ) ; 
				}
			}
		}

#ifdef USE_LIGHTING
		sphereMaterial.end( ) ; 			
		pointLight.disable() ; 
		ofDisableLighting( ) ; 
#endif

	}
}


void IisuSkeleton::drawHandProps( ) 
{
	if ( isTracked != 0 ) 
	{	
		if ( bHandTracked == false ) 
			return ; 
		SK::Array<SK::Vector3> keyPoints = iisu->m_keyPoints ; 		
		SK::Array<float> keyPointsConfidence = iisu->m_keyPointsConfidence ; 
		//ofColor red = ofColor( 255 , 0 , 0 ) ; 

		ofPushStyle( ) ; 
			ofSetColor( 255 , 255 , 0 , 255 * alpha ) ; 
			ofSetLineWidth( 4 ) ; 

			ofPushMatrix();
			ofVec3f elbow ; 
			if ( bRightHanded ) 
				elbow = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::RIGHT_ELBOW] , bounds , bFlipX , bFlipY ) ; 
			else
				elbow = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::LEFT_ELBOW] , bounds , bFlipX , bFlipY ) ; ; 
			//ofVec3f rightElbow = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::RIGHT_ELBOW] , bounds , bFlipX , bFlipY ) ;
			elbow.z *= zRange ; 
			model.setPosition( 0 , 0 , 0 ) ; 

			ofVec3f normal = elbow - primaryHand ;
			Tweenzor::add ( &orientationAngle.x , orientationAngle.x , normal.x , 0.0f , racketTweenTime ) ;   
			Tweenzor::add ( &orientationAngle.y , orientationAngle.y , normal.y , 0.0f , racketTweenTime ) ;   
			Tweenzor::add ( &orientationAngle.z , orientationAngle.z , normal.z , 0.0f , racketTweenTime ) ;   
					
			//cout << "orientationAngle.y : " << orientationAngle.y << endl ; 
			//ofVec3f racketAngle = normal.getPerpendicular( elbow ) ; 
			/*			
			float rotationAmount;
			ofVec3f rotationAngle;
			ofQuaternion rotation;
	
			ofVec3f axis(1, 0, 1);
			rotation.makeRotate(axis, normal);
			rotation.getRotate(rotationAmount, rotationAngle); 
			*/
			ofQuaternion curRot ; 

			float totalRotationX = ofClamp( orientationAngle.x + modelRotationOffset.x , 
										  ( modelRotationOffset.x + minRacketRotation.x ) , 
										  ( modelRotationOffset.x + maxRacketRotation.x ) ) ;

			float totalRotationY = ofClamp( orientationAngle.y + modelRotationOffset.y , 
										  ( modelRotationOffset.y + minRacketRotation.y ) , 
										  ( modelRotationOffset.y + maxRacketRotation.y ) ) ;

			float totalRotationZ = ofClamp( orientationAngle.z + modelRotationOffset.z , 
										  ( modelRotationOffset.z + minRacketRotation.z ) , 
										  ( modelRotationOffset.z + maxRacketRotation.z ) ) ;
					/*
					//ofClamp(  orientationAngle.y + modelRotationOffset.y , minRacketRotation , maxRacketRotation ) ; 
					if ( totalRotationX < ( modelRotationOffset.x - minRacketRotation.x )  ) 
						totalRotationX = ( modelRotationOffset.x - minRacketRotation.x ) ; 

					if ( totalRotationY > ( modelRotationOffset.y + maxRacketRotation.y ) ) 
						totalRotationY = ( modelRotationOffset.y + maxRacketRotation.y ) ; 
					*/
				//cout << "totalRotationY : " << totalRotationY << endl ;
				curRot = ofQuaternion( ) ; 
				ofQuaternion xRot( totalRotationX, ofVec3f( 0 , 0 , -1 ) ) ; 
				ofQuaternion yRot( totalRotationY , ofVec3f( 0 , 1 , 0 ) ) ; 
				ofQuaternion zRot( totalRotationZ , ofVec3f( 1 , 0 , 0 ) ) ; 
						
				curRot = yRot * xRot * zRot ;  

				ofVec3f axis;  
				float angle;  
				curRot.getRotate(angle, axis);  
					
				//Tween Racket is confidence threshold is high enough
	
					model.setRotation( 0 , angle , axis.x, axis.y  , axis.z ) ; 
					//
					//ofTranslate( primaryHand.x - bounds.width - 300 , primaryHand.y  , primaryHand.z ) ; 
					ofTranslate( primaryHand.x  + racketTranslate.x , primaryHand.y + racketTranslate.y  , primaryHand.z + racketTranslate.z ) ; 
					//ofRotate( angle , axis.x , axis.y , axis.z ) ; 
					ofSetColor(  EmiratesGlobal::Instance()->EMIRATES_RED , 255 * alpha ) ; 		
					ofScale ( .25 , .25 , .25 ) ; 
					model.drawFaces();

				ofPopMatrix();
				 
			ofPopStyle() ; 


	ofPushMatrix() ; 

		if ( bTrackServeComplete == false && bTrackBall == true ) 
			ofTranslate( secondaryHand ) ; 
		else
			ofTranslate( servePosition ) ; 
			ofRotateZ( ofGetElapsedTimef() * 360 ) ; 
			ofRotateX( ofGetElapsedTimef() * 120 ) ;
			ofSetColor( 255 , 255 , 255 ) ; 
			ofColor col1 = ofColor ( 255 , 255 , 255 ) ; 
			ofColor col2 = EmiratesGlobal::Instance()->EMIRATES_RED ; 
			ofColor curColor = col1.lerp( col2 , tennisColorLerp ) ; 
					
		if ( bTrackServeComplete == true )
			ofSetColor( curColor , ballAlpha ) ; 

		drawTennisBall ( ) ; 

		ofPopMatrix() ; 
	}
}
void IisuSkeleton::draw ( ) 
{


	//glEnable( GL_DEPTH_TEST ) ; 

	

	if ( alpha == 0 ) return ; 
	isTracked = iisu->m_skeletonStatus ; 
	//cout << "isTracked : " << isTracked << endl ; 
	if ( isTracked != 0 ) 
	{	
		
		SK::Array<SK::Vector3> keyPoints = iisu->m_keyPoints ; 		
		SK::Array<float> keyPointsConfidence = iisu->m_keyPointsConfidence ; 
		
		//ofColor red = ofColor( 255 , 0 , 0 ) ; 
		//ofColor green = ofColor( 0 , 255 , 0 ) ; 
		//ofColor _curColor = red.lerp( green , calibrationStatus ) ; 
		//ofSetColor ( _curColor , alpha * 255 ) ; 

		/*
		for ( int i = 0 ; i < keyPoints.size() ; i++ ) 
		{
			
			ofVec3f p = iisu->IIsuPosition3DToOfxScreen( keyPoints[i] , bounds , bFlipX , bFlipY ) ; 
			ofPushMatrix() ; 
				ofTranslate( p.x , p.y , p.z * 400 ) ; 
				ofSphere( 0 , 0 , 0, 6 ) ; 
			ofPopMatrix() ; 
			//ofCircle(  p , 15 ) ; 
		}*/
		

		//Get our two hands
		ofVec3f rightHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::RIGHT_WRIST ] , bounds , bFlipX , bFlipY ) ; 
		ofVec3f leftHand = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::LEFT_WRIST ] , bounds , bFlipX , bFlipY ) ;
		float rightHandConfidence = keyPointsConfidence[ SK::SkeletonEnum::RIGHT_HAND ] ; 
		float leftHandConfidence = keyPointsConfidence[ SK::SkeletonEnum::LEFT_HAND ] ; 


		rightHand.z *= zRange ;  
		leftHand.z *= zRange ; 
		//And a point to test against
		ofVec3f collar = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::COLLAR ] , bounds , bFlipX , bFlipY ) ;
		headPosition = iisu->IIsuPosition3DToOfxScreen( keyPoints[SK::SkeletonEnum::HEAD ] , bounds , bFlipX , bFlipY ) + 65 ; 
		// Default is right Handed 
		
	
		if ( bRightHanded == false ) 
		{
					
			primaryHandConfidence = rightHandConfidence ; 
			secondayHandConfidence = leftHandConfidence ; 

			//if ( minimumHandConfidence > minimumHandConfidence ) 
			//{
				Tweenzor::add( &primaryHand.x , primaryHand.x , leftHand.x , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &primaryHand.y , primaryHand.y , leftHand.y , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &primaryHand.z , primaryHand.z , leftHand.z , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
			//}
			//else
			//{
				Tweenzor::add( &secondaryHand.x , secondaryHand.x , rightHand.x , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &secondaryHand.y , secondaryHand.y , rightHand.y , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &secondaryHand.z , secondaryHand.z , rightHand.z , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ;
			//}
		}
		else
		{
			primaryHandConfidence = leftHandConfidence ; 
			secondayHandConfidence = rightHandConfidence ; 
			//if ( primaryHandConfidence > minimumHandConfidence ) 
			//{
				Tweenzor::add( &primaryHand.x , primaryHand.x , rightHand.x , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &primaryHand.y , primaryHand.y , rightHand.y , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &primaryHand.z , primaryHand.z , rightHand.z , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
			//}

		//	if ( secondayHandConfidence > minimumHandConfidence ) 
			//{
				Tweenzor::add( &secondaryHand.x , secondaryHand.x , leftHand.x , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &secondaryHand.y , secondaryHand.y , leftHand.y , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ; 
				Tweenzor::add( &secondaryHand.z , secondaryHand.z , leftHand.z , 0.0f , skeletonTweenTime , EASE_OUT_QUAD ) ;
		//	}
		}
		if( bHandTracked == true ) 
		{
						
		}

		combinedHitCenter  = primaryHand + racketTranslate + ballHitCenter ; 

		//sphereMaterial.end( ) ; 
		ofDisableLighting( ) ;
		if ( bTrackServeComplete == true )
		{
			combinedHitColor = ofColor ( 125 , 64 , 255 ) ; 
			float distance = primaryHand.distance( servePosition ) ; 
			//cout << "CALCULATE THE DISTANCE!! " << serveDistance << endl ;
		//	cout << "Distance : " << (int) distance << " / " << (int) serveDistance << " % : " << ( distance / serveDistance ) << endl ;
			
			if ( Tweenzor::getTween ( &servePosition.z ) != NULL ) 
				return ; 

			if ( distance < serveDistance )
			{	
					if ( Tweenzor::getTween( &servePosition.y ) != NULL ) 
						Tweenzor::removeCompleteListener( Tweenzor::getTween( &servePosition.y) ) ;

					float serveLength = 0.75f ; 
					if ( numServes < 2 ) 
					{
						Tweenzor::add ( &servePosition.x , servePosition.x , serveTarget.x + ofRandom( -1000 , 1000 ) , 0.0f , serveLength , EASE_OUT_QUAD ) ; 
						Tweenzor::add ( &servePosition.y , servePosition.y , serveTarget.y + ofRandom( -120 , 120 ) , 0.0f ,serveLength , EASE_OUT_QUAD ) ; 
						Tweenzor::add ( &servePosition.z , servePosition.z , serveTarget.z + ofRandom( -200 , 200 ) , 0.0f , serveLength , EASE_OUT_QUAD ) ;
						Tweenzor::add ( &ballAlpha , ballAlpha , 0.0f, serveLength * .5f , serveLength * .5f , EASE_OUT_EXPO ) ; 
						Tweenzor::addCompleteListener( Tweenzor::getTween( &servePosition.z ) , this , &IisuSkeleton::practiceServeComplete ) ; 

						if ( bDebug == false ) 
						{
						//practiceComplete
						cout << "1 or 2 " << endl ; 
						numServes++ ; 
						cout << "BALL WAS SERVED!!!! there are now " << numServes << " served in total ! @ " << ofGetElapsedTimef() << endl ; 
						}
						ofNotifyEvent( IisuSkeleton::Instance()->BALL_SERVED , numServes ) ; 
					}
					else
					{
						Tweenzor::add ( &servePosition.x , servePosition.x , victoryTarget.x + ofRandom( -1000 , 1000 ) , 0.0f ,serveLength, EASE_OUT_QUAD ) ; 
						Tweenzor::add ( &servePosition.y , servePosition.y , victoryTarget.y + ofRandom( -200 , 0 ) , 0.0f , serveLength, EASE_OUT_QUAD ) ; 
						Tweenzor::add ( &servePosition.z , servePosition.z , victoryTarget.z + ofRandom( 300 , -300 ) , 0.0f , serveLength , EASE_OUT_QUAD ) ;
						Tweenzor::add ( &ballAlpha , ballAlpha , 0.0f, serveLength * .5f , serveLength * .5f , EASE_OUT_EXPO ) ; 
						cout << "NOT DEBUGGUING STADIUM! " << endl ; 
						numServes++ ; 
						cout << "BALL WAS SERVED!!!! there are now " << numServes << " served in total ! " << endl ; 
						ofNotifyEvent( IisuSkeleton::Instance()->BALL_SERVED , numServes ) ;
					}

					
					//Tweenzor::addCompleteListener( Tweenzor::getTween( &servePosition.y ) , this , &IisuSkeleton::practiceComplete ) ; 
			}
		}
		else
		{
			combinedHitColor = ofColor ( 255 , 124 , 22 ) ; 
		}
		
		if ( bDebug == true ) 
		{
			ofSetColor( 0 , 0 , 255 ) ; 
			ofSphere( victoryTarget , 45 ) ; 

			ofSetColor( 0 , 255 , 0 ) ; 
			ofSphere ( serveTarget , 45 ) ; 

			ofSetColor ( combinedHitColor ) ; 
			ofSphere ( combinedHitCenter , 45 ) ; 

			ofSetLineWidth ( 6 ) ; 
			ofSetColor ( combinedHitColor ) ; 
			ofLine ( combinedHitCenter , servePosition ) ; 
			ofSetLineWidth ( 1 ) ; 

			ofSetColor( 255 , 255 , 255 , primaryHandConfidence * 255.0f ) ; 
			ofSphere ( primaryHand , 10 ) ;

			ofSetColor ( 15 , 15 , 15 , secondayHandConfidence * 255.0f ) ;  
			ofSphere ( secondaryHand, 10 ) ; 
		}
	} 	
}
//bTrackBall

void IisuSkeleton::drawTennisBall ( ) 
{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
			glEnable(GL_NORMALIZE);
				ofPushMatrix() ; 

			//	ballTexture.bind();
				ballMaterial.begin();
				ofScale( 0.1 , 0.1 , 0.1 ) ; 
				//ballModel.drawWireframe( ) ; 
				ballModel.drawFaces();
				ballMaterial.end();
				//ballTexture.unbind();

			
				ofPopMatrix() ; 
			glPopAttrib();		
}

/*
void IisuSkeleton::practiceResetComplete ( float * args ) 
{
	cout << "PRACTICE RESET COMPLETE" << endl ; 
	servePosition = secondaryHand ;
	//servePosition.y += 100 ; 

	Tweenzor::add( &servePosition.y , servePosition.y , secondaryHand.y , 0.0f , 2.5f , EASE_OUT_QUAD ) ;
	Tweenzor::add ( &ballAlpha , ballAlpha , 255.0f, 0.0f , 2.5f , EASE_OUT_QUAD ) ; 
	bAutomatedServe = false ; 
	//secondaryHand
}
*/

float delayTween ; 
void IisuSkeleton::practiceServeComplete ( float * args  ) 
{
	ballAlpha = 0 ; 
	
	float delay = 1.75f ; 
	//Tweenzor::add ( &delayTween , 0.0f , 1.0f, 0.0f , delay ) ; 
	Tweenzor::add ( &servePosition.z , servePosition.z , servePosition.z + ofRandom( -20 , 20 ) , 0.0f , delay , EASE_OUT_QUAD ) ;
	Tweenzor::addCompleteListener( Tweenzor::getTween( &servePosition.z ) , this , &IisuSkeleton::practiceServeDelayComplete ) ;
	cout << "PRACTIVE SERVE COMPLETE!" << endl ; 

}

void IisuSkeleton::practiceServeDelayComplete ( float * args ) 
{
	Tweenzor::add ( &ballAlpha , 0.0f , 255.0f, 0.0f , 0.5f , EASE_OUT_EXPO ) ; 
	bTrackServeComplete = false ; 
	bTrackServe = true ; 
	lastServeCross = -2 ; 
	bTrackBall = true ; 
}