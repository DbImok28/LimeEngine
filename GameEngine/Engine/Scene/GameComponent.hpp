#pragma once
#include "SceneComponent.hpp"
#include "../Base/Transform.hpp"

using namespace DirectX;

const XMVECTOR RIGHT_VECTOR =	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);	// x
const XMVECTOR FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	// z
const XMVECTOR UP_VECTOR =		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);	// y

class GameComponent : public SceneComponent
{
public:
	const Vector& GetComponentPosition() const noexcept;
	XMVECTOR GetComponentPositionVector() const noexcept;
	const XMFLOAT3& GetComponentPositionFloat3() const noexcept;
	void SetComponentLocation(const Vector& loc) noexcept;
	void SetComponentLocation(const XMVECTOR& loc) noexcept;
	void SetComponentLocation(const XMFLOAT3& loc) noexcept;
	void SetComponentLocation(float x, float y, float z) noexcept;
	void AddComponentLocation(const Vector& loc) noexcept;
	void AddComponentLocation(const XMVECTOR& loc) noexcept;
	void AddComponentLocation(const XMFLOAT3& loc) noexcept;
	void AddComponentLocation(float x, float y, float z) noexcept;

	const Vector& GetComponentRotation() const noexcept;
	XMVECTOR GetComponentRotationVector() const noexcept;
	const XMFLOAT3& GetComponentRotationFloat3() const noexcept;
	void SetComponentRotation(const Vector& rot) noexcept;
	void SetComponentRotation(const XMVECTOR& rot) noexcept;
	void SetComponentRotation(const XMFLOAT3& rot) noexcept; 
	void SetComponentRotation(float x, float y, float z) noexcept;
	void AddComponentRotation(const Vector& rot) noexcept;
	void AddComponentRotation(const XMVECTOR& rot) noexcept;
	void AddComponentRotation(const XMFLOAT3& rot) noexcept;
	void AddComponentRotation(float x, float y, float z) noexcept;

	const Vector& GetComponentScale() const noexcept;
	XMVECTOR GetComponentScaleVector() const noexcept;
	const XMFLOAT3& GetComponentScaleFloat3() const noexcept;
	void SetComponentScale(const Vector& scale) noexcept;
	void SetComponentScale(const XMVECTOR& scale) noexcept;
	void SetComponentScale(const XMFLOAT3& scale) noexcept;
	void SetComponentScale(float x, float y, float z) noexcept;
	void AddComponentScale(const Vector& scale) noexcept;
	void AddComponentScale(const XMVECTOR& scale) noexcept;
	void AddComponentScale(const XMFLOAT3& scale) noexcept;
	void AddComponentScale(float x, float y, float z) noexcept;

	const Transform& GetComponentTransform() const noexcept;
	void SetComponentTransform(const Transform& transform) noexcept;

	const XMMATRIX& GetTransformMatrix() noexcept;
	XMMATRIX GetRotationMatrix() noexcept;
	void UpdateTransform() noexcept;

	XMVECTOR GetComponentRightVector() noexcept;
	XMVECTOR GetComponentForwardVector() noexcept;
	XMVECTOR GetComponentUpVector() noexcept;

protected:
	bool isChanged = true;

private:
	Transform transform;
	XMMATRIX transformMatrix = XMMatrixIdentity();
};