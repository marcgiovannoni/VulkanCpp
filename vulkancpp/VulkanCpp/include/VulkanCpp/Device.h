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
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    typedef struct DeviceQueueCreateInfo
    {
        uint32_t  queueFamilyIndex;
        std::vector<float> queuePriorities;

        explicit operator VkDeviceQueueCreateInfo() const
        {
            return VkDeviceQueueCreateInfo{
                VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                nullptr,
                0,
                queueFamilyIndex,
                static_cast<uint32_t>(queuePriorities.size()),
                queuePriorities.data()
            };
        }
    } DeviceQueueCreateInfo;

    class Device : public Internal::VkWrapper<VkDevice>, public std::enable_shared_from_this<Device>
    {
    public:
        class Memory : public Internal::VkWrapper<VkDeviceMemory, std::shared_ptr<Device>>
        {
        public:
            Memory();
            Memory(VkDeviceMemory vkDeviceMemory, const std::shared_ptr<Device>& device);
            ~Memory();

        public:
            Memory(const Memory&) = delete;
            Memory(Memory&&) = default;
            Memory& operator=(const Memory&) = delete;
            Memory& operator=(Memory&&) = default;

            void map(VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** data);
            void unmap();
        };

    public:
        Device();
        Device(const PhysicalDevice& physicalDevice,
            const std::vector<DeviceQueueCreateInfo>& deviceQueueCreateInfo,
            const std::vector<const char*>& layers,
            const std::vector<const char*>& extensions);
        ~Device();

    public:
        Device(const Device&) = delete;
        Device(Device&&) = default;
        Device& operator=(const Device&) = delete;
        Device& operator=(Device&&) = default;

        //Queue
        Queue getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);
        Memory allocateMemory(VkDeviceSize size, uint32_t memoryTypeIndex);
    };
}

#endif  //  __DEVICE_H__
#pragma once
