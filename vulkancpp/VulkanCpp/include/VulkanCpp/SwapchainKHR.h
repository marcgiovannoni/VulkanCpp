/*
 *  SwapchainKHR.h
 *
 *  Created by Marc Giovannoni on 22/04/2016
 */

#ifndef     __SwapchainKHR_H__
#define     __SwapchainKHR_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"

namespace VulkanCpp
{
    class SwapchainKHR
    {
    private:
        std::shared_ptr<Device> _device;
        VkSwapchainKHR _vkSwapchainKHR;

    public:
        SwapchainKHR();
        SwapchainKHR(std::shared_ptr<Device> device, VkSwapchainCreateInfoKHR* vkSwapchainCreateInfoKHR);
        ~SwapchainKHR();

    public:
        SwapchainKHR(const SwapchainKHR&) = delete;
        SwapchainKHR& operator=(const SwapchainKHR&) = delete;
        SwapchainKHR(SwapchainKHR&&);
        SwapchainKHR& operator=(SwapchainKHR&&);

        // VkSwapchainKHR cast
        explicit operator VkSwapchainKHR() const;

        // Image
        std::vector<Image> getImagesKHR();
        uint32_t acquireNextImageKHR(const Semaphore& semaphore);
    };
}

#endif  //  __SwapchainKHR_H__
#pragma once
