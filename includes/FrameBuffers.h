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
	class FrameBuffers : protected GraphicsPipeline //-> VTexels
	{
		protected:
			//Descriptor Pool
			void createDescriptorPool();
			void createDescriptorSet();

			//Frame Buffers
			void createFramebuffers();

			//Commands
			std::vector<VkCommandBuffer> commandBuffers;

			void createCommandPool();
			void createCommandBuffers();

			//Synchronization
			VDeleter<VkSemaphore> imageAvailableSemaphore{ mDevice, vkDestroySemaphore };
			VDeleter<VkSemaphore> renderFinishedSemaphore{ mDevice, vkDestroySemaphore };

			void createSemaphores();

			//Textures
			VDeleter<VkImageView> textureImageView{ mDevice, vkDestroyImageView };
			VDeleter<VkSampler> textureSampler{ mDevice, vkDestroySampler };

			//Depth Image View
			VDeleter<VkImageView> depthImageView{ mDevice, vkDestroyImageView };

		private:
			//Descriptor Pool
			VDeleter<VkDescriptorPool> descriptorPool{ mDevice, vkDestroyDescriptorPool };
			VkDescriptorSet descriptorSet;

			//Frame Buffers
			std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;
	};
}

#endif // !_FRAMEBUFFERS_H
