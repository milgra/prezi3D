//
//  AppDelegate.m
//  PickNickChat
//
//  Created by Milan Toth on 12/03/14.
//  Copyright (c) 2014 Milan Toth. All rights reserved.
//

	#import "AppDelegate.h"


	#define WTH 800
	#define HTH 600


	@implementation AppDelegate


	// application entering point

	- ( BOOL ) 	application					  : ( UIApplication* ) theApplication 
				didFinishLaunchingWithOptions : ( NSDictionary*  ) theOptions
	{

		[ [ UIApplication sharedApplication ] setStatusBarHidden : YES ];

		staticDelegate 	 = self;
		prController     = NULL;

		window 			 = [ [ UIWindow alloc ] initWithFrame : [ [ UIScreen mainScreen ] bounds ] ];
		controller 		 = [ [ ViewController alloc ] init ];
        
        width =  ([ [ UIScreen mainScreen ] bounds ]).size.width * [[UIScreen mainScreen] scale];
        height =  ([ [ UIScreen mainScreen ] bounds ]).size.height * [[UIScreen mainScreen] scale];
		
		[ window setRootViewController : controller ];
		[ window makeKeyAndVisible ];

		return YES;
		
	}


	// destructor

	- ( void ) dealloc
	{

		[ controller release ];
		[ window 	 release ];
		
		if ( prController != NULL )	PRController_release( prController );

		[ super dealloc ];

	}
	
	
	// scene setup, ignited from viewcontroller

	- ( void ) setupScene
	{

		if ( prController == NULL )
		{
        
            const char* resources_path = [ [ [ NSBundle mainBundle ] resourcePath ] cStringUsingEncoding : NSUTF8StringEncoding ];

            prController = PRController_alloc( );
            PRController_init_width_height_resources_path( prController , WTH , HTH , ( char* ) resources_path );
            PRController_build( prController );
            
		}

        // [controller becomeFirstResponder];

	}
	
	
	// updates simulation and renders scene

	- ( void ) render
	{

		if ( prController != NULL )
		{

			PRController_update( prController );
			PRController_render( prController );
			
		}

	}

    - ( void ) showKeyboard
    {
        if ( [ NSThread currentThread ] != [ NSThread mainThread ] )
        {
            [self performSelectorOnMainThread:@selector(showKeyboard) withObject:nil waitUntilDone:NO];
        }
        else
        {
            printf( "\nshowkeyboard" );
            [controller becomeFirstResponder];
        }
    }


    - ( void ) hideKeyboard
    {
        printf( "\nhidekeyboard" );
        [controller resignFirstResponder];
    }


	// touch events

	- ( void ) touchStart : ( CGPoint ) theLocation
	{
	
		float x = theLocation.x * [[UIScreen mainScreen] scale];
		float y = ( controller.view.bounds.size.height - theLocation.y ) * [[UIScreen mainScreen] scale];
        
		PRController_mouse_down_at_x_y( prController , x , y );
        
        if ( x < controller.view.bounds.size.height / 2 ) PRController_left_pressed( prController );
        else PRController_right_pressed( prController );
		
	}
	

	- ( void ) touchMove : ( CGPoint ) theLocation
	{

		float x = theLocation.x * [[UIScreen mainScreen] scale];
		float y = ( controller.view.bounds.size.height - theLocation.y ) * [[UIScreen mainScreen] scale];

		PRController_mouse_move_at_x_y( prController , x , y );
		
	}


	- ( void ) touchEnd : ( CGPoint ) theLocation
	{

		float x = theLocation.x * [[UIScreen mainScreen] scale];
		float y = ( controller.view.bounds.size.height - theLocation.y * [[UIScreen mainScreen] scale] );

		PRController_mouse_up_at_x_y( prController , x , y );
		
	}


	- ( void ) key_down_characters : ( char* ) the_characters
    {
    
        PRController_key_down_characters( prController , the_characters );
    
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
        [staticDelegate showKeyboard];
    }

    void hideKeyboard( )
    {
        [staticDelegate hideKeyboard];
    }
