#pragma once
#include <DirectXMath.h>
#include "Vector.hpp"

using namespace DirectX;

using TempQuaternion = XMVECTOR;

class Rotator
{
public:
	Rotator() noexcept;
	Rotator(float rollDeg, float pitchDeg, float yawDeg) noexcept;	
	static Rotator MakeForRad(float rollRad, float pitchRad, float yawRad) noexcept;
	static Rotator MakeRotator(TempQuaternion q) noexcept;
	Rotator(const Rotator& other) noexcept = default;
	Rotator(Rotator&& other) noexcept = default;
	Rotator& operator=(const Rotator& other) = default;
	Rotator& operator=(Rotator&& other) = default;
	
	bool operator==(const Rotator& other) const noexcept;
	bool operator!=(const Rotator& other) const noexcept;
	
	TempQuaternion GetQuaternion() const noexcept;
	TempVector GetEuler() const noexcept;
	void SetQuaternion(TempQuaternion quat) noexcept;
	void SetEuler(TempVector euler) noexcept;
	float* GetArray() noexcept;
	void Combine(const Rotator& other) noexcept;
	union
	{
		struct
		{
			float roll;		// x deg
			float pitch;	// y deg
			float yaw;		// z deg
		};
		XMFLOAT3 vec3{};
	};
};