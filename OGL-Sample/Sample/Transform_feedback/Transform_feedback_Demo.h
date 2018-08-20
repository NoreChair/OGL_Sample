#pragma once
#include "../ExemplarBase.h"
class FeedbackDemo:public ExemplarBase
{
public:
	explicit FeedbackDemo();
	
	virtual ~FeedbackDemo();

	virtual void Init() override;

	virtual void Update(double delta) override;

	virtual void Render(int width, int height) override;

private:

};

