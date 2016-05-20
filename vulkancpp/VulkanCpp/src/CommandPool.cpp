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

CommandPool::CommandPool(const std::shared_ptr<Device>& device, uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags) : VkWrapper(device)
{
    VkCommandPoolCreateInfo vkCommandPoolCreateInfo;

    vkCommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    vkCommandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
    vkCommandPoolCreateInfo.flags = flags;
    vkCommandPoolCreateInfo.pNext = nullptr;

    VK_CHECK_ERROR(CommandPool::CommandPool, vkCreateCommandPool(static_cast<VkDevice>(*device), &vkCommandPoolCreateInfo, nullptr, &this->_vkHandle));
}

CommandPool::~CommandPool()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        LOG_DEBUG(CommandPool::~CommandPool, "Destroy CommandPool %p", this->_vkHandle);
        vkDestroyCommandPool(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}