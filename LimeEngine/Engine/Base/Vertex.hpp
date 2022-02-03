#pragma once
#include <DirectXMath.h>

namespace LimeEngine
{
	struct Vertex
	{
		Vertex() : pos(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), texCoord(0.0f, 0.0f) {}
		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) : pos(x, y, z), normal(nx, ny, nz), texCoord(u, v) {}
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texCoord;
	};
}