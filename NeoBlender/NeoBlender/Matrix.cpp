//
//  flMatrix.cpp
//  NeoBlender
//
//  Created by Nam, SangWook on 2015. 1. 30..
//  Copyright (c) 2015년 flowgrammer. All rights reserved.
//

#include "Matrix.h"
#include <math.h>
#include "types.h"

namespace fgx3 {

mat3::mat3()
{
    identity();
}

/*!
	Set a 3x3 matrix to the identity matrix.
	
	\param[in,out] m A valid 3x3 matrix pointer.
 */
//void mat3_identity( mat3 *m )
//{
//    memset( &m[ 0 ], 0, sizeof( mat3 ) );
//    
//    m->m[ 0 ].x =
//    m->m[ 1 ].y =
//    m->m[ 2 ].z = 1.0f;
//    
//}

void mat3::identity()
{
    m[0].x = 1; m[0].y = 0; m[0].z = 0;
    m[1].x = 0; m[1].y = 1; m[1].z = 0;
    m[2].x = 0; m[2].y = 0; m[2].z = 1;
}


/*!
	Copy the rotation part of a 4x4 matrix to a 3x3 matrix.
	
	\param[in,out] dst A valid mat3 pointer where the rotation part of the 4x4 matrix received in parameter will be stored.
	\param[in] m A valid 4x4 matrix pointer.
 */

//void mat3_copy_mat4( mat3 *dst, mat4 *m )
//{
//    memcpy( &dst->m[ 0 ], &m->m[ 0 ], sizeof( vec3 ) );
//    memcpy( &dst->m[ 1 ], &m->m[ 1 ], sizeof( vec3 ) );
//    memcpy( &dst->m[ 2 ], &m->m[ 2 ], sizeof( vec3 ) );
//}
//
void mat3::copy(const mat4&m4)
{
    m[0].x = m4.m[0].x;
    m[0].y = m4.m[0].y;
    m[0].z = m4.m[0].z;
    
    m[1].x = m4.m[1].x;
    m[1].y = m4.m[1].y;
    m[1].z = m4.m[1].z;

    m[2].x = m4.m[2].x;
    m[2].y = m4.m[2].y;
    m[2].z = m4.m[2].z;
}




mat4::mat4()
{
    identity();
}

/*!
	Set a 4x4 matrix to the identity matrix.
	
	\param[in,out] m A valid 3x3 matrix pointer.
 */
//void mat4_identity( mat4 *m )
//{
//    memset( &m[ 0 ], 0, sizeof( mat4 ) );
//    
//    m->m[ 0 ].x =
//    m->m[ 1 ].y =
//    m->m[ 2 ].z =
//    m->m[ 3 ].w = 1.0f;
//}

void mat4::identity()
{
    m[0].x = 1; m[0].y = 0; m[0].z = 0; m[0].w = 0;
    m[1].x = 0; m[1].y = 1; m[1].z = 0; m[1].w = 0;
    m[2].x = 0; m[2].y = 0; m[2].z = 1; m[2].w = 0;
    m[3].x = 0; m[3].y = 0; m[3].z = 0; m[3].w = 1;
}

/*!
	Copy the content of a 4x4 matrix to another 4x4 matrix.
	
	\param[in,out] dst A valid 4x4 matrix pointer that will be affected by the content of the m matrix received in parameter.
	\param[in] m A valid 4x4 matrix pointer that will be used as the source.
 */
//void mat4_copy_mat4( mat4 *dst, mat4 *m )
//{ memcpy( dst, m, sizeof( mat4 ) ); }

void mat4::copy(const mat4&m4)
{
    m[0].x = m4.m[0].x; m[0].y = m4.m[0].y; m[0].z = m4.m[0].z; m[0].w = m4.m[0].w;
    m[1].x = m4.m[1].x; m[1].y = m4.m[1].y; m[1].z = m4.m[1].z; m[1].w = m4.m[1].w;
    m[2].x = m4.m[2].x; m[2].y = m4.m[2].y; m[2].z = m4.m[2].z; m[2].w = m4.m[2].w;
    m[3].x = m4.m[3].x; m[3].y = m4.m[3].y; m[3].z = m4.m[3].z; m[3].w = m4.m[3].w;
}
/*!
	Multiply the current matrix by a translation vector.
	
	\param[in,out] dst A valid 4x4 matrix pointer that will be use as the destination matrix to store the result of the operation.
	\param[in] m A valid 4x4 matrix pointer that will be use as the source.
	\param[in] v A valid vec3 pointer that will be used as translation vector.
 */
//void mat4_translate( mat4 *dst, mat4 *m, vec3 *v )
//{
//    dst->m[ 3 ].x = m->m[ 0 ].x * v->x + m->m[ 1 ].x * v->y + m->m[ 2 ].x * v->z + m->m[ 3 ].x;
//    dst->m[ 3 ].y = m->m[ 0 ].y * v->x + m->m[ 1 ].y * v->y + m->m[ 2 ].y * v->z + m->m[ 3 ].y;
//    dst->m[ 3 ].z = m->m[ 0 ].z * v->x + m->m[ 1 ].z * v->y + m->m[ 2 ].z * v->z + m->m[ 3 ].z;
//    dst->m[ 3 ].w = m->m[ 0 ].w * v->x + m->m[ 1 ].w * v->y + m->m[ 2 ].w * v->z + m->m[ 3 ].w;
//}

void mat4::translate(mat4& dst, const vec3& v) const
{
    dst.m[ 3 ].x = m[ 0 ].x * v.x + m[ 1 ].x * v.y + m[ 2 ].x * v.z + m[ 3 ].x;
    dst.m[ 3 ].y = m[ 0 ].y * v.x + m[ 1 ].y * v.y + m[ 2 ].y * v.z + m[ 3 ].y;
    dst.m[ 3 ].z = m[ 0 ].z * v.x + m[ 1 ].z * v.y + m[ 2 ].z * v.z + m[ 3 ].z;
    dst.m[ 3 ].w = m[ 0 ].w * v.x + m[ 1 ].w * v.y + m[ 2 ].w * v.z + m[ 3 ].w;
}


/*!
	Rotate a matrix on a specific axis using an arbitray angle stored as the W component of the v variable.
	
	\param[in] m A valid 4x4 matrix pointer that will be used as the source matrix to rotate as well as the destination that will hold the result of the operation.
	\param[in] v A valid vec4 pointer that have the angle in degree that you desire to use for the rotation stored in the W component. Please
	take note that the rotation vector part of v can only contain one axis of rotation.
 */
//void mat4_rotate_fast( mat4 *m, vec4 *v )
//{
//    float s = sinf( v->w * DEG_TO_RAD ),
//		  c = cosf( v->w * DEG_TO_RAD );
//    
//    mat4 mat;
//    
//    mat4_identity( &mat );
//    
//    if( !v->x )
//    {
//        if( !v->y )
//        {
//            if( v->z )
//            {
//                mat.m[ 0 ].x = c;
//                mat.m[ 1 ].y = c;
//                
//                if( v->z < 0.0f )
//                {
//                    mat.m[ 1 ].x =  s;
//                    mat.m[ 0 ].y = -s;
//                }
//                else
//                {
//                    mat.m[ 1 ].x = -s;
//                    mat.m[ 0 ].y =  s;
//                }
//            }
//        }
//        else if( !v->z )
//        {
//            mat.m[ 0 ].x = c;
//            mat.m[ 2 ].z = c;
//            
//            if( v->y < 0.0f )
//            {
//                mat.m[ 2 ].x = -s;
//                mat.m[ 0 ].z =  s;
//            }
//            else
//            {
//                mat.m[ 2 ].x =  s;
//                mat.m[ 0 ].z = -s;
//            }
//        }
//    }
//    else if( !v->y )
//    {
//        if( !v->z )
//        {
//            mat.m[ 1 ].y = c;
//            mat.m[ 2 ].z = c;
//            
//            if( v->x < 0.0f )
//            {
//                mat.m[ 2 ].y =  s;
//                mat.m[ 1 ].z = -s;
//            }
//            else
//            {
//                mat.m[ 2 ].y = -s;
//                mat.m[ 1 ].z =  s;
//            }
//        }
//    }
//    
//    mat4_multiply_mat4( m, m, &mat );
//}

void mat4::rotateFast(const vec4& vr)
{
    const vec4 *v = &vr;
    float s = sinf( v->w * DEG_TO_RAD ),
		  c = cosf( v->w * DEG_TO_RAD );
    
    mat4 mat;
    mat.identity();
    
    if( !v->x )
    {
        if( !v->y )
        {
            if( v->z )
            {
                mat.m[ 0 ].x = c;
                mat.m[ 1 ].y = c;
                
                if( v->z < 0.0f )
                {
                    mat.m[ 1 ].x =  s;
                    mat.m[ 0 ].y = -s;
                }
                else
                {
                    mat.m[ 1 ].x = -s;
                    mat.m[ 0 ].y =  s;
                }
            }
        }
        else if( !v->z )
        {
            mat.m[ 0 ].x = c;
            mat.m[ 2 ].z = c;
            
            if( v->y < 0.0f )
            {
                mat.m[ 2 ].x = -s;
                mat.m[ 0 ].z =  s;
            }
            else
            {
                mat.m[ 2 ].x =  s;
                mat.m[ 0 ].z = -s;
            }
        }
    }
    else if( !v->y )
    {
        if( !v->z )
        {
            mat.m[ 1 ].y = c;
            mat.m[ 2 ].z = c;
            
            if( v->x < 0.0f )
            {
                mat.m[ 2 ].y =  s;
                mat.m[ 1 ].z = -s;
            }
            else
            {
                mat.m[ 2 ].y = -s;
                mat.m[ 1 ].z =  s;
            }
        }
    }
    
    copy(multiply(mat));
}


/*!
	Rotate a matrix on the XYZ axis of your choice, based on an arbitray angle stored as the W component of the v variable.
	
	\param[in,out] dst A valid 4x4 matrix pointer that will be use as the destination matrix to store the result of the operation.
	\param[in] m A valid 4x4 matrix pointer that will be used as the source matrix to rotate.
	\param[in] v A valid vec4 pointer that have the angle in degree that you desire to use for the rotation stored in the W component.
 */
//void mat4_rotate( mat4 *dst, mat4 *m, vec4 *v )
//{
//    float s = sinf( v->w * DEG_TO_RAD ),
//		  c = cosf( v->w * DEG_TO_RAD ),
//		  xx,
//		  yy,
//		  zz,
//		  xy,
//		  yz,
//		  zx,
//		  xs,
//		  ys,
//		  zs,
//		  c1;
//    
//    mat4 mat;
//    
//    vec3 t = { v->x, v->y, v->z };
//    
//    if( !v->w || !vec3_normalize( &t, &t ) ) return;
//    
//    xx = t.x * t.x;
//    yy = t.y * t.y;
//    zz = t.z * t.z;
//    xy = t.x * t.y;
//    yz = t.y * t.z;
//    zx = t.z * t.x;
//    xs = t.x * s;
//    ys = t.y * s;
//    zs = t.z * s;
//    c1 = 1.0f - c;
//    
//    mat4_identity( &mat );
//    
//    mat.m[ 0 ].x = ( c1 * xx ) + c;
//    mat.m[ 1 ].x = ( c1 * xy ) - zs;
//    mat.m[ 2 ].x = ( c1 * zx ) + ys;
//    
//    mat.m[ 0 ].y = ( c1 * xy ) + zs;
//    mat.m[ 1 ].y = ( c1 * yy ) + c;
//    mat.m[ 2 ].y = ( c1 * yz ) - xs;
//    
//    mat.m[ 0 ].z = ( c1 * zx ) - ys;
//    mat.m[ 1 ].z = ( c1 * yz ) + xs;
//    mat.m[ 2 ].z = ( c1 * zz ) + c;
//    
//    mat4_multiply_mat4( m, m, &mat );
//}


void mat4::rotate(const vec4& vr)
{
    const vec4 *v = &vr;
    float s = sinf( v->w * DEG_TO_RAD ),
		  c = cosf( v->w * DEG_TO_RAD ),
		  xx,
		  yy,
		  zz,
		  xy,
		  yz,
		  zx,
		  xs,
		  ys,
		  zs,
		  c1;
    
    mat4 mat;
    
    vec3 t = { v->x, v->y, v->z };
    
    if( !v->w || !t.normalize() ) {
        return;
    }
    
    xx = t.x * t.x;
    yy = t.y * t.y;
    zz = t.z * t.z;
    xy = t.x * t.y;
    yz = t.y * t.z;
    zx = t.z * t.x;
    xs = t.x * s;
    ys = t.y * s;
    zs = t.z * s;
    c1 = 1.0f - c;
    
    mat.identity();
    
    mat.m[ 0 ].x = ( c1 * xx ) + c;
    mat.m[ 1 ].x = ( c1 * xy ) - zs;
    mat.m[ 2 ].x = ( c1 * zx ) + ys;
    
    mat.m[ 0 ].y = ( c1 * xy ) + zs;
    mat.m[ 1 ].y = ( c1 * yy ) + c;
    mat.m[ 2 ].y = ( c1 * yz ) - xs;
    
    mat.m[ 0 ].z = ( c1 * zx ) - ys;
    mat.m[ 1 ].z = ( c1 * yz ) + xs;
    mat.m[ 2 ].z = ( c1 * zz ) + c;
    
    
    copy(multiply(mat));
}


/*!
	Multiply the current matrix by a scale vector.
	
	\param[in,out] dst A valid 4x4 matrix pointer that will be use as the destination matrix to store the result of the operation.
	\param[in] m A valid 4x4 matrix pointer that will be use as the source.
	\param[in] v A valid vec3 pointer that will be used as the scale vector.
 */
//void mat4_scale( mat4 *dst, mat4 *m, vec3 *v )
//{
//    dst->m[ 0 ].x = m->m[ 0 ].x * v->x;
//    dst->m[ 0 ].y = m->m[ 0 ].y * v->x;
//    dst->m[ 0 ].z = m->m[ 0 ].z * v->x;
//    dst->m[ 0 ].w = m->m[ 0 ].w * v->x;
//    
//    dst->m[ 1 ].x = m->m[ 1 ].x * v->y;
//    dst->m[ 1 ].y = m->m[ 1 ].y * v->y;
//    dst->m[ 1 ].z = m->m[ 1 ].z * v->y;
//    dst->m[ 1 ].w = m->m[ 1 ].w * v->y;
//    
//    dst->m[ 2 ].x = m->m[ 2 ].x * v->z;
//    dst->m[ 2 ].y = m->m[ 2 ].y * v->z;
//    dst->m[ 2 ].z = m->m[ 2 ].z * v->z;
//    dst->m[ 2 ].w = m->m[ 2 ].w * v->z;
//}

mat4 mat4::scale(const vec3& vr) const
{
    mat4 tmp;
    mat4 *dst = &tmp;
    const mat4 *m = this;
    const vec3* v = &vr;
    
    dst->m[ 0 ].x = m->m[ 0 ].x * v->x;
    dst->m[ 0 ].y = m->m[ 0 ].y * v->x;
    dst->m[ 0 ].z = m->m[ 0 ].z * v->x;
    dst->m[ 0 ].w = m->m[ 0 ].w * v->x;
    
    dst->m[ 1 ].x = m->m[ 1 ].x * v->y;
    dst->m[ 1 ].y = m->m[ 1 ].y * v->y;
    dst->m[ 1 ].z = m->m[ 1 ].z * v->y;
    dst->m[ 1 ].w = m->m[ 1 ].w * v->y;
    
    dst->m[ 2 ].x = m->m[ 2 ].x * v->z;
    dst->m[ 2 ].y = m->m[ 2 ].y * v->z;
    dst->m[ 2 ].z = m->m[ 2 ].z * v->z;
    dst->m[ 2 ].w = m->m[ 2 ].w * v->z;
 
    return tmp;
}


/*!
	Invert a 4x4 matrix fast.
	
	\param[in,out] m A valid 4x4 matrix that will be used for the inverse operation.
	
	\return Return 1 if the inverse is successfull, instead return 0.
	
	\sa mat4_invert_full
 */
//unsigned char mat4_invert( mat4 *m )
//{
//    mat4 mat;
//    
//    float d = ( m->m[ 0 ].x * m->m[ 0 ].x +
//               m->m[ 1 ].x * m->m[ 1 ].x +
//               m->m[ 2 ].x * m->m[ 2 ].x );
//    
//    if( !d ) return 0;
//    
//    d = 1.0f / d;
//    
//    mat.m[ 0 ].x = d * m->m[ 0 ].x;
//    mat.m[ 0 ].y = d * m->m[ 1 ].x;
//    mat.m[ 0 ].z = d * m->m[ 2 ].x;
//    
//    mat.m[ 1 ].x = d * m->m[ 0 ].y;
//    mat.m[ 1 ].y = d * m->m[ 1 ].y;
//    mat.m[ 1 ].z = d * m->m[ 2 ].y;
//    
//    mat.m[ 2 ].x = d * m->m[ 0 ].z;
//    mat.m[ 2 ].y = d * m->m[ 1 ].z;
//    mat.m[ 2 ].z = d * m->m[ 2 ].z;
//    
//    mat.m[ 3 ].x = -( mat.m[ 0 ].x * m->m[ 3 ].x + mat.m[ 1 ].x * m->m[ 3 ].y + mat.m[ 2 ].x * m->m[ 3 ].z );
//    mat.m[ 3 ].y = -( mat.m[ 0 ].y * m->m[ 3 ].x + mat.m[ 1 ].y * m->m[ 3 ].y + mat.m[ 2 ].y * m->m[ 3 ].z );
//    mat.m[ 3 ].z = -( mat.m[ 0 ].z * m->m[ 3 ].x + mat.m[ 1 ].z * m->m[ 3 ].y + mat.m[ 2 ].z * m->m[ 3 ].z );
//    
//    mat.m[ 0 ].w =
//    mat.m[ 1 ].w =
//    mat.m[ 2 ].w = 0.0f;
//    mat.m[ 3 ].w = 1.0f;
//    
//    mat4_copy_mat4( m, &mat );
//    
//    return 1;
//}


unsigned char mat4::invert()
{
    mat4 mat;
    mat4 *m = this;
    
    float d = ( m->m[ 0 ].x * m->m[ 0 ].x +
               m->m[ 1 ].x * m->m[ 1 ].x +
               m->m[ 2 ].x * m->m[ 2 ].x );
    
    if( !d ) return 0;
    
    d = 1.0f / d;
    
    mat.m[ 0 ].x = d * m->m[ 0 ].x;
    mat.m[ 0 ].y = d * m->m[ 1 ].x;
    mat.m[ 0 ].z = d * m->m[ 2 ].x;
    
    mat.m[ 1 ].x = d * m->m[ 0 ].y;
    mat.m[ 1 ].y = d * m->m[ 1 ].y;
    mat.m[ 1 ].z = d * m->m[ 2 ].y;
    
    mat.m[ 2 ].x = d * m->m[ 0 ].z;
    mat.m[ 2 ].y = d * m->m[ 1 ].z;
    mat.m[ 2 ].z = d * m->m[ 2 ].z;
    
    mat.m[ 3 ].x = -( mat.m[ 0 ].x * m->m[ 3 ].x + mat.m[ 1 ].x * m->m[ 3 ].y + mat.m[ 2 ].x * m->m[ 3 ].z );
    mat.m[ 3 ].y = -( mat.m[ 0 ].y * m->m[ 3 ].x + mat.m[ 1 ].y * m->m[ 3 ].y + mat.m[ 2 ].y * m->m[ 3 ].z );
    mat.m[ 3 ].z = -( mat.m[ 0 ].z * m->m[ 3 ].x + mat.m[ 1 ].z * m->m[ 3 ].y + mat.m[ 2 ].z * m->m[ 3 ].z );
    
    mat.m[ 0 ].w =
    mat.m[ 1 ].w =
    mat.m[ 2 ].w = 0.0f;
    mat.m[ 3 ].w = 1.0f;
    
    copy(mat);
    
    return 1;
}

/*!
	Invert a 4x4 matrix fast.
	
	\param[in,out] m A valid 4x4 matrix that will be used for the inverse operation.
	
	\return Return 1 if the inverse is successfull, instead return 0.
	
	\sa mat4_invert
 */
//unsigned char mat4_invert_full( mat4 *m )
//{
//    mat4 inv;
//    
//    float d;
//    
//    inv.m[ 0 ].x = m->m[ 1 ].y * m->m[ 2 ].z * m->m[ 3 ].w -
//    m->m[ 1 ].y * m->m[ 2 ].w * m->m[ 3 ].z -
//    m->m[ 2 ].y * m->m[ 1 ].z * m->m[ 3 ].w +
//    m->m[ 2 ].y * m->m[ 1 ].w * m->m[ 3 ].z +
//    m->m[ 3 ].y * m->m[ 1 ].z * m->m[ 2 ].w -
//    m->m[ 3 ].y * m->m[ 1 ].w * m->m[ 2 ].z;
//    
//    inv.m[ 1 ].x = -m->m[ 1 ].x * m->m[ 2 ].z * m->m[ 3 ].w +
//    m->m[ 1 ].x * m->m[ 2 ].w * m->m[ 3 ].z +
//    m->m[ 2 ].x * m->m[ 1 ].z * m->m[ 3 ].w -
//    m->m[ 2 ].x * m->m[ 1 ].w * m->m[ 3 ].z -
//    m->m[ 3 ].x * m->m[ 1 ].z * m->m[ 2 ].w +
//    m->m[ 3 ].x * m->m[ 1 ].w * m->m[ 2 ].z;
//    
//    inv.m[ 2 ].x = m->m[ 1 ].x * m->m[ 2 ].y * m->m[ 3 ].w -
//    m->m[ 1 ].x * m->m[ 2 ].w * m->m[ 3 ].y -
//    m->m[ 2 ].x * m->m[ 1 ].y * m->m[ 3 ].w +
//    m->m[ 2 ].x * m->m[ 1 ].w * m->m[ 3 ].y +
//    m->m[ 3 ].x * m->m[ 1 ].y * m->m[ 2 ].w -
//    m->m[ 3 ].x * m->m[ 1 ].w * m->m[ 2 ].y;
//    
//    inv.m[ 3 ].x = -m->m[ 1 ].x * m->m[ 2 ].y * m->m[ 3 ].z +
//    m->m[ 1 ].x * m->m[ 2 ].z * m->m[ 3 ].y +
//    m->m[ 2 ].x * m->m[ 1 ].y * m->m[ 3 ].z -
//    m->m[ 2 ].x * m->m[ 1 ].z * m->m[ 3 ].y -
//    m->m[ 3 ].x * m->m[ 1 ].y * m->m[ 2 ].z +
//    m->m[ 3 ].x * m->m[ 1 ].z * m->m[ 2 ].y;
//    
//    inv.m[ 0 ].y = -m->m[ 0 ].y * m->m[ 2 ].z * m->m[ 3 ].w +
//    m->m[ 0 ].y * m->m[ 2 ].w * m->m[ 3 ].z +
//    m->m[ 2 ].y * m->m[ 0 ].z * m->m[ 3 ].w -
//    m->m[ 2 ].y * m->m[ 0 ].w * m->m[ 3 ].z -
//    m->m[ 3 ].y * m->m[ 0 ].z * m->m[ 2 ].w +
//    m->m[ 3 ].y * m->m[ 0 ].w * m->m[ 2 ].z;
//    
//    inv.m[ 1 ].y = m->m[ 0 ].x * m->m[ 2 ].z * m->m[ 3 ].w -
//    m->m[ 0 ].x * m->m[ 2 ].w * m->m[ 3 ].z -
//    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 3 ].w +
//    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 3 ].z +
//    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 2 ].w -
//    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 2 ].z;
//    
//    inv.m[ 2 ].y = -m->m[ 0 ].x * m->m[ 2 ].y * m->m[ 3 ].w +
//    m->m[ 0 ].x * m->m[ 2 ].w * m->m[ 3 ].y +
//    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 3 ].w -
//    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 3 ].y -
//    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 2 ].w +
//    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 2 ].y;
//    
//    inv.m[ 3 ].y = m->m[ 0 ].x * m->m[ 2 ].y * m->m[ 3 ].z -
//    m->m[ 0 ].x * m->m[ 2 ].z * m->m[ 3 ].y -
//    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 3 ].z +
//    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 3 ].y +
//    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 2 ].z -
//    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 2 ].y;
//    
//    inv.m[ 0 ].z = m->m[ 0 ].y * m->m[ 1 ].z * m->m[ 3 ].w -
//    m->m[ 0 ].y * m->m[ 1 ].w * m->m[ 3 ].z -
//    m->m[ 1 ].y * m->m[ 0 ].z * m->m[ 3 ].w +
//    m->m[ 1 ].y * m->m[ 0 ].w * m->m[ 3 ].z +
//    m->m[ 3 ].y * m->m[ 0 ].z * m->m[ 1 ].w -
//    m->m[ 3 ].y * m->m[ 0 ].w * m->m[ 1 ].z;
//    
//    inv.m[ 1 ].z = -m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 3 ].w +
//    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 3 ].z +
//    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 3 ].w -
//    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 3 ].z -
//    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 1 ].w +
//    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 1 ].z;
//    
//    inv.m[ 2 ].z = m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 3 ].w -
//    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 3 ].y -
//    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 3 ].w +
//    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 3 ].y +
//    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 1 ].w -
//    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 1 ].y;
//    
//    inv.m[ 3 ].z = -m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 3 ].z +
//    m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 3 ].y +
//    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 3 ].z -
//    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 3 ].y -
//    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 1 ].z +
//    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 1 ].y;
//    
//    inv.m[ 0 ].w = -m->m[ 0 ].y * m->m[ 1 ].z * m->m[ 2 ].w +
//    m->m[ 0 ].y * m->m[ 1 ].w * m->m[ 2 ].z +
//    m->m[ 1 ].y * m->m[ 0 ].z * m->m[ 2 ].w -
//    m->m[ 1 ].y * m->m[ 0 ].w * m->m[ 2 ].z -
//    m->m[ 2 ].y * m->m[ 0 ].z * m->m[ 1 ].w +
//    m->m[ 2 ].y * m->m[ 0 ].w * m->m[ 1 ].z;
//    
//    inv.m[ 1 ].w = m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 2 ].w -
//    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 2 ].z -
//    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 2 ].w +
//    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 2 ].z +
//    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 1 ].w -
//    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 1 ].z;
//    
//    inv.m[ 2 ].w = -m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 2 ].w +
//    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 2 ].y +
//    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 2 ].w -
//    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 2 ].y -
//    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 1 ].w +
//    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 1 ].y;
//    
//    inv.m[ 3 ].w = m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 2 ].z -
//    m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 2 ].y -
//    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 2 ].z +
//    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 2 ].y +
//    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 1 ].z -
//    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 1 ].y;
//    
//    d = m->m[ 0 ].x * inv.m[ 0 ].x +
//    m->m[ 0 ].y * inv.m[ 1 ].x +
//    m->m[ 0 ].z * inv.m[ 2 ].x +
//    m->m[ 0 ].w * inv.m[ 3 ].x;
//    
//    if( !d ) return 0;
//    
//    d = 1.0f / d;
//    
//    inv.m[ 0 ].x *= d;
//    inv.m[ 0 ].y *= d;
//    inv.m[ 0 ].z *= d;
//    inv.m[ 0 ].w *= d;
//    
//    inv.m[ 1 ].x *= d;
//    inv.m[ 1 ].y *= d;
//    inv.m[ 1 ].z *= d;
//    inv.m[ 1 ].w *= d;
//    
//    inv.m[ 2 ].x *= d;
//    inv.m[ 2 ].y *= d;
//    inv.m[ 2 ].z *= d;
//    inv.m[ 2 ].w *= d;
//    
//    inv.m[ 3 ].x *= d;
//    inv.m[ 3 ].y *= d;
//    inv.m[ 3 ].z *= d;
//    inv.m[ 3 ].w *= d;
//    
//    mat4_copy_mat4( m, &inv );
//    
//    return 1;
//}


unsigned char mat4::invertFull()
{
    mat4 inv;
    mat4 *m = this;
    
    float d;
    
    inv.m[ 0 ].x = m->m[ 1 ].y * m->m[ 2 ].z * m->m[ 3 ].w -
    m->m[ 1 ].y * m->m[ 2 ].w * m->m[ 3 ].z -
    m->m[ 2 ].y * m->m[ 1 ].z * m->m[ 3 ].w +
    m->m[ 2 ].y * m->m[ 1 ].w * m->m[ 3 ].z +
    m->m[ 3 ].y * m->m[ 1 ].z * m->m[ 2 ].w -
    m->m[ 3 ].y * m->m[ 1 ].w * m->m[ 2 ].z;
    
    inv.m[ 1 ].x = -m->m[ 1 ].x * m->m[ 2 ].z * m->m[ 3 ].w +
    m->m[ 1 ].x * m->m[ 2 ].w * m->m[ 3 ].z +
    m->m[ 2 ].x * m->m[ 1 ].z * m->m[ 3 ].w -
    m->m[ 2 ].x * m->m[ 1 ].w * m->m[ 3 ].z -
    m->m[ 3 ].x * m->m[ 1 ].z * m->m[ 2 ].w +
    m->m[ 3 ].x * m->m[ 1 ].w * m->m[ 2 ].z;
    
    inv.m[ 2 ].x = m->m[ 1 ].x * m->m[ 2 ].y * m->m[ 3 ].w -
    m->m[ 1 ].x * m->m[ 2 ].w * m->m[ 3 ].y -
    m->m[ 2 ].x * m->m[ 1 ].y * m->m[ 3 ].w +
    m->m[ 2 ].x * m->m[ 1 ].w * m->m[ 3 ].y +
    m->m[ 3 ].x * m->m[ 1 ].y * m->m[ 2 ].w -
    m->m[ 3 ].x * m->m[ 1 ].w * m->m[ 2 ].y;
    
    inv.m[ 3 ].x = -m->m[ 1 ].x * m->m[ 2 ].y * m->m[ 3 ].z +
    m->m[ 1 ].x * m->m[ 2 ].z * m->m[ 3 ].y +
    m->m[ 2 ].x * m->m[ 1 ].y * m->m[ 3 ].z -
    m->m[ 2 ].x * m->m[ 1 ].z * m->m[ 3 ].y -
    m->m[ 3 ].x * m->m[ 1 ].y * m->m[ 2 ].z +
    m->m[ 3 ].x * m->m[ 1 ].z * m->m[ 2 ].y;
    
    inv.m[ 0 ].y = -m->m[ 0 ].y * m->m[ 2 ].z * m->m[ 3 ].w +
    m->m[ 0 ].y * m->m[ 2 ].w * m->m[ 3 ].z +
    m->m[ 2 ].y * m->m[ 0 ].z * m->m[ 3 ].w -
    m->m[ 2 ].y * m->m[ 0 ].w * m->m[ 3 ].z -
    m->m[ 3 ].y * m->m[ 0 ].z * m->m[ 2 ].w +
    m->m[ 3 ].y * m->m[ 0 ].w * m->m[ 2 ].z;
    
    inv.m[ 1 ].y = m->m[ 0 ].x * m->m[ 2 ].z * m->m[ 3 ].w -
    m->m[ 0 ].x * m->m[ 2 ].w * m->m[ 3 ].z -
    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 3 ].w +
    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 3 ].z +
    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 2 ].w -
    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 2 ].z;
    
    inv.m[ 2 ].y = -m->m[ 0 ].x * m->m[ 2 ].y * m->m[ 3 ].w +
    m->m[ 0 ].x * m->m[ 2 ].w * m->m[ 3 ].y +
    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 3 ].w -
    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 3 ].y -
    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 2 ].w +
    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 2 ].y;
    
    inv.m[ 3 ].y = m->m[ 0 ].x * m->m[ 2 ].y * m->m[ 3 ].z -
    m->m[ 0 ].x * m->m[ 2 ].z * m->m[ 3 ].y -
    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 3 ].z +
    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 3 ].y +
    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 2 ].z -
    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 2 ].y;
    
    inv.m[ 0 ].z = m->m[ 0 ].y * m->m[ 1 ].z * m->m[ 3 ].w -
    m->m[ 0 ].y * m->m[ 1 ].w * m->m[ 3 ].z -
    m->m[ 1 ].y * m->m[ 0 ].z * m->m[ 3 ].w +
    m->m[ 1 ].y * m->m[ 0 ].w * m->m[ 3 ].z +
    m->m[ 3 ].y * m->m[ 0 ].z * m->m[ 1 ].w -
    m->m[ 3 ].y * m->m[ 0 ].w * m->m[ 1 ].z;
    
    inv.m[ 1 ].z = -m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 3 ].w +
    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 3 ].z +
    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 3 ].w -
    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 3 ].z -
    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 1 ].w +
    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 1 ].z;
    
    inv.m[ 2 ].z = m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 3 ].w -
    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 3 ].y -
    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 3 ].w +
    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 3 ].y +
    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 1 ].w -
    m->m[ 3 ].x * m->m[ 0 ].w * m->m[ 1 ].y;
    
    inv.m[ 3 ].z = -m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 3 ].z +
    m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 3 ].y +
    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 3 ].z -
    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 3 ].y -
    m->m[ 3 ].x * m->m[ 0 ].y * m->m[ 1 ].z +
    m->m[ 3 ].x * m->m[ 0 ].z * m->m[ 1 ].y;
    
    inv.m[ 0 ].w = -m->m[ 0 ].y * m->m[ 1 ].z * m->m[ 2 ].w +
    m->m[ 0 ].y * m->m[ 1 ].w * m->m[ 2 ].z +
    m->m[ 1 ].y * m->m[ 0 ].z * m->m[ 2 ].w -
    m->m[ 1 ].y * m->m[ 0 ].w * m->m[ 2 ].z -
    m->m[ 2 ].y * m->m[ 0 ].z * m->m[ 1 ].w +
    m->m[ 2 ].y * m->m[ 0 ].w * m->m[ 1 ].z;
    
    inv.m[ 1 ].w = m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 2 ].w -
    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 2 ].z -
    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 2 ].w +
    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 2 ].z +
    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 1 ].w -
    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 1 ].z;
    
    inv.m[ 2 ].w = -m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 2 ].w +
    m->m[ 0 ].x * m->m[ 1 ].w * m->m[ 2 ].y +
    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 2 ].w -
    m->m[ 1 ].x * m->m[ 0 ].w * m->m[ 2 ].y -
    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 1 ].w +
    m->m[ 2 ].x * m->m[ 0 ].w * m->m[ 1 ].y;
    
    inv.m[ 3 ].w = m->m[ 0 ].x * m->m[ 1 ].y * m->m[ 2 ].z -
    m->m[ 0 ].x * m->m[ 1 ].z * m->m[ 2 ].y -
    m->m[ 1 ].x * m->m[ 0 ].y * m->m[ 2 ].z +
    m->m[ 1 ].x * m->m[ 0 ].z * m->m[ 2 ].y +
    m->m[ 2 ].x * m->m[ 0 ].y * m->m[ 1 ].z -
    m->m[ 2 ].x * m->m[ 0 ].z * m->m[ 1 ].y;
    
    d = m->m[ 0 ].x * inv.m[ 0 ].x +
    m->m[ 0 ].y * inv.m[ 1 ].x +
    m->m[ 0 ].z * inv.m[ 2 ].x +
    m->m[ 0 ].w * inv.m[ 3 ].x;
    
    if( !d ) return 0;
    
    d = 1.0f / d;
    
    inv.m[ 0 ].x *= d;
    inv.m[ 0 ].y *= d;
    inv.m[ 0 ].z *= d;
    inv.m[ 0 ].w *= d;
    
    inv.m[ 1 ].x *= d;
    inv.m[ 1 ].y *= d;
    inv.m[ 1 ].z *= d;
    inv.m[ 1 ].w *= d;
    
    inv.m[ 2 ].x *= d;
    inv.m[ 2 ].y *= d;
    inv.m[ 2 ].z *= d;
    inv.m[ 2 ].w *= d;
    
    inv.m[ 3 ].x *= d;
    inv.m[ 3 ].y *= d;
    inv.m[ 3 ].z *= d;
    inv.m[ 3 ].w *= d;
    
