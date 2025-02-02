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
		LE_ASSERT(e.IsType(TEvent::GetStaticType()), "Event cast failed - event types do not match. Type is {}, expected {}", e.GetType(), TEvent::GetStaticType());
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
		using TMethod = void (TObject::* const)(TArgs...);
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
			if (otherEvent) return std::addressof(object) == std::addressof(otherEvent->object) && method == otherEvent->method;
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
		using TFunction = void (*const)(TArgs...);
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

	template <typename TLambda, typename... TArgs>
	class LambdaEventHandler final : public EventHandler<TArgs...>
	{
	public:
		using type = LambdaEventHandler<TLambda, TArgs...>;

	public:
		LambdaEventHandler(TLambda lambda) : EventHandler<TArgs...>(), lambda(std::move(lambda)) {}
		virtual ~LambdaEventHandler() {}

		void Call(TArgs... args) override final
		{
			lambda(std::forward<TArgs>(args)...);
		}

		bool IsEquals(const EventHandler<TArgs...>& other) const override final
		{
			const type* otherEvent = static_cast<const type*>(&other);
			if (otherEvent) return (std::addressof(lambda) == std::addressof(otherEvent->lambda));
			return false;
		}

	private:
		TLambda lambda;
	};

	template <typename... TArgs>
	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		void operator()(TArgs... args)
		{
#ifdef LE_DEBUG
			size_t originalSize = events.size();
#endif
			auto it = events.begin();
			auto endIt = events.end();
			while (it != endIt)
			{
				auto prevIt = it++;
				(*prevIt)->Call(std::forward<TArgs>(args)...);

				size_t currentSize = events.size();
				LE_ASSERT(originalSize == currentSize, "Cannot remove event handler in event dispatcher");
			}
		}
		auto FindEventHandler(const EventHandler<TArgs...>& handler) const noexcept
		{
			return std::find_if(std::begin(events), std::end(events), [&handler](auto& item) { return (*item == handler); });
		}
		void BindEventHandler(URef<EventHandler<TArgs...>>&& handler)
		{
			bool noFounded = FindEventHandler(*handler) == events.end();
			LE_ASSERT(noFounded, "Can't bind the same events");
			if (noFounded) events.push_back(std::move(handler));
		}
		template <typename TObject>
		void Bind(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_ASSERT(object, "Object pointer cannot be null");
			LE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) BindEventHandler(MakeUnique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void Bind(FunctionEventHandler<TArgs...>::TFunction func)
		{
			LE_ASSERT(func, "Function pointer cannot be null");
			if (func) BindEventHandler(MakeUnique<FunctionEventHandler<TArgs...>>(func));
		}
		template <typename TLambda>
		void Bind(TLambda lambda)
		{
			BindEventHandler(MakeUnique<LambdaEventHandler<TLambda, TArgs...>>(lambda));
		}

		bool UnbindEventHandler(const EventHandler<TArgs...>& handler) noexcept
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
			LE_ASSERT(object, "Object pointer cannot be null");
			LE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) return UnbindEventHandler(MethodEventHandler{ *object, method });
			return false;
		}
		bool Unbind(FunctionEventHandler<TArgs...>::TFunction func) noexcept
		{
			LE_ASSERT(func, "Function pointer cannot be null");
			if (func) return UnbindEventHandler(FunctionEventHandler{ func });
			return false;
		}
		template <typename TLambda>
		void Unbind(TLambda lambda)
		{
			UnbindEventHandler(LambdaEventHandler<TLambda, TArgs...>{ lambda });
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
#ifdef LE_DEBUG
			size_t eventsSize = events.size();
			size_t handlersForAnyEventsSize = handlersForAnyEvents.size();
#endif
			auto range = events.equal_range(key);
			for (auto& it = range.first; it != range.second;)
			{
				auto prevIt = it++;
				prevIt->second->Call(std::forward<TArgs>(args)...);

				size_t currentSize = events.size();
				LE_ASSERT(eventsSize == currentSize, "Cannot remove event handler in event dispatcher");
			}
			for (auto& handler : handlersForAnyEvents)
			{
				handler->Call(std::forward<TArgs>(args)...);

				size_t currentSize = handlersForAnyEvents.size();
				LE_ASSERT(handlersForAnyEventsSize == currentSize, "Cannot remove event handler in event dispatcher");
			}
		}

		auto FindEventHandler(TKey key, const EventHandler<TArgs...>& handler) const noexcept
		{
			auto range = events.equal_range(key);
			for (auto it = range.first; it != range.second; ++it)
			{
				if (*it->second == handler) { return it; }
			}
			return std::end(events);
		}

		void BindEventHandler(TKey key, URef<EventHandler<TArgs...>>&& handler)
		{
			bool noFounded = FindEventHandler(key, *handler) == events.end();
			LE_ASSERT(noFounded, "Can't bind the same events");
			if (noFounded) events.emplace(key, std::move(handler));
		}
		template <typename TObject>
		void Bind(TKey key, TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_ASSERT(object, "Object pointer cannot be null");
			LE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) BindEventHandler(key, MakeUnique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void Bind(TKey key, FunctionEventHandler<TArgs...>::TFunction func)
		{
			LE_ASSERT(func, "Function pointer cannot be null");
			if (func) BindEventHandler(key, MakeUnique<FunctionEventHandler<TArgs...>>(func));
		}
		template <typename TLambda>
		void Bind(TKey key, TLambda lambda)
		{
			BindEventHandler(key, MakeUnique<LambdaEventHandler<TLambda, TArgs...>>(lambda));
		}

		bool UnbindEventHandler(TKey key, const EventHandler<TArgs...>& handler) noexcept
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
			LE_ASSERT(object, "Object pointer cannot be null");
			LE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) return UnbindEventHandler(key, MethodEventHandler{ *object, method });
			return false;
		}
		bool Unbind(TKey key, FunctionEventHandler<TArgs...>::TFunction func) noexcept
		{
			LE_ASSERT(func, "Function pointer cannot be null");
			if (func) return UnbindEventHandler(key, FunctionEventHandler{ func });
			return false;
		}
		template <typename TLambda>
		bool Unbind(TKey key, TLambda lambda)
		{
			return UnbindEventHandler(key, LambdaEventHandler<TArgs...>(lambda));
		}

		// For any events
		auto FindAnyEventHandler(const EventHandler<TArgs...>& handler) const noexcept
		{
			return std::find_if(std::begin(handlersForAnyEvents), std::end(handlersForAnyEvents), [&handler](auto& item) { return (*item == handler); });
		}

		void BindAnyEventHandler(URef<EventHandler<TArgs...>>&& handler)
		{
			bool noFounded = FindAnyEventHandler(*handler) == std::end(handlersForAnyEvents);
			LE_ASSERT(noFounded, "Can't bind the same events");
			if (noFounded) handlersForAnyEvents.emplace_back(std::move(handler));
		}
		template <typename TObject>
		void BindAny(TObject* const object, MethodEventHandler<TObject, TArgs...>::TMethod method)
		{
			LE_ASSERT(object, "Object pointer cannot be null");
			LE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) BindAnyEventHandler(MakeUnique<MethodEventHandler<TObject, TArgs...>>(*object, method));
		}
		void BindAny(FunctionEventHandler<TArgs...>::TFunction func)
		{
			LE_ASSERT(func, "Function pointer cannot be null");
			if (func) BindAnyEventHandler(MakeUnique<FunctionEventHandler<TArgs...>>(func));
		}
		template <typename TLambda>
		void BindAny(TLambda lambda)
		{
			BindAnyEventHandler(MakeUnique<LambdaEventHandler<TLambda, TArgs...>>(lambda));
		}

		bool UnbindAnyEventHandler(const EventHandler<TArgs...>& handler) noexcept
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
			LE_ASSERT(object, "Object pointer cannot be null");
			LE_ASSERT(method, "Method pointer cannot be null");
			if (object && method) return UnbindAnyEventHandler(MethodEventHandler{ *object, method });
			return false;
		}
		bool UnbindAny(FunctionEventHandler<TArgs...>::TFunction func) noexcept
		{
			LE_ASSERT(func, "Function pointer cannot be null");
			if (func) return UnbindAnyEventHandler(FunctionEventHandler{ func });
			return false;
		}
		template <typename TLambda>
		void UnbindAny(TLambda lambda)
		{
			UnbindAnyEventHandler(LambdaEventHandler<TLambda, TArgs...>{ lambda });
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
