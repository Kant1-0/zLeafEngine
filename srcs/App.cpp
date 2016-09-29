
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
		createInstance();
		setupDebugCallback();
		createSurface();
		pickPhysicalDevice();
		createLogicalDevice();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createDescriptorSetLayout();
		createGraphicsPipeline();
		createFramebuffers();
		createCommandPool();
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

	void App::createInstance()
	{
		//Enable validation layers
		if (enableValidationLayers && !checkValidationLayerSupport())
		{
			throw std::runtime_error("Validation layers requested, but not available!");
		}

		//Application info
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = APPLICATION_TITLE;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = ENGINE_TITLE;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//Vulkan instance info
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		// GLFW extensions
		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		// Create the actual instance
		VkResult result = vkCreateInstance(&createInfo, nullptr, mInstance.replace());

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create instance!");
		}

		std::cout << "--Vulkan Instance Created!\n";
	}

	void App::onWindowResized(GLFWwindow* window, int width, int height)
	{
		if (width == 0 || height == 0) return;

		App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
		app->recreateSwapChain();
	}
}