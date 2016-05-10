/*
 *  SurfaceKHR.cpp
 *  
 *  Created by Marc Giovannoni on 03/05/2016
 */

#include "VulkanCpp/SurfaceKHR.h"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Instance.h"

using namespace VulkanCpp;

SurfaceKHR::SurfaceKHR() : _instance(nullptr), _vkSurfaceKHR(nullptr)
{
}

#ifdef VK_USE_PLATFORM_ANDROID_KHR
template<>
SurfaceKHR::SurfaceKHR(std::shared_ptr<VulkanInstance> vulkanInstance, VkAndroidSurfaceCreateInfoKHR* surfaceCreateInfoKHR) : _vulkanInstance(vulkanInstance)
{
    VkResult err = vkCreateAndroidSurfaceKHR(static_cast<VkInstance>(*this->_instance), surfaceCreateInfoKHR, nullptr, &this->_vkSurfaceKHR);
    VK_LOG_ERROR(SurfaceKHR::SurfaceKHR, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}
#elif defined VK_USE_PLATFORM_WIN32_KHR
template<>
SurfaceKHR::SurfaceKHR(std::shared_ptr<VulkanInstance> vulkanInstance, VkWin32SurfaceCreateInfoKHR* surfaceCreateInfoKHR) : _vulkanInstance(vulkanInstance)
{
    VkResult err = vkCreateWin32SurfaceKHR(static_cast<VkInstance>(*this->_instance), surfaceCreateInfoKHR, nullptr, &this->_vkSurfaceKHR);
    VK_LOG_ERROR(SurfaceKHR::SurfaceKHR, err);

    if (err != VK_SUCCESS)
    {
        throw new VkException(err);
    }
}
#endif

SurfaceKHR::~SurfaceKHR()
{
    if (this->_vkSurfaceKHR != nullptr)
    {
        vkDestroySurfaceKHR(static_cast<VkInstance>(*this->_instance), this->_vkSurfaceKHR, nullptr);
    }
}

SurfaceKHR::SurfaceKHR(SurfaceKHR&& rhs)
{
    this->_instance = std::move(rhs._instance);
    this->_vkSurfaceKHR = std::move(rhs._vkSurfaceKHR);

    rhs._instance = nullptr;
    rhs._vkSurfaceKHR = nullptr;
}

SurfaceKHR& SurfaceKHR::operator=(SurfaceKHR&& rhs)
{
    if (this != &rhs)
    {
        this->_instance = std::move(rhs._instance);
        this->_vkSurfaceKHR = std::move(rhs._vkSurfaceKHR);
        rhs._instance = nullptr;
        rhs._vkSurfaceKHR = nullptr;
    }
    return *this;
}

SurfaceKHR::operator VkSurfaceKHR() const
{
    return this->_vkSurfaceKHR;
}
