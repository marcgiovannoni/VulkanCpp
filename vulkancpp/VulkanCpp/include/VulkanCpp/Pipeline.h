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

namespace VulkanCpp
{
    class Pipeline
    {
    private:
        std::shared_ptr<Device> _device;
        VkPipeline _vkPipeline;

    public:
        Pipeline();
        template <typename _VkPipelineCreateInfo>
        Pipeline(std::shared_ptr<Device> vulkanInstance, _VkPipelineCreateInfo* vkPipelineCreateInfo);
        ~Pipeline();

    public:
        Pipeline(Pipeline&&);
        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(Pipeline&&);
        Pipeline& operator=(const Pipeline&) = delete;

        // VkPipeline cast
        explicit operator VkPipeline() const;
    };
}

#endif  //  __PIPELINE_H__
