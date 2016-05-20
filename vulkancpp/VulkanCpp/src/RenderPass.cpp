/*
 *  RenderPass.cpp
 *  
 *  Created by Marc Giovannoni on 10/05/2016
 */

#include "VulkanCpp/RenderPass.h"
#include "VulkanCpp/VkException.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

RenderPass::RenderPass()
{
    // Empty
}

RenderPass::RenderPass(const std::shared_ptr<Device>& device, VkRenderPassCreateInfo* vkRenderPassCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(RenderPass::RenderPass, vkCreateRenderPass(static_cast<VkDevice>(*device), vkRenderPassCreateInfo, nullptr, &this->_vkHandle));
}

RenderPass::~RenderPass()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyRenderPass(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}
