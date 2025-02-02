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

namespace LimeEngine
{
	void TestMap::Load()
	{
		LE_CORE_LOG_TRACE("Load map: {}", GetMapName());

		InputDevice* inputDevice = InputLayer::GetInputLayer()->GetInputDevice();

		// Input
		inputDevice->AddAxisMapping({
			"MoveForward", { { InputKey::W, 1.0f }, { InputKey::S, -1.0f } }
        });
		inputDevice->AddAxisMapping({
			"MoveRight", { { InputKey::D, 1.0f }, { InputKey::A, -1.0f } }
        });
		inputDevice->AddAxisMapping({
			"MoveUp", { { InputKey::Space, 1.0f }, { InputKey::Z, -1.0f }, { InputKey::LeftShift, -1.0f } }
        });
		inputDevice->AddAxisMapping({ "TurnUp", { { InputKey::MouseMoveY, 1.0f } } });
		inputDevice->AddAxisMapping({ "TurnRight", { { InputKey::MouseMoveX, 1.0f } } });
		inputDevice->AddActionMapping({ "Print", { InputActionKey(InputKey::F) } });

		inputDevice->BindActionEvent("Print", InputActionType::Pressed, []() { LE_LOG_DEBUG("Press F"); });
		inputDevice->BindActionEvent("Print", InputActionType::Released, []() {
			LE_LOG_DEBUG("Released F");
			LE_LOG_DEBUG("LE_CORE_LOG_DEBUG");
			LE_LOG_ERROR("LE_CORE_LOG_ERROR");
			LE_LOG_CRITICAL_ERROR("LE_CORE_LOG_CRITICAL_ERROR");
			LE_LOG_INFO("LE_CORE_LOG_INFO");
			LE_LOG_TRACE("LE_CORE_LOG_TRACE");
			LE_LOG_WARNING("LE_CORE_LOG_WARNING");
		});

		// DataManager
		auto& gameDataManager = DataLayer::GetDataLayer()->GetGameDataManager();
		// Load materials
		InputLayout InputLayout = {
			{ "POSITION", ShaderDataType::RGB32F, true },
            { "NORMAL",   ShaderDataType::RGB32F, true },
            { "TEXCOORD", ShaderDataType::RG32F,  true }
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
			{ -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
			{ 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
			{ 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
			{ -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		};
		std::vector<uint> indices = ConvertTrianglesFormCCWToCW({ 0, 1, 2, 2, 3, 0 });

		for (auto& vertex : vertices)
		{
			vertex.texCoord.y = Math::FlipUV(vertex.texCoord.y);
		}
		auto boxMesh = gameDataManager.CreateMesh("EngineContent/Cube", vertices, indices);

		LE_CORE_LOG_DEBUG("LE_CORE_LOG_DEBUG");
		LE_CORE_LOG_ERROR("LE_CORE_LOG_ERROR");
		LE_CORE_LOG_CRITICAL_ERROR("LE_CORE_LOG_CRITICAL_ERROR");
		LE_CORE_LOG_INFO("LE_CORE_LOG_INFO");
		LE_CORE_LOG_TRACE("LE_CORE_LOG_TRACE");
		LE_CORE_LOG_WARNING("LE_CORE_LOG_WARNING");

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

		auto box1Object = SetupAttachment<MeshObject>("Box1");

		boxMaterialInstance->SetTextureParameter(texture, 0u);
		boxMaterialInstance->SetParameter("Saturation", 0.8f);
		boxMesh->segments[0].SetMaterial(boxMaterialInstance);
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

		auto upPlaneMesh = Plane(4, 0, 0).CreateMesh("EngineContent/Plane2");
		upPlaneMesh->segments[0].SetMaterial(CherryMaterialInstance);

		auto planeObject = SetupAttachment<MeshObject>("Plane");
		planeObject->SetTransform(Transform(10.05f, 0.1f, 10));

		auto upPlaneComponent = planeObject->SetupAttachment<MeshComponent>("UpPlane");
		upPlaneComponent->SetTransform(Transform(10.0f, 5.0f, 10.0f));
		upPlaneComponent->SetMesh(upPlaneMesh);

		auto planeMesh = Plane(40, 10, 12).CreateMesh("EngineContent/Plane");
		planeMesh->segments[0].SetMaterial(UVMappingMaterialInstance);
		planeObject->SetMesh(planeMesh);

		auto middlePlaneComponent = planeObject->SetupAttachment<MeshComponent>("MiddlePlane");
		middlePlaneComponent->SetTransform(Transform(10.0f, 2.5f, 10.0f));
		middlePlaneComponent->SetMesh(upPlaneMesh);

		auto sphereObject = SetupAttachment<MeshObject>("Sphere");
		sphereObject->SetTransform(Transform(10.005f, 0, 10));

		auto sphereMesh = Sphere(10, 16, 16).CreateMesh("EngineContent/Sphere");
		sphereMesh->segments[0].SetMaterial(UVMappingMaterialInstance);
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

	void TestMap::DebugUpdate()
	{
		SceneMap::DebugUpdate();
	}
}
