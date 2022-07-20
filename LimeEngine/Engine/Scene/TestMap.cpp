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
		auto& renderSystem = *static_cast<RenderingSystemDX11*>(engineInput0.renderIO.renderer->renderSystem);
		auto& device = static_cast<RenderingSystemDX11*>(engineInput0.renderIO.renderer->renderSystem)->device;
		auto& deviceContext = static_cast<RenderingSystemDX11*>(engineInput0.renderIO.renderer->renderSystem)->deviceContext;

		// Loading
		static VertexShader vertexShader;
		static PixelShader pixelShader;
		D3D11_INPUT_ELEMENT_DESC loyout[]{
			{"POSITION",  0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                            D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT numElements = ARRAYSIZE(loyout);
		vertexShader.Initalize(device, Paths::ShaderFolder + L"VertexShader.cso", loyout, numElements);
		pixelShader.Initalize(device, Paths::ShaderFolder + L"PixelShader.cso");

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
		static std::vector<DWORD> indices = { 3, 1, 0, 2, 1, 3, 6, 4, 5, 7, 4, 6, 11, 9, 8, 10, 9, 11, 14, 12, 13, 15, 12, 14, 19, 17, 16, 18, 17, 19, 22, 20, 21, 23, 20, 22 };
		auto mesh = engine->gameDataManager.meshes.Create(0, vertices, indices, 0);
		auto material = engine->gameDataManager.materials.Create(0, renderSystem, &vertexShader, &pixelShader, 0);
		auto texture = engine->gameDataManager.textures2D.Create(0, renderSystem, L"Data\\Textures\\cat.jpg", TextureType::Diffuse, 0);
		material->AddTexture(texture);
		mesh->SetMaterial(material);

		// UVMapping
		auto UVMappingTexture = engine->gameDataManager.textures2D.Create(1, renderSystem, L"Data\\Textures\\UVMapping.jpg", TextureType::Diffuse, 1);
		auto UVMappingMaterial = engine->gameDataManager.materials.Create(1, renderSystem, &vertexShader, &pixelShader, 1);
		UVMappingMaterial->AddTexture(UVMappingTexture);

		// Sphere
		auto SphereTexture = engine->gameDataManager.textures2D.Create(2, renderSystem, L"Data\\Textures\\Sphere.png", TextureType::Diffuse, 2);
		auto SphereMaterial = engine->gameDataManager.materials.Create(2, renderSystem, &vertexShader, &pixelShader, 2);
		SphereMaterial->AddTexture(SphereTexture);

		// Primitives
		Plane plane(40, 10, 12);
		auto planeMesh = plane.CreateMesh(engine);
		planeMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), planeMesh->GetId())));

		Sphere sphere(10, 16, 16);
		auto sphereMesh = sphere.CreateMesh(engine);
		sphereMesh->SetMaterial(UVMappingMaterial);
		AttachObject(std::move(std::make_unique<MeshObject>(engine, Transform(10, 0, 10), sphereMesh->GetId())));

		Cubesphere cubesphere(10, 3);
		auto cubesphereMesh = cubesphere.CreateMesh(engine);
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