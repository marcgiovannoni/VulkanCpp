/*
 *  CommandPool.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __COMMANDPOOL_H__
#define     __COMMANDPOOL_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <memory>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class CommandPool : public Internal::VkWrapper<VkCommandPool, std::shared_ptr<Device>>
    {
    public:
        CommandPool();
        CommandPool(const std::shared_ptr<Device>& device, uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags);
        ~CommandPool();

    public:
        CommandPool(CommandPool&&) = default;
        CommandPool(const CommandPool&) = delete;
        CommandPool& operator=(CommandPool&&) = default;
        CommandPool& operator=(const CommandPool&) = delete;
    };
}

#endif  //  __COMMANDPOOL_H__
