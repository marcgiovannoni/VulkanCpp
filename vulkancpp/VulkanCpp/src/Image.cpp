/*
 *  Image.cpp
 *  
 *  Created by Marc Giovannoni on 22/04/2016
 */

#include <memory>
#include "VulkanCpp/Image.h"

using namespace VulkanCpp;

Image::Image()
{
    // Empty
}

Image::Image(VkImage vkImage) : VkWrapper(vkImage)
{
    // Empty
}

Image::~Image()
{
    // Empty
}
