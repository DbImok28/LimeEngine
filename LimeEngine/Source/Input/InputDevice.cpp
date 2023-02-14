#include "lepch.hpp"
#include "InputDevice.hpp"

namespace LimeEngine
{
	InputActionKey::InputActionKey(InputKey inputKey) noexcept : inputKey(inputKey) {}

	InputAction::InputAction(const std::string& name, std::vector<InputActionKey> keys) noexcept : name(name), keys(keys) {}

	InputActionKeyHandlers::InputActionKeyHandlers(const std::string& name) noexcept : name(name) {}

	void InputActionKeyHandlers::Bind(InputActionType type, std::unique_ptr<EventHandler<>>&& handler)
	{
		handlers.push_back(std::make_pair(type, std::move(handler)));
	}

	void InputActionKeyHandlers::Unbind(InputActionType type, const EventHandler<>& handler) noexcept
	{
		handlers.erase(
			std::find_if(std::begin(handlers), std::end(handlers), [&type, &handler](auto& item) { return (item.first == type && *item.second == handler); }), std::end(handlers));
	}

	void InputActionKeyHandlers::Call(InputActionType type)
	{
		for (auto& handler : handlers)
		{
			if (handler.first == type)
			{
				handler.second->Call();
			}
		}
	}

	InputAxisKey::InputAxisKey(InputKey inputKey, float scale) noexcept : inputKey(inputKey), scale(scale) {}

	InputAxis::InputAxis(const std::string& name, std::vector<InputAxisKey> keys) noexcept : name(name), keys(keys) {}

	InputAxisKeyHandlers::InputAxisKeyHandlers(const std::string& name) noexcept : name(name) {}

	void InputAxisKeyHandlers::Bind(std::unique_ptr<EventHandler<float>>&& handler)
	{
		handlers.push_back(std::move(handler));
	}

	void InputAxisKeyHandlers::Unbind(const EventHandler<float>& handler) noexcept
	{
		handlers.erase(std::find_if(std::begin(handlers), std::end(handlers), [&handler](auto& item) { return (*item == handler); }), std::end(handlers));
	}

	void InputAxisKeyHandlers::Call(float scale)
	{
		for (auto& handler : handlers)
		{
			handler->Call(scale);
		}
	}

	void InputDevice::AddActionMapping(const InputAction& inputAction)
	{
		AddActionMapping(inputAction.name, inputAction.keys);
	}

	void InputDevice::AddActionMapping(const std::string& actionName, std::vector<InputActionKey> actionKeys)
	{
		auto ptr = std::make_shared<InputActionKeyHandlers>(actionName);
		for (auto& key : actionKeys)
		{
			keyActionEvents.emplace(key.inputKey, ptr);
		}
	}

	void InputDevice::RemoveActionMapping(const InputAction& inputAction) noexcept
	{
		RemoveActionMapping(inputAction.name);
	}

	void InputDevice::RemoveActionMapping(const std::string& actionName) noexcept
	{
		keyActionEvents.erase(
			std::find_if(std::begin(keyActionEvents), std::end(keyActionEvents), [&actionName](auto& item) { return item.second->name == actionName; }), std::end(keyActionEvents));
	}

	void InputDevice::RebindActionKey(const std::string& actionName, InputKey oldKey, InputKey newKey) noexcept
	{
		for (auto it = std::begin(keyActionEvents); it != std::end(keyActionEvents); it++)
		{
			if (it->first == oldKey && it->second->name == actionName)
			{
				auto node = keyActionEvents.extract(it);
				node.key() = newKey;
				keyActionEvents.insert(std::move(node));
				break;
			}
		}
	}

	void InputDevice::BindActionEvent(const std::string& actionName, InputActionType type, void (*func)())
	{
		BindActionEvent(actionName, type, std::make_unique<FunctionEventHandler<>>(func));
	}

