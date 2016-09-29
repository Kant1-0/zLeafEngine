
#include "App.h"

namespace zLeafEngine
{
	void	App::run()
	{
		initWindow();
		initVulkan();
		mainLoop();
	}

	void	App::initVulkan()
	{
		//VInstance
		createInstance();
		//ValidationLayer
		setupDebugCallback();
		//PhysicalDevice
		createSurface();
		pickPhysicalDevice();
		//LogicalDevice
		createLogicalDevice();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createDescriptorSetLayout();
		//GraphicsPipeline
		createGraphicsPipeline();
		createCommandPool();
		createDepthResources();
		createFramebuffers();
		createTextureImage();
		createTextureImageView();
		createTextureSampler();
		createVertexBuffer();
		createIndexBuffer();
		createUniformBuffer();
		createDescriptorPool();
		createDescriptorSet();
		createCommandBuffers();
		createSemaphores();

		std::cout << "--Vulkan Initiation Succeeded!\n";
	}

	void	App::mainLoop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			updateUniformBuffer();
			drawFrame();
		}

		vkDeviceWaitIdle(mDevice);
	}

	void	App::initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

		//Resizable Window
		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeCallback(window, App::onWindowResized);

		//Input User Action
		glfwSetKeyCallback(window, inputKeyCallback);

		std::cout << "--GLWF Initiation Succeeded!\n";
	}

	void App::onWindowResized(GLFWwindow* window, int width, int height)
	{
		if (width == 0 || height == 0) return;

		App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
		app->recreateSwapChain();
	}
}