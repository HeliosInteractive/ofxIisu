#pragma once

#include <Foundation/Services/Commands/Command.h>

namespace SK
{
#define COMMAND_HELPER(NAME, PATH, TYPE)\
	class NAME##Command : public SK::CommandHandle< TYPE >\
	{\
	public:\
		typedef SK::CommandHandle< TYPE > base_t;\
\
		NAME##Command(SK::CommandManager& commandManager): base_t(commandManager, PATH) {}\
	}

	COMMAND_HELPER(GetVersion,					"SYSTEM.GetVersion",				SK::Return<SK::String>());
	COMMAND_HELPER(LoadMovie,					"SOURCE.LoadMovie",					SK::Result(const SK::String&));
	COMMAND_HELPER(LoadCamera,					"SOURCE.LoadCamera",				SK::Result(const SK::String&));
	COMMAND_HELPER(LoadParameters,				"SYSTEM.PARAMETERS.Load",			SK::Result (const SK::String&, const SK::String&));
	COMMAND_HELPER(LoadMultipleParameters,		"SYSTEM.PARAMETERS.Load",			SK::Result (const SK::Array<SK::String>&, const SK::String&));
	COMMAND_HELPER(SaveParameters,				"SYSTEM.PARAMETERS.Save",			SK::Result (const SK::String&, const SK::String&));
	COMMAND_HELPER(SaveMultipleParameters,		"SYSTEM.PARAMETERS.Save",			SK::Result (const SK::Array<SK::String>&, const SK::String&));
	COMMAND_HELPER(ResetParameters,				"SYSTEM.PARAMETERS.Reset",			SK::Result (const SK::String&, const SK::String&));
	COMMAND_HELPER(ResetMultipleParameters,		"SYSTEM.PARAMETERS.Reset",			SK::Result (const SK::Array<SK::String>&, const SK::String&));
	COMMAND_HELPER(HasModule,					"SYSTEM.HasModule",					SK::Return<bool> (const SK::String&));
	COMMAND_HELPER(LoadBackground,				"SCENE.BACKGROUND.Load",			SK::Result ());
	COMMAND_HELPER(SaveBackground,				"SCENE.BACKGROUND.Save",			SK::Result ());
	COMMAND_HELPER(ResetBackground,				"SCENE.BACKGROUND.Reset",			SK::Result ());
	COMMAND_HELPER(TakeBackgroundSnapshot,		"SCENE.BACKGROUND.TakeSnapshot",	SK::Result (const SK::Enum&));
	COMMAND_HELPER(SaveCalibration,				"SCENE.CALIBRATION.Save",			SK::Result ());
	COMMAND_HELPER(LoadCalibration,				"SCENE.CALIBRATION.Load",			SK::Result ());
	COMMAND_HELPER(ResetCalibration,			"SCENE.CALIBRATION.Reset",			SK::Result ());
	COMMAND_HELPER(RestoreDefaultCalibration,	"SCENE.CALIBRATION.RestoreDefault",	SK::Result ());
	COMMAND_HELPER(LoadIIDGraph,				"IID.loadGraph",					SK::Result (const SK::String&));
	COMMAND_HELPER(SetIIDGraph,					"IID.setGraph",						SK::Result (const SK::String&));
	COMMAND_HELPER(UpdateIIDGraph,				"IID.updateGraph",					SK::Result (const SK::String&));
	COMMAND_HELPER(DestroyController,			"UI.CONTROLLERS.Destroy",			void(int16_t));
	COMMAND_HELPER(CreateController,			"UI.CONTROLLERS.Create",			void(int16_t, const SK::Vector3&));
	COMMAND_HELPER(ActivateUser,				"UM.ActivateUser",					SK::Result(int32_t));
	COMMAND_HELPER(DeactivateUser,				"UM.DeactivateUser",				SK::Result(int32_t));
	
	
	
	
	
	
	
	
	
	
	
}
