#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Vector
{
public:
	Vector() noexcept;
	Vector(const XMVECTOR& vec) noexcept;
	Vector(const XMFLOAT3& vec) noexcept;
	Vector(const float vec[3]) noexcept;
	Vector(float x, float y, float z) noexcept;
	Vector(const Vector& other) noexcept;
	Vector(Vector&& other) noexcept;

	Vector& operator=(const Vector& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;
	Vector& operator=(const XMVECTOR& vec) noexcept;
	Vector& operator=(const XMFLOAT3& vec) noexcept;

	const Vector operator+(const Vector& v) const noexcept;
	const Vector operator-(const Vector& v) const noexcept;
	const Vector operator*(const Vector& v) const noexcept;
	const Vector operator/(const Vector& v) const noexcept;
	Vector& operator+=(const Vector& v) noexcept;
	Vector& operator-=(const Vector& v) noexcept;
	Vector& operator*=(const Vector& v) noexcept;
	Vector& operator/=(const Vector& v) noexcept;
	Vector operator+() const noexcept;
	Vector operator-() const noexcept;
	bool operator==(const Vector& v) const noexcept;
	bool operator!=(const Vector& v) const noexcept;

	XMVECTOR GetVector() const noexcept;
	const XMFLOAT3& GetFloat3() const noexcept;
	const float* GetArray() const noexcept;

	void Set(const XMVECTOR& vec) noexcept;
	void Set(const XMFLOAT3& vec) noexcept;
	void Set(float x, float y, float z) noexcept;

	void Add(const XMVECTOR& vec) noexcept;
	void Add(const XMFLOAT3& vec) noexcept;
	void Add(float x, float y, float z) noexcept;

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