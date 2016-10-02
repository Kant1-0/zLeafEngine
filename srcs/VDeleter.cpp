
#include "VDeleter.h"

namespace zLeafEngine
{
	template <typename T>
	VDeleter<T>::VDeleter() : VDeleter([](T _) {})
	{}

	template <typename T>
	VDeleter<T>::VDeleter(std::function<void(T, VkAllocationCallbacks*)> deletef)
	{
		object = VK_NULL_HANDLE;
		this->deleter = [=](T obj) { deletef(obj, nullptr); };
	}

	template <typename T>
	VDeleter<T>::VDeleter(const VDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
	{
		object = VK_NULL_HANDLE;
		this->deleter = [&instance, deletef](T obj) { deletef(instance, obj, nullptr); };
	}

	template <typename T>
	VDeleter<T>::VDeleter(const VDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
	{
		object = VK_NULL_HANDLE;
		this->deleter = [&device, deletef](T obj) { deletef(device, obj, nullptr); };
	}

	template <typename T>
	VDeleter<T>::~VDeleter()
	{
		cleanup();
	}

	template <typename T>
	T* VDeleter<T>::operator &()
	{
		cleanup();
		return &object;
	}

	template <typename T>
	VDeleter<T>::operator T() const
	{
		return object;
	}

	template <typename T>
	T* VDeleter<T>::replace()
	{
		cleanup();
		return &object;
	}

	template <typename T>
	void VDeleter<T>::cleanup()
	{
		if (object != VK_NULL_HANDLE)
		{
			deleter(object);
		}
		object = VK_NULL_HANDLE;
	}
}