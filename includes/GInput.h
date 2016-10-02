/*
  Handle user input with GLFW poll events to update render.
*/

#ifndef _GINPUT_H
#define _GINPUT_H

#include "stdafx.h"
#include "GInput_Base.h"
#include "DrawFrame.h"

namespace zLeafEngine
{
	class GInput : public GInput_Base, public DrawFrame //-> App
	{
		//Input Callback
		virtual void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		virtual void inputMouseCallback(GLFWwindow* window, double xpos, double ypos);
		virtual void inputScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		protected:
			bool keys[1024];
			float cameraSpeed;
	};
}

#endif // !_GINPUT_H
