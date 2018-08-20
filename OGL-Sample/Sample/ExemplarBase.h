#pragma once
class ExemplarBase
{
public:
	explicit ExemplarBase()=default;
	virtual ~ExemplarBase()=default;

	ExemplarBase(const ExemplarBase&) = delete;
	ExemplarBase& operator= (const ExemplarBase&) = delete;

	virtual void Init() = 0;

	virtual void Update(double delta) = 0;

	virtual void Render(int width, int height)= 0;

	virtual void KeyCallback(int key, int scancode, int action, int mods);
	
	virtual void CursorPositionCallback(double x, double y);

	virtual void CursorEnterCallback(int entered);

	virtual void MouseButtonCallback(int button, int action, int mods);



};

