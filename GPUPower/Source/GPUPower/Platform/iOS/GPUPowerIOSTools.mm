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
    NSData *data = (__bridge NSData*)dataFromImageDataProvider;
    CFRelease(dataFromImageDataProvider);
    return data;
}

@end
