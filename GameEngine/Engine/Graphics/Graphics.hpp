#pragma once
/*
* Copyright(C) 2021, by ѕавел якушик(ruby.circles774@gmail.com)
*/
#include "DirectXDef.hpp"
#include "../Exceptions/GraphicsExceptions.hpp"
#include "../Helpers/Paths.hpp"
#include "Shaders.hpp"
#include <vector>
#include <string>
#include <sstream>
#include "../Base/Vertex.hpp"
#include "../Scene/Camera.hpp"

#include "../Base/Material.hpp"

#define IMGUI

class Engine;

class Graphics
{
public:
	Graphics(HWND hWnd, Engine* engine, int width, int height);
	void RenderFrame();
private:
	void PreProcessing();
	void Processing();
	void PostProcessing();

	void InitializeDirectX(HWND hWnd);
	void Initialize();

	com_ptr<ID3D11Device> device;
	com_ptr<ID3D11DeviceContext> deviceContext;

	com_ptr<IDXGISwapChain> swapchain;
	com_ptr<ID3D11RenderTargetView> renderTargetView;

	com_ptr<ID3D11DepthStencilView> depthStencilView;
	com_ptr<ID3D11Texture2D> depthStencilBuffer;
	com_ptr<ID3D11DepthStencilState> depthStencilState;

	com_ptr<ID3D11RasterizerState> rasterizerState;

	com_ptr<ID3D11SamplerState> samplerState;

	VertexShader vertexShader;
	PixelShader pixelShader;

	//Material *mat;
	//Mesh mesh;
	//ConstantBuffer<CB_VS_VertexShader> constantBuffer;


	int windowWidth = 0;
	int windowHeight = 0;
public:
	Camera camera;
	Engine* pEngine;
public:
#ifdef IMGUI
	void ImGuiSetup(HWND hWnd);
	void ImGuiUpdate();
#endif // IMGUI
};