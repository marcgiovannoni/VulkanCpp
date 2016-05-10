/*
 *  Image.cpp
 *  
 *  Created by Marc Giovannoni on 22/04/2016
 */

#include <memory>
#include "VulkanCpp/Image.h"

using namespace VulkanCpp;

Image::Image() : _vkImage(nullptr)
{
}

Image::Image(VkImage vkImage) : _vkImage(vkImage)
{

}

Image::~Image()
{
}

Image::Image(Image&& rhs)
{
    this->_vkImage = std::move(rhs._vkImage);

    rhs._vkImage = nullptr;
}

Image& Image::operator=(Image&& rhs)
{
    if (this != &rhs)
    {
        this->_vkImage = std::move(rhs._vkImage);
        rhs._vkImage = nullptr;
    }
    return *this;
}

Image::operator VkImage() const
{
    return this->_vkImage;
}

