#include "Window.h"
#include "format"
#include "../Core/Input.h"
#include "../Core/Time.h"
#include "ConfigGL.h"


namespace Engine
{
	Window::Window()
	{
		Init();
	}

	Window::Window(std::string title, int width, int height)
	{

	}

	Window::~Window()
	{
		DeInit(0);
	}

	void Window::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			ENGINE_CORE_FATAL(std::format("Couldn't init SDL! SDL Error: {}", SDL_GetError()));
			DeInit(1);
		}

		int imgInit = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		if (imgInit == 0)
		{
			ENGINE_CORE_FATAL(std::format("Couldn't init IMG! SDL Error: {}", SDL_GetError()));
			DeInit(1);
		}

		if (imgInit & IMG_INIT_JPG)
			ENGINE_CORE_INFO("Initialized PNG library");
		else
			ENGINE_CORE_WARN("Couldn't init PNG library");
		if (imgInit & IMG_INIT_PNG)
			ENGINE_CORE_INFO("Initialized JPG library");
		else
			ENGINE_CORE_WARN("Couldn't init JPG library");

		m_Window = SDL_CreateWindow(m_Title.c_str(), 0, 100, m_Width, m_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_SetWindowMouseRect(m_Window, NULL);
		if (m_Window == NULL)
		{
			ENGINE_CORE_FATAL(std::format("Window could not be created! SDL Error: {}", SDL_GetError()));
			DeInit(1);
		}

		ENGINE_CORE_INFO("Window has been created");

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		if (!SDL_GL_CreateContext(m_Window))
		{
			ENGINE_CORE_FATAL(std::format("Couldn't init GL Context! SDL Error: {}", SDL_GetError()));
		}

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			ENGINE_CORE_FATAL(std::format("Couldn't init GL!"));
			DeInit(1);
		}

		glEnable(GL_DEPTH_TEST);

		float vertices[] = {
			-0.5f,0.5f,-0.5f,	0.0f, 1.0f, 0.0f, 0.f,1.f,
			0.5f,0.5f,-0.5f,	1.0f, 0.0f, 0.0f, 1.f,1.f,
			0.5f,0.5f, 0.5f,	1.0f, 0.0f, 1.0f, 1.f, 0.f,
			-0.5f,0.5f, 0.5f,	0.0f, 0.5f, 0.70f, 0.f, 0.f,
			-0.5f,-0.5f, -0.5f,	0.0f, 0.3f, 1.0f, 1.f,0.f,
			0.5f,-0.5f, -0.5f,	1.0f, 0.0f, .5f, 0.f,0.f,
			0.5f,-0.5f, 0.5f,	1.0f, 0.5f, 0.0f, 0.f, 1.f,
			-0.5f,-0.5f, 0.5f,	.5f, 0.3f, 0.0f, 1.f, 1.f
		};
		unsigned int indices[] =
		{
			0,1,3,
			1,2,3,
			0,4,1,
			1,4,5,
			0,3,7,
			0,7,4,
			1,6,2,
			1,5,6,
			2,7,3,
			2,6,7,
			4,7,5,
			5,7,6
		};

		// отрефакторить код ниже
		
		GLInit::InitializeBuffers(VBO_polygon, VAO_polygon, EBO_polygon, vertices, indices);

		model = std::make_shared<Model3D>("C:\\Users\\Kek\\Desktop\\CPP\\OpenGL Shooter\\Shaders\\Basic.vert", "C:\\Users\\Kek\\Desktop\\CPP\\OpenGL Shooter\\Shaders\\basic.frag");
		gameObject1.SetModel(model);
		gameObject2.SetModel(model);
		glm::vec3 pos(0.5f, 0, 0);
		glm::vec3 pos2(-0.5f, 0, 0);
		glm::vec3 scale(0.3f);
		gameObject1.SetPosition(pos);
		gameObject2.SetPosition(pos2);
		gameObject1.SetScale(scale);
		gameObject2.SetScale(scale);
		std::shared_ptr<Texture> texture = std::make_shared<Texture>("C:\\Users\\Kek\\Desktop\\CPP\\OpenGL Shooter\\Assets\\box.jpg");
		gameObject1.SetTexture(texture);
		gameObject2.SetTexture(texture);

		camera.SetPerpectiveProjection(m_Width, m_Height);
		camera.SetPosition(glm::vec3(0.f, 0.f, 5.f));

		ENGINE_CORE_INFO("Render has been created");
		ENGINE_CORE_OK("Everything was running");
	}

	void Window::DeInit(int error)
	{
		if (m_Window != NULL) SDL_DestroyWindow(m_Window);
		ENGINE_CORE_INFO("Destroyed");
		IMG_Quit();
		SDL_Quit();
		exit(error);
	}
	void Window::WindowUpdate()
	{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		Input::ReadInputEvents();
		Time::SetDeltaTime();

		Mouse deltaMouse = Input::GetMouseAxis();

		if (Input::GetKeyDown(SDL_SCANCODE_1))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (Input::GetKeyDown(SDL_SCANCODE_2))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (Input::GetMousePosition().x > 0)
			ENGINE_CORE_INFO(std::format("position vec3 {} {} {}", Input::GetMousePosition().x, Input::GetMousePosition().y, camera.GetPosition().z));

		camera.SetPosition(glm::vec3{Input::GetHorizontal(), 0.f, Input::GetVertical()});
		camera.Rotate(Input::GetMousePosition().x * Time::GetDeltaTime(), Input::GetMousePosition().y * Time::GetDeltaTime());
		camera.OnUpdate();
		
		glm::vec3 rotation(-0.005, 0.001, 0);
		gameObject1.SetRotation(rotation);
		m_Renderer->Draw(camera, gameObject1);
		glBindVertexArray(VAO_polygon);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		rotation = { 0.005, -0.001, 0 };
		gameObject2.SetRotation(rotation);
		glBindVertexArray(VAO_polygon);
		m_Renderer->Draw(camera, gameObject2);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(m_Window);
	}
}