// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Vertex.hpp"
#include "RenderData.hpp"
#include "IBindable.hpp"
#include "Texture2D.hpp"
#include "Window/Window.hpp"

namespace LimeEngine
{
	class Mesh;
	class Material;
	class Texture2D;
	class WindowRenderOutput;

	class GraphicFactory
	{
	public:
		virtual ~GraphicFactory() = default;
		virtual std::unique_ptr<MeshRenderData> CreateMeshRenderData(const std::vector<Vertex>& vertices, const std::vector<uint>& indices) const = 0;
		virtual std::unique_ptr<IBindable> CreateVertexShader(const FPath& filePath, MaterialType materialType) const = 0;
		virtual std::unique_ptr<IBindable> CreatePixelShader(const FPath& filePath) const = 0;
		virtual std::unique_ptr<Texture2D> CreateTexture2D(const ResourcePath& resourcePath, const FPath& filePath, TextureType type) const = 0;
		virtual std::unique_ptr<WindowRenderOutput> CreateRenderOutput(Window& window) const = 0;

		std::unique_ptr<Material> CreateMaterial(const GameResourceData& data) const
		{
			static_assert("Not implemented");
			return nullptr;
		}
		std::unique_ptr<Texture2D> CreateTexture2D(const GameResourceData& data) const
		{
			static_assert("Not implemented");
			return nullptr;
		}
		std::unique_ptr<Mesh> CreateMesh(const GameResourceData& data) const
		{
			static_assert("Not implemented");
			return nullptr;
		}

		const std::string& GetMaterialLoadParams() const noexcept
		{
			return materialLoadParams;
		}
		const std::string& GetMeshLoadParams() const noexcept
		{
			return meshLoadParams;
		}
		const std::string& GetTexture2DLoadParams() const noexcept
		{
			return texture2DLoadParams;
		}

	protected:
		std::string materialLoadParams = "";
		std::string meshLoadParams = "";
		std::string texture2DLoadParams = "";
	};
}