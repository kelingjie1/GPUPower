//
//  Error.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#include <exception>
#include <string>
namespace GPUPower
{
    using namespace std;
    enum GPUPowerError
    {
        GPUPowerError_Unknow,
        
        GPUPowerError_InputNodeNotFound,
        GPUPowerError_OutputNodeNotFound,
        
        GPUPowerError_GLError,
        
        GPUPowerError_ContextCreateFailed,
        GPUPowerError_ContextCheckFailed,
        GPUPowerError_VertexShaderCompileFailed,
        GPUPowerError_FragmentShaderCompileFailed,
        GPUPowerError_ProgramLinkFailed,
        GPUPowerError_MapBufferFailed,
        GPUPowerError_UnMapBufferFailed,
        
        
    };
    
    class Error:public exception
    {
    public:
        Error(GPUPowerError error,int internalCode,string detail=""):code(error),internalCode(0),detail(detail){}
        Error(GPUPowerError error=GPUPowerError_Unknow,string detail=""):code(error),internalCode(0),detail(detail){}
        GPUPowerError code;
        int internalCode;
        string detail;
    };
}
