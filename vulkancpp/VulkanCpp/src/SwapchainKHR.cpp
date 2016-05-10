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

SwapchainKHR::SwapchainKHR() : _device(nullptr), _vkSwapchainKHR(nullptr)
{
}

SwapchainKHR::SwapchainKHR(std::shared_ptr<Device> device, VkSwapchainCreateInfoKHR* vkSwapchainCreateInfoKHR) : _device(device)
{
    VkResult err = vkCreateSwapchainKHR(static_cast<VkDevice>(*device), vkSwapchainCreateInfoKHR, nullptr, &this->_vkSwapchainKHR);
    VK_LOG_ERROR(SwapchainKHR, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

SwapchainKHR::~SwapchainKHR()
{
    if (this->_device != nullptr && this->_vkSwapchainKHR != nullptr)
    {
        vkDestroySwapchainKHR(static_cast<VkDevice>(*this->_device), this->_vkSwapchainKHR, nullptr);
    }
}

SwapchainKHR::SwapchainKHR(SwapchainKHR&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkSwapchainKHR = std::move(rhs._vkSwapchainKHR);

    rhs._device = nullptr;
    rhs._vkSwapchainKHR = nullptr;
}

SwapchainKHR& SwapchainKHR::operator=(SwapchainKHR&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkSwapchainKHR = std::move(rhs._vkSwapchainKHR);
        rhs._device = nullptr;
        rhs._vkSwapchainKHR = nullptr;
    }
    return *this;
}

SwapchainKHR::operator VkSwapchainKHR() const
{
    return this->_vkSwapchainKHR;
}

std::vector<Image> SwapchainKHR::getImagesKHR()
{
    uint32_t imageCount = 0;
    std::vector<Image> images;

    VkResult err = vkGetSwapchainImagesKHR(static_cast<VkDevice>(*this->_device), this->_vkSwapchainKHR, &imageCount, nullptr);
    VK_LOG_ERROR(Device::getSwapchainImagesKHR, err);
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }

    if (imageCount > 0)
    {
        std::vector<VkImage> vkImages(imageCount);

        err = vkGetSwapchainImagesKHR(static_cast<VkDevice>(*this->_device), this->_vkSwapchainKHR, &imageCount, &vkImages[0]);
        VK_LOG_ERROR(Device::getSwapchainImagesKHR, err);

        if (err != VK_SUCCESS)
        {
            throw new VkException(err);
        }
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

    VkResult err = vkAcquireNextImageKHR(static_cast<VkDevice>(*this->_device), this->_vkSwapchainKHR, UINT64_MAX, static_cast<VkSemaphore>(semaphore), nullptr, &currentBuffer);
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
    return currentBuffer;
}

