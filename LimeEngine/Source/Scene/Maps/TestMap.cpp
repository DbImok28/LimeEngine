// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "TestMap.hpp"
#include "Engine.hpp"
#include "Utility/Paths.hpp"
#include "Scene/Objects/MeshObject.hpp"
#include "Base/Primitives.hpp"
#include "Graphics/Shaders.hpp"
#include "Base/Math.hpp"

#include "Graphics/API/DX11/RenderOutputDX11.hpp"
#include "Graphics/API/DX11/Texture2DDX11.hpp"

namespace LimeEngine
{
	void TestMap::Load()
	{
		LE_CORE_LOG_TRACE("Load map: {}", GetMapName());

		auto& inputDevice = InputLayer::GetInputLayer().GetInputDevice();

		// Input
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

		// DataManager
		auto& gameDataManager = DataLayer::GetDataLayer().GetGameDataManager();
		// Load materials
		InputLayout InputLayout = {
			{"POSITION",  ShaderDataType::RGB32F, true},
            { "NORMAL",   ShaderDataType::RGB32F, true},
            { "TEXCOORD", ShaderDataType::RG32F,  true}
		};
		ShaderArray simpleShader(InputLayout, Paths::ShaderFolder, "SimpleShader");
		auto material = gameDataManager.CreateMaterial("EngineContent/M_Cat", std::move(simpleShader), {}, MaterialType::Solid);
		material->parameters.AddParameter("Saturation", 1.0f);

		// Load meshes
		//std::vector<Vertex> vertices = {
		//	{-1.0f,  1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f},
		//          { 1.0f,  1.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f},
		//	{ 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f},
		//          { -1.0f, 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f},

		//	{ -1.0f, -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f},
		//          { 1.0f,  -1.0f, -1.0f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f},
		//	{ 1.0f,  -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f},
		//          { -1.0f, -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f},

		//	{ -1.0f, -1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,  0.0f, 1.0f},
		//          { -1.0f, -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f},
		//	{ -1.0f, 1.0f,  -1.0f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f},
		//          { -1.0f, 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f},

		//	{ 1.0f,  -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f},
		//          { 1.0f,  -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f},
		//	{ 1.0f,  1.0f,  -1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f},
		//          { 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f},

		//	{ -1.0f, -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f},
		//          { 1.0f,  -1.0f, -1.0f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f},
		//	{ 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f},
		//          { -1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f},

		//	{ -1.0f, -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f},
		//          { 1.0f,  -1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f},
		//	{ 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f},
		//          { -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f},
		//};
		//std::vector<uint> indices = { 3, 1, 0, 2, 1, 3, 6, 4, 5, 7, 4, 6, 11, 9, 8, 10, 9, 11, 14, 12, 13, 15, 12, 14, 19, 17, 16, 18, 17, 19, 22, 20, 21, 23, 20, 22 };
		//auto boxMesh = gameDataManager.CreateMesh("EngineContent/Cube", vertices, indices);

		std::vector<Vertex> vertices = {
			{-1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
			{ 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
			{ 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
			{ -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		};
		std::vector<uint> indices = ConvertTrianglesFormCCWToCW({ 0, 1, 2, 2, 3, 0 });

		for (auto& vertex : vertices)
		{
			vertex.texCoord.y = Math::FlipUV(vertex.texCoord.y);
		}
		auto boxMesh = gameDataManager.CreateMesh("EngineContent/Cube", vertices, indices);

		// up	  forward
		// +     +
		// ^    /
		// |   /
		// |  /
		// Y Z
		//  X--->+ right
		// Paths
		FPath TextureFolder = Paths::ContentFolder / "Textures";

		// Box

		auto texture = gameDataManager.CreateTexture2D("EngineContent/T_Cat", TextureFolder / "cat.jpg", TextureFormat::RGBA8, TextureType::Diffuse);
		auto boxMaterialInstance = material->Instantiate();

		boxMaterialInstance->SetTextureParameter(texture, 0u);
		boxMaterialInstance->SetParameter("Saturation", 0.8f);
		boxMesh->segments[0].SetMaterial(boxMaterialInstance);

		auto box1Object = SetupAttachment<MeshObject>("Box1");
		box1Object->SetMesh(boxMesh);
		auto box2Component = box1Object->SetupAttachment<MeshComponent>("Box2");
		box2Component->SetTransform(Transform(0, 10, 0));
		box2Component->SetMesh(boxMesh);

		// UVMapping
		auto UVMappingTexture = gameDataManager.CreateTexture2D("EngineContent/T_UVMapping", TextureFolder / "UVMapping.jpg", TextureFormat::RGBA8, TextureType::Diffuse);
		auto UVMappingMaterialInstance = material->Instantiate();
		UVMappingMaterialInstance->SetTextureParameter(UVMappingTexture, 0u);

		// Sphere material
		auto SphereTexture = gameDataManager.CreateTexture2D("EngineContent/T_Sphere", TextureFolder / "Sphere.png", TextureFormat::RGBA8, TextureType::Diffuse);
		auto SphereMaterialInstance = material->Instantiate();
		SphereMaterialInstance->SetTextureParameter(SphereTexture, 0u);

		// Cherry
		auto CherryTexture = gameDataManager.CreateTexture2D("EngineContent/T_Cherry", TextureFolder / "cherry.png", TextureFormat::RGBA8, TextureType::Diffuse);
		auto CherryMaterialInstance = material->Instantiate();
		CherryMaterialInstance->SetTextureParameter(CherryTexture, 0u);

		// Primitives
		auto planeMesh = Plane(40, 10, 12).CreateMesh("EngineContent/Plane");
		planeMesh->segments[0].SetMaterial(UVMappingMaterialInstance);

		auto upPlaneMesh = Plane(4, 0, 0).CreateMesh("EngineContent/Plane2");
		upPlaneMesh->segments[0].SetMaterial(CherryMaterialInstance);

		auto planeObject = SetupAttachment<MeshObject>("Plane");
		planeObject->SetTransform(Transform(10.05f, 0.1f, 10));
		planeObject->SetMesh(planeMesh);

		auto upPlaneComponent = planeObject->SetupAttachment<MeshComponent>("UpPlane");
		upPlaneComponent->SetMesh(upPlaneMesh);
		upPlaneComponent->SetTransform(Transform(10.0f, 5.0f, 10.0f));

		auto middlePlaneComponent = planeObject->SetupAttachment<MeshComponent>("MiddlePlane");
		middlePlaneComponent->SetMesh(upPlaneMesh);
		middlePlaneComponent->SetTransform(Transform(10.0f, 2.5f, 10.0f));

		auto sphereMesh = Sphere(10, 16, 16).CreateMesh("EngineContent/Sphere");
		sphereMesh->segments[0].SetMaterial(UVMappingMaterialInstance);

		auto sphereObject = SetupAttachment<MeshObject>("Sphere");
		sphereObject->SetTransform(Transform(10.005f, 0, 10));
		sphereObject->SetMesh(sphereMesh);

		auto cubesphereMesh = Cubesphere(10, 3).CreateMesh("EngineContent/Cubesphere");
		cubesphereMesh->segments[0].SetMaterial(UVMappingMaterialInstance);

		auto cubesphereObject = SetupAttachment<MeshObject>("Cubesphere");
		cubesphereObject->SetTransform(Transform(-10.0005f, 0, 10));
		cubesphereObject->SetMesh(cubesphereMesh);

		// Camera
		auto playerCamera = SetupAttachment<SceneObject>()->SetupAttachment<DefaultPlayerCameraComponent>("PlayerCamera");
		playerCamera->SetTransform(Transform(0, 5, -10));
	}

	void TestMap::Update()
	{
		if (RuntimeEditor::BeginPanel("Assets"))
		{
			auto& gameDataManager = DataLayer::GetDataLayer().GetGameDataManager();
			RuntimeEditor::Text(std::format("Assets {}", gameDataManager.GetAllResources().size()));
			for (auto& [path, ref] : gameDataManager.GetAllResources())
			{
				RuntimeEditor::Text(std::format("{}, refs: {}", ref->GetPath().GetPath(), ref->GetRefCount()));
			}
		}
		RuntimeEditor::EndPanel();

		if (RuntimeEditor::BeginPanel("Properties"))
		{
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
		}
		RuntimeEditor::EndPanel();

		if (RuntimeEditor::BeginPanel("Info"))
		{
			for (auto& object : GetSubObjects())
			{
				RuntimeEditor::Text(object->GetObjectName(), std::format("{}", object->GetObjectTransform()));
			}
		}
		RuntimeEditor::EndPanel();

		SceneMap::Update();
	}
}
