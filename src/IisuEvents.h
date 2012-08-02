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

		ofEvent<int> HAND_CLOSE ; 
		ofEvent<int> HAND_OPEN ; 

		ofEvent<int> POSE_GESTURE ; 
		ofEvent<int> THUMBS_UP ; 
		
};

#endif ; 