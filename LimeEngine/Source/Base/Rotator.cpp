#include "lepch.hpp"
#include "Rotator.hpp"
#include "Math.hpp"

namespace LimeEngine
{
	Rotator::Rotator() noexcept : roll(0.0f), pitch(0.0f), yaw(0.0f) {}

	Rotator::Rotator(float rollDeg, float pitchDeg, float yawDeg) noexcept : roll(rollDeg), pitch(pitchDeg), yaw(yawDeg) {}

	bool Rotator::operator==(const Rotator& other) const noexcept
	{
		return roll == other.roll && pitch == other.pitch && yaw == other.yaw;
	}

	bool Rotator::operator!=(const Rotator& other) const noexcept
	{
		return !(*this == other);
	}

	Rotator Rotator::MakeFromRadians(float rollRad, float pitchRad, float yawRad) noexcept
	{
		return Rotator(Math::ConvertToDegrees(rollRad), Math::ConvertToDegrees(pitchRad), Math::ConvertToDegrees(yawRad));
	}

	Rotator Rotator::MakeRotator(TempQuaternion q) noexcept
	{
		Rotator r;
		r.SetQuaternion(q);
		return r;
	}

	TempQuaternion Rotator::MakeTempQuaternion(const Rotator& rot) noexcept
	{
		return MakeTempQuaternion(rot.roll, rot.pitch, rot.yaw);
	}

	TempQuaternion Rotator::MakeTempQuaternion(float roll, float pitch, float yaw) noexcept
	{
		return DirectX::XMQuaternionRotationRollPitchYaw(roll, pitch, yaw);
	}

	TempQuaternion Rotator::MakeTempQuaternionFromRadians(const Rotator& rot) noexcept
	{
		return MakeTempQuaternionFromRadians(rot.roll, rot.pitch, rot.yaw);
	}

	TempQuaternion Rotator::MakeTempQuaternionFromRadians(float roll, float pitch, float yaw) noexcept
	{
		return MakeTempQuaternion(Math::ConvertToRadians(roll), Math::ConvertToRadians(pitch), Math::ConvertToRadians(yaw));
	}

	void Rotator::Combine(const Rotator& other) noexcept
	{
		roll += other.roll;
		pitch += other.pitch;
		yaw += other.yaw;
	}

	TempQuaternion Rotator::GetQuaternion() const noexcept
	{
		return MakeTempQuaternionFromRadians(roll, pitch, yaw);
	}

	void Rotator::SetQuaternion(TempQuaternion quat) noexcept
	{
		DirectX::XMFLOAT4 q;
		DirectX::XMStoreFloat4(&q, DirectX::XMQuaternionNormalize(quat));

		// roll
		float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
		float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		roll = Math::ConvertToDegrees(Math::ATan2(sinr_cosp, cosr_cosp));

		// pitch
		float sinp = 2.0f * (q.w * q.y - q.z * q.x);
		if (Math::Abs(sinp) >= 1.0f)
		{
			pitch = Math::ConvertToDegrees(Math::Copysign(Math::piDivBy2, sinp));
		}
		else
		{
			pitch = Math::ConvertToDegrees(Math::ASin(sinp));
		}

		// yaw
		float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
		float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		yaw = Math::ConvertToDegrees(Math::ATan2(siny_cosp, cosy_cosp));
	}

	TempVector Rotator::GetEuler() const noexcept
	{
		return Vector::MakeTempVector(Math::ConvertToRadians(roll), Math::ConvertToRadians(pitch), Math::ConvertToRadians(yaw));
	}

	void Rotator::SetEuler(TempVector euler) noexcept
	{
		XMStoreFloat3(&vec3, euler);
		roll = Math::ConvertToDegrees(roll);
		pitch = Math::ConvertToDegrees(pitch);
		yaw = Math::ConvertToDegrees(yaw);
	}

	float* Rotator::GetArray() noexcept
	{
		return &roll;
	}
}