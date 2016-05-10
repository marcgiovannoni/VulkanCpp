/*
 *  VkException.cpp
 *  
 *  Created by Marc Giovannoni on 22/04/2016
 */

#include "VulkanCpp/VkException.h"

using namespace VulkanCpp;

VkException::VkException(VkResult error) : _error(error)
{
    // Empty
};

VkException::VkException(VkException&& src)
: _error(src._error)
{
    // Empty
};

VkException::VkException(const VkException& src)
: _error(src._error)
{
    // Empty
};

VkException::~VkException()
{
    // Empty
};

VkResult VkException::getError() const
{
    return (this->_error);
};
