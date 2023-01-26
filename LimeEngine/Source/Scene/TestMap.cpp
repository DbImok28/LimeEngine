#include "TestMap.hpp"
#include "Engine.hpp"
#include "Helpers/Paths.hpp"
#include "MeshObject.hpp"
#include "Base/Primitives.hpp"
#include "Graphics/Base/GraphicFactory.hpp"

namespace LimeEngine
{
	void TestMap::Load()
	{
		if (engine->engineIO.empty()) return;
		auto& engineInput0 = engine->engineIO.front();

		// Configuration
		engineInput0.GetInput().AddAxisMapping({
			"MoveForward", {{ InputKey::W, 1.0f }, { InputKey::S, -1.0f }}
        });
		engineInput0.GetInput().AddAxisMapping({
			"MoveRight", {{ InputKey::D, 1.0f }, { InputKey::A, -1.0f }}
        });
		engineInput0.GetInput().AddAxisMapping({
			"MoveUp", {{ InputKey::Space, 1.0f }, { InputKey::Z, -1.0f }, { InputKey::Shift, -1.0f }}
        });
		engineInput0.GetInput().AddAxisMapping({ "TurnUp", { { InputKey::MouseMoveY, 1.0f } } });
		engineInput0.GetInput().AddAxisMapping({ "TurnRight", { { InputKey::MouseMoveX, 1.0f } } });

		// Graphic
		auto renderer = engineInput0.renderIO.renderer;
		auto graphicFactory = renderer->GetGraphicFactory();

		// Loading
		auto& gameDataManager = engine->gameDataManager;

		static auto vertexShader = graphicFactory->CreateVertexShader(Paths::ShaderFolder + L"Shaders\\VertexShader.cso", MaterialType::Solid);
		static auto pixelShader = graphicFactory->CreatePixelShader(Paths::ShaderFolder + L"Shaders\\PixelShader.cso");

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
		auto mesh = gameDataManager.CreateMesh("EngineContent\\Cube", vertices, indices);

		// Box
		auto texture = gameDataManager.CreateTexture2D("EngineContent\\T_Cat", L"Content\\Textures\\cat.jpg", TextureType::Diffuse);
		auto material = engine->gameDataManager.CreateMasterMaterial("EngineContent\\Cat", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		material.Get()->AddTexture(texture);
		mesh->segments[0].SetMaterial(material.Get());
		auto object = std::make_unique<MeshObject>(engine, Transform(), mesh);
		object->rootComponent->AttachComponent(std::make_unique<MeshComponent>(engine, Transform(0, 10, 0), mesh));
		AttachObject(std::move(object));

		// UVMapping
		auto UVMappingTexture = gameDataManager.CreateTexture2D("EngineContent\\T_UVMapping", L"Content\\Textures\\UVMapping.jpg", TextureType::Diffuse);
		auto UVMappingMaterial = engine->gameDataManager.CreateMasterMaterial("EngineContent\\M_UVMapping", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		UVMappingMaterial.Get()->AddTexture(UVMappingTexture);

		// Sphere material
		auto SphereTexture = gameDataManager.CreateTexture2D("EngineContent\\T_Sphere", L"Content\\Textures\\Sphere.png", TextureType::Diffuse);
		auto SphereMaterial = engine->gameDataManager.CreateMasterMaterial("EngineContent\\M_Sphere", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		SphereMaterial.Get()->AddTexture(SphereTexture);

		// Primitives
		Plane plane(40, 10, 12);
		auto planeMesh = plane.CreateMesh(engine, "EngineContent\\Plane");
		planeMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), planeMesh)));

		Sphere sphere(10, 16, 16);
		auto sphereMesh = sphere.CreateMesh(engine, "EngineContent\\Sphere");
		sphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), sphereMesh)));

		Cubesphere cubesphere(10, 3);
		auto cubesphereMesh = cubesphere.CreateMesh(engine, "EngineContent\\Cubesphere");
		cubesphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(-10, 0, 10), cubesphereMesh)));

		// Camera
		auto cameraComponent = std::make_unique<DefaultPlayerCameraComponent>(engine, Transform(0, 5, -10));
		auto cameraObject = std::make_unique<SceneObject>(engine, std::move(cameraComponent));
		AttachObject(std::move(cameraObject));
	}
	void TestMap::Print1()
	{
		LE_DEBUG("Down");
	}
	void TestMap::Print3()
	{
		LE_DEBUG("Up");
	}
}