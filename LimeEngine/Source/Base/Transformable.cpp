// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Transformable.hpp"

namespace LimeEngine
{
	Transformable::Transformable() : transform() {}
	Transformable::Transformable(const Transform& transform) : transform(transform) {}
	const Vector& Transformable::GetLocation() const noexcept
	{
		return transform.location;
	}

	TempVector Transformable::GetTempLocationVector() const noexcept
	{
		return transform.location.GetTempVector();
	}

	void Transformable::SetLocation(const Vector& loc) noexcept
	{
		transform.location = loc;
		isTransformChange = true;
	}

	void Transformable::SetLocation(const TempVector& loc) noexcept
	{
		transform.location = loc;
		isTransformChange = true;
	}

	void Transformable::SetLocation(float x, float y, float z) noexcept
	{
		transform.location = { x, y, z };
		isTransformChange = true;
	}

	void Transformable::AddLocation(const Vector& loc) noexcept
	{
		transform.location.Add(loc);
		isTransformChange = true;
	}

	void Transformable::AddLocation(const TempVector& loc) noexcept
	{
		transform.location.Add(loc);
		isTransformChange = true;
	}

	void Transformable::AddLocation(float x, float y, float z) noexcept
	{
		transform.location.Add(Vector{ x, y, z });
		isTransformChange = true;
	}

	const Rotator& Transformable::GetRotation() const noexcept
	{
		return transform.rotation;
	}

	TempQuaternion Transformable::GetQuaternion() const noexcept
	{
		return transform.rotation.GetQuaternion();
	}

	void Transformable::SetRotation(const Rotator& rot) noexcept
	{
		transform.rotation = rot;
		isTransformChange = true;
	}

	void Transformable::SetRotation(const TempQuaternion& rot) noexcept
	{
		transform.rotation.SetQuaternion(rot);
		isTransformChange = true;
	}

	void Transformable::SetRotation(float roll, float pitch, float yaw) noexcept
	{
		transform.rotation = { roll, pitch, yaw };
		isTransformChange = true;
	}

	void Transformable::AddRotation(const Rotator& rot) noexcept
	{
		transform.rotation.Combine(rot);
		isTransformChange = true;
	}

	void Transformable::AddRotation(const TempQuaternion& rot) noexcept
	{
		transform.rotation.Combine(Rotator::MakeRotator(rot));
		isTransformChange = true;
	}

	void Transformable::AddRotation(float roll, float pitch, float yaw) noexcept
	{
		transform.rotation.Combine(Rotator{ roll, pitch, yaw });
		isTransformChange = true;
	}

	const Vector& Transformable::GetScale() const noexcept
	{
		return transform.scale;
	}

	TempVector Transformable::GetTempScaleVector() const noexcept
	{
		return transform.scale.GetTempVector();
	}

	void Transformable::SetScale(const Vector& scale) noexcept
	{
		transform.scale = scale;
		isTransformChange = true;
	}

	void Transformable::SetScale(const TempVector& scale) noexcept
	{
		transform.scale = scale;
		isTransformChange = true;
	}

	void Transformable::SetScale(float x, float y, float z) noexcept
	{
		transform.scale = { x, y, z };
		isTransformChange = true;
	}

	void Transformable::AddScale(const Vector& scale) noexcept
	{
		transform.scale.Add(scale);
		isTransformChange = true;
	}

	void Transformable::AddScale(const TempVector& scale) noexcept
	{
		transform.scale.Add(scale);
		isTransformChange = true;
	}

	void Transformable::AddScale(float x, float y, float z) noexcept
	{
		transform.scale.Add(Vector{ x, y, z });
		isTransformChange = true;
	}

	const Transform& Transformable::GetTransform() const noexcept
	{
		return transform;
	}

	void Transformable::SetTransform(const Transform& transform) noexcept
	{
		this->transform = transform;
		isTransformChange = true;
	}

	const TempTransformMatrix& Transformable::GetTempTransformMatrix() const noexcept
	{
		if (isTransformChange)
		{
			UpdateTransform();
			isTransformChange = false;
		}
		return transformMatrix;
	}

	TempTransformMatrix Transformable::GetRotationMatrix() const noexcept
	{
		if (isTransformChange)
		{
			UpdateTransform();
			isTransformChange = false;
		}
		return XMMatrixRotationQuaternion(transform.rotation.GetQuaternion());
	}

	void Transformable::UpdateTransform() const noexcept
	{
		transformMatrix = transform.GetTransformMatrix();
	}

	TempVector Transformable::GetRightVector() const noexcept
	{
		return XMVector3TransformCoord(RIGHT_VECTOR, GetRotationMatrix());
	}

	TempVector Transformable::GetForwardVector() const noexcept
	{
		return XMVector3TransformCoord(FORWARD_VECTOR, GetRotationMatrix());
	}

	TempVector Transformable::GetUpVector() const noexcept
	{
		return XMVector3TransformCoord(UP_VECTOR, GetRotationMatrix());
	}
}