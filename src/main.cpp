
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
		return -1;
	}

	// startup gl3w -- for great good!
	if(gl3wInit())
	{
		glfwTerminate();
		return -1;
	}

	// checking for gl 3.2
	if (!gl3wIsSupported(3, 2))
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pGlfwWindow);

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

