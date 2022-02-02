#pragma once
#include <list>
#include <functional>

namespace LimeEngine
{
	using EventId = size_t;

	template<typename... TArgs>
	struct Event
	{
		Event(EventId id, std::function<void(TArgs...)> func = nullptr) noexcept : id(id), func(func) {}
		bool operator==(const Event& other) const noexcept
		{
			return id == other.id;
		}
		bool operator==(const EventId otherId) const noexcept
		{
			return id == otherId;
		}
		bool operator!=(const Event& other) const noexcept
		{
			return !(*this == other);
		}
		bool operator!=(const EventId& otherId) const noexcept
		{
			return !(*this == otherId);
		}
		void operator()(TArgs... args)
		{
			func(std::forward<TArgs>(args)...);
		}
		EventId id;
		std::function<void(TArgs...)> func;
	};

	template<typename... TArgs>
	class EventDispatcher
	{
	public:
		EventDispatcher() = default;
		EventId Bind(std::function<void(TArgs...)>&& f)
		{
			events.push_back({ next_id,  std::move(f) });
			return next_id++;
		}
		void Unbind(EventId id)
		{
			events.remove(id);
		}
		EventId operator+=(std::function<void(TArgs...)>&& f)
		{
			Bind(std::move(f));
		}
		void operator-=(EventId id)
		{
			Unbind(id);
		}
		void operator()(TArgs... args)
		{
			for (auto&& f : events)
			{
				f(std::forward<TArgs>(args)...);
			}
		}
	private:
		size_t next_id = 0;
		std::list<Event<TArgs...>> events;
	};
}