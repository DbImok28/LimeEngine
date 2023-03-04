#pragma once
#include "Base/Transform.hpp"

namespace LimeEngine
{
	struct VSTransformConstantBuffer
	{
		TempTransformMatrix wvpMatrix;
		TempTransformMatrix worldMatrix;
	};
}