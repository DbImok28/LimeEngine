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

	void UpdateViewMatrix() noexcept;
	const XMMATRIX& GetViewMatrix() noexcept;
	const XMMATRIX& GetProjectionMatrix() const noexcept;
	XMMATRIX GetViewProjectionMatrix() noexcept;
	ProjectionType projectionType = ProjectionType::Perspective;

	float width;
	float height;
	float fovRadians;
	float aspectRatio;
	float nearZ;
	float farZ;
private:
	XMMATRIX viewMatrix = XMMatrixIdentity();
	XMMATRIX projectionMatrix = XMMatrixIdentity();
};