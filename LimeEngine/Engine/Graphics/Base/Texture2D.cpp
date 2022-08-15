#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(TextureType type, size_t id) noexcept : type(type), id(id) {}

	size_t Texture2D::GetID() const noexcept
	{
		return id;
	}
}