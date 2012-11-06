#include "IisuServer.h"

enum POINTER_STATUS
{
	POINTER_STATUS_NOT_DETECTED = 0,
	POINTER_STATUS_STILL = 1,
	POINTER_STATUS_OUT_OF_BOX = 2,
	POINTER_STATUS_ACTIVE = 3
};


void IisuServer::setup() 
{
	// We need to specify where is located the iisu dll and it's configuration file.
	// in this sample we'll use the SDK's environment variable.
	string dllLocation = getenv("IISU_SDK_DIR") ;
	dllLocation+="/bin" ;

	// get the working context
	Context& context = Context::Instance();

	// create an iisu configuration
	IisuHandle::Configuration iisuConfiguration(dllLocation.c_str(),"iisu_config.xml");
	// you can customize the configuration here
	
	// create the handle according to the configuration structure
	Return<IisuHandle*> retHandle = context.createHandle(iisuConfiguration);
	if(retHandle.failed())
	{
		cerr << "Failed to get iisu handle!" << endl
			<< "Error " << retHandle.getErrorCode() << ": " << retHandle.getDescription().ptr() << endl;
		getchar();
		exit(0);
	}

	// get the iisu handle
	m_iisuHandle = retHandle.get();

	// create device configuration
	Device::Configuration deviceConfiguration ;
	// you can customize the configuration here

	// create the device according to the configuration structure
	Return<Device*> retDevice = m_iisuHandle->initializeDevice(deviceConfiguration);
	if(retDevice.failed())
	{
		cerr << "Failed to create device!" << endl
			<< "Error " << retDevice.getErrorCode() << ": " << retDevice.getDescription().ptr() << endl;
		getchar();
		exit(0);
	}

	// get the device
	m_device = retDevice.get();

	registerEvents() ; 
	//initIisu() ; 


	

	m_skeletonStatus = 0 ; 
}

int IisuServer::addController( ) 
{
	int iisuIndex = controllerIsActiveData.size() + 1 ; 

	string pointerString = "UI.CONTROLLER" + ofToString( iisuIndex ) ;

	string activeString = pointerString +".IsActive"  ; 
	controllerIsActiveData.push_back(  m_device->registerDataHandle<bool>( activeString.c_str() ) ) ;
	controllerIsActive.push_back ( false ) ; 
	
	string normalizedString = pointerString + ".POINTER.NormalizedCoordinates" ; 
	pointerNormalizedCoordinatesData.push_back( m_device->registerDataHandle<Vector3>( normalizedString.c_str() ) );
	pointerNormalizedCoordinates.push_back( Vector3( ) ) ; 

	string statusString = pointerString + ".POINTER.Status" ; 
	pointerStatusData.push_back( m_device->registerDataHandle<int32_t>(statusString.c_str() ) );
	pointerStatus.push_back( 0 ) ;

	return ( iisuIndex - 1 ) ; 
	
}
void IisuServer::initIisu() 
{
	//User
	m_user1SceneID = m_device->registerDataHandle<int32_t>("USER1.SceneObjectID") ; 
	m_userIsActiveData = m_device->registerDataHandle<bool>("USER.IsActive") ; 

	/*
	//Controller UI
	m_controllerIsActiveData_0 = m_device->registerDataHandle<bool>("UI.CONTROLLER1.IsActive");
	m_pointerNormalizedCoordinatesData_0 = m_device->registerDataHandle<Vector3>("UI.CONTROLLER1.POINTER.NormalizedCoordinates");
	m_pointerStatusData_0 = m_device->registerDataHandle<int32_t>("UI.CONTROLLER1.POINTER.Status");
	m_controllerIsActiveData_1 = m_device->registerDataHandle<bool>("UI.CONTROLLER2.IsActive");
	m_pointerNormalizedCoordinatesData_1 = m_device->registerDataHandle<Vector3>("UI.CONTROLLER2.POINTER.NormalizedCoordinates");
	m_pointerStatusData_1 = m_device->registerDataHandle<int32_t>("UI.CONTROLLER2.POINTER.Status");
	*/
	//Volume + Skeleton
	m_skeletonStatusData = m_device->registerDataHandle<int>("USER1.SKELETON.Status");
	m_keyPointsData = m_device->registerDataHandle<Array<Vector3> >("USER1.SKELETON.KeyPoints");
	m_keyPointsConfidenceData = m_device->registerDataHandle<Array<float> >("USER1.SKELETON.KeyPointsConfidence");
	m_centroidCountParameter = m_device->registerParameterHandle<int32_t>( "SHAPE.CENTROIDS.Count" ) ; 
	m_centroidPositionsData = m_device->registerDataHandle<SK::Array<SK::Vector3>>("USER1.SHAPE.CENTROIDS.Positions") ;
	m_user1MassCenterData = m_device->registerDataHandle<Vector3>("USER1.MassCenter") ; 
	m_centroidsJumpStatusHandle = m_device->registerDataHandle< Array<int> >("USER1.SHAPE.CENTROIDS.JumpStatus" ) ; 

	//Camera
	sceneImageHandle = m_device->registerDataHandle< SK::Image >("SCENE.LabelImage") ; 

	m_centroidCountParameter.set( 150 ) ; 

	
	// we need it check if applicatin is set-up properly
	//m_uiEnabledParameter = m_device->registerParameterHandle<bool>("UI.Enabled");
	//m_controllersCount = m_device->registerParameterHandle<int32_t>("UI.ControllerCount");

	// we will use circle gestures to create controller and to start game, therefore...
	// ...set-up activation gesture (for simplicity we will use just circle gesture)
	ParameterHandle<bool> circleActivation = m_device->registerParameterHandle<bool>("UI.ACTIVATIONGESTURE.CIRCLE.Enabled");
	circleActivation.set(true);

	// ...make sure that gestures and circle gesture are enabled
	ParameterHandle<bool> gesturesEnabled = m_device->registerParameterHandle<bool>("UI.CONTROLLERS.GESTURES.Enabled");
	ParameterHandle<bool> circleGestureEnabled = m_device->registerParameterHandle<bool>("UI.CONTROLLERS.GESTURES.CIRCLE.Enabled");

	gesturesEnabled.set(true);
	circleGestureEnabled.set(true);

	// register this object to listen for UI.CONTROLLERS.Created event (we satrt game as soon as controller is created)
	Result res = m_device->getEventManager().registerEventListener("UI.CONTROLLERS.Created", *this, &IisuServer::onControllerCreated);
	if (res.failed()) 
	{
		cerr << "Failed to register in iisu for UI.CONTROLLERS.Created events!" << endl;
	}

	// register this object to listen for UI.CONTROLLERS.GESTURES.CIRCLE.Detected event (we might have controller already
	res = m_device->getEventManager().registerEventListener("UI.CONTROLLERS.GESTURES.CIRCLE.Detected", *this, &IisuServer::onCircleGesture);
	if (res.failed()) 
	{
		cerr << "Failed to register in iisu for UI.CONTROLLERS.GESTURES.CIRCLE.Detected events!" << endl;
	}

	SK::Result devStart = m_device->start();
	if(devStart.failed())
	{
		cerr << "Failed to start device!" << endl
			<< "Error " << devStart.getErrorCode() << ": " << devStart.getDescription().ptr() << endl;
		getchar();
		exit(0);
	}
}

