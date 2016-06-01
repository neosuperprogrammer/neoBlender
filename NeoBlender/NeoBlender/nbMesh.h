//
//  nbMesh.h
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 2. 10..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#ifndef __NeoBlender__nbMesh__
#define __NeoBlender__nbMesh__

//#include "Object.h"
#include <vector>
#include "nbMaterial.h"

using namespace fgx3;
using namespace std;


class nbObject;


typedef struct
{
    int vertex_index[ 3 ];
    
    int uv_index[ 3 ];
    
} OBJTRIANGLEINDEX;

//! Structure definition for a unique vertex data indices.
typedef struct
{
    //! The vertex index of the OBJVERTEXDATA.
    int vertexIndex;
    
    //! The uv index of the OBJVERTEXDATA.
    int uvIndex;
    
} UniqueVertexUVIndex;

class VertexManager {
public:
    vector<vec3> uniqueVertexList;
    vector<vec3> uniqueNormalList;
    vector<vec3> uniqueFaceNormalList;
    vector<vec3> uniqueTangentList;
    vector<vec2> uniqueUVList;
    
    vector<OBJTRIANGLEINDEX> triangleIndexList;
    
public:
    VertexManager() { }
    virtual ~VertexManager() { freeObj(); }
    
    void addUniqueVertex(vec3 vertex);
    void addUniqueUV(vec2 uv);
    void buildNormalAndTangent();

    void freeObj();
};

class nbMesh {
    
public:
    //! The name of the object.
    char			name[ MAX_CHAR ];  // o
    
    //! Flag to determine if the object is visible for drawing.
    unsigned char	visible;
    
    //! The object group (if any).
    char			group[ MAX_CHAR ]; // g
    
    vector<UniqueVertexUVIndex> uniqueVertexUVIndexList;
    
    //! The XYZ location in worldspace of the OBJMESH.
    vec3			location;
    
    //! The XYZ euler angle rotation of the OBJMESH.
    vec3			rotation;
    
    //! The XYZ scale vector for the current OBJMESH.
    vec3			scale;
    
    //! The bottom left XYZ coordinate in worldspace of the OBJMESH bounding box.
    vec3			min;
    
    //! The upper right XYZ coordinate in worldspace of the OBJMESH bounding box.
    vec3			max;
    
    //! The XYZ dimension of the bounding box.
    vec3			dimension;
    
    //! The bounding sphere radius.
    float			radius;
    
    //! The distance of the OBJMESH with the viewer.
    float			distance;
    
    //! The vertex buffer VBO id maintained by GLES.
    unsigned int	vboVertex;
    
    //! The stride size in bytes to determine where the next chunk of data in the vertex buffer is located.
    unsigned int	stride;
    
    //! The total size of the vertex data array.
    unsigned int	size;
    
    //! The VBO offsets.
    unsigned int	offset[ 5 ];
    
    //! The VAO id maintained by GLES.
    unsigned int	vao;
    
    //! Pointer a btRigidBody inside a physical world.
    //	btRigidBody		*btrigidbody;
    
    //! Determine if the OBJMESH is using vertex or face normals.
    bool useSmoothNormals;
    
    
    // from OBJTRIANGLELIST
    
    
    //! Flag to determine if the OBJTRIANGLELIST is using UVs.
    bool	 useuvs;
    
    vector<short> vertexIndexList;
    
    //! Pointer to an OBJMATERIAL to use when drawing the OBJTRIANGLELIST.
//    OBJMATERIAL		 *objmaterial;

    nbMaterial		 *material;

    //! The drawing mode to use. (Default: GL_TRIANGLES)
    int				 mode;
    
    //! The internal VBO id maintained by GLES to draw the OBJTRIANGLELIST.
    unsigned int	 vboVertexIndex;
    
public:
    nbMesh() { init(); }
    virtual ~nbMesh() { freeObj(); }
    
    void init();
    void freeObj();
    
    void addVertexIndex(int vertexIndex, int uvIndex);
    int getUniqueVertexUVIndex(int vertexIndex, int uvIndex);
    
    void build(VertexManager *vertexMgr);
    void updateBound(VertexManager *vertexMgr);
    void buildVboVertex(VertexManager *vertexMgr);
    void buildVboVertexIndex();
    void buildVao();
    void setAttributePointer();
    void draw();

    
    void freeVertexData(void);
};


#endif /* defined(__NeoBlender__nbMesh__) */
