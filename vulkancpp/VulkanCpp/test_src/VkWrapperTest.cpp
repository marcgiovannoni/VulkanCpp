/*
 *  VkWrapperTest.cpp
 *  
 *  Created by Marc Giovannoni on 19/05/2016
 */

#include <gtest/gtest.h>
#include "../src/Internal.hpp"
#include <VulkanCpp/VulkanCpp.h>
#include <VulkanCpp/Instance.h>

using namespace Internal;
using namespace VulkanCpp;

namespace 
{

#define TEST_A A*

    class A
    {
    public:
        int* _i;
        
        A() { this->_i = new int[10]; }
        ~A() { delete[] this->_i; }
    };

    class B
    {
    public:
        float* _f;

        B() { this->_f = new float[10]; }
        ~B() { delete[] this->_f; }
    };

    class C : public VkWrapper<TEST_A, std::shared_ptr<B>>
    {
    public:
        C() : VkWrapper() {}
        C(std::shared_ptr<B> b) : VkWrapper<TEST_A, std::shared_ptr<B>>(b) {}
    };
}

TEST(BaseWrapper, move)
{
    std::shared_ptr<B> b = std::make_shared<B>();

    C foo(b);
    C bar = std::move(foo);

    EXPECT_TRUE(true);
}

TEST(BaseWrapper, default_constructor)
{
    C foo;
    C f;

    EXPECT_TRUE(true);
}
