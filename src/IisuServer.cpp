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
	initIisu() ; 


	SK::Result devStart = m_device->start();
	if(devStart.failed())
	{
		cerr << "Failed to start device!" << endl
			<< "Error " << devStart.getErrorCode() << ": " << devStart.getDescription().ptr() << endl;
		getchar();
		exit(0);
	}

	m_skeletonStatus = 0 ; 
}


void IisuServer::initIisu() 
{
	m_controllerIsActiveData = m_device->registerDataHandle<bool>("UI.CONTROLLER1.IsActive");
	m_pointerCoordinatesData = m_device->registerDataHandle<Vector3>("UI.CONTROLLER1.POINTER.NormalizedCoordinates");
	m_pointerStatusData = m_device->registerDataHandle<int32_t>("UI.CONTROLLER1.POINTER.Status");
	m_centroidCountParameter = m_device->registerParameterHandle<int32_t>( "SHAPE.CENTROIDS.Count" ) ; 
	m_centroidCountParameter.set( 90 ) ; 
	sceneImageHandle = m_device->registerDataHandle< SK::Image >("SCENE.LabelImage") ; 
	m_centroidPositionsData = m_device->registerDataHandle<SK::Array<SK::Vector3>>("USER1.SHAPE.CENTROIDS.Positions") ; 

	// we are only interested with one User 1 in this tutorial
	m_skeletonStatusData = m_device->registerDataHandle<int>("USER1.SKELETON.Status");
	m_keyPointsData = m_device->registerDataHandle<Array<Vector3> >("USER1.SKELETON.KeyPoints");
	m_keyPointsConfidenceData = m_device->registerDataHandle<Array<float> >("USER1.SKELETON.KeyPointsConfidence");
	

	m_user1SceneID = m_device->registerDataHandle<int32_t>("USER1.SceneObjectID") ; 

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
	// created but game is over, so another circle starts next game round)
	res = m_device->getEventManager().registerEventListener("UI.CONTROLLERS.GESTURES.CIRCLE.Detected", *this, &IisuServer::onCircleGesture);
	if (res.failed()) 
	{
		cerr << "Failed to register in iisu for UI.CONTROLLERS.GESTURES.CIRCLE.Detected events!" << endl;
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
	ofBackground ( 25 , 25 , 25 ) ; 
}

void IisuServer::onCircleGesture(CircleGestureEvent event)
{
	//cout << "Circle gesture has been completed! " << endl ; 	
}


void IisuServer::onDataFrame(const DataFrameEvent& event)	
{
  	SK::Result resUpdate = m_device->updateFrame(true);
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
		return;
	}
	else
	{
		//cout << "frame# " << currentFrameID << endl ; 
	}

	// remember current frame id
	m_lastFrameID = currentFrameID;

	// check if controller is active
	m_controllerIsActive = m_controllerIsActiveData.get();

	// get status of the pointer
	m_pointerStatus = m_pointerStatusData.get();

	m_centroidCount = m_centroidCountParameter.get() ; 
	//cout << "centroid count is : " << m_centroidCount << endl;
	m_centroidPositions = m_centroidPositionsData.get() ; 

	// we are only interested with one User 1 in this tutorial
	m_skeletonStatus = m_skeletonStatusData.get() ; // = m_device.registerDataHandle<int>("USER1.SKELETON.Status");
	if ( m_skeletonStatus != 0 ) 
	{
		m_keyPoints = m_keyPointsData.get() ; 
		m_keyPointsConfidence = m_keyPointsConfidenceData.get() ; 
	}

	// if pointer is detected we can read it's coordinates
	if (m_pointerStatus != POINTER_STATUS_NOT_DETECTED )
	{
		m_pointerPosition = m_pointerCoordinatesData.get() ; 
		//cout << m_pointerPosition << endl ; 
	}

	sceneImage = sceneImageHandle.get() ; 

	user1SceneID = m_user1SceneID.get() ;
	
	// tell iisu we finished using data.
	m_device->releaseFrame();
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