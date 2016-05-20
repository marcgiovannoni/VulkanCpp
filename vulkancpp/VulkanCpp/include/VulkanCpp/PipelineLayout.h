/*
 *  PipelineLayout.h
 *
 *  Created by Marc Giovannoni on 04/05/2016
 */

#ifndef     __PIPELINELAYOUT_H__
#define     __PIPELINELAYOUT_H__

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
    class PipelineLayout : public Internal::VkWrapper<VkPipelineLayout, std::shared_ptr<Device>>
    {
    public:
        PipelineLayout();
        PipelineLayout(const std::shared_ptr<Device>& device, VkPipelineLayoutCreateInfo* vkPipelineLayoutCreateInfo);
        ~PipelineLayout();

    public:
        PipelineLayout(const PipelineLayout&) = delete;
        PipelineLayout(PipelineLayout&&) = default;
        PipelineLayout& operator=(const PipelineLayout&) = delete;
        PipelineLayout& operator=(PipelineLayout&&) = default;
    };
}

#endif  //  __PIPELINELAYOUT_H__
