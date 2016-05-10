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

namespace VulkanCpp
{
    class Semaphore
    {
    private:
        std::shared_ptr<Device> _device;
        VkSemaphore _vkSemaphore;

    public:
        Semaphore();
        Semaphore(std::shared_ptr<Device> device, VkSemaphoreCreateInfo* vkSemaphoreCreateInfo);
        ~Semaphore();

    public:
        Semaphore(const Semaphore&) = delete;
        Semaphore& operator=(const Semaphore&) = delete;
        Semaphore(Semaphore&&);
        Semaphore& operator=(Semaphore&&);

        // VkSemaphore cast
        explicit operator VkSemaphore() const;
    };
}

#endif  //  __SEMAPHORE_H__
