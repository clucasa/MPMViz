// ShaderSystem.h - Zander Clucas 2014
// Manages shaders

// Includes
#include "ShaderSystem.h"

ShaderSystem::ShaderSystem()
{
    curr_vert = 0;
    curr_frag = 0;
    curr_prog = 0;
}

ShaderSystem::~ShaderSystem()
{
    curr_vert = 0;
    curr_frag = 0;
    glDeleteProgram(curr_prog);
    curr_prog = 0;
}

void ShaderSystem::recompile(const GLchar *vert_src, const GLchar *frag_src)
{
    GLuint temp_vert = 0;
    GLuint temp_frag = 0;

    temp_vert = compile_vert(vert_src);
    temp_frag = compile_frag(frag_src);

    if(temp_vert != 0 && temp_frag != 0)
    {
        link_shaders(temp_vert, temp_frag);
    }
}

GLuint ShaderSystem::compile_vert(const GLchar *vert)
{
    GLuint temp_vert = 0;
    GLint result = 0;
    string source = read_shader_source( vert );
    if ( source.size() == 0 ) 
    {
        std::cerr << "Failed to read " << vert << std::endl;
        exit( EXIT_FAILURE );
    }

    temp_vert = glCreateShader(GL_VERTEX_SHADER);
    char const * src_ptr = source.c_str();
    glShaderSource(temp_vert, 1, &src_ptr, NULL);

    glCompileShader(temp_vert);
    glGetShaderiv(temp_vert, GL_COMPILE_STATUS, &result);

    if(!result)
    {
        printf("Vertex shader not compiled correctly!\n");
        char log[512];
        GLsizei len;
        glGetShaderInfoLog(temp_vert,512,&len,log);
        printf(log);
        printf("\n");
        //return 0;
    }

    return temp_vert;
}

GLuint ShaderSystem::compile_frag(const GLchar *frag)
{
    GLuint temp_frag = 0;
    GLint result = 0;
    string source = read_shader_source( frag );
    if ( source.size() == 0 ) 
    {
        std::cerr << "Failed to read " << frag << std::endl;
        exit( EXIT_FAILURE );
    }

    temp_frag = glCreateShader(GL_FRAGMENT_SHADER);
    char const * src_ptr = source.c_str();
    glShaderSource(temp_frag, 1, &src_ptr, NULL);
    
    glCompileShader(temp_frag);
    glGetShaderiv(temp_frag, GL_COMPILE_STATUS, &result);

    if(!result)
    {
        printf("Fragment shader not compiled correctly!\n");
        //return 0;
    }

    return temp_frag;
}

void ShaderSystem::link_shaders(GLuint temp_vert, GLuint temp_frag)
{
    GLuint temp_prog = 0;
    GLint result = 0;
        
    temp_prog = glCreateProgram();
    
    glAttachShader(temp_prog, temp_vert);
    glAttachShader(temp_prog, temp_frag);

    glLinkProgram(temp_prog);
    glGetProgramiv(temp_prog, GL_LINK_STATUS, &result);

    if(!result)
    {
        printf("Program was not linked correctly!\n");
        //return;
    }

    glDeleteProgram(curr_prog);
    curr_prog = temp_prog;
    glUseProgram(curr_prog);
}

// Create a NULL-terminated string by reading the provided file
string ShaderSystem::read_shader_source(const char* shader_file)
{
    string buff;
    ifstream shader_stream;
    
    shader_stream.open(shader_file);
    if(shader_stream.is_open())
    {
        string line = "";
        while(std::getline(shader_stream, line))
        {
            buff += "\n" + line;
        }
        shader_stream.close();
    }
    
    return buff;
}