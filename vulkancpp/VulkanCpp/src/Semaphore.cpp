/*
 *  Semaphore.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VulkanCpp/Semaphore.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

Semaphore::Semaphore()
{
    // Empty
}

Semaphore::Semaphore(const std::shared_ptr<Device>& device, VkSemaphoreCreateInfo* vkSemaphoreCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(Semaphore::Semaphore, vkCreateSemaphore(static_cast<VkDevice>(*device), vkSemaphoreCreateInfo, nullptr, &this->_vkHandle));
}

Semaphore::~Semaphore()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroySemaphore(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}
