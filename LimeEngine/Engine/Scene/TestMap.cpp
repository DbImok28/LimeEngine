#include "TestMap.hpp"
#include "../Engine.hpp"
#include "../Helpers/Paths.hpp"
#include "MeshObject.hpp"
#include "../Base/Primitives.hpp"
#include "../Graphics/Base/GraphicFactory.hpp"

namespace LimeEngine
{
	void TestMap::Load()
	{
		if (engine->engineIO.empty()) return;
		auto& engineInput0 = engine->engineIO.front();

		// Graphic
		auto renderer = engineInput0.renderIO.renderer;
		auto graphicFactory = renderer->GetGraphicFactory();

		// Loading
		static auto vertexShader = graphicFactory->CreateVertexShader(Paths::ShaderFolder + L"VertexShader.cso", MaterialType::Solid);
		static auto pixelShader = graphicFactory->CreatePixelShader(Paths::ShaderFolder + L"PixelShader.cso");

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
		auto mesh = engine->gameDataManager.meshes.Create(0, graphicFactory, vertices, indices, 0);

		// Box
		static auto texture = graphicFactory->CreateTexture2D(L"Data\\Textures\\cat.jpg", TextureType::Diffuse, 0);
		auto material = engine->gameDataManager.materials.Register(new MasterMaterial(vertexShader.get(), pixelShader.get(), MaterialType::Solid, 0));
		material->AddTexture(texture.get());
		mesh->SetMaterial(material);
		auto object = std::make_unique<MeshObject>(engine, Transform(), 0);
		object->rootComponent->AttachComponent(std::make_unique<MeshComponent>(engine, Transform(0, 10, 0), 0));
		AttachObject(std::move(object));

		// UVMapping
		static auto UVMappingTexture = graphicFactory->CreateTexture2D(L"Data\\Textures\\UVMapping.jpg", TextureType::Diffuse, 1);
		auto UVMappingMaterial = engine->gameDataManager.materials.Register(new MasterMaterial(vertexShader.get(), pixelShader.get(), MaterialType::Solid, 1));
		UVMappingMaterial->AddTexture(UVMappingTexture.get());

		// Sphere material
		static auto SphereTexture = graphicFactory->CreateTexture2D(L"Data\\Textures\\Sphere.png", TextureType::Diffuse, 2);
		auto SphereMaterial = engine->gameDataManager.materials.Register(new MasterMaterial(vertexShader.get(), pixelShader.get(), MaterialType::Solid, 2));
		SphereMaterial->AddTexture(SphereTexture.get());

		// Primitives
		Plane plane(40, 10, 12);
		auto planeMesh = plane.CreateMesh(graphicFactory, engine);
		planeMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), planeMesh->GetId())));

		Sphere sphere(10, 16, 16);
		auto sphereMesh = sphere.CreateMesh(graphicFactory, engine);
		sphereMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), sphereMesh->GetId())));

		Cubesphere cubesphere(10, 3);
		auto cubesphereMesh = cubesphere.CreateMesh(graphicFactory, engine);
		cubesphereMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(-10, 0, 10), cubesphereMesh->GetId())));

		// Camera
		auto cameraComponent = std::make_unique<DefaultPlayerCameraComponent>(engine, Transform(0, 5, -10));
		auto cameraObject = std::make_unique<SceneObject>(engine, std::move(cameraComponent));
		AttachObject(std::move(cameraObject));
	}
}