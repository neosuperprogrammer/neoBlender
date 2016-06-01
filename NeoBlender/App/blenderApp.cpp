//
//  blenderApp.cpp
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 1. 28..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#include "blenderApp.h"
//#include "glManager2.h"

void BlenderApp::init( int width, int height )
{
    nbMgr->start(width, height);
//    glManager2::getInstance().init(width, height);
}

void BlenderApp::draw( void )
{
//    glManager2::getInstance().draw();
    nbMgr->draw();
}

void BlenderApp::toucheBegan( float x, float y, unsigned int tap_count )
{
//    glManager2::getInstance().toucheBegan(x, y, tap_count);
    nbMgr->toucheBegan(x, y, tap_count);
}

void BlenderApp::toucheMoved( float x, float y, unsigned int tap_count )
{
//    glManager2::getInstance().toucheMoved(x, y, tap_count);
    nbMgr->toucheMoved(x, y, tap_count);
}

void BlenderApp::toucheEnded( float x, float y, unsigned int tap_count )
{
    
}

void BlenderApp::toucheCancelled( float x, float y, unsigned int tap_count )
{
    
}

void BlenderApp::accelerometer( float x, float y, float z )
{
    
}

void BlenderApp::exit( void )
{
//    delete obj;
    delete nbMgr;
}
