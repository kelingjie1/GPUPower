//
//  GPUPowerIOSTools.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/15.
//  Copyright © 2018 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "../../OpenGL/GLTexture.h"

NS_ASSUME_NONNULL_BEGIN

@interface GPUPowerIOSTools : NSObject

+ (NSData*)dataWithCGImage:(CGImageRef)image;
+ (void)setDataForGLTexture:(std::shared_ptr<GPUPower::GLTexture>)texture image:(CGImageRef)image;


@end

NS_ASSUME_NONNULL_END
