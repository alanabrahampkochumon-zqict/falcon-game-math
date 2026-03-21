#pragma once

#include "common/MathTraits.h"
#include "vector/Vector4D.h"

#include <cstddef>

namespace fgm
{
    template <StrictArithmetic T>
    struct alignas(16) Matrix4D
    {
        using value_type = T;

        static constexpr std::size_t columns = 4;
        static constexpr std::size_t rows = 4;

        union {
            Vector4D<T> col_vectors[columns];
            T elements[columns][rows];
        };

        /*************************************
         *                                   *
         *            INITIALIZERS           *
         *                                   *
         *************************************/

        Matrix4D();

        Matrix4D(T v_0_0, T v_0_1, T v_0_2, T v_0_3, T v_1_0, T v_1_1, T v_1_2, T v_1_3, T v_2_0, T v_2_1, T v_2_2,
                 T v_2_3, T v_3_0, T v_3_1, T v_3_2, T v_3_3);

        Matrix4D(Vector4D<T> col0, Vector4D<T> col1, Vector4D<T> col2, Vector4D<T> col3);

        template <StrictArithmetic U>
        Matrix4D(const Matrix4D<U>& other);


        /*************************************
         *                                   *
         *            ACCESSORS              *
         *                                   *
         *************************************/

        Vector4D<T>& operator[](std::size_t index);
        const Vector4D<T>& operator[](std::size_t index) const;

        T& operator()(std::size_t row, std::size_t col);
        const T& operator()(std::size_t row, std::size_t col) const;


        /*************************************
         *                                   *
         *      ARITHMETIC OPERATORS         *
         *                                   *
         *************************************/
        template <StrictArithmetic U>
        auto operator+(const Matrix4D<U>& other) const -> Matrix4D<std::common_type_t<T, U>>;

        template <StrictArithmetic U>
        Matrix4D& operator+=(const Matrix4D<U>& other);
    };

} // namespace fgm

#include "Matrix4D.tpp"