//
//  nbObject.cpp
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 9..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#include "nbObject.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Texture.h"
#include "utils.h"
#include "nbLog.h"
#include "nbMaterial.h"
#include "Texture.h"
#include "Program.h"

void nbObject::loadObjFile(char *filename, unsigned char relative_path)
{
    _loadObjFile(filename, relative_path);
    
    for (int i = 0; i < meshList.size(); i++) {
        nbMesh *mesh = meshList[i];
        mesh->build(&vertextMgr);
    }
    
    for (int i = 0; i < _textureList.size(); i++) {
        Texture *texture = _textureList[i];
        texture->build(TEXTURE_MIPMAP, TEXTURE_FILTER_2X, 0.0f);
    }
}

void nbObject::buildMaterial(char *vertexShaderFile, char *fragmentShaderFile, PROGRAMBINDATTRIBCALLBACK *programbindattribcallback,
                             MATERIALDRAWCALLBACK *materialdrawcallback)
{
    for (int i = 0; i < _materialList.size(); i++) {
        nbMaterial *material = _materialList[i];
        material->bindTexture(_textureList);
        material->program = Program::create(material->name, vertexShaderFile, fragmentShaderFile, 1, 1, programbindattribcallback, NULL);
        
        material->materialdrawcallback = materialdrawcallback;
    }
}


void nbObject::init()
{
}

bool nbObject::_loadObjFile(char *filename, unsigned char relative_path)
{
    Memory *mem = Memory::open(filename, relative_path);
    
    if (!mem) {
        return false;
    }
    char name [MAX_CHAR] = {0,};
    char group [MAX_CHAR] = {0,};
    char materialName[MAX_CHAR] = {0,};
    char str[MAX_PATH] = {0,};
    char lastChar  = 0;
    char *line = strtok( ( char * )mem->buffer, "\n" );
    
    bool use_smooth_normals = 0;
    
    nbMesh *mesh = NULL;
    
    vec3 v;
    
    //    obj = new Object();
    
    while (line) {
        if (!line[0] || line[0] == '#') {
            goto next_obj_line;
        }
        else if (sscanf(line, "mtllib %s", str) == 1 )
        {
            load_mtl(str, relative_path);
            mem->position = (unsigned int)(( unsigned char * )line - mem->buffer + strlen( line ) + 1);
            line = strtok((char *)&mem->buffer[mem->position], "\n");
            continue;
        }
        else if (sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z) == 3)
        {
            vertextMgr.addUniqueVertex(vec3(v.x, v.y, v.z));
        }
        // Drop the normals.
        else if (sscanf(line, "vn %f %f %f", &v.x, &v.y, &v.z) == 3)
        {
            goto next_obj_line;
        }
        else if (line[ 0 ] == 'v' && line[ 1 ] == 'n')
        {
            goto next_obj_line;
        }
        else if (sscanf(line, "vt %f %f", &v.x, &v.y) == 2)
        {
            vertextMgr.addUniqueUV(vec2(v.x, v.y));
        }
        else if (sscanf(line, "usemtl %s", str) == 1)
        {
            strcpy(materialName, str );
        }
        else if (sscanf(line, "o %s", str ) == 1)
        {
            strcpy( name, str );
        }
        else if (sscanf(line, "g %s", str ) == 1)
        {
            strcpy( group, str );
        }
        else if (sscanf(line, "s %s", str ) == 1)
        {
            use_smooth_normals = 1;
            
            if (strstr( str, "off" ) || strstr( str, "0" )) {
                use_smooth_normals = 0;
            }
        }
        else if (line[0] == 'f' && line[1] == ' ')
        {
            bool useuvs;
            int vertex_index[3] = {0, 0, 0};
            int normal_index[3] = {0, 0, 0};
            int uv_index[3] = {0, 0, 0};
            
            if (sscanf(line, "f %d %d %d", &vertex_index[0],
                       &vertex_index[1],
                       &vertex_index[2] ) == 3 )
            {
                useuvs = 0;
            }
            else if (sscanf(line, "f %d//%d %d//%d %d//%d", &vertex_index[ 0 ],
                            &normal_index[ 0 ],
                            &vertex_index[ 1 ],
                            &normal_index[ 1 ],
                            &vertex_index[ 2 ],
                            &normal_index[ 2 ] ) == 6)
            {
                useuvs = 0;
            }
            
            else if (sscanf(line, "f %d/%d %d/%d %d/%d", &vertex_index[ 0 ],
                            &uv_index    [ 0 ],
                            &vertex_index[ 1 ],
                            &uv_index    [ 1 ],
                            &vertex_index[ 2 ],
                            &uv_index    [ 2 ] ) == 6)
            {
                useuvs = 1;
            }
            else
            {
                sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertex_index[ 0 ],
                       &uv_index    [ 0 ],
                       &normal_index[ 0 ],
                       &vertex_index[ 1 ],
                       &uv_index    [ 1 ],
                       &normal_index[ 1 ],
                       &vertex_index[ 2 ],
                       &uv_index    [ 2 ],
                       &normal_index[ 2 ]);
                useuvs = 1;
            }
            
            if (lastChar != 'f') {
                
                mesh = new nbMesh();
                meshList.push_back(mesh);
                
                if (name[0]) {
                    strcpy(mesh->name, name);
                }
                else if(materialName[0]) {
                    strcpy(mesh->name, materialName);
                }
                
                if (group[0]) {
                    strcpy(mesh->group, group);
                }
                
                mesh->useSmoothNormals = use_smooth_normals;
                mesh->mode = GL_TRIANGLES;
                
                if(useuvs) {
                    mesh->useuvs = useuvs;
                }
                
                if(materialName[0]) {
                    mesh->material = getMaterial(materialName, 1);
                }
                
                name[ 0 ] = 0;
                materialName[ 0 ] = 0;
            }
            
            --vertex_index[ 0 ];
            --vertex_index[ 1 ];
            --vertex_index[ 2 ];
            
            --uv_index[ 0 ];
            --uv_index[ 1 ];
            --uv_index[ 2 ];
            
            mesh->addVertexIndex(vertex_index[0], uv_index[0]);
            mesh->addVertexIndex(vertex_index[1], uv_index[1]);
            mesh->addVertexIndex(vertex_index[2], uv_index[2]);
            
            // normal, tanget 를 계산하기 위한 자료 구죠.
            OBJTRIANGLEINDEX triangleIndex = {vertex_index[0], vertex_index[1], vertex_index[2], uv_index[0], uv_index[1], uv_index[2]};
            vertextMgr.triangleIndexList.push_back(triangleIndex);
        }
        
    next_obj_line:
        
        lastChar = line[0];
        line = strtok(NULL, "\n");
    }
    
    delete mem;
    
    buildNormalAndTangent();
    
    return true;
}


