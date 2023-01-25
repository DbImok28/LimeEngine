#pragma once
#include <memory>
#include <map>
#include "InputKeys.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Base/Events.hpp"

namespace LimeEngine
{
	struct AxisKey
	{
		AxisKey(InputKey inputKey, float scale) noexcept : inputKey(inputKey), scale(scale) {}

		InputKey inputKey;
		float scale;
	};

	struct InputAxis
	{
		InputAxis(std::string name, std::vector<AxisKey> keys) noexcept : name(name), keys(keys) {}

		std::string name;
		std::vector<AxisKey> keys;
	};

	class InputAxisEvent
	{
	public:
		InputAxisEvent(const std::string& name, float axisScale) noexcept : name(name), axisScale(axisScale) {}
		InputAxisEvent(const std::string& name, float axisScale, std::shared_ptr<IEventHandler<float>>&& handler) :
			name(name), axisScale(axisScale), handlers({ std::move(handler) })
		{}

		void Bind(std::shared_ptr<IEventHandler<float>> handler)
		{
			handlers.push_back(handler);
		}
		void Unbind(const IEventHandler<float>& handler) noexcept
		{
			handlers.erase(std::find_if(std::begin(handlers), std::end(handlers), [&handler](auto& item) { return (*item == handler); }), std::end(handlers));
		}
		void Call(float inputScale)
		{
			for (auto& handler : handlers)
			{
				handler->Call(axisScale * inputScale);
			}
		}

	public:
		std::string name;
		float axisScale;
		std::vector<std::shared_ptr<IEventHandler<float>>> handlers;
	};

	class InputDevice
	{
		friend class Window;

	public:
		void AddInputAxis(const InputAxis& inputAxis)
		{
			for (auto& axisKey : inputAxis.keys)
			{
				keyAxisEvents.emplace(axisKey.inputKey, InputAxisEvent{ inputAxis.name, axisKey.scale });
			}
		}
		void RemoveInputAxis(const InputAxis& inputAxis) noexcept
		{
			RemoveInputAxis(inputAxis.name);
		}
		void RemoveInputAxis(const std::string& name) noexcept
		{
			keyAxisEvents.erase(
				std::find_if(std::begin(keyAxisEvents), std::end(keyAxisEvents), [&name](auto& item) { return item.second.name == name; }), std::end(keyAxisEvents));
		}
		void RebindInputAxisKey(const std::string& axisName, InputKey oldKey, InputKey newKey) noexcept
		{
			for (auto it = std::begin(keyAxisEvents); it != std::end(keyAxisEvents); it++)
			{
				if (it->first == oldKey && it->second.name == axisName)
				{
					auto node = keyAxisEvents.extract(it);
					node.key() = newKey;
					keyAxisEvents.insert(std::move(node));
					break;
				}
			}
		}
		template <typename TObject>
		void BindAxisEvent(const std::string& axisName, TObject* const object, void (TObject::*const method)(float))
		{
			BindAxisEvent(axisName, std::make_shared<MethodEventHandler<TObject, float>>(*object, method));
		}
		void BindAxisEvent(const std::string& axisName, std::shared_ptr<IEventHandler<float>> handler)
		{
			for (auto& keyAxisEvent : keyAxisEvents)
			{
				if (keyAxisEvent.second.name == axisName)
				{
					keyAxisEvent.second.Bind(handler);
				}
			}
		}
		template <typename TObject>
		void UnbindAxisEvent(const std::string& axisName, TObject* const object, void (TObject::*const method)(float)) noexcept
		{
			UnbindAxisEvent(axisName, MethodEventHandler<TObject, float>(*object, method));
		}
		void UnbindAxisEvent(const std::string& axisName, const IEventHandler<float>& handler) noexcept
		{
			for (auto& keyAxisEvent : keyAxisEvents)
			{
				if (keyAxisEvent.second.name == axisName)
				{
					keyAxisEvent.second.Unbind(handler);
				}
			}
		}
		void UpdateKey(InputKey key, float inputScale = 1.0f) noexcept
		{
			auto axisEventsIt = keyAxisEvents.equal_range(key);
			for (auto& it = axisEventsIt.first; it != axisEventsIt.second; it++)
			{
				it->second.Call(inputScale);
			}
		}
		void OnKeyPressed(InputKey key) noexcept
		{
			pressedKeys.push_back(key);
		}
		void OnKeyReleased(InputKey key)
		{
			for (auto it = std::begin(pressedKeys); it != std::end(pressedKeys); it++)
			{
				if (*it == key)
				{
					pressedKeys.erase(it);
					break;
				}
			}
		}
		void OnKeyAction(InputKey actionKey, float scale) noexcept
		{
			keyActions.push({ actionKey, scale });
		}

