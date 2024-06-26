// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class GameResource;

	struct GameResourceData
	{
		GameResourceData(uint8* data, uint size) : size(size), data(data) {}
		uint size;
		uint8* data;
	};

	// TODO: Add ResourcePath to string conversion

	class ResourcePath
	{
	public:
		ResourcePath(const char* path);
		ResourcePath(const std::string& path);
		ResourcePath(std::string&& path);
		ResourcePath& operator=(const std::string& path);
		ResourcePath& operator=(std::string&& path);
		ResourcePath& operator=(const char* path);

		ResourcePath(const ResourcePath&) = default;
		ResourcePath(ResourcePath&&) noexcept = default;
		ResourcePath& operator=(const ResourcePath&) = default;
		ResourcePath& operator=(ResourcePath&&) noexcept = default;
		auto operator<=>(const ResourcePath&) const = default;

		const std::string& GetPath() const noexcept;
		void SetPath(const std::string& path);

		// The resource path must consist of a set of letters, numbers, '_' or '-' separated by '\', '/' or ':'
		static bool IsValidPathFormat(const std::string& path) noexcept;

		// The resource path must consist of a set of letters, numbers, '_' or '-' separated by '\', '/' or ':'
		static bool CheckPathFormat(const std::string& path);

	private:
		std::string path;
	};

	template <std::derived_from<GameResource> TResource>
	class GameResourceRef
	{
		friend GameResource;

	public:
		static GameResourceRef<TResource> NullRef() noexcept
		{
			return nullptr;
		};

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
		GameResourceRef() noexcept : resource(nullptr) {}
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
				if (resource) resource->ReleaseRef();
				resource = other.resource;
				if (resource) resource->IncreaseRef();
			}
			return *this;
		}
		GameResourceRef& operator=(GameResourceRef&& other) noexcept
		{
			if (&other != this)
			{
				if (resource) resource->ReleaseRef();
				resource = std::move(other.resource);
				other.resource = nullptr;
				if (resource) resource->IncreaseRef();
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
		uint GetRefCount() const noexcept
		{
			return resource->GetRefCount();
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
		template <std::derived_from<GameResource> TResource>
		friend class GameResourceRef;

	public:
		GameResource(const ResourcePath& resourcePath) : resourcePath(resourcePath) {}
		virtual ~GameResource() = default;

		uint RefCount() const noexcept
		{
			return refCount;
		}
		template <typename TResource>
		GameResourceRef<TResource> GetRef() noexcept
		{
			return GameResourceRef<TResource>(static_cast<TResource*>(this));
		}
		const ResourcePath& GetPath() const
		{
			return resourcePath;
		}
		uint GetRefCount() const noexcept
		{
			return refCount;
		}

	private:
		void IncreaseRef() noexcept
		{
			++refCount;
		}
		void ReleaseRef() noexcept
		{
			--refCount;
		}

	private:
		ResourcePath resourcePath;
		uint refCount = 0u;
	};
}