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

#include "VulkanCpp_Fwd.h"
#include "SurfaceKHR.h"
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class PhysicalDevice : public Internal::VkWrapper<VkPhysicalDevice>
    {
    public:
        PhysicalDevice();
        explicit PhysicalDevice(VkPhysicalDevice physicalDevice);
        ~PhysicalDevice();

    public:
        PhysicalDevice(const PhysicalDevice&) = delete;
        PhysicalDevice(PhysicalDevice&&) = default;
        PhysicalDevice& operator=(const PhysicalDevice&) = delete;
        PhysicalDevice& operator=(PhysicalDevice&&) = default;

        // Physical device
        VkPhysicalDeviceProperties getPhysicalDeviceProperties() const;
        std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const;

        // SurfaceKHR
        bool getSurfaceSupportKHR(uint32_t graphicsFamilyIndex, const SurfaceKHR& surfaceKHR) const;
        VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR(const SurfaceKHR& surfaceKHR) const;
        std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR(const SurfaceKHR& surfaceKHR) const;
        std::vector<VkPresentModeKHR> getSurfacePresentModesKHR(const SurfaceKHR& surfaceKHR) const;
        VkPhysicalDeviceMemoryProperties getMemoryProperties() const;
    };
}

#endif  //  __PHYSICALDEVICE_H__
#pragma once
