//
//  Util.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/11.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once
#include <string>
#include <fstream>

namespace GPUPower
{
    using namespace std;
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
