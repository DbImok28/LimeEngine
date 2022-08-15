#pragma once
#include <map>
#include <type_traits>

namespace LimeEngine
{
	template <typename T>
	class GameData
	{
	public:
		template <typename... Args>
		T* Create(size_t id, Args&&... args);
		T* Register(T* item) noexcept;
		T* Register(size_t id, T* item) noexcept;
		T* Get(size_t id);
		~GameData();
		size_t GetLastId() const noexcept
		{
			return maxId;
		}

	private:
		size_t maxId = 0;
		std::map<size_t, T*> data;
	};

	template <typename T>
	template <typename... Args>
	T* GameData<T>::Create(size_t id, Args&&... args)
	{
		T* item = new T(std::forward<Args>(args)...);
		Register(id, item);
		return item;
	}

	template <typename T>
	T* GameData<T>::Register(T* item) noexcept
	{
		++maxId;
		data.insert({ maxId, item });
		return item;
	}

	template <typename T>
	T* GameData<T>::Register(size_t id, T* item) noexcept
	{
		maxId = maxId < id ? id : maxId;
		data.insert({ id, item });
		return item;
	}

	template <typename T>
	T* GameData<T>::Get(size_t id)
	{
		// TODO: out of range
		return data.at(id);
	}

	template <typename T>
	GameData<T>::~GameData()
	{
		for (auto& item : data)
		{
			delete item.second;
		}
	}
}