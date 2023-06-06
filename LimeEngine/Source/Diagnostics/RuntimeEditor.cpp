#include "lepch.hpp"
#include "RuntimeEditor.hpp"
#include "Input/InputDevice.hpp"

#if defined(LE_ENABLE_RENDER_API_DX11)
	#include "Graphics/API/DX11/DirectXDef.hpp"
#endif

#if defined(LE_ENABLE_IMGUI)
	#include "imgui.h"
	#include "misc/cpp/imgui_stdlib.h"
	#include "backends/imgui_impl_win32.h"
	#include "backends/imgui_impl_dx11.h"
	#include "imgui-notify/imgui_notify.hpp"
	#include "imgui-notify/tahoma.hpp"
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
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(device), reinterpret_cast<ID3D11DeviceContext*>(deviceContext));
		SetDefaultTheme();
	}

	void RuntimeEditor::SetDefaultTheme()
	{
		ImGui::StyleColorsDark();

		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		ImGuiIO& io = ImGui::GetIO();
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
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();
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

	void RuntimeEditor::NewPanel(const std::string& name)
	{
		if (inPanel)
		{
			ImGui::End();
		}
		ImGui::Begin(name.c_str());
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

	bool RuntimeEditor::Drag(const std::string& label, char& var, char min, char max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S8, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int8& var, int8 min, int8 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S8, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int16& var, int16 min, int16 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S16, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int32& var, int32 min, int32 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S32, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int64& var, int64 min, int64 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S64, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint8& var, uint8 min, uint8 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U8, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint16& var, uint16 min, uint16 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U16, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint32& var, uint32 min, uint32 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U32, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint64& var, uint64 min, uint64 max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U64, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, float& var, float min, float max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_Float, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, double& var, double min, double max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_Double, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, Vector& vec, float min, float max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragFloat3(label.c_str(), reinterpret_cast<float*>(&vec), speed, min, max);
	}

	bool RuntimeEditor::Drag(const std::string& label, Rotator& rot, float min, float max, float speed)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::DragFloat3(label.c_str(), reinterpret_cast<float*>(&rot), speed, min, max);
	}

	bool RuntimeEditor::Slider(const std::string& label, char& var, char min, char max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S8, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int8& var, int8 min, int8 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S8, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int16& var, int16 min, int16 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S16, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int32& var, int32 min, int32 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S32, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int64& var, int64 min, int64 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S64, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint8& var, uint8 min, uint8 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U8, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint16& var, uint16 min, uint16 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U16, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint32& var, uint32 min, uint32 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U32, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint64& var, uint64 min, uint64 max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U64, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, float& var, float min, float max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_Float, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, double& var, double min, double max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_Double, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, Vector& vec, float min, float max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderFloat3(label.c_str(), reinterpret_cast<float*>(&vec), min, max);
	}

	bool RuntimeEditor::Slider(const std::string& label, Rotator& rot, float min, float max)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::SliderFloat3(label.c_str(), reinterpret_cast<float*>(&rot), min, max);
	}

	bool RuntimeEditor::TextField(const std::string& label, std::string& var)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::InputText(label.c_str(), &var);
	}

	bool RuntimeEditor::TextField(const std::string& label, char* buf, size_t bufSize)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::InputText(label.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::TextField(const std::string& label, const std::string& hint, std::string& var)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::InputTextWithHint(label.c_str(), hint.c_str(), &var);
	}

	bool RuntimeEditor::TextField(const std::string& label, const std::string& hint, char* buf, size_t bufSize)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::InputTextWithHint(label.c_str(), hint.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::MultilineTextField(const std::string& label, std::string& var)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::InputTextMultiline(label.c_str(), &var);
	}

	bool RuntimeEditor::MultilineTextField(const std::string& label, char* buf, size_t bufSize)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::InputText(label.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::CheckBox(const std::string& label, bool& var)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::Checkbox(label.c_str(), &var);
	}

	bool RuntimeEditor::Button(const std::string& label)
	{
		if (!inPanel) NewPanel("None");
		return ImGui::Button(label.c_str());
	}

	bool RuntimeEditor::Button(const std::string& label, bool& varToStore)
	{
		if (Button(label)) varToStore = !varToStore;
		return varToStore;
	}

	void RuntimeEditor::Text(const std::string& str)
	{
		if (!inPanel) NewPanel("None");
		ImGui::Text(str.c_str());
	}

	void RuntimeEditor::Text(const std::string& label, const std::string& str)
	{
		if (!inPanel) NewPanel("None");
		ImGui::LabelText(label.c_str(), str.c_str());
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

	bool RuntimeEditor::Input(const std::string& label, char& var, char min, char max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int8& var, int8 min, int8 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int16& var, int16 min, int16 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int32& var, int32 min, int32 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int64& var, int64 min, int64 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint8& var, uint8 min, uint8 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint16& var, uint16 min, uint16 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint32& var, uint32 min, uint32 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint64& var, uint64 min, uint64 max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, float& var, float min, float max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, double& var, double min, double max, float speed)
	{
		return Drag(label.c_str(), var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, bool& var)
	{
		return CheckBox(label.c_str(), var);
	}

	bool RuntimeEditor::Input(const std::string& label, std::string& var)
	{
		return TextField(label.c_str(), var);
	}

	bool RuntimeEditor::Input(const std::string& label, char* buf, size_t bufSize)
	{
		return TextField(label.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::Input(const std::string& label, const std::string& hint, std::string& var)
	{
		return TextField(label.c_str(), hint, var);
	}

	bool RuntimeEditor::Input(const std::string& label, const std::string& hint, char* buf, size_t bufSize)
	{
		return TextField(label.c_str(), hint, buf, bufSize);
	}

	bool RuntimeEditor::Input(const std::string& label, Vector& vec, float min, float max, float speed)
	{
		return Drag(label.c_str(), vec, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, Transform& transform)
	{
		if (!inPanel) NewPanel("None");
		Text(label);
		ImGui::PushID(label.c_str());
		bool changed = false;
		changed = Drag("Location", transform.location) || changed;
		changed = Drag("Rotation", transform.rotation) || changed;
		changed = Drag("Scale", transform.scale, 0, 0, 0.25f) || changed;
		ImGui::PopID();
		return changed;
	}
}
