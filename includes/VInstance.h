/*
  Constructors for mInstance used to init the app
  and launch zLeaf Engine.
*/


#ifndef _VINSTANCE_H
#define _VINSTANCE_H

#include "stdafx.h"
#include "VDeleter.h"

namespace zLeafEngine
{
	class VInstance
	{
		protected:
			//Vulkan Instance (App)
			VDeleter<VkInstance> mInstance{ vkDestroyInstance };

			//GLFW Extensions (App)
			std::vector<const char*> getRequiredExtensions();

			//Macro for Debug
			#ifdef NDEBUG
			const bool enableValidationLayers = false;
			#else
			const bool enableValidationLayers = true;
			#endif
	};
}

#endif // !_VINSTANCE_H
