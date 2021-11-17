#pragma once
#include <vector>
#include <memory>

#include "SceneComponent.hpp"
#include "../Base/Transform.hpp"

using namespace DirectX;

const XMVECTOR RIGHT_VECTOR =	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);	// x
const XMVECTOR FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	// z
const XMVECTOR UP_VECTOR =		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);	// y

class SceneObject
{
public:
	virtual void Initialize(Engine* engine);
	virtual void Update();
	virtual void Render();

	// Components

	void InitializeComponents();
	void UpdateComponents();
	void RenderComponents();
	void AttachComponent(std::unique_ptr<SceneComponent>&& component) noexcept;

	// Transform

	const Vector& GetObjectLocation() const noexcept;
	XMVECTOR GetObjectLocationVector() const noexcept;
	const XMFLOAT3& GetObjectLocationFloat3() const noexcept;
	void SetObjectLocation(const Vector& loc) noexcept;
	void SetObjectLocation(const XMVECTOR& loc) noexcept;
	void SetObjectLocation(const XMFLOAT3& loc) noexcept;
	void SetObjectLocation(float x, float y, float z) noexcept;
	void AddObjectLocation(const Vector& loc) noexcept;
	void AddObjectLocation(const XMVECTOR& loc) noexcept;
	void AddObjectLocation(const XMFLOAT3& loc) noexcept;
	void AddObjectLocation(float x, float y, float z) noexcept;

	const Vector& GetObjectRotation() const noexcept;
	XMVECTOR GetObjectRotationVector() const noexcept;
	const XMFLOAT3& GetObjectRotationFloat3() const noexcept;
	void SetObjectRotation(const Vector& rot) noexcept;
	void SetObjectRotation(const XMVECTOR& rot) noexcept;
	void SetObjectRotation(const XMFLOAT3& rot) noexcept; 
	void SetObjectRotation(float x, float y, float z) noexcept;
	void AddObjectRotation(const Vector& rot) noexcept;
	void AddObjectRotation(const XMVECTOR& rot) noexcept;
	void AddObjectRotation(const XMFLOAT3& rot) noexcept;
	void AddObjectRotation(float x, float y, float z) noexcept;

	const Vector& GetObjectScale() const noexcept;
	XMVECTOR GetObjectScaleVector() const noexcept;
	const XMFLOAT3& GetObjectScaleFloat3() const noexcept;
	void SetObjectScale(const Vector& scale) noexcept;
	void SetObjectScale(const XMVECTOR& scale) noexcept;
	void SetObjectScale(const XMFLOAT3& scale) noexcept;
	void SetObjectScale(float x, float y, float z) noexcept;
	void AddObjectScale(const Vector& scale) noexcept;
	void AddObjectScale(const XMVECTOR& scale) noexcept;
	void AddObjectScale(const XMFLOAT3& scale) noexcept;
	void AddObjectScale(float x, float y, float z) noexcept;

	const Transform& GetObjectTransform() const noexcept;
	void SetObjectTransform(const Transform& transform) noexcept;

	const XMMATRIX& GetTransformMatrix() noexcept;
	XMMATRIX GetRotationMatrix() noexcept;
	void UpdateTransform() noexcept;

	XMVECTOR GetObjectRightVector() noexcept;
	XMVECTOR GetObjectForwardVector() noexcept;
	XMVECTOR GetObjectUpVector() noexcept;

	virtual ~SceneObject() noexcept = default;
public:
	std::vector<std::unique_ptr<SceneComponent>> components;

protected:
	Engine* engine = nullptr;
	bool isChanged = true;

private:
	Transform transform;
	XMMATRIX transformMatrix = XMMatrixIdentity();
};