/*
 *  Device.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VulkanCpp/Device.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Queue.h"
#include "VulkanCpp/PhysicalDevice.h"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

Device::Device(const PhysicalDevice& physicalDevice, VkDeviceCreateInfo* deviceCreateInfo)
{
    VkResult err = vkCreateDevice(static_cast<VkPhysicalDevice>(physicalDevice), deviceCreateInfo, nullptr, &this->_vkDevice);
    VK_LOG_ERROR(PhysicalDevice::PhysicalDevice, err);
    
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

Device::~Device()
{
    if (this->_vkDevice != nullptr)
    {
        vkDestroyDevice(this->_vkDevice, nullptr);
    }
}

Device::Device(Device&& rhs)
{
    this->_vkDevice = std::move(rhs._vkDevice);

    rhs._vkDevice = nullptr;
}

Device& Device::operator=(Device&& rhs)
{
    if (this != &rhs)
    {
        this->_vkDevice = std::move(rhs._vkDevice);
        rhs._vkDevice = nullptr;
    }
    return *this;
}

Device::operator VkDevice() const
{
    return this->_vkDevice;
}

Queue Device::getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex)
{
    VkQueue vkQueue = nullptr;

    vkGetDeviceQueue(this->_vkDevice, queueFamilyIndex, queueIndex, &vkQueue);
    return Queue(vkQueue);
}