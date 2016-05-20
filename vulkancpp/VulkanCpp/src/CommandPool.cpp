/*
 *  CommandPool.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VulkanCpp/CommandPool.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

CommandPool::CommandPool()
{
    // Empty
}

CommandPool::CommandPool(const std::shared_ptr<Device>& device, VkCommandPoolCreateInfo* vkCommandPoolCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(CommandPool::CommandPool, vkCreateCommandPool(static_cast<VkDevice>(*device), vkCommandPoolCreateInfo, nullptr, &this->_vkHandle));
}

CommandPool::~CommandPool()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        LOG_DEBUG(CommandPool::~CommandPool, "Destroy CommandPool %p", this->_vkHandle);
        vkDestroyCommandPool(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}