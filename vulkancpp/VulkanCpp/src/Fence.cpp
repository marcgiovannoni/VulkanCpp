/*
 *  Fence.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VulkanCpp/Fence.h"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Device.h"
#include "VkDebugLogging.hpp"

using namespace VulkanCpp;

Fence::Fence() : _vkFence(nullptr), _device(nullptr)
{
}

Fence::Fence(std::shared_ptr<Device> device, VkFenceCreateInfo* vkFenceCreateInfo) : _vkFence(nullptr), _device(device)
{
    VkResult err = vkCreateFence(static_cast<VkDevice>(*this->_device), vkFenceCreateInfo, nullptr, &this->_vkFence);
    VK_LOG_ERROR(Fence::Fence, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

Fence::~Fence()
{
    if (this->_vkFence != nullptr)
    {
        vkDestroyFence(static_cast<VkDevice>(*this->_device), static_cast<VkFence>(this->_vkFence), nullptr);
    }
}

Fence::Fence(Fence&& rhs)
{
    this->_vkFence = std::move(rhs._vkFence);
    this->_device = std::move(rhs._device);

    rhs._vkFence = nullptr;
    rhs._device = nullptr;
}

Fence& Fence::operator=(Fence&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkFence = std::move(rhs._vkFence);
        rhs._device = nullptr;
        rhs._vkFence = nullptr;
    }
    return *this;
}

Fence::operator VkFence() const
{
    return this->_vkFence;
}

void Fence::wait(uint64_t timeout) const
{
    VkResult err = vkWaitForFences(static_cast<VkDevice>(*this->_device), 1, &this->_vkFence, true, timeout);

    VK_LOG_ERROR(VulkanRenderer::waitForFences, err);
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

template<>
void Fence::wait(const Device& device, const std::vector<std::reference_wrapper<Fence>>& fences, bool waitAll, uint64_t timeout)
{
    VkFence vkFence = static_cast<VkFence>(fences[0].get());
    VkResult err = vkWaitForFences(static_cast<VkDevice>(device), static_cast<uint32_t>(fences.size()), &vkFence, waitAll, timeout);

    VK_LOG_ERROR(VulkanRenderer::waitForFences, err);
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

template<>
void Fence::wait(const Device& device, const std::vector<std::shared_ptr<Fence>>& fences, bool waitAll, uint64_t timeout)
{
    VkFence vkFence = static_cast<VkFence>(*fences[0]);
    VkResult err = vkWaitForFences(static_cast<VkDevice>(device), static_cast<uint32_t>(fences.size()), &vkFence, waitAll, timeout);

    VK_LOG_ERROR(VulkanRenderer::waitForFences, err);
    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}