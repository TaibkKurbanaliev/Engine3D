#include "Renderer/Window.h"
#include "Core/Input.h"

int main(int argc, char* argv[])
{
	bool isRunnig = true;
	Engine::Window window;

	while (isRunnig)
	{
		Engine::Input::ReadInputEvents();

		if (Engine::Input::GetQuit())
			isRunnig = false;

		window.WindowUpdate();
	}

	return 0;
}