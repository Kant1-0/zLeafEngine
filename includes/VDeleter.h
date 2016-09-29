/*
  Overloading functions to delete the different available Vulkan Objects.
  Help to easily cleanup the program all along the process (RAII based).
*/

#ifndef _VDELETER_H
#define _VDELETER_H

#include "stdafx.h"

namespace zLeafEngine
{
	template <typename T>
	class VDeleter
	{
	public:
		//Initialazers
		VDeleter() : VDeleter([](T, VkAllocationCallbacks*) {}) {}

		VDeleter(std::function<void(T, VkAllocationCallbacks*)> deletef)
		{
			this->deleter = [=](T obj) { deletef(obj, nullptr); };
		}

		VDeleter(const VDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
		{
			this->deleter = [&instance, deletef](T obj) { deletef(instance, obj, nullptr); };
		}

		VDeleter(const VDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
		{
			this->deleter = [&device, deletef](T obj) { deletef(device, obj, nullptr); };
		}

		//Deconstructors
		~VDeleter()
		{
			cleanup();
		}


		//Surcharged Operators
		const T* operator &() const
		{
			return &object;
		}

		operator T() const
		{
			return object;
		}

		void operator=(T rhs)
		{
			cleanup();
			object = rhs;
		}

		template<typename V>
		bool operator==(V rhs)
		{
			return object == T(rhs);
		}


		//Cleanup Function
		T* replace()
		{
			cleanup();
			return &object;
		}

	private:
		//Objects
		T object{ VK_NULL_HANDLE };
		std::function<void(T)> deleter;

		//Cleanup Function
		void cleanup()
		{
			if (object != VK_NULL_HANDLE)
			{
				deleter(object);
			}
			object = VK_NULL_HANDLE;
		}
	};
}

#endif // !_VDELETER_H
