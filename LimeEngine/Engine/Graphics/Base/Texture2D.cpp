#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(const std::string& gamePath, TextureType type) noexcept : GameResource(gamePath), type(type) {}
}