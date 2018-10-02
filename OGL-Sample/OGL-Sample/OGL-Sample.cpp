#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>

#include "ExemplarSelect.h"

std::function<void(int, int, int, int)>  _sample_key_callback ;
std::function<void(double x, double y)> _sample_curosr_position_callback ;
std::function<void(int)> _sample_cursor_enter_callback ;
std::function<void(int, int, int)> _sample_mouse_button_callback ;


static void error_callback(int error, const char* description)
{
	//fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (_sample_key_callback)
	{
		_sample_key_callback(key, scancode, action, mods);
	}
}

static void cursor_position_callback(GLFWwindow* window, double x, double y) {
	//printf("Cursor position %.3f ,%.3f \n", x, y);

	if (_sample_curosr_position_callback)
	{
		_sample_curosr_position_callback(x, y);
	}
}

static void cursor_enter_callback(GLFWwindow* window, int entered)
{
	//printf("Cursor Enter Callback %d \n", entered);
	if (_sample_cursor_enter_callback)
	{
		_sample_cursor_enter_callback(entered);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//printf("Mouse button button %d, mods %d ,action name %d \n", button, mods, action);
	if (_sample_mouse_button_callback)
	{
		_sample_mouse_button_callback(button, action, mods);
	}
}

int _screen_width = 1080;
int _screen_height = 720;
int main()
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(_screen_width, _screen_height, "OGL-Sample", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	
	const unsigned char* gl_version = glGetString(GL_VERSION);
	printf("GL Version %s \n", gl_version);

	ExemplarBase*  cur_demo = CreateExemplar(ExemplarEnum::Transform_Feedback);
	if (!cur_demo)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	_sample_mouse_button_callback = std::bind(&(ExemplarBase::MouseButtonCallback), cur_demo, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	_sample_key_callback = std::bind(&(ExemplarBase::KeyCallback), cur_demo, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	_sample_cursor_enter_callback = std::bind(&(ExemplarBase::CursorEnterCallback), cur_demo, std::placeholders::_1);
	_sample_curosr_position_callback = std::bind(&(ExemplarBase::CursorPositionCallback), cur_demo, std::placeholders::_1, std::placeholders::_2);

	cur_demo->Init();

	while (!glfwWindowShouldClose(window))
	{
		cur_demo->Update(1.0 / 60.0);
		cur_demo->Render(_screen_width, _screen_height);

		glfwSwapBuffers(window);
		glfwPollEvents();
		//glfwWaitEvents();
		//fflush(stdout);
	}
	
	cur_demo->Destory();
	delete(cur_demo);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

