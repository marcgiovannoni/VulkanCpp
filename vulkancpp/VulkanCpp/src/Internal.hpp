/*
 *  Internal.hpp
 *
 *  Created by Marc Giovannoni on 19/05/2016
 */

#ifndef     __INTERNAL_H__
#define     __INTERNAL_H__

//
// System includes
//

#include <memory>
#include <mutex>
#include <tuple>

//
// Project includes
//

#include "VulkanCpp/VulkanCpp_Fwd.h"

namespace Internal
{
    template<std::size_t _SizeL = 0, std::size_t _SizeR = 0, typename... _ArgsL, typename... _ArgsR>
    inline typename std::enable_if<(sizeof...(_ArgsL) == sizeof...(_ArgsR)) && (_SizeL == sizeof...(_ArgsL)), void>::type
        move(std::tuple<_ArgsL...>&, std::tuple<_ArgsR...>&)
    {
    }

    template<std::size_t _SizeL = 0, std::size_t _SizeR = 0, typename... _ArgsL, typename... _ArgsR>
    inline typename std::enable_if<(sizeof...(_ArgsL) == sizeof...(_ArgsR)) && (_SizeL < sizeof...(_ArgsL)), void>::type
        move(std::tuple<_ArgsL...>& l, std::tuple<_ArgsR...>& r)
    {
        std::get<_SizeL>(l) = std::move(std::get<_SizeR>(r));
        std::get<_SizeL>(r) = nullptr;

        move<_SizeL + 1, _SizeR + 1>(l, r);
    }

    template <class _VkHandle, class... _Deps>
    class VkWrapper
    {
    protected:
        _VkHandle _vkHandle;
        std::mutex _mutex;
        std::tuple<_Deps...> _deps;

    protected:
        VkWrapper(_VkHandle vkHandle) : _vkHandle(vkHandle) {}

        template<class... _CTypes>
        VkWrapper(_VkHandle vkHandle, _CTypes&&... cvals) : _vkHandle(vkHandle), _deps(std::forward<_CTypes>(cvals)...) {}

    public:
        template<class... _CTypes>
        VkWrapper() : _vkHandle(nullptr), _deps(std::forward<_CTypes>(nullptr)...) {}

        template<class... _CTypes>
        VkWrapper(_CTypes&&... cvals) : _vkHandle(nullptr), _deps(std::forward<_CTypes>(cvals)...) {}

        ~VkWrapper() {}


        VkWrapper(const VkWrapper&) = delete;
        VkWrapper& operator=(const VkWrapper&) = delete;

        VkWrapper(VkWrapper&& rhs)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);

            this->_vkHandle = std::move(rhs._vkHandle);
            rhs._vkHandle = nullptr;

            move(this->_deps, rhs._deps);
        }

        VkWrapper& operator=(VkWrapper&& rhs)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);

            if (this != &rhs)
            {
                this->_vkHandle = std::move(rhs._vkHandle);
                rhs._vkHandle = nullptr;

                move(this->_deps, rhs._deps);
            }
            return *this;
        }

        explicit operator _VkHandle() const
        {
            return this->_vkHandle;
        }

        template<class _Type>
        const _Type& get() const
        {
            return std::get<_Type>(this->_deps);
        }
    };
}

#endif  //  __INTERNAL_H__
