// Mat4.h - Zander Clucas 2014
// Handles all Mat4 functionality
#ifndef MAT4_H
#define MAT4_H

// Includes
#include <stdio.h>
#include <string.h>
#define _USE_MATH_INCLUDES
#include <cmath>
#include "Vec3.h"
#include <glew.h>

class Mat4
{
    public:
        GLfloat	m[4][4];
        
    public:
    Mat4( );
    Mat4( Vec3, GLfloat, Vec3, GLfloat, Vec3, GLfloat, Vec3, GLfloat );
    Mat4( GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,
          GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
    void    constructor( Vec3, GLfloat, Vec3, GLfloat, Vec3, GLfloat, Vec3, GLfloat );
    void    constructor( GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,
                         GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
    Mat4&	operator=( const Mat4& );
    Mat4	operator*( Mat4& );
    Vec3	operator*( Vec3& );
    void	export_out(	GLfloat [4][4] );
    void	print( char * = "", FILE * = stderr );
    void	set_identity( );
    void	set_rotateX( GLfloat );
    void	set_rotateY( GLfloat );
    void	set_rotateZ( GLfloat );
    void	set_scale( GLfloat, GLfloat, GLfloat );
    void    set_translate( Vec3 );
    void	set_translate( GLfloat, GLfloat, GLfloat );
    void	set_transpose( );
    void    set_perspective( GLfloat fovy, GLfloat ratio, GLfloat znear, GLfloat zfar);
};

inline Mat4 lookat(Vec3 eye, Vec3 at, Vec3 up)
{
    Vec3 n = (eye - at).normalize();
    Vec3 u = up.cross(n).normalize();
    Vec3 v = n.cross(u).normalize();
    Vec3 t;
    Mat4 c(u,0.0f, v,0.0f, n,0.0f, t,1.0f);
    Mat4 trans;
    trans.set_translate( -eye );
    return c * trans;
}
#endif          // MAT4_H