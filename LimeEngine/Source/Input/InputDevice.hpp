#pragma once
#include <memory>
#include <map>
#include "InputKeys.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Base/Events.hpp"

namespace LimeEngine
{
	struct InputAxisKey
	{
		InputAxisKey(InputKey inputKey, float scale) noexcept : inputKey(inputKey), scale(scale) {}

		InputKey inputKey;
		float scale;
	};

	struct InputAxis
	{
		InputAxis(const std::string& name, std::vector<InputAxisKey> keys) noexcept : name(name), keys(keys) {}

		std::string name;
		std::vector<InputAxisKey> keys;
	};

	class InputAxisKeyHandlers
	{
	public:
		InputAxisKeyHandlers(const std::string& name, float axisScale) noexcept : name(name), axisScale(axisScale) {}
		InputAxisKeyHandlers(const std::string& name, float axisScale, std::shared_ptr<IEventHandler<float>>&& handler) :
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

	enum class InputActionType
	{
		Pressed,
		Released
	};

	struct InputActionKey
	{
		InputActionKey(InputKey inputKey) noexcept : inputKey(inputKey) {}

		InputKey inputKey;
	};

	struct InputAction
	{
		InputAction(const std::string& name, std::vector<InputActionKey> keys) noexcept : name(name), keys(keys) {}

		std::string name;
		std::vector<InputActionKey> keys;
	};

	class InputActionKeyHandlers
	{
	public:
		InputActionKeyHandlers(const std::string& name) noexcept : name(name) {}
		InputActionKeyHandlers(const std::string& name, InputActionType actionType, std::shared_ptr<IEventHandler<>>&& actionHandler) :
			name(name), handlers({ std::make_pair(actionType, actionHandler) })
		{}

		void Bind(InputActionType type, std::shared_ptr<IEventHandler<>> handler)
		{
			handlers.push_back(std::make_pair(type, handler));
		}
		void Unbind(InputActionType type, const IEventHandler<>& handler) noexcept
		{
			handlers.erase(
				std::find_if(std::begin(handlers), std::end(handlers), [&type, &handler](auto& item) { return (item.first == type && *item.second == handler); }),
				std::end(handlers));
		}
		void Call(InputActionType type)
		{
			for (auto& handler : handlers)
			{
				if (handler.first == type)
				{
					handler.second->Call();
				}
			}
		}

	public:
		std::string name;
		std::vector<std::pair<InputActionType, std::shared_ptr<IEventHandler<>>>> handlers;
	};

	class InputDevice
	{
		friend class Window;

	public:
		void AddActionMapping(const InputAction& inputAction)
		{
			AddActionMapping(inputAction.name, inputAction.keys);
		}
		void AddActionMapping(const std::string& actionName, std::vector<InputActionKey> actionKeys)
		{
			for (auto& key : actionKeys)
			{
				keyActionEvents.emplace(key.inputKey, InputActionKeyHandlers{ actionName });
			}
		}
		void RemoveActionMapping(const InputAction& inputAction) noexcept
		{
			RemoveActionMapping(inputAction.name);
		}
		void RemoveActionMapping(const std::string& actionName) noexcept
		{
			keyActionEvents.erase(
				std::find_if(std::begin(keyActionEvents), std::end(keyActionEvents), [&actionName](auto& item) { return item.second.name == actionName; }),
				std::end(keyActionEvents));
		}
		void RebindActionKey(const std::string& actionName, InputKey oldKey, InputKey newKey) noexcept
		{
			for (auto it = std::begin(keyActionEvents); it != std::end(keyActionEvents); it++)
			{
				if (it->first == oldKey && it->second.name == actionName)
				{
					auto node = keyActionEvents.extract(it);
					node.key() = newKey;
					keyActionEvents.insert(std::move(node));
					break;
				}
			}
		}
		template <typename TObject>
		void BindActionEvent(const std::string& actionName, InputActionType type, TObject* const object, void (TObject::*const method)())
		{
			BindActionEvent(actionName, type, std::make_shared<MethodEventHandler<TObject>>(*object, method));
		}
		void BindActionEvent(const std::string& actionName, InputActionType type, std::shared_ptr<IEventHandler<>> handler)
		{
			for (auto& keyActionEvent : keyActionEvents)
			{
				if (keyActionEvent.second.name == actionName)
				{
					keyActionEvent.second.Bind(type, handler);
				}
			}
		}
		template <typename TObject>
		void UnbindActionEvent(const std::string& actionName, InputActionType type, TObject* const object, void (TObject::*const method)()) noexcept
		{
			UnbindActionEvent(actionName, MethodEventHandler<TObject>(*object, type, method));
		}
		void UnbindActionEvent(const std::string& actionName, InputActionType type, const IEventHandler<>& handler) noexcept
		{
			for (auto& keyActionEvent : keyActionEvents)
			{
				if (keyActionEvent.second.name == actionName)
				{
					keyActionEvent.second.Unbind(type, handler);
				}
			}
		}

