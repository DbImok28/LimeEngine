#include "lepch.hpp"
#include "TestMap.hpp"
#include "Engine.hpp"
#include "Helpers/Paths.hpp"
#include "MeshObject.hpp"
#include "Base/Primitives.hpp"
#include "Graphics/GraphicFactory.hpp"

namespace LimeEngine
{
	void TestMap::Load()
	{
		auto& inputDevice = engine->inputLayer.GetInputDevice();

		// Configuration
		inputDevice.AddAxisMapping({
			"MoveForward", {{ InputKey::W, 1.0f }, { InputKey::S, -1.0f }}
        });
		inputDevice.AddAxisMapping({
			"MoveRight", {{ InputKey::D, 1.0f }, { InputKey::A, -1.0f }}
        });
		inputDevice.AddAxisMapping({
			"MoveUp", {{ InputKey::Space, 1.0f }, { InputKey::Z, -1.0f }, { InputKey::Shift, -1.0f }}
        });
		inputDevice.AddAxisMapping({ "TurnUp", { { InputKey::MouseMoveY, 1.0f } } });
		inputDevice.AddAxisMapping({ "TurnRight", { { InputKey::MouseMoveX, 1.0f } } });
		inputDevice.AddActionMapping({ "Print", { InputKey::F } });

		inputDevice.BindActionEvent("Print", InputActionType::Pressed, []() { LE_LOG_DEBUG("Press F"); });
		inputDevice.BindActionEvent("Print", InputActionType::Released, []() { LE_LOG_DEBUG("Released F"); });
		// Graphic
		auto graphicFactory = engine->renderLayer.GetGraphicFactory();

		// Loading
		auto& gameDataManager = engine->dataLayer.GetGameDataManager();

		static auto vertexShader = graphicFactory->CreateVertexShader(Paths::ShaderFolder / "VertexShader.cso", MaterialType::Solid);
		static auto pixelShader = graphicFactory->CreatePixelShader(Paths::ShaderFolder / "PixelShader.cso");

		std::vector<Vertex> vertices = {
			{-1.0f,  1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f},
            { 1.0f,  1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f},
			{ 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f},
            { -1.0f, 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f},

			{ -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f},
            { 1.0f,  -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f},
			{ 1.0f,  -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f},
            { -1.0f, -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f},

			{ -1.0f, -1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,  0.0f, 1.0f},
            { -1.0f, -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f},
			{ -1.0f, 1.0f,  -1.0f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f},
            { -1.0f, 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f},

			{ 1.0f,  -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f},
            { 1.0f,  -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f},
			{ 1.0f,  1.0f,  -1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f},
            { 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f},

			{ -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f},
            { 1.0f,  -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f},
			{ 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f},
            { -1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f},

			{ -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f},
            { 1.0f,  -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f},
			{ 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f},
            { -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f},
		};
		std::vector<uint> indices = { 3, 1, 0, 2, 1, 3, 6, 4, 5, 7, 4, 6, 11, 9, 8, 10, 9, 11, 14, 12, 13, 15, 12, 14, 19, 17, 16, 18, 17, 19, 22, 20, 21, 23, 20, 22 };
		auto mesh = gameDataManager.CreateMesh("EngineContent/Cube", vertices, indices);

		// Box
		auto texture = gameDataManager.CreateTexture2D("EngineContent/T_Cat", Paths::ContentFolder / "Textures" / "cat.jpg", TextureType::Diffuse);
		auto material = gameDataManager.CreateMasterMaterial("EngineContent/Cat", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		material.Get()->AddTexture(texture);
		mesh->segments[0].SetMaterial(material.Get());
		auto object = std::make_unique<MeshObject>(engine, Transform(), mesh);
		object->rootComponent->AttachComponent(std::make_unique<MeshComponent>(engine, Transform(0, 10, 0), mesh));
		AttachObject(std::move(object));

		// UVMapping
		auto UVMappingTexture = gameDataManager.CreateTexture2D("EngineContent/T_UVMapping", Paths::ContentFolder / "Textures" / "UVMapping.jpg", TextureType::Diffuse);
		auto UVMappingMaterial = gameDataManager.CreateMasterMaterial("EngineContent/M_UVMapping", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		UVMappingMaterial.Get()->AddTexture(UVMappingTexture);

		// Sphere material
		auto SphereTexture = gameDataManager.CreateTexture2D("EngineContent/T_Sphere", Paths::ContentFolder / "Textures" / "Sphere.png", TextureType::Diffuse);
		auto SphereMaterial = gameDataManager.CreateMasterMaterial("EngineContent/M_Sphere", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		SphereMaterial.Get()->AddTexture(SphereTexture);

		// Primitives
		Plane plane(40, 10, 12);
		auto planeMesh = plane.CreateMesh(engine, "EngineContent/Plane");
		planeMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), planeMesh)));

		Sphere sphere(10, 16, 16);
		auto sphereMesh = sphere.CreateMesh(engine, "EngineContent/Sphere");
		sphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), sphereMesh)));

		Cubesphere cubesphere(10, 3);
		auto cubesphereMesh = cubesphere.CreateMesh(engine, "EngineContent/Cubesphere");
		cubesphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(-10, 0, 10), cubesphereMesh)));

		// Camera
		auto cameraComponent = std::make_unique<DefaultPlayerCameraComponent>(engine, Transform(0, 5, -10));
		auto cameraObject = std::make_unique<SceneObject>(engine, std::move(cameraComponent));
		AttachObject(std::move(cameraObject));
	}

	void TestMap::Update()
	{
		static bool isInput;
		static int32 intValue;
		static Vector vec;
		static Transform transform;
		RuntimeEditor::NewPanel("Hello");

		if (RuntimeEditor::Button("TestInput", isInput))
		{
			RuntimeEditor::Text("BlaBla1");
			RuntimeEditor::Text("hiint", "Basdf");
			RuntimeEditor::Slider("test", intValue);

			RuntimeEditor::Slider("test", vec);

			RuntimeEditor::Input("tes2t", transform);
		}
	}
}