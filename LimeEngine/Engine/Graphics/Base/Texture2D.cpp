#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(ID3D11Device* device, const std::wstring& filePath, TextureType type, size_t Id) : Id(Id), type(type), renderTexture(device, filePath) {}
}