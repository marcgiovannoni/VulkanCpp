/*
 *  Framebuffer.h
 *
 *  Created by Marc Giovannoni on 20/05/2016
 */

#ifndef     __FRAMEBUFFER_H__
#define     __FRAMEBUFFER_H__

//
// System includes
//

#include <vulkan/vulkan.h>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class Framebuffer : public Internal::VkWrapper<VkFramebuffer, std::shared_ptr<Device>>
    {
    public:
        Framebuffer();
        Framebuffer(const std::shared_ptr<Device>& device, VkFramebufferCreateInfo* vkFramebufferCreateInfo);
        ~Framebuffer();

    public:
        Framebuffer(const Framebuffer&) = delete;
        Framebuffer(Framebuffer&&) = default;
        Framebuffer& operator=(const Framebuffer&) = delete;
        Framebuffer& operator=(Framebuffer&&) = default;
    };
}

#endif  //  __FRAMEBUFFER_H__
