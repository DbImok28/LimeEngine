#include "lepch.hpp"
#include "Transform.hpp"

namespace LimeEngine
{
	Transform::Transform() noexcept : location(), rotation(), scale(1.0f, 1.0f, 1.0f) {}

	Transform::Transform(Vector location, Rotator rotation, Vector scale) noexcept : location(location), rotation(rotation), scale(scale) {}

	Transform::Transform(const TempTransformMatrix& mat) noexcept
	{
		XMVECTOR loc, rot, sc;
		XMMatrixDecompose(&sc, &rot, &loc, mat);
		location = loc;
		rotation.SetQuaternion(rot);
		scale = sc;
	}

	Transform::Transform(float lx, float ly, float lz) noexcept : location(lx, ly, lz), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {}

	Transform::Transform(float lx, float ly, float lz, float rx, float ry, float rz) noexcept : location(lx, ly, lz), rotation(rx, ry, rz), scale(1.0f, 1.0f, 1.0f) {}

	Transform::Transform(float lx, float ly, float lz, float rx, float ry, float rz, float sx, float sy, float sz) noexcept :
		location(lx, ly, lz), rotation(rx, ry, rz), scale(sx, sy, sz)
	{}

	Transform::Transform(const Transform& other) noexcept : location(other.location), rotation(other.rotation), scale(other.scale) {}

	Transform::Transform(Transform&& other) noexcept : location(std::move(other.location)), rotation(std::move(other.rotation)), scale(std::move(other.scale)) {}

	Transform& Transform::operator=(const Transform& other) noexcept
	{
		if (this != &other)
		{
			location = other.location;
			rotation = other.rotation;
			scale = other.scale;
		}
		return *this;
	}

	Transform& Transform::operator=(Transform&& other) noexcept
	{
		if (this != &other)
		{
			location = std::move(other.location);
			rotation = std::move(other.rotation);
			scale = std::move(other.scale);
		}
		return *this;
	}

	Transform& Transform::operator=(const TempTransformMatrix& mat) noexcept
	{
		XMVECTOR loc, rot, sc;
		XMMatrixDecompose(&sc, &rot, &loc, mat);
		location = loc;
		rotation.SetQuaternion(rot);
		scale = sc;

		return *this;
	}

	bool Transform::operator==(const Transform& t) const noexcept
	{
		return location == t.location && rotation == t.rotation && scale == t.scale;
	}

	bool Transform::operator!=(const Transform& t) const noexcept
	{
		return !(*this == t);
	}

	const float* Transform::GetArray() const noexcept
	{
		return &location.x;
	}

	TempTransformMatrix Transform::GetTransformMatrix() const noexcept
	{
		return XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationQuaternion(rotation.GetQuaternion()) * XMMatrixTranslation(location.x, location.y, location.z);
	}
}