		// ---------
		void ClearKeyState() noexcept
		{
			keyboard.ClearKeyState();
			pressedKeys.clear();
		}
		void OnKeyboardChar(char key) noexcept
		{
			keyboard.OnChar(key);
		}
		void OnKeyboardKeyPressed(InputKey key) noexcept
		{
			OnKeyPressed(key);
			keyboard.OnKeyPressed(static_cast<unsigned char>(key));
		}
		void OnKeyboardKeyReleased(InputKey key) noexcept
		{
			OnKeyReleased(key);
			keyboard.OnKeyReleased(static_cast<unsigned char>(key));
		}

		void OnMouseLeftPressed(int x, int y) noexcept
		{
			mouse.OnLeftPressed(x, y);
			OnKeyPressed(InputKey::LeftMouseButton);
		}
		void OnMouseLeftReleased(int x, int y) noexcept
		{
			mouse.OnLeftReleased(x, y);
			OnKeyReleased(InputKey::LeftMouseButton);
		}

		void OnMouseRightPressed(int x, int y) noexcept
		{
			mouse.OnRightPressed(x, y);
			OnKeyPressed(InputKey::RightMouseButton);
		}
		void OnMouseRightReleased(int x, int y) noexcept
		{
			mouse.OnRightReleased(x, y);
			OnKeyReleased(InputKey::RightMouseButton);
		}

		void OnMouseMiddlePressed(int x, int y) noexcept
		{
			mouse.OnMiddlePressed(x, y);
			OnKeyPressed(InputKey::MiddleMouseButton);
		}
		void OnMouseMiddleReleased(int x, int y) noexcept
		{
			mouse.OnMiddleReleased(x, y);
			OnKeyReleased(InputKey::MiddleMouseButton);
		}
		void OnMouseWheelDelta(int x, int y, int delta) noexcept
		{
			mouse.OnWheelDelta(x, y, delta);
			if (delta >= WHEEL_DELTA)
			{
				OnKeyAction(InputKey::WheelUp, delta);
			}
			else
			{
				OnKeyAction(InputKey::WheelDown, delta);
			}
		}

		void OnMouseMove(int x, int y) noexcept
		{
			mouse.OnMouseMove(x, y);
		}
		void OnMouseRawMove(int x, int y) noexcept
		{
			mouse.OnMouseRawMove(x, y);
			if (x != 0)
			{
				OnKeyAction(InputKey::MouseMoveX, x);
			}
			if (y != 0)
			{
				OnKeyAction(InputKey::MouseMoveY, y);
			}
		}

		void OnMouseLeave() noexcept
		{
			mouse.OnMouseLeave();
		}
		void OnMouseEnter() noexcept
		{
			mouse.OnMouseEnter();
		}

		void Update() noexcept
		{
			for (auto& key : pressedKeys)
			{
				UpdateKey(key);
			}

			while (!keyActions.empty())
			{
				auto keyAction = keyActions.front();
				UpdateKey(keyAction.first, keyAction.second);
				keyActions.pop();
			}
		}

	public:
		Keyboard keyboard;
		Mouse mouse;

	private:
		std::multimap<InputKey, InputAxisEvent> keyAxisEvents;
		std::list<InputKey> pressedKeys;
		std::queue<std::pair<InputKey, float>> keyActions;
	};
}