//    mat4_copy_mat4( m, &inv );
    copy(inv);
    
    return 1;
}
/*!
	Transpose a 4x4 matrix.
	
	\param[in,out] m A valid 4x4 matrix pointer to use as the source and destination of the transpose operation.
 */
//void mat4_transpose( mat4 *m )
//{
//    float t;
//    
//    t			= m->m[ 0 ].y;
//    m->m[ 0 ].y = m->m[ 1 ].x;
//    m->m[ 1 ].x = t;
//    
//    t			= m->m[ 0 ].z;
//    m->m[ 0 ].z = m->m[ 2 ].x;
//    m->m[ 2 ].x = t;
//    
//    t			= m->m[ 0 ].w;
//    m->m[ 0 ].w = m->m[ 3 ].x;
//    m->m[ 3 ].x = t;
//    
//    t			= m->m[ 1 ].z;
//    m->m[ 1 ].z = m->m[ 2 ].y;
//    m->m[ 2 ].y = t;
//    
//    t			= m->m[ 1 ].w ;
//    m->m[ 1 ].w = m->m[ 3 ].y ;
//    m->m[ 3 ].y = t;
//    
//    t			= m->m[ 2 ].w ;
//    m->m[ 2 ].w = m->m[ 3 ].z ;
//    m->m[ 3 ].z = t;
//}

