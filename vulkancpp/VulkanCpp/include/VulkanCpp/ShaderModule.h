/*
 *  ShaderModule.h
 *
 *  Created by Marc Giovannoni on 04/05/2016
 */

#ifndef     __SHADERMODULE_H__
#define     __SHADERMODULE_H__

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
    class ShaderModule : public Internal::VkWrapper<VkShaderModule, std::shared_ptr<Device>>
    {
    public:
        ShaderModule();
        ShaderModule(const std::shared_ptr<Device>& device, VkShaderModuleCreateInfo* vkShaderModuleCreateInfo);
        ~ShaderModule();

    public:
        ShaderModule(const ShaderModule&) = delete;
        ShaderModule(ShaderModule&&) = default;
        ShaderModule& operator=(const ShaderModule&) = delete;
        ShaderModule& operator=(ShaderModule&&) = default;

        static ShaderModule fromSPVFile(std::shared_ptr<Device> device, const char* filename);
    };
}

#endif  //  __SHADERMODULE_H__
