/*
 *  PhysicalDevice.h
 *
 *  Created by Marc Giovannoni on 19/04/2016
 */

#ifndef     __PHYSICALDEVICE_H__
#define     __PHYSICALDEVICE_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <vector>

//
// Project includes
//

namespace VulkanCpp
{
    class PhysicalDevice
    {
    private:
        VkPhysicalDevice _vkPhysicalDevice;

    public:
        PhysicalDevice();
        explicit PhysicalDevice(VkPhysicalDevice physicalDevice);
        ~PhysicalDevice();

    public:
        PhysicalDevice(const PhysicalDevice&) = delete;
        PhysicalDevice& operator=(const PhysicalDevice&) = delete;
        PhysicalDevice(PhysicalDevice&&);
        PhysicalDevice& operator=(PhysicalDevice&&) = delete;

        // VkPhysicalDevice cast
        explicit operator VkPhysicalDevice() const;

        // Physical device
        VkPhysicalDeviceProperties getPhysicalDeviceProperties();
        std::vector<VkQueueFamilyProperties> getQueueFamilyProperties();
    };
}

#endif  //  __PHYSICALDEVICE_H__
#pragma once
