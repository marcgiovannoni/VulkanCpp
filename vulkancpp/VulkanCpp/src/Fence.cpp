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

Fence::Fence()
{
    // Empty
}

Fence::Fence(const std::shared_ptr<Device>& device, VkFenceCreateInfo* vkFenceCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(Fence::Fence, vkCreateFence(static_cast<VkDevice>(*device), vkFenceCreateInfo, nullptr, &this->_vkHandle));
}

Fence::~Fence()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyFence(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), static_cast<VkFence>(this->_vkHandle), nullptr);
    }
}

void Fence::wait(uint64_t timeout) const
{
    VK_CHECK_ERROR(Fence::wait, vkWaitForFences(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), 1, &this->_vkHandle, true, timeout));
}

template<>
void Fence::wait(const Device& device, const std::vector<std::reference_wrapper<Fence>>& fences, bool waitAll, uint64_t timeout)
{
    VkFence vkFence = static_cast<VkFence>(fences[0].get());

    VK_CHECK_ERROR(Fence::wait, vkWaitForFences(static_cast<VkDevice>(device), static_cast<uint32_t>(fences.size()), &vkFence, waitAll, timeout));
}

template<>
void Fence::wait(const Device& device, const std::vector<std::shared_ptr<Fence>>& fences, bool waitAll, uint64_t timeout)
{
    VkFence vkFence = static_cast<VkFence>(*fences[0]);
    
    VK_CHECK_ERROR(Fence::wait, vkWaitForFences(static_cast<VkDevice>(device), static_cast<uint32_t>(fences.size()), &vkFence, waitAll, timeout));
}