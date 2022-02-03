#include "TestMap.hpp"
#include "../Engine.hpp"

#include "MeshObject.hpp"

namespace LimeEngine
{
	void TestMap::Load()
	{
		this->engine = engine;
		// Loading
		static VertexShader vertexShader;
		static PixelShader pixelShader;
		D3D11_INPUT_ELEMENT_DESC loyout[]
		{
			{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },	
		};
		UINT numElements = ARRAYSIZE(loyout);
		vertexShader.Initalize(engine->window.graphics.device, Paths::ShaderFolder + L"VertexShader.cso", loyout, numElements);
		pixelShader.Initalize(engine->window.graphics.device, Paths::ShaderFolder + L"PixelShader.cso");
		
		static std::vector<Vertex> vertices =
		{
			{ -1.0f,  1.0f, -1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f },
			{  1.0f,  1.0f, -1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f },
			{  1.0f,  1.0f,  1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f },
			{ -1.0f,  1.0f,  1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f },
			 									 
			{ -1.0f, -1.0f, -1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f },
			{  1.0f, -1.0f, -1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f },
			{  1.0f, -1.0f,  1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f },
			{ -1.0f, -1.0f,  1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f },
			 									 
			{ -1.0f, -1.0f,  1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f },
			{ -1.0f, -1.0f, -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
			{ -1.0f,  1.0f, -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f },
			{ -1.0f,  1.0f,  1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 1.0f },
			 									 
			{  1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f },
			{  1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
			{  1.0f,  1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f },
			{  1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f },
			 					    			 
			{ -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f },
			{  1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
			{  1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f },
			{ -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f },
			 					    			 
			{ -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f },
			{  1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f },
			{  1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f },
			{ -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f },
		};
		static std::vector<DWORD> indices =
		{
			3,1,0,2,1,3,
			6,4,5,7,4,6,
			11,9,8,10,9,11,
			14,12,13,15,12,14,
			19,17,16,18,17,19,
			22,20,21,23,20,22
		};
		auto mesh = engine->gameDataManager.meshes.Create(0, engine->window.graphics.device.Get(), engine->window.graphics.deviceContext.Get(), vertices, indices);
		auto material = engine->gameDataManager.materials.Create(0, engine->window.graphics.deviceContext.Get(), &vertexShader, &pixelShader);
		auto texture = engine->gameDataManager.textures2D.Create(0, engine->window.graphics.device.Get(), L"Data\\Textures\\cat.jpg", TextureType::Diffuse);

		material->AddTexture(texture);
		mesh->SetMaterial(material);
		// Make Scene
		auto object = std::make_unique<MeshObject>(engine, Transform(), 0);
		object->rootComponent->AttachComponent(std::make_unique<MeshComponent>(engine,Transform(0, 10, 0), 0));
		AttachObject(std::move(object));
	}
}