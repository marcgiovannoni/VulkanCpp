/*
 *  Framebuffer.cpp
 *  
 *  Created by Marc Giovannoni on 20/05/2016
 */

#include "VulkanCpp/Framebuffer.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

Framebuffer::Framebuffer()
{
    // Empty
}

Framebuffer::Framebuffer(const std::shared_ptr<Device>& device, VkFramebufferCreateInfo* vkFramebufferCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(Framebuffer::Framebuffer, vkCreateFramebuffer(static_cast<VkDevice>(*device), vkFramebufferCreateInfo, nullptr, &this->_vkHandle));
}

Framebuffer::~Framebuffer()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyFramebuffer(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}

