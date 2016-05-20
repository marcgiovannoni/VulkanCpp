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
#include "RenderPass.h"
#include "Framebuffer.h"

namespace VulkanCpp
{
    class CommandBuffer : public Internal::VkWrapper<VkCommandBuffer, std::shared_ptr<Device>, std::shared_ptr<CommandPool>>
    {
    public:
        CommandBuffer();
        CommandBuffer(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, VkCommandBufferLevel level);
        ~CommandBuffer();

    protected:
        CommandBuffer(VkCommandBuffer vkCommandBuffer, const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool);

    public:
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer(CommandBuffer&&) = default;
        CommandBuffer& operator=(const CommandBuffer&) = delete;
        CommandBuffer& operator=(CommandBuffer&&) = default;

        template <typename... _Command>
        void record(VkCommandBufferUsageFlags flags, _Command&&... commands)
        {
            this->begin(flags);
            bool vars[] = { this->cmd(std::forward<_Command>(commands))... };
            this->end();
        }

        template <typename... _Command>
        void recordWithInheritance(VkCommandBufferUsageFlags flags,
            const RenderPass& renderPass,
            uint32_t subpass,
            const Framebuffer& framebuffer,
            bool occlusionQueryEnable,
            VkQueryControlFlags queryFlags,
            VkQueryPipelineStatisticFlags pipelineStatistics,
            _Command&&... commands)
        {
            this->begin(flags, renderPass, subpass, framebuffer, occlusionQueryEnable, queryFlags, pipelineStatistics);
            bool vars[] = { this->cmd(std::forward<_Command>(commands))... };
            this->end();
        }

    public:
        void begin(VkCommandBufferUsageFlags flags);
        void begin(VkCommandBufferUsageFlags flags,
            const RenderPass& renderPass,
            uint32_t subpass,
            const Framebuffer& framebuffer,
            bool occlusionQueryEnable,
            VkQueryControlFlags queryFlags,
            VkQueryPipelineStatisticFlags pipelineStatistics);
        void end() const;

        // Command
        template <class _CommandType>
        bool cmd(const _CommandType& commandType);

        static std::vector<CommandBuffer> allocate(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, uint32_t bufferCount, VkCommandBufferLevel level);
    };
}

#endif  //  __COMMANDBUFFER_H__
#pragma once