void nbObject::buildNormalAndTangent()
{
    vertextMgr.buildNormalAndTangent();
    
    // Normalize Normals & Tangent
    for (int i = 0; i < meshList.size(); i++) {
        nbMesh *mesh = meshList[i];
        for (int j = 0; j < mesh->uniqueVertexUVIndexList.size(); j++) {
            UniqueVertexUVIndex index = mesh->uniqueVertexUVIndexList[j];
            vertextMgr.uniqueNormalList[index.vertexIndex].normalize();
            if(index.uvIndex != -1 ) {
                vertextMgr.uniqueTangentList[index.vertexIndex].normalize();
            }
        }
    }
    
}
/*!
 Helper function to load an MTL file.
 
 \param[in,out] obj A valid OBJ structure pointer.
 \param[in] filename The .MTL filename to load.
 \param[in] relative_path Determine if the filename is relative to the application or an absolute path.
 
 \return Return 1 if the file was loaded successfully, else return 0.
 */
unsigned char nbObject::load_mtl(char *filename, unsigned char relative_path)
{
    Memory *m = Memory::open(filename, relative_path);
    
//    OBJMATERIAL *objmaterial = NULL;
    nbMaterial *material = NULL;
    
    if( !m ) return 0;
    
//    get_file_path( m->filename, texturePath );
    getPathFromFilePath(texturePath, m->filename);
    
//    get_file_path( m->filename, programPath );
    
    char *line = strtok( ( char * )m->buffer, "\n" ),
    str[ MAX_PATH ] = {""};
    
    vec3 v;
    
    while( line )
    {
        if( !line[ 0 ] || line[ 0 ] == '#' ) goto next_mat_line;
        
        else if( sscanf( line, "newmtl %s", str ) == 1 )
        {
            material = new nbMaterial;
            strcpy(material->name, str);
            _materialList.push_back(material);
        }
        else if( sscanf( line, "Ka %f %f %f", &v.x, &v.y, &v.z ) == 3 )
        {
            memcpy( &material->ambient, &v, sizeof( vec3 ) );
        }
        else if( sscanf( line, "Kd %f %f %f", &v.x, &v.y, &v.z ) == 3 )
        {
            memcpy( &material->diffuse, &v, sizeof( vec3 ) );
        }
        else if( sscanf( line, "Ks %f %f %f", &v.x, &v.y, &v.z ) == 3 )
        {
            memcpy( &material->specular, &v, sizeof( vec3 ) );
        }
        else if( sscanf( line, "Tf %f %f %f", &v.x, &v.y, &v.z ) == 3 )
        {
            memcpy( &material->transmission_filter, &v, sizeof( vec3 ) );
        }
        else if( sscanf( line, "illum %f", &v.x ) == 1 )
        {
            material->illumination_model = ( int )v.x;
        }
        else if( sscanf( line, "d %f", &v.x ) == 1 )
        {
            material->ambient.w  = v.x;
            material->diffuse.w  = v.x;
            material->specular.w = v.x;
            material->dissolve   = v.x;
        }
        else if( sscanf( line, "Ns %f", &v.x ) == 1 )
        {
            material->specular_exponent = v.x;
        }
        else if( sscanf( line, "Ni %f", &v.x ) == 1 )
        {
            material->optical_density = v.x;
        }
        else if( sscanf( line, "map_Ka %s", str ) == 1 )
        {
            getFileNameFromFilePath(material->map_ambient, str);
            addTexture(material->map_ambient );
        }
        else if( sscanf( line, "map_Kd %s", str ) == 1 )
        {
            getFileNameFromFilePath(material->map_diffuse, str);
            addTexture(material->map_diffuse );
        }
        else if( sscanf( line, "map_Ks %s", str ) == 1 )
        {
            getFileNameFromFilePath(material->map_specular, str);
            addTexture(material->map_specular );
        }
        else if( sscanf( line, "map_Tr %s", str ) == 1 )
        {
            getFileNameFromFilePath(material->map_translucency, str);
            addTexture(material->map_translucency );
        }
        
        else if( sscanf( line, "map_disp %s", str ) == 1 ||
                sscanf( line, "map_Disp %s", str ) == 1 ||
                sscanf( line, "disp %s"    , str ) == 1 )
        {
            getFileNameFromFilePath(material->map_disp, str);
            addTexture(material->map_disp );
        }
        else if( sscanf( line, "map_bump %s", str ) == 1 ||
                sscanf( line, "map_Bump %s", str ) == 1 ||
                sscanf( line, "bump %s"	, str ) == 1 )
        {
            getFileNameFromFilePath(material->map_bump, str);
            addTexture(material->map_bump );
        }
        
    next_mat_line:
        
        line = strtok( NULL, "\n" );
    }
    
    delete m;
    
    return 1;
}

