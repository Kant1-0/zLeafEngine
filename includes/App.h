/*
  Run Application, starting point.
  And Validation layers to help debugging.
*/

#ifndef _APP_H
#define _APP_H

#include "stdafx.h"
#include "GInput.h"

namespace zLeafEngine
{
	class App : public GInput
	{
		public:
			//Init App Point
			void run();

		private:
			//GLFW
			void initGLFW();
			//Vulkan
			void initVulkan();
			//Rendering Loop
			void mainLoop();
			//Callback
			void initCallback();

			//Window Resize
			static void onWindowResized(GLFWwindow* window, int width, int height);
	};
}

#endif // !_APP_H