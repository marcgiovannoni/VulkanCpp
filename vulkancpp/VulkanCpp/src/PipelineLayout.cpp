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

PipelineLayout::PipelineLayout() : _device(nullptr), _vkPipelineLayout(nullptr)
{
}

PipelineLayout::PipelineLayout(std::shared_ptr<Device> device, VkPipelineLayoutCreateInfo* vkPipelineLayoutCreateInfo) : _device(device)
{
    VkResult err = vkCreatePipelineLayout(static_cast<VkDevice>(*device), vkPipelineLayoutCreateInfo, nullptr, &this->_vkPipelineLayout);
    VK_LOG_ERROR(PipelineLayout, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

PipelineLayout::~PipelineLayout()
{
    if (this->_device != nullptr && this->_vkPipelineLayout != nullptr)
    {
        vkDestroyPipelineLayout(static_cast<VkDevice>(*this->_device), this->_vkPipelineLayout, nullptr);
    }
}

PipelineLayout::PipelineLayout(PipelineLayout&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkPipelineLayout = std::move(rhs._vkPipelineLayout);

    rhs._device = nullptr;
    rhs._vkPipelineLayout = nullptr;
}

PipelineLayout& PipelineLayout::operator=(PipelineLayout&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkPipelineLayout = std::move(rhs._vkPipelineLayout);

        rhs._device = nullptr;
        rhs._vkPipelineLayout = nullptr;
    }
    return *this;
}

PipelineLayout::operator VkPipelineLayout() const
{
    return this->_vkPipelineLayout;
}
