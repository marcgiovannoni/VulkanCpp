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

#define VK_LOG_ERROR_MESSAGE(scope, vkResult) VulkanCpp::logError(#scope, __FILE__, __LINE__, vkResult)
#define VK_LOG_ERROR_MESSAGE_DISABLED(scope, vkResult) LOG_MESSAGE_DISABLED(Error, scope, vkResult)

#if !defined NDEBUG || defined BUILD_ENABLE_VULKAN_RUNTIME_DEBUG
#define VK_LOG_ERROR(scope, vkResult) VK_LOG_ERROR_MESSAGE(scope, vkResult)
#else
#define VK_LOG_ERROR(scope, vkResult) VK_LOG_ERROR_MESSAGE_DISABLED(scope, vkResult)
#endif

namespace VulkanCpp
{
    static void logError(const char *scope, const char *fileName, int lineNumber, VkResult result)
    {
        if (result < 0)
        {
            switch (result)
            {
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_OUT_OF_HOST_MEMORY");
                break;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_OUT_OF_DEVICE_MEMORY");
                break;
            case VK_ERROR_INITIALIZATION_FAILED:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_INITIALIZATION_FAILED");
                break;
            case VK_ERROR_DEVICE_LOST:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_DEVICE_LOST");
                break;
            case VK_ERROR_MEMORY_MAP_FAILED:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_MEMORY_MAP_FAILED");
                break;
            case VK_ERROR_LAYER_NOT_PRESENT:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_LAYER_NOT_PRESENT");
                break;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_EXTENSION_NOT_PRESENT");
                break;
            case VK_ERROR_FEATURE_NOT_PRESENT:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_FEATURE_NOT_PRESENT");
                break;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_INCOMPATIBLE_DRIVER");
                break;
            case VK_ERROR_TOO_MANY_OBJECTS:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_TOO_MANY_OBJECTS");
                break;
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_FORMAT_NOT_SUPPORTED");
                break;
            case VK_ERROR_SURFACE_LOST_KHR:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_SURFACE_LOST_KHR");
                break;
            case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
                break;
            case VK_SUBOPTIMAL_KHR:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_SUBOPTIMAL_KHR");
                break;
            case VK_ERROR_OUT_OF_DATE_KHR:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_OUT_OF_DATE_KHR");
                break;
            case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
                break;
            case VK_ERROR_VALIDATION_FAILED_EXT:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_VALIDATION_FAILED_EXT");
                break;
            case VK_ERROR_INVALID_SHADER_NV:
                DebugLogging::logMessage(DebugLogging::llError, scope, fileName, lineNumber, "VK_ERROR_INVALID_SHADER_NV");
                break;
            default:
                break;
            }
        }
    }
}

#endif  //  __VKDEBUGLOGGING_H__
#pragma once
