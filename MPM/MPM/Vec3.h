// Vec3.h - Zander Clucas 2014
// Handles all Vec3 functionality
#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <glew.h>

class Vec3
{
    public:
        GLfloat x, y, z;

    public:
        Vec3( GLfloat=0, GLfloat=0, GLfloat=0 );
        Vec3&   operator=( const Vec3& );
        Vec3    operator+( const Vec3& );
        Vec3    operator-( const Vec3& );       // binary -
        Vec3    operator-( );                   // unary -
        Vec3    cross( Vec3& );
        GLfloat   dot( Vec3& );
        void	export_out( GLfloat [3] );
        GLfloat   length( );
        void    print( char * = "", FILE * = stderr );
        Vec3    normalize( );

    friend class Mat4;
};

inline GLfloat
SQR( GLfloat f )
{
    return f * f;
}

#endif