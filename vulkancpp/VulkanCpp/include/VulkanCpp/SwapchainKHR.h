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
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class SwapchainKHR : public Internal::VkWrapper<VkSwapchainKHR, std::shared_ptr<Device>>
    {
    public:
        SwapchainKHR();
        SwapchainKHR(const std::shared_ptr<Device>& device, VkSwapchainCreateInfoKHR* vkSwapchainCreateInfoKHR);
        ~SwapchainKHR();

    public:
        SwapchainKHR(const SwapchainKHR&) = delete;
        SwapchainKHR(SwapchainKHR&&) = default;
        SwapchainKHR& operator=(const SwapchainKHR&) = delete;
        SwapchainKHR& operator=(SwapchainKHR&&) = default;

        // Image
        std::vector<Image> getImagesKHR();
        uint32_t acquireNextImageKHR(const Semaphore& semaphore);
    };
}

#endif  //  __SwapchainKHR_H__
#pragma once
