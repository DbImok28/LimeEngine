#pragma once
// TODO: Remove
#include <DirectXMath.h>

namespace LimeEngine
{
	struct VSTransformConstantBuffer
	{
		DirectX::XMMATRIX wvpMatrix;
		DirectX::XMMATRIX worldMatrix;
	};
}