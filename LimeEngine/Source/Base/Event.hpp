// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "CoreBase.hpp"

namespace LimeEngine
{
	class Event
	{
	public:
		virtual ~Event() = default;

		static const char* GetStaticType()
		{
			return "Event";
		}
		virtual const char* GetType() const noexcept
		{
			return GetStaticType();
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
	static const char* GetStaticType()            \
	{                                             \
		return #eventType;                        \
	}                                             \
	const char* GetType() const noexcept override \
	{                                             \
		return GetStaticType();                   \
	}

	template <typename TEvent>
	const TEvent& CastEvent(const Event& e)
	{
		LE_CORE_ASSERT(e.IsType(TEvent::GetStaticType()), "Event cast failed - event types do not match. Type is {}, expected {}", e.GetType(), TEvent::GetStaticType());
		return static_cast<const TEvent&>(e);
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
			(object.*method)(std::forward<TArgs>(args)...);
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
			(*fun)(std::forward<TArgs>(args)...);
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
		void Bind(URef<EventHandler<TArgs...>>&& handler)
		{
			bool noFinded = FindEventHandler(*handler) == events.end();
			LE_CORE_ASSERT(noFinded, "Can't bind the same events");
			if (noFinded) events.push_back(std::move(handler));
		}
		template <typename TObject>
		void Bind(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) Bind(MakeUnique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void Bind(void (*func)(TArgs...))
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			if (func) Bind(MakeUnique<FunctionEventHandler<TArgs...>>(func));
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
			if (object && method) return Unbind(MethodEventHandler{ *object, method });
			return false;
		}
		bool Unbind(void (*func)(TArgs...)) noexcept
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			if (func) return Unbind(FunctionEventHandler{ func });
			return false;
		}
		void Clear() noexcept
		{
			events.clear();
		}

	private:
		std::list<URef<EventHandler<TArgs...>>> events;
	};

	template <typename TKey, typename... TArgs>
	class CustomMultiEventDispatcher
	{
	public:
		CustomMultiEventDispatcher() = default;

		void operator()(TKey key, TArgs... args)
		{
			auto range = events.equal_range(key);
			for (auto& it = range.first; it != range.second;)
			{
				auto it_last = it++;
				it_last->second->Call(std::forward<TArgs>(args)...);
			}
			for (auto& handler : handlersForAnyEvents)
			{
				handler->Call(std::forward<TArgs>(args)...);
			}
		}

		auto FindEventHandler(TKey key, const EventHandler<TArgs...>& handler) const noexcept
		{
			auto range = events.equal_range(key);
			for (auto it = range.first; it != range.second; ++it)
			{
				if (*it->second == handler)
				{
					return it;
				}
			}
			return std::end(events);
		}

		void Bind(TKey key, URef<EventHandler<TArgs...>>&& handler)
		{
			bool noFinded = FindEventHandler(key, *handler) == events.end();
			LE_CORE_ASSERT(noFinded, "Can't bind the same events");
			if (noFinded) events.emplace(key, std::move(handler));
		}
		template <typename TObject>
		void Bind(TKey key, TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) Bind(key, MakeUnique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void Bind(TKey key, void (*func)(TArgs...))
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			if (func) Bind(key, MakeUnique<FunctionEventHandler<TArgs...>>(func));
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
			if (object && method) return Unbind(key, MethodEventHandler{ *object, method });
			return false;
		}
		bool Unbind(TKey key, void (*func)(TArgs...)) noexcept
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			if (func) return Unbind(key, FunctionEventHandler{ func });
			return false;
		}

		// For any events
		auto FindAnyEventHandler(const EventHandler<TArgs...>& handler) const noexcept
		{
			return std::find_if(std::begin(handlersForAnyEvents), std::end(handlersForAnyEvents), [&handler](auto& item) { return (*item == handler); });
		}

		void BindAny(URef<EventHandler<TArgs...>>&& handler)
		{
			bool noFinded = FindAnyEventHandler(*handler) == std::end(handlersForAnyEvents);
			LE_CORE_ASSERT(noFinded, "Can't bind the same events");
			if (noFinded) handlersForAnyEvents.emplace_back(std::move(handler));
		}
		template <typename TObject>
		void BindAny(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) BindAny(MakeUnique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void BindAny(void (*func)(TArgs...))
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			if (func) BindAny(MakeUnique<FunctionEventHandler<TArgs...>>(func));
		}

		bool UnbindAny(const EventHandler<TArgs...>& handler) noexcept
		{
			auto it = FindAnyEventHandler(handler);
			if (it != std::end(handlersForAnyEvents))
			{
				handlersForAnyEvents.erase(it);
				return true;
			}
			return false;
		}
		template <typename TObject>
		bool UnbindAny(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method) noexcept
		{
			LE_CORE_ASSERT(object, "Object pointer cannot be null");
			LE_CORE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) return UnbindAny(MethodEventHandler{ *object, method });
			return false;
		}
		bool UnbindAny(void (*func)(TArgs...)) noexcept
		{
			LE_CORE_ASSERT(func, "Function pointer cannot be null");
			if (func) return UnbindAny(FunctionEventHandler{ func });
			return false;
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
		void ClearAny() noexcept
		{
			handlersForAnyEvents.clear();
		}

	private:
		std::multimap<TKey, URef<EventHandler<TArgs...>>> events;
		std::list<URef<EventHandler<TArgs...>>> handlersForAnyEvents;
	};

	template <typename TKey>
	using MultiEventDispatcher = CustomMultiEventDispatcher<TKey, const Event&>;
}
