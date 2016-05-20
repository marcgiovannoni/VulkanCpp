/*
 *  PipelineLayout.cpp
 *  
 *  Created by Marc Giovannoni on 04/05/2016
 */

#include "VulkanCpp/PipelineLayout.h"
#include "VulkanCpp/VkException.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

PipelineLayout::PipelineLayout()
{
    // Empty
}

PipelineLayout::PipelineLayout(const std::shared_ptr<Device>& device, VkPipelineLayoutCreateInfo* vkPipelineLayoutCreateInfo)
    : VkWrapper(device)
{
    VK_CHECK_ERROR(PipelineLayout::PipelineLayout, vkCreatePipelineLayout(static_cast<VkDevice>(*device), vkPipelineLayoutCreateInfo, nullptr, &this->_vkHandle));
}

PipelineLayout::~PipelineLayout()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyPipelineLayout(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}
