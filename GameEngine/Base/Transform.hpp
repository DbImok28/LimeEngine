#pragma once
#include "Vector.hpp"

class Transform
{
public:
	XMMATRIX getTransformMatrix();
private:
	Vector location;
	Vector rotation;
	Vector scale;
};