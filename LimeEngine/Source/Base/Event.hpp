#pragma once

namespace LimeEngine
{
	class Event
	{
	public:
		virtual ~Event() = default;

		virtual const char* GetType() const noexcept
		{
			return "Event";
		}
		bool IsType(const std::string& isType) const noexcept
		{
			return GetType() == isType;
		}
		std::string ToString() const noexcept
		{
			return GetType();
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

#define EVENT_TYPE(eventType)                     \
public:                                           \
	const char* GetType() const noexcept override \
	{                                             \
		return #eventType;                        \
	}

	template <typename... TArgs>
	class EventHandler
	{
	public:
		using type = EventHandler<TArgs...>;

	protected:
		EventHandler() = default;

	public:
		virtual ~EventHandler() noexcept = default;

		virtual void Call(TArgs... args) = 0;
		virtual bool IsEquals(const type& other) const = 0;
		void operator()(TArgs... args)
		{
			Call(std::forward<TArgs>(args)...);
		}
		bool operator==(const type& other) const
		{
			return IsEquals(other);
		}
		bool operator!=(const type& other) const
		{
			return !(*this == other);
		}
	};

	template <typename TObject, typename... TArgs>
	class MethodEventHandler final : public EventHandler<TArgs...>
	{
	public:
		using TMethod = void (TObject::*const)(TArgs...);
		using type = MethodEventHandler<TObject, TArgs...>;

	public:
		MethodEventHandler(TObject& object, TMethod method) : EventHandler<TArgs...>(), object(object), method(method) {}
		virtual ~MethodEventHandler() {}

		void Call(TArgs... args) override final
		{
			(object.*method)(args...);
		}
		bool IsEquals(const EventHandler<TArgs...>& other) const override final
		{
			const type* otherEvent = static_cast<const type*>(&other);
			if (otherEvent) return &object == &otherEvent->object && method == otherEvent->method;
			return false;
		}

	private:
		TObject& object;
		TMethod method;
	};

	template <typename... TArgs>
	class FunctionEventHandler final : public EventHandler<TArgs...>
	{
	public:
		using TFunction = void (*)(TArgs...);
		using type = FunctionEventHandler<TArgs...>;

	public:
		FunctionEventHandler(TFunction fun) : EventHandler<TArgs...>(), fun(fun) {}
		virtual ~FunctionEventHandler() {}

		void Call(TArgs... args) override final
		{
			(*fun)(args...);
		}
		bool IsEquals(const EventHandler<TArgs...>& other) const override final
		{
			const type* otherEvent = static_cast<const type*>(&other);
			if (otherEvent) return fun == otherEvent->fun;
			return false;
		}

	private:
		TFunction fun;
	};

	template <typename... TArgs>
	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		void operator()(TArgs... args)
		{
			auto it = events.begin();
			auto it_end = events.end();
			while (it != it_end)
			{
				auto it_last = it++;
				(*it_last)->Call(std::forward<TArgs>(args)...);
			}
		}
		auto FindEventHandler(const EventHandler<TArgs...>& handler) const noexcept
		{
			return std::find_if(std::begin(events), std::end(events), [&handler](auto& item) { return (*item == handler); });
		}
		void Bind(std::unique_ptr<EventHandler<TArgs...>>&& handler)
		{
			LE_CORE_ASSERT(FindEventHandler(*handler) == events.end(), "Ñan't bind the same events");
			events.push_back(std::move(handler));
		}
		template <typename TObject>
		void Bind(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			Bind(std::make_unique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void Bind(void (*func)(TArgs...))
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			Bind(std::make_unique<FunctionEventHandler<TArgs...>>(func));
		}

		bool Unbind(const EventHandler<TArgs...>& handler) noexcept
		{
			auto it = FindEventHandler(handler);
			if (it != std::end(events))
			{
				events.erase(it, std::end(events));
				return true;
			}
			return false;
		}
		template <typename TObject>
		bool Unbind(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method) noexcept
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			return Unbind(MethodEventHandler{ *object, method });
		}
		bool Unbind(void (*func)(TArgs...)) noexcept
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			return Unbind(FunctionEventHandler{ func });
		}
		void Clear() noexcept
		{
			events.clear();
		}

	private:
		std::list<std::unique_ptr<EventHandler<TArgs...>>> events;
	};

	template <typename TKey, typename... TArgs>
	class MultiEventDispatcher
	{
	public:
		MultiEventDispatcher() = default;

		void operator()(TKey key, TArgs... args)
		{
			auto range = events.equal_range(key);
			for (auto& it = range.first; it != range.second;)
			{
				auto it_last = it++;
				it_last->second->Call(std::forward<TArgs>(args)...);
			}
		}
		auto FindEventHandler(TKey key, const EventHandler<TArgs...>& handler) const noexcept
		{
			auto range = events.equal_range(key);
			return std::find_if(range.first, range.second, [&handler](auto& item) { return (*item.second == handler); });
		}
		void Bind(TKey key, std::unique_ptr<EventHandler<TArgs...>>&& handler)
		{
			LE_CORE_ASSERT(FindEventHandler(key, *handler) == events.end(), "Ñan't bind the same events");
			events.emplace(key, std::move(handler));
		}
		template <typename TObject>
		void Bind(TKey key, TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			Bind(key, std::make_unique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void Bind(TKey key, void (*func)(TArgs...))
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			Bind(key, std::make_unique<FunctionEventHandler<TArgs...>>(func));
		}

		bool Unbind(TKey key, const EventHandler<TArgs...>& handler) noexcept
		{
			auto it = FindEventHandler(key, handler);
			if (it != std::end(events))
			{
				events.erase(it);
				return true;
			}
			return false;
		}
		template <typename TObject>
		bool Unbind(TKey key, TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method) noexcept
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			return Unbind(key, MethodEventHandler{ *object, method });
		}
		bool Unbind(TKey key, void (*func)(TArgs...)) noexcept
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			return Unbind(key, FunctionEventHandler{ func });
		}
		void Clear(TKey key) noexcept
		{
			auto range = events.equal_range(key);
			events.erase(range.first, range.second);
		}
		void Clear() noexcept
		{
			events.clear();
		}

	private:
		std::multimap<TKey, std::unique_ptr<EventHandler<TArgs...>>> events;
	};
}