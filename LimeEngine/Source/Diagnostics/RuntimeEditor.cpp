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
#endif // IMGUI

namespace LimeEngine
{
	bool RuntimeEditor::inPanel = false;

#if defined(LE_ENABLE_RENDER_API_DX11)
	void RuntimeEditor::Init(void* hWnd, void* device, void* deviceContext)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		const ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(reinterpret_cast<HWND>(hWnd));
		ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(device), reinterpret_cast<ID3D11DeviceContext*>(deviceContext));
		ImGui::StyleColorsDark();
	}

	void RuntimeEditor::Processing()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		inPanel = false;
	}

	void RuntimeEditor::Render()
	{
		if (inPanel)
		{
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
#else
	void RuntimeEditor::Processing() {}
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

	void RuntimeEditor::CheckBox(const char* label, bool& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::Checkbox(label, &var);
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

	void RuntimeEditor::Input(const char* label, bool& var)
	{
		CheckBox(label, var);
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
		ImGui::Text(label);
		Drag("Location", transform.location);
		Drag("Rotation", transform.rotation);
		Drag("Scale", transform.scale);
	}
}
