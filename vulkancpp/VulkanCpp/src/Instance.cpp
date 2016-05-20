/*
 *  Instance.cpp
 *  
 *  Created by Marc Giovannoni on 19/04/2016
 */

#include "VulkanCpp/Instance.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/PhysicalDevice.h"
#include "VulkanCpp/VkException.h"

using namespace VulkanCpp;

Instance::Instance(VkInstanceCreateInfo* instanceCreateInfo)
{
    VK_CHECK_ERROR(Instance::Instance, vkCreateInstance(instanceCreateInfo, nullptr, &this->_vkHandle));
}

Instance::Instance(const std::vector<const char *>& layers, const std::vector<const char *>& extensions)
{
    VkInstanceCreateInfo vkInstanceCreateInfo;

    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceCreateInfo.pApplicationInfo = nullptr;
    vkInstanceCreateInfo.pNext = nullptr;
    vkInstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
    vkInstanceCreateInfo.ppEnabledLayerNames = layers.data();
    vkInstanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    vkInstanceCreateInfo.ppEnabledExtensionNames = extensions.data();

    VK_CHECK_ERROR(Instance::Instance, vkCreateInstance(&vkInstanceCreateInfo, nullptr, &this->_vkHandle));
}

Instance::~Instance()
{
    if (this->_vkHandle != nullptr)
    {
        vkDestroyInstance(this->_vkHandle, nullptr);
        this->_vkHandle = nullptr;
    }
}

std::vector<PhysicalDevice> Instance::enumeratePhysicalDevices() const
{
    uint32_t deviceCnt = 0;
    std::vector<PhysicalDevice> physicalDevices;

    VK_CHECK_ERROR(Instance::enumeratePhysicalDevices, vkEnumeratePhysicalDevices(this->_vkHandle, &deviceCnt, nullptr));
    if (!deviceCnt)
    {
        LOG_ERROR(Instance, "No physical devices found.");
        return physicalDevices;
    }

    std::vector<VkPhysicalDevice> vKphysicalDevices(deviceCnt);

    VK_CHECK_ERROR(Instance::enumeratePhysicalDevices, vkEnumeratePhysicalDevices(this->_vkHandle, &deviceCnt, &vKphysicalDevices[0]));

    for (std::vector<VkPhysicalDevice>::iterator i = vKphysicalDevices.begin(),
        end = vKphysicalDevices.end(); i != end; ++i)
    {
        physicalDevices.push_back(PhysicalDevice(*i));
    }
    return physicalDevices;
}