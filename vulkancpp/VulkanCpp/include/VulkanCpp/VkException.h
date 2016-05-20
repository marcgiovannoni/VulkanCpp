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
        const char* _error;

    public:
        explicit VkException(const char* error);
        virtual ~VkException();

    public:
        VkException(VkException&&);
        VkException(const VkException&);
        VkException& operator=(VkException&&) = delete;
        VkException& operator=(const VkException&) = delete;

    public:
        const char* getError() const;
    };
}

#endif  //  __VKEXCEPTION_H__