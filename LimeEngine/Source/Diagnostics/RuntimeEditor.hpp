// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Graphics/Systems/DX11/DirectXDef.hpp"

namespace LimeEngine
{
	class RuntimeEditor
	{
	public:
		static void Init(void* hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		static void Processing();
		static void Render();
		static void NewPanel(const char* name);
		static void Drag(const char* label, int& var);
		static void Drag(const char* label, float& var);

	private:
		static bool inPanel;
	};
}
