// Mat4.cpp - Zander Clucas 2014
// Handles all Mat4 functionality
#include "mat4.h"

const GLfloat D2R = (GLfloat)/*M_PI*/3.14159265358979323846 / 180.f; //M_PI

Mat4::Mat4( )
{
    set_identity( );
}

Mat4::Mat4( Vec3 v1, GLfloat f1, Vec3 v2, GLfloat f2, Vec3 v3, GLfloat f3, Vec3 v4, GLfloat f4 )
{
    constructor(v1.x,v1.y,v1.z,f1, v2.x,v2.y,v2.z,f2, v3.x,v3.y,v3.z,f3, v4.x,v4.y,v4.z,f2);
}

Mat4::Mat4( GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f, GLfloat g, GLfloat h,
            GLfloat i, GLfloat j, GLfloat k, GLfloat l, GLfloat n, GLfloat o, GLfloat p, GLfloat q )
{
    constructor(a,b,c,d,e,f,g,h,i,j,k,l,n,o,p,q);
}

void Mat4::constructor( Vec3 v1, GLfloat f1, Vec3 v2, GLfloat f2, Vec3 v3, GLfloat f3, Vec3 v4, GLfloat f4 )
{
    constructor(v1.x,v1.y,v1.z,f1, v2.x,v2.y,v2.z,f2, v3.x,v3.y,v3.z,f3, v4.x,v4.y,v4.z,f2);
}

void Mat4::constructor( GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f, GLfloat g, GLfloat h,
                        GLfloat i, GLfloat j, GLfloat k, GLfloat l, GLfloat n, GLfloat o, GLfloat p, GLfloat q )
{
    m[0][0] = a;
    m[0][1] = b;
    m[0][2] = c;
    m[0][3] = d;
    m[1][0] = e;
    m[1][1] = f;
    m[1][2] = g;
    m[1][3] = h;
    m[2][0] = i;
    m[2][1] = j;
    m[2][2] = k;
    m[2][3] = l;
    m[3][0] = n;
    m[3][1] = o;
    m[3][2] = p;
    m[3][3] = q;
}

Mat4& Mat4::operator=( const Mat4& that )
{
    // "this" is a pointer to this class's mat4  (this->name)
    // "that" is a reference to the other matrix (that.name)

    this->m[0][0] = that.m[0][0];
    this->m[0][1] = that.m[0][1];
    this->m[0][2] = that.m[0][2];
    this->m[0][3] = that.m[0][3];
    this->m[1][0] = that.m[1][0];
    this->m[1][1] = that.m[1][1];
    this->m[1][2] = that.m[1][2];
    this->m[1][3] = that.m[1][3];
    this->m[2][0] = that.m[2][0];
    this->m[2][1] = that.m[2][1];
    this->m[2][2] = that.m[2][2];
    this->m[2][3] = that.m[2][3];
    this->m[3][0] = that.m[3][0];
    this->m[3][1] = that.m[3][1];
    this->m[3][2] = that.m[3][2];
    this->m[3][3] = that.m[3][3];

    return *this;
}

Mat4 Mat4::operator*( Mat4& that )
{
    // "this" is a pointer to this class's mat4  (this->name)
    // "that" is a reference to the other matrix (that.name)

    Mat4 result;

    for( int i = 0; i < 4; i++)
    {
        for( int j = 0; j < 4; j++)
        {
            result.m[i][j] = 0.;
            for( int k = 0; k < 4; k++)
            {
                result.m[i][j] += this->m[i][k] * that.m[k][j];
            }
        }
    }
    
    return result;
}

Vec3 Mat4::operator*( Vec3& that )
{
    // "this" is a pointer to this class's mat4  (this->name)
    // "that" is a reference to the vector (that.name)

    Vec3 result;

    result.x = ( this->m[0][0] * that.x ) + ( this->m[0][1] * that.y ) + ( this->m[0][2] * that.z ) + ( this->m[0][3] );
    result.y = ( this->m[1][0] * that.x ) + ( this->m[1][1] * that.y ) + ( this->m[1][2] * that.z ) + ( this->m[0][3] );
    result.z = ( this->m[2][0] * that.x ) + ( this->m[2][1] * that.y ) + ( this->m[2][2] * that.z ) + ( this->m[0][3] );

    return result;
}

