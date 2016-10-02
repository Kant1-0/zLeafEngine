/*
  Constructors for mInstance used to init the app
  and launch zLeaf Engine.
*/


#ifndef _VINSTANCE_H
#define _VINSTANCE_H

#include "stdafx.h"
#include "VDeleter.h"
#include "GWindow.h"

namespace zLeafEngine
{
	class VInstance : public GWindow //-> ValidationLayer
	{
		protected:
			//Vulkan Instance (App)
			VDeleter<VkInstance> mInstance{ vkDestroyInstance };
			void createInstance();

			//Validation Layers
			static const std::vector<const char*> validationLayers;
			bool checkValidationLayerSupport();

			//Macro for Debug
			#ifdef NDEBUG
			const bool enableValidationLayers = false;
			#else
			const bool enableValidationLayers = true;
			#endif

		private:
			//GLFW Extensions for Vulkan
			std::vector<const char*> getRequiredExtensions();
	};
}

#endif // !_VINSTANCE_H
