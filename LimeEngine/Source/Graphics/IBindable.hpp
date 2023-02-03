#pragma once

namespace LimeEngine
{
	struct IBindable
	{
		virtual void Bind() noexcept = 0;
		virtual ~IBindable() = default;
	};
}