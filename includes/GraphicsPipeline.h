/*
  Graphics pipeline operation sequence.
  Takes the vertices and textures of a mesh all the way to the pixels
  in the render targets.
*/

#ifndef _GRAPHICSPIPELINE_H
#define _GRAPHICSPIPELINE_H

#include "stdafx.h"
#include "VertexBuffers.h"

namespace zLeafEngine
{
	class GraphicsPipeline : protected VertexBuffers
	{
		protected:
			//Descriptor Set Layout
			VDeleter<VkDescriptorSetLayout> mDescriptorSetLayout{ mDevice, vkDestroyDescriptorSetLayout };
			void createDescriptorSetLayout();

			//Render Pass
			VDeleter<VkRenderPass> mRenderPass{ mDevice, vkDestroyRenderPass };
			void createRenderPass();

			//Graphics Pipeline
			VDeleter<VkPipeline> mGraphicsPipeline{ mDevice, vkDestroyPipeline };
			VDeleter<VkPipelineLayout> pipelineLayout{ mDevice, vkDestroyPipelineLayout };
			void createGraphicsPipeline();

		private:
			/*//Graphics Pipeline
			void initShaderModules();
			void initVertexInput();
			void initViewportScissors();
			void initRasterizer();
			void initMultisampling();
			void initDepthStencil();
			void initColorBlending();
			void initDynamicState();
			void initPipelineLayout();
			*/
			//Files Handle
			static std::vector<char> readFile(const std::string& filename);

			//Shader
			void createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule);
	};
}

#endif // !_GRAPHICSPIPELINE_H
