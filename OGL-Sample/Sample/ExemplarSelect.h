#pragma once
#include "ExemplarBase.h"
enum ExemplarEnum
{
	Transform_Feedback=1,
	Cascaded_Shadow_Maps,
	ExemplarEnumCount
};

ExemplarBase* CreateExemplar(ExemplarEnum scene);