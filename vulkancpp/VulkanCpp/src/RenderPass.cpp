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

RenderPass::RenderPass() : _device(nullptr), _vkRenderPass(nullptr)
{
}

RenderPass::RenderPass(std::shared_ptr<Device> device, VkRenderPassCreateInfo* vkRenderPassCreateInfo) : _device(device)
{
    VkResult err = vkCreateRenderPass(static_cast<VkDevice>(*this->_device), vkRenderPassCreateInfo, nullptr, &this->_vkRenderPass);
    VK_LOG_ERROR(RenderPass::RenderPass, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

RenderPass::~RenderPass()
{
}

RenderPass::RenderPass(RenderPass&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkRenderPass = std::move(rhs._vkRenderPass);

    rhs._device = nullptr;
    rhs._vkRenderPass = nullptr;
}

RenderPass& RenderPass::operator=(RenderPass&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkRenderPass = std::move(rhs._vkRenderPass);

        rhs._device = nullptr;
        rhs._vkRenderPass = nullptr;
    }
    return *this;
}

RenderPass::operator VkRenderPass() const
{
    return this->_vkRenderPass;
}
