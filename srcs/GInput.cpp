
#include "GInput.h"

namespace zLeafEngine
{
	void GInput::inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			std::cout << "\rUP   ";
			cameraView.pos -= (cameraSpeed * deltaTime);
			cameraView.target -= (cameraSpeed * deltaTime);
		}
		if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			std::cout << "\rDOWN ";
			cameraView.pos += (cameraSpeed * deltaTime);
			cameraView.target += (cameraSpeed * deltaTime);
		}
		if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			std::cout << "\rLEFT ";
			cameraView.pos -= glm::normalize(glm::cross(cameraView.target, cameraView.up)) * (cameraSpeed * deltaTime);
		}
		if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		{
			std::cout << "\rRIGHT";
			cameraView.pos += glm::normalize(glm::cross(cameraView.target, cameraView.up)) * (cameraSpeed * deltaTime);
		}
	}

	void GInput::inputMouseCallback(GLFWwindow* window, double xpos, double ypos)
	{

	}

	void GInput::inputScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{

	}
}