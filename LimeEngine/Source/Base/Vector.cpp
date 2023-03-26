#include "lepch.hpp"
#include "Vector.hpp"

namespace LimeEngine
{
	using namespace DirectX;

	Vector::Vector() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

	Vector::Vector(const TempVector& vec) noexcept
	{
		XMStoreFloat3(&this->vec, vec);
	}

	Vector::Vector(const DirectX::XMFLOAT3& vec) noexcept : vec(vec) {}

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

	Vector& Vector::operator=(const DirectX::XMFLOAT3& vec) noexcept
	{
		this->vec = vec;
		return *this;
	}

	Vector::operator TempVector() const noexcept
	{
		return GetTempVector();
	}

	Vector::operator DirectX::XMFLOAT3() const noexcept
	{
		return vec;
	}

	TempVector Vector::operator+(const Vector& v) const noexcept
	{
		return GetTempVector() + v.GetTempVector();
	}

	TempVector Vector::operator-(const Vector& v) const noexcept
	{
		return GetTempVector() - v.GetTempVector();
	}

	TempVector Vector::operator*(const Vector& v) const noexcept
	{
		return GetTempVector() * v.GetTempVector();
	}

	TempVector Vector::operator/(const Vector& v) const noexcept
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

	const DirectX::XMFLOAT3& Vector::GetFloat3() const noexcept
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

	TempVector Vector::LengthVec() const noexcept
	{
		return Vector::LengthVec(*this);
	}

	float Vector::Length() const noexcept
	{
		return Vector::Length(*this);
	}

	void Vector::Normalize() noexcept
	{
		*this = Vector::Normalize(*this);
	}

	TempVector Vector::Cross(const TempVector& v) const noexcept
	{
		return Vector::Cross(*this, v);
	}

	TempVector Vector::DotVec(const TempVector& v) const noexcept
	{
		return Vector::DotVec(*this, v);
	}

	float Vector::Dot(const TempVector& v) const noexcept
	{
		return Vector::Dot(*this, v);
	}

	// static

	TempVector Vector::MakeTempVector(const Vector& v) noexcept
	{
		return XMLoadFloat3(&v.vec);
	}

	TempVector Vector::MakeTempVector(float x, float y, float z) noexcept
	{
		Vector v(x, y, z);
		return XMLoadFloat3(&v.vec);
	}

	TempVector Vector::LengthVec(const TempVector& v) noexcept
	{
		return XMVector3Length(v);
	}

	float Vector::Length(const TempVector& v) noexcept
	{
		return XMVectorGetX(Vector::LengthVec(v));
	}

	TempVector Vector::Normalize(const TempVector& v) noexcept
	{
		return XMVector3Normalize(v);
	}

	TempVector Vector::Cross(const TempVector& v1, const TempVector& v2) noexcept
	{
		return XMVector3Cross(v1, v2);
	}

	TempVector Vector::DotVec(const TempVector& v1, const TempVector& v2) noexcept
	{
		return XMVector3Dot(v1, v2);
	}

	float Vector::Dot(const TempVector& v1, const TempVector& v2) noexcept
	{
		return XMVectorGetX(Vector::DotVec(v1, v2));
	}

	std::string Vector::ToString() const noexcept
	{
		return std::format("x: {} \ty: {}\t z: {}", x, y, z);
	}

	std::ostream& operator<<(std::ostream& os, const Vector& vec)
	{
		os << vec.ToString();
		return os;
	}
}