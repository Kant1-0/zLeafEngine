
#include "PhysicalDevices.h"

namespace zLeafEngine
{
	VkPhysicalDevice PhysicalDevices::mPhysicalDevice = VK_NULL_HANDLE;

	const std::vector<const char*> PhysicalDevices::deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	int32_t PhysicalDevices::QueueFamilyIndices::graphicsFamily = -1;
	int32_t PhysicalDevices::QueueFamilyIndices::presentFamily = -1;

	GLFWwindow* PhysicalDevices::window = nullptr;

	bool PhysicalDevices::QueueFamilyIndices::isComplete() const
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}

	void PhysicalDevices::pickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(mInstance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			throw std::runtime_error("Failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(mInstance, &deviceCount, devices.data());

		// Use an ordered map to automatically sort candidates by increasing score
		std::map<int64_t, VkPhysicalDevice> candidates;

		std::cout << "--Found " << devices.size() << " graphics devices:\n";
		for (const auto& device : devices)
		{
			int64_t score = rateDeviceSuitability(device);
			std::cout << "\t" << "Score = " << score << "\n";
			candidates[score] = device;
		}

		//Check if the best candidate is suitable at all
		if (candidates.begin()->first > 0)
		{
			mPhysicalDevice = candidates.begin()->second;
			
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(mPhysicalDevice, &deviceProperties);
			std::cout << "--Using Physical Device: " << deviceProperties.deviceName << "\n";
		}
		else
		{
			throw std::runtime_error("Failed to find a suitable GPU!");
		}
	}

	int64_t PhysicalDevices::rateDeviceSuitability(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		std::cout << "Rating graphics device: " << deviceProperties.deviceName << "\n";
		int64_t score = 0;

		//Discrete GPUs have a significant performance advantage
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}

		//Maximum possible size of textures affects graphics quality
		score += deviceProperties.limits.maxImageDimension2D;
		score += deviceProperties.limits.maxMemoryAllocationCount;
		score += deviceProperties.limits.maxSamplerAllocationCount;

		//Queue Families
		QueueFamilyIndices indices = findQueueFamilies(device);

		//Extensions Supported
		bool extensionsSupported = checkDeviceExtensionSupport(device);

		//Adequate Swap Chain
		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

			score += static_cast<int64_t>(swapChainSupport.capabilities.maxImageArrayLayers);
			score += static_cast<int64_t>(swapChainSupport.capabilities.maxImageCount);

			//Zero maxImageCount means illimited (usual value is 8)
			if (swapChainSupport.capabilities.maxImageCount == 0)
			{
				score += 100;
			}
		}

		//Set NULL Score if Error
		if (!swapChainAdequate)
		{
			std::cerr << "\t" << "_Device does not support swap-chain, or is inadequate!\n";
			score = 0;
		}
		if (!extensionsSupported)
		{
			std::cerr << "\t" << "_Device does not support required extensions, or is inadequate!\n";
			score = 0;
		}
		if (!indices.isComplete())
		{
			std::cerr << "\t" << "_Device does not support queues, or is inadequate!\n";
			score = 0;
		}
		if (!deviceFeatures.geometryShader)
		{
			std::cerr << "\t" << "_Device does not support geometry shaders, or is inadequate!\n";
			score = 0;
		}

		return score;
	}

	PhysicalDevices::QueueFamilyIndices PhysicalDevices::findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		size_t i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = static_cast<int32_t>(i);
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, static_cast<uint32_t>(i), surface, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport)
			{
				indices.presentFamily = static_cast<int32_t>(i);
			}

			if (indices.isComplete())
			{
				break;
			}

			++i;
		}

		return indices;
	}

	PhysicalDevices::SwapChainSupportDetails PhysicalDevices::querySwapChainSupport(VkPhysicalDevice device)
	{
		SwapChainSupportDetails details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	bool PhysicalDevices::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	void PhysicalDevices::createSurface()
	{
		if (glfwCreateWindowSurface(mInstance, window, nullptr, surface.replace()) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create window surface!");
		}
	}
}