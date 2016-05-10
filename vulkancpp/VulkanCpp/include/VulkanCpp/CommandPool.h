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

namespace VulkanCpp
{
    class CommandPool
    {
    private:
        VkCommandPool _vkCommandPool;
        std::shared_ptr<Device> _device;

    public:
        CommandPool(std::shared_ptr<Device> device, VkCommandPoolCreateInfo* vkCommandPoolCreateInfo);
        ~CommandPool();

    public:
        CommandPool(CommandPool&&);
        CommandPool(const CommandPool&) = delete;
        CommandPool& operator=(CommandPool&&);
        CommandPool& operator=(const CommandPool&) = delete;

        // VkCommandPool cast
        explicit operator VkCommandPool() const;
    };
}

#endif  //  __COMMANDPOOL_H__
