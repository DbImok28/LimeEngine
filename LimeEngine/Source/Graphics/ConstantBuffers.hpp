// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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