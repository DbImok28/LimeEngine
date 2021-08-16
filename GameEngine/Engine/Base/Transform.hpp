#pragma once
#include "Vector.hpp"

class Transform
{
public:
	XMMATRIX getTransformMatrix();

	Vector location	{ 0.0f, 0.0f, 0.0f };
	Vector rotation	{ 0.0f, 0.0f, 0.0f };
	Vector scale	{ 1.0f, 1.0f, 1.0f };
};