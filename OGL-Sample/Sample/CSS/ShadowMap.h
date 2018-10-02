#pragma once
#include "../ExemplarBase.h"
class ShadowMap:public ExemplarBase
{
public:
	explicit ShadowMap();
	virtual ~ShadowMap();

	virtual void Init() override;

	virtual void Update(double delta) override;

	virtual void Render(int width, int height) override;

	virtual void Destory() override;

private:

};

