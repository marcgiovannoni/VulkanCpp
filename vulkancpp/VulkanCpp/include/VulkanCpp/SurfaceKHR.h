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
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class SurfaceKHR : public Internal::VkWrapper<VkSurfaceKHR, std::shared_ptr<Instance>>
    {
    public:
        SurfaceKHR();
        template <typename _VkSurfaceCreateInfoKHR>
        SurfaceKHR(const std::shared_ptr<Instance>& instance, _VkSurfaceCreateInfoKHR* win32SurfaceKHRInfo);
        ~SurfaceKHR();

    public:
        SurfaceKHR(const SurfaceKHR&) = delete;
        SurfaceKHR(SurfaceKHR&&) = default;
        SurfaceKHR& operator=(const SurfaceKHR&) = delete;
        SurfaceKHR& operator=(SurfaceKHR&&) = default;
    };
}

#endif  //  __SURFACEKHR_H__
