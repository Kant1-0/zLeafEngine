/*
  Logical device to interface with the physical device.
*/

#ifndef _LOGICALDEVICES_H
#define _LOGICALDEVICES_H

#include "stdafx.h"
#include "PhysicalDevices.h"

namespace zLeafEngine
{
	class LogicalDevices : public PhysicalDevices //-> VTextures
	{
		protected:
			//Commands (FrameBuffer)
			VDeleter<VkCommandPool> commandPool{ mDevice, vkDestroyCommandPool };

			//Logical Device
			VDeleter<VkDevice> mDevice{ vkDestroyDevice };

			void createLogicalDevice();

			//Queues
			VkQueue graphicsQueue;
			VkQueue presentQueue;

			//Swap Chain
			VDeleter<VkSwapchainKHR> mSwapChain{ mDevice, vkDestroySwapchainKHR };
			std::vector<VkImage> swapChainImages;

			void createSwapChain();

			//Image Views
			VkExtent2D swapChainExtent;
			VkFormat swapChainImageFormat;
			std::vector<VDeleter<VkImageView>> swapChainImageViews;

		private:
			//Swap Chain
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			
	};
}

#endif // !_LOGICALDEVICES_H

