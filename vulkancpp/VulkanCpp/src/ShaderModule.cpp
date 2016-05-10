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

ShaderModule::ShaderModule() : _device(nullptr), _vkShaderModule(nullptr)
{
}

ShaderModule::ShaderModule(std::shared_ptr<Device> device, VkShaderModuleCreateInfo* vkShaderModuleCreateInfo) : _device(device)
{
    VkResult err = vkCreateShaderModule(static_cast<VkDevice>(*device), vkShaderModuleCreateInfo, nullptr, &this->_vkShaderModule);
    VK_LOG_ERROR(ShaderModule::ShaderModule, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}

ShaderModule::~ShaderModule()
{
    if (this->_device != nullptr && this->_vkShaderModule != nullptr)
    {
        vkDestroyShaderModule(static_cast<VkDevice>(*this->_device), this->_vkShaderModule, nullptr);
    }
}

ShaderModule::ShaderModule(ShaderModule&& rhs)
{
    this->_device = std::move(rhs._device);
    this->_vkShaderModule = std::move(rhs._vkShaderModule);

    rhs._device = nullptr;
    rhs._vkShaderModule = nullptr;
}

ShaderModule& ShaderModule::operator=(ShaderModule&& rhs)
{
    if (this != &rhs)
    {
        this->_device = std::move(rhs._device);
        this->_vkShaderModule = std::move(rhs._vkShaderModule);

        rhs._device = nullptr;
        rhs._vkShaderModule = nullptr;
    }
    return *this;
}

ShaderModule::operator VkShaderModule() const
{
    return this->_vkShaderModule;
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
