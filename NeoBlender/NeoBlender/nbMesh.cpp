//
//  nbMesh.cpp
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 10..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#include "nbMesh.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdlib.h>
#include "nbLog.h"
#include "nbObject.h"

void VertexManager::addUniqueVertex(vec3 vertex)
{
    uniqueVertexList.push_back(vertex);
    uniqueNormalList.push_back(vec3(0,0,0));
    uniqueFaceNormalList.push_back(vec3(0,0,0));
    uniqueTangentList.push_back(vec3(0,0,0));
}

void VertexManager::addUniqueUV(vec2 uv)
{
    uv.y = 1.0f - uv.y;
    uniqueUVList.push_back(uv);
}

void VertexManager::buildNormalAndTangent()
{
    vec3 v1, v2, normal;
    
    for (int j = 0; j < triangleIndexList.size(); j++) {
        OBJTRIANGLEINDEX triangleIndex = triangleIndexList[j];
        vec3 vertex0 = uniqueVertexList[triangleIndex.vertex_index[0]];
        vec3 vertex1 = uniqueVertexList[triangleIndex.vertex_index[1]];
        vec3 vertex2 = uniqueVertexList[triangleIndex.vertex_index[2]];
        
        v1 = vertex0.diff(vertex1);
        v2 = vertex0.diff(vertex2);
        
        normal = v1.cross(v2);
        normal.normalize();
        
        // Face normals
        uniqueFaceNormalList[triangleIndex.vertex_index[0]] = normal;
        uniqueFaceNormalList[triangleIndex.vertex_index[1]] = normal;
        uniqueFaceNormalList[triangleIndex.vertex_index[2]] = normal;
        
        
        // Smooth normals
        uniqueNormalList[triangleIndex.vertex_index[0]] = uniqueNormalList[triangleIndex.vertex_index[0]].add(normal);
        uniqueNormalList[triangleIndex.vertex_index[1]] = uniqueNormalList[triangleIndex.vertex_index[1]].add(normal);
        uniqueNormalList[triangleIndex.vertex_index[2]] = uniqueNormalList[triangleIndex.vertex_index[2]].add(normal);
        
        if(triangleIndex.uv_index[0] >= 0) {
            vec3 tangent;
            
            vec2 uv1, uv2;
            
            vec2 uuv0 = uniqueUVList[triangleIndex.uv_index[0]];
            vec2 uuv1 = uniqueUVList[triangleIndex.uv_index[1]];
            vec2 uuv2 = uniqueUVList[triangleIndex.uv_index[2]];
            
            
            
            float c;
            uv1 = uuv2.diff(uuv0);
            uv2 = uuv1.diff(uuv0);
            c = 1.0f / ( uv1.x * uv2.y - uv2.x * uv1.y );
            
            tangent.x = ( v1.x * uv2.y + v2.x * uv1.y ) * c;
            tangent.y = ( v1.y * uv2.y + v2.y * uv1.y ) * c;
            tangent.z = ( v1.z * uv2.y + v2.z * uv1.y ) * c;
            
            
            uniqueTangentList[triangleIndex.vertex_index[0]] = uniqueTangentList[triangleIndex.vertex_index[0]].add(tangent);
            uniqueTangentList[triangleIndex.vertex_index[1]] = uniqueTangentList[triangleIndex.vertex_index[1]].add(tangent);
            uniqueTangentList[triangleIndex.vertex_index[2]] = uniqueTangentList[triangleIndex.vertex_index[2]].add(tangent);
        }
    }
}

void VertexManager::freeObj()
{
    uniqueVertexList.clear();
    uniqueNormalList.clear();
    uniqueFaceNormalList.clear();
    uniqueTangentList.clear();
    uniqueUVList.clear();
    triangleIndexList.clear();
}

