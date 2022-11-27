#pragma once
#include "Vector.hpp"

namespace LimeEngine
{
	struct Vertex
	{
		Vertex() : pos(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), texCoord(0.0f, 0.0f) {}
		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) : pos(x, y, z), normal(nx, ny, nz), texCoord(u, v) {}
		Vertex(const Vector& pos, const Vector& normal, const DirectX::XMFLOAT2& texCoord) : pos(pos), normal(normal), texCoord(texCoord) {}
		Vector pos;
		Vector normal;
		DirectX::XMFLOAT2 texCoord;
	};
}