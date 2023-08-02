// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
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
		LE_CORE_LOG_TRACE("Load map: {}", GetMapName());

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
		auto boxMesh = gameDataManager.CreateMesh("EngineContent/Cube", vertices, indices);

		// Box
		auto texture = gameDataManager.CreateTexture2D("EngineContent/T_Cat", Paths::ContentFolder / "Textures" / "cat.jpg", TextureType::Diffuse);
		auto material = gameDataManager.CreateMasterMaterial("EngineContent/Cat", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		material.Get()->AddTexture(texture);
		boxMesh->segments[0].SetMaterial(material.Get());

		auto box1Object = SetupAttachment<MeshObject>(engine, "Box1");
		box1Object->SetMesh(boxMesh);
		auto box2Component = box1Object->SetupAttachment<MeshComponent>(engine, "Box2");
		box2Component->SetTransform(Transform(0, 10, 0));
		box2Component->SetMesh(boxMesh);

		// UVMapping
		auto UVMappingTexture = gameDataManager.CreateTexture2D("EngineContent/T_UVMapping", Paths::ContentFolder / "Textures" / "UVMapping.jpg", TextureType::Diffuse);
		auto UVMappingMaterial = gameDataManager.CreateMasterMaterial("EngineContent/M_UVMapping", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		UVMappingMaterial.Get()->AddTexture(UVMappingTexture);

		// Sphere material
		auto SphereTexture = gameDataManager.CreateTexture2D("EngineContent/T_Sphere", Paths::ContentFolder / "Textures" / "Sphere.png", TextureType::Diffuse);
		auto SphereMaterial = gameDataManager.CreateMasterMaterial("EngineContent/M_Sphere", vertexShader.get(), pixelShader.get(), MaterialType::Solid);
		SphereMaterial.Get()->AddTexture(SphereTexture);

		// Primitives
		auto planeMesh = Plane(40, 10, 12).CreateMesh(engine, "EngineContent/Plane");
		planeMesh->segments[0].SetMaterial(UVMappingMaterial.Get());

		auto planeObject = SetupAttachment<MeshObject>(engine, "Plane");
		planeObject->SetTransform(Transform(10.05f, 0.1f, 10));
		planeObject->SetMesh(planeMesh);

		auto sphereMesh = Sphere(10, 16, 16).CreateMesh(engine, "EngineContent/Sphere");
		sphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());

		auto sphereObject = SetupAttachment<MeshObject>(engine, "Sphere");
		sphereObject->SetTransform(Transform(10.005f, 0, 10));
		sphereObject->SetMesh(sphereMesh);

		auto cubesphereMesh = Cubesphere(10, 3).CreateMesh(engine, "EngineContent/Cubesphere");
		cubesphereMesh->segments[0].SetMaterial(UVMappingMaterial.Get());

		auto cubesphereObject = SetupAttachment<MeshObject>(engine, "Cubesphere");
		cubesphereObject->SetTransform(Transform(-10.0005f, 0, 10));
		cubesphereObject->SetMesh(cubesphereMesh);

		// Camera
		auto playerCamera = SetupAttachment<SceneObject>(engine)->SetupAttachment<DefaultPlayerCameraComponent>(engine, "PlayerCamera");
		playerCamera->SetTransform(Transform(0, 5, -10));
	}

	void TestMap::Update()
	{
		RuntimeEditor::NewPanel("Properties");
		for (auto& object : GetSubObjects())
		{
			if (object != nullptr)
			{
				Transform transform = object->GetTransform();
				RuntimeEditor::Input(object->GetObjectName(), transform);
				object->SetTransform(transform);

				for (auto& component : object->GetSubComponents())
				{
					transform = component->GetTransform();
					RuntimeEditor::Input(std::format("{}/{}", object->GetObjectName(), component->GetComponentName()), transform);
					component->SetTransform(transform);
				}
			}
		}
		RuntimeEditor::EndPanel();

		RuntimeEditor::NewPanel("Info");
		for (auto& object : GetSubObjects())
		{
			RuntimeEditor::Text(object->GetObjectName(), std::format("{}", object->GetObjectTransform()));
		}
		RuntimeEditor::EndPanel();
		SceneMap::Update();
	}
}
