/*
  Setup the Validation Layer debugging stage for Vulkan.
*/

#ifndef _VALIDATIONLAYER_H
#define _VALIDATIONLAYER_H

//#define NDEBUG

#include "stdafx.h"
#include "VInstance.h"

namespace zLeafEngine
{
	class ValidationLayer: protected VInstance //-> LogicalDevices
	{
		protected:
			//Validation Layer (Debug)
			void setupDebugCallback();

		private:
			//Message Callback
			VDeleter<VkDebugReportCallbackEXT> callback{ mInstance, DestroyDebugReportCallbackEXT };

			static VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
			static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
	};
}

#endif // !_VALIDATIONLAYER_H