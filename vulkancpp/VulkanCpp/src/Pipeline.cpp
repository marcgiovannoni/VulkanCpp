/*
 *  Pipeline.cpp
 *  
 *  Created by Marc Giovannoni on 10/05/2016
 */

#include "VulkanCpp/Pipeline.h"
#include "VulkanCpp/VkException.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

Pipeline::Pipeline()
{
}

template<>
Pipeline::Pipeline(const std::shared_ptr<Device>& device, VkGraphicsPipelineCreateInfo* vkPipelineCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(Pipeline::Pipeline, vkCreateGraphicsPipelines(static_cast<VkDevice>(*device), nullptr, 1, vkPipelineCreateInfo, nullptr, &this->_vkHandle));
}

template<>
Pipeline::Pipeline(const std::shared_ptr<Device>& device, VkComputePipelineCreateInfo* vkPipelineCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(Pipeline::Pipeline, vkCreateComputePipelines(static_cast<VkDevice>(*device), nullptr, 1, vkPipelineCreateInfo, nullptr, &this->_vkHandle));
}

Pipeline::~Pipeline()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyPipeline(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}
