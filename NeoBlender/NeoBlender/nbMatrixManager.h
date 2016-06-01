//
//  nbMatrixManager.h
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 8..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#ifndef __NeoBlender__nbMatrixManager__
#define __NeoBlender__nbMatrixManager__

#include <stack>
#include "Matrix.h"

using namespace fgx3;
using namespace std;

typedef enum {
    kModelViewMatrix = 1,
    kProjectionMatrix,
    kTextureMatrix,
} eMatrixMode;

class nbMatrixManager {
    
private:
    stack<mat4> modelViewMatrixList;
    stack<mat4> projectionMatrixList;
    stack<mat4> textureMatrixList;
    mat4 modelViewProjectionMatrix;
    mat3 normalMatrix;
    
    eMatrixMode mode;
    
public:
    nbMatrixManager() { initMatrix(); }
    virtual ~nbMatrixManager() {}
    
    void initMatrix();
    void setMatrixMode(eMatrixMode mode);
    mat4& currentMatrix();

    void loadIdentity();
    void pushMatrix(void);
    void popMatrix(void);
    stack<mat4>& currentMatrixList(void);

    
    void setPerspective(float fovy, float aspect_ratio, float clip_start, float clip_end, float screen_orientation);
    void set_perspective(float left, float right, float bottom, float top, float near, float far, float screen_orientation);
    void multiply(const mat4& m);
    void rotate(float angle, float x, float y, float z);
    void translate(float x, float y, float z);
    void lookAt(vec3& eye, vec3& center, vec3& up);
    void loadMatrix(mat4& m);
    
    void scale(float x, float y, float z);
    mat4& getModelViewMatrix(void);
    mat4& getProjectionMatrix(void);
    mat4& getTextureMatrix(void);
    mat4& getModelViewProjectionMatrix(void);
    mat3& getNormalMatrix(void);

};

#endif /* defined(__NeoBlender__nbMatrixManager__) */