	void InputDevice::BindActionEvent(const std::string& actionName, InputActionType type, std::unique_ptr<EventHandler<>>&& handler)
	{
		for (auto& keyActionEvent : keyActionEvents)
		{
			if (keyActionEvent.second->name == actionName)
			{
				keyActionEvent.second->Bind(type, std::move(handler));
				break;
			}
		}
	}

	void InputDevice::UnbindActionEvent(const std::string& actionName, InputActionType type, void (*func)()) noexcept
	{
		UnbindActionEvent(actionName, type, FunctionEventHandler<>(func));
	}

	void InputDevice::UnbindActionEvent(const std::string& actionName, InputActionType type, const EventHandler<>& handler) noexcept
	{
		for (auto& keyActionEvent : keyActionEvents)
		{
			if (keyActionEvent.second->name == actionName)
			{
				keyActionEvent.second->Unbind(type, handler);
				break;
			}
		}
	}

	void InputDevice::CallActionEvent(InputActionType type, InputKey key)
	{
		auto actionEventsIt = keyActionEvents.equal_range(key);
		for (auto& it = actionEventsIt.first; it != actionEventsIt.second; it++)
		{
			it->second->Call(type);
		}
	}

	//-----

	void InputDevice::AddAxisMapping(const InputAxis& inputAxis)
	{
		AddAxisMapping(inputAxis.name, inputAxis.keys);
	}

	void InputDevice::AddAxisMapping(const std::string& axisName, std::vector<InputAxisKey> axisKeys)
	{
		auto ptr = std::make_shared<InputAxisKeyHandlers>(axisName);
		for (auto& key : axisKeys)
		{
			keyAxisEvents.emplace(key.inputKey, std::make_pair(key.scale, ptr));
		}
	}

	void InputDevice::RemoveAxisMapping(const InputAxis& inputAxis) noexcept
	{
		RemoveAxisMapping(inputAxis.name);
	}

	void InputDevice::RemoveAxisMapping(const std::string& axisName) noexcept
	{
		keyAxisEvents.erase(
			std::find_if(std::begin(keyAxisEvents), std::end(keyAxisEvents), [&axisName](auto& item) { return item.second.second->name == axisName; }), std::end(keyAxisEvents));
	}

	void InputDevice::RebindAxisKey(const std::string& axisName, InputKey oldKey, InputKey newKey) noexcept
	{
		for (auto it = std::begin(keyAxisEvents); it != std::end(keyAxisEvents); it++)
		{
			if (it->first == oldKey && it->second.second->name == axisName)
			{
				auto node = keyAxisEvents.extract(it);
				node.key() = newKey;
				keyAxisEvents.insert(std::move(node));
				break;
			}
		}
	}

	void InputDevice::BindAxisEvent(const std::string& axisName, void (*func)(float))
	{
		BindAxisEvent(axisName, std::make_unique<FunctionEventHandler<float>>(func));
	}

	void InputDevice::BindAxisEvent(const std::string& axisName, std::unique_ptr<EventHandler<float>>&& handler)
	{
		for (auto& keyAxisEvent : keyAxisEvents)
		{
			if (keyAxisEvent.second.second->name == axisName)
			{
				keyAxisEvent.second.second->Bind(std::move(handler));
				break;
			}
		}
	}

	void InputDevice::UnbindAxisEvent(const std::string& axisName, void (*func)(float)) noexcept
	{
		UnbindAxisEvent(axisName, FunctionEventHandler<float>(func));
	}

	void InputDevice::UnbindAxisEvent(const std::string& axisName, const EventHandler<float>& handler) noexcept
	{
		for (auto& keyAxisEvent : keyAxisEvents)
		{
			if (keyAxisEvent.second.second->name == axisName)
			{
				keyAxisEvent.second.second->Unbind(handler);
				break;
			}
		}
	}

	void InputDevice::CallAxisEvent(InputKey key, float inputScale)
	{
		auto axisEventsIt = keyAxisEvents.equal_range(key);
		for (auto& it = axisEventsIt.first; it != axisEventsIt.second; it++)
		{
			it->second.second->Call(it->second.first * inputScale);
		}
	}

