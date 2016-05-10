/*
 *  Queue.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __QUEUE_H__
#define     __QUEUE_H__

//
// System includes
//

#include <vulkan/vulkan.h>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"

namespace VulkanCpp
{
    class Queue
    {
    private:
        VkQueue _vkQueue;

        // TODO: Do not expose publicly
    public:
        Queue();
        explicit Queue(VkQueue vkQueue);
        ~Queue();

    public:
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;
        Queue(Queue&&);
        Queue& operator=(Queue&&);

        // VkQueue cast
        explicit operator VkQueue() const;

        void waitIdle();
        void submit(VkSubmitInfo* vkSubmitInfo, const Fence& fence);
    };
}

#endif  //  __QUEUE_H__
