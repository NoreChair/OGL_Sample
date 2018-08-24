#include "vutils.h"
#include <stb/stb_image.h>
#include <fstream>
void vglAttachShaderSource(GLuint prog, GLenum type, const char * source)
{
	GLuint sh;
	sh = glCreateShader(type);
	glShaderSource(sh, 1, &source, NULL);
	glCompileShader(sh);
	GLint compile_state;
	glGetShaderiv(sh, GL_COMPILE_STATUS, &compile_state);
	if (!compile_state)
	{
		char buffer[1024];
		char error_info[1024];
		glGetShaderInfoLog(sh, sizeof(buffer), nullptr, buffer);
		Log_Error(buffer);
		std::string shader_type;
		switch (type)
		{
		case GL_VERTEX_SHADER:
			shader_type = "Vertex Shader";
			break;
		case GL_FRAGMENT_SHADER:
			shader_type = "Fragment Shader";
			break;
		}
		sprintf(error_info, "Load shader error with shader type %s", shader_type.c_str());
		Log_Error(error_info);
		
	}
	glAttachShader(prog, sh);
	glDeleteShader(sh);
}

std::string vglReadFile(const char * path)
{
	std::fstream read_stream;
	read_stream.open(path, std::ios::in);
	std::string core;
	if (read_stream.is_open())
	{
		read_stream.seekg(0, std::ios::end);
		std::streampos n = read_stream.tellg();
		char* s = new char[(unsigned int)n];
		memset(s, 0, (unsigned int)n);
		read_stream.seekg(0, std::ios::beg);
		read_stream.read(s, n);
		core = std::string(s);
		read_stream.close();

		delete[]s;
	}
	else {
		char log[200];
		sprintf(log, "Read file fale %s", path);
		Log_Error(log);
	}
	return core;
}

void vglCreateProgramFromFile(GLuint & program, const char * vert_path, const char * frag_path)
{

	std::string vert_core = vglReadFile(vert_path);
	std::string frag_core = vglReadFile(frag_path);
	
	GLuint prog = glCreateProgram();
	vglAttachShaderSource(prog, GL_VERTEX_SHADER, vert_core.c_str());
	vglAttachShaderSource(prog, GL_FRAGMENT_SHADER, frag_core.c_str());
	glLinkProgram(prog);
	GLint link_state;
	glGetProgramiv(prog, GL_LINK_STATUS, &link_state);
	if (!link_state)
	{
		char log[1024];
		glGetProgramInfoLog(prog, sizeof(log), nullptr, log);
		sprintf(log, "Program link Error %s ",log);
		Log_Error(log);
		glDeleteProgram(prog);
		program = 0;
		return;
	}
	program = prog;
}

float * vglLoadPictureDataFloat(const char * path, int * comp, int * width, int * height)
{
	float* pciture_data = nullptr;
	pciture_data=stbi_loadf(path, width, height, comp, 0);
	return pciture_data;
}

unsigned char * vglLoadPictureDataByte(const char * path, int * comp, int * width, int * height)
{
	unsigned char* pciture_data = nullptr;
	pciture_data = stbi_load(path, width, height, comp, 0);
	return pciture_data;
}
