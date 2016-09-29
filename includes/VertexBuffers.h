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
	class VertexBuffers : protected VBuffer //-> GraphicsPipeline
	{
		public:
			//Vertex Data
			struct Vertex
			{
				glm::vec3 pos;
				glm::vec3 color;
				glm::vec2 texCoord;

				///Binding Descriptions
				static VkVertexInputBindingDescription getBindingDescription();
				///Attribute Descriptions
				static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

				bool operator==(const Vertex& other) const;
			};

		protected:
			struct UniformBufferObject
			{
				glm::mat4 model;
				glm::mat4 view;
				glm::mat4 proj;
			};

			///Model Import
			std::vector<Vertex> modelVertices;
			std::vector<uint32_t> modelIndices;
			///Triangle
			static const std::vector<Vertex> triangleVertices;
			///Rectangle
			static const std::vector<Vertex> rectangleVertices;
			static const std::vector<uint16_t> rectangleIndices;

			//Uniform Buffer Object
			void createUniformBuffer();
			void updateUniformBuffer();

			//Load Model
			void loadModel();

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

namespace std
{
	template<> struct hash<zLeafEngine::VertexBuffers::Vertex>
	{
		size_t operator()(zLeafEngine::VertexBuffers::Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

#endif // !_VERTEXDATA_H