void mat4::transpose()
{
    float t;
    mat4 *m = this;
    
    t			= m->m[ 0 ].y;
    m->m[ 0 ].y = m->m[ 1 ].x;
    m->m[ 1 ].x = t;
    
    t			= m->m[ 0 ].z;
    m->m[ 0 ].z = m->m[ 2 ].x;
    m->m[ 2 ].x = t;
    
    t			= m->m[ 0 ].w;
    m->m[ 0 ].w = m->m[ 3 ].x;
    m->m[ 3 ].x = t;
    
    t			= m->m[ 1 ].z;
    m->m[ 1 ].z = m->m[ 2 ].y;
    m->m[ 2 ].y = t;
    
    t			= m->m[ 1 ].w ;
    m->m[ 1 ].w = m->m[ 3 ].y ;
    m->m[ 3 ].y = t;
    
    t			= m->m[ 2 ].w ;
    m->m[ 2 ].w = m->m[ 3 ].z ;
    m->m[ 3 ].z = t;
}
/*!
	Create an orthographic matrix.
 
	\param[in,out] dst A valid 4x4 matrix that will be use as destination.
	\param[in] left Specify the coordinates for the left vertical clipping planes.
	\param[in] right Specify the coordinates for the right vertical clipping planes.
	\param[in] bottom Specify the coordinates for the bottom horizontal clipping planes.
	\param[in] top Specify the coordinates for the top horizontal clipping planes.
	\param[in] clip_start Specify the distance to the nearer depth clipping planes. This value is negative if the plane is to be behind the viewer.
	\param[in] clip_end Specify the distance to the farther depth clipping planes. This value is negative if the plane is to be behind the viewer.
 */
