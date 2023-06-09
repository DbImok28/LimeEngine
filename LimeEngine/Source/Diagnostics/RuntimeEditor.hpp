// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Transform.hpp"

namespace LimeEngine
{
	class InputDevice;
	class Event;

	enum class NotificationType
	{
		None,
		Success,
		Warning,
		Error,
		Info
	};

	std::string NotificationTypeToString(NotificationType type) noexcept;

	class RuntimeEditor
	{
	public:
#if defined(LE_ENABLE_RENDER_API_DX11)
		static void Init(void* hWnd, void* device, void* deviceContext);
#endif
	private:
		static void SetDefaultTheme();

	public:
		static void Destroy();
		static void Processing(float deltaTime);
		static void Render();
		static void NewPanel(const std::string& name);
		static void EndPanel();

		static bool Drag(const std::string& label, char& var, char min = 0, char max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, int8& var, int8 min = 0, int8 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, int16& var, int16 min = 0, int16 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, int32& var, int32 min = 0, int32 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, int64& var, int64 min = 0, int64 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, uint8& var, uint8 min = 0, uint8 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, uint16& var, uint16 min = 0, uint16 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, uint32& var, uint32 min = 0, uint32 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, uint64& var, uint64 min = 0, uint64 max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, float& var, float min = 0, float max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, double& var, double min = 0, double max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, Vector& vec, float min = 0, float max = 0, float speed = 1.0f);
		static bool Drag(const std::string& label, Rotator& rot, float min = 0, float max = 0, float speed = 1.0f);

		static bool Slider(const std::string& label, char& var, char min = 0, char max = 100);
		static bool Slider(const std::string& label, int8& var, int8 min = 0, int8 max = 100);
		static bool Slider(const std::string& label, int16& var, int16 min = 0, int16 max = 100);
		static bool Slider(const std::string& label, int32& var, int32 min = 0, int32 max = 100);
		static bool Slider(const std::string& label, int64& var, int64 min = 0, int64 max = 100);
		static bool Slider(const std::string& label, uint8& var, uint8 min = 0, uint8 max = 100);
		static bool Slider(const std::string& label, uint16& var, uint16 min = 0, uint16 max = 100);
		static bool Slider(const std::string& label, uint32& var, uint32 min = 0, uint32 max = 100);
		static bool Slider(const std::string& label, uint64& var, uint64 min = 0, uint64 max = 100);
		static bool Slider(const std::string& label, float& var, float min = 0, float max = 1.0f);
		static bool Slider(const std::string& label, double& var, double min = 0, double max = 1.0);
		static bool Slider(const std::string& label, Vector& vec, float min = 0, float max = 1.0f);
		static bool Slider(const std::string& label, Rotator& rot, float min = 0, float max = 1.0f);

		static bool TextField(const std::string& label, std::string& var);
		static bool TextField(const std::string& label, char* buf, size_t bufSize);
		static bool TextField(const std::string& label, const std::string& hint, std::string& var);
		static bool TextField(const std::string& label, const std::string& hint, char* buf, size_t bufSize);
		static bool MultilineTextField(const std::string& label, std::string& var);
		static bool MultilineTextField(const std::string& label, char* buf, size_t bufSize);

		static bool CheckBox(const std::string& label, bool& var);

		static bool Button(const std::string& label);
		static bool Button(const std::string& label, bool& varToStore);

		static void Text(const std::string& str);
		static void Text(const std::string& label, const std::string& str);

		static void ShowNotification(NotificationType type, const std::string& title, const std::string& content, int displayTime = 3000);
		static void ShowNotification(NotificationType type, const std::string& content, int displayTime = 3000);
		static void ShowNotification(const std::string& title, const std::string& content, int displayTime = 3000);
		static void ShowNotification(const std::string& content, int displayTime = 3000);

	public:
		static bool Input(const std::string& label, char& var, char min = 0, char max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, int8& var, int8 min = 0, int8 max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, int16& var, int16 min = 0, int16 max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, int32& var, int32 min = 0, int32 max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, int64& var, int64 min = 0, int64 max = 0, float speed = 1.0f);

		static bool Input(const std::string& label, uint8& var, uint8 min = 0, uint8 max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, uint16& var, uint16 min = 0, uint16 max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, uint32& var, uint32 min = 0, uint32 max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, uint64& var, uint64 min = 0, uint64 max = 0, float speed = 1.0f);

		static bool Input(const std::string& label, float& var, float min = 0, float max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, double& var, double min = 0, double max = 0, float speed = 1.0f);

		static bool Input(const std::string& label, bool& var);

		static bool Input(const std::string& label, std::string& var);
		static bool Input(const std::string& label, char* buf, size_t bufSize);
		static bool Input(const std::string& label, const std::string& hint, std::string& var);
		static bool Input(const std::string& label, const std::string& hint, char* buf, size_t bufSize);

		static bool Input(const std::string& label, Vector& vec, float min = 0, float max = 0, float speed = 1.0f);
		static bool Input(const std::string& label, Transform& transform);

	private:
		static bool inPanel;
	};
}
