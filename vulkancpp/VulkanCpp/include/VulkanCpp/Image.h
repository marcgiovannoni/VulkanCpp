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

namespace VulkanCpp
{
    class Image
    {
    private:
        VkImage _vkImage;

    public:
        Image();
        explicit Image(VkImage vkImage);
        ~Image();

    public:
        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;
        Image(Image&&);
        Image& operator=(Image&&);

        // VkImage cast
        explicit operator VkImage() const;
    };
}

#endif  //  __IMAGE_H__
