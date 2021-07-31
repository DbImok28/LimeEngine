#include "GameObject.hpp"

XMVECTOR GameObject::GetPositionVector() const noexcept
{
	return transform.location.GetVector();
}

const XMFLOAT3& GameObject::GetPositionFloat3() const noexcept
{
	return transform.location.GetFloat3();
}

XMVECTOR GameObject::GetRotationVector() const noexcept
{
	return transform.rotation.GetVector();
}

const XMFLOAT3& GameObject::GetRotationFloat3() const noexcept
{
	return transform.rotation.GetFloat3();
}

XMVECTOR GameObject::GetScaleVector() const noexcept
{
	return transform.scale.GetVector();
}

const XMFLOAT3& GameObject::GetScaleFloat3() const noexcept
{
	return transform.scale.GetFloat3();
}
// location
void GameObject::SetPosition(const XMVECTOR& pos) noexcept
{
	transform.location.Set(pos);
	isChanged = true;
}

void GameObject::SetPosition(const XMFLOAT3& pos) noexcept
{
	transform.location.Set(pos);
	isChanged = true;
}

void GameObject::SetPosition(float x, float y, float z) noexcept
{
	transform.location.Set(x, y, z);
	isChanged = true;
}

void GameObject::AddPosition(const XMVECTOR& pos) noexcept
{
	transform.location.Add(pos);
	isChanged = true;
}

void GameObject::AddPosition(const XMFLOAT3& pos) noexcept
{
	transform.location.Add(pos);
	isChanged = true;
}

void GameObject::AddPosition(float x, float y, float z) noexcept
{
	transform.location.Add(x, y, z);
	isChanged = true;
}
// rotation
void GameObject::SetRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void GameObject::SetRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void GameObject::SetRotation(float x, float y, float z) noexcept
{
	transform.rotation.Set(x, y, z);
	isChanged = true;
}

void GameObject::AddRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void GameObject::AddRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void GameObject::AddRotation(float x, float y, float z) noexcept
{
	transform.rotation.Add(x, y, z);
	isChanged = true;
}
// scale
void GameObject::SetScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void GameObject::SetScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void GameObject::SetScale(float x, float y, float z) noexcept
{
	transform.scale.Set(x, y, z);
	isChanged = true;
}

void GameObject::AddScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void GameObject::AddScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void GameObject::AddScale(float x, float y, float z) noexcept
{
	transform.scale.Add(x, y, z);
	isChanged = true;
}

void GameObject::SetTransform(const Transform& transform) noexcept
{
	this->transform = transform;
	isChanged = true;
}

const XMMATRIX& GameObject::GetTransformMatrix()
{
	if (isChanged)
	{
		transformMatrix = transform.getTransformMatrix();
		isChanged = false;
	}
	return transformMatrix;
}