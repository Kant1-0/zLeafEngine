
#include "App.h"

namespace zLeafEngine
{
	void	App::run()
	{
		initGLFW();
		initVulkan();
		initCallback();
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
		//VertexBuffer
		loadModel();
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
		initView();
		deltaTime = 0.0f;
		lastFrame = 0.0f;
		cameraSpeed = 15.0f;

		while (!glfwWindowShouldClose(window))
		{
			//Calcule framerate
			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glfwPollEvents();

			updateUniformBuffer();
			drawFrame();
		}

		vkDeviceWaitIdle(mDevice);
	}

	void App::initGLFW()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

		GLFWimage icon[1];
		loadIcon(GLFW_ICON, &(icon[0]));

		glfwSetWindowIcon(window, 1, icon);
		glfwSetWindowUserPointer(window, this);

		glfwSetWindowSizeCallback(window, onWindowResized);

		std::cout << "--GLWF Initiation Succeeded!\n";
	}

	void App::initCallback()
	{
		setEventHandling();

		glfwSetKeyCallback(window, inputKeyCallback_Dispatch);
		glfwSetCursorPosCallback(window, inputMouseCallback_Dispatch);
		glfwSetScrollCallback(window, inputScrollCallback_Dispatch);
	}

	void App::onWindowResized(GLFWwindow* window, int width, int height)
	{
		if (width == 0 || height == 0) return;

		App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
		app->recreateSwapChain();
	}
}