//void mat4_ortho( mat4 *dst, float left, float right, float bottom, float top, float clip_start, float clip_end )
//{
//    mat4 mat;
//    
//    mat.m[ 0 ].x = 2.0f / ( right - left  );
//    mat.m[ 1 ].x = 0.0f;
//    mat.m[ 2 ].x = 0.0f;
//    mat.m[ 3 ].x = -( right + left ) / ( right - left );
//    
//    mat.m[ 0 ].y = 0.0f;
//    mat.m[ 1 ].y = 2.0f / ( top - bottom );
//    mat.m[ 2 ].y = 0.0f;
//    mat.m[ 3 ].y = -( top + bottom ) / ( top - bottom );
//    
//    mat.m[ 0 ].z = 0.0f;
//    mat.m[ 1 ].z = 0.0f;
//    mat.m[ 2 ].z = -2.0f / ( clip_end - clip_start );
//    mat.m[ 3 ].z = -( clip_end + clip_start ) / ( clip_end - clip_start );
//    
//    mat.m[ 0 ].w =
//    mat.m[ 1 ].w =
//    mat.m[ 2 ].w = 0.0f;
//    mat.m[ 3 ].w = 1.0f;
//    
//    mat4_multiply_mat4( dst, dst, &mat );
//}

void mat4::ortho(float left, float right, float bottom, float top, float clip_start, float clip_end )
{
    mat4 mat;
    
    mat.m[ 0 ].x = 2.0f / ( right - left  );
    mat.m[ 1 ].x = 0.0f;
    mat.m[ 2 ].x = 0.0f;
    mat.m[ 3 ].x = -( right + left ) / ( right - left );
    
    mat.m[ 0 ].y = 0.0f;
    mat.m[ 1 ].y = 2.0f / ( top - bottom );
    mat.m[ 2 ].y = 0.0f;
    mat.m[ 3 ].y = -( top + bottom ) / ( top - bottom );
    
    mat.m[ 0 ].z = 0.0f;
    mat.m[ 1 ].z = 0.0f;
    mat.m[ 2 ].z = -2.0f / ( clip_end - clip_start );
    mat.m[ 3 ].z = -( clip_end + clip_start ) / ( clip_end - clip_start );
    
    mat.m[ 0 ].w =
    mat.m[ 1 ].w =
    mat.m[ 2 ].w = 0.0f;
    mat.m[ 3 ].w = 1.0f;
    
    copy(multiply(mat));
}
/*!
	Copy a 3x3 matrix to a 4x4 matrix.
 
	\param[in,out] dst A valid 4x4 matrix pointer that will be use as the destination.
	\param[in] m A valid 3x3 matrix pointer used as the source.
 */
