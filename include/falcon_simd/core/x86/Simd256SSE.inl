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
        requires(sizeof...(Args) <= Lane) && (std::same_as<Args, DataType> && ...)
    FALCON_INLINE constexpr Simd256<SimdBackend::ARCH_SSE2, DataType, Lane>& Simd256<SimdBackend::ARCH_SSE2, DataType,
                                                                                     Lane>::set(Args... args)
    {
        // TODO: Apply this to SIMD128
        // To set values in 2 registers store the values into a tuple
        // and store and fill the lower lane and then the upper lane.
        constexpr auto argCount = sizeof...(args);
        const auto tuple        = std::make_tuple(args...);

        // Helper to set the values with unpacking to set to the correct register.
        auto invokeSet = []<size_t Offset, size_t... Is>(auto& reg, const auto& t, std::index_sequence<Is...>) {
            reg.set(std::get<Offset + Is>(t)...);
        };

        invokeSet.template operator()<0>(_lower, tuple, std::make_index_sequence<LOWER_LANE_COUNT>{});
        constexpr size_t upperArgs = argCount - LOWER_LANE_COUNT;
        invokeSet.template operator()<LOWER_LANE_COUNT>(_upper, tuple, std::make_index_sequence<upperArgs>{});

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
