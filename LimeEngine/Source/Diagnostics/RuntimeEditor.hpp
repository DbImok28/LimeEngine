// Copyright (C) 2022 Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"
#include "Base/Transform.hpp"

namespace LimeEngine
{
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
		static void Destroy();
		static void Processing(float deltaTime);
		static void Render();
		static void NewPanel(const char* name);
		static void EndPanel();

		static bool Drag(const char* label, char& var, char min = 0, char max = std::numeric_limits<char>::max(), float speed = 1.0f);
		static bool Drag(const char* label, int8& var, int8 min = 0, int8 max = std::numeric_limits<int8>::max(), float speed = 1.0f);
		static bool Drag(const char* label, int16& var, int16 min = 0, int16 max = std::numeric_limits<int16>::max(), float speed = 1.0f);
		static bool Drag(const char* label, int32& var, int32 min = 0, int32 max = std::numeric_limits<int32>::max(), float speed = 1.0f);
		static bool Drag(const char* label, int64& var, int64 min = 0, int64 max = std::numeric_limits<int64>::max(), float speed = 1.0f);
		static bool Drag(const char* label, uint8& var, uint8 min = 0, uint8 max = std::numeric_limits<uint8>::max(), float speed = 1.0f);
		static bool Drag(const char* label, uint16& var, uint16 min = 0, uint16 max = std::numeric_limits<uint16>::max(), float speed = 1.0f);
		static bool Drag(const char* label, uint32& var, uint32 min = 0, uint32 max = std::numeric_limits<uint32>::max(), float speed = 1.0f);
		static bool Drag(const char* label, uint64& var, uint64 min = 0, uint64 max = std::numeric_limits<uint64>::max(), float speed = 1.0f);
		static bool Drag(const char* label, float& var, float min = 0, float max = std::numeric_limits<float>::max(), float speed = 1.0f);
		static bool Drag(const char* label, double& var, double min = 0, double max = std::numeric_limits<double>::max(), float speed = 1.0f);
		static bool Drag(const char* label, Vector& vec, float min = 0, float max = std::numeric_limits<float>::max(), float speed = 1.0f);
		static bool Drag(const char* label, Rotator& rot, float min = 0, float max = std::numeric_limits<float>::max(), float speed = 1.0f);

		static bool Slider(const char* label, char& var, char min = std::numeric_limits<char>::max(), char max = 100);
		static bool Slider(const char* label, int8& var, int8 min = std::numeric_limits<int8>::max(), int8 max = 100);
		static bool Slider(const char* label, int16& var, int16 min = std::numeric_limits<int16>::max(), int16 max = 100);
		static bool Slider(const char* label, int32& var, int32 min = std::numeric_limits<int32>::max(), int32 max = 100);
		static bool Slider(const char* label, int64& var, int64 min = std::numeric_limits<int64>::max(), int64 max = 100);
		static bool Slider(const char* label, uint8& var, uint8 min = std::numeric_limits<uint8>::max(), uint8 max = 100);
		static bool Slider(const char* label, uint16& var, uint16 min = std::numeric_limits<uint16>::max(), uint16 max = 100);
		static bool Slider(const char* label, uint32& var, uint32 min = std::numeric_limits<uint32>::max(), uint32 max = 100);
		static bool Slider(const char* label, uint64& var, uint64 min = std::numeric_limits<uint64>::max(), uint64 max = 100);
		static bool Slider(const char* label, float& var, float min = std::numeric_limits<float>::max(), float max = 1.0f);
		static bool Slider(const char* label, double& var, double min = std::numeric_limits<double>::max(), double max = 1.0);
		static bool Slider(const char* label, Vector& vec, float min = std::numeric_limits<float>::max(), float max = 1.0f);
		static bool Slider(const char* label, Rotator& rot, float min = std::numeric_limits<float>::max(), float max = 1.0f);

		static bool TextField(const char* label, std::string& var);
		static bool TextField(const char* label, char* buf, size_t bufSize);
		static bool TextField(const char* label, const char* hint, std::string& var);
		static bool TextField(const char* label, const char* hint, char* buf, size_t bufSize);
		static bool MultilineTextField(const char* label, std::string& var);
		static bool MultilineTextField(const char* label, char* buf, size_t bufSize);

		static bool CheckBox(const char* label, bool& var);

		static bool Button(const char* label);
		static bool Button(const char* label, bool& varToStore);

		static void Text(const char* str);
		static void Text(const std::string& str);
		static void Text(const char* label, const char* str);
		static void Text(const char* label, const std::string& str);

		static void ShowNotification(NotificationType type, const std::string& title, const std::string& content, int displayTime = 3000);
		static void ShowNotification(NotificationType type, const std::string& content, int displayTime = 3000);
		static void ShowNotification(const std::string& title, const std::string& content, int displayTime = 3000);
		static void ShowNotification(const std::string& content, int displayTime = 3000);

	public:
		static bool Input(const char* label, char& var, char min = 0, char max = std::numeric_limits<char>::max(), float speed = 1.0f);
		static bool Input(const char* label, int8& var, int8 min = 0, int8 max = std::numeric_limits<int8>::max(), float speed = 1.0f);
		static bool Input(const char* label, int16& var, int16 min = 0, int16 max = std::numeric_limits<int16>::max(), float speed = 1.0f);
		static bool Input(const char* label, int32& var, int32 min = 0, int32 max = std::numeric_limits<int32>::max(), float speed = 1.0f);
		static bool Input(const char* label, int64& var, int64 min = 0, int64 max = std::numeric_limits<int64>::max(), float speed = 1.0f);

		static bool Input(const char* label, uint8& var, uint8 min = 0, uint8 max = std::numeric_limits<uint8>::max(), float speed = 1.0f);
		static bool Input(const char* label, uint16& var, uint16 min = 0, uint16 max = std::numeric_limits<uint16>::max(), float speed = 1.0f);
		static bool Input(const char* label, uint32& var, uint32 min = 0, uint32 max = std::numeric_limits<uint32>::max(), float speed = 1.0f);
		static bool Input(const char* label, uint64& var, uint64 min = 0, uint64 max = std::numeric_limits<uint64>::max(), float speed = 1.0f);

		static bool Input(const char* label, float& var, float min = 0, float max = std::numeric_limits<float>::max(), float speed = 1.0f);
		static bool Input(const char* label, double& var, double min = 0, double max = std::numeric_limits<double>::max(), float speed = 1.0f);

		static bool Input(const char* label, bool& var);

		static bool Input(const char* label, std::string& var);
		static bool Input(const char* label, char* buf, size_t bufSize);
		static bool Input(const char* label, const char* hint, std::string& var);
		static bool Input(const char* label, const char* hint, char* buf, size_t bufSize);

		static bool Input(const char* label, Vector& vec, float min = 0, float max = std::numeric_limits<float>::max(), float speed = 1.0f);
		static bool Input(const char* label, Transform& transform);

	private:
		static bool inPanel;
	};
}
