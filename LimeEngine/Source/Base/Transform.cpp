#include "lepch.hpp"
#include "Transform.hpp"

namespace LimeEngine
{
	Transform::Transform() noexcept : location(), rotation(), scale(1.0f, 1.0f, 1.0f) {}

	Transform::Transform(const Vector& location, const Rotator& rotation, const Vector& scale) noexcept : location(location), rotation(rotation), scale(scale) {}

	Transform::Transform(const TempTransformMatrix& mat) noexcept
	{
		Matrix::DecomposeTransform(location, rotation, scale, mat);
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
		Matrix::DecomposeTransform(location, rotation, scale, mat);
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
		return Matrix::CreateTransformMatrix(location, rotation, scale);
	}

	std::string Transform::ToString() const noexcept
	{
		return std::format("{}", *this);
	}

	std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		os << transform.ToString();
		return os;
	}
}
