/*
 *  Queue.cpp
 *  
 *  Created by Marc Giovannoni on 20/04/2016
 */

#include "VulkanCpp/Queue.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Fence.h"

using namespace VulkanCpp;

Queue::Queue() : _vkQueue(nullptr)
{
}

Queue::Queue(VkQueue vkQueue) : _vkQueue(vkQueue)
{
}

Queue::~Queue()
{
}

Queue::Queue(Queue&& rhs)
{
    this->_vkQueue = std::move(rhs._vkQueue);

    rhs._vkQueue = nullptr;
}

Queue& Queue::operator=(Queue&& rhs)
{
    if (this != &rhs)
    {
        this->_vkQueue = std::move(rhs._vkQueue);
        rhs._vkQueue = nullptr;
    }
    return *this;
}

Queue::operator VkQueue() const
{
    return this->_vkQueue;
}

void Queue::waitIdle()
{
    VkResult err = vkQueueWaitIdle(this->_vkQueue);
    VK_LOG_ERROR(Queue::waitIdle, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

void Queue::submit(VkSubmitInfo* vkSubmitInfo, const Fence& fence)
{
    VkResult err = vkQueueSubmit(this->_vkQueue, 1, vkSubmitInfo, static_cast<VkFence>(fence));
    VK_LOG_ERROR(Queue::submit, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}