//void mat4_copy_mat3( mat4 *dst, mat3 *m )
//{
//    memcpy( &dst->m[ 0 ], &m->m[ 0 ], sizeof( vec3 ) );
//    memcpy( &dst->m[ 1 ], &m->m[ 1 ], sizeof( vec3 ) );
//    memcpy( &dst->m[ 2 ], &m->m[ 2 ], sizeof( vec3 ) );
//}

void mat4::copy(const mat3&m3)
{
    m[0].x = m3.m[0].x; m[0].y = m3.m[0].y; m[0].z = m3.m[0].z; m[0].w = 0;
    m[1].x = m3.m[1].x; m[1].y = m3.m[1].y; m[1].z = m3.m[1].z; m[1].w = 0;
    m[2].x = m3.m[2].x; m[2].y = m3.m[2].y; m[2].z = m3.m[2].z; m[2].w = 0;
    m[3].x = 0; m[3].y = 0; m[3].z = 0; m[3].w = 0;
}
/*!
	Multiply a 4x4 matrix by a 3x3 matrix.
	
	\param[in,out] dst A valid 4x4 matrix pointer that will be used to store the result of the operation.
	\param[in] m0 A valid 4x4 matrix used as source.
	\param[in] m1 A valid 3x3 matrix used as source.
 */
