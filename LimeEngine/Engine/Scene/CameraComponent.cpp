#include "CameraComponent.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	CameraComponent::CameraComponent(
		Engine* engine, const Transform& transform, float width, float height, ProjectionType projectionType, float fovDegrees, float nearZ, float farZ) noexcept :
		SceneComponent(engine, transform),
		projectionType(projectionType), width(width), height(height), fovRadians((fovDegrees / 360.0f) * XM_2PI), nearZ(nearZ), farZ(farZ), aspectRatio(width / height)
	{
		switch (projectionType)
		{
			case ProjectionType::Perspective:
			{
				SetPerspective();
				break;
			}
			case ProjectionType::Orthographic:
			{
				SetOrthographic();
				break;
			}
		}
		UpdateViewMatrix();
	}

	void CameraComponent::SetPerspective()
	{
		projectionType = ProjectionType::Perspective;
		projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
	}

	void CameraComponent::SetOrthographic()
	{
		projectionType = ProjectionType::Orthographic;
		projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
	}

	void CameraComponent::UpdateViewMatrix() const noexcept
	{
		if (isTransformChange)
		{
			UpdateTransform();
			isTransformChange = false;
		}
		XMMATRIX camRotationMatrix = GetRotationMatrix();
		XMVECTOR camTarget = XMVector3TransformCoord(FORWARD_VECTOR, camRotationMatrix);
		XMVECTOR upDir = XMVector3TransformCoord(UP_VECTOR, camRotationMatrix);
		camTarget += GetTempLocationVector();
		viewMatrix = XMMatrixLookAtLH(GetTempLocationVector(), camTarget, upDir);
	}

	const XMMATRIX& CameraComponent::GetViewMatrix() const noexcept
	{
		UpdateViewMatrix();
		return viewMatrix;
	}

	const XMMATRIX& CameraComponent::GetProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	XMMATRIX CameraComponent::GetViewProjectionMatrix() const noexcept
	{
		return GetViewMatrix() * GetProjectionMatrix();
	}
}