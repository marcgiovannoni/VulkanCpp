/*
 *  Buffer.h
 *
 *  Created by Marc Giovannoni on 18/05/2016
 */

#ifndef     __BUFFER_H__
#define     __BUFFER_H__

//
// System includes
//

#include <memory>
#include <vulkan/vulkan.h>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"
#include "../src/Internal.hpp"
#include "VulkanCpp/Device.h"

namespace VulkanCpp
{
    class Buffer : public Internal::VkWrapper<VkBuffer, std::shared_ptr<Device>>
    {
    public:
        Buffer();
        Buffer(const std::shared_ptr<Device>& device, VkBufferCreateInfo* vkBufferCreateInfo);
        ~Buffer();

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&&) = default;
        Buffer& operator=(const Buffer&) = delete;
        Buffer& operator=(Buffer&&) = default;

        VkMemoryRequirements getMemoryRequirements() const;
        void bindMemory(const Device::Memory& deviceMemory, VkDeviceSize offset);
    };
}

#endif  //  __BUFFER_H__
