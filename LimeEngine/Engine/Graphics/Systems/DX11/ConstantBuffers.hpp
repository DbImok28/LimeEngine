#pragma once
#include "Buffers.hpp"
#include <DirectXMath.h>

namespace LimeEngine
{
	struct VSTransformConstantBuffer
	{
		DirectX::XMMATRIX wvpMatrix;
		DirectX::XMMATRIX worldMatrix;
	};
}