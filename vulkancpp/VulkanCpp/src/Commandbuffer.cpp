/*
 *  Commandbuffer.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Commandbuffer.hpp"
#include "VulkanCpp/Device.h"
#include "VulkanCpp/CommandPool.h"
#include "VulkanCpp/Command.h"

using namespace VulkanCpp;
using namespace VulkanCpp::Command;

CommandBuffer::CommandBuffer()
{
    // Empty
}

CommandBuffer::CommandBuffer(VkCommandBuffer vkCommandBuffer, const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool)
    : VkWrapper(vkCommandBuffer, device, commandPool)
{
    // Empty
}

CommandBuffer::CommandBuffer(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, VkCommandBufferLevel level)
    : VkWrapper(device, commandPool)
{
    VkCommandBufferAllocateInfo vkCommandBufferAllocateInfo;

    vkCommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    vkCommandBufferAllocateInfo.commandPool = static_cast<VkCommandPool>(*commandPool);
    vkCommandBufferAllocateInfo.commandBufferCount = 1;
    vkCommandBufferAllocateInfo.level = level;
    vkCommandBufferAllocateInfo.pNext = nullptr;

    VK_CHECK_ERROR(CommandBuffer::CommandBuffer, vkAllocateCommandBuffers(static_cast<VkDevice>(*device), &vkCommandBufferAllocateInfo, &this->_vkHandle));
}

CommandBuffer::~CommandBuffer()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkFreeCommandBuffers(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), static_cast<VkCommandPool>(*this->get<std::shared_ptr<CommandPool>>()), 1, &this->_vkHandle);
    }
}

void CommandBuffer::begin(VkCommandBufferUsageFlags flags)
{
    VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        nullptr,
        flags,
        nullptr
    };
    VK_CHECK_ERROR(CommandBuffer::begin, vkBeginCommandBuffer(this->_vkHandle, &vkCommandBufferBeginInfo));
}

void CommandBuffer::begin(VkCommandBufferUsageFlags flags, const InheritanceInfo& inheritanceInfo)
{
    VkCommandBufferInheritanceInfo vkCommandBufferInheritanceInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO,
        nullptr,
        static_cast<VkRenderPass>(inheritanceInfo.renderPass),
        inheritanceInfo.subpass,
        static_cast<VkFramebuffer>(inheritanceInfo.framebuffer),
        static_cast<VkBool32>(inheritanceInfo.occlusionQueryEnable),
        inheritanceInfo.queryFlags,
        inheritanceInfo.pipelineStatistics
    };
    VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        nullptr,
        flags,
        &vkCommandBufferInheritanceInfo
    };

    VK_CHECK_ERROR(CommandBuffer::begin, vkBeginCommandBuffer(this->_vkHandle, &vkCommandBufferBeginInfo));
}

void CommandBuffer::end() const
{
    VK_CHECK_ERROR(CommandBuffer::end, vkEndCommandBuffer(this->_vkHandle));
}

template <>
void CommandBuffer::cmd(const PipelineBarrier& pipelineBarrier)
{
    std::vector<VkMemoryBarrier> vkMemoryBarriers(pipelineBarrier.memoryBarriers.cbegin(), pipelineBarrier.memoryBarriers.cend());
    std::vector<VkBufferMemoryBarrier> vkBufferMemoryBarriers(pipelineBarrier.bufferMemoryBarriers.cbegin(), pipelineBarrier.bufferMemoryBarriers.cend());
    std::vector<VkImageMemoryBarrier> vkImageMemoryBarriers(pipelineBarrier.imageMemoryBarriers.cbegin(), pipelineBarrier.imageMemoryBarriers.cend());

    vkCmdPipelineBarrier(this->_vkHandle, pipelineBarrier.srcStageMask, pipelineBarrier.dstStageMask, pipelineBarrier.dependencyFlags,
        static_cast<uint32_t>(pipelineBarrier.memoryBarriers.size()), vkMemoryBarriers.data(),
        static_cast<uint32_t>(pipelineBarrier.bufferMemoryBarriers.size()), vkBufferMemoryBarriers.data(),
        static_cast<uint32_t>(pipelineBarrier.imageMemoryBarriers.size()), vkImageMemoryBarriers.data());
}

template <>
void CommandBuffer::cmd(const BindPipeline& bindPipeline)
{
    vkCmdBindPipeline(this->_vkHandle, bindPipeline.pipelineBindPoint, static_cast<VkPipeline>(bindPipeline.pipeline));
}

template <>
void CommandBuffer::cmd(const BindVertexBuffer& bindVertexBuffer)
{
    std::vector<VkBuffer> vkBuffers(bindVertexBuffer.buffers.size());

    for (size_t i = 0, end = bindVertexBuffer.buffers.size(); i != end; ++i)
    {
        vkBuffers[i] = static_cast<VkBuffer>(bindVertexBuffer.buffers[i].get());
    }
    std::vector<VkDeviceSize> vkOffsets(bindVertexBuffer.offsets.cbegin(), bindVertexBuffer.offsets.cend());

    vkCmdBindVertexBuffers(this->_vkHandle, bindVertexBuffer.firstBinding, static_cast<uint32_t>(bindVertexBuffer.buffers.size()), vkBuffers.data(), bindVertexBuffer.offsets.data());
}

template <>
void CommandBuffer::cmd(const BindIndexBuffer& bindIndexBuffer)
{
    vkCmdBindIndexBuffer(this->_vkHandle, static_cast<VkBuffer>(bindIndexBuffer.buffer), bindIndexBuffer.offset, bindIndexBuffer.indexType);
}

template <>
void CommandBuffer::cmd(const DrawIndexed& drawIndexed)
{
    vkCmdDrawIndexed(this->_vkHandle, drawIndexed.indexCount, drawIndexed.instanceCount, drawIndexed.firstIndex, drawIndexed.vertexOffset, drawIndexed.firstInstance);
}

template <>
void CommandBuffer::cmd(const ExecCommands& execCommands)
{
    std::vector<VkCommandBuffer> vkCommandBuffers(execCommands.commands.size());

    for (size_t i = 0, end = execCommands.commands.size(); i != end; ++i)
    {
        vkCommandBuffers[i] = static_cast<VkCommandBuffer>(execCommands.commands[i].get());
    }
    vkCmdExecuteCommands(this->_vkHandle, static_cast<uint32_t>(execCommands.commands.size()), vkCommandBuffers.data());
}

std::vector<CommandBuffer> CommandBuffer::allocate(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, uint32_t bufferCount, VkCommandBufferLevel level)
{
    std::vector<VkCommandBuffer> vkCommandBuffers(bufferCount);
    VkCommandBufferAllocateInfo vkCommandBufferAllocateInfo;

    vkCommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    vkCommandBufferAllocateInfo.commandPool = static_cast<VkCommandPool>(*commandPool);
    vkCommandBufferAllocateInfo.commandBufferCount = bufferCount;
    vkCommandBufferAllocateInfo.level = level;
    vkCommandBufferAllocateInfo.pNext = nullptr;

    VK_CHECK_ERROR(CommandBuffer::allocate, vkAllocateCommandBuffers(static_cast<VkDevice>(*device), &vkCommandBufferAllocateInfo, &vkCommandBuffers[0]));

    std::vector<CommandBuffer> commandBuffers;

    for (std::vector<VkCommandBuffer>::iterator i = vkCommandBuffers.begin(),
        end = vkCommandBuffers.end(); i != end; ++i)
    {
        commandBuffers.push_back(CommandBuffer(*i, device, commandPool));
    }
    return commandBuffers;
}
