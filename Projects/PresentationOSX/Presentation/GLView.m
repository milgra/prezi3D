//
//  GLView.m
//  DynamicsX
//
//  Created by Milan Toth on 9/4/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

    #import <Carbon/Carbon.h>
	#import "GLView.h"
	#import "AppDelegate.h"


	@implementation GLView


	- ( BOOL ) canBecomeFirstResponder
	{
	
		return YES;
		
	}
    
    
	- ( void ) scrollWheel : ( NSEvent * )theEvent
    {
    
        [ [ AppDelegate sharedDelegate ] scrollX : [ theEvent deltaX ] scrollY : [ theEvent deltaY ] ];
        
        
    }
    
    
    - ( void ) keyDown:(NSEvent *)theEvent
    {
        switch( [theEvent keyCode] )
        {
        
            case kVK_UpArrow :
                break;
            case kVK_DownArrow :
                break;
            case kVK_RightArrow :
                [ [ AppDelegate sharedDelegate ] right_pressed ];
                break;
            case kVK_LeftArrow :
                [ [ AppDelegate sharedDelegate ] left_pressed ];
                break;
            default:
                [ [ AppDelegate sharedDelegate ] key_down_characters : ( char* ) [ theEvent.characters cStringUsingEncoding : NSUTF8StringEncoding ] ];
                break;
                
        }
        
    }
    
    - ( void ) keyUp:(NSEvent *)theEvent
    {

    }
	
	- ( void ) mouseDown : ( NSEvent* ) theEvent
	{

		NSPoint location = [ theEvent locationInWindow ];
		
		[ [ AppDelegate sharedDelegate ] mouse_down_at_x_y : location fromView : self ];

	}


	- ( void ) mouseUp : ( NSEvent* ) theEvent
	{

		NSPoint location = [ theEvent locationInWindow ];
		
		[ [ AppDelegate sharedDelegate ] mouse_up_at_x_y : location fromView : self ];

	}


	- ( void ) mouseDragged : ( NSEvent* ) theEvent
	{

		NSPoint location = [ theEvent locationInWindow ];
		
		[ [ AppDelegate sharedDelegate ] mouse_move_at_x_y : location fromView : self ];

	}


	@end
