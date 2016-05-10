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

namespace VulkanCpp
{
    class Fence
    {
    private:
        VkFence _vkFence;
        std::shared_ptr<Device> _device;

    public:
        Fence();
        Fence(std::shared_ptr<Device> device, VkFenceCreateInfo* vkFenceCreateInfo);
        ~Fence();

    public:
        Fence(const Fence&) = delete;
        Fence& operator=(const Fence&) = delete;
        Fence(Fence&&);
        Fence& operator=(Fence&&);

        // VkFence cast
        explicit operator VkFence() const;

        void wait(uint64_t timeout) const;

        template<typename _ContainedType>
        static void wait(const Device& device, const std::vector<_ContainedType>& fences, bool waitAll, uint64_t timeout);
    };
}

#endif  //  __FENCE_H__
