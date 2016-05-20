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

Queue::Queue()
{
    // Empty
}

Queue::Queue(VkQueue vkQueue) : VkWrapper(vkQueue)
{
    // Empty
}

Queue::~Queue()
{
    // Empty
}

void Queue::waitIdle()
{
    VK_CHECK_ERROR(Queue::waitIdle, vkQueueWaitIdle(this->_vkHandle));
}

void Queue::submit(VkSubmitInfo* vkSubmitInfo)
{
    VK_CHECK_ERROR(Queue::waitIdle, vkQueueSubmit(this->_vkHandle, 1, vkSubmitInfo, nullptr));
}
