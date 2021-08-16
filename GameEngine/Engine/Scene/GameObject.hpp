#pragma once
#include "../Base/Transform.hpp"

using namespace DirectX;

//const XMVECTOR RIGHT_VECTOR		= XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f); // x
//const XMVECTOR FORWARD_VECTOR	= XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // y
//const XMVECTOR UP_VECTOR		= XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // z

const XMVECTOR RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);		// x
const XMVECTOR FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	// z
const XMVECTOR UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);			// y

class GameObject
{
public:
	const Vector& GetObjectPosition() const noexcept;
	XMVECTOR GetObjectPositionVector() const noexcept;
	const XMFLOAT3& GetObjectPositionFloat3() const noexcept;
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
	bool isChanged = true;
	Transform transform;
	XMMATRIX transformMatrix = XMMatrixIdentity();
private:
};