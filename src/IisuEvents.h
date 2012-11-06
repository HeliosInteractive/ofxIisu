#ifndef _iisu_events
#define _iisu_events

#include "ofMain.h" 
#include "IisuEventArgs.h"

class IisuEvents
{
	public : 
		IisuEvents ( ) { } 

		//Universal access to the same event type
		static IisuEvents* Instance()
        {
            static IisuEvents inst;
            return &inst;
        }

		ofEvent<int> exitApplication ; 
		ofEvent<IisuEventArgs> CURSOR_HOVER_START ; 
		ofEvent<int> CURSOR_HOVER_FINISHED ; 
		ofEvent<int> CURSOR_HOVER_INTERRUPTED ; 

		ofEvent<int> USER_DETECTED ;
		ofEvent<int> USER_LOST ; 

		ofEvent<int> HAND_CLOSE ; 
		ofEvent<int> HAND_OPEN ; 
		ofEvent<int> POSE_GESTURE ; 
		ofEvent<int> HAND_CALIBRATED ; 

		ofEvent<int> IDLE_INSTRUCTIONS ; 
		ofEvent<int> CURSOR_DETECTED ; 
		ofEvent<int> CURSOR_LOST ; 
		ofEvent<int> CURSOR_DESTROYED ; 
		
};

#endif ; 