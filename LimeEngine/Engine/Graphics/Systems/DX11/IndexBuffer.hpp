#pragma once
#include "DirectXDef.hpp"

namespace LimeEngine
{
	class IndexBuffer
	{
	private:
		com_ptr<ID3D11Buffer> buffer;
		UINT bufferSize = 0;
	public:
		IndexBuffer() noexcept {}
		IndexBuffer(const IndexBuffer& vb) noexcept;
		IndexBuffer(IndexBuffer&& vb) noexcept;
		IndexBuffer& operator=(const IndexBuffer& vb) noexcept;
		IndexBuffer& operator=(IndexBuffer&& vb) noexcept;

		HRESULT Initialize(ID3D11Device* device, const DWORD* data, UINT numVertices) noexcept;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		UINT Count() const noexcept;
	};
}