#pragma once
#include "GameComponent.hpp"
#include "../Base/Mesh.hpp"

class MeshComponent : public GameComponent
{
public:
	MeshComponent(size_t id = 0) noexcept;
	void InitializeComponent(Engine* engine) override;
	void Render() override;
	size_t id = 0;
	Mesh* mesh = nullptr;
};