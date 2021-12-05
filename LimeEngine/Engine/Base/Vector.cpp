#include "Vector.hpp"
#include <type_traits>

namespace LimeEngine
{
	Vector::Vector() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

	Vector::Vector(const TempVector& vec) noexcept
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

	Vector& Vector::operator=(const TempVector& vec) noexcept
	{
		XMStoreFloat3(&this->vec, vec);
		return *this;
	}

	Vector& Vector::operator=(const XMFLOAT3& vec) noexcept
	{
		this->vec = vec;
		return *this;
	}

	Vector::operator TempVector() const noexcept
	{
		return XMLoadFloat3(&this->vec);
	}

	Vector::operator XMFLOAT3() const noexcept
	{
		return vec;
	}

	TempVector Vector::operator+(const Vector& v) noexcept
	{
		return GetTempVector() + v.GetTempVector();
	}

	TempVector Vector::operator-(const Vector& v) noexcept
	{
		return GetTempVector() - v.GetTempVector();
	}

	TempVector Vector::operator*(const Vector& v) noexcept
	{
		return GetTempVector() * v.GetTempVector();
	}

	TempVector Vector::operator/(const Vector& v) noexcept
	{
		return GetTempVector() / v.GetTempVector();
	}

	Vector& Vector::operator+=(const TempVector& v) noexcept
	{
		*this = GetTempVector() + v;
		return *this;
	}

	Vector& Vector::operator-=(const TempVector& v) noexcept
	{
		*this = GetTempVector() - v;
		return *this;
	}

	Vector& Vector::operator*=(const TempVector& v) noexcept
	{
		*this = GetTempVector() * v;
		return *this;
	}

	Vector& Vector::operator/=(const TempVector& v) noexcept
	{
		*this = GetTempVector() / v;
		return *this;
	}

	const Vector& Vector::operator+() const noexcept
	{
		return *this;
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

	TempVector Vector::GetTempVector() const noexcept
	{
		return XMLoadFloat3(&this->vec);
	}

	const XMFLOAT3& Vector::GetFloat3() const noexcept
	{
		return vec;
	}

	float* Vector::GetArray() noexcept
	{
		return &x;
	}

	void Vector::Add(const TempVector& v) noexcept
	{
		*this = GetTempVector() + v;
	}

	void Vector::Subtract(const TempVector& v) noexcept
	{
		*this = GetTempVector() - v;
	}

	void Vector::Multiply(const TempVector& v) noexcept
	{
		*this = GetTempVector() * v;
	}

	void Vector::Divide(const TempVector& v) noexcept
	{
		*this = GetTempVector() / v;
	}
}