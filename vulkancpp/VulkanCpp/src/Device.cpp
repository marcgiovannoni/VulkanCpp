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
    VK_CHECK_ERROR(Device::Device, vkCreateDevice(static_cast<VkPhysicalDevice>(physicalDevice), deviceCreateInfo, nullptr, &this->_vkHandle));
}

Device::~Device()
{
    if (this->_vkHandle != nullptr)
    {
        vkDestroyDevice(this->_vkHandle, nullptr);
    }
}

Queue Device::getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex)
{
    VkQueue vkQueue = nullptr;

    vkGetDeviceQueue(this->_vkHandle, queueFamilyIndex, queueIndex, &vkQueue);
    return Queue(vkQueue);
}

Device::Memory Device::allocateMemory(VkDeviceSize size, uint32_t memoryTypeIndex)
{
    VkMemoryAllocateInfo vkMemoryAllocateInfo;
    VkDeviceMemory vkDeviceMemory;

    vkMemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    vkMemoryAllocateInfo.allocationSize = size;
    vkMemoryAllocateInfo.memoryTypeIndex = memoryTypeIndex;
    vkMemoryAllocateInfo.pNext = nullptr;

    vkAllocateMemory(this->_vkHandle, &vkMemoryAllocateInfo, nullptr, &vkDeviceMemory);

    return Device::Memory(vkDeviceMemory, this->shared_from_this());
}

Device::Memory::Memory(VkDeviceMemory vkDeviceMemory, const std::shared_ptr<Device>& device) : VkWrapper(vkDeviceMemory, device)
{
    // Empty
}

Device::Memory::Memory()
{
    // Empty
}

Device::Memory::~Memory()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkFreeMemory(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}

void Device::Memory::map(VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** data)
{
    VK_CHECK_ERROR(Device::Memory::map, vkMapMemory(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, offset, size, flags, data));
}

void Device::Memory::unmap()
{
    vkUnmapMemory(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle);
}
