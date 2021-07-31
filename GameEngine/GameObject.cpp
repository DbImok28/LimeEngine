#include "GameObject.hpp"

const XMVECTOR& GameObject::GetPositionVector() const noexcept
{
	return XMLoadFloat3(&this->pos);
}

const XMFLOAT3& GameObject::GetPositionFloat3() const noexcept
{
	return pos;
}

const XMVECTOR& GameObject::GetRotationVector() const noexcept
{
	return XMLoadFloat3(&this->rot);
}

const XMFLOAT3& GameObject::GetRotationFloat3() const noexcept
{
	return rot;
}

const XMVECTOR& GameObject::GetScaleVector() const noexcept
{
	return XMLoadFloat3(&this->scale);
}

const XMFLOAT3& GameObject::GetScaleFloat3() const noexcept
{
	return scale;
}

void GameObject::SetPosition(const XMVECTOR& pos) noexcept
{
	XMStoreFloat3(&this->pos, pos);
	isChanged = true;
}

void GameObject::SetPosition(const XMFLOAT3& pos) noexcept
{
	this->pos = pos;
	isChanged = true;
}

void GameObject::SetPosition(float x, float y, float z) noexcept
{
	pos = XMFLOAT3(x, y, z);
	isChanged = true;
}

void GameObject::AddPosition(const XMVECTOR& pos) noexcept
{
	XMStoreFloat3(&this->pos, GetPositionVector() + pos);
	isChanged = true;
}

void GameObject::AddPosition(const XMFLOAT3& pos) noexcept
{
	this->pos.x += pos.x;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	isChanged = true;
}

void GameObject::AddPosition(float x, float y, float z) noexcept
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
	isChanged = true;
}

void GameObject::SetRotation(const XMVECTOR& rot) noexcept
{
	XMStoreFloat3(&this->rot, rot);
	isChanged = true;
}

void GameObject::SetRotation(const XMFLOAT3& rot) noexcept
{
	this->rot = rot;
	isChanged = true;
}

void GameObject::SetRotation(float x, float y, float z) noexcept
{
	rot = XMFLOAT3(x, y, z);
	isChanged = true;
}

void GameObject::AddRotation(const XMVECTOR& rot) noexcept
{
	XMStoreFloat3(&this->rot, GetRotationVector() + rot);
	isChanged = true;
}

void GameObject::AddRotation(const XMFLOAT3& rot) noexcept
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	isChanged = true;
}

void GameObject::AddRotation(float x, float y, float z) noexcept
{
	rot.x += x;
	rot.y += y;
	rot.z += z;
	isChanged = true;
}

void GameObject::SetScale(const XMVECTOR& scale) noexcept
{
	XMStoreFloat3(&this->scale, scale);
	isChanged = true;
}

void GameObject::SetScale(const XMFLOAT3& scale) noexcept
{
	this->scale = scale;
	isChanged = true;
}

void GameObject::SetScale(float x, float y, float z) noexcept
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	isChanged = true;
}

void GameObject::AddScale(const XMVECTOR& scale) noexcept
{
	XMStoreFloat3(&this->scale, GetScaleVector() + scale);
	isChanged = true;
}

void GameObject::AddScale(const XMFLOAT3& scale) noexcept
{
	this->scale.x += scale.x;
	this->scale.y += scale.y;
	this->scale.z += scale.z;
	isChanged = true;
}

void GameObject::AddScale(float x, float y, float z) noexcept
{
	scale.x += x;
	scale.y += y;
	scale.z += z;
	isChanged = true;
}