//void mat4_multiply_mat3( mat4 *dst, mat4 *m0, mat3 *m1 )
//{
//    mat3 mat;
//    
//    mat.m[ 0 ].x = m0->m[ 0 ].x * m1->m[ 0 ].x + m0->m[ 1 ].x * m1->m[ 0 ].y + m0->m[ 2 ].x * m1->m[ 0 ].z;
//    mat.m[ 0 ].y = m0->m[ 0 ].y * m1->m[ 0 ].x + m0->m[ 1 ].y * m1->m[ 0 ].y + m0->m[ 2 ].y * m1->m[ 0 ].z;
//    mat.m[ 0 ].z = m0->m[ 0 ].z * m1->m[ 0 ].x + m0->m[ 1 ].z * m1->m[ 0 ].y + m0->m[ 2 ].z * m1->m[ 0 ].z;
//    
//    mat.m[ 1 ].x = m0->m[ 0 ].x * m1->m[ 1 ].x + m0->m[ 1 ].x * m1->m[ 1 ].y + m0->m[ 2 ].x * m1->m[ 1 ].z;
//    mat.m[ 1 ].y = m0->m[ 0 ].y * m1->m[ 1 ].x + m0->m[ 1 ].y * m1->m[ 1 ].y + m0->m[ 2 ].y * m1->m[ 1 ].z;
//    mat.m[ 1 ].z = m0->m[ 0 ].z * m1->m[ 1 ].x + m0->m[ 1 ].z * m1->m[ 1 ].y + m0->m[ 2 ].z * m1->m[ 1 ].z;
//    
//    mat.m[ 2 ].x = m0->m[ 0 ].x * m1->m[ 2 ].x + m0->m[ 1 ].x * m1->m[ 2 ].y + m0->m[ 2 ].x * m1->m[ 2 ].z;
//    mat.m[ 2 ].y = m0->m[ 0 ].y * m1->m[ 2 ].x + m0->m[ 1 ].y * m1->m[ 2 ].y + m0->m[ 2 ].y * m1->m[ 2 ].z;
//    mat.m[ 2 ].z = m0->m[ 0 ].z * m1->m[ 2 ].x + m0->m[ 1 ].z * m1->m[ 2 ].y + m0->m[ 2 ].z * m1->m[ 2 ].z;
//    
//    mat4_copy_mat3( dst, &mat );
//}

