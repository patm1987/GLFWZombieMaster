
#include "entity/entity.h"
#include "entity/renderable.h"
#include "renderer/renderer.h"
#include "renderer/shader.h"
#include "utils/autolist.h"

static const int kWindowWidth = 640;
static const int kWindowHeight = 480;
static const char* kWindowTitle = "GLFWZombieMaster";

int main()
{
	GLFWwindow* pGlfwWindow;

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	pGlfwWindow = glfwCreateWindow(
				kWindowWidth,
				kWindowHeight,
				kWindowTitle,
				nullptr,
				nullptr);
	if (!pGlfwWindow)
	{
		glfwTerminate();
		std::cerr << "Failed to create a glfw window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(pGlfwWindow);

	// startup gl3w -- for great good!
	if(auto err = gl3wInit())
	{
		glfwTerminate();
		std::cerr << "Failed to init gl3w with " << err << std::endl;
		return -1;
	}

	// checking for gl 3.2
	if (!gl3wIsSupported(3, 2))
	{
		glfwTerminate();
		std::cerr << "Your system doesn't support gl 3.2" << std::endl;
		return -1;
	}

	Renderer::Renderer::initialize();
	Renderer::Renderer& renderer = Renderer::Renderer::instance();

	Entity::Entity camera; // TODO: build me!
	Renderer::Shader shader; // TODO: build me!

	// temp variables to store the screen dimensions in
	// TODO: move screen management into some renderer, display, or screen class
	int screenWidth, screenHeight;
	while(!glfwWindowShouldClose(pGlfwWindow))
	{
		// setup the viewport
		glfwGetFramebufferSize(pGlfwWindow, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenHeight);

		renderer.setShader(&shader);
		renderer.setCamera(&camera);

		for(auto entityNode : Entity::Entity::getList())
		{
			Entity::Entity& entity = entityNode.value();

			Entity::Renderable* pRenderable = entity.getRenderable();
			if (entity.isInScenegraph() && pRenderable)
			{
				renderer.renderObject(entity);
			}
		}

		// rendering!
		glfwSwapBuffers(pGlfwWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

