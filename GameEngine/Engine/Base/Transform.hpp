#pragma once
#include "Vector.hpp"
#include "Rotator.hpp"

using TempTransformMatrix = XMMATRIX;

const TempVector RIGHT_VECTOR	= XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);	// x
const TempVector UP_VECTOR		= XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);	// y
const TempVector FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	// z


class Transform
{
public:
	Transform() noexcept;
	Transform(Vector location, Rotator rotation, Vector scale) noexcept;
	Transform(const TempTransformMatrix& mat) noexcept;
	Transform(float lx, float ly, float lz, float rx, float ry, float rz, float sx, float sy, float sz) noexcept;
	Transform(const Transform& other) noexcept;
	Transform(Transform&& other) noexcept;

	Transform& operator=(const Transform& other) noexcept;
	Transform& operator=(Transform&& other) noexcept;
	Transform& operator=(const TempTransformMatrix& mat) noexcept;

	bool operator==(const Transform& t) const noexcept;
	bool operator!=(const Transform& t) const noexcept;

	const float* GetArray() const noexcept;
	TempTransformMatrix GetTransformMatrix() const noexcept;

	Vector location;
	Rotator rotation;
	Vector scale;
};