/*
 *  ImageView.h
 *
 *  Created by Marc Giovannoni on 22/04/2016
 */

#ifndef     __IMAGEVIEW_H__
#define     __IMAGEVIEW_H__

//
// System includes
//

#include <vulkan/vulkan.h>
#include <memory>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"

namespace VulkanCpp
{
    class ImageView
    {
    private:
        std::shared_ptr<Device> _device;
        VkImageView _vkImageView;

    public:
        ImageView();
        ImageView(std::shared_ptr<Device> device, VkImageViewCreateInfo* vkImageViewCreateInfo);
        ~ImageView();

    public:
        ImageView(const ImageView&) = delete;
        ImageView& operator=(const ImageView&) = delete;
        ImageView(ImageView&&);
        ImageView& operator=(ImageView&&);

        // VkImageView cast
        explicit operator VkImageView() const;
    };
}

#endif  //  __IMAGEVIEW_H__
