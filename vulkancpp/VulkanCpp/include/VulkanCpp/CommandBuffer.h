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
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class CommandBuffer : public Internal::VkWrapper<VkCommandBuffer, std::shared_ptr<Device>, std::shared_ptr<CommandPool>>
    {
    public:
        CommandBuffer();
        CommandBuffer(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, VkCommandBufferAllocateInfo* vkCommandBuffer);
        ~CommandBuffer();

    protected:
        CommandBuffer(VkCommandBuffer vkCommandBuffer, const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool);

    public:
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer(CommandBuffer&&) = default;
        CommandBuffer& operator=(const CommandBuffer&) = delete;
        CommandBuffer& operator=(CommandBuffer&&) = default;
        
        void begin(VkCommandBufferBeginInfo* vkCommandBufferBeginInfo) const;
        void end() const;

        // Command
        template <class _CommandType>
        void cmd(const _CommandType& commandType);

        static std::vector<CommandBuffer> allocate(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, VkCommandBufferAllocateInfo* vkCommandBufferAllocateInfo);
    };
}

#endif  //  __COMMANDBUFFER_H__
#pragma once
