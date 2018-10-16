//
//  GLProgram.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/8.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "../Error.h"
#include "../Util.h"
#include "GLObject.h"
#include <string>
#include <memory>
#include <fstream>
namespace GPUPower
{
    using namespace std;
    class GLProgram:public GLObject
    {
        
        string vertexShaderStr;
        string fragmentShaderStr;
        GLProgram(shared_ptr<GLContext> context): GLObject(context),programID(0),vertexShaderID(0),fragmentShaderID(0){}
    public:
        GLuint programID;
        GLuint vertexShaderID;
        GLuint fragmentShaderID;
        static shared_ptr<GLProgram> create(shared_ptr<GLContext> context)
        {
            return shared_ptr<GLProgram>(new GLProgram(context));
        }
        void loadFromFile(string vertexShaderFile, string fragmentShaderFile)
        {
            auto vs = Util::readFile(vertexShaderFile);
            auto fs = Util::readFile(fragmentShaderFile);
            setShaderString(vs,fs);

        }
        void setShaderString(string vs, string fs)
        {
            vertexShaderStr = vs;
            fragmentShaderStr = fs;
        }
        virtual void init()
        {
            GLint success;
            GLchar infoLog[512];

            const GLchar *const vsStr = vertexShaderStr.c_str();
            const GLchar *const fsStr = fragmentShaderStr.c_str();
            try
            {
                vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShaderID, 1, &vsStr, nullptr);
                glCompileShader(vertexShaderID);
                glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
                    throw Error(GPUPowerError_VertexShaderCompileFailed,infoLog);
                }

                fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShaderID, 1, &fsStr, nullptr);
                glCompileShader(fragmentShaderID);
                glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
                    throw Error(GPUPowerError_FragmentShaderCompileFailed,infoLog);
                }

                programID = glCreateProgram();
                glAttachShader(programID, vertexShaderID);
                glAttachShader(programID, fragmentShaderID);

                GLint linked;

                glLinkProgram(programID);
                glGetProgramiv(programID, GL_LINK_STATUS, &linked);
                if (!linked)
                {
                    glGetProgramInfoLog(programID, 512, nullptr, infoLog);
                    throw Error(GPUPowerError_ProgramLinkFailed,infoLog);
                }
            }
            catch (Error error)
            {
                if (vertexShaderID)
                {
                    glDeleteShader(vertexShaderID);
                }
                if (fragmentShaderID)
                {
                    glDeleteShader(fragmentShaderID);
                }
                if (programID)
                {
                    glDeleteProgram(programID);
                }
                throw error;
            }
        }
        
        virtual void clearup()
        {
            auto c = context.lock();
            GLuint vs = vertexShaderID;
            GLuint fs = fragmentShaderID;
            GLuint p = programID;
            c->checkAndAsyncTask([=]
            {
                if (vs)
                {
                    glDeleteShader(vs);
                }
                if (fs)
                {
                    glDeleteShader(fs);
                }
                if (p)
                {
                    glDeleteProgram(p);
                }
            });
            
            
        }
        
        void use()
        {
            glUseProgram(programID);
        }
    };
}
