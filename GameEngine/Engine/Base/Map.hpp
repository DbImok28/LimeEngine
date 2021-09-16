#pragma once
#include <map>
#include <type_traits>
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture2D.hpp"

template<typename T>
class MapData
{
public:
	template<typename... Args>
	T* Create(size_t id, Args&&... args) noexcept;
	size_t Register(T* item) noexcept;
	void Register(size_t id, T* item) noexcept;
	T* Get(size_t id) noexcept;
	~MapData();
private:
	size_t maxId = 0;
	std::map<size_t, T*> data;
};

class Map
{
public:
	MapData<Mesh> meshes;
	MapData<Material> materials;
	MapData<Texture2D> textures2D;
};

template<typename T>
template<typename ...Args>
T* MapData<T>::Create(size_t id, Args && ...args) noexcept
{
	T* item = new T(std::forward<Args>(args)...);
	Register(id, item);
	return item;
}

template<typename T>
size_t MapData<T>::Register(T* item) noexcept
{
	++maxId;
	data.insert({ maxId, item });
	return maxId;
}

template<typename T>
void MapData<T>::Register(size_t id, T* item) noexcept
{
	maxId = maxId < id ? id : maxId;
	data.insert({ id, item });
}

template<typename T>
T* MapData<T>::Get(size_t id) noexcept
{
	return data.at(id);
}

template<typename T>
MapData<T>::~MapData()
{
	for (auto& item : data)
	{
		delete item.second;
	}
}
