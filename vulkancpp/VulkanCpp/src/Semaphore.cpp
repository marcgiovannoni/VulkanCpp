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

Semaphore::Semaphore() : _device(nullptr), _vkSemaphore(nullptr)
{
}

Semaphore::Semaphore(std::shared_ptr<Device> device, VkSemaphoreCreateInfo* vkSemaphoreCreateInfo) : _device(device)
{
    VkResult err = vkCreateSemaphore(static_cast<VkDevice>(*device), vkSemaphoreCreateInfo, nullptr, &this->_vkSemaphore);
    VK_LOG_ERROR(Device::createSemaphore, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

Semaphore::~Semaphore()
{
    if (this->_device != nullptr && this->_vkSemaphore != nullptr)
    {
        vkDestroySemaphore(static_cast<VkDevice>(*this->_device), this->_vkSemaphore, nullptr);
    }
}

Semaphore::Semaphore(Semaphore&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkSemaphore = std::move(rhs._vkSemaphore);

    rhs._device = nullptr;
    rhs._vkSemaphore = nullptr;
}

Semaphore& Semaphore::operator=(Semaphore&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkSemaphore = std::move(rhs._vkSemaphore);
        rhs._device = nullptr;
        rhs._vkSemaphore = nullptr;
    }
    return *this;
}

Semaphore::operator VkSemaphore() const
{
    return this->_vkSemaphore;
}