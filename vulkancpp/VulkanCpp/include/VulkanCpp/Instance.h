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

//
// Project includes
//

#include "PhysicalDevice.h"

namespace VulkanCpp
{
    class Instance
    {
    private:
        VkInstance _vkInstance;

    public:
        Instance(VkInstanceCreateInfo* instanceCreateInfo);
        ~Instance();

    public:
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;
        Instance(Instance&&);
        Instance& operator=(Instance&&);

        // VkInstance cast
        explicit operator VkInstance() const;

    public:
        // Physical devices
        std::vector<PhysicalDevice> enumeratePhysicalDevices() const;
    };
}

#endif  //  __INSTANCE_H__
#pragma once
