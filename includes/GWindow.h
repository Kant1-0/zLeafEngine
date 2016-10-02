/*
Handle user input with GLFW poll events to update render.
*/

#ifndef _GWINDOW_H
#define _GWINDOW_H

#include "stdafx.h"
#include "Globals.h"

namespace zLeafEngine
{
	class GWindow // -> VInstance
	{
		protected:
			//GLFW Window
			static GLFWwindow* window;

			//Icon
			void loadIcon(std::string path, GLFWimage *icon);
	};
}

#endif // !_GWINDOW_H