/*
 *  Pipeline.h
 *
 *  Created by Marc Giovannoni on 10/05/2016
 */

#ifndef     __PIPELINE_H__
#define     __PIPELINE_H__

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
    class Pipeline : public Internal::VkWrapper<VkPipeline, std::shared_ptr<Device>>
    {
    public:
        Pipeline();
        template <typename _VkPipelineCreateInfo>
        Pipeline(const std::shared_ptr<Device>& vulkanInstance, _VkPipelineCreateInfo* vkPipelineCreateInfo);
        ~Pipeline();

    public:
        Pipeline(const Pipeline&) = delete;
        Pipeline(Pipeline&&) = default;
        Pipeline& operator=(const Pipeline&) = delete;
        Pipeline& operator=(Pipeline&&) = default;
    };
}

#endif  //  __PIPELINE_H__
