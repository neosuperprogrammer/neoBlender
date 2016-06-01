//
//  nbMatrixManager.cpp
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 8..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#include "nbMatrixManager.h"
//#include <pthread.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <math.h>
//#include <ctype.h>
//#include <stdarg.h>
//#include <sys/time.h>
//#include <unistd.h>

void nbMatrixManager::initMatrix()
{
    modelViewMatrixList.push(*(new mat4()));
    projectionMatrixList.push(*(new mat4()));
    textureMatrixList.push(*(new mat4()));
    
    mode = kModelViewMatrix;
}

void nbMatrixManager::setMatrixMode(eMatrixMode mode)
{
    this->mode = mode;
}

mat4& nbMatrixManager::currentMatrix()
{
    return currentMatrixList().top();
}

void nbMatrixManager::pushMatrix(void)
{
    mat4 m;
    m.copy(currentMatrix());
    currentMatrixList().push(m);
}

void nbMatrixManager::popMatrix(void)
{
    currentMatrixList().pop();
}

stack<mat4>& nbMatrixManager::currentMatrixList(void)
{
    switch (mode) {
        case kModelViewMatrix: {
            return modelViewMatrixList;
            break;
        }
        case kProjectionMatrix: {
            return projectionMatrixList;
            break;
        }
        case kTextureMatrix: {
            return textureMatrixList;
            break;
        }
    }
}

void nbMatrixManager::loadIdentity()
{
    currentMatrix().identity();
}

void nbMatrixManager::setPerspective(float fovy, float aspect_ratio, float clip_start, float clip_end, float screen_orientation)
{

    float top = clip_start * tanf(fovy * 3.14 / 360.0f);
    float bottom = -top;
    float left = bottom * aspect_ratio;
    float right = top * aspect_ratio;
    
    set_perspective(left, right, bottom, top, clip_start, clip_end, screen_orientation);

}

void nbMatrixManager::set_perspective(float left, float right, float bottom, float top, float near, float far, float screen_orientation)
{
    mat4 mat;
    
    float a = 2 * near / (right - left);
    float b = 2 * near / (top - bottom);
    float c = (right + left) / (right - left);
    float d = (top + bottom) / (top - bottom);
    float e = - (far + near) / (far - near);
    float f = -2 * far * near / (far - near);
    
    //	mat4_identity( &mat );
    mat.identity();
    
    mat.m[ 0 ].x = a;
    mat.m[ 1 ].y = b;
    mat.m[ 2 ].x = c;
    mat.m[ 2 ].y = d;
    mat.m[ 2 ].z = e;
    mat.m[ 2 ].w = -1.0f;
    mat.m[ 3 ].z = f;
    mat.m[ 3 ].w = 1.0f;
    
    multiply(mat);
    
    if (screen_orientation) {
        rotate(screen_orientation, 0.0f, 0.0f, 1.0f);
    }
}

void nbMatrixManager::multiply(const mat4& m)
{
    currentMatrix() = currentMatrix().multiply(m);
}

void nbMatrixManager::rotate(float angle, float x, float y, float z)
{
    if (!angle) {
        return;
    }
    
    vec4 v = vec4(x, y, z, angle);
    currentMatrix().rotate(v);
}

void nbMatrixManager::lookAt(vec3& eye, vec3& center, vec3& up)
{
    vec3 f, s, u;
    
    mat4 mat;
    
    //	mat4_identity( &mat );
    mat.identity();
    
    //	vec3_diff( &f, center, eye );
    f = center.diff(eye);
    
    //	vec3_normalize( &f, &f );
    
    f.normalize();
    
    //	vec3_cross( &s, &f, up );
    s = f.cross(up);
    
    //	vec3_normalize( &s, &s );
    s.normalize();
    
    //	vec3_cross( &u, &s, &f );
    u = s.cross(f);
    
    mat.m[ 0 ].x = s.x;
    mat.m[ 1 ].x = s.y;
    mat.m[ 2 ].x = s.z;
    
    mat.m[ 0 ].y = u.x;
    mat.m[ 1 ].y = u.y;
    mat.m[ 2 ].y = u.z;
    
    mat.m[ 0 ].z = -f.x;
    mat.m[ 1 ].z = -f.y;
    mat.m[ 2 ].z = -f.z;
    
    multiply(mat);
    
    translate(-eye.x, -eye.y, -eye.z);
}


void nbMatrixManager::translate(float x, float y, float z)
{
    vec3 v = vec3(x, y, z);
    
    currentMatrix().translate(currentMatrix(), v);
}

void nbMatrixManager::loadMatrix(mat4& m)
{
    currentMatrix() = m;
}


void nbMatrixManager::scale(float x, float y, float z)
{
    static vec3 scale = vec3(1.0f, 1.0f, 1.0f);
    
    vec3 v = vec3(x, y, z);
    
    if( !memcmp( &v, &scale, sizeof( vec3 ) ) ) return;
    
    currentMatrix() = currentMatrix().scale(v);
}


/*!
 Return the modelview matrix pointer on the top of the modelview matrix stack.
 
 \return Return a 4x4 matrix pointer of the top most modelview matrix.
 */
mat4& nbMatrixManager::getModelViewMatrix(void)
{
    return modelViewMatrixList.top();
}


/*!
 Return the projection matrix pointer on the top of the projection matrix stack.
 
 \return  Return a 4x4 matrix pointer of the top most projection matrix index.
 */
mat4& nbMatrixManager::getProjectionMatrix(void)
{
    return projectionMatrixList.top();
}


/*!
 Return the texture matrix pointer on the top of the texture matrix stack.
 
 \return  Return a 4x4 matrix pointer of the top most texture matrix index.
 */
mat4& nbMatrixManager::getTextureMatrix(void)
{
    return textureMatrixList.top();
}


/*!
 Return the result of the of the top most modelview matrix multiplied by the top
 most projection matrix.
 
 \return Return the 4x4 matrix pointer of the projection matrix index.
 */
mat4& nbMatrixManager::getModelViewProjectionMatrix(void)
{
    modelViewProjectionMatrix = getProjectionMatrix().multiply(getModelViewMatrix());
    return modelViewProjectionMatrix;
}


/*!
 Return the result of the inverse and transposed operation of the top most modelview matrix applied
 on the rotation part of the matrix.
 
 \return Return the 3x3 matrix pointer that represent the invert and transpose
 result of the top most model view matrix.
 */
mat3& nbMatrixManager::getNormalMatrix(void)
{
    mat4 mat = getModelViewMatrix();
    mat.invertFull();
    mat.transpose();
    normalMatrix.copy(mat);
    
    return normalMatrix;
}



