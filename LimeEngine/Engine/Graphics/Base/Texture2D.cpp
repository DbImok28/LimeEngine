#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(std::string path, TextureType type) noexcept : GameResource(path), type(type) {}
}