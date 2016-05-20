/*
 *  Command.h
 *
 *  Created by Marc Giovannoni on 18/05/2016
 */

#ifndef     __COMMAND_H__
#define     __COMMAND_H__

//
// System includes
//

#include <vector>
#include <vulkan/vulkan.h>

//
// Project includes
//

#include "VulkanCpp_Fwd.h"
#include "Buffer.h"
#include "Image.h"
#include "Pipeline.h"

#undef MemoryBarrier

namespace VulkanCpp
{
    typedef struct MemoryBarrier
    {
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;

        explicit operator VkMemoryBarrier() const
        {
            return VkMemoryBarrier {
                VK_STRUCTURE_TYPE_MEMORY_BARRIER,
                nullptr,
                srcAccessMask,
                dstAccessMask
            };
        }
    } MemoryBarrier;

    typedef struct BufferMemoryBarrier
    {
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;
        uint32_t  srcQueueFamilyIndex;
        uint32_t dstQueueFamilyIndex;
        const Buffer& buffer;
        VkDeviceSize offset;
        VkDeviceSize size;

        explicit operator VkBufferMemoryBarrier() const
        {
            return VkBufferMemoryBarrier{
                VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
                nullptr,
                srcAccessMask,
                dstAccessMask,
                srcQueueFamilyIndex,
                dstQueueFamilyIndex,
                static_cast<VkBuffer>(buffer),
                offset,
                size
            };
        }
    } BufferMemoryBarrier;

    typedef struct ImageMemoryBarrier
    {
        VkAccessFlags srcAccessMask;
        VkAccessFlags dstAccessMask;
        VkImageLayout oldLayout;
        VkImageLayout newLayout;
        uint32_t srcQueueFamilyIndex;
        uint32_t dstQueueFamilyIndex;
        const Image& image;
        VkImageSubresourceRange subresourceRange;

        explicit operator VkImageMemoryBarrier() const
        {
            return VkImageMemoryBarrier{
                VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                nullptr,
                srcAccessMask,
                dstAccessMask,
                oldLayout,
                newLayout,
                srcQueueFamilyIndex,
                dstQueueFamilyIndex,
                static_cast<VkImage>(image),
                subresourceRange
            };
        }
    } ImageMemoryBarrier;

    typedef struct PipelineBarrier
    {
        VkPipelineStageFlags                        srcStageMask;
        VkPipelineStageFlags                        dstStageMask;
        VkDependencyFlags                           dependencyFlags;
        const std::vector<MemoryBarrier>&           memoryBarriers;
        const std::vector<BufferMemoryBarrier>&     bufferMemoryBarriers;
        const std::vector<ImageMemoryBarrier>&      imageMemoryBarriers;
    } PipelineBarrier;

    typedef struct BindPipeline
    {
        VkPipelineBindPoint pipelineBindPoint;
        const Pipeline& pipeline;
    } BindPipeline;

    typedef struct BindVertexBuffer
    {
        uint32_t firstBinding;
        const std::vector<std::reference_wrapper<const Buffer>>& buffers;
        const std::vector<VkDeviceSize>& offsets;
    } BindVertexBuffer;

    typedef struct BindIndexBuffer
    {
        const Buffer& buffer;
        VkDeviceSize offset;
        VkIndexType indexType;
    } BindIndexBuffer;

    typedef struct DrawIndexed
    {
        uint32_t indexCount;
        uint32_t instanceCount;
        uint32_t firstIndex;
        int32_t vertexOffset;
        uint32_t firstInstance;
    } DrawIndexed;
}

#endif  //  __COMMAND_H__
