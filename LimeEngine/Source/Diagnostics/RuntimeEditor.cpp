// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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
	bool RuntimeEditor::inPanel = false;
	bool RuntimeEditor::inDockSpace = false;

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

#if defined(LE_ENABLE_RENDER_API_DX11)
	void RuntimeEditor::Init(void* hWnd, void* device, void* deviceContext)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

		SetDefaultTheme();

		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(device), reinterpret_cast<ID3D11DeviceContext*>(deviceContext));
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

		SetupDockSpace();
	}

	void RuntimeEditor::Render()
	{
		if (inPanel) { ImGui::End(); }
		if (inDockSpace) { ImGui::End(); }
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1);

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

#else
	void RuntimeEditor::Destroy() {}
	void RuntimeEditor::Processing(float deltaTime) {}
	void RuntimeEditor::Render() {}
#endif

	void RuntimeEditor::SetDefaultTheme()
	{
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();

		// When viewports are enabled we tweak WindowRounding / WindowBg so platform windows can look identical to regular ones.ImGuiStyle& style = ImGui::GetStyle();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		io.Fonts->AddFontFromMemoryTTF(reinterpret_cast<void*>(const_cast<unsigned char*>(tahoma)), sizeof(tahoma), 15.f, &font_cfg);
		ImGui::MergeIconsWithLatestFont(16.f, false);
	}

	void RuntimeEditor::SetupDockSpace()
	{
		static bool opt_fullscreen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else { dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode; }

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("MainDockSpace", nullptr, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen) ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				}
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				}
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				}
				ImGui::Separator();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		inDockSpace = true;
	}

	void RuntimeEditor::PushID(const std::string& id)
	{
		ImGui::PushID(id.c_str());
	}

	void RuntimeEditor::PushID(int id)
	{
		ImGui::PushID(id);
	}

	void RuntimeEditor::PopID()
	{
		ImGui::PopID();
	}

	void RuntimeEditor::AutoScroll(bool shouldAutoScroll)
	{
		if (shouldAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f);
	}

	void RuntimeEditor::SetTextColor(const Vector4D& color)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color.x, color.y, color.z, color.w));
	}

	void RuntimeEditor::ResetTextColor()
	{
		ImGui::PopStyleColor();
	}

	EditorPanel RuntimeEditor::MakePanel(const std::string& name)
	{
		return EditorPanel(name);
	}

	EditorPanel RuntimeEditor::MakePanel(const std::string& name, bool& isOpen)
	{
		return EditorPanel(name, isOpen);
	}

	bool RuntimeEditor::BeginPanel(const std::string& name)
	{
		if (inPanel) ImGui::End();
		bool isVisible = ImGui::Begin(name.c_str());
		inPanel = true;
		return isVisible;
	}

	bool RuntimeEditor::BeginPanel(const std::string& name, bool& isOpen)
	{
		if (inPanel) ImGui::End();
		bool isVisible = ImGui::Begin(name.c_str(), &isOpen);
		inPanel = true;
		return isVisible;
	}

	void RuntimeEditor::EndPanel()
	{
		if (inPanel) ImGui::End();
		inPanel = false;
	}

	bool RuntimeEditor::Drag(const std::string& label, char& var, char min, char max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S8, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int8& var, int8 min, int8 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S8, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int16& var, int16 min, int16 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S16, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int32& var, int32 min, int32 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S32, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, int64& var, int64 min, int64 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_S64, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint8& var, uint8 min, uint8 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U8, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint16& var, uint16 min, uint16 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U16, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint32& var, uint32 min, uint32 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U32, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, uint64& var, uint64 min, uint64 max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_U64, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, float& var, float min, float max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_Float, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, double& var, double min, double max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragScalar(label.c_str(), ImGuiDataType_Double, &var, speed, &min, &max);
	}

	bool RuntimeEditor::Drag(const std::string& label, Vector& vec, float min, float max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragFloat3(label.c_str(), reinterpret_cast<float*>(&vec), speed, min, max);
	}

	bool RuntimeEditor::Drag(const std::string& label, Rotator& rot, float min, float max, float speed)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::DragFloat3(label.c_str(), reinterpret_cast<float*>(&rot), speed, min, max);
	}

	bool RuntimeEditor::Slider(const std::string& label, char& var, char min, char max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S8, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int8& var, int8 min, int8 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S8, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int16& var, int16 min, int16 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S16, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int32& var, int32 min, int32 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S32, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, int64& var, int64 min, int64 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_S64, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint8& var, uint8 min, uint8 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U8, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint16& var, uint16 min, uint16 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U16, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint32& var, uint32 min, uint32 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U32, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, uint64& var, uint64 min, uint64 max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_U64, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, float& var, float min, float max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_Float, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, double& var, double min, double max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderScalar(label.c_str(), ImGuiDataType_Double, &var, &min, &max);
	}

	bool RuntimeEditor::Slider(const std::string& label, Vector& vec, float min, float max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderFloat3(label.c_str(), reinterpret_cast<float*>(&vec), min, max);
	}

	bool RuntimeEditor::Slider(const std::string& label, Rotator& rot, float min, float max)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::SliderFloat3(label.c_str(), reinterpret_cast<float*>(&rot), min, max);
	}

	bool RuntimeEditor::TextField(const std::string& label, std::string& var)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::InputText(label.c_str(), &var);
	}

	bool RuntimeEditor::TextField(const std::string& label, char* buf, size_t bufSize)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::InputText(label.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::TextField(const std::string& label, const std::string& hint, std::string& var)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::InputTextWithHint(label.c_str(), hint.c_str(), &var);
	}

	bool RuntimeEditor::TextField(const std::string& label, const std::string& hint, char* buf, size_t bufSize)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::InputTextWithHint(label.c_str(), hint.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::MultilineTextField(const std::string& label, std::string& var)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::InputTextMultiline(label.c_str(), &var);
	}

	bool RuntimeEditor::MultilineTextField(const std::string& label, char* buf, size_t bufSize)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::InputText(label.c_str(), buf, bufSize);
	}

	bool RuntimeEditor::CheckBox(const std::string& label, bool& var)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::Checkbox(label.c_str(), &var);
	}

	bool RuntimeEditor::Button(const std::string& label)
	{
		if (!inPanel) BeginPanel("None");
		return ImGui::Button(label.c_str());
	}

	bool RuntimeEditor::Button(const std::string& label, bool& varToStore)
	{
		if (Button(label)) varToStore = !varToStore;
		return varToStore;
	}

	void RuntimeEditor::Text(const std::string& str)
	{
		if (!inPanel) BeginPanel("None");
		ImGui::TextUnformatted(str.c_str());
	}

	void RuntimeEditor::Text(const std::string& label, const std::string& str)
	{
		if (!inPanel) BeginPanel("None");
		ImGui::LabelText(label.c_str(), str.c_str());
	}

	void RuntimeEditor::Text(const std::string& str, Vector4D color)
	{
		if (!inPanel) BeginPanel("None");
		ImGui::TextColored(*reinterpret_cast<ImVec4*>(&color), str.c_str());
	}

	void RuntimeEditor::Image(const Texture2D* texture)
	{
		if (!inPanel) BeginPanel("None");
		ImGui::Image(texture->GetView(), ImVec2(static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight())));
	}

	void RuntimeEditor::Image(const Texture2D* texture, UIntVector2D size)
	{
		if (!inPanel) BeginPanel("None");
		ImGui::Image(texture->GetView(), ImVec2(static_cast<float>(size.x), static_cast<float>(size.y)));
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
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int8& var, int8 min, int8 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int16& var, int16 min, int16 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int32& var, int32 min, int32 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, int64& var, int64 min, int64 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint8& var, uint8 min, uint8 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint16& var, uint16 min, uint16 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint32& var, uint32 min, uint32 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, uint64& var, uint64 min, uint64 max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, float& var, float min, float max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, double& var, double min, double max, float speed)
	{
		return Drag(label, var, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, bool& var)
	{
		return CheckBox(label, var);
	}

	bool RuntimeEditor::Input(const std::string& label, std::string& var)
	{
		return TextField(label, var);
	}

	bool RuntimeEditor::Input(const std::string& label, char* buf, size_t bufSize)
	{
		return TextField(label, buf, bufSize);
	}

	bool RuntimeEditor::Input(const std::string& label, const std::string& hint, std::string& var)
	{
		return TextField(label, hint, var);
	}

	bool RuntimeEditor::Input(const std::string& label, const std::string& hint, char* buf, size_t bufSize)
	{
		return TextField(label, hint, buf, bufSize);
	}

	bool RuntimeEditor::Input(const std::string& label, Vector& vec, float min, float max, float speed)
	{
		return Drag(label, vec, min, max, speed);
	}

	bool RuntimeEditor::Input(const std::string& label, Transform& transform)
	{
		if (!inPanel) BeginPanel("None");
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
