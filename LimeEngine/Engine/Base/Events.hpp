#pragma once
#include <list>
#include <memory>
#include <cassert>

namespace LimeEngine
{
	template <typename... TArgs>
	class EventHandler
	{
	public:
		using type = EventHandler<TArgs...>;
		void operator()(TArgs... args)
		{
			Call(std::forward<TArgs>(args)...);
		}
		virtual void Call(TArgs... args) = 0;
		virtual bool IsEquals(const type& other) const = 0;
		bool operator==(const type& other) const
		{
			return IsEquals(other);
		}
		bool operator!=(const type& other) const
		{
			return !(*this == other);
		}
		virtual ~EventHandler() noexcept = default;

	protected:
		EventHandler() = default;
	};

	template <typename TObject, typename... TArgs>
	class MethodEventHandler final : public EventHandler<TArgs...>
	{
	public:
		using TMethod = void (TObject::*const)(TArgs...);
		using type = MethodEventHandler<TObject, TArgs...>;

	private:
		TObject& object;
		TMethod method;

	public:
		MethodEventHandler(TObject& object, TMethod method) : EventHandler<TArgs...>(), object(object), method(method) {}
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
	};

	template <typename... TArgs>
	class FunctionEventHandler final : public EventHandler<TArgs...>
	{
	public:
		using TFunction = void (*)(TArgs...);
		using type = FunctionEventHandler<TArgs...>;

	private:
		TFunction fun;

	public:
		FunctionEventHandler(TFunction fun) : EventHandler<TArgs...>(), fun(fun) {}
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
	};

	template <typename... TArgs>
	class EventDispatcher
	{
	private:
		std::list<std::unique_ptr<EventHandler<TArgs...>>> events;

	public:
		EventDispatcher() = default;
		auto FindEventHandler(const EventHandler<TArgs...>& handler) const noexcept
		{
			return std::find_if(std::begin(events), std::end(events), [&handler](auto& item) { return (*item == handler); });
		}
		template <typename TObject>
		void Bind(TObject* const object, void (TObject::*const method)(TArgs...))
		{
			assert(object && "Object pointer cannot be null");
			assert(method && "Method pointer cannot be null");
			auto ptr = std::make_unique<MethodEventHandler<TObject, TArgs...>>(*object, method);
			assert(FindEventHandler(*ptr) == events.end() && "Ñan't bind the same events");
			events.push_back(std::move(ptr));
		}
		void Bind(void (*func)(TArgs...))
		{
			assert(func && "Function pointer cannot be null");
			auto ptr = std::make_unique<FunctionEventHandler<TArgs...>>(func);
			assert(FindEventHandler(*ptr) == events.end() && "Ñan't bind the same events");
			events.push_back(std::move(ptr));
		}
		template <typename TObject>
		bool Unbind(TObject* const object, void (TObject::*const method)(TArgs...)) noexcept
		{
			assert(object && "Object pointer cannot be null");
			assert(method && "Method pointer cannot be null");
			MethodEventHandler handler{ *object, method };
			return Unbind(handler);
		}
		bool Unbind(void (*func)(TArgs...)) noexcept
		{
			assert(func && "Function pointer cannot be null");
			FunctionEventHandler handler{ func };
			return Unbind(handler);
		}
		bool Unbind(const EventHandler<TArgs...>& handler) noexcept
		{
			auto it = FindEventHandler(handler);
			if (it != std::end(events))
			{
				events.erase(it);
				return true;
			}
			return false;
		}
		void Clear() noexcept
		{
			events.clear();
		}
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
	};
}