/*
 *  VkException.cpp
 *  
 *  Created by Marc Giovannoni on 22/04/2016
 */

#include <stdexcept>
#include "VulkanCpp/VkException.h"

using namespace VulkanCpp;

VkException::VkException(const char* error) : _error(error)
{
    std::logic_error(this->_error);
}

VkException::VkException(VkException&& src)
: _error(src._error)
{
    // Empty
}

VkException::VkException(const VkException& src)
: _error(src._error)
{
    // Empty
}

VkException::~VkException()
{
    // Empty
}

const char* VkException::getError() const
{
    return (this->_error);
}
