#include "CameraComponent.hpp"

void CameraComponent::Initialize(ProjectionType projectionType, float width, float height, float fovDegrees, float nearZ, float farZ)
{
	this->width = width;
	this->height = height;
	this->nearZ = nearZ;
	this->farZ = farZ;
	fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	aspectRatio = width / height;
	switch (projectionType)
	{
	case CameraComponent::ProjectionType::Perspective:
	{
		SetPerspective();
		break;
	}
	case CameraComponent::ProjectionType::Orthographic:
	{
		SetOrthographic();
		break;
	}
	}
	UpdateViewMatrix();
	return;
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

void CameraComponent::UpdateViewMatrix() noexcept
{
	if (isChanged)
	{
		UpdateTransform();
		isChanged = false;
	}
	/*const XMMATRIX TransformZUpToYUp = XMMatrixSet // Converting a Z Up Matrix to a Y Up Matrix
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	viewMatrix = TransformZUpToYUp;
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.z, transform.rotation.y);
	XMVECTOR camTarget = XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), camRotationMatrix);
	XMVECTOR upDir = XMVector3TransformCoord(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), camRotationMatrix);
	camTarget += XMVectorSet(transform.location.x, transform.location.z, transform.location.y, 1.0f);
	viewMatrix *= XMMatrixLookAtLH(XMVectorSet(transform.location.x, transform.location.z, transform.location.y, 1.0f), camTarget, upDir);*/

	XMMATRIX camRotationMatrix = GetRotationMatrix();
	XMVECTOR camTarget = XMVector3TransformCoord(FORWARD_VECTOR, camRotationMatrix);
	XMVECTOR upDir = XMVector3TransformCoord(UP_VECTOR, camRotationMatrix);
	camTarget += GetComponentPositionVector();
	viewMatrix = XMMatrixLookAtLH(GetComponentPositionVector(), camTarget, upDir);

	// last
	/*XMMATRIX camRotationMatrix = GetRotationMatrix();
	XMVECTOR camTarget = XMVector3TransformCoord(FORWARD_VECTOR, camRotationMatrix);
	XMVECTOR upDir = XMVector3TransformCoord(UP_VECTOR, camRotationMatrix);
	camTarget += GetComponentPositionVector();
	viewMatrix = XMMatrixLookAtLH(GetComponentPositionVector(), camTarget, upDir);*/
}

const XMMATRIX& CameraComponent::GetViewMatrix() noexcept
{
	UpdateViewMatrix();
	return viewMatrix;
}

const XMMATRIX& CameraComponent::GetProjectionMatrix() const noexcept
{
	return projectionMatrix;
}

XMMATRIX CameraComponent::GetViewProjectionMatrix() noexcept
{
	return GetViewMatrix() * GetProjectionMatrix();
}
