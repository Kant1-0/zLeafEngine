/*
  Enable Z axis ordering checking to correctly render 3D objects in space.
*/

#ifndef _DEPTHBUFFERS_H
#define _DEPTHBUFFERS_H

#include "stdafx.h"
#include "VTexels.h"

namespace zLeafEngine
{
	class DepthBuffers : public VTexels //-> CameraProjection
	{
		protected:
			//Depth Ressources
			void createDepthResources();

		private:
			//Depth Images and Views
			VDeleter<VkImage> depthImage{ mDevice, vkDestroyImage };

			//Depth Memory
			VDeleter<VkDeviceMemory> depthImageMemory{ mDevice, vkFreeMemory };

	};
}

#endif // !_DEPTHBUFFERS_H