mat3 mat4::multiply(const mat3& m1r) const
{
    const mat3* m1 = &m1r;
    mat3 mat;
    const mat4 *m0 = this;
    
    mat.m[ 0 ].x = m0->m[ 0 ].x * m1->m[ 0 ].x + m0->m[ 1 ].x * m1->m[ 0 ].y + m0->m[ 2 ].x * m1->m[ 0 ].z;
    mat.m[ 0 ].y = m0->m[ 0 ].y * m1->m[ 0 ].x + m0->m[ 1 ].y * m1->m[ 0 ].y + m0->m[ 2 ].y * m1->m[ 0 ].z;
    mat.m[ 0 ].z = m0->m[ 0 ].z * m1->m[ 0 ].x + m0->m[ 1 ].z * m1->m[ 0 ].y + m0->m[ 2 ].z * m1->m[ 0 ].z;
    
    mat.m[ 1 ].x = m0->m[ 0 ].x * m1->m[ 1 ].x + m0->m[ 1 ].x * m1->m[ 1 ].y + m0->m[ 2 ].x * m1->m[ 1 ].z;
    mat.m[ 1 ].y = m0->m[ 0 ].y * m1->m[ 1 ].x + m0->m[ 1 ].y * m1->m[ 1 ].y + m0->m[ 2 ].y * m1->m[ 1 ].z;
    mat.m[ 1 ].z = m0->m[ 0 ].z * m1->m[ 1 ].x + m0->m[ 1 ].z * m1->m[ 1 ].y + m0->m[ 2 ].z * m1->m[ 1 ].z;
    
    mat.m[ 2 ].x = m0->m[ 0 ].x * m1->m[ 2 ].x + m0->m[ 1 ].x * m1->m[ 2 ].y + m0->m[ 2 ].x * m1->m[ 2 ].z;
    mat.m[ 2 ].y = m0->m[ 0 ].y * m1->m[ 2 ].x + m0->m[ 1 ].y * m1->m[ 2 ].y + m0->m[ 2 ].y * m1->m[ 2 ].z;
    mat.m[ 2 ].z = m0->m[ 0 ].z * m1->m[ 2 ].x + m0->m[ 1 ].z * m1->m[ 2 ].y + m0->m[ 2 ].z * m1->m[ 2 ].z;
    
    return mat;
}
/*!
	Multiply a 4x4 matrix by another 4x4 matrix (multiply m0 by m1).
	
	\param[in,out] dst A valid 4x4 matrix pointer to store the result of the operation.
	\param[in] m0 A valid 4x4 pointer.
	\param[in] m1 A valid 4x4 pointer.
 */
//void mat4_multiply_mat4( mat4 *dst, mat4 *m0, mat4 *m1 )
//{
//    mat4 mat;
//    
//    mat.m[ 0 ].x = m0->m[ 0 ].x * m1->m[ 0 ].x + m0->m[ 1 ].x * m1->m[ 0 ].y + m0->m[ 2 ].x * m1->m[ 0 ].z + m0->m[ 3 ].x * m1->m[ 0 ].w;
//    mat.m[ 0 ].y = m0->m[ 0 ].y * m1->m[ 0 ].x + m0->m[ 1 ].y * m1->m[ 0 ].y + m0->m[ 2 ].y * m1->m[ 0 ].z + m0->m[ 3 ].y * m1->m[ 0 ].w;
//    mat.m[ 0 ].z = m0->m[ 0 ].z * m1->m[ 0 ].x + m0->m[ 1 ].z * m1->m[ 0 ].y + m0->m[ 2 ].z * m1->m[ 0 ].z + m0->m[ 3 ].z * m1->m[ 0 ].w;
//    mat.m[ 0 ].w = m0->m[ 0 ].w * m1->m[ 0 ].x + m0->m[ 1 ].w * m1->m[ 0 ].y + m0->m[ 2 ].w * m1->m[ 0 ].z + m0->m[ 3 ].w * m1->m[ 0 ].w;
//    
//    mat.m[ 1 ].x = m0->m[ 0 ].x * m1->m[ 1 ].x + m0->m[ 1 ].x * m1->m[ 1 ].y + m0->m[ 2 ].x * m1->m[ 1 ].z + m0->m[ 3 ].x * m1->m[ 1 ].w;
//    mat.m[ 1 ].y = m0->m[ 0 ].y * m1->m[ 1 ].x + m0->m[ 1 ].y * m1->m[ 1 ].y + m0->m[ 2 ].y * m1->m[ 1 ].z + m0->m[ 3 ].y * m1->m[ 1 ].w;
//    mat.m[ 1 ].z = m0->m[ 0 ].z * m1->m[ 1 ].x + m0->m[ 1 ].z * m1->m[ 1 ].y + m0->m[ 2 ].z * m1->m[ 1 ].z + m0->m[ 3 ].z * m1->m[ 1 ].w;
//    mat.m[ 1 ].w = m0->m[ 0 ].w * m1->m[ 1 ].x + m0->m[ 1 ].w * m1->m[ 1 ].y + m0->m[ 2 ].w * m1->m[ 1 ].z + m0->m[ 3 ].w * m1->m[ 1 ].w;
//    
//    mat.m[ 2 ].x = m0->m[ 0 ].x * m1->m[ 2 ].x + m0->m[ 1 ].x * m1->m[ 2 ].y + m0->m[ 2 ].x * m1->m[ 2 ].z + m0->m[ 3 ].x * m1->m[ 2 ].w;
//    mat.m[ 2 ].y = m0->m[ 0 ].y * m1->m[ 2 ].x + m0->m[ 1 ].y * m1->m[ 2 ].y + m0->m[ 2 ].y * m1->m[ 2 ].z + m0->m[ 3 ].y * m1->m[ 2 ].w;
//    mat.m[ 2 ].z = m0->m[ 0 ].z * m1->m[ 2 ].x + m0->m[ 1 ].z * m1->m[ 2 ].y + m0->m[ 2 ].z * m1->m[ 2 ].z + m0->m[ 3 ].z * m1->m[ 2 ].w;
//    mat.m[ 2 ].w = m0->m[ 0 ].w * m1->m[ 2 ].x + m0->m[ 1 ].w * m1->m[ 2 ].y + m0->m[ 2 ].w * m1->m[ 2 ].z + m0->m[ 3 ].w * m1->m[ 2 ].w;
//    
//    mat.m[ 3 ].x = m0->m[ 0 ].x * m1->m[ 3 ].x + m0->m[ 1 ].x * m1->m[ 3 ].y + m0->m[ 2 ].x * m1->m[ 3 ].z + m0->m[ 3 ].x * m1->m[ 3 ].w;
//    mat.m[ 3 ].y = m0->m[ 0 ].y * m1->m[ 3 ].x + m0->m[ 1 ].y * m1->m[ 3 ].y + m0->m[ 2 ].y * m1->m[ 3 ].z + m0->m[ 3 ].y * m1->m[ 3 ].w;
//    mat.m[ 3 ].z = m0->m[ 0 ].z * m1->m[ 3 ].x + m0->m[ 1 ].z * m1->m[ 3 ].y + m0->m[ 2 ].z * m1->m[ 3 ].z + m0->m[ 3 ].z * m1->m[ 3 ].w;
//    mat.m[ 3 ].w = m0->m[ 0 ].w * m1->m[ 3 ].x + m0->m[ 1 ].w * m1->m[ 3 ].y + m0->m[ 2 ].w * m1->m[ 3 ].z + m0->m[ 3 ].w * m1->m[ 3 ].w;
//    
//    mat4_copy_mat4( dst, &mat );
//}


