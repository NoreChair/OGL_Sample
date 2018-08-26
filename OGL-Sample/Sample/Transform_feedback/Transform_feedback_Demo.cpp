#include "Transform_feedback_Demo.h"
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
FeedbackDemo::FeedbackDemo() :ExemplarBase()
{
}

FeedbackDemo::~FeedbackDemo()
{

}

void FeedbackDemo::Init()
{
	vglCreateProgramFromFile(_program[PE_Render], "Shader/transform_feedback.vert", "Shader/transform_feedback.frag");
	const char* varying[]{
		"world_space_position","gl_SkipComponents3"	};
	glTransformFeedbackVaryings(_program[PE_Render], 2, varying, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(_program[PE_Render]);

	_program[PE_Transform] = glCreateProgram();
	std::string vert_core = vglReadFile("Shader/update.vert");
	vglAttachShaderSource(_program[PE_Transform], GL_VERTEX_SHADER, vert_core.c_str());
	glLinkProgram(_program[PE_Transform]);
	GLint link_state;
	glGetProgramiv(_program[PE_Transform], GL_LINK_STATUS, &link_state);
	if (!link_state)
	{
		char log[1024];
		glGetProgramInfoLog(_program[PE_Transform], sizeof(log), nullptr, log);
		sprintf(log, "Program link Error %s ", log);
		Log_Error(log);
	}
	const char* varying2[] = {
		"out_position","out_velocity"
	};
	glTransformFeedbackVaryings(_program[PE_Transform], 2, varying2, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(_program[PE_Transform]);


	glGenBuffers(BufferEnumCount, _buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer[BE_VertexArray]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _max_particle_count, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, _buffer[BE_Feedback]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float) * 6 *  _max_particle_count, nullptr, GL_DYNAMIC_COPY);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, _buffer[BE_Transform]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float) * 6 * _max_particle_count, nullptr, GL_DYNAMIC_COPY);

	float* pointer=(float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < _max_particle_count; i++)
	{
		pointer[3 * i] = RandomGen()*200.0f - 100.0f;
		pointer[3 * i + 1] = RandomGen()*200.0f - 100.0f;
		pointer[3 * i + 2] = 0.0;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	pointer = nullptr;

	glBindBuffer(GL_UNIFORM_BUFFER, _buffer[BE_Unifrom]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, nullptr, GL_DYNAMIC_DRAW);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	Check_GL_Error;

}

void FeedbackDemo::Update(double delta)
{
	static int call_count = 0;

	if (call_count)
	{
		glUseProgram(_program[PE_Transform]);
		
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[BE_Transform]);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 6, (void*)(sizeof(float)*3));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_UNIFORM_BUFFER, _buffer[BE_Unifrom]);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _buffer[BE_Unifrom]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _buffer[BE_Feedback]);

		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, _max_particle_count);
		glEndTransformFeedback();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

#if 1
		{
			glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, _buffer[BE_Feedback]);
			float* pointer = (float*)glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);
			glBindBuffer(GL_ARRAY_BUFFER, _buffer[BE_VertexArray]);
			float* pointer1 = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			for (int i = 0; i < _max_particle_count; i++)
			{
				pointer1[i * 3] = pointer[i * 6];
				pointer1[i * 3 + 1] = pointer[i * 6 + 1];
				pointer1[i * 3 + 2] = pointer[i * 6 + 2];
			}
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
		}
#endif

	}

	Check_GL_Error;

	call_count++;
}

void FeedbackDemo::Render(int width, int height)
{
	_last_width = width;
	_last_height = height;
#ifdef HDR_BUFFER
	if (!_frame_buffer_object)
	{
		glGenFramebuffers(1, &_frame_buffer_object);
		glGenRenderbuffers(RenderBufferCount, _render_buffer);
		glGenBuffers(BufferEnumCount, _buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_object);
		glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[RBE_ColorBuffer]);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA16F, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _render_buffer[RBE_ColorBuffer]);
		glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[RBE_DepthBuffer]);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT32, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _render_buffer[RBE_DepthBuffer]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_object);
#endif	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::orthoRH(-width / 2 + 0.0, width / 2 + 0.0, -height / 2 + 0.0, height / 2 + 0.0, -100.0, 100.0);
	glm::mat4 model=glm::mat4(1.0);
	glUseProgram(_program[PE_Render]);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer[BE_VertexArray]);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_UNIFORM_BUFFER, _buffer[BE_Unifrom]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(model));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _buffer[BE_Unifrom]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _buffer[BE_Transform]);

	glPointSize(5.0);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, _max_particle_count);
	glEndTransformFeedback();

	glDisableVertexAttribArray(0);
	
#if 0
	{
		glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, _buffer[BE_Transform]);
		float* pointer=(float*) glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);
		float r = pointer[0];
		glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
		pointer = nullptr;
	}
#endif
	Check_GL_Error;

#ifdef HDR_BUFFER
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _frame_buffer_object);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, _last_width, _last_height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
#endif
	
	
}

void FeedbackDemo::Destory()
{
#ifdef HDR_BUFFER
	glDeleteFramebuffers(1, &_frame_buffer_object);
	glDeleteRenderbuffers(RenderBufferCount, _render_buffer);
#endif 
	glDeleteBuffers(BufferEnumCount, _buffer);
	glDeleteProgram(_program[PE_Transform]);
}

void FeedbackDemo::MouseButtonCallback(int button, int action, int mods)
{
	printf("FeedbackDemo mouse button %d \n",button);
}


