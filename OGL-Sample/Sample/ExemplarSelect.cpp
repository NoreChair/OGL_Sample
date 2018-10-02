#include "ExemplarSelect.h"
#include "Transform_feedback\Transform_feedback_Demo.h"
#include "CSS\ShadowMap.h"
ExemplarBase * CreateExemplar(ExemplarEnum scene)
{
	ExemplarBase* demo = nullptr;
	switch (scene)
	{
	case Transform_Feedback:
		demo = new FeedbackDemo();
		break;
	case Cascaded_Shadow_Maps:
		demo =new ShadowMap();
	default:
		break;
	}
	return demo;
}
