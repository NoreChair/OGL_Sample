#pragma once
#include "../ExemplarBase.h"
class FeedbackDemo:public ExemplarBase
{
	enum BufferEnum
	{
		VertexArray,
		TransformFeedback,
		BufferEnumCount
	};
	enum RenderBufferEnum
	{
		ColorBuffer,
		DepthBuffer,
		RenderBufferCount
	};
	enum ProgramEnum
	{
		RenderProgram,
		TransformProgram,
		ProgramEnumCount
	};
public:
	explicit FeedbackDemo();
	
	virtual ~FeedbackDemo();

	virtual void Init() override;

	virtual void Update(double delta) override;

	virtual void Render(int width, int height) override;

	virtual void Destory() override;

	virtual void MouseButtonCallback(int button, int action, int mods) override;

private:
	GLuint _buffer[BufferEnumCount] ;
	
	GLuint _render_buffer[RenderBufferCount];

	GLuint _frame_buffer_object = 0;

	GLuint _program[ProgramEnumCount];

	int _max_particle_count = 1000;

	int _last_width = 0;

	int _last_height = 0;
};

