// System.cpp - Zander Clucas 2014
// The main controller

#include "System.h"

System* g_current_system = 0;            // needed for callback in a class
extern "C"
void draw_callback()
{
    g_current_system->draw();
}

void animate_callback()
{
    g_current_system->animate();
}

void resize_callback(int x, int y)
{
	g_current_system->resize(x,y);
}

void keyboard_callback(unsigned char key, int x, int y)
{
    g_current_system->keyboard(key,x,y);
}

System::System()
{
    main_window = 0;
}

System::~System()
{

}

int System::init( int argc, char **argv )
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
    glutInitWindowPosition( 0,0 );
    main_window = glutCreateWindow("MPM Visualization");
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    ratio = (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT;
    
    setup_callbacks();
    

    glEnable( GL_DEPTH_TEST );

    glShadeModel(GL_SMOOTH);

    glClearColor(0.56f, 0.8667f, 1.f, 0.0f);

    sh_sys.recompile("mainvs.v.glsl","mainfs.f.glsl");

    
    int result = init_graphics();

    return result;
}

int System::run()
{
    glutMainLoop();
    return 1;
}

void System::animate()
{
    if(current_step < 0)
    {
        return; //Nothing to draw
    }
    else
    {
        runtime = glutGet(GLUT_ELAPSED_TIME);
        int delta = runtime - prev_runtime;
        step_switch += delta;
        if(step_switch > anim_speed)
        {
			if (!pause)
			{
				next_step();
			}
            step_switch = 0;
        }
        prev_runtime = runtime;
    }

    glutPostRedisplay( );
}

void System::setup_callbacks()
{
    ::g_current_system = this;
    ::glutDisplayFunc(::draw_callback);
    ::glutKeyboardFunc(::keyboard_callback);
    ::glutIdleFunc(::animate_callback);
	::glutReshapeFunc(::resize_callback); // Scale the obect if the window size changes

    /*
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );
    glutMotionFunc( drag_mouse );
    */
}

void System::keyboard(unsigned char key, int x, int y)
{
    switch( key ) {
    case 033: // Escape Key
        // Deselect and leave modes
        exit( EXIT_SUCCESS );
        break;
    case 'r': case 'R':
        //printf("Recompiling shaders...\n");
        //sh_sys.recompile("mainvs.v.glsl","mainfs.f.glsl");
        //glutPostRedisplay();
        break;
    case 'e': // rEset
		globalEyepos = Vec3(0.0, 0.0, 60.0);
        glutPostRedisplay();
        break;
	case 'w':
		globalEyepos.z -= 1.0;
		glutPostRedisplay();
		break;
    case 's':
        globalEyepos.z += 1.0;
        glutPostRedisplay();
        break;
    case 'a':
        globalEyepos.x -= 1.0;
        glutPostRedisplay();
        break;
    case 'd':
        globalEyepos.x += 1.0;
        glutPostRedisplay();
        break;
    case 'c':
        globalEyepos.y -= 1.0;
        glutPostRedisplay();
        break;
    case 'x':
        globalEyepos.y += 1.0;
        glutPostRedisplay();
        break;
    case 'f':
        anim_speed -= 10;
        break;
    case 'g':
        anim_speed += 10;
        break;
	case 't':
		if (rendermode == REAL_RENDER)
		{
			rendermode = STRESSXX_RENDER;

			glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		}
		else
		{
			rendermode = REAL_RENDER;

			glClearColor(0.56f, 0.8667f, 1.f, 0.0f);
		}
		glutPostRedisplay();
		break;
	case '1':
		if (showTire)
		{
			showTire = false;
		}
		else
		{
			showTire = true;
		}
		glutPostRedisplay();
		break;
	case '2':
		if (showSnow)
		{
			showSnow = false;
		}
		else
		{
			showSnow = true;
		}
		glutPostRedisplay();
		break;
	case '3':
		if (showGround)
		{
			showGround = false;
		}
		else
		{
			showGround = true;
		}
		glutPostRedisplay();
		break;
	case '4':
		if (showAxle)
		{
			showAxle = false;
		}
		else
		{
			showAxle = true;
		}
		glutPostRedisplay();
		break;
	case 'p':
		if (pause)
		{
			pause = false;
		}
		else
		{
			pause = true;
		}
		break;
    }
}

//TEMP----
GLuint mmatID;
GLuint vmatID;
GLuint pmatID;
GLuint colorID;
//------




