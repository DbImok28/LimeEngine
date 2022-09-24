#include "Primitives.hpp"
#include "Vertex.hpp"
#include "Math.hpp"
#include "../Engine.hpp"

namespace LimeEngine
{
	GameResourceRef<Mesh> Primitive::CreateMesh(Engine* engine, const std::string& gamePath) const
	{
		return engine->gameDataManager.CreateMesh(gamePath, vertices, indices);
	}

	Plane::Plane(float size, uint8 segmentsLength, uint8 segmentsWidth)
	{
		const uint8 totalLength = segmentsLength + 2u;
		const uint8 totalWidth = segmentsWidth + 2u;

		vertices.clear();
		indices.clear();
		vertices.reserve(static_cast<size_t>(totalLength) * static_cast<size_t>(totalWidth));
		indices.reserve((static_cast<size_t>(totalLength) - 1u) * (static_cast<size_t>(totalWidth) - 1u) * 6u);

		const float dx = 1.0f / static_cast<float>(totalLength - 1);
		const float dy = 1.0f / static_cast<float>(totalWidth - 1);

		for (uint16 i = 0u; i < totalLength; i++)
		{
			for (uint16 j = 0u; j < totalWidth; j++)
			{
				vertices.push_back({ i * dx * size, 0.0f, j * dy * size, 0.0f, 1.0f, 0.0f, i * dx, Math::FlipUV(j * dy) });
			}
		}
		for (uint16 j = 0u; j < totalWidth - 1u; j++)
		{
			for (uint16 i = 0u; i < totalLength - 1u; i++)
			{
				uint pos = j + i * totalWidth;
				indices.push_back(pos + totalWidth + 1u);
				indices.push_back(pos + totalWidth);
				indices.push_back(pos);
				indices.push_back(pos + 1u);
				indices.push_back(pos + totalWidth + 1u);
				indices.push_back(pos);
			}
		}
	}

