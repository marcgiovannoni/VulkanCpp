/*
 *  Image.h
 *
 *  Created by Marc Giovannoni on 22/04/2016
 */

#ifndef     __IMAGE_H__
#define     __IMAGE_H__

//
// System includes
//

#include <vulkan/vulkan.h>

//
// Project includes
//

#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class Image : public Internal::VkWrapper<VkImage>
    {
    public:
        Image();
        explicit Image(VkImage vkImage);
        ~Image();

    public:
        Image(const Image&) = delete;
        Image(Image&&) = default;
        Image& operator=(const Image&) = delete;
        Image& operator=(Image&&) = default;
    };
}

#endif  //  __IMAGE_H__
