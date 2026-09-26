#pragma once
/**
 * @file Simd256SSE.inl
 * @author Alan Abraham P Kochumon
 * @date Created on: September 26, 2026
 *
 * @brief Implementation of templated functions declared in Simd256SSE.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <tuple>

namespace falcon
{
    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(SimdSafeConvertible<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(Args&&... data) noexcept
    {
        /// If only single argument is provided then it will be broadcast otherwise the data will be filled
        /// from bottom to top, with zeroes in unoccupied spaces.
        if constexpr (sizeof...(data) == 1)
        {
            broadcast(std::forward<Args>(data)...);
        }
        else
        {
            set(std::forward<Args>(data)...);
        }
    }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, T, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                             Lane>::cast() const noexcept
    { return Simd256(_lower.template cast<T>(), _upper.template cast<T>()); }


    template <typename DataType, size_t Lane>
    template <typename T>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, T, Lane> Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                             Lane>::cast() noexcept
    { return Simd256(_lower.template cast<T>(), _upper.template cast<T>()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(
        std::span<const DataType> values) noexcept
    { loadAligned(values.data()); }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(const DataType* pBuffer) noexcept
    { loadAligned(pBuffer); }


    template <typename DataType, size_t Lane>
    template <typename... Args>
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                     Lane>::set(Args... args)
    {
        // TODO: Apply this to SIMD128
        // To support variable argument passing we need to return pass down a zero for all the lanes that are
        // not provided.
        constexpr auto argCount  = sizeof...(args);
        const DataType arr[Lane] = { args... };

        // Fill the upper lane
        if constexpr (argCount <= LOWER_LANE_COUNT)
        {
            _upper.setZero();
        }
        else
        {
            auto fillUpper = [&]<size_t... Indices>(std::index_sequence<Indices...>) {
                _upper.set(arr[LOWER_LANE_COUNT + Indices]...);
            };
            fillUpper(std::make_index_sequence<UPPER_LANE_COUNT>{});
        }
        // Fill the lower lane
        auto fillLower = [&]<size_t... Indices>(std::index_sequence<Indices...>) {
            _lower.set(arr[Indices]...);
        };
        fillLower(std::make_index_sequence<LOWER_LANE_COUNT>{});

        return *this;
    }


    template <typename DataType, size_t Lane>
    template <typename DataType2>
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::Simd256(
        const Simd256<SimdBackend::ARCH_SSE2, DataType2, Lane>& other)
    {
        _lower = static_cast<Simd128<SimdBackend::ARCH_SSE2, DataType, LOWER_LANE_COUNT>>(other._lower);
        _upper = static_cast<Simd128<SimdBackend::ARCH_SSE2, DataType, UPPER_LANE_COUNT>>(other._upper);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::loadAligned(
        const DataType* data) noexcept
    {
        _lower.loadAligned(data);
        _upper.loadAligned(data + LOWER_LANE_COUNT);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::load(const DataType* data) noexcept
    {
        _lower.load(data);
        _upper.load(data + LOWER_LANE_COUNT);
    }

    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::broadcast(DataType value) noexcept
    {
        _lower.broadcast(value);
        _upper.broadcast(value);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::setZero() noexcept
    {
        _lower.setZero();
        _upper.setZero();
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::setOne() noexcept
    {
        _lower.setOne();
        _upper.setOne();
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::store(
        DataType* pBuffer) const noexcept
    {
        _lower.store(pBuffer);
        _upper.store(pBuffer + LOWER_LANE_COUNT);
    }


    template <typename DataType, size_t Lane>
    FALCON_INLINE constexpr void Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>::storeAligned(
        DataType* pBuffer) const noexcept
    {
        _lower.storeAligned(pBuffer);
        _upper.storeAligned(pBuffer + LOWER_LANE_COUNT);
    }
} // namespace falcon
