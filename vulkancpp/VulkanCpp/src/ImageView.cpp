/*
 *  ImageView.cpp
 *  
 *  Created by Marc Giovannoni on 22/04/2016
 */

#include "VulkanCpp/ImageView.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

ImageView::ImageView()
{
    // Empty
}

ImageView::ImageView(const std::shared_ptr<Device>& device, VkImageViewCreateInfo* vkImageViewCreateInfo)
    : VkWrapper(device)
{
    VK_CHECK_ERROR(ImageView::ImageView, vkCreateImageView(static_cast<VkDevice>(*device), vkImageViewCreateInfo, nullptr, &this->_vkHandle));
}

ImageView::~ImageView()
{
    if (this->get<std::shared_ptr<Device>>() != nullptr && this->_vkHandle != nullptr)
    {
        vkDestroyImageView(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}
