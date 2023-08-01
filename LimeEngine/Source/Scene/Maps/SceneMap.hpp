// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "Scene/Objects/SceneObject.hpp"

namespace LimeEngine
{
	class SceneMap : public ScenePrimaryComponent
	{

	public:
		explicit SceneMap(Engine* engine, const std::string& mapName = "SceneMap");
		virtual ~SceneMap() noexcept = default;

		virtual void Load(){};

		SceneObject* SetupAttachment(std::unique_ptr<SceneObject>&& object);

		template <std::derived_from<SceneObject> TObject, typename... TArgs>
		TObject* SetupAttachment(TArgs&&... args) noexcept
		{
			return reinterpret_cast<TObject*>(SetupAttachment(std::make_unique<TObject>(std::forward<TArgs>(args)...)));
		}
		const std::vector<std::unique_ptr<SceneObject>>& GetSubObjects() const noexcept;

		std::string GetMapName() const noexcept;

	protected:
		Engine* engine = nullptr;
	};
}
