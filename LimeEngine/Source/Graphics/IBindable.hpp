#pragma once

namespace LimeEngine
{
	struct IBindable
	{
		virtual void Bind() = 0;
		virtual ~IBindable() = default;
	};
}