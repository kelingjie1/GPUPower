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
#include "GPUPower.h"
using namespace GPUPower;
@interface SimpleExampleViewController ()<GLKViewDelegate>
{
    shared_ptr<GLRenderNode> node;
    shared_ptr<GLContext> context;
}
@property (nonatomic) GLKView *glview;


@end

@implementation SimpleExampleViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    context = GLContext::create();
    self.glview = [[GLKView alloc] initWithFrame:CGRectMake(100, 100, 200, 200)];
    [self.view addSubview:self.glview];
    self.glview.delegate = self;
    self.glview.context = (__bridge EAGLContext*)context->context;
    
    shared_ptr<GLShaderRenderNode> node0(new GLShaderRenderNode(context));
    node0->program = GLProgram::create(context);
    node0->program->loadFromFile(GPUPower::passThroughVertexShader, GPUPower::passThroughFragmentShader);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}


@end
