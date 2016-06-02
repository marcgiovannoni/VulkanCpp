/*
 *  CommandBuffer.hpp
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
#include "Command.h"
#include "Utility/Tuple.hpp"

namespace VulkanCpp
{
    class CommandBuffer : public Internal::VkWrapper<VkCommandBuffer, std::shared_ptr<Device>, std::shared_ptr<CommandPool>>
    {
    public:
        typedef struct InheritanceInfo
        {
            const RenderPass& renderPass;
            uint32_t subpass;
            const Framebuffer& framebuffer;
            bool occlusionQueryEnable;
            VkQueryControlFlags queryFlags;
            VkQueryPipelineStatisticFlags pipelineStatistics;
        } InheritanceInfo;

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

        template <typename... _Commands>
        void record(VkCommandBufferUsageFlags flags, _Commands&&... commands)
        {
            this->begin(flags);
            const int vars[] = { (this->cmd(std::forward<_Commands>(commands)), 0)... };
            this->end();
        }

        template <typename... _Commands>
        void record(VkCommandBufferUsageFlags flags,
            InheritanceInfo inheritanceInfo,
            _Commands&&... commands)
        {
            this->begin(flags, inheritanceInfo);
            const int vars[] = { (this->cmd(std::forward<_Commands>(commands)), 0)... };
            this->end();
        }

    public:
        void begin(VkCommandBufferUsageFlags flags);
        void begin(VkCommandBufferUsageFlags flags, const InheritanceInfo& inheritanceInfo);
        void end() const;

        // Command
        template <typename _CommandType>
        void cmd(const _CommandType& commandType);

        template <typename... _RenderPassCommands>
        void cmd(const Command::RecordRenderPass<_RenderPassCommands...>& renderPass)
        {
            VkRenderPassBeginInfo vkRenderPassBeginInfo = {
                VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                nullptr,
                static_cast<VkRenderPass>(renderPass.renderPass),
                static_cast<VkFramebuffer>(renderPass.framebuffer),
                renderPass.renderArea,
                renderPass.clearValues.size(),
                renderPass.clearValues.data()
            };

           vkCmdBeginRenderPass(this->_vkHandle, &vkRenderPassBeginInfo, renderPass.contents);
           Utility::Tuple::const_for_each(renderPass.commands,
               [&](auto command) { this->cmd(command); });
           vkCmdEndRenderPass(this->_vkHandle);
        }

        static std::vector<CommandBuffer> allocate(const std::shared_ptr<Device>& device, const std::shared_ptr<CommandPool>& commandPool, uint32_t bufferCount, VkCommandBufferLevel level);
    };
}

#endif  //  __COMMANDBUFFER_H__
#pragma once
