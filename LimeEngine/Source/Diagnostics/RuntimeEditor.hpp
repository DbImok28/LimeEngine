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

		static void Drag(const char* label, char& var, char min = 0, char max = 0, float speed = 1.0f);
		static void Drag(const char* label, int8& var, int8 min = 0, int8 max = 0, float speed = 1.0f);
		static void Drag(const char* label, int16& var, int16 min = 0, int16 max = 0, float speed = 1.0f);
		static void Drag(const char* label, int32& var, int32 min = 0, int32 max = 0, float speed = 1.0f);
		static void Drag(const char* label, int64& var, int64 min = 0, int64 max = 0, float speed = 1.0f);

		static void Drag(const char* label, uint8& var, uint8 min = 0, uint8 max = 0, float speed = 1.0f);
		static void Drag(const char* label, uint16& var, uint16 min = 0, uint16 max = 0, float speed = 1.0f);
		static void Drag(const char* label, uint32& var, uint32 min = 0, uint32 max = 0, float speed = 1.0f);
		static void Drag(const char* label, uint64& var, uint64 min = 0, uint64 max = 0, float speed = 1.0f);

		static void Drag(const char* label, float& var, float min = 0, float max = 0, float speed = 1.0f);
		static void Drag(const char* label, double& var, double min = 0, double max = 0, float speed = 1.0f);

	private:
		static bool inPanel;
	};
}
