/*
  Draws frames and updates content on screen.
  Recreates swap chains and check queues.
*/

#ifndef _DRAWFRAME_H
#define _DRAWFRAME_H

#include "stdafx.h"
#include "DepthBuffers.h"

namespace zLeafEngine
{
	class DrawFrame : protected DepthBuffers // -> GInput
	{
		protected:
			//Draw Frame
			void drawFrame();

			//Update Frame
			void recreateSwapChain();
	};
}

#endif // !_DRAWFRAME_H
