//
//  GPUPowerGLView.m
//  GPUPower
//
//  Created by lingtonke on 2018/10/15.
//  Copyright © 2018 tencent. All rights reserved.
//

#import "GPUPowerGLView.h"

@implementation GPUPowerGLView

- (void)drawRect:(CGRect)rect
{
    if (self.async)
    {
        
    }
    else
    {
        
    }
}

- (void)setInput:(std::shared_ptr<GPUPower::GLRenderNode>)node
{
    self.node->removeAllInputs();
}

@end
