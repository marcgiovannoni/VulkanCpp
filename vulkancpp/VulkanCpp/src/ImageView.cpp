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

ImageView::ImageView() : _device(nullptr), _vkImageView(nullptr)
{
}

ImageView::ImageView(std::shared_ptr<Device> device, VkImageViewCreateInfo* vkImageViewCreateInfo) : _device(device)
{
    VkResult err = vkCreateImageView(static_cast<VkDevice>(*device), vkImageViewCreateInfo, nullptr, &this->_vkImageView);
    VK_LOG_ERROR(ImageView, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

ImageView::~ImageView()
{
    if (this->_device != nullptr && this->_vkImageView != nullptr)
    {
        vkDestroyImageView(static_cast<VkDevice>(*this->_device), this->_vkImageView, nullptr);
    }
}

ImageView::ImageView(ImageView&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkImageView = std::move(rhs._vkImageView);

    rhs._device = nullptr;
    rhs._vkImageView = nullptr;
}

ImageView& ImageView::operator=(ImageView&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkImageView = std::move(rhs._vkImageView);

        rhs._device = nullptr;
        rhs._vkImageView = nullptr;
    }
    return *this;
}

ImageView::operator VkImageView() const
{
    return this->_vkImageView;
}
