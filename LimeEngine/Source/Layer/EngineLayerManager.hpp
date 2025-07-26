// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "EngineLayer.hpp"
#include "Diagnostics/OutputLogPanel.hpp"

namespace LimeEngine
{
	class EngineLayerManager
	{
	public:
		void Init()
		{
			ResolvePendingLayerDependencies();
			LE_ASSERT(pendingLayerDependencies.empty(), "Failed to resolve all layer dependencies");

			for (const auto& layer : layersOrder)
			{
				layer->Init();
			}
		}

		void Begin()
		{
			for (const auto& layer : layersOrder)
			{
				layer->Begin();
			}

			for (const auto& pair : layerDependencies)
			{
				const std::string& layerName = pair.first;
				const std::vector<const char*>& dependencies = pair.second;

				LE_LOG_INFO(LogEngineLayer, layerName);
				if (!dependencies.empty())
				{
					for (auto dependency : dependencies)
					{
						LE_LOG_INFO(LogEngineLayer, "- {}", dependency);
					}
				}
			}
		}

		void End()
		{
			for (auto it = std::rbegin(layersOrder); it != layersOrder.rend();)
			{
				(*it)->End();
				++it;
			}
		}

		~EngineLayerManager()
		{
			for (auto it = std::rbegin(layersOrder); it != layersOrder.rend();)
			{
				it = decltype(it)(layersOrder.erase(std::next(it).base()));
			}
		}

		virtual void PreUpdate()
		{
			for (const auto& layer : layersOrder)
			{
				layer->PreUpdate();
			}
		}

		void Update()
		{
			for (const auto& layer : layersOrder)
			{
				layer->Update();
			}
		}

		void DebugUpdate()
		{
			for (const auto& layer : layersOrder)
			{
				layer->DebugUpdate();
			}
		}

		virtual void PostUpdate()
		{
			for (const auto& layer : layersOrder)
			{
				layer->PostUpdate();
			}
		}

		template <std::derived_from<EngineLayer> TLayer, typename... TArgs>
		TLayer* EmplaceLayer(TArgs&&... args)
		{
			return reinterpret_cast<TLayer*>(AddLayer(MakeUnique<TLayer>(std::forward<TArgs>(args)...), TLayer::GetLayerDependencies()));
		}

		template <std::derived_from<EngineLayer> TLayer>
		TLayer* AddLayer(URef<TLayer>&& newLayer)
		{
			return reinterpret_cast<TLayer*>(AddLayer(std::move(newLayer), TLayer::GetLayerDependencies()));
		}

		EngineLayer* AddLayer(URef<EngineLayer>&& newLayer, const std::vector<const char*>& dependencies)
		{
			auto insertedLayer = layers.emplace_back(std::move(newLayer)).get();

#if defined(LE_DEBUG)
			layerDependencies.emplace(insertedLayer->GetLayerName().c_str(), dependencies);
			LE_ASSERT(!HasCircularDependency(insertedLayer, dependencies), "{} has a circular dependency", insertedLayer->GetLayerName());
#endif
			ResolveLayerDependenciesOrDefer(insertedLayer, dependencies);
			return insertedLayer;
		}

	private:
		void ResolveLayerDependenciesOrDefer(EngineLayer* newLayer, const std::vector<const char*>& dependencies)
		{
			if (!TryResolveLayerDependencies(newLayer, dependencies)) DeferDependencyResolution(newLayer, dependencies);
		}

		void DeferDependencyResolution(EngineLayer* newLayer, const std::vector<const char*>& dependencies)
		{
			pendingLayerDependencies.emplace_back(newLayer, dependencies);
		}

		bool TryResolveLayerDependencies(EngineLayer* newLayer, const std::vector<const char*>& dependencies)
		{
			if (dependencies.size() > layersOrder.size()) return false;

			if (dependencies.empty())
				layersOrder.push_back(newLayer);
			else
			{
				auto pos = FindPositionByDependencies(dependencies);
				if (pos == std::end(layersOrder)) return false;
				layersOrder.insert(++pos, newLayer);
			}
			return true;
		}

		void ResolvePendingLayerDependencies()
		{
			bool isResolved = true;
			while (!pendingLayerDependencies.empty() && isResolved)
			{
				isResolved = false;
				for (auto it = std::begin(pendingLayerDependencies); it != std::end(pendingLayerDependencies);)
				{
					if (TryResolveLayerDependencies(it->first, it->second))
					{
						it = pendingLayerDependencies.erase(it);
						isResolved = true;
					}
					else
						++it;
				}
			}
		}

		// TODO: Rename
		Array<EngineLayer*>::iterator FindPositionByDependencies(const std::vector<const char*>& dependencies)
		{
			auto maxIt = std::begin(layersOrder);
			for (const char* dependencyName : dependencies)
			{
				auto it = std::find_if(std::begin(layersOrder), std::end(layersOrder), [&dependencyName](auto layer) { return layer->GetLayerName() == dependencyName; });
				if (it == std::end(layersOrder)) return std::end(layersOrder);
				if (it > maxIt) maxIt = it;
			}
			return maxIt;
		}

#if defined(LE_DEBUG)
		bool HasCircularDependency(EngineLayer* newLayer, const std::vector<const char*>& dependencies)
		{
			std::set<const char*> visited;
			return CheckDependenciesRecursive(newLayer->GetLayerName().c_str(), dependencies, visited);
		}

		bool CheckDependenciesRecursive(const char* currentLayer, const std::vector<const char*>& newDependencies, std::set<const char*> visited)
		{
			if (visited.count(currentLayer)) return true;

			visited.insert(currentLayer);
			for (const char* dependency : newDependencies)
			{
				auto it = layerDependencies.find(dependency);
				if (it != layerDependencies.end())
				{
					std::vector<const char*> depDependencies = it->second;
					if (CheckDependenciesRecursive(dependency, depDependencies, visited)) return true;
				}
			}
			visited.erase(currentLayer);
			return false;
		}
#endif

	public:
		List<URef<EngineLayer>> layers;
		Array<EngineLayer*> layersOrder;
		Array<std::pair<EngineLayer*, std::vector<const char*>>> pendingLayerDependencies;

#if defined(LE_DEBUG)
		std::map<std::string, std::vector<const char*>> layerDependencies;
#endif
	};
}
