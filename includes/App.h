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
	class App : private GInput
	{
		public:
			//Init App Point
			void run();

		private:
			//Init App Point
			void initWindow();
			void initVulkan();
			void mainLoop();

			//Window
			static void onWindowResized(GLFWwindow* window, int width, int height);
	};
}

#endif // !_APP_H