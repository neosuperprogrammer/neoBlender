//
//  blenderApp.h
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 1. 28..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#ifndef __NeoBlender__blenderApp__
#define __NeoBlender__blenderApp__

//#include "fgx3/glState.h"

//using namespace fgx3;

#include "nbManager.h"

class BlenderApp {
    
private:
//    Object *obj;
    nbManager *nbMgr;
    
public:
    BlenderApp() { nbMgr = new nbManager; };
    
    virtual ~BlenderApp() { exit(); };

    void init( int width, int height );
    
    void draw( void );
    
    void toucheBegan( float x, float y, unsigned int tap_count );
    
    void toucheMoved( float x, float y, unsigned int tap_count );
    
    void toucheEnded( float x, float y, unsigned int tap_count );
    
    void toucheCancelled( float x, float y, unsigned int tap_count );
    
    void accelerometer( float x, float y, float z );
    
    void exit( void );
    
    
    static void program_bind_attrib_location( void *ptr );
    static void material_draw_callback( void *ptr );
};

//extern BlenderApp blenderApp;

#endif /* defined(__NeoBlender__blenderApp__) */
