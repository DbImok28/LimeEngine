#include "lepch.hpp"
#include "TestMap.hpp"
#include "Engine.hpp"
#include "Helpers/Paths.hpp"
#include "Scene/Objects/MeshObject.hpp"
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
			"MoveUp", {{ InputKey::Space, 1.0f }, { InputKey::Z, -1.0f }, { InputKey::LeftShift, -1.0f }}
        });
		inputDevice.AddAxisMapping({ "TurnUp", { { InputKey::MouseMoveY, 1.0f } } });
		inputDevice.AddAxisMapping({ "TurnRight", { { InputKey::MouseMoveX, 1.0f } } });
		inputDevice.AddActionMapping({ "Print", { InputActionKey(InputKey::F) } });

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
		auto object = std::make_unique<MeshObject>(engine, mesh, "Box1", Transform());
		object->rootComponent->AttachComponent(std::make_unique<MeshComponent>(engine, mesh, "Box2", Transform(0, 10, 0)));
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
		AttachObject(std::move(std::make_unique<MeshObject>(engine, planeMesh, "Plane", Transform(10.05f, 0.1f, 10))));

		Sphere sphere(10, 16, 16);
		auto sphereMesh = sphere.CreateMesh(engine, "EngineContent/Sphere");
		sphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, sphereMesh, "Sphere", Transform(10.005f, 0, 10))));

		Cubesphere cubesphere(10, 3);
		auto cubesphereMesh = cubesphere.CreateMesh(engine, "EngineContent/Cubesphere");
		cubesphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());
		AttachObject(std::move(std::make_unique<MeshObject>(engine, cubesphereMesh, "Cubesphere", Transform(-10.0005f, 0, 10))));

		// Camera
		auto cameraComponent = std::make_unique<DefaultPlayerCameraComponent>(engine, "PlayerCamera", Transform(0, 5, -10));
		auto cameraObject = std::make_unique<SceneObject>(engine, std::move(cameraComponent));
		AttachObject(std::move(cameraObject));
	}

	void TestMap::Update()
	{
		RuntimeEditor::NewPanel("Objects");
		for (auto& object : objects)
		{
			if (object->rootComponent != nullptr)
			{
				Transform transform = object->rootComponent->GetTransform();
				RuntimeEditor::Input(object->GetObjectName().c_str(), transform);
				object->rootComponent->SetTransform(transform);
			}
		}

		RuntimeEditor::NewPanel("Objects Info");
		for (auto& object : objects)
		{
			RuntimeEditor::Text(object->GetObjectName().c_str(), std::format("{}", object->GetObjectTransform()));
		}
	}
}
