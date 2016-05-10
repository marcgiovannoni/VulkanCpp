/*
 *  Commandbuffer.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Commandbuffer.h"
#include "VulkanCpp/Device.h"
#include "VulkanCpp/CommandPool.h"

using namespace VulkanCpp;

CommandBuffer::CommandBuffer() : _device(nullptr), _vkCommandBuffer(nullptr)
{
}

CommandBuffer::CommandBuffer(std::shared_ptr<Device> device, std::shared_ptr<CommandPool> commandPool, VkCommandBuffer vkCommandBuffer)
    : _device(device), _commandPool(commandPool), _vkCommandBuffer(vkCommandBuffer)
{

}

CommandBuffer::CommandBuffer(std::shared_ptr<Device> device, std::shared_ptr<CommandPool> commandPool, VkCommandBufferAllocateInfo* vkCommandBufferAllocateInfo) : _device(device), _commandPool(commandPool)
{
    if (vkCommandBufferAllocateInfo->commandBufferCount != 1)
    {
        throw new VkException(VK_ERROR_TOO_MANY_OBJECTS);
    }

    VkResult err = vkAllocateCommandBuffers(static_cast<VkDevice>(*device), vkCommandBufferAllocateInfo, &this->_vkCommandBuffer);
    VK_LOG_ERROR(Device::createCommandBuffer, err);
    
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

CommandBuffer::~CommandBuffer()
{
    if (this->_vkCommandBuffer != nullptr)
    {
        vkFreeCommandBuffers(static_cast<VkDevice>(*this->_device), static_cast<VkCommandPool>(*this->_commandPool), 1, &this->_vkCommandBuffer);
    }
}

CommandBuffer::CommandBuffer(CommandBuffer&& rhs)
{
    this->_vkCommandBuffer = std::move(rhs._vkCommandBuffer);
    this->_device = std::move(rhs._device);
    this->_commandPool = std::move(rhs._commandPool);

    rhs._vkCommandBuffer = nullptr;
    rhs._device = nullptr;
    rhs._commandPool = nullptr;
}

CommandBuffer& CommandBuffer::operator=(CommandBuffer&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_commandPool = std::move(rhs._commandPool);
        this->_vkCommandBuffer = std::move(rhs._vkCommandBuffer);
        rhs._device = nullptr;
        rhs._commandPool = nullptr;
        rhs._vkCommandBuffer = nullptr;
    }
    return *this;
}

CommandBuffer::operator VkCommandBuffer() const
{
    return this->_vkCommandBuffer;
}

void CommandBuffer::begin(VkCommandBufferBeginInfo* vkCommandBufferBeginInfo) const
{
    VkResult err = vkBeginCommandBuffer(this->_vkCommandBuffer, vkCommandBufferBeginInfo);
    VK_LOG_ERROR(VulkanRenderer::beginCommandBuffer, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

void CommandBuffer::end() const
{
    VkResult err = vkEndCommandBuffer(this->_vkCommandBuffer);
    VK_LOG_ERROR(VulkanRenderer::endCommandBuffer, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

std::vector<CommandBuffer> CommandBuffer::allocate(std::shared_ptr<Device> device, std::shared_ptr<CommandPool> commandPool, VkCommandBufferAllocateInfo* vkCommandBufferAllocateInfo)
{
    std::vector<VkCommandBuffer> vkCommandBuffers(vkCommandBufferAllocateInfo->commandBufferCount);

    VkResult err = vkAllocateCommandBuffers(static_cast<VkDevice>(*device), vkCommandBufferAllocateInfo, &vkCommandBuffers[0]);
    VK_LOG_ERROR(Device::createCommandBuffer, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
    std::vector<CommandBuffer> commandBuffers;

    for (std::vector<VkCommandBuffer>::iterator i = vkCommandBuffers.begin(),
        end = vkCommandBuffers.end(); i != end; ++i)
    {
        commandBuffers.push_back(CommandBuffer(device, commandPool, *i));
    }
    return commandBuffers;
}

void CommandBuffer::free(std::vector<CommandBuffer>& vector)
{
    uint32_t len = static_cast<uint32_t>(vector.size());

    if (len > 0)
    {
        std::vector<VkCommandBuffer> vkCommandBuffers;

        vkCommandBuffers.reserve(len);
        VkDevice device = static_cast<VkDevice>(*vector[0]._device);
        VkCommandPool commandPool = static_cast<VkCommandPool>(*vector[0]._commandPool);

        for (uint32_t i = 0; i < len; ++i)
        {
            vkCommandBuffers[i] = static_cast<VkCommandBuffer>(vector[i]);
        }

        vkFreeCommandBuffers(device, commandPool, len, &vkCommandBuffers[0]);
    }
}