mat4 mat4::multiply(const mat4& m1r) const
{
    const mat4* m1 = &m1r;
    mat4 mat;
    const mat4 *m0 = this;
    
    mat.m[ 0 ].x = m0->m[ 0 ].x * m1->m[ 0 ].x + m0->m[ 1 ].x * m1->m[ 0 ].y + m0->m[ 2 ].x * m1->m[ 0 ].z + m0->m[ 3 ].x * m1->m[ 0 ].w;
    mat.m[ 0 ].y = m0->m[ 0 ].y * m1->m[ 0 ].x + m0->m[ 1 ].y * m1->m[ 0 ].y + m0->m[ 2 ].y * m1->m[ 0 ].z + m0->m[ 3 ].y * m1->m[ 0 ].w;
    mat.m[ 0 ].z = m0->m[ 0 ].z * m1->m[ 0 ].x + m0->m[ 1 ].z * m1->m[ 0 ].y + m0->m[ 2 ].z * m1->m[ 0 ].z + m0->m[ 3 ].z * m1->m[ 0 ].w;
    mat.m[ 0 ].w = m0->m[ 0 ].w * m1->m[ 0 ].x + m0->m[ 1 ].w * m1->m[ 0 ].y + m0->m[ 2 ].w * m1->m[ 0 ].z + m0->m[ 3 ].w * m1->m[ 0 ].w;
    
    mat.m[ 1 ].x = m0->m[ 0 ].x * m1->m[ 1 ].x + m0->m[ 1 ].x * m1->m[ 1 ].y + m0->m[ 2 ].x * m1->m[ 1 ].z + m0->m[ 3 ].x * m1->m[ 1 ].w;
    mat.m[ 1 ].y = m0->m[ 0 ].y * m1->m[ 1 ].x + m0->m[ 1 ].y * m1->m[ 1 ].y + m0->m[ 2 ].y * m1->m[ 1 ].z + m0->m[ 3 ].y * m1->m[ 1 ].w;
    mat.m[ 1 ].z = m0->m[ 0 ].z * m1->m[ 1 ].x + m0->m[ 1 ].z * m1->m[ 1 ].y + m0->m[ 2 ].z * m1->m[ 1 ].z + m0->m[ 3 ].z * m1->m[ 1 ].w;
    mat.m[ 1 ].w = m0->m[ 0 ].w * m1->m[ 1 ].x + m0->m[ 1 ].w * m1->m[ 1 ].y + m0->m[ 2 ].w * m1->m[ 1 ].z + m0->m[ 3 ].w * m1->m[ 1 ].w;
    
    mat.m[ 2 ].x = m0->m[ 0 ].x * m1->m[ 2 ].x + m0->m[ 1 ].x * m1->m[ 2 ].y + m0->m[ 2 ].x * m1->m[ 2 ].z + m0->m[ 3 ].x * m1->m[ 2 ].w;
    mat.m[ 2 ].y = m0->m[ 0 ].y * m1->m[ 2 ].x + m0->m[ 1 ].y * m1->m[ 2 ].y + m0->m[ 2 ].y * m1->m[ 2 ].z + m0->m[ 3 ].y * m1->m[ 2 ].w;
    mat.m[ 2 ].z = m0->m[ 0 ].z * m1->m[ 2 ].x + m0->m[ 1 ].z * m1->m[ 2 ].y + m0->m[ 2 ].z * m1->m[ 2 ].z + m0->m[ 3 ].z * m1->m[ 2 ].w;
    mat.m[ 2 ].w = m0->m[ 0 ].w * m1->m[ 2 ].x + m0->m[ 1 ].w * m1->m[ 2 ].y + m0->m[ 2 ].w * m1->m[ 2 ].z + m0->m[ 3 ].w * m1->m[ 2 ].w;
    
    mat.m[ 3 ].x = m0->m[ 0 ].x * m1->m[ 3 ].x + m0->m[ 1 ].x * m1->m[ 3 ].y + m0->m[ 2 ].x * m1->m[ 3 ].z + m0->m[ 3 ].x * m1->m[ 3 ].w;
    mat.m[ 3 ].y = m0->m[ 0 ].y * m1->m[ 3 ].x + m0->m[ 1 ].y * m1->m[ 3 ].y + m0->m[ 2 ].y * m1->m[ 3 ].z + m0->m[ 3 ].y * m1->m[ 3 ].w;
    mat.m[ 3 ].z = m0->m[ 0 ].z * m1->m[ 3 ].x + m0->m[ 1 ].z * m1->m[ 3 ].y + m0->m[ 2 ].z * m1->m[ 3 ].z + m0->m[ 3 ].z * m1->m[ 3 ].w;
    mat.m[ 3 ].w = m0->m[ 0 ].w * m1->m[ 3 ].x + m0->m[ 1 ].w * m1->m[ 3 ].y + m0->m[ 2 ].w * m1->m[ 3 ].z + m0->m[ 3 ].w * m1->m[ 3 ].w;
    
    return mat;
}
    
}





