/*
 *  VulkanCpp.h
 *
 *  Created by Marc Giovannoni on 02/05/2016
 */

#ifndef     __VULKANCPP_H__
#define     __VULKANCPP_H__

#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
#define VK_CPP_NULL nullptr
#else
#define VK_CPP_NULL 0
#endif

#endif  //  __VULKANCPP_H__
