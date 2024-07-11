#include "Input.h"

namespace Engine
{
	Mouse Engine::Input::s_Mouse;
	int Engine::Input::s_Horizontal;
	int Engine::Input::s_Vertical;
	bool Engine::Input::s_Quit = false;
	bool Engine::Input::s_WindowResized = false;
	const Uint8* Engine::Input::KEYBOARD_STATES = SDL_GetKeyboardState(NULL);
	bool* Engine::Input::PREVIOUS_DOWN_STATES = new bool[SDL_NUM_SCANCODES] {false};
	bool* Engine::Input::PREVIOUS_UP_STATES = new bool[SDL_NUM_SCANCODES] {false};
	SDL_Event Engine::Input::s_Event;

	void Input::ReadInputEvents()
	{
		while (SDL_PollEvent(&s_Event))
		{
			switch (s_Event.type)
			{
			case SDL_QUIT:
				s_Quit = true;
				return;
			case SDL_WINDOWEVENT:
				if (s_Event.window.event == SDL_WINDOWEVENT_RESIZED)
					s_WindowResized = true;
				break;
			case SDL_MOUSEMOTION:
				s_Mouse.x = (float)s_Event.motion.xrel;
				s_Mouse.y = (float)s_Event.motion.yrel;
				break;
			}
		}

		if ((KEYBOARD_STATES[SDL_SCANCODE_UP] || KEYBOARD_STATES[SDL_SCANCODE_W]) && !(KEYBOARD_STATES[SDL_SCANCODE_DOWN] || KEYBOARD_STATES[SDL_SCANCODE_S]))
			SetVertical(VERTICAL_AXIS_UP);
		if (!(KEYBOARD_STATES[SDL_SCANCODE_UP] || KEYBOARD_STATES[SDL_SCANCODE_W]) && (KEYBOARD_STATES[SDL_SCANCODE_DOWN] || KEYBOARD_STATES[SDL_SCANCODE_S]))
			SetVertical(VERTICAL_AXIS_DOWN);
		if (!(KEYBOARD_STATES[SDL_SCANCODE_UP] || KEYBOARD_STATES[SDL_SCANCODE_W]) && !(KEYBOARD_STATES[SDL_SCANCODE_DOWN] || KEYBOARD_STATES[SDL_SCANCODE_S]))
			SetVertical(0);
		if ((KEYBOARD_STATES[SDL_SCANCODE_LEFT] || KEYBOARD_STATES[SDL_SCANCODE_A]) && !(KEYBOARD_STATES[SDL_SCANCODE_RIGHT] || KEYBOARD_STATES[SDL_SCANCODE_D]))
			SetHorizontal(HORIZONTAL_AXIS_LEFT);
		if (!(KEYBOARD_STATES[SDL_SCANCODE_LEFT] || KEYBOARD_STATES[SDL_SCANCODE_A]) && (KEYBOARD_STATES[SDL_SCANCODE_RIGHT] || KEYBOARD_STATES[SDL_SCANCODE_D]))
			SetHorizontal(HORIZONTAL_AXIS_RIGHT);
		if (!(KEYBOARD_STATES[SDL_SCANCODE_LEFT] || KEYBOARD_STATES[SDL_SCANCODE_A]) && !(KEYBOARD_STATES[SDL_SCANCODE_RIGHT] || KEYBOARD_STATES[SDL_SCANCODE_D]))
			SetHorizontal(0);

	}

	void Input::SetHorizontal(int direction)
	{
		if (direction > HORIZONTAL_AXIS_RIGHT || direction < HORIZONTAL_AXIS_LEFT)
			return;

		s_Horizontal = direction;
	}

	void Input::SetVertical(int direction)
	{
		if (direction < VERTICAL_AXIS_UP || direction > VERTICAL_AXIS_DOWN)
			return;

		s_Vertical = direction;
	}

	Mouse Input::GetMousePosition()
	{
		return s_Mouse;
	}

	Mouse Input::GetMouseAxis()
	{
		Mouse mouse;
		//int mouseX, mouseY;
		//static int prevMouseX = 0, prevMouseY = 0;


		mouse.y = s_Event.motion.yrel;
		mouse.x = s_Event.motion.xrel;
		
		//prevMouseX = mouseX;
		//prevMouseY = mouseY;

		return mouse;
	}

	bool Input::GetKey(SDL_Scancode key) // Always works while the key is pressed
	{
		return KEYBOARD_STATES[key];
	}

	bool Input::GetKeyDown(SDL_Scancode key) // Triggered once while the key is pressed
	{
		bool currentState = KEYBOARD_STATES[key];

		if (currentState && !PREVIOUS_DOWN_STATES[key])
		{
			PREVIOUS_DOWN_STATES[key] = true;
			return true;
		}

		PREVIOUS_DOWN_STATES[key] = currentState; // Update the previous state

		return false;
	}

	bool Input::GetKeyUp(SDL_Scancode key) // Triggered once while the key is pressed
	{
		bool currentState = KEYBOARD_STATES[key];

		if (!currentState && PREVIOUS_UP_STATES[key])
		{
			PREVIOUS_UP_STATES[key] = false;
			return true;
		}

		PREVIOUS_UP_STATES[key] = currentState;

		return false;
	}
}