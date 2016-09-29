
#include "GInput.h"

namespace zLeafEngine
{
	void GInput::inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		//if (key == )
	}
}