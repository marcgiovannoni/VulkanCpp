/*
 *  PhysicalDevice.cpp
 *  
 *  Created by Marc Giovannoni on 19/04/2016
 */

#include "VulkanCpp/PhysicalDevice.h"
#include "VulkanCpp/SurfaceKHR.h"
#include "VkDebugLogging.hpp"
#include "VulkanCpp/VkException.h"

using namespace VulkanCpp;

PhysicalDevice::PhysicalDevice()
{
    // Empty
}

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) : VkWrapper(physicalDevice)
{
    // Empty
}

PhysicalDevice::~PhysicalDevice()
{
    // Empty
}

VkPhysicalDeviceProperties PhysicalDevice::getPhysicalDeviceProperties() const
{
    VkPhysicalDeviceProperties properties;

    vkGetPhysicalDeviceProperties(this->_vkHandle, &properties);

    return properties;
}

std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties() const
{
    std::vector<VkQueueFamilyProperties> queueFamiliysProperties;
    uint32_t queueFamilyCnt = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(this->_vkHandle, &queueFamilyCnt, nullptr);

    if (!queueFamilyCnt)
    {
        return queueFamiliysProperties;
    }

    queueFamiliysProperties.resize(queueFamilyCnt);

    vkGetPhysicalDeviceQueueFamilyProperties(this->_vkHandle, &queueFamilyCnt, &queueFamiliysProperties[0]);

    return queueFamiliysProperties;
}

bool PhysicalDevice::getSurfaceSupportKHR(uint32_t graphicsFamilyIndex, const SurfaceKHR& surfaceKHR) const
{
    VkBool32 supported = false;

    VK_CHECK_ERROR(PhysicalDevice::getSurfaceSupportKHR, vkGetPhysicalDeviceSurfaceSupportKHR(this->_vkHandle, graphicsFamilyIndex, static_cast<VkSurfaceKHR>(surfaceKHR), &supported));
    return supported == VK_TRUE;
}

VkSurfaceCapabilitiesKHR PhysicalDevice::getSurfaceCapabilitiesKHR(const SurfaceKHR& surfaceKHR) const
{
    VkSurfaceCapabilitiesKHR surfaceCapabilitiesKHR;

    VK_CHECK_ERROR(PhysicalDevice::getSurfaceCapabilitiesKHR, vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->_vkHandle, static_cast<VkSurfaceKHR>(surfaceKHR), &surfaceCapabilitiesKHR));
    
    return surfaceCapabilitiesKHR;
}

std::vector<VkSurfaceFormatKHR> PhysicalDevice::getSurfaceFormatsKHR(const SurfaceKHR& surfaceKHR) const
{
    std::vector<VkSurfaceFormatKHR> formats;
    uint32_t formatCount = 0;

    VK_CHECK_ERROR(PhysicalDevice::getSurfaceFormatsKHR, vkGetPhysicalDeviceSurfaceFormatsKHR(this->_vkHandle, static_cast<VkSurfaceKHR>(surfaceKHR), &formatCount, nullptr));
    if (formatCount)
    {
        formats.resize(formatCount);
        VK_CHECK_ERROR(PhysicalDevice::getSurfaceFormatsKHR, vkGetPhysicalDeviceSurfaceFormatsKHR(this->_vkHandle, static_cast<VkSurfaceKHR>(surfaceKHR), &formatCount, &formats[0]));
    }
    return formats;
}

std::vector<VkPresentModeKHR> PhysicalDevice::getSurfacePresentModesKHR(const SurfaceKHR& surfaceKHR) const
{
    uint32_t presentModeCount;
    std::vector<VkPresentModeKHR> presentModesKHR;

    VK_CHECK_ERROR(PhysicalDevice::getSurfacePresentModesKHR, vkGetPhysicalDeviceSurfacePresentModesKHR(this->_vkHandle, static_cast<VkSurfaceKHR>(surfaceKHR), &presentModeCount, nullptr));
    if (presentModeCount > 0)
    {
        presentModesKHR.resize(presentModeCount);
        VK_CHECK_ERROR(PhysicalDevice::getSurfacePresentModesKHR, vkGetPhysicalDeviceSurfacePresentModesKHR(this->_vkHandle, static_cast<VkSurfaceKHR>(surfaceKHR), &presentModeCount, &presentModesKHR[0]));
    }
    return presentModesKHR;
}

VkPhysicalDeviceMemoryProperties PhysicalDevice::getMemoryProperties() const
{
    VkPhysicalDeviceMemoryProperties properties;

    vkGetPhysicalDeviceMemoryProperties(this->_vkHandle, &properties);
    return properties;
}
