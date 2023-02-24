// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Transform.hpp"

namespace LimeEngine
{
	class RuntimeEditor
	{
	public:
#if defined(LE_ENABLE_RENDER_API_DX11)
		static void Init(void* hWnd, void* device, void* deviceContext);
#endif
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

		static void Drag(const char* label, Vector& vec, float min = 0, float max = 0, float speed = 1.0f);
		static void Drag(const char* label, Rotator& rot, float min = 0, float max = 0, float speed = 1.0f);

		static void TextField(const char* label, std::string& var);
		static void TextField(const char* label, char* buf, size_t bufSize);
		static void TextField(const char* label, const char* hint, std::string& var);
		static void TextField(const char* label, const char* hint, char* buf, size_t bufSize);
		static void MultilineTextField(const char* label, std::string& var);
		static void MultilineTextField(const char* label, char* buf, size_t bufSize);
		static void CheckBox(const char* label, bool& var);

	public:
		static void Input(const char* label, char& var, char min = 0, char max = 0, float speed = 1.0f);
		static void Input(const char* label, int8& var, int8 min = 0, int8 max = 0, float speed = 1.0f);
		static void Input(const char* label, int16& var, int16 min = 0, int16 max = 0, float speed = 1.0f);
		static void Input(const char* label, int32& var, int32 min = 0, int32 max = 0, float speed = 1.0f);
		static void Input(const char* label, int64& var, int64 min = 0, int64 max = 0, float speed = 1.0f);

		static void Input(const char* label, uint8& var, uint8 min = 0, uint8 max = 0, float speed = 1.0f);
		static void Input(const char* label, uint16& var, uint16 min = 0, uint16 max = 0, float speed = 1.0f);
		static void Input(const char* label, uint32& var, uint32 min = 0, uint32 max = 0, float speed = 1.0f);
		static void Input(const char* label, uint64& var, uint64 min = 0, uint64 max = 0, float speed = 1.0f);

		static void Input(const char* label, float& var, float min = 0, float max = 0, float speed = 1.0f);
		static void Input(const char* label, double& var, double min = 0, double max = 0, float speed = 1.0f);

		static void Input(const char* label, bool& var);

		static void Input(const char* label, std::string& var);
		static void Input(const char* label, char* buf, size_t bufSize);
		static void Input(const char* label, const char* hint, std::string& var);
		static void Input(const char* label, const char* hint, char* buf, size_t bufSize);

		static void Input(const char* label, Vector& vec, float min = 0, float max = 0, float speed = 1.0f);
		static void Input(const char* label, Transform& transform);

	private:
		static bool inPanel;
	};
}
