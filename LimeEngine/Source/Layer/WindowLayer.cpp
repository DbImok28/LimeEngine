// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#include "lepch.hpp"
#include "WindowLayer.hpp"
#include "Engine.hpp"

namespace LimeEngine
{
	WindowLayer::~WindowLayer()
	{
		//window->events.Unbind(WindowEventType::Close, Engine::GetEngine(), &Engine::Close);
		//window->events.Clear();
		Renderer::GetRenderer().RemoveRenderOutput();
	}

	WindowLayer* WindowLayer::GetWindowLayer()
	{
		return GetEngine()->windowLayer;
	}

	void WindowLayer::Update()
	{
		EngineLayer::Update();

		for (auto& window : windows)
		{
			window->OnUpdate();
		}
	}

	void WindowLayer::PostUpdate()
	{
		for (auto [windowToClose, exitCode] : pendingWindowsToClose)
		{
			LE_LOG_TRACE(LogEngineLayer, "Window {} closed with exit code {}", windowToClose->GetName(), exitCode);

			bool founded = false;
			for (auto it = std::begin(windows); it != std::end(windows);)
			{
				if (it->get() == windowToClose)
				{
					windows.erase(it);
					founded = true;
					break;
				}
			}
			LE_ASSERT(founded, "Attempting to delete a window that is not tracked by a window layer");

			if (exitCode != 0 || (closeEngineAfterClosingAllWindows && windows.empty())) Engine::GetEngine()->Close(exitCode);
		}
	}

	void WindowLayer::AddWindow(const WindowArgs& windowArgs)
	{
		AddWindow(Window::Create(windowArgs));
	}

	void WindowLayer::AddWindow(URef<Window>&& window)
	{
		Window* windowRef = windows.emplace_back(std::move(window)).get();
		windowRef->GetInput().SetInputDevice(InputLayer::GetInputLayer()->GetInputDevice());
		windowRef->events.Bind(WindowEventType::Close, [this, windowRef](const Event& e) {
			int exitCode = CastEvent<CloseWindowEvent>(e).exitCode;
			OnWindowCloseEvent(windowRef, exitCode);
		});
	}

	void WindowLayer::OnWindowCloseEvent(Window* window, int exitCode)
	{
		pendingWindowsToClose.emplace_back(window, exitCode);
	}

	Window* WindowLayer::GetWindow(int index) noexcept
	{
		auto iter = std::begin(windows);
		for (int i = 0; i < index; ++i)
		{
			++iter;
			if (iter == std::end(windows)) return {};
		}
		return iter->get();
	}
}
