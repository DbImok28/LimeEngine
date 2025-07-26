// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include <DirectXMath.h>
#include <format>

namespace LimeEngine
{
	enum class AxisOrder
	{
		XYZ,
		XZY,
		YXZ,
		YZX,
		ZXY,
		ZYX
	};

	using TempVector = DirectX::XMVECTOR;

	template <typename T>
	class CustomVector2D
	{
	public:
		CustomVector2D() noexcept : x(0), y(0) {}
		CustomVector2D(T x, T y) noexcept : x(x), y(y) {}
		CustomVector2D(const T vec[2]) noexcept : x(vec[0]), y(vec[1]) {}

		std::string ToString() const noexcept
		{
			return std::format("x:{:< 8} y:{:< 8}", x, y);
		}

		T* GetArray() noexcept
		{
			return &x;
		}
		uint8 GetSize() noexcept
		{
			return 2u;
		}

	public:
		T x;
		T y;
	};

	using IntVector2D = CustomVector2D<int32>;
	using UIntVector2D = CustomVector2D<uint32>;
	using Vector2D = CustomVector2D<float>;

	template <typename T>
	class CustomVector4D
	{
	public:
		CustomVector4D() noexcept : x(0), y(0), z(0), w(0) {}
		CustomVector4D(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) {}
		CustomVector4D(const T vec[4]) noexcept : x(vec[0]), y(vec[1]), z(vec[2]), w(vec[3]) {}

		std::string ToString() const noexcept
		{
			return std::format("x:{:< 8} y:{:< 8} z:{:< 8} w:{:< 8}", x, y, z, w);
		}

		T* GetArray() noexcept
		{
			return &x;
		}
		uint8 GetSize() noexcept
		{
			return 4u;
		}

	public:
		T x;
		T y;
		T z;
		T w;
	};

	using IntVector4D = CustomVector4D<int32>;
	using UIntVector4D = CustomVector4D<uint32>;
	using Vector4D = CustomVector4D<float>;

	class Vector
	{
	public:
		static inline const TempVector ZeroVector = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		static inline const TempVector OneVector = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);

		static inline const TempVector UpVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		static inline const TempVector DownVector = DirectX::XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);

		static inline const TempVector ForwardVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		static inline const TempVector BackwardVector = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);

		static inline const TempVector RightVector = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		static inline const TempVector LeftVector = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

		static inline const TempVector XAxisVector = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		static inline const TempVector YAxisVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		static inline const TempVector ZAxisVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	public:
		Vector() noexcept;
		Vector(const TempVector& vec) noexcept;
		Vector(const DirectX::XMFLOAT3& vec) noexcept;
		Vector(const float vec[3]) noexcept;
		Vector(float x, float y, float z) noexcept;
		Vector(const Vector& other) noexcept;
		Vector(Vector&& other) noexcept;

		Vector& operator=(const Vector& other) noexcept;
		Vector& operator=(Vector&& other) noexcept;
		Vector& operator=(const TempVector& vec) noexcept;
		Vector& operator=(const DirectX::XMFLOAT3& vec) noexcept;

		operator TempVector() const noexcept;
		operator DirectX::XMFLOAT3() const noexcept;

		TempVector operator+(const Vector& v) const noexcept;
		TempVector operator-(const Vector& v) const noexcept;
		TempVector operator*(const Vector& v) const noexcept;
		TempVector operator/(const Vector& v) const noexcept;
		Vector& operator+=(const TempVector& v) noexcept;
		Vector& operator-=(const TempVector& v) noexcept;
		Vector& operator*=(const TempVector& v) noexcept;
		Vector& operator/=(const TempVector& v) noexcept;
		const Vector& operator+() const noexcept;
		Vector operator-() const noexcept;
		bool operator==(const Vector& v) const noexcept;
		bool operator!=(const Vector& v) const noexcept;

		TempVector GetTempVector() const noexcept;
		const DirectX::XMFLOAT3& GetFloat3() const noexcept;
		float* GetArray() noexcept;

		void Add(const TempVector& v) noexcept;
		void Subtract(const TempVector& v) noexcept;
		void Multiply(const TempVector& v) noexcept;
		void Divide(const TempVector& v) noexcept;
		TempVector LengthVec() const noexcept;
		float Length() const noexcept;
		void Normalize() noexcept;
		TempVector Cross(const TempVector& v) const noexcept;
		TempVector DotVec(const TempVector& v) const noexcept;
		float Dot(const TempVector& v) const noexcept;
		std::string ToString() const noexcept;

		static TempVector MakeTempVector(const Vector& v) noexcept;
		static TempVector MakeTempVector(float x, float y, float z) noexcept;

		static TempVector LengthVec(const TempVector& v) noexcept;
		static float Length(const TempVector& v) noexcept;
		static TempVector Normalize(const TempVector& v) noexcept;
		static TempVector Cross(const TempVector& v1, const TempVector& v2) noexcept;
		static TempVector DotVec(const TempVector& v1, const TempVector& v2) noexcept;
		static float Dot(const TempVector& v1, const TempVector& v2) noexcept;
		Vector GetByOrder(AxisOrder order) const noexcept
		{
			switch (order)
			{
				case AxisOrder::XYZ: return { x, y, z };
				case AxisOrder::XZY: return { x, z, y };
				case AxisOrder::YXZ: return { y, x, z };
				case AxisOrder::YZX: return { y, z, x };
				case AxisOrder::ZXY: return { z, x, y };
				case AxisOrder::ZYX: return { z, y, x };
				default: return { x, y, z };
			}
		}

		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			DirectX::XMFLOAT3 vec{};
		};
	};

	std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
	std::ostream& operator<<(std::ostream& os, const Vector& vec);
}

template <typename T>
struct std::formatter<LimeEngine::CustomVector2D<T>> : std::formatter<std::string>
{
	auto format(LimeEngine::CustomVector2D<T> vec, auto& ctx) const
	{
		return std::format_to(ctx.out(), "x:{:< 8} y:{:< 8}", vec.x, vec.y);
	}
};

template <>
struct std::formatter<LimeEngine::Vector> : std::formatter<std::string>
{
	auto format(LimeEngine::Vector vec, auto& ctx) const
	{
		return std::format_to(ctx.out(), "x:{:< 8} y:{:< 8} z:{:< 8}", vec.x, vec.y, vec.z);
	}
};
