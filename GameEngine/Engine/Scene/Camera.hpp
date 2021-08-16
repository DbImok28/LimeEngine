#pragma once
#include "GameObject.hpp"
class Camera : public GameObject
{
public:
	enum class ProjectionType
	{
		Perspective,
		Orthographic
	};
	void Initialize(ProjectionType projectionType, float width, float height, float fovDegrees = 90.0f, float nearZ = 0.001f, float farZ = 10000.0f);
	void SetPerspective();
	void SetOrthographic();

	void UpdateViewMatrix() noexcept;
	const XMMATRIX& GetViewMatrix() noexcept;
	const XMMATRIX& GetProjectionMatrix() const noexcept;
	XMMATRIX GetViewProjectionMatrix() noexcept;
	ProjectionType projectionType;

	float width = 0.0f;
	float height = 0.0f;
	float fovRadians = 0.0f;
	float aspectRatio = 0.0f;
	float nearZ = 0.0f;
	float farZ = 0.0f;
private:
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
};