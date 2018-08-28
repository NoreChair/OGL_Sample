#include "ExemplarSelect.h"
#include "Transform_feedback\Transform_feedback_Demo.h"
ExemplarBase * CreateExemplar(ExemplarEnum scene)
{
	ExemplarBase* demo = nullptr;
	switch (scene)
	{
	case TransformFeedback:
		demo = new FeedbackDemo();
		break;
	default:
		break;
	}
	return demo;
}
