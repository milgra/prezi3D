//
//  AppDelegate.h
//  PickNickChat
//
//  Created by Milan Toth on 03/02/14.
//  Copyright (c) 2014 Milan Toth. All rights reserved.
//

	#import <Cocoa/Cocoa.h>
	#import <OpenGL/gl3.h>
    #import <sys/types.h>
    #import <pwd.h>
	#import "GLView.h"
	#import "clcsrc.h"


	@interface AppDelegate : NSObject <NSApplicationDelegate,NSWindowDelegate>
	{

		GLView*				menuView;
		NSWindow*			menuWindow;
        dispatch_source_t   initTimer;
        dispatch_source_t   runTimer;
		
        struct PRController* controller;

	}

	
	- ( void ) left_pressed;
	- ( void ) right_pressed;
	- ( void ) scrollX              : ( float   ) the_x        scrollY  : ( float   ) the_y;
	- ( void ) mouse_up_at_x_y		: ( NSPoint ) theLocation fromView : ( NSView* ) theView;
	- ( void ) mouse_down_at_x_y 	: ( NSPoint ) theLocation fromView : ( NSView* ) theView;
	- ( void ) mouse_move_at_x_y 	: ( NSPoint ) theLocation fromView : ( NSView* ) theView;
	- ( void ) key_down_characters  : ( char* ) the_characters;

	+ ( AppDelegate* ) sharedDelegate;


	@end