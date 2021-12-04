#pragma once
#include <DirectXMath.h>

using namespace DirectX;

using TempVector = XMVECTOR;

class Vector
{
public:
	Vector() noexcept;
	Vector(const TempVector& vec) noexcept;
	Vector(const XMFLOAT3& vec) noexcept;
	Vector(const float vec[3]) noexcept;
	Vector(float x, float y, float z) noexcept;
	Vector(const Vector& other) noexcept;
	Vector(Vector&& other) noexcept;

	Vector& operator=(const Vector& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;
	Vector& operator=(const TempVector& vec) noexcept;
	Vector& operator=(const XMFLOAT3& vec) noexcept;

	operator TempVector() const noexcept;
	operator XMFLOAT3() const noexcept;

	TempVector operator+(const Vector& v) noexcept;
	TempVector operator-(const Vector& v) noexcept;
	TempVector operator*(const Vector& v) noexcept;
	TempVector operator/(const Vector& v) noexcept;
	Vector& operator+=(const TempVector& v) noexcept;
	Vector& operator-=(const TempVector& v) noexcept;
	Vector& operator*=(const TempVector& v) noexcept;
	Vector& operator/=(const TempVector& v) noexcept;
	const Vector& operator+() const noexcept;
	Vector operator-() const noexcept;
	bool operator==(const Vector& v) const noexcept;
	bool operator!=(const Vector& v) const noexcept;

	TempVector GetTempVector() const noexcept;
	const XMFLOAT3& GetFloat3() const noexcept;
	float* GetArray() noexcept;
	void Add(const TempVector& v) noexcept;
	void Subtract(const TempVector& v) noexcept;
	void Multiply(const TempVector& v) noexcept;
	void Divide(const TempVector& v) noexcept;

	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		XMFLOAT3 vec{};
	};
};