//
//  ViewController.m
//  CerebralCortex
//
//  Created by Milan Toth on 9/14/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#import "ViewController.h"
#import "AppDelegate.h"

@implementation ViewController

- (void)dealloc
{
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }    
    [_context release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
	
	self.preferredFramesPerSecond = 60;
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
	view.multipleTouchEnabled = YES;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat16;
    view.contentScaleFactor = [[UIScreen mainScreen] scale];

   [EAGLContext setCurrentContext:self.context];
    
}

- (void)viewDidLayoutSubviews
{

   [ [ AppDelegate sharedDelegate ] setupScene ]; 

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [ touches anyObject ];
    CGPoint location = [touch locationInView: self.view];
	
	[ [ AppDelegate sharedDelegate ] touchStart : location ];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [ touches anyObject ];
    CGPoint location = [touch locationInView: self.view];
	
	[ [ AppDelegate sharedDelegate ] touchMove : location ];
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [ touches anyObject ];
    CGPoint location = [touch locationInView: self.view];
	
	[ [ AppDelegate sharedDelegate ] touchEnd : location ];
}

- (void)update
{
	[ [ AppDelegate sharedDelegate ] render ];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{

}

- (void)insertText:(NSString *)text {
    // Do something with the typed character
    [ [ AppDelegate sharedDelegate ] key_down_characters : ( char* ) [ text cStringUsingEncoding:NSUTF8StringEncoding ] ];
}
- (void)deleteBackward {
    // Handle the delete key
}
- (BOOL)hasText {
    // Return whether there's any text present
    return YES;
}

- (BOOL)canBecomeFirstResponder {
    return NO;
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

@end
