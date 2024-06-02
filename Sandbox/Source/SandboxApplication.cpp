// Copyright (C) Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "LimeEngine.hpp"

namespace Sandbox
{
	class SandboxApplication : public LimeEngine::Application
	{
	};
}

LimeEngine::URef<LimeEngine::Application> LimeEngine::CreateApplication()
{
	return MakeUnique<Sandbox::SandboxApplication>();
}
