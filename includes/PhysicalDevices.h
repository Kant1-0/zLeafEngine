/*
  Check if a Vulkan compatible physical device exists.
  Then rate its suitability and compare which one is the best.
*/

#ifndef _PHYSICALDEVICES_H
#define _PHYSICALDEVICES_H

#include "stdafx.h"
#include "ValidationLayer.h"

namespace zLeafEngine
{
	class PhysicalDevices : public ValidationLayer //-> LogicalDevices
	{
		protected:
			//Physical Devices
			static VkPhysicalDevice mPhysicalDevice;

			void pickPhysicalDevice();

			static const std::vector<const char*> deviceExtensions;

			//Queue Families
			struct QueueFamilyIndices
			{
				static int32_t graphicsFamily;
				static int32_t presentFamily;

				bool isComplete() const;
			};

			QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

			//Window Surface
			VDeleter<VkSurfaceKHR> surface{ mInstance, vkDestroySurfaceKHR };
			void createSurface();

			//Swap Chain
			struct SwapChainSupportDetails
			{
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentModes;
			};

			SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		private:
			//Physical Devices
			bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			int64_t rateDeviceSuitability(VkPhysicalDevice device);

	};
}

#endif // !_PHYSICALDEVICES_H
