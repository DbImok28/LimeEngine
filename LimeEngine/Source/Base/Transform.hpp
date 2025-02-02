// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Vector.hpp"
#include "Rotator.hpp"
#include "Matrix.hpp"

namespace LimeEngine
{
	class Transform
	{
	public:
		Transform() noexcept;
		explicit Transform(const TempTransformMatrix& mat) noexcept;
		Transform(const Vector& location, const Rotator& rotation, const Vector& scale) noexcept;
		Transform(float lx, float ly, float lz) noexcept;
		Transform(float lx, float ly, float lz, float rx, float ry, float rz) noexcept;
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

		std::string ToString() const noexcept;

		Vector location;
		Rotator rotation;
		Vector scale;
	};

	std::ostream& operator<<(std::ostream& os, const Transform& transform);
}

template <>
struct std::formatter<LimeEngine::Transform> : std::formatter<std::string>
{
	auto format(LimeEngine::Transform transform, auto& ctx) const
	{
		return std::format_to(ctx.out(), "Location {}\nRotation {}\nScale    {}", transform.location, transform.rotation, transform.scale);
	}
};
