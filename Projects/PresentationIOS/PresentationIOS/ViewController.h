//
//  ViewController.h
//  CerebralCortex
//
//  Created by Milan Toth on 9/14/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController < UIKeyInput >
@property (strong, nonatomic) EAGLContext *context;
@end
