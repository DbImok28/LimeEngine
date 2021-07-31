#include "Vector.hpp"
#include <type_traits>

Vector::Vector() noexcept {}

Vector::Vector(const XMVECTOR& vec) noexcept
{
	XMStoreFloat3(&this->vec, vec);
}

Vector::Vector(const XMFLOAT3& vec) noexcept : vec(vec) {}

Vector::Vector(const float vec[3]) noexcept : vec(vec) {}

Vector::Vector(float x, float y, float z) noexcept : vec(x, y, z) {}

Vector::Vector(const Vector& other) noexcept : vec(other.vec) {}

Vector::Vector(Vector&& other) noexcept : vec(std::move(other.vec)) {}

Vector& Vector::operator=(const Vector& other) noexcept
{
	if (this != &other)
	{
		this->vec = other.vec;
	}
	return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
	if (this != &other)
	{
		this->vec = std::move(other.vec);
	}
	return *this;
}

Vector& Vector::operator=(const XMVECTOR& vec) noexcept
{
	XMStoreFloat3(&this->vec, vec);
	return *this;
}

Vector& Vector::operator=(const XMFLOAT3& vec) noexcept
{
	this->vec = vec;
	return *this;
}

const Vector Vector::operator+(const Vector& v) const noexcept
{
	return Vector(vec.x + v.vec.x, vec.y + v.vec.y, vec.z + v.vec.z);
}

const Vector Vector::operator-(const Vector& v) const noexcept
{
	return Vector(vec.x - v.vec.x, vec.y - v.vec.y, vec.z - v.vec.z);
}

const Vector Vector::operator*(const Vector& v) const noexcept
{
	return Vector(vec.x * v.vec.x, vec.y * v.vec.y, vec.z * v.vec.z);
}

const Vector Vector::operator/(const Vector& v) const noexcept
{
	return Vector(vec.x / v.vec.x, vec.y / v.vec.y, vec.z / v.vec.z);
}

Vector& Vector::operator+=(const Vector& v) noexcept
{
	vec.x += v.vec.x;
	vec.y += v.vec.y;
	vec.z += v.vec.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& v) noexcept
{
	vec.x -= v.vec.x;
	vec.y -= v.vec.y;
	vec.z -= v.vec.z;
	return *this;
}

Vector& Vector::operator*=(const Vector& v) noexcept
{
	vec.x *= v.vec.x;
	vec.y *= v.vec.y;
	vec.z *= v.vec.z;
	return *this;
}

Vector& Vector::operator/=(const Vector& v) noexcept
{
	vec.x /= v.vec.x;
	vec.y /= v.vec.y;
	vec.z /= v.vec.z;
	return *this;
}

Vector Vector::operator+() const noexcept
{
	return Vector(*this);
}

Vector Vector::operator-() const noexcept
{
	return Vector(-vec.x, -vec.y, -vec.z);
}

bool Vector::operator==(const Vector& v) const noexcept
{
	return (vec.x == v.vec.x && vec.y == v.vec.y && vec.z == v.vec.z);
}

bool Vector::operator!=(const Vector& v) const noexcept
{
	return !(*this == v);
}

XMVECTOR Vector::GetVector() const noexcept
{
	return XMLoadFloat3(&this->vec);
}

const XMFLOAT3& Vector::GetFloat3() const noexcept
{
	return vec;
}

const float* Vector::GetArray() const noexcept
{
	return &vec.x;
}

void Vector::Set(const XMVECTOR& vec) noexcept
{
	XMStoreFloat3(&this->vec, vec);
}

void Vector::Set(const XMFLOAT3& vec) noexcept
{
	this->vec = vec;
}

void Vector::Set(float x, float y, float z) noexcept
{
	vec = XMFLOAT3(x, y, z);
}

void Vector::Add(const XMVECTOR& vec) noexcept
{
	XMStoreFloat3(&this->vec, GetVector() + vec);
}

void Vector::Add(const XMFLOAT3& vec) noexcept
{
	this->vec.x += vec.x;
	this->vec.y += vec.y;
	this->vec.z += vec.z;
}

void Vector::Add(float x, float y, float z) noexcept
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
}