void IisuServer::onError(const ErrorEvent& event)
{
	cerr << "iisu error : " << event.getError().getDescription().ptr() << endl;
	getchar();
}

void IisuServer::onControllerCreated(ControllerCreationEvent event)
{
	//First controller created 
	cout << "IisuServer::onControllerCreated !! " << endl ; 
}

void IisuServer::onCircleGesture(CircleGestureEvent event)
{
	cout << "IisuServer::onCircleGesture !! " << endl ; 	
}


void IisuServer::onDataFrame(const DataFrameEvent& event)	
{
  	SK::Result resUpdate = m_device->updateFrame( false ) ; 
	if(resUpdate.failed())
	{
		cerr << "Failed to update data frame" << endl;

	}
	// the rest of the logic depends on iisu data, so we need to make sure that we have
	// already a new data frame
	const int32_t currentFrameID = m_device->getDataFrame().getFrameID();
	if (currentFrameID == m_lastFrameID)
	{
		cout << "Same Frame as before" << endl ; 
		//return;
	}
	else
	{
		//cout << "frame# " << currentFrameID << endl ; 
	}

	// remember current frame id
	m_lastFrameID = currentFrameID;

	//USER
	m_user1MassCenter = m_user1MassCenterData.get() ; 
	m_userIsActive = m_userIsActiveData.get() ; 
	sceneImage = sceneImageHandle.get() ; 
	user1SceneID = m_user1SceneID.get() ;

	//Look through all our cursor data
	for ( int i = 0 ; i < pointerStatusData.size() ; i++ ) 
	{
		pointerStatus[ i ]  = pointerStatusData[ i ].get() ; 
		pointerNormalizedCoordinates[ i ] = pointerNormalizedCoordinatesData[ i ].get() ; 
		controllerIsActive[ i ] = controllerIsActiveData[ i ].get( ) ; 
	}

	/*
	//UI + Controller
	m_controllerIsActive_0 = m_controllerIsActiveData_0.get();
	m_pointerStatus_0 = m_pointerStatusData_0.get();
	m_pointerStatus_1 = m_pointerStatusData_1.get();

	// if pointer is detected we can read it's coordinates
	if ( m_pointerStatus_0 != POINTER_STATUS_NOT_DETECTED )
	{
		m_pointerNormalizedCoordinates_0 = m_pointerNormalizedCoordinatesData_0.get() ; 
	}

	if ( m_pointerStatus_1 != POINTER_STATUS_NOT_DETECTED ) 
	{
		m_pointerNormalizedCoordinates_1 = m_pointerNormalizedCoordinatesData_1.get() ; 
	}*/

	//Skeleton + Volume
	m_centroidCount = m_centroidCountParameter.get() ; 
	m_centroidPositions = m_centroidPositionsData.get() ; 
	m_skeletonStatus = m_skeletonStatusData.get() ; 	

	if ( m_skeletonStatus != 0 ) 
	{
		m_keyPoints = m_keyPointsData.get() ; 
		m_keyPointsConfidence = m_keyPointsConfidenceData.get() ; 
		m_centroidJumpStatus = m_centroidsJumpStatusHandle.get( ) ; 
	}

	if ( m_skeletonStatus != last_skeletonStatus ) 
	{
		int args = 9 ; 
		if ( m_skeletonStatus != 0 ) 
			ofNotifyEvent( IisuEvents::Instance()->USER_DETECTED , args ) ; 
		else
			ofNotifyEvent( IisuEvents::Instance()->USER_LOST , args ) ; 
	}

	// tell iisu we finished using data.
	m_device->releaseFrame();

	last_skeletonStatus = m_skeletonStatus ;
}

