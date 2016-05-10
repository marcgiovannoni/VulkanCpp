/*
 *  SurfaceKHR.h
 *
 *  Created by Marc Giovannoni on 03/05/2016
 */

#ifndef     __SURFACEKHR_H__
#define     __SURFACEKHR_H__

//
// System includes
//

#include <memory>
#include <vulkan/vulkan.h>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"

namespace VulkanCpp
{
    class SurfaceKHR
    {
    private:
        std::shared_ptr<Instance> _instance;
        VkSurfaceKHR _vkSurfaceKHR;

    public:
        SurfaceKHR();
        template <typename _VkSurfaceCreateInfoKHR>
        SurfaceKHR(std::shared_ptr<Instance> vulkanInstance, _VkSurfaceCreateInfoKHR* win32SurfaceKHRInfo);
        ~SurfaceKHR();

    public:
        SurfaceKHR(SurfaceKHR&&);
        SurfaceKHR(const SurfaceKHR&) = delete;
        SurfaceKHR& operator=(SurfaceKHR&&);
        SurfaceKHR& operator=(const SurfaceKHR&) = delete;

        // VkSurfaceKHR cast
        explicit operator VkSurfaceKHR() const;
    };
}

#endif  //  __SURFACEKHR_H__
