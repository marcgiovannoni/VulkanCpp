/*
 *  PhysicalDevice.cpp
 *  
 *  Created by Marc Giovannoni on 19/04/2016
 */

#include "VulkanCpp/PhysicalDevice.h"

using namespace VulkanCpp;

PhysicalDevice::PhysicalDevice() : _vkPhysicalDevice(nullptr)
{
}

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) : _vkPhysicalDevice(physicalDevice)
{
}

PhysicalDevice::~PhysicalDevice()
{
}

PhysicalDevice::PhysicalDevice(PhysicalDevice&& rhs)
{
    this->_vkPhysicalDevice = std::move(rhs._vkPhysicalDevice);
    rhs._vkPhysicalDevice = nullptr;
}

PhysicalDevice::operator VkPhysicalDevice() const
{
    return this->_vkPhysicalDevice;
}

VkPhysicalDeviceProperties PhysicalDevice::getPhysicalDeviceProperties()
{
    VkPhysicalDeviceProperties properties;

    vkGetPhysicalDeviceProperties(this->_vkPhysicalDevice, &properties);

    return properties;
}

std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties()
{
    std::vector<VkQueueFamilyProperties> queueFamiliysProperties;
    uint32_t queueFamilyCnt = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(this->_vkPhysicalDevice, &queueFamilyCnt, nullptr);

    if (!queueFamilyCnt)
    {
        return queueFamiliysProperties;
    }

    queueFamiliysProperties.resize(queueFamilyCnt);

    vkGetPhysicalDeviceQueueFamilyProperties(this->_vkPhysicalDevice, &queueFamilyCnt, &queueFamiliysProperties[0]);

    return queueFamiliysProperties;
}