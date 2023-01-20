// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "LimeEngine.hpp"

namespace Sandbox
{
	class SandboxApplication : public LimeEngine::Application
	{
	public:
		SandboxApplication() {}
		~SandboxApplication() {}
	};
}

std::unique_ptr<LimeEngine::Application> LimeEngine::CreateApplication()
{
	return std::make_unique<Sandbox::SandboxApplication>();
}
