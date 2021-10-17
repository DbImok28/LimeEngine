#include "GameComponent.hpp"

// location
const Vector& GameComponent::GetComponentPosition() const noexcept
{
	return transform.location;
}

XMVECTOR GameComponent::GetComponentPositionVector() const noexcept
{
	return transform.location.GetVector();
}

const XMFLOAT3& GameComponent::GetComponentPositionFloat3() const noexcept
{
	return transform.location.GetFloat3();
}

void GameComponent::SetComponentLocation(const Vector& loc) noexcept
{
	transform.location = loc;
	isChanged = true;
}

void GameComponent::SetComponentLocation(const XMVECTOR& loc) noexcept
{
	transform.location.Set(loc);
	isChanged = true;
}

void GameComponent::SetComponentLocation(const XMFLOAT3& loc) noexcept
{
	transform.location.Set(loc);
	isChanged = true;
}

void GameComponent::SetComponentLocation(float x, float y, float z) noexcept
{
	transform.location.Set(x, y, z);
	isChanged = true;
}

void GameComponent::AddComponentLocation(const Vector& loc) noexcept
{
	transform.location += loc;
	isChanged = true;
}

void GameComponent::AddComponentLocation(const XMVECTOR& loc) noexcept
{
	transform.location.Add(loc);
	isChanged = true;
}

void GameComponent::AddComponentLocation(const XMFLOAT3& loc) noexcept
{
	transform.location.Add(loc);
	isChanged = true;
}

void GameComponent::AddComponentLocation(float x, float y, float z) noexcept
{
	transform.location.Add(x, y, z);
	isChanged = true;
}

// rotation
const Vector& GameComponent::GetComponentRotation() const noexcept
{
	return transform.rotation;
}

XMVECTOR GameComponent::GetComponentRotationVector() const noexcept
{
	return transform.rotation.GetVector();
}

const XMFLOAT3& GameComponent::GetComponentRotationFloat3() const noexcept
{
	return transform.rotation.GetFloat3();
}

void GameComponent::SetComponentRotation(const Vector& rot) noexcept
{
	transform.rotation = rot;
	isChanged = true;
}

void GameComponent::SetComponentRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void GameComponent::SetComponentRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void GameComponent::SetComponentRotation(float x, float y, float z) noexcept
{
	transform.rotation.Set(x, y, z);
	isChanged = true;
}

void GameComponent::AddComponentRotation(const Vector& rot) noexcept
{
	transform.rotation += rot;
	isChanged = true;
}

void GameComponent::AddComponentRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void GameComponent::AddComponentRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void GameComponent::AddComponentRotation(float x, float y, float z) noexcept
{
	transform.rotation.Add(x, y, z);
	isChanged = true;
}

// scale
const Vector& GameComponent::GetComponentScale() const noexcept
{
	return transform.scale;
}

XMVECTOR GameComponent::GetComponentScaleVector() const noexcept
{
	return transform.scale.GetVector();
}

const XMFLOAT3& GameComponent::GetComponentScaleFloat3() const noexcept
{
	return transform.scale.GetFloat3();
}

void GameComponent::SetComponentScale(const Vector& scale) noexcept
{
	transform.scale = scale;
	isChanged = true;
}

void GameComponent::SetComponentScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void GameComponent::SetComponentScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void GameComponent::SetComponentScale(float x, float y, float z) noexcept
{
	transform.scale.Set(x, y, z);
	isChanged = true;
}

void GameComponent::AddComponentScale(const Vector& scale) noexcept
{
	transform.scale += scale;
	isChanged = true;
}

void GameComponent::AddComponentScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void GameComponent::AddComponentScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void GameComponent::AddComponentScale(float x, float y, float z) noexcept
{
	transform.scale.Add(x, y, z);
	isChanged = true;
}

// transform
const Transform& GameComponent::GetComponentTransform() const noexcept
{
	return transform;
}

void GameComponent::SetComponentTransform(const Transform& transform) noexcept
{
	this->transform = transform;
	isChanged = true;
}

const XMMATRIX& GameComponent::GetTransformMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	return transformMatrix;
}

XMMATRIX GameComponent::GetRotationMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	return XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
}

void GameComponent::UpdateTransform() noexcept
{
	transformMatrix = transform.getTransformMatrix();
}

XMVECTOR GameComponent::GetComponentRightVector() noexcept
{
	return XMVector3TransformCoord(RIGHT_VECTOR, GetRotationMatrix());
}

XMVECTOR GameComponent::GetComponentForwardVector() noexcept
{
	return XMVector3TransformCoord(FORWARD_VECTOR, GetRotationMatrix());
}

XMVECTOR GameComponent::GetComponentUpVector() noexcept
{
	return XMVector3TransformCoord(UP_VECTOR, GetRotationMatrix());
}