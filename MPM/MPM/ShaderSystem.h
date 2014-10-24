// ShaderSystem.h - Zander Clucas 2014
// Manages shaders
#ifndef SHADERSYSTEM_H
#define SHADERSYSTEM_H

// Includes
#include <glew.h>
#include <glut.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Classes
class ShaderSystem
{
public:
    // Functions
    ShaderSystem();
    ~ShaderSystem();

    void recompile(const GLchar *vert_src, const GLchar *frag_src);

    GLuint curr_vert;
    GLuint curr_frag;
    GLuint curr_prog;

private:
    GLuint compile_vert(const char *vert);
    GLuint compile_frag(const char *frag);
    void link_shaders(GLuint temp_vert, GLuint temp_frag);
    string read_shader_source(const char* shader_file);
};
#endif