	void InputDevice::OnKeyPressed(InputKey key) noexcept
	{
		pressedKeys.push_back(key);
		OnKeyAction(InputActionType::Pressed, key);
	}

	void InputDevice::OnKeyReleased(InputKey key) noexcept
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

	void InputDevice::OnKeyAxis(InputKey actionKey, float scale) noexcept
	{
		axisKeyActions.push({ actionKey, scale });
	}

	void InputDevice::OnKeyAction(InputActionType type, InputKey key) noexcept
	{
		keyActions.push(std::make_pair(type, key));
	}

	// ---

	void InputDevice::ClearKeyState() noexcept
	{
		keyboard.ClearKeyState();
		pressedKeys.clear();
	}

	void InputDevice::OnKeyboardChar(char key) noexcept
	{
		keyboard.OnChar(key);
	}

	void InputDevice::OnKeyboardKeyPressed(InputKey key) noexcept
	{
		OnKeyPressed(key);
		keyboard.OnKeyPressed(key);
	}

	void InputDevice::OnKeyboardKeyReleased(InputKey key) noexcept
	{
		OnKeyReleased(key);
		keyboard.OnKeyReleased(key);
	}

	void InputDevice::OnMouseKeyPressed(InputKey key, int x, int y) noexcept
	{
		switch (key)
		{
			case InputKey::LeftMouseButton: mouse.OnButtonPressed(MouseButton::Left, x, y); break;
			case InputKey::RightMouseButton: mouse.OnButtonPressed(MouseButton::Right, x, y); break;
			case InputKey::MiddleMouseButton: mouse.OnButtonPressed(MouseButton::Middle, x, y); break;
			default: break;
		}
		OnKeyPressed(key);
	}

	void InputDevice::OnMouseKeyReleased(InputKey key, int x, int y) noexcept
	{
		switch (key)
		{
			case InputKey::LeftMouseButton: mouse.OnButtonReleased(MouseButton::Left, x, y); break;
			case InputKey::RightMouseButton: mouse.OnButtonReleased(MouseButton::Right, x, y); break;
			case InputKey::MiddleMouseButton: mouse.OnButtonReleased(MouseButton::Middle, x, y); break;
			default: break;
		}
		OnKeyReleased(key);
	}

	void InputDevice::OnMouseWheelDelta(int x, int y, int delta) noexcept
	{
		if (delta > 0)
		{
			OnKeyAxis(InputKey::WheelUp, static_cast<float>(delta));
		}
		else
		{
			OnKeyAxis(InputKey::WheelDown, static_cast<float>(delta));
		}
		mouse.OnWheelDelta(x, y, delta);
	}

	void InputDevice::OnMouseMove(int x, int y) noexcept
	{
		int deltaX = x - mouse.GetPosX();
		if (deltaX != 0)
		{
			OnKeyAxis(InputKey::MouseMoveX, deltaX);
		}
		int deltaY = y - mouse.GetPosY();
		if (deltaY != 0)
		{
			OnKeyAxis(InputKey::MouseMoveY, deltaY);
		}
		mouse.OnMouseMove(x, y);
	}

	void InputDevice::OnMouseRawMove(int x, int y) noexcept
	{
		mouse.OnMouseRawMove(x, y);
	}

	void InputDevice::OnMouseLeave() noexcept
	{
		mouse.OnMouseLeave();
	}

	void InputDevice::OnMouseEnter() noexcept
	{
		mouse.OnMouseEnter();
	}

	void InputDevice::OnUpdate() noexcept
	{
		while (!keyActions.empty())
		{
			auto& action = keyActions.front();
			CallActionEvent(action.first, action.second);
			keyActions.pop();
		}

		for (auto& key : pressedKeys)
		{
			CallAxisEvent(key);
		}

		while (!axisKeyActions.empty())
		{
			auto& action = axisKeyActions.front();
			CallAxisEvent(action.first, action.second);
			axisKeyActions.pop();
		}

		keyboard.Update();
		mouse.Update();
	}
}