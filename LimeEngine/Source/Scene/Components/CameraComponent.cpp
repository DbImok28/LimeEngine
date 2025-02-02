// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "CameraComponent.hpp"
#include "Base/Math.hpp"

namespace LimeEngine
{
	CameraComponent::CameraComponent(const std::string& componentName, float width, float height, ProjectionType projectionType, float fovDegrees, float nearZ, float farZ) noexcept
		: SceneComponent(componentName), projectionType(projectionType), width(width), height(height), fovDegrees(fovDegrees), nearZ(nearZ), farZ(farZ), aspectRatio(width / height)
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
		XMVECTOR camTarget = XMVector3TransformCoord(Vector::ForwardVector, camRotationMatrix);
		XMVECTOR upDir = XMVector3TransformCoord(Vector::UpVector, camRotationMatrix);
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
		SceneComponent::DebugUpdate();

		bool changed = false;
		changed = RuntimeEditor::Input("FovDegrees", fovDegrees) || changed;
		changed = RuntimeEditor::Input("NearZ", nearZ) || changed;
		changed = RuntimeEditor::Input("FarZ", farZ) || changed;
		if (changed) RecalculateViewMatrix();
	}
}