void nbMesh::init()
{
    scale.x = scale.y = scale.z = distance = 1.0f;
    visible = 1;
    
    memset(name, 0, sizeof(name));
    memset(group, 0, sizeof(group));
    
    radius = 0;
    stride = 0;
    size = 0;
    
    memset(offset, 0, sizeof(offset));
    
    vao = 0;
    useSmoothNormals = false;
    useuvs = false;
    material = NULL;
    mode = GL_TRIANGLES;
    
    vboVertex = 0;
    vboVertexIndex = 0;
}

void nbMesh::freeObj()
{
    if (vao) {
        glLog("glDeleteVertexArraysOES : vao");
        glDeleteVertexArraysOES(1, &vao);
    }
    
    if (vboVertex) {
        glLog("glDeleteBuffers : vbo");
        glDeleteBuffers(1, &vboVertex);
    }
    
    if (vboVertexIndex) {
        glLog("glDeleteBuffers : vbo");
        glDeleteBuffers(1, &vboVertexIndex);
    }
}

void nbMesh::addVertexIndex(int vertexIndex, int uvIndex)
{
    int index = getUniqueVertexUVIndex(vertexIndex, uvIndex);
    vertexIndexList.push_back(index);
}

int nbMesh::getUniqueVertexUVIndex(int vertexIndex, int uvIndex)
{
    for (int i = 0; i < uniqueVertexUVIndexList.size(); i++) {
        UniqueVertexUVIndex uniqueIndex = uniqueVertexUVIndexList[i];
        if (vertexIndex == uniqueIndex.vertexIndex) {
            if (uvIndex < 0) {
                return i;
            }
            else {
                if (uvIndex == uniqueIndex.uvIndex) {
                    return i;
                }
            }
        }
    }
    
    UniqueVertexUVIndex uniqueIndex = {vertexIndex, uvIndex};
    uniqueVertexUVIndexList.push_back(uniqueIndex);
    
    return (int)uniqueVertexUVIndexList.size() - 1;
}


void nbMesh::build(VertexManager *vertexMgr)
{
    updateBound(vertexMgr);
    buildVboVertex(vertexMgr);
    buildVboVertexIndex();
    buildVao();
    
//    freeVertexData();
}

void nbMesh::freeVertexData(void)
{
    uniqueVertexUVIndexList.clear();
    vertexIndexList.clear();
}

void nbMesh::updateBound(VertexManager *vertexMgr)
{
    nbMesh *mesh = this;
    // Get the mesh min and max.
    mesh->min.x =
    mesh->min.y =
    mesh->min.z = 99999.999f;
    
    mesh->max.x =
    mesh->max.y =
    mesh->max.z = -99999.999f;
    
#if 1 // 아래 코드는 전체 오브젝트가 아니라 이 Mesh 에 대해서만 중심좌표를 계산하고 있다.
    // 만약 Obj 에 여러 Mesh 가 하나의 Object 를 구성한다면 회전 시 각각의 메시의 중심좌표가 틀리기 때문에
    // 좌표가 틀어지게 된다. 그럴 경우가 있다면 전체 Object 의 중심좌표를 구해서 넣어야 할 것이다.
    // 그러나 보통은 하나의 오브제는 하나의 메시로 구성될 것이고 그 메시를 회전시키는 것이 맞으므로 아래 코드가 맞다.
    
    for (int i = 0; i < mesh->uniqueVertexUVIndexList.size(); i++) {
        UniqueVertexUVIndex index = mesh->uniqueVertexUVIndexList[i];
        vec3 vertex = vertexMgr->uniqueVertexList[index.vertexIndex];
        
        
        if( vertex.x < mesh->min.x ) {
            mesh->min.x = vertex.x;
        }
        if( vertex.y < mesh->min.y ) {
            mesh->min.y = vertex.y;
        }
        if( vertex.z < mesh->min.z ) {
            mesh->min.z = vertex.z;
        }
        
        if( vertex.x > mesh->max.x ) {
            mesh->max.x = vertex.x;
        }
        if( vertex.y > mesh->max.y ) {
            mesh->max.y = vertex.y;
        }
        if( vertex.z > mesh->max.z ) {
            mesh->max.z = vertex.z;
        }
        
    }
#else
    for (int i = 0; i < vertexMgr->uniqueVertexList.size(); i++) {
        vec3 vertex = vertexMgr->uniqueVertexList[i];
        
        
        if( vertex.x < mesh->min.x ) {
            mesh->min.x = vertex.x;
        }
        if( vertex.y < mesh->min.y ) {
            mesh->min.y = vertex.y;
        }
        if( vertex.z < mesh->min.z ) {
            mesh->min.z = vertex.z;
        }
        
        if( vertex.x > mesh->max.x ) {
            mesh->max.x = vertex.x;
        }
        if( vertex.y > mesh->max.y ) {
            mesh->max.y = vertex.y;
        }
        if( vertex.z > mesh->max.z ) {
            mesh->max.z = vertex.z;
        }
        
    }
#endif
    
    mesh->location = mesh->min.mid(mesh->max);
    
    mesh->dimension = mesh->max.diff(mesh->min);
    
    
    // Bounding sphere radius
    mesh->radius = mesh->dimension.x >= mesh->dimension.y ?
    mesh->dimension.x:
    mesh->dimension.y;
    
    mesh->radius = mesh->radius >= mesh->dimension.z ?
    mesh->radius * 0.5f:
    mesh->dimension.z * 0.5f;
}


