
#include "VertexBuffers.h"

namespace zLeafEngine
{
	//Triangle
	const std::vector<VertexBuffers::Vertex> VertexBuffers::triangleVertices =
	{
		{ {  0.0f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ {  0.5f,  0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		{ { -0.5f,  0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } }
	};

	//Rectangle
	const std::vector<VertexBuffers::Vertex> VertexBuffers::rectangleVertices =
	{
		{ { -0.5f, -0.5f,  0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ {  0.5f, -0.5f,  0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		{ {  0.5f,  0.5f,  0.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { -0.5f,  0.5f,  0.0f },{ 1.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },

		{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
		{ {  0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
		{ {  0.5f,  0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	};

	const std::vector<uint16_t> VertexBuffers::rectangleIndices =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	//Vertex Buffer Functions
	void VertexBuffers::loadModel()
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, MODEL_PATH.c_str()))
		{
			throw std::runtime_error(err);
		}

		std::unordered_map<Vertex, int> uniqueVertices = {};

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex = {};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<int>(modelVertices.size());
					modelVertices.push_back(vertex);
				}

				modelIndices.push_back(uniqueVertices[vertex]);
			}
		}
	}

	void VertexBuffers::createUniformBuffer()
	{
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformStagingBuffer, uniformStagingBufferMemory);
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, uniformBuffer, uniformBufferMemory);
	}

	void VertexBuffers::updateUniformBuffer()
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

		UniformBufferObject ubo = {};
		ubo.model = glm::rotate(glm::mat4(), time * glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		void* data;
		vkMapMemory(mDevice, uniformStagingBufferMemory, 0, sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(mDevice, uniformStagingBufferMemory);

		copyBuffer(uniformStagingBuffer, uniformBuffer, sizeof(ubo));
	}

	VkVertexInputBindingDescription VertexBuffers::Vertex::getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 3> VertexBuffers::Vertex::getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		///inPosition (vec2)
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		///inColor (vec3)
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		///inTexCoord (vec2)
		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}

	bool VertexBuffers::Vertex::operator==(const Vertex& other) const
	{
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}

	void VertexBuffers::createVertexBuffer()
	{
		VkDeviceSize bufferSize = sizeof(modelVertices[0]) * modelVertices.size();

		VDeleter<VkBuffer> stagingBuffer{ mDevice, vkDestroyBuffer };
		VDeleter<VkDeviceMemory> stagingBufferMemory{ mDevice, vkFreeMemory };
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(mDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, modelVertices.data(), (size_t)bufferSize);
		vkUnmapMemory(mDevice, stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

		copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		std::cout << "--Vertex Buffer created!\n";
	}

	void VertexBuffers::createIndexBuffer()
	{
		VkDeviceSize bufferSize = sizeof(modelIndices[0]) * modelIndices.size();

		VDeleter<VkBuffer> stagingBuffer{ mDevice, vkDestroyBuffer };
		VDeleter<VkDeviceMemory> stagingBufferMemory{ mDevice, vkFreeMemory };
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(mDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, modelIndices.data(), (size_t)bufferSize);
		vkUnmapMemory(mDevice, stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

		copyBuffer(stagingBuffer, indexBuffer, bufferSize);
	}
}