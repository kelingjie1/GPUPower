//
//  GLVertexArray.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/10.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include <string>
#include <memory>
#include <vector>
#include "GLBuffer.h"
#include "../Error.h"
namespace GPUPower
{
    using namespace std;
    class GLBaseVertex;
    template<class vboType=GLBaseVertex,class eboType = unsigned char>
    class GLVertexArray;
    
    static shared_ptr<GLVertexArray<GLBaseVertex>> basicVertexArrayInstance;
    class GLBaseVertex
    {
    public:
        GLfloat x;
        GLfloat y;
        GLfloat u;
        GLfloat v;
    };
    class GLVertexArrayParams
    {
    public:
        GLuint index;
        GLint size;
        GLenum type;
    };
    
    template<class vboType,class eboType>
    class GLVertexArray:public GLObject
    {
        GLuint vao;
        GLenum mode;
        shared_ptr<GLBuffer<vboType>> vertexbuffer;
        shared_ptr<GLBuffer<eboType>> elementBuffer;
    public:
        GLVertexArray(shared_ptr<GLContext> context):GLObject(context){}
        virtual void init()
        {
            GLObject::init();
            glGenVertexArrays(1, &vao);
            if (!vao)
            {
                throw Error();
            }
        }
        
        void setVertexBuffer(shared_ptr<GLBuffer<vboType>> vertexbuffer)
        {
            auto c = context.lock();
            c->check();
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer->bufferID);
            glBindVertexArray(0);
        }
        void setElementBuffer(shared_ptr<GLBuffer<vboType>> elementbuffer)
        {
            auto c = context.lock();
            c->check();
            glBindVertexArray(vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer->bufferID);
            glBindVertexArray(0);
        }
        
        
        void setParams(vector<GLVertexArrayParams> params)
        {
            auto c = context.lock();
            c->check();
            for (int i=0; i<params.size(); i++)
            {
                glEnableVertexAttribArray(i);
            }
            GLint maxAttributes = 0;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
            for (int i=params.size(); i<maxAttributes; i++)
            {
                glDisableVertexAttribArray(i);
            }
        }
        
        void setDrawMode(GLenum mode)
        {
            this->mode = mode;
        }
        
        void draw(GLsizei count=0)
        {
            auto c = context.lock();
            c->check();
            glBindVertexArray(vao);
            if (elementBuffer)
            {
                if (count == 0)
                {
                    count = elementBuffer->count;
                }
                GLenum type;
                if (sizeof(eboType) == sizeof(unsigned char))
                {
                    type = GL_UNSIGNED_BYTE;
                }
                else if (sizeof(eboType) == sizeof(unsigned short))
                {
                    type = GL_UNSIGNED_SHORT;
                }
                else if (sizeof(eboType) == sizeof(unsigned int))
                {
                    type = GL_UNSIGNED_INT;
                }
                else
                {
                    throw "";
                }
                glDrawElements(mode, count, type, nullptr);
            }
            else
            {
                if (count == 0)
                {
                    count = vertexbuffer->count;
                }
                glDrawArrays(mode, 0, count);
            }
            
            glBindVertexArray(0);
        }
        
        static shared_ptr<GLVertexArray<GLBaseVertex>> basicVertexArray()
        {
            if (!basicVertexArrayInstance)
            {
                basicVertexArrayInstance = make_shared<GLVertexArray<GLBaseVertex>>();
                
                auto buffer = make_shared<GLBuffer<GLBaseVertex>>();
                buffer->alloc(4);
                auto vertex = buffer->lock();
                vertex[0].x = -1.0f;
                vertex[0].y = -1.0f;
                vertex[0].u = 0.0f;
                vertex[0].v = 0.0f;
                
                vertex[1].x = 1.0f;
                vertex[1].y = -1.0f;
                vertex[1].u = 1.0f;
                vertex[1].v = 0.0f;
                
                vertex[2].x = -1.0f;
                vertex[2].y = 1.0f;
                vertex[2].u = 0.0f;
                vertex[2].v = 1.0f;
                
                vertex[3].x = 1.0f;
                vertex[3].y = 1.0f;
                vertex[3].u = 1.0f;
                vertex[3].v = 1.0f;
                buffer->unlock();
                basicVertexArrayInstance->setDrawMode(GL_TRIANGLE_FAN);
                basicVertexArrayInstance->setVertexBuffer(buffer);
            }
            return basicVertexArrayInstance;
        }
    };
}
