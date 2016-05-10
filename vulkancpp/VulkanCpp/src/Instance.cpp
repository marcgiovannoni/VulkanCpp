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
    VkResult err = vkCreateInstance(instanceCreateInfo, nullptr, &this->_vkInstance);

    if (err != VK_SUCCESS)
    {
        VK_LOG_ERROR(Instance::Instance, err);
        throw new VkException(err);
    }
    LOG_DEBUG(Instance::Instance, "Vulkan instance successfully created.");
}

Instance::~Instance()
{
    if (this->_vkInstance != nullptr)
    {
        vkDestroyInstance(this->_vkInstance, nullptr);
        this->_vkInstance = nullptr;
        LOG_DEBUG(Instance::Instance, "Vulkan instance successfully destroyed.");
    }
}

Instance::Instance(Instance&& rhs)
{
    this->_vkInstance = std::move(rhs._vkInstance);
    rhs._vkInstance = nullptr;
}

Instance& Instance::operator=(Instance&& rhs)
{
    if (this != &rhs)
    {
        this->_vkInstance = std::move(rhs._vkInstance);
        rhs._vkInstance = nullptr;
    }
    return *this;
}

Instance::operator VkInstance() const
{
    return this->_vkInstance;
}

std::vector<PhysicalDevice> Instance::enumeratePhysicalDevices() const
{
    uint32_t deviceCnt = 0;
    std::vector<PhysicalDevice> physicalDevices;

    VkResult err = vkEnumeratePhysicalDevices(this->_vkInstance, &deviceCnt, nullptr);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
    if (!deviceCnt)
    {
        LOG_ERROR(Instance, "No physical devices found.");
        return physicalDevices;
    }

    std::vector<VkPhysicalDevice> vKphysicalDevices(deviceCnt);

    err = vkEnumeratePhysicalDevices(this->_vkInstance, &deviceCnt, &vKphysicalDevices[0]);
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
    for (std::vector<VkPhysicalDevice>::iterator i = vKphysicalDevices.begin(),
        end = vKphysicalDevices.end(); i != end; ++i)
    {
        physicalDevices.push_back(PhysicalDevice(*i));
    }
    return physicalDevices;
}