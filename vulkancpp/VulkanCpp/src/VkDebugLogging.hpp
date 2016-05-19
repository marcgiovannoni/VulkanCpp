/*
 *  VkDebugLogging.hpp
 *
 *  Created by Marc Giovannoni on 19/04/2016
 */

#ifndef     __VKDEBUGLOGGING_H__
#define     __VKDEBUGLOGGING_H__

//
// System includes
//

#include <sstream>

//
// Project includes
//

#include <vulkan/vulkan.h>
#include "DebugLogging/DebugLogging.h"
#include "VulkanCpp/VkException.h"

#define VK_LOG_ERROR_MESSAGE(scope, vkResult) VulkanCpp::logError(#scope, __FILE__, __LINE__, vkResult)
#define VK_LOG_ERROR_MESSAGE_DISABLED(scope, vkResult) LOG_MESSAGE_DISABLED(Error, scope, vkResult)

#if !defined NDEBUG || defined BUILD_ENABLE_VULKAN_RUNTIME_DEBUG
#define VK_LOG_ERROR(scope, vkResult) VK_LOG_ERROR_MESSAGE(scope, vkResult)
#else
#define VK_LOG_ERROR(scope, vkResult) VK_LOG_ERROR_MESSAGE_DISABLED(scope, vkResult)
#endif

#define VK_CHECK_ERROR(scope, error) VulkanCpp::throwError(error)

namespace VulkanCpp
{
    static const char* getVkError(VkResult result)
    {
        switch (result)
        {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "VK_ERROR_INITIALIZATION_FAILED";
        case VK_ERROR_DEVICE_LOST:
            return "VK_ERROR_DEVICE_LOST";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "VK_ERROR_MEMORY_MAP_FAILED";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "VK_ERROR_LAYER_NOT_PRESENT";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "VK_ERROR_FEATURE_NOT_PRESENT";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "VK_ERROR_TOO_MANY_OBJECTS";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "VK_ERROR_SURFACE_LOST_KHR";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        case VK_SUBOPTIMAL_KHR:
            return "VK_SUBOPTIMAL_KHR";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "VK_ERROR_OUT_OF_DATE_KHR";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "VK_ERROR_VALIDATION_FAILED_EXT";
        case VK_ERROR_INVALID_SHADER_NV:
            return "VK_ERROR_INVALID_SHADER_NV";
        default:
            return "VK_UNKNOWN_ERROR";
        }
    }

    static void throwError(VkResult result)
    {
        if (result != VK_SUCCESS)
        {
            throw new VkException(getVkError(result));
        }
    }
}

#endif  //  __VKDEBUGLOGGING_H__
#pragma once
