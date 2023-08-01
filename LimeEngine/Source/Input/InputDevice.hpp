// Copyright (C) Pavel Jakushik - All Rights Reserved
// See file LICENSE for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "InputKeys.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Base/Event.hpp"

namespace LimeEngine
{
	enum class InputActionType
	{
		Pressed,
		Released
	};

	struct InputActionKey
	{
		explicit InputActionKey(InputKey inputKey) noexcept;
		InputActionKey(InputKey inputKey, bool alt, bool shift, bool ctrl, bool cmd) noexcept;

		bool CheckInputKey(InputKey inputKey) const noexcept;
		bool CheckSystemKey(bool alt, bool shift, bool ctrl, bool cmd) const noexcept;
		bool NeedSystemKey() const noexcept;

		bool operator==(const InputActionKey& other) const noexcept;
		bool operator<(const InputActionKey& other) const noexcept;

		InputKey inputKey;
		bool alt = false;
		bool shift = false;
		bool ctrl = false;
		bool cmd = false;
	};

	struct InputAction
	{
		InputAction(const std::string& name, const std::vector<InputActionKey>& keys) noexcept;

		std::string name;
		std::vector<InputActionKey> keys;
	};

	class InputActionKeyHandlers
	{
	public:
		explicit InputActionKeyHandlers(const std::string& name) noexcept;

		void Bind(InputActionType type, std::unique_ptr<EventHandler<>>&& handler);
		void Unbind(InputActionType type, const EventHandler<>& handler) noexcept;
		void Call(InputActionType type);

	public:
		std::string name;
		std::vector<std::pair<InputActionType, std::unique_ptr<EventHandler<>>>> handlers;
	};

	struct InputAxisKey
	{
		InputAxisKey(InputKey inputKey, float scale) noexcept;

		InputKey inputKey;
		float scale;
	};

	struct InputAxis
	{
		InputAxis(const std::string& name, const std::vector<InputAxisKey>& keys) noexcept;

		std::string name;
		std::vector<InputAxisKey> keys;
	};

	class InputAxisKeyHandlers
	{
	public:
		explicit InputAxisKeyHandlers(const std::string& name) noexcept;

		void Bind(std::unique_ptr<EventHandler<float>>&& handler);
		void Unbind(const EventHandler<float>& handler) noexcept;
		void Call(float scale);

	public:
		std::string name;
		std::vector<std::unique_ptr<EventHandler<float>>> handlers;
	};

	class Input;

	class InputDevice
	{
		friend class Input;

	public:
		void AddActionMapping(const InputAction& inputAction);
		void AddActionMapping(const std::string& actionName, std::vector<InputActionKey> actionKeys);
		void RemoveActionMapping(const InputAction& inputAction) noexcept;
		void RemoveActionMapping(const std::string& actionName) noexcept;
		void RebindActionKey(const std::string& actionName, InputActionKey oldKey, InputActionKey newKey) noexcept;
		template <typename TObject>
		void BindActionEvent(const std::string& actionName, InputActionType type, TObject* const object, void (TObject::*const method)())
		{
			BindActionEvent(actionName, type, std::make_unique<MethodEventHandler<TObject>>(*object, method));
		}
		void BindActionEvent(const std::string& actionName, InputActionType type, void (*func)());
		void BindActionEvent(const std::string& actionName, InputActionType type, std::unique_ptr<EventHandler<>>&& handler);
		template <typename TObject>
		void UnbindActionEvent(const std::string& actionName, InputActionType type, TObject* const object, void (TObject::*const method)()) noexcept
		{
			UnbindActionEvent(actionName, type, MethodEventHandler<TObject>(*object, method));
		}
		void UnbindActionEvent(const std::string& actionName, InputActionType type, void (*func)()) noexcept;
		void UnbindActionEvent(const std::string& actionName, InputActionType type, const EventHandler<>& handler) noexcept;

	private:
		void CallActionEvent(InputActionType type, InputKey key);

	public:
		void AddAxisMapping(const InputAxis& inputAxis);
		void AddAxisMapping(const std::string& axisName, std::vector<InputAxisKey> axisKeys);
		void RemoveAxisMapping(const InputAxis& inputAxis) noexcept;
		void RemoveAxisMapping(const std::string& axisName) noexcept;
		void RebindAxisKey(const std::string& axisName, InputKey oldKey, InputKey newKey) noexcept;
		void BindAxisEvent(const std::string& axisName, void (*func)(float));
		template <typename TObject>
		void BindAxisEvent(const std::string& axisName, TObject* const object, void (TObject::*const method)(float))
		{
			BindAxisEvent(axisName, std::make_unique<MethodEventHandler<TObject, float>>(*object, method));
		}
		void BindAxisEvent(const std::string& axisName, std::unique_ptr<EventHandler<float>>&& handler);
		template <typename TObject>
		void UnbindAxisEvent(const std::string& axisName, TObject* const object, void (TObject::*const method)(float)) noexcept
		{
			UnbindAxisEvent(axisName, MethodEventHandler<TObject, float>(*object, method));
		}
		void UnbindAxisEvent(const std::string& axisName, void (*func)(float)) noexcept;
		void UnbindAxisEvent(const std::string& axisName, const EventHandler<float>& handler) noexcept;

	private:
		void CallAxisEvent(InputKey key, float inputScale = 1.0f);

	private:
		void OnKeyPressed(InputKey key) noexcept;
		void OnKeyReleased(InputKey key) noexcept;
		void OnKeyAxis(InputKey actionKey, float scale) noexcept;
		void OnKeyAction(InputActionType type, InputKey key) noexcept;

		void ClearKeyState() noexcept;
		void OnKeyboardChar(wchar_t key) noexcept;
		void OnKeyboardKeyPressed(InputKey key) noexcept;
		void OnKeyboardKeyReleased(InputKey key) noexcept;

		void OnMouseKeyPressed(InputKey key, int x, int y) noexcept;
		void OnMouseKeyReleased(InputKey key, int x, int y) noexcept;
		void OnMouseWheelDelta(int x, int y, float delta) noexcept;

		void OnMouseMove(int x, int y) noexcept;
		void OnMouseRawMove(int x, int y) noexcept;

		void OnMouseLeave() noexcept;
		void OnMouseEnter() noexcept;

	public:
		void OnUpdate() noexcept;

	public:
		Keyboard keyboard;
		Mouse mouse;

	private:
		std::multimap<InputKey, std::pair<float, std::shared_ptr<InputAxisKeyHandlers>>> keyAxisEvents;
		std::multimap<InputActionKey, std::shared_ptr<InputActionKeyHandlers>> keyActionEvents;
		std::list<InputKey> pressedKeys;
		std::queue<std::pair<InputKey, float>> axisKeyActions;
		std::queue<std::pair<InputActionType, InputKey>> keyActions;
	};
}