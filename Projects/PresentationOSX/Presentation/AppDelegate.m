//
//  AppDelegate.m
//  PickNickChat
//
//  Created by Milan Toth on 03/02/14.
//  Copyright (c) 2014 Milan Toth. All rights reserved.
//

	#import "AppDelegate.h"

	#define WTH 800
	#define HTH 600


	@implementation AppDelegate


	// entering point

	- ( void ) applicationDidFinishLaunching : ( NSNotification* ) theNotification
	{
	
		// create view and window

		NSRect menuViewRect = NSMakeRect( 0 , 0 , WTH ,	HTH );
		NSRect menuWindowRect = NSMakeRect( 100.0 , ( [ [ NSScreen mainScreen ] frame ].size.height - HTH ) / 2 , WTH ,	HTH );

		NSOpenGLPixelFormatAttribute attributes[ ] = { NSOpenGLPFADoubleBuffer , NSOpenGLPFADepthSize ,	16 , 0 };
		NSOpenGLPixelFormat* pixelFormat = [ [ NSOpenGLPixelFormat alloc ] initWithAttributes : attributes ];

		staticDelegate = self;

		menuView = [ [ GLView alloc ]
			initWithFrame : menuViewRect
			pixelFormat : pixelFormat ];

		menuWindow = [ [ NSWindow alloc ]
			initWithContentRect : menuWindowRect
			styleMask : NSTitledWindowMask | NSClosableWindowMask
			backing	: NSBackingStoreBuffered
			defer : YES ];

		[ menuWindow setLevel : NSNormalWindowLevel ];
		[ menuWindow setDelegate : self ];
		[ menuWindow setHasShadow : YES ];
		[ menuWindow setContentView : menuView ];
		[ menuWindow setAcceptsMouseMovedEvents : YES ];
		
		[ menuWindow makeKeyAndOrderFront : self ];
		[ menuWindow makeFirstResponder : menuView ];
		[ menuWindow makeMainWindow ];

		[ self init_simulation ];
        
	}


	// destructor

	- ( void ) dealloc
	{

        dispatch_source_cancel( runTimer );
    
        PRController_release( controller );

		[ menuView release ];
		[ menuWindow release ];
	
		[ super dealloc ];
		
	}


    - ( void ) init_simulation
    {
    
        initTimer = dispatch_source_create( DISPATCH_SOURCE_TYPE_TIMER , 0 , 0 , dispatch_queue_create( "menu" , NULL ) );
        dispatch_source_set_timer( initTimer , DISPATCH_TIME_NOW , (1.0 / 60.0) * NSEC_PER_SEC , 0.25 * NSEC_PER_SEC );
        
        // handlers

        dispatch_source_set_event_handler( initTimer , ^{
        
            [ menuView.openGLContext makeCurrentContext ];
            
            const char* resources_path = [ [ [ NSBundle mainBundle ] resourcePath ] cStringUsingEncoding : NSUTF8StringEncoding ];

            controller = PRController_alloc( );
            PRController_init_width_height_resources_path( controller , WTH , HTH , ( char* ) resources_path );
            PRController_update( controller );
            PRController_render( controller );

            [ menuView.openGLContext flushBuffer ];

            PRController_build( controller );

            dispatch_source_cancel( initTimer );
            
            [ self start_simulation ];

        });

        dispatch_source_set_cancel_handler( initTimer , ^{
            dispatch_release( initTimer );
            
        });
        
        // start threads
        
        dispatch_resume( initTimer );
    }


    - ( void ) start_simulation
    {
    
        runTimer = dispatch_source_create( DISPATCH_SOURCE_TYPE_TIMER , 0 , 0 , dispatch_queue_create( "run" , NULL ) );
        dispatch_source_set_timer( runTimer , DISPATCH_TIME_NOW , (1.0 / 60.0) * NSEC_PER_SEC , 0.25 * NSEC_PER_SEC );
        
        // handlers

        dispatch_source_set_event_handler( runTimer , ^{
        
            [ menuView.openGLContext makeCurrentContext ];
            
            PRController_update( controller );
            PRController_render( controller );

            [ menuView.openGLContext flushBuffer ];

        });

        dispatch_source_set_cancel_handler( runTimer , ^{

            dispatch_release( runTimer );
            
        });
        
        // start threads
        
        dispatch_resume( runTimer );
        
    }


    // oepns url

    - ( void ) openUrl : ( char* ) the_name
    {
    
        NSURL* url;

        // open file

        url = [ NSURL URLWithString : [ NSString stringWithCString : the_name encoding : NSUTF8StringEncoding ] ];
        [ [ NSWorkspace sharedWorkspace ] openURL : url ];
        
    }


	- ( void ) left_pressed
    {
        
        PRController_left_pressed( controller );

    }


	- ( void ) right_pressed
    {
        
        PRController_right_pressed( controller );

    }


	- ( void ) scrollX : ( float ) the_x scrollY : ( float ) the_y
    {
        
        PRController_scroll_x_y( controller , the_x , the_y );

    }


	// mouse up event
	
	- ( void ) mouse_up_at_x_y : ( NSPoint ) theLocation fromView : ( NSView* ) theView
	{
    
        PRController_mouse_up_at_x_y( controller , theLocation.x , theLocation.y );

	}


	// mouse down event

	- ( void ) mouse_down_at_x_y : ( NSPoint ) theLocation fromView : ( NSView* ) theView
	{

        PRController_right_pressed( controller );
        PRController_mouse_down_at_x_y( controller , theLocation.x , theLocation.y );

	}


	// mouse move event

	- ( void ) mouse_move_at_x_y : ( NSPoint ) theLocation fromView : ( NSView* ) theView
	{

        PRController_mouse_move_at_x_y( controller , theLocation.x , theLocation.y );

	}


	- ( void ) key_down_characters : ( char* ) the_characters
    {
    
        PRController_key_down_characters( controller , the_characters );
    
    }


	// close button pressed, quitting application

	- ( void ) windowWillClose : ( NSNotification* ) theNotification
	{
    
        [ [ NSApplication sharedApplication ] terminate : nil ];
		
	}


    // returns static delegate

	static AppDelegate* staticDelegate;

	+ ( AppDelegate* ) sharedDelegate
	{
		return staticDelegate;
	}


	@end


    void openUrl( char* the_name )
    {

    }

    void showKeyboard( )
    {
    
    }

    void hideKeyboard( )
    {
    
    }

