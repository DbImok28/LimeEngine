#include "SceneObject.hpp"

void SceneObject::Initialize(Engine* engine)
{
	this->engine = engine;
	InitializeComponents();
}

void SceneObject::Update()
{
	UpdateComponents();
}

void SceneObject::Render()
{
	RenderComponents();
}

void SceneObject::InitializeComponents()
{
	for (auto&& component : components)
	{
		component->Initialize(engine);
	}
}

void SceneObject::UpdateComponents()
{
	for (auto&& component : components)
	{
		component->Update();
	}
}

void SceneObject::RenderComponents()
{
	for (auto&& component : components)
	{
		component->Render();
	}
}

void SceneObject::AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept
{
	components.push_back(std::move(component));
	components.back()->Initialize(engine);
}

// location
const Vector& SceneObject::GetObjectLocation() const noexcept
{
	return transform.location;
}

XMVECTOR SceneObject::GetObjectLocationVector() const noexcept
{
	return transform.location.GetVector();
}

const XMFLOAT3& SceneObject::GetObjectLocationFloat3() const noexcept
{
	return transform.location.GetFloat3();
}

void SceneObject::SetObjectLocation(const Vector& loc) noexcept
{
	transform.location = loc;
	isChanged = true;
}

void SceneObject::SetObjectLocation(const XMVECTOR& loc) noexcept
{
	transform.location.Set(loc);
	isChanged = true;
}

void SceneObject::SetObjectLocation(const XMFLOAT3& loc) noexcept
{
	transform.location.Set(loc);
	isChanged = true;
}

void SceneObject::SetObjectLocation(float x, float y, float z) noexcept
{
	transform.location.Set(x, y, z);
	isChanged = true;
}

void SceneObject::AddObjectLocation(const Vector& loc) noexcept
{
	transform.location += loc;
	isChanged = true;
}

void SceneObject::AddObjectLocation(const XMVECTOR& loc) noexcept
{
	transform.location.Add(loc);
	isChanged = true;
}

void SceneObject::AddObjectLocation(const XMFLOAT3& loc) noexcept
{
	transform.location.Add(loc);
	isChanged = true;
}

void SceneObject::AddObjectLocation(float x, float y, float z) noexcept
{
	transform.location.Add(x, y, z);
	isChanged = true;
}

// rotation
const Vector& SceneObject::GetObjectRotation() const noexcept
{
	return transform.rotation;
}

XMVECTOR SceneObject::GetObjectRotationVector() const noexcept
{
	return transform.rotation.GetVector();
}

const XMFLOAT3& SceneObject::GetObjectRotationFloat3() const noexcept
{
	return transform.rotation.GetFloat3();
}

void SceneObject::SetObjectRotation(const Vector& rot) noexcept
{
	transform.rotation = rot;
	isChanged = true;
}

void SceneObject::SetObjectRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void SceneObject::SetObjectRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Set(rot);
	isChanged = true;
}

void SceneObject::SetObjectRotation(float x, float y, float z) noexcept
{
	transform.rotation.Set(x, y, z);
	isChanged = true;
}

void SceneObject::AddObjectRotation(const Vector& rot) noexcept
{
	transform.rotation += rot;
	isChanged = true;
}

void SceneObject::AddObjectRotation(const XMVECTOR& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void SceneObject::AddObjectRotation(const XMFLOAT3& rot) noexcept
{
	transform.rotation.Add(rot);
	isChanged = true;
}

void SceneObject::AddObjectRotation(float x, float y, float z) noexcept
{
	transform.rotation.Add(x, y, z);
	isChanged = true;
}

// scale
const Vector& SceneObject::GetObjectScale() const noexcept
{
	return transform.scale;
}

XMVECTOR SceneObject::GetObjectScaleVector() const noexcept
{
	return transform.scale.GetVector();
}

const XMFLOAT3& SceneObject::GetObjectScaleFloat3() const noexcept
{
	return transform.scale.GetFloat3();
}

void SceneObject::SetObjectScale(const Vector& scale) noexcept
{
	transform.scale = scale;
	isChanged = true;
}

void SceneObject::SetObjectScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void SceneObject::SetObjectScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Set(scale);
	isChanged = true;
}

void SceneObject::SetObjectScale(float x, float y, float z) noexcept
{
	transform.scale.Set(x, y, z);
	isChanged = true;
}

void SceneObject::AddObjectScale(const Vector& scale) noexcept
{
	transform.scale += scale;
	isChanged = true;
}

void SceneObject::AddObjectScale(const XMVECTOR& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void SceneObject::AddObjectScale(const XMFLOAT3& scale) noexcept
{
	transform.scale.Add(scale);
	isChanged = true;
}

void SceneObject::AddObjectScale(float x, float y, float z) noexcept
{
	transform.scale.Add(x, y, z);
	isChanged = true;
}

// transform
const Transform& SceneObject::GetObjectTransform() const noexcept
{
	return transform;
}

void SceneObject::SetObjectTransform(const Transform& transform) noexcept
{
	this->transform = transform;
	isChanged = true;
}

const XMMATRIX& SceneObject::GetTransformMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	return transformMatrix;
}

XMMATRIX SceneObject::GetRotationMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	return XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
}

void SceneObject::UpdateTransform() noexcept
{
	transformMatrix = transform.getTransformMatrix();
}

XMVECTOR SceneObject::GetObjectRightVector() noexcept
{
	return XMVector3TransformCoord(RIGHT_VECTOR, GetRotationMatrix());
}

XMVECTOR SceneObject::GetObjectForwardVector() noexcept
{
	return XMVector3TransformCoord(FORWARD_VECTOR, GetRotationMatrix());
}

XMVECTOR SceneObject::GetObjectUpVector() noexcept
{
	return XMVector3TransformCoord(UP_VECTOR, GetRotationMatrix());
}