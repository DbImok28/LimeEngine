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

void CameraObject::UpdateViewMatrix() noexcept
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
	camTarget += GetObjectLocationVector();
	viewMatrix = XMMatrixLookAtLH(GetObjectLocationVector(), camTarget, upDir);

	// last
	/*XMMATRIX camRotationMatrix = GetRotationMatrix();
	XMVECTOR camTarget = XMVector3TransformCoord(FORWARD_VECTOR, camRotationMatrix);
	XMVECTOR upDir = XMVector3TransformCoord(UP_VECTOR, camRotationMatrix);
	camTarget += GetObjectLocationVector();
	viewMatrix = XMMatrixLookAtLH(GetObjectLocationVector(), camTarget, upDir);*/
}

const XMMATRIX& CameraObject::GetViewMatrix() noexcept
{
	UpdateViewMatrix();
	return viewMatrix;
}

const XMMATRIX& CameraObject::GetProjectionMatrix() const noexcept
{
	return projectionMatrix;
}

XMMATRIX CameraObject::GetViewProjectionMatrix() noexcept
{
	return GetViewMatrix() * GetProjectionMatrix();
}
