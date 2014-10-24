// System.h - Zander Clucas 2014
// The main controller
#ifndef SYSTEM_H
#define SYSTEM_H

// Includes
#include <glew.h>
#include <glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "ShaderSystem.h"
#include "Structs.h"

using namespace std;


enum matnums 
{
	BLANK, TIRE_MAT, GROUND_MAT, SNOW_MAT, SNOW2_MAT, AXLE_MAT, METAL_MAT, TIRE2_MAT
};

// Structs
struct mpm_sim_data_node
{
    GLdouble x,y,z;
    GLdouble sxx,syy,szz;
    GLdouble sxy,sxz,syz;
	int matnum;
};

struct mpm_sim_data_entry
{
    GLdouble time;
    vector<mpm_sim_data_node> nodes;
    vector<Mat4> model_mats;
	vector<Vec3> node_sxx_color;
	vector<Vec3> node_real_color;
};

struct mpm_sim_data_collection
{
	GLdouble dx,dy,dz; //cube size
	vector<mpm_sim_data_entry> entries;
};

// Classes
class System
{
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
public:
    // Functions
    System();
    ~System();

    int init( int argc, char **argv );
    int run();
    void animate();
    
    // Callbacks
    void draw();
    void keyboard(unsigned char key, int x, int y);
	void resize(int x, int y);

    // Variables

private:
    // Functions
    int init_graphics();
    void load_mpm();
    
    // Variables
    GLuint main_window;
    float ratio;
    
	bool pause;
    int anim_speed;
    int prev_runtime;
    int runtime;
    int step_switch;
    int current_step;
	bool showTire;
	bool showGround;
	bool showSnow;
	bool showAxle;


	int rendermode;
	enum RenderModes {REAL_RENDER,STRESSXX_RENDER};
    inline void next_step()
    {
        if(mpm_data.entries.size() == 0)
        {
            current_step = -1;
            return;
        }
        current_step++;
        if(current_step >= mpm_data.entries.size())
        {
            current_step = 0;
        }
    }

    mpm_sim_data_collection mpm_data;

    Vec3 globalEyepos;
    Vec3 light_pos;

    ShaderSystem sh_sys;

    // fix
    void setup_callbacks();
};

#endif