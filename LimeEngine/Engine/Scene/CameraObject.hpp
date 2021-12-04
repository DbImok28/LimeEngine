#pragma once
#include "SceneObject.hpp"

class CameraObject : public SceneObject
{
public:
	enum class ProjectionType
	{
		Perspective,
		Orthographic
	};
	CameraObject(ProjectionType projectionType, float width, float height, float fovDegrees = 90.0f, float nearZ = 0.001f, float farZ = 10000.0f) noexcept;
	void Initialize(Engine* engine) override;
	void SetPerspective();
	void SetOrthographic();

	void UpdateViewMatrix() const noexcept;
	const XMMATRIX& GetViewMatrix() const noexcept;
	const XMMATRIX& GetProjectionMatrix() const noexcept;
	XMMATRIX GetViewProjectionMatrix() const noexcept;

private:
	mutable XMMATRIX viewMatrix = XMMatrixIdentity();
	mutable XMMATRIX projectionMatrix = XMMatrixIdentity();
	ProjectionType projectionType = ProjectionType::Perspective;
public:
	float width;
	float height;
	float fovRadians;
	float aspectRatio;
	float nearZ;
	float farZ;
};