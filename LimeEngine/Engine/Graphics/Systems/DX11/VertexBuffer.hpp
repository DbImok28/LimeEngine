#pragma once
#include "DirectXDef.hpp"
#include "../../../Base/Vertex.hpp"

namespace LimeEngine
{
	class VertexBuffer
	{
	public:
		VertexBuffer() noexcept {}
		VertexBuffer(const VertexBuffer& vb) noexcept;
		VertexBuffer(VertexBuffer&& vb) noexcept;
		VertexBuffer& operator=(const VertexBuffer& vb) noexcept;
		VertexBuffer& operator=(VertexBuffer&& vb) noexcept;

		HRESULT Initialize(ID3D11Device* device, const Vertex* data, UINT vertexCount) noexcept;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		UINT VertexCount() const noexcept;
		const UINT Stride() const noexcept;
		const UINT* StridePtr() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
		UINT stride = sizeof(Vertex);
		UINT bufferSize = 0;
	};
}