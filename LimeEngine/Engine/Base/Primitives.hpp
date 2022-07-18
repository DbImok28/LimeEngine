#pragma once
#include "../CoreBase.hpp"
#include "../Graphics/Base/Mesh.hpp"
#include <vector>

namespace LimeEngine
{
	class Primitive
	{
	public:
		Mesh* CreateMesh(Engine* engine);

	protected:
		std::vector<Vertex> vertices;
		std::vector<DWORD> indices;
	};

	struct Plane : public Primitive
	{
		Plane(float size, uint8 segmentsLength, uint8 segmentsWidth);
	};

	struct Cubesphere : public Primitive
	{
		Cubesphere(float radius, uint8 subdivisions);

	private:
		void BuildByCopy(Vector direction, AxisOrder order, size_t vertexCount, size_t indicesCount);
		std::vector<Vector> ProjectPlane(uint32 vertexCount) const;
	};

	struct Sphere : public Primitive
	{
		Sphere(float radius, uint8 rings, uint8 segments);
	};
}