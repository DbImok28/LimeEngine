// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "Texture2D.hpp"

namespace LimeEngine
{
	Texture2D::Texture2D(const ResourcePath& resourcePath, TextureType type) noexcept : GameResource(resourcePath), type(type) {}
}