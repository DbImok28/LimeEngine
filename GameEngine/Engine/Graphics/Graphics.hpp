#pragma once
/*
* Copyright(C) 2021, by ѕавел якушик(ruby.circles774@gmail.com)
*/
#include "DirectXDef.hpp"
#include <vector>
#include <string>
#include <sstream>
#include "Shaders.hpp"
#include "../Base/Material.hpp"
#include "../Scene/Camera.hpp"
#include "../Exceptions/GraphicsExceptions.hpp"
#include "../Helpers/Paths.hpp"

#ifndef NO_IMGUI
	#ifndef IMGUI
		#define IMGUI
	#endif // !IMGUI
#endif // !NO_IMGUI


class Engine;

class Graphics
{
public:
	Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) noexcept = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics& operator=(Graphics&&) noexcept = delete;

	void RenderFrame();
	void Initialize(HWND hWnd, Engine* engine, int width, int height);
private:
	void InitializeDirectX(HWND hWnd);
	void PreProcessing();
	void Processing();
	void PostProcessing();

	com_ptr<IDXGISwapChain> swapchain;
	com_ptr<ID3D11RenderTargetView> renderTargetView;

	com_ptr<ID3D11DepthStencilView> depthStencilView;
	com_ptr<ID3D11Texture2D> depthStencilBuffer;
	com_ptr<ID3D11DepthStencilState> depthStencilState;

	com_ptr<ID3D11RasterizerState> rasterizerState;

	com_ptr<ID3D11SamplerState> samplerState;

public:
	com_ptr<ID3D11Device> device;
	com_ptr<ID3D11DeviceContext> deviceContext;

private:
	int windowWidth = 0;
	int windowHeight = 0;

public:
	Camera camera;
	Engine* pEngine = nullptr;

#ifdef IMGUI
public:
	void ImGuiSetup(HWND hWnd);
	void ImGuiUpdate();
#endif // IMGUI
};