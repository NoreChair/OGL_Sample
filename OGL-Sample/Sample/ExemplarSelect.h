#pragma once
#include "ExemplarBase.h"
enum ExemplarEnum
{
	TransformFeedback=1,
	ExemplarEnumCount
};

ExemplarBase* CreateExemplar(ExemplarEnum scene);