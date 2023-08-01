// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Transform.hpp"

namespace LimeEngine
{
	using namespace DirectX;

	class Transformable
	{
	public:
		Transformable();
		Transformable(const Transform& transform);

		const Vector& GetLocation() const noexcept;
		TempVector GetTempLocationVector() const noexcept;
		void SetLocation(const Vector& loc) noexcept;
		void SetLocation(const TempVector& loc) noexcept;
		void SetLocation(float x, float y, float z) noexcept;
		void AddLocation(const Vector& loc) noexcept;
		void AddLocation(const TempVector& loc) noexcept;
		void AddLocation(float x, float y, float z) noexcept;

		const Rotator& GetRotation() const noexcept;
		TempQuaternion GetQuaternion() const noexcept;
		void SetRotation(const Rotator& rot) noexcept;
		void SetRotation(const TempQuaternion& rot) noexcept;
		void SetRotation(float roll, float pitch, float yaw) noexcept;
		void AddRotation(const Rotator& rot) noexcept;
		void AddRotation(const TempQuaternion& rot) noexcept;
		void AddRotation(float roll, float pitch, float yaw) noexcept;

		const Vector& GetScale() const noexcept;
		TempVector GetTempScaleVector() const noexcept;
		void SetScale(const Vector& scale) noexcept;
		void SetScale(const TempVector& scale) noexcept;
		void SetScale(float x, float y, float z) noexcept;
		void AddScale(const Vector& scale) noexcept;
		void AddScale(const TempVector& scale) noexcept;
		void AddScale(float x, float y, float z) noexcept;

		const Transform& GetTransform() const noexcept;
		void SetTransform(const Transform& transform) noexcept;
		virtual TempTransformMatrix GetWorldTransformMatrix() const noexcept = 0;

		void UpdateTransform() const noexcept;
		const TempTransformMatrix& GetTempTransformMatrix() const noexcept;
		TempTransformMatrix GetRotationMatrix() const noexcept;

		TempVector GetRightVector() const noexcept;
		TempVector GetForwardVector() const noexcept;
		TempVector GetUpVector() const noexcept;

		virtual ~Transformable() noexcept = default;

	private:
		mutable TempTransformMatrix transformMatrix = XMMatrixIdentity();
		Transform transform;

	protected:
		mutable bool isTransformChange = true;
	};
}