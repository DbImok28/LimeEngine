#include "TestMap.hpp"
#include "../Engine.hpp"
#include "../Helpers/Paths.hpp"
#include "MeshObject.hpp"

#include "../Base/Primitives.hpp"
// TODO: Remove
#include "../Graphics/Systems/DX11/RenderingSystemDX11.hpp"

namespace LimeEngine
{
	void TestMap::Load()
	{
		if (engine->engineIO.empty()) return;
		auto& engineInput0 = engine->engineIO.front();
		// TODO: Remove
		auto& renderingSystem = static_cast<RenderingSystemDX11&>(*engineInput0.renderIO.renderer->renderingSystem);

		// Loading
		static VertexShader vertexShader(renderingSystem);
		static PixelShader pixelShader(renderingSystem);
		vertexShader.Initalize(Paths::ShaderFolder + L"VertexShader.cso", MaterialType::Solid);
		pixelShader.Initalize(Paths::ShaderFolder + L"PixelShader.cso");

		static std::vector<Vertex> vertices = {
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
		static std::vector<uint> indices = { 3, 1, 0, 2, 1, 3, 6, 4, 5, 7, 4, 6, 11, 9, 8, 10, 9, 11, 14, 12, 13, 15, 12, 14, 19, 17, 16, 18, 17, 19, 22, 20, 21, 23, 20, 22 };
		auto mesh = engine->gameDataManager.meshes.Create(0, renderingSystem, vertices, indices, 0);
		//auto mesh = engine->gameDataManager.CreateMesh(renderingSystem, vertices, indices);

		auto texture = engine->gameDataManager.CreateTexture2D(renderingSystem);
		texture->Initialize(L"Data\\Textures\\cat.jpg");
		auto material = engine->gameDataManager.materials.Create(0, &vertexShader, &pixelShader, MaterialType::Solid, 0);
		material->AddTexture(texture);
		mesh->SetMaterial(material);

		// UVMapping
		auto UVMappingTexture = engine->gameDataManager.CreateTexture2D(renderingSystem);
		UVMappingTexture->Initialize(L"Data\\Textures\\UVMapping.jpg");
		auto UVMappingMaterial = engine->gameDataManager.materials.Create(1, &vertexShader, &pixelShader, MaterialType::Solid, 1);
		UVMappingMaterial->AddTexture(UVMappingTexture);

		// Sphere
		auto SphereTexture = engine->gameDataManager.CreateTexture2D(renderingSystem);
		SphereTexture->Initialize(L"Data\\Textures\\Sphere.png");
		auto SphereMaterial = engine->gameDataManager.materials.Create(2, &vertexShader, &pixelShader, MaterialType::Solid, 2);
		SphereMaterial->AddTexture(SphereTexture);

		// Primitives
		Plane plane(40, 10, 12);
		auto planeMesh = plane.CreateMesh(renderingSystem, engine);
		planeMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), planeMesh->GetId())));

		Sphere sphere(10, 16, 16);
		auto sphereMesh = sphere.CreateMesh(renderingSystem, engine);
		sphereMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), sphereMesh->GetId())));

		Cubesphere cubesphere(10, 3);
		auto cubesphereMesh = cubesphere.CreateMesh(renderingSystem, engine);
		cubesphereMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(-10, 0, 10), cubesphereMesh->GetId())));

		// Make Scene
		auto cameraComponent = std::make_unique<DefaultPlayerCameraComponent>(engine, Transform(0, 5, -10));
		auto cameraObject = std::make_unique<SceneObject>(engine, std::move(cameraComponent));
		//engineInput0.sceneIO.camera = cameraComponent.get();
		AttachObject(std::move(cameraObject));

		auto object = std::make_unique<MeshObject>(engine, Transform(), 0);
		object->rootComponent->AttachComponent(std::make_unique<MeshComponent>(engine, Transform(0, 10, 0), 0));
		AttachObject(std::move(object));
	}
}