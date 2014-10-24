// Vec3.cpp - Zander Clucas 2014
// Handles all Vec3 functionality

#include "Vec3.h"

Vec3::Vec3( GLfloat x, GLfloat y, GLfloat z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3& Vec3::operator=( const Vec3& rhs )
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

Vec3 Vec3::operator+( const Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
	result.x = this->x + that.x;
	result.y = this->y + that.y;
	result.z = this->z + that.z;
	return result;
}

Vec3 Vec3::operator-( const Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
	result.x = this->x - that.x;
	result.y = this->y - that.y;
	result.z = this->z - that.z;
	return result;
}

Vec3 Vec3::operator-( )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// there is no "that" here
	Vec3 result;
	result.x = this->x * -1;
	result.y = this->y * -1;
	result.z = this->z * -1;
	return result;
}

Vec3 Vec3::cross( Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	Vec3 result;
	result.x = (this->y * that.z) - (this->z * that.y);
	result.y = (this->z * that.x) - (this->x * that.z);
	result.z = (this->x * that.y) - (this->y * that.x);
	return result;
}

GLfloat Vec3::dot( Vec3& that )
{
	// "this" is a pointer to this class's vec3  (this->name)
	// "that" is a reference to the other vector (that.name)
	GLfloat d = (this->x * that.x) + (this->y * that.y) + (this->z * that.z);
	return d;
}

void Vec3::export_out( GLfloat out[3] )
{
	out[0] = x;
	out[1] = y;
	out[2] = z;
}

GLfloat Vec3::length( )
{
	// "this" is a pointer to this class's vec3  (this->name)
	GLfloat len = sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
	return len;
}

void Vec3::print( char *str, FILE *fp )
{
	fprintf( fp, "%s [ %8.3f %8.3f %8.3f ]\n", str, this->x, this->y, this->z );
}

Vec3 Vec3::normalize( )
{
	// "this" is a pointer to this class's vec3  (this->name)
	Vec3 result;
	GLfloat len = length();
	result.x = this->x / len;
	result.y = this->y / len;
	result.z = this->z / len;
	return result;
}