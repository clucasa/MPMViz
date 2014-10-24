// Structs.h - Zander Clucas 2014
// adds all important structs
#ifndef STRUCTS_H
#define STRUCTS_H

// Includes
#include "Vertex.h"
//#include "Mat4.h"
//#include "Vec3.h"
#include "Angel.h"

#include <string>
#include <iostream>
#include <ostream>

typedef Angel::mat4 Mat4;
typedef Angel::vec3 Vec3;

// routine to convert HSV to RGB 
// 
// Reference:  Foley, van Dam, Feiner, Hughes, 
//      "Computer Graphics Principles and Practices,"   
inline void HsvRgb( GLfloat hsv[3], GLfloat rgb[3] ) 
{ 
    GLfloat r , g, b;          // red, green, blue 
	GLfloat tol = 0.0001;
    // guarantee valid input: 
	if (hsv[0] < (0 + tol) && hsv[0] > (0-tol))
	{
		hsv[0] = 0.;
	}
	if (hsv[0] < (6 + tol) && hsv[0] > (6 - tol))
	{
		hsv[0] = 0.;
	}

    GLfloat h = hsv[0] / 60.; 
    while( h >= 6. ) h -= 6.; 
    while( h <  0. )     h += 6.; 
  
    GLfloat s = hsv[1]; 
    if( s < 0. ) 
        s = 0.; 
    if( s > 1. ) 
        s = 1.; 
  
    GLfloat v = hsv[2]; 
    if( v < 0. ) 
        v = 0.; 
    if( v > 1. ) 
        v = 1.; 
  
  
    // if sat==0, then is a gray: 
  
    if( s == 0.0 ) 
    { 
        rgb[0] = rgb[1] = rgb[2] = v; 
        return; 
    } 
  
  
    // get an rgb from the hue itself: 
      
    GLfloat i = floor( h ); 
    GLfloat f = h - i; 
    GLfloat p = v * ( 1. - s ); 
    GLfloat q = v * ( 1. - s*f ); 
    GLfloat t = v * ( 1. - ( s * (1.-f) ) ); 
  
    switch( (int) i ) 
    { 
        case 0: 
            r = v;  g = t;  b = p; 
            break; 
      
        case 1: 
            r = q;  g = v;  b = p; 
            break; 
      
        case 2: 
            r = p;  g = v;  b = t; 
            break; 
      
        case 3: 
            r = p;  g = q;  b = v; 
            break; 
      
        case 4: 
            r = t;  g = p;  b = v; 
            break; 
      
        case 5: 
            r = v;  g = p;  b = q; 
            break; 
    } 
  
  
    rgb[0] = r; 
    rgb[1] = g; 
    rgb[2] = b; 
}


//std::string POV_FILE =
//"// File by Alexander Clucas"
//"// Snowball"
//"#version 3.7;"
//"global_settings{ assumed_gamma 1.0  max_trace_level 10 }"
//""
//"global_settings{"
//"	assumed_gamma 1.0"
//"	number_of_waves 3"
//"	max_trace_level 5"
//"}"
//""
//R"#include "colors.inc""
//R"#include "shapes.inc"
//R"#include "textures.inc"
//R"
//R"camera{
//R"	location <20.0, 15.0, -45.0>
//R"	angle 15 //  direction z
//R"	up y
//R"	right x*image_width / image_height
//R"	look_at <0.0, 0.0, 0.0>
//R"}
//R"
//R"light_source{ <10.0, 50.0, 35.0> colour White }
//R"light_source{ <-35.0, 30.0, -150.0> colour White }
//R"
//R"#declare Snow =
//R"texture{
//R"	pigment{
//R"	color rgb <0.9, 0.95, 1>
//R"}
//R"	normal{
//R"		gradient y .5
//R"		slope_map{
//R"		[0 <.1, .1>]
//R"		[0.25 <.25, 0>]
//R"		[0.5 <.1, -.1>]
//R"		[0.75 <.25, 0>]
//R"		[1 <.1, .1>]
//R"	}
//R"		turbulence 0.5
//R"			scale 3
//R"	}
//R"	finish{
//R"		brilliance 0.75
//R"		phong 0.1
//R"		phong_size 5
//R"		subsurface{ translucency <0.1, 0.31, 0.48> }
//R"		//emission .2
//R"		//use with  radiosity instead
//R"	}
//R"}
//R"
//R"texture{
//R"	pigment{
//R"	color rgbt <1, 1, 1, .9>
//R"}
//R"	normal{
//R"		bumps 5
//R"		scale .05
//R"	}
//R"	finish{
//R"		specular 1
//R"		roughness .01
//R"	}
//R"}
//R"
//R"texture{
//R"	pigment{
//R"	color rgbt <1, 1, 1, .9>
//R"}
//R"	normal{
//R"		bumps 3
//R"		scale .1
//R"	}
//R"}
//R"
//R"#declare Snowball =
//R"object{
//R"	sphere{ <0, 0, 0>, 1 }
//R"	texture{ Snow }
//R"}
//R"
//R"#declare Snow2 =
//R"interior{
//R"	media{ method 3
//R"	emission 0.6
//R"	scattering{ 1, // Type
//R"	<1, 1, 1>*3.00 // color of scattering haze
//R"	extinction  1.50
//R"	// how fast the scattering media absorbs light
//R"	// useful if the media absorbs too much light
//R"	} // end scattering
//R"	density{ spherical
//R"		turbulence 0.45
//R"		color_map{
//R"		[0.00 rgb 0]
//R"		[0.05 rgb 0]
//R"		[0.20 rgb 0.2]
//R"		[0.30 rgb 0.6]
//R"		[0.40 rgb 1]
//R"		[1.00 rgb 1]
//R"	} // end color_map
//R"	} // end of density
//R"	samples 2, 2   // 3,3 for adaptive sampling
//R"		intervals 3   // increase up to 15
//R"		confidence .9 // decrease down to .03
//R"		//  for better quality
//R"} // end of media ----------------------------------
//R"}
//R"
//R"#declare Snowball2 =
//R"object{
//R"	sphere{ <0, 0, 0>, 1.5 }
//R"	pigment{ rgbt 1 }
//R"	hollow
//R"		interior{ Snow2 }
//R"}
//R"
//R"#declare Snowbox2 =
//R"object{
//R"	box{ <-.5, -.5, -.5>, <.5, .5, .5> }
//R"	pigment{ rgbt 1 }
//R"	hollow
//R"		interior{ Snow2 }
//R"}
//R"
//R"#declare Snowbox =
//R"object{
//R"	box{ <-.5, -.5, -.5>, <.5, .5, .5> }"
//R"	texture{ Snow }"
//R"}"
//R""
//R"fog{ distance 200 color Black }"
//R""
//R"// How did I figure out those wierd transformations below?"
//R"// Well, they'd be less obscure had I created the wine glass properly,"
//R"// but since I didn't, I simply put the camera a tiny bit above the"
//R"// floorplane and tried various values until it "fit"."
//""
//R"//object { Snowball }"
//R"//object { Snowball2 translate <-2,0,0> }"
//R"object{ Snowbox }"
//R"object{ Snowbox translate <1, 0, 0> }"
//R"object{ Snowbox translate <2, 0, 0> }"
//R"object{ Snowbox translate <-1, 0, 0> }"
//R"object{ Snowbox translate <-2, 0, 0> }"
//;


#endif