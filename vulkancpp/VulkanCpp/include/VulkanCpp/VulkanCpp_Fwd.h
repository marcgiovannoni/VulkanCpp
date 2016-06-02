/*
 *  VulkanCpp_Fwd.h
 *
 *  Created by Marc Giovannoni on 03/05/2016
 */

#ifndef     __VULKANCPP_FWD_H__
#define     __VULKANCPP_FWD_H__

namespace VulkanCpp
{
    class Instance;
    class PhysicalDevice;
    class Device;
    class Queue;
    class Fence;
    class CommandPool;
    class Semaphore;
    class Image;
    class SwapchainKHR;
    class SurfaceKHR;
    class CommandPool;
    class CommandBuffer;
    class ShaderModule;
    class PipelineLayout;
    class Buffer;
    class Pipeline;
    class RenderPass;
    class Framebuffer;

    namespace Command
    {
        struct MemoryBarrier;
        struct BufferMemoryBarrier;
        struct ImageMemoryBarrier;
        struct PipelineBarrier;
        struct BindPipeline;
        struct BindVertexBuffer;
        struct BindIndexBuffer;
        struct DrawIndexed;
    }
}

#endif  //  __VULKANCPP_FWD_H__
