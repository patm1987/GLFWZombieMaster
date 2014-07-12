
#include "entity/entity.h"
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

	glfwMakeContextCurrent(pGlfwWindow);

	// temp variables to store the screen dimensions in
	// TODO: move screen management into some renderer, display, or screen class
	int screenWidth, screenHeight;
	while(!glfwWindowShouldClose(pGlfwWindow))
	{
		// setup the viewport
		glfwGetFramebufferSize(pGlfwWindow, &screenWidth, &screenHeight);
		glViewport(0, 0, screenWidth, screenHeight);

		for(auto entityNode : Entity::Entity::getList())
		{
			Entity::Entity& entity = entityNode.value();
			entity.isInScenegraph();

			// todo: render if in scenegraph
		}

		// rendering!
		glfwSwapBuffers(pGlfwWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