	private:
		void CallActionEvent(InputActionType type, InputKey key) noexcept
		{
			auto actionEventsIt = keyActionEvents.equal_range(key);
			for (auto& it = actionEventsIt.first; it != actionEventsIt.second; it++)
			{
				it->second.Call(type);
			}
		}

	public:
		//-----
		void AddAxisMapping(const InputAxis& inputAxis)
		{
			AddAxisMapping(inputAxis.name, inputAxis.keys);
		}
		void AddAxisMapping(const std::string& axisName, std::vector<InputAxisKey> axisKeys) noexcept
		{
			for (auto& key : axisKeys)
			{
				keyAxisEvents.emplace(key.inputKey, InputAxisKeyHandlers{ axisName, key.scale });
			}
		}
		void RemoveAxisMapping(const InputAxis& inputAxis) noexcept
		{
			RemoveAxisMapping(inputAxis.name);
		}
		void RemoveAxisMapping(const std::string& axisName) noexcept
		{
			keyAxisEvents.erase(
				std::find_if(std::begin(keyAxisEvents), std::end(keyAxisEvents), [&axisName](auto& item) { return item.second.name == axisName; }), std::end(keyAxisEvents));
		}
		void RebindAxisKey(const std::string& axisName, InputKey oldKey, InputKey newKey) noexcept
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

	private:
		void CallAxisEvent(InputKey key, float inputScale = 1.0f) noexcept
		{
			auto axisEventsIt = keyAxisEvents.equal_range(key);
			for (auto& it = axisEventsIt.first; it != axisEventsIt.second; it++)
			{
				it->second.Call(inputScale);
			}
		}

	private:
		void OnKeyPressed(InputKey key) noexcept
		{
			pressedKeys.push_back(key);
			OnKeyAction(InputActionType::Pressed, key);
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
			OnKeyAction(InputActionType::Released, key);
		}
		void OnKeyAxis(InputKey actionKey, float scale) noexcept
		{
			axisKeyActions.push({ actionKey, scale });
		}
		void OnKeyAction(InputActionType type, InputKey key)
		{
			keyActions.push(std::make_pair(type, key));
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
				OnKeyAxis(InputKey::WheelUp, delta);
			}
			else
			{
				OnKeyAxis(InputKey::WheelDown, delta);
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
				OnKeyAxis(InputKey::MouseMoveX, x);
			}
			if (y != 0)
			{
				OnKeyAxis(InputKey::MouseMoveY, y);
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

	public:
		void Update() noexcept
		{
			while (!keyActions.empty())
			{
				auto action = keyActions.front();
				CallActionEvent(action.first, action.second);
				keyActions.pop();
			}

			for (auto& key : pressedKeys)
			{
				CallAxisEvent(key);
			}

			while (!axisKeyActions.empty())
			{
				auto action = axisKeyActions.front();
				CallAxisEvent(action.first, action.second);
				axisKeyActions.pop();
			}
		}

	public:
		Keyboard keyboard;
		Mouse mouse;

	private:
		std::multimap<InputKey, InputAxisKeyHandlers> keyAxisEvents;
		std::multimap<InputKey, InputActionKeyHandlers> keyActionEvents;
		std::list<InputKey> pressedKeys;
		std::queue<std::pair<InputKey, float>> axisKeyActions;
		std::queue<std::pair<InputActionType, InputKey>> keyActions;
	};
}