	Cubesphere::Cubesphere(float radius, uint8 subdivisions)
	{
		uint16 vertexCountPerRow = static_cast<uint16>(pow(2, subdivisions) + 1u);
		std::vector<Vector> projectedVertices = ProjectPlane(vertexCountPerRow);
		vertices.clear();
		indices.clear();
		vertices.reserve(static_cast<size_t>(vertexCountPerRow) * static_cast<size_t>(vertexCountPerRow) * 6u);
		indices.reserve((static_cast<size_t>(vertexCountPerRow) - 1u) * (static_cast<size_t>(vertexCountPerRow) - 1u) * 6u * 6u);

		for (uint32 i = 0u, k = 0u; i < vertexCountPerRow; ++i) // +X
		{
			uint k1 = i * vertexCountPerRow;
			uint k2 = k1 + vertexCountPerRow;
			float v = static_cast<float>(i) / static_cast<float>(vertexCountPerRow - 1u);

			for (uint32 j = 0u; j < vertexCountPerRow; ++j, ++k, ++k1, ++k2)
			{
				float u = Math::FlipUV(static_cast<float>(j) / static_cast<float>(vertexCountPerRow - 1u));
				vertices.push_back({
					projectedVertices[k] * radius, projectedVertices[k], {u, v}
                });

				if (i < (vertexCountPerRow - 1u) && j < (vertexCountPerRow - 1u))
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1u);

					indices.push_back(k1 + 1u);
					indices.push_back(k2);
					indices.push_back(k2 + 1u);
				}
			}
		}
		size_t vertexCount = vertices.size();
		size_t indicesCount = indices.size();

		BuildByCopy({ -1, 1, -1 }, AxisOrder::XYZ, vertexCount, indicesCount); // -X

		BuildByCopy({ -1, 1, -1 }, AxisOrder::ZXY, vertexCount, indicesCount); // +Y
		BuildByCopy({ -1, -1, 1 }, AxisOrder::ZXY, vertexCount, indicesCount); // -Y

		BuildByCopy({ -1, 1, 1 }, AxisOrder::ZYX, vertexCount, indicesCount); // +Z
		BuildByCopy({ 1, 1, -1 }, AxisOrder::ZYX, vertexCount, indicesCount); // -Z
	}

	void Cubesphere::BuildByCopy(Vector direction, AxisOrder order, size_t vertexCount, size_t indicesCount)
	{
		size_t startIndex = vertices.size();
		for (size_t i = 0ull; i < vertexCount; ++i)
		{
			vertices.push_back(Vertex{ direction * Vector(vertices[i].pos).GetByOrder(order), direction * Vector(vertices[i].normal).GetByOrder(order), vertices[i].texCoord });
		}
		for (size_t i = 0ull; i < indicesCount; ++i)
		{
			indices.push_back(static_cast<DWORD>(startIndex) + indices[i]);
		}
	}

	std::vector<Vector> Cubesphere::ProjectPlane(uint32 vertexCount) const
	{
		std::vector<Vector> result;
		result.reserve(static_cast<size_t>(vertexCount) * static_cast<size_t>(vertexCount));
		for (float i = 0.0f; i < vertexCount; ++i)
		{
			float a2 = Math::toRad * (45.0f - 90.0f * i / static_cast<float>(vertexCount - 1u)); // normal
			Vector n2{ -Math::Sin(a2), Math::Cos(a2), 0.0f };                                    // plane rotating along Z-axis
			for (float j = 0.0f; j < vertexCount; ++j)
			{
				float a1 = Math::toRad * (-45.0f + 90.0f * j / static_cast<float>(vertexCount - 1u)); // normal
				Vector n1{ -Math::Sin(a1), 0.0f, -Math::Cos(a1) };                                    // plane rotating along Y-axis
				Vector v = Vector::Normalize(Vector::Cross(n1, n2));                                  // direction
				result.push_back(v);
			}
		}
		return result;
	}

	Sphere::Sphere(float radius, uint8 rings, uint8 segments)
	{
		vertices.clear();
		indices.clear();
		vertices.reserve((static_cast<size_t>(rings) + 1u) * (static_cast<size_t>(segments) + 1u));
		indices.reserve((static_cast<size_t>(rings) - 1u) * (static_cast<size_t>(segments)) * 6u);

		float lengthInv = 1.0f / radius; // normal

		float segmentsStep = 2.0f * Math::pi / static_cast<float>(segments);
		float ringsStep = Math::pi / static_cast<float>(rings);

		for (float i = 0.0f; i <= rings; ++i)
		{
			float ringsAngle = Math::pi / 2.0f - i * ringsStep;
			float xz = radius * cosf(ringsAngle);
			float y = radius * sinf(ringsAngle);

			for (float j = 0.0f; j <= segments; ++j)
			{
				float segmentsAngle = j * segmentsStep;

				float x = xz * cosf(segmentsAngle); // r * cos(u) * cos(v)
				float z = xz * sinf(segmentsAngle); // r * cos(u) * sin(v)

				float nx = x * lengthInv;
				float ny = y * lengthInv;
				float nz = z * lengthInv;

				float u = j / static_cast<float>(segments);
				float v = i / static_cast<float>(rings);
				// Shift of UV coordinates from top and bottom
				if (i == 0u)
				{
					v += 1.0f / (static_cast<float>(rings));
				}
				if (i == (rings))
				{
					v -= 1.0f / (static_cast<float>(rings));
				}

				vertices.push_back({ x, y, z, nx, ny, nz, u, v });
			}
		}
		for (uint8 i = 0u; i < rings; ++i)
		{
			uint16 k1 = i * (segments + 1);
			uint16 k2 = k1 + segments + 1;

			for (uint8 j = 0u; j < segments; ++j, ++k1, ++k2)
			{
				if (i != 0u)
				{
					indices.push_back(k1 + 1u);
					indices.push_back(k2);
					indices.push_back(k1);
				}
				if (i != (rings - 1u))
				{
					indices.push_back(k2 + 1u);
					indices.push_back(k2);
					indices.push_back(k1 + 1u);
				}
			}
		}
	}
}