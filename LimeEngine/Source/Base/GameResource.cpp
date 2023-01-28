#include "lepch.hpp"
#include "GameResource.hpp"

namespace LimeEngine
{
	ResourcePath& ResourcePath::operator=(const std::string& path)
	{
		SetPath(path);
		return *this;
	}

	ResourcePath& ResourcePath::operator=(std::string&& path)
	{
		SetPath(std::move(path));
		return *this;
	}

	ResourcePath& ResourcePath::operator=(const char* path)
	{
		*this = std::string(path);
		return *this;
	}

	ResourcePath::ResourcePath(const char* path) : path(path)
	{
		CheckPathFormat(this->path);
	}

	ResourcePath::ResourcePath(const std::string& path) : path(path)
	{
		CheckPathFormat(this->path);
	}

	ResourcePath::ResourcePath(std::string&& path) : path(std::move(path))
	{
		CheckPathFormat(this->path);
	}

	const std::string& ResourcePath::GetPath() const noexcept
	{
		return path;
	}
	void ResourcePath::SetPath(const std::string& path)
	{
		CheckPathFormat(path);
		this->path = path;
	}

	bool ResourcePath::IsValidPathFormat(const std::string& path) noexcept
	{
		bool mustBeLetter = true;
		for (auto& symbol : path)
		{
			if (std::isalnum(symbol) || symbol == '_' || symbol == '-')
			{
				mustBeLetter = false;
			}
			else if (!mustBeLetter && (symbol == '\\' || symbol == '/' || symbol == ':'))
			{
				mustBeLetter = true;
			}
			else
			{
				return false;
			}
		}
		if (mustBeLetter) return false;
		return true;
	}

	bool ResourcePath::CheckPathFormat(const std::string& path)
	{
		auto str = "The resource path \"" + path + "\" is not in the correct format.";
		if (!IsValidPathFormat(path)) throw MSG_EXCEPTION(str);
	}
}