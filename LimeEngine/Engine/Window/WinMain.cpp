// Developed by Pavel Jakushik.
// See LICENSE for copyright and licensing details (standard MIT License).
// GitHub https://github.com/RubyCircle/LimeEngine
#include "../Engine.hpp"
#include "../Graphics/Systems/DX11/RenderingSystemDX11.hpp"
#include "../Scene/TestMap.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	using namespace LimeEngine;
	try
	{
		HRESULT hr = CoInitialize(NULL);
		if (FAILED(hr)) throw HR_EXCEPTION(hr);

		// engine io
		std::unique_ptr<RenderingSystemDX11> renderingSystem = std::make_unique<RenderingSystemDX11>();
		std::unique_ptr<Window> window = std::make_unique<Window>(1080, 720, L"LimeEngine");
		Renderer renderer(renderingSystem.get(), window.get());

		RenderIO renderIO(&renderer);
		SceneIO sceneIO;
		EngineIO engineIO(std::move(renderIO), std::move(sceneIO));

		Engine engine(std::move(engineIO));

		// load map
		auto map = std::make_unique<TestMap>(&engine);
		map->Load();
		engine.scene.AttachMap(std::move(map));

		engine.Start();
		return EXIT_SUCCESS;
	}
	catch (const EngineException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No info", "Unknown exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return EXIT_FAILURE;
}