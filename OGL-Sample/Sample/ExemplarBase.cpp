#include "ExemplarBase.h"
#include <stdio.h>

void ExemplarBase::KeyCallback(int key, int scancode, int action, int mods)
{
}

void ExemplarBase::CursorPositionCallback(double x, double y)
{
}

void ExemplarBase::CursorEnterCallback(int entered)
{
}

void ExemplarBase::MouseButtonCallback(int button, int action, int mods)
{
	printf("ExemplarBase mouse button %d \n", button);
}
