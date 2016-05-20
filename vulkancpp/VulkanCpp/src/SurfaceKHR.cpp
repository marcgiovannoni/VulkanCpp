/*
 *  SurfaceKHR.cpp
 *  
 *  Created by Marc Giovannoni on 03/05/2016
 */

#include "VulkanCpp/VulkanCpp.h"
#include "VulkanCpp/SurfaceKHR.h"
#include "VulkanCpp/VkException.h"
#include "VulkanCpp/Instance.h"
#include "VkDebugLogging.hpp"

using namespace VulkanCpp;

SurfaceKHR::SurfaceKHR()
{
    // Empty
}

#ifdef VK_USE_PLATFORM_ANDROID_KHR
template<>
SurfaceKHR::SurfaceKHR(const std::shared_ptr<Instance>& instance, VkAndroidSurfaceCreateInfoKHR* surfaceCreateInfoKHR) : VkWrapper(instance)
{
    VK_CHECK_ERROR(SurfaceKHR::SurfaceKHR, vkCreateAndroidSurfaceKHR(static_cast<VkInstance>(*this->get<std::shared_ptr<Instance>>()), surfaceCreateInfoKHR, nullptr, &this->_vkHandle));
}
#elif defined VK_USE_PLATFORM_WIN32_KHR
template<>
SurfaceKHR::SurfaceKHR(const std::shared_ptr<Instance>& instance, VkWin32SurfaceCreateInfoKHR* surfaceCreateInfoKHR) : VkWrapper(instance)
{
    VK_CHECK_ERROR(SurfaceKHR::SurfaceKHR, vkCreateWin32SurfaceKHR(static_cast<VkInstance>(*this->get<std::shared_ptr<Instance>>()), surfaceCreateInfoKHR, nullptr, &this->_vkHandle));
}
#endif

SurfaceKHR::~SurfaceKHR()
{
    if (this->_vkHandle != nullptr && this->get<std::shared_ptr<Instance>>() != nullptr)
    {
        vkDestroySurfaceKHR(static_cast<VkInstance>(*this->get<std::shared_ptr<Instance>>()), this->_vkHandle, nullptr);
    }
}
