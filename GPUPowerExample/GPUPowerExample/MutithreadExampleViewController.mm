//
//  MutithreadExampleViewController.m
//  GPUPowerExample
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//

#import "MutithreadExampleViewController.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES3/gl.h>
#include "GPUPower.h"
#include "GPUPower/Platform/iOS/GPUPowerIOSTools.h"
using namespace GPUPower;
@interface MutithreadExampleViewController ()<GLKViewDelegate>
{
    shared_ptr<GLRenderNode> node;
    shared_ptr<GLShareGroup> shareGroup;
    shared_ptr<GLContext> mainContext;
    shared_ptr<GLContext> renderContext;
}
@property (nonatomic) GPUPowerGLView *glview;


@end

@implementation MutithreadExampleViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    shareGroup = GLShareGroup::create();
    mainContext = GLContext::createMainThreadContext(shareGroup);
    renderContext = GLContext::create(shareGroup);
    self.glview = [[GPUPowerGLView alloc] initWithFrame:CGRectMake(100, 100, 200, 200)];
    self.glview.glcontext = mainContext;
    [self.view addSubview:self.glview];
    
    NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Resource/image0.png"];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    
    shared_ptr<GLTextureNode> textureNode(new GLTextureNode(renderContext));
    auto texture = GLTexture::create(renderContext);
    [GPUPowerIOSTools setDataForGLTexture:texture image:image.CGImage];
    textureNode->setTexture(texture);
    [self.glview setInput:textureNode];
    
    shared_ptr<GLShaderRenderNode> node0(new GLShaderRenderNode(renderContext));
    node0->program = GLProgram::create(renderContext);
    node0->program->loadFromFile(GPUPower::passThroughVertexShader, GPUPower::passThroughFragmentShader);
    
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}


@end
