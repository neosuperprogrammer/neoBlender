//
//  nbManager.h
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 8..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#ifndef __NeoBlender__nbManager__
#define __NeoBlender__nbManager__

#include "Matrix.h"
//#include "Object.h"
#include "nbMatrixManager.h"
#include "nbObject.h"

using namespace fgx3;

class nbManager {
    
public:
    static nbMatrixManager *matrixMgr;
    
private:
//    Object *obj;
    nbObject nbObj;
    
    int width, height;
    vec2 touche;
    vec3 rotAngle;;
    
public:
    nbManager() { init(); }
    virtual ~nbManager() {}
    
    void start(int width, int height);
    void draw(void);
    void drawMesh(nbMesh *mesh);
    
    void toucheBegan( float x, float y, unsigned int tap_count );
    void toucheMoved( float x, float y, unsigned int tap_count );
    
private:
    void init();
    void loadObject(void);
    void error(void);
    
    static void programBindAttrLocation(void *ptr);
    static void materialDrawCallback(void *ptr);
};

#endif /* defined(__NeoBlender__nbManager__) */
