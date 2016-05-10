/*
 *  Device.h
 *
 *  Created by Marc Giovannoni on 20/04/2016
 */

#ifndef     __DEVICE_H__
#define     __DEVICE_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

//
// Project includes
//

#include "Queue.h"
#include "VulkanCpp_Fwd.h"

namespace VulkanCpp
{
    class Device
    {
    private:
        VkDevice _vkDevice;

    public:
        Device(const PhysicalDevice& physicalDevice, VkDeviceCreateInfo* deviceCreateInfo);
        ~Device();

    public:
        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;
        Device(Device&&);
        Device& operator=(Device&&);

        // VkDevice cast
        explicit operator VkDevice() const;

        //Queue
        Queue getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);
    };
}

#endif  //  __DEVICE_H__
#pragma once
