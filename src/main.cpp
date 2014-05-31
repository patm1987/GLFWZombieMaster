#include <GLFW/glfw3.h>

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

	pGlfwWindow = glfwCreateWindow(kWindowWidth, kWindowHeight, kWindowTitle, nullptr, nullptr);
	if (!pGlfwWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pGlfwWindow);

	while(!glfwWindowShouldClose(pGlfwWindow))
	{
		// rendering!
		glfwSwapBuffers(pGlfwWindow);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

