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

namespace VulkanCpp
{
    class ShaderModule
    {
    private:
        std::shared_ptr<Device> _device;
        VkShaderModule _vkShaderModule;

    public:
        ShaderModule();
        ShaderModule(std::shared_ptr<Device> device, VkShaderModuleCreateInfo* vkShaderModuleCreateInfo);
        ~ShaderModule();

    public:
        ShaderModule(ShaderModule&&);
        ShaderModule(const ShaderModule&) = delete;
        ShaderModule& operator=(ShaderModule&&);
        ShaderModule& operator=(const ShaderModule&) = delete;

        // VkSemaphore cast
        explicit operator VkShaderModule() const;

        static ShaderModule fromSPVFile(std::shared_ptr<Device> device, const char* filename);
    };
}

#endif  //  __SHADERMODULE_H__
