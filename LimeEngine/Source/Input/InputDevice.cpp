// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#include "lepch.hpp"
#include "InputDevice.hpp"

namespace LimeEngine
{
	InputActionKey::InputActionKey(InputKey inputKey) noexcept : inputKey(inputKey) {}

	InputActionKey::InputActionKey(InputKey inputKey, bool alt, bool shift, bool ctrl, bool cmd) noexcept : inputKey(inputKey), alt(alt), shift(shift), ctrl(ctrl), cmd(cmd) {}

	bool InputActionKey::CheckSystemKey(bool alt, bool shift, bool ctrl, bool cmd) const noexcept
	{
		return (!this->alt || alt) && (!this->shift || shift) && (!this->ctrl || ctrl) && (!this->cmd || cmd);
	}

	bool InputActionKey::NeedSystemKey() const noexcept
	{
		return (this->alt || this->shift || this->ctrl || this->cmd);
	}

	bool InputActionKey::operator==(const InputActionKey& other) const noexcept
	{
		return (inputKey == other.inputKey) && (!alt || other.alt) && (!shift || other.shift) && (!ctrl || other.ctrl) && (!cmd || other.cmd);
	}
	bool InputActionKey::operator<(const InputActionKey& other) const noexcept
	{
		return inputKey < other.inputKey;
	}

	InputAction::InputAction(const std::string& name, const std::vector<InputActionKey>& keys) noexcept : name(name), keys(keys) {}

	InputActionKeyHandlers::InputActionKeyHandlers(const std::string& name) noexcept : name(name) {}

	void InputActionKeyHandlers::Bind(InputActionType type, URef<EventHandler<>>&& handler)
	{
		handlers.push_back(std::make_pair(type, std::move(handler)));
	}

	void InputActionKeyHandlers::Unbind(InputActionType type, const EventHandler<>& handler) noexcept
	{
		handlers.erase(
			std::find_if(std::begin(handlers), std::end(handlers), [&type, &handler](const auto& item) { return (item.first == type && *item.second == handler); }),
			std::end(handlers));
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

	InputAxis::InputAxis(const std::string& name, const std::vector<InputAxisKey>& keys) noexcept : name(name), keys(keys) {}

	InputAxisKeyHandlers::InputAxisKeyHandlers(const std::string& name) noexcept : name(name) {}

	void InputAxisKeyHandlers::Bind(URef<EventHandler<float>>&& handler)
	{
		handlers.push_back(std::move(handler));
	}

	void InputAxisKeyHandlers::Unbind(const EventHandler<float>& handler) noexcept
	{
		handlers.erase(std::find_if(std::begin(handlers), std::end(handlers), [&handler](const auto& item) { return (*item == handler); }), std::end(handlers));
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
			keyActionEvents.emplace(key, ptr);
		}
	}

	void InputDevice::RemoveActionMapping(const InputAction& inputAction) noexcept
	{
		RemoveActionMapping(inputAction.name);
	}

	void InputDevice::RemoveActionMapping(const std::string& actionName) noexcept
	{
		keyActionEvents.erase(
			std::find_if(std::begin(keyActionEvents), std::end(keyActionEvents), [&actionName](const auto& item) { return item.second->name == actionName; }),
			std::end(keyActionEvents));
	}

