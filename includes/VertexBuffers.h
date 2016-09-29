/*
  Buffer holding vertex information.
  Binds to shaders. 
*/

#ifndef _VERTEXBUFFERS_H
#define _VERTEXBUFFERS_H

#include "stdafx.h"
#include "VBuffer.h"

namespace zLeafEngine
{
	class VertexBuffers : protected VBuffer
	{
		protected:
			//Vertex Data
			struct Vertex
			{
				glm::vec2 pos;
				glm::vec3 color;

				///Binding Descriptions
				static VkVertexInputBindingDescription getBindingDescription();
				///Attribute Descriptions
				static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
			};

			struct UniformBufferObject
			{
				glm::mat4 model;
				glm::mat4 view;
				glm::mat4 proj;
			};

			///Triangle
			static const std::vector<Vertex> triangleVertices;
			///Rectangle
			static const std::vector<Vertex> rectangleVertices;
			static const std::vector<uint16_t> rectangleIndices;

			//Uniform Buffer Object
			void createUniformBuffer();
			void updateUniformBuffer();

			//Vertex Buffer
			void createVertexBuffer();

			//IndexBuffer
			void createIndexBuffer();

			//Buffers
			VDeleter<VkBuffer> vertexBuffer{ mDevice, vkDestroyBuffer };
			VDeleter<VkBuffer> indexBuffer{ mDevice, vkDestroyBuffer };
			VDeleter<VkBuffer> uniformStagingBuffer{ mDevice, vkDestroyBuffer };
			VDeleter<VkBuffer> uniformBuffer{ mDevice, vkDestroyBuffer };

		private:
			//Buffer Memories
			VDeleter<VkDeviceMemory> vertexBufferMemory{ mDevice, vkFreeMemory };
			VDeleter<VkDeviceMemory> indexBufferMemory{ mDevice, vkFreeMemory };
			VDeleter<VkDeviceMemory> uniformStagingBufferMemory{ mDevice, vkFreeMemory };
			VDeleter<VkDeviceMemory> uniformBufferMemory{ mDevice, vkFreeMemory };
	};
}

#endif // !_VERTEXDATA_H
