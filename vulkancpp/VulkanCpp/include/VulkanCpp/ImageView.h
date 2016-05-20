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
#include "../src/Internal.hpp"

namespace VulkanCpp
{
    class ImageView : public Internal::VkWrapper<VkImageView, std::shared_ptr<Device>>
    {
    public:
        ImageView();
        ImageView(const std::shared_ptr<Device>& device, VkImageViewCreateInfo* vkImageViewCreateInfo);
        ~ImageView();

    public:
        ImageView(const ImageView&) = delete;
        ImageView(ImageView&&) = default;
        ImageView& operator=(const ImageView&) = delete;
        ImageView& operator=(ImageView&&) = default;
    };
}

#endif  //  __IMAGEVIEW_H__
