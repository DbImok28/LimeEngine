#pragma once
#include "CoreBase.hpp"
#include <concepts>

namespace LimeEngine
{
	struct GameResourceData
	{
		GameResourceData(uint8* data, uint size) : size(size), data(data) {}
		uint size;
		uint8* data;
	};

	class GameResource;

	template <std::derived_from<GameResource> TResource>
	class GameResourceRef
	{
		friend GameResource;

	private:
		GameResourceRef(TResource& resource) noexcept : resource(&resource)
		{
			if (resource) resource->IncreaseRef();
		}
		GameResourceRef(TResource* resource) noexcept : resource(resource)
		{
			if (resource) resource->IncreaseRef();
		}

	public:
		GameResourceRef(const GameResourceRef& other) noexcept : resource(other.resource)
		{
			if (resource) resource->IncreaseRef();
		}
		GameResourceRef(GameResourceRef&& other) noexcept : resource(std::move(other.resource))
		{
			other.resource = nullptr;
		}
		GameResourceRef& operator=(const GameResourceRef& other) noexcept
		{
			if (&other != this)
			{
				resource = other.resource;
				if (resource) resource->IncreaseRef();
			}
			return *this;
		}
		GameResourceRef& operator=(GameResourceRef&& other) noexcept
		{
			if (&other != this)
			{
				resource = std::move(other.resource);
				other.resource = nullptr;
			}
			return *this;
		}
		~GameResourceRef() noexcept
		{
			if (resource) resource->ReleaseRef();
		}

		TResource* operator->()
		{
			return resource;
		}
		TResource& operator*()
		{
			return *resource;
		}
		const TResource* operator->() const
		{
			return resource;
		}
		const TResource& operator*() const
		{
			return *resource;
		}

		TResource* Get() const noexcept
		{
			return resource;
		}
		GameResourceRef<TResource> GetRef() noexcept
		{
			return resource->GetRef();
		}
		template <std::derived_from<GameResource> TResource>
		GameResourceRef<TResource> GetRef() noexcept
		{
			return resource->GetRef();
		}
		std::string GetPath() const noexcept
		{
			return resource->GetPath();
		}
		bool IsNull() const noexcept
		{
			return !resource;
		}

	private:
		TResource* resource;
	};

	class GameResource
	{
	public:
		GameResource(const std::string& gamePath) : gamePath(gamePath) {}
		virtual ~GameResource() = default;

		uint RefCount() const noexcept
		{
			return refCount;
		}
		template <typename TResource>
		GameResourceRef<TResource> GetRef() noexcept
		{
			++refCount;
			return GameResourceRef<TResource>(static_cast<TResource*>(this));
		}
		void IncreaseRef() noexcept
		{
			++refCount;
		}
		void ReleaseRef() noexcept
		{
			--refCount;
		}
		const std::string& GetPath() const
		{
			return gamePath;
		}

	private:
		const std::string gamePath;
		uint refCount = 0u;
	};
}