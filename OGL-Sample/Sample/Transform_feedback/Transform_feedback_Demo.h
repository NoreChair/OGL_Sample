#pragma once
#include "../ExemplarBase.h"


class FeedbackDemo:public ExemplarBase
{
	enum BufferEnum
	{
		BE_VertexArray,
		BE_Transform,
		BE_Feedback,
		BE_Unifrom,
		BufferEnumCount
	};
	enum RenderBufferEnum
	{
		RBE_ColorBuffer,
		RBE_DepthBuffer,
		RenderBufferCount
	};
	enum ProgramEnum
	{
		PE_Render,
		PE_Transform,
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

#ifdef HDR_BUFFER
	GLuint _render_buffer[RenderBufferCount];

	GLuint _frame_buffer_object = 0;
#endif 
	GLuint _program[ProgramEnumCount];

	int _max_particle_count = 100;

	int _last_width = 0;

	int _last_height = 0;
};