	void InputDevice::RebindActionKey(const std::string& actionName, InputActionKey oldKey, InputActionKey newKey) noexcept
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
		BindActionEvent(actionName, type, MakeUnique<FunctionEventHandler<>>(func));
	}

	void InputDevice::BindActionEvent(const std::string& actionName, InputActionType type, URef<EventHandler<>>&& handler)
	{
		auto findedKeyActionEvent =
			std::find_if(std::begin(keyActionEvents), std::end(keyActionEvents), [&actionName](const auto& item) { return item.second->name == actionName; });
		if (findedKeyActionEvent != std::end(keyActionEvents))
		{
			findedKeyActionEvent->second->Bind(type, std::move(handler));
		}
	}

	void InputDevice::UnbindActionEvent(const std::string& actionName, InputActionType type, void (*func)()) noexcept
	{
		UnbindActionEvent(actionName, type, FunctionEventHandler<>(func));
	}

	void InputDevice::UnbindActionEvent(const std::string& actionName, InputActionType type, const EventHandler<>& handler) noexcept
	{
		auto findedKeyActionEvent =
			std::find_if(std::begin(keyActionEvents), std::end(keyActionEvents), [&actionName](const auto& item) { return item.second->name == actionName; });
		if (findedKeyActionEvent != std::end(keyActionEvents))
		{
			findedKeyActionEvent->second->Unbind(type, handler);
		}
	}

	void InputDevice::CallActionEvent(InputActionType type, InputKey key)
	{
		bool alt = keyboard.AltIsPressed();
		bool shift = keyboard.ShiftIsPressed();
		bool ctrl = keyboard.ControlIsPressed();
		bool cmd = keyboard.CommondIsPressed();

		if (Keyboard::IsSystemKey(key))
		{
			if (type == InputActionType::Released)
			{
				if (Keyboard::IsAltKey(key))
				{
					alt = true;
				}
				else if (Keyboard::IsShiftKey(key))
				{
					shift = true;
				}
				else if (Keyboard::IsControlKey(key))
				{
					ctrl = true;
				}
				else if (Keyboard::IsCommondKey(key))
				{
					cmd = true;
				}
			}
			for (auto& item : keyActionEvents)
			{
				if (item.first.NeedSystemKey() && keyboard.KeyIsPressed(item.first.inputKey) && item.first.CheckSystemKey(alt, shift, ctrl, cmd))
				{
					item.second->Call(type);
				}
				else if (item.first.inputKey == key && item.first.CheckSystemKey(alt, shift, ctrl, cmd))
				{
					item.second->Call(type);
				}
			}
		}
		else
		{
			auto keyMatchHandlers = keyActionEvents.equal_range(InputActionKey(key));
			
			for (auto& it = keyMatchHandlers.first; it != keyMatchHandlers.second; it++)
			{
				if (it->first.CheckSystemKey(alt, shift, ctrl, cmd))
				{
					it->second->Call(type);
				}
			}
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
			std::find_if(std::begin(keyAxisEvents), std::end(keyAxisEvents), [&axisName](const auto& item) { return item.second.second->name == axisName; }),
			std::end(keyAxisEvents));
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
		BindAxisEvent(axisName, MakeUnique<FunctionEventHandler<float>>(func));
	}

	void InputDevice::BindAxisEvent(const std::string& axisName, URef<EventHandler<float>>&& handler)
	{
		auto findedkeyAxisEvent = std::find_if(std::begin(keyAxisEvents), std::end(keyAxisEvents), [&axisName](const auto& item) { return item.second.second->name == axisName; });
		if (findedkeyAxisEvent != std::end(keyAxisEvents))
		{
			findedkeyAxisEvent->second.second->Bind(std::move(handler));
		}
	}

	void InputDevice::UnbindAxisEvent(const std::string& axisName, void (*func)(float)) noexcept
	{
		UnbindAxisEvent(axisName, FunctionEventHandler<float>(func));
	}

	void InputDevice::UnbindAxisEvent(const std::string& axisName, const EventHandler<float>& handler) noexcept
	{
		auto findedkeyAxisEvent = std::find_if(std::begin(keyAxisEvents), std::end(keyAxisEvents), [&axisName](const auto& item) { return item.second.second->name == axisName; });
		if (findedkeyAxisEvent != std::end(keyAxisEvents))
		{
			findedkeyAxisEvent->second.second->Unbind(handler);
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

	void InputDevice::OnKeyboardChar(wchar_t key) noexcept
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
			case InputKey::ThumbForwardMouseButton: mouse.OnButtonPressed(MouseButton::ThumbForward, x, y); break;
			case InputKey::ThumbBackMouseButton: mouse.OnButtonPressed(MouseButton::ThumbBack, x, y); break;
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
			case InputKey::ThumbForwardMouseButton: mouse.OnButtonReleased(MouseButton::ThumbForward, x, y); break;
			case InputKey::ThumbBackMouseButton: mouse.OnButtonReleased(MouseButton::ThumbBack, x, y); break;
			default: break;
		}
		OnKeyReleased(key);
	}

	void InputDevice::OnMouseWheelDelta(int x, int y, float delta) noexcept
	{
		if (delta > 0)
		{
			OnKeyAxis(InputKey::WheelUp, delta);
		}
		else
		{
			OnKeyAxis(InputKey::WheelDown, delta);
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