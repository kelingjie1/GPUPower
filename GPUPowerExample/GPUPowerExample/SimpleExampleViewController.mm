//
//  SimpleExampleViewController.m
//  GPUPowerExample
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//

#import "SimpleExampleViewController.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES3/gl.h>
#import "GPUPower.h"

@interface SimpleExampleViewController ()<GLKViewDelegate>

@property (nonatomic) GLKView *glview;
@property (nonatomic) EAGLContext *context;

@end

@implementation SimpleExampleViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.glview = [[GLKView alloc] initWithFrame:CGRectMake(100, 100, 200, 200)];
    [self.view addSubview:self.glview];
    self.glview.delegate = self;
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    self.glview.context = self.context;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    [EAGLContext setCurrentContext:self.context];
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}


@end
