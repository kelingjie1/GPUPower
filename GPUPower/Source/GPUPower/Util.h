//
//  Util.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/11.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#define GPSTRING(x) #x

#include <string>
#include <fstream>



namespace GPUPower
{
    using namespace std;
    static const string passThroughVertexShader = string("#version 300 es\n")+
    GPSTRING(
             precision highp float;
             layout(location = 0) in vec2 position;
             layout(location = 1) in vec2 coord;
             out vec2 uv;
             void main()
             {
                 uv = coord;
             }
    );
    static const string passThroughFragmentShader = string("#version 300 es\n")+
    GPSTRING(
             precision highp float;
             layout(location = 0) out vec4 color;
             uniform sampler2D tex;
             in vec2 uv;
             void main()
             {
                 color = texture(tex, uv);
             }
             );
    class Util
    {
    public:
        static string readFile(string file)
        {
            char buf[1000];
            string str;
            fstream f(file);
            long getCount = 0;
            do
            {
                f.read(buf, 1000);
                getCount = f.gcount();
                str.append(buf, getCount);
            }
            while (getCount>0);
            return str;
        }
    };
}
