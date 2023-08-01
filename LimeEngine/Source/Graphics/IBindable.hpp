// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once

namespace LimeEngine
{
	struct IBindable
	{
		virtual void Bind() = 0;
		virtual ~IBindable() = default;
	};
}