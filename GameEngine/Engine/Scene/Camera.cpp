#include "Camera.hpp"

void Camera::Initialize(ProjectionType projectionType, float width, float height, float fovDegrees, float nearZ, float farZ)
{
	this->width = width;
	this->height = height;
	this->nearZ = nearZ;
	this->farZ = farZ;
	fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	aspectRatio = width / height;
	switch (projectionType)
	{
	case Camera::ProjectionType::Perspective:
	{
		SetPerspective();
		break;
	}
	case Camera::ProjectionType::Orthographic:
	{
		SetOrthographic();
		break;
	}
	}
	UpdateViewMatrix();
	return;
}

void Camera::SetPerspective()
{
	projectionType = ProjectionType::Perspective;
	projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

void Camera::SetOrthographic()
{
	projectionType = ProjectionType::Orthographic;
	projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
}

void Camera::UpdateViewMatrix() noexcept
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
	camTarget += GetObjectPositionVector();
	viewMatrix = XMMatrixLookAtLH(GetObjectPositionVector(), camTarget, upDir);

	// last
	/*XMMATRIX camRotationMatrix = GetRotationMatrix();
	XMVECTOR camTarget = XMVector3TransformCoord(FORWARD_VECTOR, camRotationMatrix);
	XMVECTOR upDir = XMVector3TransformCoord(UP_VECTOR, camRotationMatrix);
	camTarget += GetObjectPositionVector();
	viewMatrix = XMMatrixLookAtLH(GetObjectPositionVector(), camTarget, upDir);*/
}

const XMMATRIX& Camera::GetViewMatrix() noexcept
{
	UpdateViewMatrix();
	return viewMatrix;
}

const XMMATRIX& Camera::GetProjectionMatrix() const noexcept
{
	return projectionMatrix;
}

XMMATRIX Camera::GetViewProjectionMatrix() noexcept
{
	return GetViewMatrix() * GetProjectionMatrix();
}
