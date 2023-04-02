#include "lepch.hpp"
#include "RuntimeEditor.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "Graphics/API/DX11/DirectXDef.hpp"
#endif

#if defined(LE_ENABLE_IMGUI)
	#include "imgui.h"
	#include "misc/cpp/imgui_stdlib.h"
	#include "backends/imgui_impl_win32.h"
	#include "backends/imgui_impl_dx11.h"
	#include "imgui-notify/imgui_notify.h"
	#include "imgui-notify/tahoma.h"
#endif

namespace LimeEngine
{
	std::string NotificationTypeToString(NotificationType type) noexcept
	{
		switch (type)
		{
			case LimeEngine::NotificationType::None: return "None";
			case LimeEngine::NotificationType::Success: return "Success";
			case LimeEngine::NotificationType::Warning: return "Warning";
			case LimeEngine::NotificationType::Error: return "Error";
			case LimeEngine::NotificationType::Info: return "Info";
			default: return "Unknown";
		}
	}

	bool RuntimeEditor::inPanel = false;

#if defined(LE_ENABLE_RENDER_API_DX11)
	void RuntimeEditor::Init(void* hWnd, void* device, void* deviceContext)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(device), reinterpret_cast<ID3D11DeviceContext*>(deviceContext));
		ImGui::StyleColorsDark();

		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 15.f, &font_cfg);
		ImGui::MergeIconsWithLatestFont(16.f, false);
	}

	void RuntimeEditor::Destroy()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void RuntimeEditor::Processing(float deltaTime)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::GetIO().DeltaTime = deltaTime;
		inPanel = false;
	}

	void RuntimeEditor::Render()
	{
		if (inPanel)
		{
			ImGui::End();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1);

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
#else
	void RuntimeEditor::Destroy() {}
	void RuntimeEditor::Processing(float deltaTime) {}
	void RuntimeEditor::Render() {}
#endif

	void RuntimeEditor::NewPanel(const char* name)
	{
		if (inPanel)
		{
			ImGui::End();
		}
		ImGui::Begin(name);
		inPanel = true;
	}

	void RuntimeEditor::EndPanel()
	{
		if (inPanel)
		{
			ImGui::End();
		}
		inPanel = false;
	}

	void RuntimeEditor::Drag(const char* label, char& var, char min, char max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_S8, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, int8& var, int8 min, int8 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_S8, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, int16& var, int16 min, int16 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_S16, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, int32& var, int32 min, int32 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_S32, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, int64& var, int64 min, int64 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_S64, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, uint8& var, uint8 min, uint8 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_U8, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, uint16& var, uint16 min, uint16 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_U16, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, uint32& var, uint32 min, uint32 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_U32, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, uint64& var, uint64 min, uint64 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_U64, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, float& var, float min, float max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_Float, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, double& var, double min, double max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragScalar(label, ImGuiDataType_Double, &var, speed, &min, &max);
	}

	void RuntimeEditor::Drag(const char* label, Vector& vec, float min, float max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragFloat3(label, reinterpret_cast<float*>(&vec), speed, min, max);
	}

	void RuntimeEditor::Drag(const char* label, Rotator& rot, float min, float max, float speed)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragFloat3(label, reinterpret_cast<float*>(&rot), speed, min, max);
	}

	void RuntimeEditor::Slider(const char* label, char& var, char min, char max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_S8, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, int8& var, int8 min, int8 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_S8, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, int16& var, int16 min, int16 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_S16, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, int32& var, int32 min, int32 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_S32, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, int64& var, int64 min, int64 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_S64, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, uint8& var, uint8 min, uint8 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_U8, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, uint16& var, uint16 min, uint16 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_U16, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, uint32& var, uint32 min, uint32 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_U32, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, uint64& var, uint64 min, uint64 max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_U64, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, float& var, float min, float max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_Float, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, double& var, double min, double max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderScalar(label, ImGuiDataType_Double, &var, &min, &max);
	}

	void RuntimeEditor::Slider(const char* label, Vector& vec, float min, float max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderFloat3(label, reinterpret_cast<float*>(&vec), min, max);
	}

	void RuntimeEditor::Slider(const char* label, Rotator& rot, float min, float max)
	{
		if (!inPanel) NewPanel("None");
		ImGui::SliderFloat3(label, reinterpret_cast<float*>(&rot), min, max);
	}

	void RuntimeEditor::TextField(const char* label, std::string& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::InputText(label, &var);
	}

	void RuntimeEditor::TextField(const char* label, char* buf, size_t bufSize)
	{
		if (!inPanel) NewPanel("None");
		ImGui::InputText(label, buf, bufSize);
	}

	void RuntimeEditor::TextField(const char* label, const char* hint, std::string& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::InputTextWithHint(label, hint, &var);
	}

	void RuntimeEditor::TextField(const char* label, const char* hint, char* buf, size_t bufSize)
	{
		if (!inPanel) NewPanel("None");
		ImGui::InputTextWithHint(label, hint, buf, bufSize);
	}

	void RuntimeEditor::MultilineTextField(const char* label, std::string& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::InputTextMultiline(label, &var);
	}

	void RuntimeEditor::MultilineTextField(const char* label, char* buf, size_t bufSize)
	{
		if (!inPanel) NewPanel("None");
		ImGui::InputText(label, buf, bufSize);
	}

	bool RuntimeEditor::CheckBox(const char* label, bool& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::Checkbox(label, &var);
		return var;
	}

	bool RuntimeEditor::Button(const char* label)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::Button(label);
	}

	bool RuntimeEditor::Button(const char* label, bool& varToStore)
	{
		if (Button(label)) varToStore = !varToStore;
		return varToStore;
	}

	void RuntimeEditor::Text(const char* str)
	{
		if (!inPanel) NewPanel("None");
		ImGui::Text(str);
	}

	void RuntimeEditor::Text(const std::string& str)
	{
		Text(str.c_str());
	}

	void RuntimeEditor::Text(const char* label, const char* str)
	{
		if (!inPanel) NewPanel("None");
		ImGui::LabelText(label, str);
	}

	void RuntimeEditor::Text(const char* label, const std::string& str)
	{
		Text(label, str.c_str());
	}

	void RuntimeEditor::ShowNotification(NotificationType type, const std::string& title, const std::string& content, int displayTime)
	{
		ImGuiToast toast(static_cast<ImGuiToastType_>(type), displayTime);
		toast.set_title(title.c_str());
		toast.set_content(content.c_str());
		ImGui::InsertNotification(toast);
	}

	void RuntimeEditor::ShowNotification(NotificationType type, const std::string& content, int displayTime)
	{
		ShowNotification(type, NotificationTypeToString(type), content.c_str(), displayTime);
	}

	void RuntimeEditor::ShowNotification(const std::string& title, const std::string& content, int displayTime)
	{
		ShowNotification(NotificationType::None, title.c_str(), content.c_str(), displayTime);
	}

	void RuntimeEditor::ShowNotification(const std::string& content, int displayTime)
	{
		ImGuiToast toast(static_cast<ImGuiToastType_>(NotificationType::None), displayTime);
		toast.set_content(content.c_str());
		ImGui::InsertNotification(toast);
	}

	// ---------

	void RuntimeEditor::Input(const char* label, char& var, char min, char max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, int8& var, int8 min, int8 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, int16& var, int16 min, int16 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, int32& var, int32 min, int32 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, int64& var, int64 min, int64 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, uint8& var, uint8 min, uint8 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, uint16& var, uint16 min, uint16 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, uint32& var, uint32 min, uint32 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, uint64& var, uint64 min, uint64 max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, float& var, float min, float max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, double& var, double min, double max, float speed)
	{
		Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const char* label, bool& var)
	{
		return CheckBox(label, var);
	}

	void RuntimeEditor::Input(const char* label, std::string& var)
	{
		TextField(label, var);
	}

	void RuntimeEditor::Input(const char* label, char* buf, size_t bufSize)
	{
		TextField(label, buf, bufSize);
	}

	void RuntimeEditor::Input(const char* label, const char* hint, std::string& var)
	{
		TextField(label, hint, var);
	}

	void RuntimeEditor::Input(const char* label, const char* hint, char* buf, size_t bufSize)
	{
		TextField(label, hint, buf, bufSize);
	}

	void RuntimeEditor::Input(const char* label, Vector& vec, float min, float max, float speed)
	{
		Drag(label, vec, min, max, speed);
	}

	void RuntimeEditor::Input(const char* label, Transform& transform)
	{
		if (!inPanel) NewPanel("None");
		Text(label);
		ImGui::PushID(label);
		Drag("Location", transform.location);
		Drag("Rotation", transform.rotation);
		Drag("Scale", transform.scale);
		ImGui::PopID();
	}
}
