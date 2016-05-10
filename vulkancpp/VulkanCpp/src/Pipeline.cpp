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

Pipeline::Pipeline() : _device(nullptr), _vkPipeline(nullptr)
{
}

template<>
Pipeline::Pipeline(std::shared_ptr<Device> device, VkGraphicsPipelineCreateInfo* vkPipelineCreateInfo) : _device(device)
{
    VkResult err = vkCreateGraphicsPipelines(static_cast<VkDevice>(*this->_device), nullptr, 1, vkPipelineCreateInfo, nullptr, &this->_vkPipeline);
    VK_LOG_ERROR(Pipeline::Pipeline, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

template<>
Pipeline::Pipeline(std::shared_ptr<Device> device, VkComputePipelineCreateInfo* vkPipelineCreateInfo) : _device(device)
{
    VkResult err = vkCreateComputePipelines(static_cast<VkDevice>(*this->_device), nullptr, 1, vkPipelineCreateInfo, nullptr, &this->_vkPipeline);
    VK_LOG_ERROR(Pipeline::Pipeline, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

Pipeline::~Pipeline()
{
    if (this->_device != nullptr && this->_vkPipeline != nullptr)
    {
        vkDestroyPipeline(static_cast<VkDevice>(*this->_device), this->_vkPipeline, nullptr);
    }
}

Pipeline::Pipeline(Pipeline&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkPipeline = std::move(rhs._vkPipeline);

    rhs._device = nullptr;
    rhs._vkPipeline = nullptr;
}

Pipeline& Pipeline::operator=(Pipeline&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkPipeline = std::move(rhs._vkPipeline);

        rhs._device = nullptr;
        rhs._vkPipeline = nullptr;
    }
    return *this;
}

Pipeline::operator VkPipeline() const
{
    return this->_vkPipeline;
}
