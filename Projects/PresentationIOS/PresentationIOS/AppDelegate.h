//
//  AppDelegate.h
//  PickNickChat
//
//  Created by Milan Toth on 12/03/14.
//  Copyright (c) 2014 Milan Toth. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ViewController.h"
#import "clcsrc.h"


	@class ViewController;
	

	@interface AppDelegate : UIResponder <UIApplicationDelegate>
	{
    
        float width;
        float height;

		NSTimer*					sceneTimer;
		UIWindow* 					window;
		ViewController*				controller;
        struct PRController*        prController;
		
	}

	- ( void ) render;
	- ( void ) setupScene;
	- ( void ) touchEnd   : ( CGPoint ) theLocation;
	- ( void ) touchMove  : ( CGPoint ) theLocation;
	- ( void ) touchStart : ( CGPoint ) theLocation;
	- ( void ) key_down_characters : ( char* ) the_characters;
	- ( void ) showKeyboard;
	- ( void ) hideKeyboard;

	+ ( AppDelegate* ) sharedDelegate;


@end
