#pragma once
#include "DirectXDef.hpp"
#include "../../../CoreBase.hpp"

namespace LimeEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer() noexcept {}
		IndexBuffer(const IndexBuffer& vb) noexcept;
		IndexBuffer(IndexBuffer&& vb) noexcept;
		IndexBuffer& operator=(const IndexBuffer& vb) noexcept;
		IndexBuffer& operator=(IndexBuffer&& vb) noexcept;

		HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const uint* data, uint numVertices) noexcept;
		void Bind() const;
		ID3D11Buffer* Get() const noexcept;
		ID3D11Buffer* const* GetAddressOf() const noexcept;
		uint Count() const noexcept;

	private:
		com_ptr<ID3D11Buffer> buffer;
		uint bufferSize = 0u;
		ID3D11DeviceContext* deviceContext = nullptr;
	};
}