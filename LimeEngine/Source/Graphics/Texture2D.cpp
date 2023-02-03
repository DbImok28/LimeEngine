#include "lepch.hpp"
#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept : GameResource(resourcePath), type(type) {}
}