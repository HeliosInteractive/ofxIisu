
//******************************************************************************
//
//  Softkinetic iisu SDK
//
//  Copyright (C) 2006-2011 by Softkinetic SA/NV
//  All rights reserved.
//
//  Version           : 3.0
//
//  Description       : Header file including all iisu API files.
//
//******************************************************************************

/*! \file iisuSDK.h>
    \brief Header file including all iisu API files.
*/


#ifndef IISU_SDK
#define IISU_SDK

//Prevent clash in case of new/delete macro override
#pragma push_macro("new")
#pragma push_macro("delete")
#undef new
#undef delete

#pragma warning(push, 0)
#include <Foundation/DataTypes/3D/Vertex.h>
#include <Foundation/DataTypes/Array/Array.h>
#include <Foundation/DataTypes/Color/Color.h>
#include <Foundation/DataTypes/Enumeration/Enum.h>
#include <Foundation/DataTypes/Geometry/Frame.h>
#include <Foundation/DataTypes/Geometry/Matrix3.h>
#include <Foundation/DataTypes/Geometry/Matrix4.h>
#include <Foundation/DataTypes/Geometry/Quaternion.h>
#include <Foundation/DataTypes/Geometry/Vector2.h>
#include <Foundation/DataTypes/Geometry/Vector2i.h>
#include <Foundation/DataTypes/Geometry/Vector3.h>
#include <Foundation/DataTypes/Geometry/Vector3i.h>
#include <Foundation/DataTypes/Geometry/Vector4.h>
#include <Foundation/DataTypes/Image/ColorConvertor.h>
#include <Foundation/DataTypes/Image/Image.h>
#include <Foundation/DataTypes/Image/ImageInfos.h>
#include <Foundation/DataTypes/MetaInformation/Attributes.h>
#include <Foundation/DataTypes/MetaInformation/MetaInfo.h>
#include <Foundation/DataTypes/MetaInformation/MetaInfoImpl.h>
#include <Foundation/DataTypes/Skeleton/KeyPoints.h>
#include <Foundation/DataTypes/String/String.h>
#include <Foundation/Services/Commands/BackgroundSnapshotType.h>
#include <Foundation/Services/Commands/Command.h>
#include <Foundation/Services/Commands/CommandManager.h>
#include <Foundation/Services/Events/ActivationGestureEvent.h>
#include <Foundation/Services/Events/BackgroundLearningEvent.h>
#include <Foundation/Services/Events/CalibrationEvent.h>
#include <Foundation/Services/Events/ControllerEvents.h>
#include <Foundation/Services/Events/DeviceEvent.h>
#include <Foundation/Services/Events/ErrorEvent.h>
#include <Foundation/Services/Events/Event.h>
#include <Foundation/Services/Events/EventEnum.h>
#include <Foundation/Services/Events/EventListenerProxy.h>
#include <Foundation/Services/Events/EventManager.h>
#include <Foundation/Services/Events/GenericEvent.h>
#include <Foundation/Services/Events/GestureEvent.h>
#include <Foundation/Services/Events/HandPosingGestureEvent.h>
#include <Foundation/Services/Events/HandMovingGestureEvent.h>
#include <Foundation/Services/Events/HumanoidActivatorEvent.h>
#include <Foundation/Services/Events/HumanoidComputerEvent.h>
#include <Foundation/Services/Types/FunctionTypeInfo.h>
#include <Foundation/Services/Types/FunctionTypeInfoImpl.h>
#include <Foundation/Services/Types/RawData.h>
#include <Foundation/Services/Types/TypeInfo.h>
#include <Foundation/Services/Types/TypeInfoDefinition.h>
#include <Foundation/Services/Types/TypeInfoImpl.h>
#include <Framework/Errors/Error.h>
#include <Framework/Errors/ErrorCodes.h>
#include <Framework/Errors/Return.h>
#include <Framework/Functor/CallingConventionConverter.h>
#include <Framework/Functor/Function.h>
#include <Framework/Instances/SharedPtr.h>
#include <Framework/Instances/Singleton.h>
#include <Framework/Types/FunctionTypeTrait.h>
#include <Framework/Types/MetaInfoTrait.h>
#include <Framework/Types/RefTypeTrait.h>
#include <Iisu/API/IisuCTypes.h>
#include <Iisu/Config/ApplicationConfigurator.h>
#include <Iisu/Devices/DataExtractor.h>
#include <Iisu/Devices/DataFrame.h>
#include <Iisu/Devices/Device.h>
#include <Iisu/Handles/IisuHandle.h>
#include <Platform/CompileTimeUtils.h>
#include <Platform/SkPlatform.h>
#include <SDK/CApi/iisuAPI.h>
#include <SDK/CApi/iisuAPIHelpers.h>
#include <SDK/Context/Context.h>
#include <SDK/Helpers/CommandHelpers.h>
#include <System/Math/Math.h>
#include <System/Math/NumericCast.h>
#pragma warning(pop)

#pragma pop_macro("delete")
#pragma pop_macro("new")

#endif // IISU_SDK

