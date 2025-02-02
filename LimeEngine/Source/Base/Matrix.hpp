// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Vector.hpp"

using TempMatrix = DirectX::XMMATRIX;
using TempTransformMatrix = TempMatrix;

namespace LimeEngine
{
	class Matrix
	{
	public:
		Matrix(
			float m00,
			float m01,
			float m02,
			float m03,
			float m10,
			float m11,
			float m12,
			float m13,
			float m20,
			float m21,
			float m22,
			float m23,
			float m30,
			float m31,
			float m32,
			float m33) noexcept : xmMat(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33)
		{}
		Matrix(const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4) noexcept :
			Matrix(v1.x, v1.y, v1.z, 0.0f, v2.x, v2.y, v2.z, 0.0f, v3.x, v3.y, v3.z, 0.0f, v4.x, v4.y, v4.z, 0.0f)
		{}

		static TempTransformMatrix CreateTransformMatrix(const Vector& location, const Rotator& rotation, const Vector& scale)
		{
			return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) * DirectX::XMMatrixRotationQuaternion(rotation.GetQuaternion())
				   * DirectX::XMMatrixTranslation(location.x, location.y, location.z);
		}
		static void DecomposeTransform(const TempTransformMatrix& mat, TempVector& location, TempVector& rotation, TempVector& scale)
		{
			DirectX::XMMatrixDecompose(&scale, &rotation, &location, mat);
		}
		static void DecomposeTransform(const TempTransformMatrix& mat, Vector& location, Rotator& rotation, Vector& scale)
		{
			TempVector tempLocation{}, tempRotation{}, tempScale{};
			DecomposeTransform(mat, tempLocation, tempRotation, tempScale);
			location = tempScale;
			rotation.SetQuaternion(tempRotation);
			scale = tempLocation;
		}

	private:
		union
		{
			float mat[4][4];
			DirectX::XMFLOAT4X4 xmMat;
		};
	};
}
