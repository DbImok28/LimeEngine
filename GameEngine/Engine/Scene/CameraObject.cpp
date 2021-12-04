#include "CameraObject.hpp"

CameraObject::CameraObject(ProjectionType projectionType, float width, float height, float fovDegrees, float nearZ, float farZ) noexcept :
	projectionType(projectionType),
	width(width),
	height(height),
	fovRadians((fovDegrees / 360.0f)* XM_2PI),
	nearZ(nearZ),
	farZ(farZ),
	aspectRatio(width / height)
{}

void CameraObject::Initialize(Engine* engine)
{
	this->engine = engine;
	switch (projectionType)
	{
	case CameraObject::ProjectionType::Perspective:
	{
		SetPerspective();
		break;
	}
	case CameraObject::ProjectionType::Orthographic:
	{
		SetOrthographic();
		break;
	}
	}
	UpdateViewMatrix();

	InitializeComponents();
}

void CameraObject::SetPerspective()
{
	projectionType = ProjectionType::Perspective;
	projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

void CameraObject::SetOrthographic()
{
	projectionType = ProjectionType::Orthographic;
	projectionMatrix = XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
}

void CameraObject::UpdateViewMatrix() const noexcept
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

const XMMATRIX& CameraObject::GetViewMatrix() const noexcept
{
	UpdateViewMatrix();
	return viewMatrix;
}

const XMMATRIX& CameraObject::GetProjectionMatrix() const noexcept
{
	return projectionMatrix;
}

XMMATRIX CameraObject::GetViewProjectionMatrix() const noexcept
{
	return GetViewMatrix() * GetProjectionMatrix();
}