void Mat4::export_out( GLfloat out[4][4] )
{
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            out[i][j] = m[i][j];
}

void Mat4::print( char *str, FILE *fp )
{
    // "this" is a pointer to this class's mat4  (this->name)

    fprintf( fp, "%s \n", str );
    fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[0][0], this->m[0][1], this->m[0][2], this->m[0][3] );
    fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[1][0], this->m[1][1], this->m[1][2], this->m[1][3] );
    fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[2][0], this->m[2][1], this->m[2][2], this->m[2][3] );
    fprintf( fp, "\t%8.2f  %8.2f  %8.2f  %8.2f\n", this->m[3][0], this->m[3][1], this->m[3][2], this->m[3][3] );
}

void Mat4::set_identity( )
{
    // "this" is a pointer to this class's mat4  (this->name)

    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            if(col == row)
            {
                this->m[row][col] = 1.;
            }
            else
            {
                this->m[row][col] = 0.;
            }
        }
    }
}

void Mat4::set_rotateX( GLfloat deg )
{
    // "this" is a pointer to this class's mat4  (this->name)
    
    GLfloat theta = deg * D2R;

    set_identity( );
    
    this->m[1][1] = cos(theta);
    this->m[2][2] = cos(theta);
    this->m[2][1] = sin(theta);
    this->m[1][2] = -sin(theta);
}

void Mat4::set_rotateY( GLfloat deg )
{
    // "this" is a pointer to this class's mat4  (this->name)

    GLfloat theta = deg * D2R;

    set_identity( );
    
    this->m[0][0] = cos(theta);
    this->m[2][2] = cos(theta);
    this->m[2][0] = -sin(theta);
    this->m[0][2] = sin(theta);
}

void Mat4::set_rotateZ( GLfloat deg )
{
    // "this" is a pointer to this class's mat4  (this->name)
    
    GLfloat theta = deg * D2R;

    set_identity( );
    
    this->m[0][0] = cos(theta);
    this->m[1][1] = cos(theta);
    this->m[1][0] = sin(theta);
    this->m[0][1] = -sin(theta);
}

void Mat4::set_scale( GLfloat sx, GLfloat sy, GLfloat sz )
{
    // "this" is a pointer to this class's mat4  (this->name)

    set_identity( );

    this->m[0][0] = sx;
    this->m[1][1] = sy;
    this->m[2][2] = sz;
}

void Mat4::set_translate( Vec3 translate )
{
    set_translate( translate.x, translate.y, translate.z );
}

void Mat4::set_translate( GLfloat tx, GLfloat ty, GLfloat tz )
{
    // "this" is a pointer to this class's mat4  (this->name)
    
    set_identity( );

    this->m[0][3] = tx;
    this->m[1][3] = ty;
    this->m[2][3] = tz;
}

void Mat4::set_transpose( )
{
    // "this" is a pointer to this class's mat4  (this->name)
    
    Mat4 *temp = new Mat4();

    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            temp->m[col][row] = this->m[row][col];
        }
    }
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            this->m[row][col] = temp->m[row][col];
        }
    }
}

void Mat4::set_perspective( GLfloat fovy, GLfloat ratio, GLfloat znear, GLfloat zfar)
{
    GLfloat top   = tan(fovy*D2R/2.0f) * znear;
    GLfloat right = top * ratio;

    set_identity();
    m[0][0] = znear/right;
    m[1][1] = znear/top;
    m[2][2] = -(zfar + znear)/(zfar - znear);
    m[2][3] = -2.0*zfar*znear/(zfar - znear);
    m[3][2] = -1.0;
    m[3][3] = 0.0;
}