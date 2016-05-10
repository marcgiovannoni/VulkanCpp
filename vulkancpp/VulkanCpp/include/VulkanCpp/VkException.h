/*
 *  VkException.h
 *
 *  Created by Marc Giovannoni on 22/04/2016
 */

#ifndef     __VKEXCEPTION_H__
#define     __VKEXCEPTION_H__

//
// System includes
//

//
// Project includes
//

#include <vulkan/vulkan.h>

namespace VulkanCpp
{
    class VkException
    {
    private:
        VkResult _error;

    public:
        explicit VkException(VkResult error);
        virtual ~VkException();

    public:
        VkException(VkException&&);
        VkException(const VkException&);
        VkException& operator=(VkException&&) = delete;
        VkException& operator=(const VkException&) = delete;

    public:
        VkResult getError() const;
    };
}

#endif  //  __VKEXCEPTION_H__