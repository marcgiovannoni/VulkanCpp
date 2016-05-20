/*
 *  SwapchainKHR.cpp
 *  
 *  Created by Marc Giovannoni on 22/04/2016
 */

#include "VulkanCpp/SwapchainKHR.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Semaphore.h"
#include "VulkanCpp/Image.h"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

SwapchainKHR::SwapchainKHR()
{
    // Empty
}

SwapchainKHR::SwapchainKHR(const std::shared_ptr<Device>& device, VkSwapchainCreateInfoKHR* vkSwapchainCreateInfoKHR) : VkWrapper(device)
{
    VK_CHECK_ERROR(SwapchainKHR::SwapchainKHR, vkCreateSwapchainKHR(static_cast<VkDevice>(*device), vkSwapchainCreateInfoKHR, nullptr, &this->_vkHandle));
}

SwapchainKHR::~SwapchainKHR()
{
    if (this->get<std::shared_ptr<Device>>() != nullptr && this->_vkHandle != nullptr)
    {
        vkDestroySwapchainKHR(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}

std::vector<Image> SwapchainKHR::getImagesKHR()
{
    uint32_t imageCount = 0;
    std::vector<Image> images;

    VK_CHECK_ERROR(SwapchainKHR::getImagesKHR, vkGetSwapchainImagesKHR(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, &imageCount, nullptr));

    if (imageCount > 0)
    {
        std::vector<VkImage> vkImages(imageCount);

        VK_CHECK_ERROR(SwapchainKHR::getImagesKHR, vkGetSwapchainImagesKHR(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, &imageCount, &vkImages[0]));

        for (std::vector<VkImage>::iterator i = vkImages.begin(),
            end = vkImages.end(); i != end; ++i)
        {
            images.push_back(Image(*i));
        }
    }
    return images;
}

uint32_t SwapchainKHR::acquireNextImageKHR(const Semaphore& semaphore)
{
    uint32_t currentBuffer;

    VK_CHECK_ERROR(SwapchainKHR::acquireNextImageKHR, vkAcquireNextImageKHR(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, UINT64_MAX, static_cast<VkSemaphore>(semaphore), nullptr, &currentBuffer));

    return currentBuffer;
}