void IisuServer::registerEvents ( ) 
{
	if (m_device==NULL || m_iisuHandle==NULL)
	{
		cerr << "Iisu is not initialized" <<endl;
		getchar();
		exit();
	}
	// system errors events
	Result ret = m_iisuHandle->getEventManager().registerEventListener("SYSTEM.Error", *this, &IisuServer::onError);
	if (ret.failed()) 
	{
		cerr << "Failed to register for system error events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}

	// a new dataframe has been computed by iisu
	ret = m_iisuHandle->getEventManager().registerEventListener("DEVICE.DataFrame", *this, &IisuServer::onDataFrame);
	if (ret.failed()) 
	{
		cerr << "Failed to register for data frame events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}

	/*
	// users activation events 
	if (ret.failed()) 
	{
		cerr << "Failed to register for user activation events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}

	// users deactivation events 
	ret = m_iisuHandle->getEventManager().registerEventListener("UM.UserDeactivated", *this, &IisuServer::onUserDeactivation);
	if (ret.failed()) 
	{
		cerr << "Failed to register for user deactivation events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}
	*/
}

int IisuServer::getCursorStatus ( int cursorID ) 
{
	if ( cursorID < pointerStatus.size() ) 
		return pointerStatus[ cursorID ] ; 
	else
		cout << "IisuServer::getCursorStatus :: INVALID INDEX" << endl ; 
	

	return -1 ; 
}

Vector3 IisuServer::getNormalizedCursorCoordinates ( int cursorID ) 
{	
	if ( cursorID < pointerStatus.size() ) 
		return pointerNormalizedCoordinates[ cursorID ] ;
	else
		cout << "IisuServer::getNormalizedCursorCoordinates :: INVALID INDEX" << endl ;

	return Vector3( ) ; 
}

Vector3 IisuServer::getWorldCursorPosition( int cursorID ) 
{
	return Vector3() ; 
}

void IisuServer::exit ( int exitCode ) 
{
	m_iisuHandle->getEventManager().unregisterEventListener( "SYSTEM.Error" , *this , &IisuServer::onError ) ; 
	m_iisuHandle->getEventManager().unregisterEventListener( "DEVICE.DataFrame" , *this , &IisuServer::onDataFrame );
	
	cout << "IISU ERROR ! Exit Code of : " << exitCode << endl ; 

	ofNotifyEvent( IisuEvents::Instance()->exitApplication , exitCode , this ) ; 
}

ofVec3f IisuServer::iisuPointToOF( Vector3 point )
{
	ofVec3f vector = ofVec3f( (( point.x +1.0f )/2.0f ) * ofGetWidth() ,ofGetHeight() +- ( ( point.z +1.0f ) /2.0f ) * ofGetHeight() ,  point.y ) ; 
	return vector ; 
}

ofVec3f IisuServer::iisuPointToOF( Vector3 point , ofVec3f range ) 
{
	ofVec3f vector = ofVec3f( (( point.x +1.0f )/2.0f ) * range.x , ( ( point.z +1.0f ) /2.0f ) * range.y ,  point.y * range.z ) ; 
	return vector ; 
}

ofVec3f IisuServer::IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofRectangle bounds , bool mirrorX , bool mirrorY )
{
	ofVec3f screenPosition ; 
	float factorX = ( mirrorX == true ) ? -2 : 2 ; 
	float factorY = ( mirrorY == true ) ? -2 : 2 ; 
		
	screenPosition.x = bounds.x + ( ( ( IisuPosition.x + 1 ) / factorX ) * bounds.width );
	screenPosition.y = bounds.y + ( bounds.height -( ( IisuPosition.z + 1 ) / factorY ) * bounds.height ) ; 
	screenPosition.z = IisuPosition.y; 
		
	return screenPosition ;
}