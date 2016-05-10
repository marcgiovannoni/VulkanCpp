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

CommandPool::CommandPool(std::shared_ptr<Device> device, VkCommandPoolCreateInfo* vkCommandPoolCreateInfo) : _device(device)
{
    VkResult err = vkCreateCommandPool(static_cast<VkDevice>(*device), vkCommandPoolCreateInfo, nullptr, &this->_vkCommandPool);
    VK_LOG_ERROR(CommandPool::CommandPool, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

CommandPool::~CommandPool()
{
    vkDestroyCommandPool(static_cast<VkDevice>(*this->_device), this->_vkCommandPool, nullptr);
}

CommandPool::CommandPool(CommandPool&& rhs)
{
    this->_vkCommandPool = std::move(rhs._vkCommandPool);
    this->_device = std::move(rhs._device);
    rhs._vkCommandPool = nullptr;
    rhs._device = nullptr;
}

CommandPool& CommandPool::operator=(CommandPool&& rhs)
{
    if (this != &rhs)
    {
        this->_vkCommandPool = std::move(rhs._vkCommandPool);
        this->_device = std::move(rhs._device);
        rhs._vkCommandPool = nullptr;
        rhs._device = nullptr;
    }
    return *this;
}

CommandPool::operator VkCommandPool() const
{
    return this->_vkCommandPool;
}
