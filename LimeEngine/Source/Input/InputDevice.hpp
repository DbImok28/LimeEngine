#pragma once
#include <memory>
#include <map>
#include "InputKeys.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Base/Events.hpp"

namespace LimeEngine
{
	enum class InputActionType
	{
		Pressed,
		Released
	};

	struct InputActionKey
	{
		InputActionKey(InputKey inputKey) noexcept;

		InputKey inputKey;
	};

	struct InputAction
	{
		InputAction(const std::string& name, std::vector<InputActionKey> keys) noexcept;

		std::string name;
		std::vector<InputActionKey> keys;
	};

	class InputActionKeyHandlers
	{
	public:
		InputActionKeyHandlers(const std::string& name) noexcept;

		void Bind(InputActionType type, std::unique_ptr<IEventHandler<>>&& handler);
		void Unbind(InputActionType type, const IEventHandler<>& handler) noexcept;
		void Call(InputActionType type);

	public:
		std::string name;
		std::vector<std::pair<InputActionType, std::unique_ptr<IEventHandler<>>>> handlers;
	};

	struct InputAxisKey
	{
		InputAxisKey(InputKey inputKey, float scale) noexcept;

		InputKey inputKey;
		float scale;
	};

	struct InputAxis
	{
		InputAxis(const std::string& name, std::vector<InputAxisKey> keys) noexcept;

		std::string name;
		std::vector<InputAxisKey> keys;
	};

	class InputAxisKeyHandlers
	{
	public:
		InputAxisKeyHandlers(const std::string& name) noexcept;

		void Bind(std::unique_ptr<IEventHandler<float>>&& handler);
		void Unbind(const IEventHandler<float>& handler) noexcept;
		void Call(float scale);

	public:
		std::string name;
		std::vector<std::unique_ptr<IEventHandler<float>>> handlers;
	};

	class InputDevice
	{
		friend class Window;

	public:
		void AddActionMapping(const InputAction& inputAction);
		void AddActionMapping(const std::string& actionName, std::vector<InputActionKey> actionKeys);
		void RemoveActionMapping(const InputAction& inputAction) noexcept;
		void RemoveActionMapping(const std::string& actionName) noexcept;
		void RebindActionKey(const std::string& actionName, InputKey oldKey, InputKey newKey) noexcept;
		template <typename TObject>
		void BindActionEvent(const std::string& actionName, InputActionType type, TObject* const object, void (TObject::*const method)())
		{
			BindActionEvent(actionName, type, std::make_unique<MethodEventHandler<TObject>>(*object, method));
		}
		void BindActionEvent(const std::string& actionName, InputActionType type, void (*func)());
		void BindActionEvent(const std::string& actionName, InputActionType type, std::unique_ptr<IEventHandler<>>&& handler);
		template <typename TObject>
		void UnbindActionEvent(const std::string& actionName, InputActionType type, TObject* const object, void (TObject::*const method)()) noexcept
		{
			UnbindActionEvent(actionName, type, MethodEventHandler<TObject>(*object, method));
		}
		void UnbindActionEvent(const std::string& actionName, InputActionType type, void (*func)()) noexcept;
		void UnbindActionEvent(const std::string& actionName, InputActionType type, const IEventHandler<>& handler) noexcept;

	private:
		void CallActionEvent(InputActionType type, InputKey key);

	public:
		//-----
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
		void BindAxisEvent(const std::string& axisName, std::unique_ptr<IEventHandler<float>>&& handler);
		template <typename TObject>
		void UnbindAxisEvent(const std::string& axisName, TObject* const object, void (TObject::*const method)(float)) noexcept
		{
			UnbindAxisEvent(axisName, MethodEventHandler<TObject, float>(*object, method));
		}
		void UnbindAxisEvent(const std::string& axisName, void (*func)(float)) noexcept;
		void UnbindAxisEvent(const std::string& axisName, const IEventHandler<float>& handler) noexcept;

	private:
		void CallAxisEvent(InputKey key, float inputScale = 1.0f);

	private:
		void OnKeyPressed(InputKey key) noexcept;
		void OnKeyReleased(InputKey key) noexcept;
		void OnKeyAxis(InputKey actionKey, float scale) noexcept;
		void OnKeyAction(InputActionType type, InputKey key) noexcept;

		// ---------
		void ClearKeyState() noexcept;
		void OnKeyboardChar(char key) noexcept;
		void OnKeyboardKeyPressed(InputKey key) noexcept;
		void OnKeyboardKeyReleased(InputKey key) noexcept;

		void OnMouseLeftPressed(int x, int y) noexcept;
		void OnMouseLeftReleased(int x, int y) noexcept;

		void OnMouseRightPressed(int x, int y) noexcept;
		void OnMouseRightReleased(int x, int y) noexcept;

		void OnMouseMiddlePressed(int x, int y) noexcept;
		void OnMouseMiddleReleased(int x, int y) noexcept;
		void OnMouseWheelDelta(int x, int y, int delta) noexcept;

		void OnMouseMove(int x, int y) noexcept;
		void OnMouseRawMove(int x, int y) noexcept;

		void OnMouseLeave() noexcept;
		void OnMouseEnter() noexcept;

	public:
		void Update() noexcept;

	public:
		Keyboard keyboard;
		Mouse mouse;

	private:
		std::multimap<InputKey, std::pair<float, std::shared_ptr<InputAxisKeyHandlers>>> keyAxisEvents;
		std::multimap<InputKey, std::shared_ptr<InputActionKeyHandlers>> keyActionEvents;
		std::list<InputKey> pressedKeys;
		std::queue<std::pair<InputKey, float>> axisKeyActions;
		std::queue<std::pair<InputActionType, InputKey>> keyActions;
	};
}