void nbObject::freeObj()
{
    for (int i =0; i < _materialList.size(); i++) {
        nbMaterial *material = _materialList[i];
        delete material->program;
        delete material;
    }
    
    _materialList.clear();

    
    for (int i = 0; i < _programList.size(); i++) {
        Program *program = _programList[i];
        delete program;
    }
    _programList.clear();
    

    for (int i = 0; i < _textureList.size(); i++) {
        Texture *texture = _textureList[i];
        delete texture;
    }
    _textureList.clear();

}

nbMaterial *nbObject::getMaterial(const char *name, bool exactName)
{
    for (int i = 0; i < _materialList.size(); i++) {
        nbMaterial *material = _materialList[i];
        if (exactName) {
            if (!strcmp(material->name, name)) {
                return material;
            }
        }
        else {
            if (strstr(material->name, name)) {
                return material;
            }
        }
    }
    return NULL;
}

void nbObject::addProgram(char *filename)
{
    if (getProgramIndex(filename) != -1) {
        return;
    }
    
    _programList.push_back(new Program(filename));
}


int nbObject::getProgramIndex(char *filename)
{
    for (int i = 0; i < _programList.size(); i++) {
        Program *program = _programList[i];
        if (!strcmp(filename, program->name)) {
            return i;
        }
    }
    return -1;
}

Program *nbObject::getProgram(const char *name, unsigned char exactName )
{
    for (int i = 0; i < _programList.size(); i++) {
        Program *program = _programList[i];
        if (exactName) {
            if (!strcmp(program->name, name)) {
                return program;
            }
        }
        else {
            if (strstr(program->name, name)) {
                return program;
            }
        }

    }
    return NULL;
}

void nbObject::addTexture(char *filename)
{
    if (getTextureIndex(filename ) != -1) {
        return;
    }
    
    Texture *texture = new Texture(filename);
    strcpy(texture->fullPath, texturePath);
    _textureList.push_back(texture);
}

int nbObject::getTextureIndex(char *filename)
{
    for (int i = 0; i < _textureList.size(); i++) {
        if (!strcmp(filename, _textureList[ i ]->name)) {
            return i;
        }
    }
    return -1;
}

nbMesh *nbObject::getMesh(const char *name, bool exactName )
{
    for (int i = 0; i < meshList.size(); i++) {
        nbMesh *mesh = meshList[i];
        if( exactName )
        { if( !strcmp( mesh->name, name ) ) return mesh; }
        
        else
        { if( strstr( mesh->name, name ) ) return mesh; }
    }
    
    return NULL;
}


int nbObject::get_mesh_index(const char *name, unsigned char exactName )
{
    for (int i = 0; i < meshList.size(); i++) {
        nbMesh *mesh = meshList[i];
        if( exactName )
        { if( !strcmp( mesh->name, name ) ) return i; }
        
        else
        { if( strstr( mesh->name, name ) ) return i; }
    }
    
    return -1;
}

Texture *nbObject::get_texture(const char *name, unsigned char exact_name )
{
    for (int i = 0; i < _textureList.size(); i++) {
        if( exact_name )
        { if( !strcmp( _textureList[ i ]->name, name ) ) return _textureList[ i ]; }
        
        else
        { if( strstr(_textureList[ i ]->name, name ) ) return _textureList[ i ]; }
    }
    
    return NULL;
}


