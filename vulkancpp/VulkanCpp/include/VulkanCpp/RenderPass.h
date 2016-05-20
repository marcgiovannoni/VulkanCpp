/*
 *  RenderPass.h
 *
 *  Created by Marc Giovannoni on 10/05/2016
 */

#ifndef     __RENDERPASS_H__
#define     __RENDERPASS_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <memory>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class RenderPass : public Internal::VkWrapper<VkRenderPass, std::shared_ptr<Device>>
    {
    public:
        RenderPass();
        RenderPass(const std::shared_ptr<Device>& device, VkRenderPassCreateInfo* vkRenderPassCreateInfo);
        ~RenderPass();

    public:
        RenderPass(const RenderPass&) = delete;
        RenderPass(RenderPass&&) = default;
        RenderPass& operator=(const RenderPass&) = delete;
        RenderPass& operator=(RenderPass&&) = default;
    };
}

#endif  //  __RENDERPASS_H__
