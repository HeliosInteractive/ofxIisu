#include "CloseIisuServer.h"


enum POINTER_STATUS
{
	POINTER_STATUS_NOT_DETECTED = 0,
	POINTER_STATUS_STILL = 1,
	POINTER_STATUS_OUT_OF_BOX = 2,
	POINTER_STATUS_ACTIVE = 3
};


void CloseIisuServer::setup() 
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

}


void CloseIisuServer::initIisu() 
{
	/*
	m_controllerIsActiveData = m_device->registerDataHandle<bool>("UI.CONTROLLER1.IsActive");
	m_pointerCoordinatesData = m_device->registerDataHandle<Vector3>("UI.CONTROLLER1.POINTER.NormalizedCoordinates");
	m_pointerStatusData = m_device->registerDataHandle<int32_t>("UI.CONTROLLER1.POINTER.Status");
	m_centroidCountParameter = m_device->registerParameterHandle<int32_t>( "SHAPE.CENTROIDS.Count" ) ; 
	m_centroidCountParameter.set( 90 ) ; */

	
	/*
	sceneImageHandle = m_device->registerDataHandle< SK::Image >("SCENE.LabelImage") ; 
	m_centroidPositionsData = m_device->registerDataHandle<SK::Array<SK::Vector3>>("USER1.SHAPE.CENTROIDS.Positions") ; 
	m_user1SceneID = m_device->registerDataHandle<int32_t>("USER1.SceneObjectID") ; 
	*/
	m_CI_EnabledHandle = m_device->registerParameterHandle<bool>("CI.Enabled") ; 
	m_hand1_statusHandle = m_device->registerDataHandle<int32_t>("CI.HAND1.Status") ; 
	m_hand1_palmPositionHandle = m_device->registerDataHandle<Vector3>("CI.HAND1.PalmPosition3D" ) ; 
	m_hand1_fingerTipsHandle = m_device->registerDataHandle<SK::Array<Vector3>>("CI.HAND1.FingerTipPositions3D" ) ; 
	m_hand1_fingerTipsStatusHandle = m_device->registerDataHandle<SK::Array<int32_t>>("CI.HAND1.FingerStatus" ) ; 

	m_hand1_openHandle = m_device->registerDataHandle<bool>("CI.HAND1.IsOpen" ) ; 
	m_hand1_openAmountHandle = m_device->registerDataHandle<float>("CI.HAND1.Openness" ) ; 


	
	Result res = m_device->getEventManager().registerEventListener( "CI.HandActivated" , *this , &CloseIisuServer::handActivatedHandler ) ; 
	if ( res.failed() )
		cout << "failed to regsiter CI.HandActivated!" << endl ; 
	else
		cout << "succesfully registered CI.HandActivat6ed! " << endl ; 

	res = m_device->getEventManager().registerEventListener( "CI.HandDeactivated" , *this , &CloseIisuServer::handDeactivatedHandler ) ; 
	if ( res.failed() )
		cout << "failed to regsiter CI.HandDeactivated!" << endl ; 
	else
		cout << "succesfully registered CI.HandDeactivated! " << endl ; 

}

void CloseIisuServer::onError(const ErrorEvent& event)
{
	cerr << "iisu error : " << event.getError().getDescription().ptr() << endl;
	getchar();
}

void CloseIisuServer::handActivatedHandler( SK::HandActivatedEvent ) 
{
	cout << "hand activated! " << endl ;
}
void CloseIisuServer::handDeactivatedHandler( SK::HandDeactivatedEvent )
{
	cout << "hand deactivated! " << endl ; 

}

void CloseIisuServer::onDataFrame(const DataFrameEvent& event)	
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
	
	m_hand1_status = m_hand1_statusHandle.get( ) ; 
	if ( m_hand1_status >  0 ) 
	{
		m_hand1_palmPosition = m_hand1_palmPositionHandle.get() ;
		m_hand1_fingerTipsStatus = m_hand1_fingerTipsStatusHandle.get() ; 
		m_hand1_fingerTips = m_hand1_fingerTipsHandle.get() ; 
		m_hand1_open = m_hand1_openHandle.get() ; 
		m_hand1_openAmount = m_hand1_openAmountHandle.get() ; 
	}

	// remember current frame id
	m_lastFrameID = currentFrameID;

	// tell iisu we finished using data.
	m_device->releaseFrame();
}

