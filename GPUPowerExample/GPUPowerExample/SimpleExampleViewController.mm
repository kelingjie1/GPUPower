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
#include "GPUPower/Platform/iOS/GPUPowerIOSTools.h"
using namespace GPUPower;
@interface SimpleExampleViewController ()<GLKViewDelegate>
{
    shared_ptr<GLRenderNode> node;
    shared_ptr<GLContext> context;
}
@property (nonatomic) GPUPowerGLView *glview;


@end

@implementation SimpleExampleViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    context = GLContext::createMainThreadContext();
    self.glview = [[GPUPowerGLView alloc] initWithFrame:CGRectMake(100, 100, 200, 200)];
    self.glview.glcontext = context;
    [self.view addSubview:self.glview];
    
    NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Resource/image0.png"];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    
    shared_ptr<GLTextureNode> textureNode(new GLTextureNode(context));
    auto texture = GLTexture::create(context);
    [GPUPowerIOSTools setDataForGLTexture:texture image:image.CGImage];
    textureNode->setTexture(texture);
    [self.glview setInput:textureNode];
    
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
