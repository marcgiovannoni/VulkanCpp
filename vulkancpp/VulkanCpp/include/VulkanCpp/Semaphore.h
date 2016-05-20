/*
 *  Semaphore.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __SEMAPHORE_H__
#define     __SEMAPHORE_H__

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
    class Semaphore : public Internal::VkWrapper<VkSemaphore, std::shared_ptr<Device>>
    {
    public:
        Semaphore();
        Semaphore(const std::shared_ptr<Device>& device, VkSemaphoreCreateInfo* vkSemaphoreCreateInfo);
        ~Semaphore();

    public:
        Semaphore(const Semaphore&) = delete;
        Semaphore(Semaphore&&) = default;
        Semaphore& operator=(const Semaphore&) = delete;
        Semaphore& operator=(Semaphore&&) = default;
    };
}

#endif  //  __SEMAPHORE_H__
