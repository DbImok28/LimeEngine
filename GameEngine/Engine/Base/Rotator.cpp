#include "Rotator.hpp"
#include <cmath>

Rotator::Rotator() noexcept : roll(0.0f), pitch(0.0f), yaw(0.0f) {}

Rotator::Rotator(float rollDeg, float pitchDeg, float yawDeg) noexcept : roll(rollDeg), pitch(pitchDeg), yaw(yawDeg) {}

inline Rotator Rotator::MakeForRad(float rollRad, float pitchRad, float yawRad) noexcept
{
    return Rotator(XMConvertToDegrees(rollRad), XMConvertToDegrees(pitchRad), XMConvertToDegrees(yawRad));
}

Rotator Rotator::MakeRotator(TempQuaternion q) noexcept
{
    Rotator r;
    r.SetQuaternion(q);
    return r;
}

bool Rotator::operator==(const Rotator& other) const noexcept
{
    return roll == other.roll && pitch == other.pitch && yaw == other.yaw;
}

bool Rotator::operator!=(const Rotator& other) const noexcept
{
    return !(*this == other);
}

TempQuaternion Rotator::GetQuaternion() const noexcept
{
    return XMQuaternionRotationRollPitchYaw(XMConvertToRadians(roll), XMConvertToRadians(pitch), XMConvertToRadians(yaw));
}

TempVector Rotator::GetEuler() const noexcept
{
    XMFLOAT3 euler(XMConvertToRadians(roll), XMConvertToRadians(pitch), XMConvertToRadians(yaw));
    return XMLoadFloat3(&vec3);
}

void Rotator::SetQuaternion(TempQuaternion quat) noexcept
{
    XMFLOAT4 q;
    XMStoreFloat4(&q, XMQuaternionNormalize(quat));
   
    // roll
    float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    roll = XMConvertToDegrees(std::atan2f(sinr_cosp, cosr_cosp));
    // pitch
    float sinp = 2.0f * (q.w * q.y - q.z * q.x);

    if (std::fabs(sinp) >= 1.0f)
    {
        pitch = XMConvertToDegrees(std::copysignf(XM_PIDIV2, sinp));
    }
    else
    {
        pitch = XMConvertToDegrees(std::asinf(sinp));
    }
    // yaw
    float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    yaw = XMConvertToDegrees(std::atan2f(siny_cosp, cosy_cosp));
}

void Rotator::SetEuler(TempVector euler) noexcept
{
    XMStoreFloat3(&vec3, euler);
    roll = XMConvertToDegrees(roll);
    pitch = XMConvertToDegrees(pitch);
    yaw = XMConvertToDegrees(yaw);
}

float* Rotator::GetArray() noexcept
{
    return &roll;
}

void Rotator::Combine(const Rotator& other) noexcept
{
    roll += other.roll;
    pitch += other.pitch;
    yaw += other.yaw;
}