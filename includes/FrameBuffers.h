/*
  FrameBuffer binded to the SwapChain.
  Render objects on screen.
*/

#ifndef _FRAMEBUFFERS_H
#define _FRAMEBUFFERS_H

#include "stdafx.h"
#include "GraphicsPipeline.h"

namespace zLeafEngine
{
	class FrameBuffers : protected GraphicsPipeline
	{
		protected:
			//Descriptor Pool
			void createDescriptorPool();
			void createDescriptorSet();

			//Frame Buffers
			void createFramebuffers();

			//Commands
			void createCommandPool();
			void createCommandBuffers();

			//Synchronization
			void createSemaphores();

			//Draw Frame
			void drawFrame();

			//Recreate Swap Chain
			void recreateSwapChain();

		private:
			//Descriptor Pool
			VDeleter<VkDescriptorPool> descriptorPool{ mDevice, vkDestroyDescriptorPool };
			VkDescriptorSet descriptorSet;

			//Frame Buffers
			std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;

			//Commands
			std::vector<VkCommandBuffer> commandBuffers;

			//Synchronization
			VDeleter<VkSemaphore> imageAvailableSemaphore{ mDevice, vkDestroySemaphore };
			VDeleter<VkSemaphore> renderFinishedSemaphore{ mDevice, vkDestroySemaphore };
	};
}

#endif // !_FRAMEBUFFERS_H