int System::init_graphics()
{
    load_mpm();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLdouble dx = mpm_data.dx/2.;
    GLdouble dy = mpm_data.dy/2.;
    GLdouble dz = mpm_data.dz/2.;
    vertex_pos square[] = {
      //  X      Y     Z     W
        -dx,-dy,-dz, 1.0f, 
        -dx,-dy, dz, 1.0f,
        -dx, dy, dz, 1.0f, 

         dx, dy,-dz, 1.0f, 
        -dx,-dy,-dz, 1.0f,
        -dx, dy,-dz, 1.0f,

         dx,-dy, dz, 1.0f,
        -dx,-dy,-dz, 1.0f,
         dx,-dy,-dz, 1.0f,

         dx, dy,-dz, 1.0f,
         dx,-dy,-dz, 1.0f,  
        -dx,-dy,-dz, 1.0f,

        -dx,-dy,-dz, 1.0f,
        -dx, dy, dz, 1.0f,
        -dx, dy,-dz, 1.0f,

         dx,-dy, dz, 1.0f,
        -dx,-dy, dz, 1.0f,
        -dx,-dy,-dz, 1.0f,

        -dx, dy, dz, 1.0f,
        -dx,-dy, dz, 1.0f,
         dx,-dy, dz, 1.0f,

         dx, dy, dz, 1.0f,
         dx,-dy,-dz, 1.0f,
         dx, dy,-dz, 1.0f,

         dx,-dy,-dz, 1.0f,
         dx, dy, dz, 1.0f,
         dx,-dy, dz, 1.0f,

         dx, dy, dz, 1.0f,
         dx, dy,-dz, 1.0f,
        -dx, dy,-dz, 1.0f, 

         dx, dy, dz, 1.0f,
        -dx, dy,-dz, 1.0f,
        -dx, dy, dz, 1.0f,

         dx, dy, dz, 1.0f,
        -dx, dy, dz, 1.0f,
         dx,-dy, dz, 1.0f,
    };

    GLuint vertex_buffer;

    glGenBuffers(1, &vertex_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square),square, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       4,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    int ssq = sizeof(square)/sizeof(GLfloat);
    vertex_normal square_normals[] = {
      //  X     Y      Z     A
        -1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f,  0.0f,  0.0f, 1.0f,

         0.0f,  0.0f, -1.0f, 1.0f,
         0.0f,  0.0f, -1.0f, 1.0f, 
         0.0f,  0.0f, -1.0f, 1.0f,

         0.0f, -1.0f,  0.0f, 1.0f,
         0.0f, -1.0f,  0.0f, 1.0f,
         0.0f, -1.0f,  0.0f, 1.0f,

         0.0f,  0.0f, -1.0f, 1.0f,
         0.0f,  0.0f, -1.0f, 1.0f,
         0.0f,  0.0f, -1.0f, 1.0f,

        -1.0f,  0.0f,  0.0f, 1.0f,
        -1.0f,  0.0f,  0.0f, 1.0f,       // Color won't be varying, each block
        -1.0f,  0.0f,  0.0f, 1.0f,       // will get a uniform color, stress based

         0.0f, -1.0f,  0.0f, 1.0f,       // change to normals? for phong shading?
         0.0f, -1.0f,  0.0f, 1.0f,
         0.0f, -1.0f,  0.0f, 1.0f,

         0.0f,  0.0f,  1.0f, 1.0f,
         0.0f,  0.0f,  1.0f, 1.0f,
         0.0f,  0.0f,  1.0f, 1.0f,

         1.0f,  0.0f,  0.0f, 1.0f,
         1.0f,  0.0f,  0.0f, 1.0f,
         1.0f,  0.0f,  0.0f, 1.0f,

         1.0f,  0.0f,  0.0f, 1.0f,
         1.0f,  0.0f,  0.0f, 1.0f,
         1.0f,  0.0f,  0.0f, 1.0f, 

         0.0f,  1.0f,  0.0f, 1.0f,
         0.0f,  1.0f,  0.0f, 1.0f,
         0.0f,  1.0f,  0.0f, 1.0f,

         0.0f,  1.0f,  0.0f, 1.0f,
         0.0f,  1.0f,  0.0f, 1.0f,
         0.0f,  1.0f,  0.0f, 1.0f,

         0.0f,  0.0f,  1.0f, 1.0f,
         0.0f,  0.0f,  1.0f, 1.0f,
         0.0f,  0.0f,  1.0f, 1.0f,
    };

    GLuint normal_buffer;

    glGenBuffers(1, &normal_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_normals),square_normals, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(
       1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
       4,                  // size
       GL_FLOAT,           // type
       GL_TRUE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    mmatID = glGetUniformLocation(sh_sys.curr_prog, "Model");
    vmatID = glGetUniformLocation(sh_sys.curr_prog, "View");
    pmatID  = glGetUniformLocation(sh_sys.curr_prog, "Projection");

    colorID = glGetUniformLocation(sh_sys.curr_prog, "Color");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    globalEyepos = Vec3( 0.0, 0.0, 60.0);
    light_pos = Vec3( -10.0, 4.0, 10.0 );

    glUniform3fv( glGetUniformLocation(sh_sys.curr_prog, "LightPosition"),
          1, light_pos );

    if(mpm_data.entries.size() > 0)
    {
        current_step = 0;
    }
    else
    {
        current_step = -1;
    }

	pause = false;
    anim_speed = 100;
    step_switch = 0;
	rendermode = REAL_RENDER;
    prev_runtime = glutGet(GLUT_ELAPSED_TIME);
    
	showTire = true;
	showGround = true;
	showSnow = true;
	showAxle = true;

    return 1;
}


void System::resize(int w, int h)
{
	ratio = (GLfloat)w / (GLfloat)h;
	Mat4 pmat;
	pmat = Perspective(90, ratio, 0.1, 550);

	glViewport(0, 0, w, h);
	glUniformMatrix4fv(pmatID, 1, GL_TRUE, pmat);
	glutPostRedisplay();
}

// glut main loop
void System::draw()
{
    if(current_step < 0)
    {
        return; //Nothing to draw
    }

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

    // set the matrices
    Mat4 vmat,pmat;

    //Set up the model_view matrix with LookAt
    Vec3 globalAt( 0.0, 0.0, 0.0 );
    Vec3 globalUp( 0.0, 1.0, 0.0 );

    vmat = LookAt( globalEyepos, globalAt, globalUp );
    pmat = Perspective(90, ratio, 0.1, 550);
    
    glUniformMatrix4fv(vmatID, 1, GL_TRUE, vmat);
    glUniformMatrix4fv(pmatID, 1, GL_TRUE, pmat);
    
    //Mat4 mmat = Translate(0,0,0);
    //glUniformMatrix4fv(mmatID, 1, GL_TRUE, mmat);
    //// set color for sxx stress
    //glUniform3fv( colorID, 1, Vec3(0.5,0.5,0.1) );
    //    
    //// Draw
    //glDrawArrays(GL_TRIANGLES, 0, 36); // 6 per side, 6 sides
    
	for (int i = 0; i < mpm_data.entries[current_step].model_mats.size(); i++)
	{
		if (!showAxle)
		{
			if (mpm_data.entries[current_step].nodes[i].matnum == AXLE_MAT)
			{
				continue;
			}
		}
		if (!showGround)
		{
			if (mpm_data.entries[current_step].nodes[i].matnum == GROUND_MAT)
			{
				continue;
			}
		}
		if (!showSnow)
		{
			if (mpm_data.entries[current_step].nodes[i].matnum == SNOW_MAT || mpm_data.entries[current_step].nodes[i].matnum == SNOW2_MAT)
			{
				continue;
			}
		}
		if (!showTire)
		{
			if (mpm_data.entries[current_step].nodes[i].matnum == TIRE_MAT)
			{
				continue;
			}
		}

		// Current square in simulation
		glUniformMatrix4fv(mmatID, 1, GL_TRUE, mpm_data.entries[current_step].model_mats[i]);

		// set color for sxx stress
		if (rendermode == REAL_RENDER)
		{
			glUniform3fv(colorID, 1, mpm_data.entries[current_step].node_real_color[i]);
		}
		else
		{
			//if (mpm_data.entries[current_step].node_sxx_color[i].x != mpm_data.entries[current_step].node_sxx_color[i].y)
			//{
			//	glUniform3fv(colorID, 1, Vec3(1., 1., 1.));
			//}
			//else
			//{
				glUniform3fv(colorID, 1, mpm_data.entries[current_step].node_sxx_color[i]);
//			}
		}

        // Draw
        glDrawArrays(GL_TRIANGLES, 0, 36); // 6 per side, 6 sides
    }
    
    // Swap
    glutSwapBuffers();
}

void System::load_mpm()
{
    string line;
    vector<string> sim_files;
    ifstream input ("output_list.txt");
    if (input.is_open())
    {
        while ( getline (input,line) )
        {
			if (line.compare("") != 0)
			{
				sim_files.push_back(line);
			}
        }
        input.close();
    }

	string basepov;
	ifstream povbase("POVout/base.pov");
	if (povbase.is_open())
	{
		while (getline(povbase, line))
		{
			basepov = basepov + line + "\n";
		}
	}

    // hardcoded size, to be read in later
	GLdouble cellsize = 1.0 / 2.;
    mpm_data.dx = cellsize;
    mpm_data.dy = cellsize;
    mpm_data.dz = cellsize;
    
    GLdouble sxx_max = -999999;
    GLdouble sxx_min =  999999;
    for(int i = 0; i < sim_files.size(); i++)
    {
        GLdouble time = 0;
        GLdouble x,y,z,sxx,sxy,syy,syz,szz,sxz;
		int matnum;

        ifstream mpm_entry (sim_files[i].c_str());
        if (mpm_entry.is_open())
        {
			string povout;
            string s1,s2;
            mpm_sim_data_entry mpm_data_entry;

            // Header (hard coded bs)
            getline (mpm_entry,line); // Source
            mpm_entry >> s1 >> time >> s2; // Time
            getline (mpm_entry,line); // (return char)
            getline (mpm_entry,line); // Export
            getline (mpm_entry,line); // Data
            getline (mpm_entry,line); // Format
            getline (mpm_entry,line); // End
            if(!line.compare("EndHeader")==0)
            {
                printf("Output file lacking header, unable to determine time.\n");
                break;
            }
            mpm_data_entry.time = time;
            
			povout = sim_files[i].erase(0, 4); // remove "out."
			povout = povout.substr(0, sim_files[i].find(".")); // remove ".txt"
			povout = "POVout/povfile." + povout + ".pov";
			ofstream output(povout);
			output << basepov;
			// Data
            while (mpm_entry >> x >> y >> z
                             >> sxx >> syy >> szz
                             >> sxy >> syz >> sxz >> matnum)
            {
                mpm_sim_data_node mpm_node;
                mpm_node.x = x;
                mpm_node.y = y;
                mpm_node.z = z;
                mpm_node.sxx = sxx;
                mpm_node.syy = syy;
                mpm_node.szz = szz;
                mpm_node.sxy = sxy;
                mpm_node.syz = syz;
                mpm_node.sxz = sxz;
				mpm_node.matnum = matnum;
                mpm_data_entry.nodes.push_back(mpm_node);
                Mat4 model_mat = Translate(x,y,z);
                mpm_data_entry.model_mats.push_back(model_mat);

                // sxx stress color map
                if(sxx > sxx_max)
                {
                    sxx_max = sxx;
                }
                if(sxx < sxx_min)
                {
                    sxx_min = sxx;
                }
				GLdouble r = sqrtf(x*x + y*y);
				if (r < 16) // skip povray rendering the center to insert the wheel in post
				{
					continue;
				}
				if (matnum == SNOW_MAT || matnum == SNOW2_MAT)
				{
					output << "object { Snowbox translate <" << x << "," << y << "," << z << "> }\n";
				}
				else if (matnum == TIRE_MAT)
				{
					output << "object { Rubberbox translate <" << x << "," << y << "," << z << "> }\n";
				}/*
				else if (matnum == GROUND_MAT)
				{
					output << "object { Groundbox translate <" << x << "," << y << "," << z << "> }\n";
				}*/
            }
			output.close();
            mpm_entry.close();
            mpm_data.entries.push_back(mpm_data_entry);
        }
    }
    for(int i = 0; i < sim_files.size(); i++)
    {
        for(int j = 0; j < mpm_data.entries[i].nodes.size(); j++)
        {
			GLfloat hsv[3], rgb[3];
			if (sxx_min == sxx_max)
			{
				hsv[0] = 0.5f;
			}
			else
			{
				hsv[0] = 240.0f - 240.0f * (mpm_data.entries[i].nodes[j].sxx - sxx_min) / (sxx_max - sxx_min);
			}
            hsv[1] = 1.0f;
            hsv[2] = 1.0f;
            HsvRgb( hsv, rgb );
            Vec3 color(rgb[0],rgb[1],rgb[2]);
			mpm_data.entries[i].node_sxx_color.push_back(color);

			if (mpm_data.entries[i].nodes[j].matnum == TIRE_MAT)
			{
				color = Vec3(0.3, 0.3, 0.3);
			}
			else if (mpm_data.entries[i].nodes[j].matnum == GROUND_MAT)
			{
				color = Vec3(0.58, 0.4, 0.25);
			}
			else if (mpm_data.entries[i].nodes[j].matnum == SNOW_MAT || mpm_data.entries[i].nodes[j].matnum == SNOW2_MAT)
			{
				color = Vec3(0.9, 0.9, 0.9);
			}
			mpm_data.entries[i].node_real_color.push_back(color);
        }
    }
}