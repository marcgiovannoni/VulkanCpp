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

namespace VulkanCpp
{
    class RenderPass
    {
    private:
        std::shared_ptr<Device> _device;
        VkRenderPass _vkRenderPass;

    public:
        RenderPass();
        RenderPass(std::shared_ptr<Device> device, VkRenderPassCreateInfo* vkRenderPassCreateInfo);
        ~RenderPass();

    public:
        RenderPass(RenderPass&&);
        RenderPass(const RenderPass&) = delete;
        RenderPass& operator=(RenderPass&&);
        RenderPass& operator=(const RenderPass&) = delete;

        // VkRenderPass cast
        explicit operator VkRenderPass() const;
    };
}

#endif  //  __RENDERPASS_H__
