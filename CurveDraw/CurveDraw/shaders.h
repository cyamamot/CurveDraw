#include <iostream>
#include <string>

#ifndef __INCLUDESHADERS 
#define __INCLUDESHADERS 

//reads in filename and open file
std::string ReadTextFile (const char * filename);
//Log program errors
void LogProgramError (const GLint program);
//Log shader errors
void LogShaderError (const GLint shader);
//initiates vertex or fragment shader
GLuint InitializeShaders (GLenum type, const char * filename);
//initiates a program with shaders
GLuint InitializeProgram (GLuint vertexshader, GLuint fragmentshader);

#endif 
