#include "GameObject.hpp"

// location
const Vector& GameObject::GetObjectPosition() const noexcept
{
	return transform.location;
}

XMVECTOR GameObject::GetObjectPositionVector() const noexcept
{
	return transform.location.GetVector();
}

const XMFLOAT3& GameObject::GetObjectPositionFloat3() const noexcept
{
	return transform.location.GetFloat3();
}

void GameObject::SetObjectLocation(const Vector& loc) noexcept
{
	transform.location = loc;
	isChanged = true;
}

void GameObject::SetObjectLocation(const XMVECTOR& loc) noexcept
{
	transform.location.Set(loc);
	isChanged = true;
}

void GameObject::SetObjectLocation(const XMFLOAT3& loc) noexcept
{
	transform.location.Set(loc);
	isChanged = true;
}

void GameObject::SetObjectLocation(float x, float y, float z) noexcept
{
	transform.location.Set(x, y, z);
	isChanged = true;
}

void GameObject::AddObjectLocation(const Vector& loc) noexcept
{
	transform.location += loc;
	isChanged = true;
}

void GameObject::AddObjectLocation(const XMVECTOR& loc) noexcept
{
	transform.location.Add(loc);
	isChanged = true;
}

void GameObject::AddObjectLocation(const XMFLOAT3& loc) noexcept
{
	transform.location.Add(loc);
	isChanged = true;
}

void GameObject::AddObjectLocation(float x, float y, float z) noexcept
{
	transform.location.Add(x, y, z);
	isChanged = true;
}

// rotation
const Vector& GameObject::GetObjectRotation() const noexcept
{
	return transform.rotation;
}

XMVECTOR GameObject::GetObjectRotationVector() const noexcept
{
	return transform.rotation.GetVector();
}

const XMFLOAT3& GameObject::GetObjectRotationFloat3() const noexcept
{
	return transform.rotation.GetFloat3();
}

void GameObject::SetObjectRotation(const Vector& rot) noexcept
{
	transform.rotation = rot;
	isChanged = true;
}

void GameObject::SetObjectRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void GameObject::SetObjectRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void GameObject::SetObjectRotation(float x, float y, float z) noexcept
{
	transform.rotation.Set(x, y, z);
	isChanged = true;
}

void GameObject::AddObjectRotation(const Vector& rot) noexcept
{
	transform.rotation += rot;
	isChanged = true;
}

void GameObject::AddObjectRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void GameObject::AddObjectRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void GameObject::AddObjectRotation(float x, float y, float z) noexcept
{
	transform.rotation.Add(x, y, z);
	isChanged = true;
}

// scale
const Vector& GameObject::GetObjectScale() const noexcept
{
	return transform.scale;
}

XMVECTOR GameObject::GetObjectScaleVector() const noexcept
{
	return transform.scale.GetVector();
}

const XMFLOAT3& GameObject::GetObjectScaleFloat3() const noexcept
{
	return transform.scale.GetFloat3();
}

void GameObject::SetObjectScale(const Vector& scale) noexcept
{
	transform.scale = scale;
	isChanged = true;
}

void GameObject::SetObjectScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void GameObject::SetObjectScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void GameObject::SetObjectScale(float x, float y, float z) noexcept
{
	transform.scale.Set(x, y, z);
	isChanged = true;
}

void GameObject::AddObjectScale(const Vector& scale) noexcept
{
	transform.scale += scale;
	isChanged = true;
}

void GameObject::AddObjectScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void GameObject::AddObjectScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void GameObject::AddObjectScale(float x, float y, float z) noexcept
{
	transform.scale.Add(x, y, z);
	isChanged = true;
}

// transform
const Transform& GameObject::GetObjectTransform() const noexcept
{
	return transform;
}

void GameObject::SetObjectTransform(const Transform& transform) noexcept
{
	this->transform = transform;
	isChanged = true;
}

const XMMATRIX& GameObject::GetTransformMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	return transformMatrix;
}

XMMATRIX GameObject::GetRotationMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	return XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
}

void GameObject::UpdateTransform() noexcept
{
	transformMatrix = transform.getTransformMatrix();
}

XMVECTOR GameObject::GetObjectRightVector() noexcept
{
	return XMVector3TransformCoord(RIGHT_VECTOR, GetRotationMatrix());
}

XMVECTOR GameObject::GetObjectForwardVector() noexcept
{
	return XMVector3TransformCoord(FORWARD_VECTOR, GetRotationMatrix());
}

XMVECTOR GameObject::GetObjectUpVector() noexcept
{
	return XMVector3TransformCoord(UP_VECTOR, GetRotationMatrix());
}