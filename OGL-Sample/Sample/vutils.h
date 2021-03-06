#pragma once
#include <string>
#include <stdio.h>
#include <random>
#include <glad\glad.h>

#ifndef Log_Error
#define Log_Error(X) printf("\033[1,31,40m""Error: %s   %s::%s  line:%d  \n\n",X ,__FILE__,__FUNCTION__,__LINE__);
#endif 

#ifndef Log_Warning
#define Log_Warning printf("\033[1,34,40m""Warning: %s    %s::%s  line:%d  \n\n",X ,__FILE__,__FUNCTION__,__LINE__);
#endif 

#ifndef _Assert
	#if defined(DEBUG)||defined(_DEBUG)
		#define _Assert(X)  Log_Error(X); assert(false);
	#else
		#define _Assert(X) Log_Error(X);
	#endif // DEBUG
#endif 

#ifndef Check_GL_Error
#define Check_GL_Error 	{GLenum error= glGetError();\
if (error != GL_NO_ERROR)\
{\
	char info[200];\
	sprintf(info, "GL error type %d ", error);\
	Log_Error(info);}}
#endif

static std::default_random_engine  g_gen;
static std::uniform_int_distribution<> g_random_dis(-100, +100);

float RandomGen();


void vglAttachShaderSource(GLuint prog, GLenum type, const char * source);

std::string vglReadFile(const char* path);

void vglCreateProgramFromFile(GLuint& program, const char* vert_path, const char* frag_path);

float* vglLoadPictureDataFloat(const char* path, int* comp=nullptr, int* width = nullptr, int* height = nullptr);

unsigned char* vglLoadPictureDataByte(const char* path, int* comp = nullptr, int* width = nullptr, int* height = nullptr);