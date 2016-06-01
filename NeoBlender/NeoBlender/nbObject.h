//
//  nbObject.h
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 9..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#ifndef __NeoBlender__nbObject__
#define __NeoBlender__nbObject__

//#include "Object.h"
#include "nbMesh.h"
#include <vector>

using namespace fgx3;
using namespace std;

class nbMaterial;

class nbObject {
    
private:
    //! The texture path (By default relative to the location of the .mtl file).
    char			texturePath[ MAX_PATH ];
    
public:
    vector<nbMesh *> meshList;
    vector<Texture *> _textureList;
    vector<Program *> _programList;
    vector<nbMaterial *> _materialList;
    VertexManager vertextMgr;
    
public:
    nbObject() { init(); }
    virtual ~nbObject() { freeObj(); }

    void init();
    void freeObj();

    void loadObjFile(char *filename, unsigned char relative_path);
    void buildMaterial(char *vertexShaderFile, char *fragmentShaderFile,
                       PROGRAMBINDATTRIBCALLBACK *programbindattribcallback,
                                 MATERIALDRAWCALLBACK *materialdrawcallback);
    
    void buildNormalAndTangent();
    bool _loadObjFile(char *filename, unsigned char relative_path);
    nbMaterial *getMaterial(const char *name, bool exactName);
    
    unsigned char load_mtl(char *filename, unsigned char relative_path);

    void addProgram(char *filename);
    int getProgramIndex(char *filename);
    Program *getProgram(const char *name, unsigned char exactName);

    nbMesh *getMesh(const char *name, bool exactName );
    int get_mesh_index(const char *name, unsigned char exact_name );
    Texture *get_texture(const char *name, unsigned char exact_name );
    
    void addTexture(char *filename);
    int getTextureIndex(char *filename);
};

#endif /* defined(__NeoBlender__nbObject__) */
