/*
  Functions to manage the creation of Vulkan Buffers.
*/

#ifndef _VBUFFER_H
#define _VBUFFER_H

#include "stdafx.h"
#include "LogicalDevices.h"

namespace zLeafEngine
{
	class VBuffer : public LogicalDevices //-> VertexBuffer
	{
		protected:
		//Buffer Creation
			void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VDeleter<VkBuffer>& buffer, VDeleter<VkDeviceMemory>& bufferMemory);

			void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

			//Layout Transitions
			VkCommandBuffer beginSingleTimeCommands();
			void endSingleTimeCommands(VkCommandBuffer commandBuffer);

			//Handle Memory
			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};
}

#endif // !_VBUFFER_H
