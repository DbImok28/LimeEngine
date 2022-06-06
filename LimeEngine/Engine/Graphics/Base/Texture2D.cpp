#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(const RenderingSystemDX11& renderer, const std::wstring& filePath, TextureType type, size_t Id) : Id(Id), type(type), renderTexture(renderer, filePath) {}
}