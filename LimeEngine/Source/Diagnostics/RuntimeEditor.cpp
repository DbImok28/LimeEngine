#include "lepch.hpp"
#include "RuntimeEditor.hpp"

#ifdef IMGUI
	#include "imgui.h"
	#include "backends/imgui_impl_win32.h"
	#include "backends/imgui_impl_dx11.h"
#endif // IMGUI

namespace LimeEngine
{
	bool RuntimeEditor::inPanel = false;

	void RuntimeEditor::Init(void* hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		const ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(reinterpret_cast<HWND>(hWnd));
		ImGui_ImplDX11_Init(device, deviceContext);
		ImGui::StyleColorsDark();
	}
	void RuntimeEditor::NewPanel(const char* name)
	{
		if (inPanel)
		{
			ImGui::End();
		}
		ImGui::Begin(name);
		inPanel = true;
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

	void RuntimeEditor::Drag(const char* label, int& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragInt(label, &var);
	}
	void RuntimeEditor::Drag(const char* label, float& var)
	{
		if (!inPanel) NewPanel("None");
		ImGui::DragFloat(label, &var);
	}
}
