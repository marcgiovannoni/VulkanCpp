/*
 *  CommandBuffer.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __COMMANDBUFFER_H__
#define     __COMMANDBUFFER_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"

namespace VulkanCpp
{
    class CommandBuffer
    {
    private:
        std::shared_ptr<Device> _device;
        std::shared_ptr<CommandPool> _commandPool;
        VkCommandBuffer _vkCommandBuffer;

    public:
        CommandBuffer();
        CommandBuffer(std::shared_ptr<Device> device, std::shared_ptr<CommandPool> commandPool, VkCommandBufferAllocateInfo* vkCommandBuffer);
        ~CommandBuffer();

    protected:
        explicit CommandBuffer(std::shared_ptr<Device> device, std::shared_ptr<CommandPool> commandPool, VkCommandBuffer vkCommandBuffer);

    public:
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer(CommandBuffer&&);
        CommandBuffer& operator=(const CommandBuffer&) = delete;
        CommandBuffer& operator=(CommandBuffer&&);

        // VkDevice cast
        explicit operator VkCommandBuffer() const;
        
        void begin(VkCommandBufferBeginInfo* vkCommandBufferBeginInfo) const;
        void end() const;

        static std::vector<CommandBuffer> allocate(std::shared_ptr<Device> device, std::shared_ptr<CommandPool> commandPool, VkCommandBufferAllocateInfo* vkCommandBufferAllocateInfo);
        static void free(std::vector<CommandBuffer>& vector);
    };
}

#endif  //  __COMMANDBUFFER_H__
#pragma once