/*!
 Build the vertex data array buffer VBO for a specific OBJMESH index.
 
 \param[in] obj A valid OBJ structure pointer.
 \param[in] mesh_index The mesh index in the OBJ OBJMESH database.
 */
void nbMesh::buildVboVertex(VertexManager *vertexMgr)
{
    unsigned int index, offset;
    
    //    OBJMESH *objmesh = &meshList[mesh_index];
    nbMesh *mesh = this;
    
    mesh->stride  = sizeof(vec3); // Vertex
    mesh->stride += sizeof(vec3); // Normals
    mesh->stride += sizeof(vec3); // Face Normals
    
    if (mesh->useuvs) {
        mesh->stride += sizeof(vec2); // Uv
        mesh->stride += sizeof(vec3); // Tangent
    }
    
    mesh->size = (int)mesh->uniqueVertexUVIndexList.size() * mesh->stride;
    
    unsigned char *vertexArray = (unsigned char *)malloc(mesh->size);
    unsigned char *vertexStart = vertexArray;
    
    for (int i = 0; i < mesh->uniqueVertexUVIndexList.size(); i++) {
        index = mesh->uniqueVertexUVIndexList[i].vertexIndex;
        
        vec3 pivot = vertexMgr->uniqueVertexList[index];
        
        pivot = pivot.diff(mesh->location);
        
        memcpy(vertexArray, &pivot, sizeof(vec3));
        vertexArray += sizeof(vec3);
        
        memcpy(vertexArray, &vertexMgr->uniqueNormalList[index], sizeof(vec3));
        vertexArray += sizeof(vec3);
        
        memcpy(vertexArray, &vertexMgr->uniqueFaceNormalList[index], sizeof(vec3));
        vertexArray += sizeof(vec3);
        
        if (mesh->useuvs) {
            memcpy(vertexArray,
                   &vertexMgr->uniqueUVList[mesh->uniqueVertexUVIndexList[i].uvIndex],
                   sizeof(vec2));
            
            vertexArray += sizeof(vec2);
            
            memcpy(vertexArray,
                   &vertexMgr->uniqueTangentList[index],
                   sizeof(vec3));
            
            vertexArray += sizeof(vec3);
        }
        
    }
    
    glLog("glGenBuffers : vbo");
    glGenBuffers( 1, &mesh->vboVertex );
    
    glLog("glBindBuffer : GL_ARRAY_BUFFER");
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vboVertex);
    
    glLog("glBufferData : GL_ARRAY_BUFFER");
    glBufferData(GL_ARRAY_BUFFER,
                 mesh->size,
                 vertexStart,
                 GL_STATIC_DRAW);
    
    free(vertexStart);
    
    mesh->offset[0] = 0;
    offset = sizeof(vec3);
    
    mesh->offset[1] = offset;
    offset += sizeof(vec3);
    
    mesh->offset[2] = offset;
    offset += sizeof(vec3);
    
    if (mesh->useuvs) {
        mesh->offset[ 3 ] = offset;
        offset += sizeof( vec2 );
        
        mesh->offset[ 4 ] = offset;
    }
}


