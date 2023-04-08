#include "lepch.hpp"
#include "CameraComponent.hpp"
#include "Engine.hpp"
#include "Base/Math.hpp"

namespace LimeEngine
{
	CameraComponent::CameraComponent(
		Engine* engine,
		const std::string& componentName,
		const Transform& transform,
		float width,
		float height,
		ProjectionType projectionType,
		float fovDegrees,
		float nearZ,
		float farZ) noexcept :
		SceneComponent(engine, componentName, transform),
		projectionType(projectionType), width(width), height(height), fovDegrees(fovDegrees) /*fovRadians((fovDegrees / 360.0f) * Math::pi2)*/, nearZ(nearZ), farZ(farZ),
		aspectRatio(width / height)
	{
		SetProjectionType(projectionType);
	}

	void CameraComponent::SetProjectionType(ProjectionType type)
	{
		this->projectionType = type;
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

	void CameraComponent::CheckClippingPlane() noexcept
	{
		if (nearZ <= 0) nearZ = 0.0001f;
		if (Math::IsNearEqual(nearZ, farZ, 0.0001f)) farZ = nearZ + 0.0001f;
		if (farZ <= 0) farZ = 0.0001f;
	}

	void CameraComponent::SetPerspective()
	{
		CheckClippingPlane();
		if (Math::IsNearEqual(fovDegrees, 0, 0.005f)) fovDegrees = 0.005f;
		aspectRatio = width / height;
		projectionType = ProjectionType::Perspective;
		projectionMatrix = XMMatrixPerspectiveFovLH(Math::toRadians * fovDegrees, aspectRatio, nearZ, farZ);
	}

	void CameraComponent::SetOrthographic()
	{
		CheckClippingPlane();
		projectionType = ProjectionType::Orthographic;
		projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
	}

	void CameraComponent::Resize(float width, float height) noexcept
	{
		this->width = width;
		this->height = height;
		RecalculateViewMatrix();
	}

	void CameraComponent::RecalculateViewMatrix() noexcept
	{
		SetProjectionType(projectionType);
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

	void CameraComponent::DebugUpdate()
	{
		bool changed = false;
		changed = RuntimeEditor::Input("FovDegrees", fovDegrees) || changed;
		changed = RuntimeEditor::Input("NearZ", nearZ) || changed;
		changed = RuntimeEditor::Input("FarZ", farZ) || changed;
		if (changed)
		{
			RecalculateViewMatrix();
		}
	}
}