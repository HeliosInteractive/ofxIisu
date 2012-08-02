//
//  PixelEventArgs.h
//  Helios_TableTop
//
//  Created by Ben McChesney on 12/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once 

#include "ofMain.h"

class IisuEventArgs : public ofEventArgs
{
    public:
    
        IisuEventArgs( int _inputHex , float _holdDelay ) 
		{
			inputHex = _inputHex;
			holdDelay = _holdDelay ; 
		}

        virtual ~IisuEventArgs( ) { }
    
        //Add whatever you need !
        int inputHex ; 
		float holdDelay ; 
    
};
