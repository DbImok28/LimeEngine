#pragma once
#include "Vector.hpp"

class Transform
{
public:
	XMMATRIX getTransformMatrix();

	Vector location;
	Vector rotation;
	Vector scale;
};