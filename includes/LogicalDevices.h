/*
  Logical device to interface with the physical device.
*/

#ifndef _LOGICALDEVICES_H
#define _LOGICALDEVICES_H

#include "stdafx.h"
#include "PhysicalDevices.h"

namespace zLeafEngine
{
	class LogicalDevices : protected PhysicalDevices
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
			void createSwapChain();

			//Image Views
			VkExtent2D swapChainExtent;
			VkFormat swapChainImageFormat;
			std::vector<VDeleter<VkImageView>> swapChainImageViews;

			void createImageViews();

		private:
			//Swap Chain
			std::vector<VkImage> swapChainImages;

			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
			VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			
	};
}

#endif // !_LOGICALDEVICES_H

