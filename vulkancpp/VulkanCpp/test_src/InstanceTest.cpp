/*
 *  InstanceTest.cpp
 *  
 *  Created by Marc Giovannoni on 10/05/2016
 */

#include <gtest/gtest.h>
#include <VulkanCpp/Instance.h>

using namespace VulkanCpp;

VkApplicationInfo vkApplicationInfo = {
    VK_STRUCTURE_TYPE_APPLICATION_INFO,
    nullptr,
    "VkApplication",
    VK_MAKE_VERSION(0, 0, 1),
    "VkEngine",
    VK_MAKE_VERSION(0, 0, 1),
    VK_MAKE_VERSION(1, 0, 8),
};

VkInstanceCreateInfo vkInstanceCreateInfo = {
    VK_STRUCTURE_TYPE_APPLICATION_INFO,
    nullptr,
    0,
    &vkApplicationInfo,
    0,
    nullptr,
    0,
    nullptr
};

TEST(InstanceTest, constructor_destructor)
{
    Instance instance(&vkInstanceCreateInfo);

    EXPECT_TRUE(true);
}

TEST(InstanceTest, move_copy_constructor)
{
    Instance instance(&vkInstanceCreateInfo);
    VkInstance ptr = static_cast<VkInstance>(instance);
    Instance instance2(std::move(instance));

    EXPECT_TRUE(static_cast<VkInstance>(instance) == nullptr &&
        static_cast<VkInstance>(instance2) == ptr);
}

TEST(InstanceTest, physical_devices)
{
    Instance instance(&vkInstanceCreateInfo);

    std::vector<PhysicalDevice> devices = instance.enumeratePhysicalDevices();

    EXPECT_FALSE(devices.empty());
}
