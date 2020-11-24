#pragma once

#include "Fireworks/Core.h"

namespace Fireworks {

	class FIREWORKS_API Input {
	public:
		// Singleton class, so we should delete these methods to ensure we don't accidentally create copies.
		// Public as recommended by Scott Meyers in Effective Modern C++ because it result in better error messages 
		// due to the compiler's behavior to check accessibility before deleted status.
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return  s_Instance->IsKeyPressedImpl(keycode); }
		
		inline static bool IsMouseButtonPressed(int button) { return  s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return  s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return  s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return  s_Instance->GetMouseYImpl(); }

	protected:
		// Singleton class, so we want to put the constructor in protected or private to prevent 
		// direct construction calls with the 'new' operator.
		Input() = default;

		// Will be implemented per platform.
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}