void CloseIisuServer::registerEvents ( ) 
{
	if (m_device==NULL || m_iisuHandle==NULL)
	{
		cerr << "Iisu is not initialized" <<endl;
		getchar();
		exit();
	}
	// system errors events
	Result ret = m_iisuHandle->getEventManager().registerEventListener("SYSTEM.Error", *this, &CloseIisuServer::onError);
	if (ret.failed()) 
	{
		cerr << "Failed to register for system error events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}
	
	// a new dataframe has been computed by iisu
	ret = m_iisuHandle->getEventManager().registerEventListener("DEVICE.DataFrame", *this, &CloseIisuServer::onDataFrame);
	if (ret.failed()) 
	{
		cerr << "Failed to register for data frame events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}

	ret = m_iisuHandle->getEventManager().registerEventListener("CI.HandPosingGesture", *this, &CloseIisuServer::handPoseGestureHandler );
	if (ret.failed()) 
	{
		cerr << "Failed to register for CI.HandPosing Gesture events!" << endl
			<< "Error " << ret.getErrorCode() << ": " << ret.getDescription().ptr() << endl;
		getchar();
		exit();
	}
}

void CloseIisuServer::handPoseGestureHandler ( SK::HandPosingGestureEvent e ) 
{
	//Get posing metaInfo
	SK::Return<SK::MetaInfo<SK::HandPosingGestureEvent> > retMetaInfo = m_device->getEventManager().getMetaInfo<SK::HandPosingGestureEvent>("CI.HandPosingGesture") ; 

	if ( retMetaInfo.succeeded() ) 
	{
		SK::MetaInfo<SK::HandPosingGestureEvent> poseMetaInfo = retMetaInfo.get() ; 
		const SK::EnumMapper &enumMapper = poseMetaInfo.getEnumMapper() ; 

		/*
		//Get the Big 5
		SK::Return<uint32_t> retBig5GestureId = enumMapper["BIG_5"] ; 
		if ( retBig5GestureId.succeeded() ) 
		{
			uint32_t big5GestureID = retBig5GestureId.get() ; 
			//cout << "BIG_5 id : " << big5GestureID << endl ; 
		}
		

		SK::Return<uint32_t> retFistGestureID = enumMapper["FIST"] ; 
		if ( retBig5GestureId.succeeded() ) 
		{
			uint32_t fistGestureID = retFistGestureID.get() ; 
			//cout << "FIST id : " << fistGestureID << endl ; 
		}*/


		int gestureID = e.getGestureTypeID() ; 
		SK::Return<SK::String> retPosingGestureName = enumMapper[gestureID] ; 
		if ( retPosingGestureName.succeeded() ) 
		{
			SK::String gestureName = retPosingGestureName.get() ; 
			cout << "pose: " << gestureName << "   _ gestureTypeID : " << e.getGestureTypeID() << "   _ firstHand ID: " << e.getFirstHandID() << endl ; 
			int args =  e.getGestureTypeID() ; 
			ofNotifyEvent( IisuEvents::Instance()->POSE_GESTURE , args ) ; 
		}

		/*
		if ( gestureID == 3 || gestureID == 12  ) 
		{
			//cout << "selection event occured!" << endl ; 
			//ofNotifyEvent( IisuEvents::Instance()->HAND_CLAMP_SELECTION , gestureID ) ; 
		}

		if ( gestureID == 13 ) 
		{
			cout << "selection event occured!" << endl ; 
			//ofNotifyEvent( IisuEvents::Instance()->THUMBS_UP , gestureID ) ; 
		}*/
		
	}
	else
	{
		//cout << "meta Info did not succeed! " << endl ; 
	}
	
	//cout << "hand pose handled!" << endl ; 
	
	
}

void CloseIisuServer::exit ( int exitCode ) 
{
	m_iisuHandle->getEventManager().unregisterEventListener( "SYSTEM.Error" , *this , &CloseIisuServer::onError ) ; 
	m_iisuHandle->getEventManager().unregisterEventListener( "DEVICE.DataFrame" , *this , &CloseIisuServer::onDataFrame );
	
	cout << "IISU ERROR ! Exit Code of : " << exitCode << endl ; 

	ofNotifyEvent( IisuEvents::Instance()->exitApplication , exitCode , this ) ; 
}

ofVec3f CloseIisuServer::iisuPointToOF( Vector3 point )
{
	ofVec3f vector = ofVec3f( (( point.x +1.0f )/2.0f ) * ofGetWidth() ,ofGetHeight() +- ( ( point.y +1.0f ) /2.0f ) * ofGetHeight() ,  point.z ) ; 
	return vector ; 
}

ofVec3f CloseIisuServer::IIsuPosition3DToOfxScreen( Vector3 IisuPosition , ofRectangle bounds , bool mirrorX )
{
	ofVec3f screenPosition ; 
	float factor = ( mirrorX == true ) ? -2 : 2 ; 
		
	screenPosition.x = bounds.x + ( ( ( IisuPosition.x + 1 ) / factor ) * bounds.width );
	screenPosition.y = bounds.y + ( bounds.height -( ( IisuPosition.z + 1 ) / factor ) * bounds.height ) ; 
	screenPosition.z = IisuPosition.y; 
		
	return screenPosition ;
}