/*
 *  Fence.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __FENCE_H__
#define     __FENCE_H__

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
    class Fence : Internal::VkWrapper<VkFence, std::shared_ptr<Device>>
    {
    public:
        Fence();
        Fence(const std::shared_ptr<Device>& device, VkFenceCreateInfo* vkFenceCreateInfo);
        ~Fence();

    public:
        Fence(const Fence&) = delete;
        Fence(Fence&&) = default;
        Fence& operator=(const Fence&) = delete;
        Fence& operator=(Fence&&) = default;

        void wait(uint64_t timeout) const;

        template<typename _ContainedType>
        static void wait(const Device& device, const std::vector<_ContainedType>& fences, bool waitAll, uint64_t timeout);
    };
}

#endif  //  __FENCE_H__
