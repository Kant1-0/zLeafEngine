/*
  Draws frames and updates content on screen.
  Recreates swap chains and check queues.
*/

#ifndef _DRAWFRAME_H
#define _DRAWFRAME_H

#include "stdafx.h"
#include "CameraProjection.h"

namespace zLeafEngine
{
	class DrawFrame : public CameraProjection // -> GInput
	{
		protected:
			//Update Frame
			void recreateSwapChain();
			void updateUniformBuffer();

			//Draw Frame
			void drawFrame();

			//Framerate
			float deltaTime;
			float lastFrame;
	};
}

#endif // !_DRAWFRAME_H
