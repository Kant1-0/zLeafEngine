/*
  Implement texturing for Vulkan using STB import library.
*/

#ifndef _VTEXEL_H
#define _VTEXEL_H

#include "stdafx.h"
#include "FrameBuffers.h"

namespace zLeafEngine
{
	class VTexels : protected FrameBuffers //-> DepthBuffers
	{
		protected:
			//Loading Images
			void createTextureImage();
			void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkImage>& image, VDeleter<VkDeviceMemory>& imageMemory);

			//Transition Image Layout
			void transitionImageLayout(VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout);
			void copyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);

			//Image View
			void createTextureImageView();
			void createImageViews();
			void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VDeleter<VkImageView>& imageView);

			//Samplers
			void createTextureSampler();

		private:
			//Images
			VDeleter<VkImage> textureImage{ mDevice, vkDestroyImage };

			//Image Memories
			VDeleter<VkDeviceMemory> textureImageMemory{ mDevice, vkFreeMemory };
	};
}

#endif // !_VTEXTURES_H
