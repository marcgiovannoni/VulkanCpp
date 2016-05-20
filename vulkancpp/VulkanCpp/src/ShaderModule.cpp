/*
 *  ShaderModule.cpp
 *  
 *  Created by Marc Giovannoni on 04/05/2016
 */

#include <fstream>
#include "VulkanCpp/ShaderModule.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Device.h"

using namespace VulkanCpp;

ShaderModule::ShaderModule()
{
    // Empty
}

ShaderModule::ShaderModule(const std::shared_ptr<Device>& device, VkShaderModuleCreateInfo* vkShaderModuleCreateInfo) : VkWrapper(device)
{
    VK_CHECK_ERROR(ShaderModule::ShaderModule, vkCreateShaderModule(static_cast<VkDevice>(*device), vkShaderModuleCreateInfo, nullptr, &this->_vkHandle));
}

ShaderModule::~ShaderModule()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Device>>() != nullptr)
    {
        vkDestroyShaderModule(static_cast<VkDevice>(*this->get<std::shared_ptr<Device>>()), this->_vkHandle, nullptr);
    }
}

ShaderModule ShaderModule::fromSPVFile(std::shared_ptr<Device> device, const char* filename)
{
    // TODO: Use Primitives File class
    std::ifstream file(filename, std::ios::binary);

    if (file.fail())
    {
        LOG_ERROR(ShaderModule::fromSPVFile, "Could not open %s file.", filename);
        // TODO: Use File Exception
    }

    std::streampos begin;
    std::streampos end;

    begin = file.tellg();
    file.seekg(0, std::ios::end);
    end = file.tellg();

    std::vector<char> code(static_cast<size_t>(end - begin));

    file.seekg(0, std::ios::beg);
    file.read(&code[0], end - begin);
    file.close();

    VkShaderModuleCreateInfo vkShaderModuleCreateInfo = {
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,    // VkStructureType                sType
        nullptr,                                        // const void                    *pNext
        0,                                              // VkShaderModuleCreateFlags      flags
        code.size(),                                    // size_t                         codeSize
        reinterpret_cast<const uint32_t*>(&code[0])     // const uint32_t                *pCode
    };

    return ShaderModule(device, &vkShaderModuleCreateInfo);
}
