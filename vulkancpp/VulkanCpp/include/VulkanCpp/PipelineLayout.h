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

namespace VulkanCpp
{
    class PipelineLayout
    {
    private:
        std::shared_ptr<Device> _device;
        VkPipelineLayout _vkPipelineLayout;

    public:
        PipelineLayout();
        PipelineLayout(std::shared_ptr<Device> device, VkPipelineLayoutCreateInfo* vkPipelineLayoutCreateInfo);
        ~PipelineLayout();

    public:
        PipelineLayout(PipelineLayout&&);
        PipelineLayout(const PipelineLayout&) = delete;
        PipelineLayout& operator=(PipelineLayout&&);
        PipelineLayout& operator=(const PipelineLayout&) = delete;

        explicit operator VkPipelineLayout() const;
    };
}

#endif  //  __PIPELINELAYOUT_H__
