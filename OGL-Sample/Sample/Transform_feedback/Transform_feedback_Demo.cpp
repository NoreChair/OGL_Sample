#include "Transform_feedback_Demo.h"
#include <stdio.h>
#include <glm/glm.hpp>
FeedbackDemo::FeedbackDemo() :ExemplarBase()
{
}

FeedbackDemo::~FeedbackDemo()
{

}

void FeedbackDemo::Init()
{
	vglCreateProgramFromFile(_program[RenderProgram], "Shader/transform_feedback.vert", "Shader/transform_feedback.frag");
	const char* varying[]{
		"world_space_position",
		"world_space_normal"
	};
	glTransformFeedbackVaryings(_program[TransformProgram], 2, varying, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(_program[TransformProgram]);




}

void FeedbackDemo::Update(double delta)
{

}

void FeedbackDemo::Render(int width, int height)
{
	if (!_frame_buffer_object)
	{
		glGenFramebuffers(1, &_frame_buffer_object);
		glGenRenderbuffers(RenderBufferCount, _render_buffer);
		glGenBuffers(BufferEnumCount, _buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_object);
		glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[ColorBuffer]);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA16F, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _render_buffer[ColorBuffer]);
		glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[DepthBuffer]);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT32, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _render_buffer[DepthBuffer]);
		glClearColor(1.0, 0.0, 0.0, 1.0);
		_last_width = width;
		_last_height = height;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_object);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _frame_buffer_object);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, _last_width, _last_height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	
}

void FeedbackDemo::Destory()
{
	glDeleteFramebuffers(1, &_frame_buffer_object);
	glDeleteRenderbuffers(RenderBufferCount, _render_buffer);
	glDeleteBuffers(BufferEnumCount, _buffer);
	glDeleteProgram(_program[TransformProgram]);
}

void FeedbackDemo::MouseButtonCallback(int button, int action, int mods)
{
	printf("FeedbackDemo mouse button %d \n",button);
}


