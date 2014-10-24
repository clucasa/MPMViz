// This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/ or send a
// letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.

// Persistence Of Vision raytracer sample file.
// File by Alexander Clucas
// Snowball
// Updated October, 1996
// Updated January, 1998  DCB
//
// -w320 -h240
// -w800 -h600 +a0.3

#version 3.7;
global_settings { assumed_gamma 1.0  max_trace_level 10 } 

global_settings {
  assumed_gamma 1.0
  number_of_waves 3
  max_trace_level 5
  }

#include "colors.inc"
#include "shapes.inc"
#include "textures.inc"

camera {
   location <54.0, 0.0, 61.0>
   angle 90 //  direction z
   up y
   right x*image_width/image_height
   look_at <0.0, 0.0, 0.0>
}

light_source { <20.0, 250.0, 70.0> colour White }
light_source { <-35.0, 230.0, -150.0> colour White }
light_source { 	<0, 120, -50> 
				color rgb <1,1,1> 
				area_light 200, 200, 10, 10
				jitter
			}

#declare Snow =
  texture{ 
    pigment{
      color rgb <0.95, 0.95, 1>
    }
    normal{
      granite
      slope_map {
	[0 <.1, .1>]
	[0.25 <.25, 0>] 
	[0.5 <.1, -.1>] 
	[0.75 <.25, 0>] 
	[1 <.1, .1>] 
      }
      turbulence 0.5
      scale 3
    }
    finish{
      brilliance 0.75
      phong 0.1
      phong_size 5
      subsurface {translucency <0.1, 0.31, 0.48>}
      //emission .2
      //use with  radiosity instead
    }
  }
 
  texture{
    pigment{
      color rgbt <1, 1, 1, .9>
    }
    normal{
      bumps 5
      scale .05  
    }
    finish{
      specular 1
      roughness .01
    }
  }
 
   texture{
    pigment{
      color rgbt <1, 1, 1, .9>
    }
    normal{
      bumps 3
      scale .1
    }
   }
   
#declare Snowbox = 
   object {
      sphere { <0, 0, 0>, 0.5 }
      texture { Snow }
   }
   
#declare Asphalt = texture{
        pigment{ color rgb<1,1,1>*0.2}
        normal { bumps 0.5 scale 0.005}
        finish { diffuse 0.9 phong 0.1}
}

#declare Groundbox =
	object {
	  box { <-0.5,-0.5,-0.5>,<0.5,0.5,0.5>
		  texture { Asphalt }
	  }
	}

#declare Rubber =
  texture{
    pigment{
      aoi
      color_map{
	[0.00 rgb <.075, .175, .025>]
	[0.55 rgb <.20, .22, .24>]
	[0.65 rgb <.04, .04, .04>]
	[0.85 rgb <.06, .02, .01>]
	[1.00 rgb <.07, .04, .01>]
    } 
    poly_wave 1.25
    scale 0.1
    }
    normal {bumps 0.5 scale 0.005}
    finish{
      specular .015
      roughness .075
      brilliance 0.275
    }
  }
  
#declare Rubberbox =
	object {
      sphere { <0, 0, 0>, 0.5 }
      texture { Rubber }
    }
	

fog { 
distance 800 color rgb <0.39, 0.51, 0.61> 
}

background { color rgb <0.39, 0.51, 0.61> }

/* Ground plane */
plane {
   y, -23
   texture {
      Snow
      //pigment { rgb <0.38, 0.32, 0.20> }
   }
}

#declare Tire_tex  =   // tires - Reifen - pneu - gomma - neumático
 texture{ pigment{ color rgb<1,1,1>*0.05}
          finish { phong 0.1 } }
#declare Rim_tex =     // rim - Felge - jante - cerchione - llanta
 texture{ Polished_Chrome        
          finish { phong 1.0 }}                        
#declare Spoke_tex =    // spokes - Speiche - rayon - raggio - rayo
 texture{ Chrome_Metal        
          finish { phong 1.0 }}                        
#declare Hub_tex =      // hub - Nabe - moyeu - mozzo - cubo
 texture{ Polished_Chrome        
          finish { phong 1.0 }}    
		
#declare Number_of_spokes = 36;

//-------------------------------------------------- wheel, Rad,
union{ // (a)
 torus{0.85,0.10 rotate<90,0,0> scale <1,1,3>
         texture{Rim_tex}} // rim
 //torus{1.0,0.25 scale <1,1,1> rotate<90,0,0>
 //        texture{Tire_tex}} // tire

 cylinder {<0,0,-0.13>,<0,0, 0.13>,0.18
         texture{Hub_tex}} // hub
 cylinder {<0,0,-0.15>,<0,0, 0.15>,0.15
         texture{Hub_tex}} // hub
 sphere{<0,0,0>,0.13 scale<1,1,0.3> translate <0,0,-0.15>
         texture{Hub_tex}} // hub
 cylinder {<0,0,-0.005>,<0,0, 0.005>,0.22 translate<0,0,-0.085>
         texture{Hub_tex}} // hub
 cylinder {<0,0,-0.005>,<0,0, 0.005>,0.22 translate<0,0, 0.085>
         texture{Hub_tex}} // hub

//------------------- without #while loop: -----------<<1
 union{ // (b)
  #local Nr = 0;                    // start
  #local EndNr = Number_of_spokes; // end
  #while (Nr< EndNr) 
  union{
   cylinder{ <0,0,-0.07>,<1,0,-0.12>,0.0125} 
   cylinder{ <0.72,0,-0.11>,<0.90,0,-0.12>,0.0175} 
   cylinder{ <0,0,-0.07>,<1,0,-0.12>,0.0125 scale<1,1,-1> rotate<0,0,0.5 *360/EndNr>} 
   cylinder{ <0.72,0,-0.11>,<0.90,0,-0.12>,0.0175  scale<1,1,-1> rotate<0,0,0.5 *360/EndNr>} 
   
             texture{Spoke_tex} 
             rotate<0,0,Nr * 360/EndNr>} 



  #local Nr = Nr + 1;    // next Nr
  #end // ---------------  end of loop 
 } // end of union (b) 
//----------------------------------------------------<<2
scale 17.5
translate<0,0,0> 
rotate<0, 0, 0>
} // end of union (a)