void nbMesh::buildVboVertexIndex()
{
    nbMesh *mesh = this;
    glLog("glGenBuffers : vbo");
    glGenBuffers(1, &mesh->vboVertexIndex);
    
    glLog("glBindBuffer : GL_ELEMENT_ARRAY_BUFFER");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vboVertexIndex);
    
    glLog("glBufferData : GL_ELEMENT_ARRAY_BUFFER");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 mesh->vertexIndexList.size() * sizeof(unsigned short),
                 &mesh->vertexIndexList[0],
                 GL_STATIC_DRAW );
}


void nbMesh::buildVao()
{
    glLog("glGenVertexArraysOES : vao");
    glGenVertexArraysOES( 1, &vao );
    
    glLog("glBindVertexArrayOES : vao");
    glBindVertexArrayOES(vao);
    
    setAttributePointer( );
    
    glLog("glBindBuffer : GL_ELEMENT_ARRAY_BUFFER");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboVertexIndex);
    
    glLog("glBindVertexArrayOES : 0");
    glBindVertexArrayOES(0);
}

void nbMesh::setAttributePointer()
{
    glLog("glBindBuffer : GL_ARRAY_BUFFER");
    glBindBuffer( GL_ARRAY_BUFFER, vboVertex );
    
    glLog("glEnableVertexAttribArray : 0");
    glEnableVertexAttribArray( 0 );
    
    glLog("glVertexAttribPointer : 0");
    glVertexAttribPointer( 0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          ( void * )NULL );
    
    
    glLog("glEnableVertexAttribArray : 1");
    glEnableVertexAttribArray( 1 );
    
    glLog("glVertexAttribPointer : 1");
    glVertexAttribPointer( 1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          BUFFER_OFFSET( offset[ 1 ] ) );
    
    
    glLog("glEnableVertexAttribArray : 4");
    glEnableVertexAttribArray( 4 );
    
    glLog("glVertexAttribPointer : 4");
    glVertexAttribPointer( 4,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          BUFFER_OFFSET( offset[ 2 ] ) );
    
    
    if( offset[ 3 ] != -1 )
    {
        glLog("glEnableVertexAttribArray : 2");
        glEnableVertexAttribArray( 2 );
        
        glLog("glVertexAttribPointer : 2");
        glVertexAttribPointer( 2,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              stride,
                              BUFFER_OFFSET( offset[ 3 ] ) );
        
        glLog("glEnableVertexAttribArray : 3");
        glEnableVertexAttribArray( 3 );
        
        glLog("glVertexAttribPointer : 3");
        glVertexAttribPointer( 3,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              stride,
                              BUFFER_OFFSET( offset[ 4 ] ) );
    }
}

void nbMesh::draw()
{
    if (visible && distance) {
        if (vao) {
            glLogVerbose("glBindVertexArrayOES : vao");
            glBindVertexArrayOES(vao);
        }
        else {
            setAttributePointer();
        }
        
        if (material) {
            material->draw();
        }
        
        glLogVerbose("glBindBuffer : GL_ELEMENT_ARRAY_BUFFER");
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboVertexIndex);
        
        glLogVerbose("glDrawElements");
        glDrawElements(mode,
                       (int)vertexIndexList.size(),
                       GL_UNSIGNED_SHORT,
                       ( void * )NULL );
    }
}

