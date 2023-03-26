#pragma once
#include <DirectXMath.h>

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

	class Vector
	{
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

	std::ostream& operator<<(std::ostream& os, const Vector& vec);
}