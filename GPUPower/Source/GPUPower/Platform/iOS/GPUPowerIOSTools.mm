//
//  GPUPowerIOSTools.m
//  GPUPower
//
//  Created by lingtonke on 2018/10/15.
//  Copyright © 2018 tencent. All rights reserved.
//

#import "GPUPowerIOSTools.h"

@implementation GPUPowerIOSTools

+ (NSData *)dataWithCGImage:(CGImageRef)image
{
    CFDataRef dataFromImageDataProvider = CGDataProviderCopyData(CGImageGetDataProvider(image));;
    NSData *data = (__bridge_transfer NSData*)dataFromImageDataProvider;
    return data;
}

+ (void)setDataForGLTexture:(std::shared_ptr<GPUPower::GLTexture>)texture image:(CGImageRef)image
{
    NSData *data = [self dataWithCGImage:image];
    texture->setImageData(data.bytes, (GLsizei)CGImageGetWidth(image), (GLsizei)CGImageGetHeight(image));
}

@end
