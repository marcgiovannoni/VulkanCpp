/*
 *  Instance.h
 *
 *  Created by Marc Giovannoni on 19/04/2016
 */

#ifndef     __INSTANCE_H__
#define     __INSTANCE_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <memory>
#include <set>

//
// Project includes
//

#include "PhysicalDevice.h"
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class Instance : public Internal::VkWrapper<VkInstance>
    {
    public:
        explicit Instance(VkInstanceCreateInfo* instanceCreateInfo);
        Instance(const std::vector<const char *>& layers, const std::vector<const char *>& extensions);
        ~Instance();

    public:
        Instance(const Instance&) = delete;
        Instance(Instance&&) = default;
        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&&) = default;

    public:
        // Physical devices
        std::vector<PhysicalDevice> enumeratePhysicalDevices() const;
    };
}

#endif  //  __INSTANCE_H__
#pragma once
