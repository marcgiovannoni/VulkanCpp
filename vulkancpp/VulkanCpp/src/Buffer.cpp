/*
 *  Buffer.cpp
 *  
 *  Created by Marc Giovannoni on 18/05/2016
 */

#include "VulkanCpp/Buffer.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

Buffer::Buffer() : VkWrapper()
{
    // Empty
}

Buffer::Buffer(const std::shared_ptr<Device>& device, VkBufferCreateInfo* vkBufferCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(Buffer::Buffer, vkCreateBuffer(static_cast<VkDevice>(*device), vkBufferCreateInfo, nullptr, &this->_vkHandle));
}

Buffer::~Buffer()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyBuffer(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}

VkMemoryRequirements Buffer::getMemoryRequirements() const
{
    VkMemoryRequirements requirements;

    vkGetBufferMemoryRequirements(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, &requirements);
    
    return requirements;
}

void Buffer::bindMemory(const Device::Memory& deviceMemory, VkDeviceSize offset)
{
    vkBindBufferMemory(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, static_cast<VkDeviceMemory>(deviceMemory), offset);
}
