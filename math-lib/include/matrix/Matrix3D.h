#pragma once
#include "../vector/Vector3D.h"

#include <cstddef>
#include <type_traits>

namespace fgm
{
    template <typename T>
    struct Matrix3D
    {
        static_assert(std::is_arithmetic_v<T>,
                      "Matrix3D can only be instantiated with numbers like floats, integers, etc.");
        using value_type = T;

    private:
        union {
            T elements[3][3];
            Vector3D<T> columns[3];
        };

    public:
        Matrix3D();
        Matrix3D(T v_0_0, T v_0_1, T v_0_2, T v_1_0, T v_1_1, T v_1_2, T v_2_0, T v_2_1, T v_2_2);
        Matrix3D(Vector3D<T> col0, Vector3D<T> col1, Vector3D<T> col2);

        template <typename S,
                  typename = std::enable_if_t<std::is_arithmetic_v<S>, int>> // int added to solve compiler confusing
                                                                             // this with copy constructor
        Matrix3D(const Matrix3D<S>& other);
        // template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>> // Added 'typename' and ', int'
        // Matrix3D(const Matrix3D<S>& other)
        //{
        //	columns[0] = Vector3D<T>(other[0]);
        //	columns[1] = Vector3D<T>(other[1]);
        //	columns[2] = Vector3D<T>(other[2]);
        // }


        Vector3D<T>& operator[](size_t index);
        const Vector3D<T>& operator[](size_t index) const;

        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;


        // Math Operators
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator+(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix3D& operator+=(const Matrix3D<S>& other);


        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator-(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix3D& operator-=(const Matrix3D<S>& other);


        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator*(const S& scalar) const -> Matrix3D<std::common_type_t<T, S>>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix3D& operator*=(const S& scalar);


        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator*(const Vector3D<S>& vec) const -> Vector3D<std::common_type_t<T, S>>;


        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator*(const Matrix3D<S>& other) const -> Matrix3D<std::common_type_t<T, S>>;

        /**
         * Multiplies a matrix by a matrix with *= operator.
         * NOTE: Not recommended for game engine, since it involves object copying.
         * RECOMMENDED: Use Mat * Mat
         * @tparam S Type of the other Matrix
         * @param other The matrix to be multiplied with.
         * @return Matrix on which *= is called, but with new values
         */
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix3D& operator*=(const Matrix3D<S>& other);


        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        auto operator/(const S& scalar) const -> Matrix3D<std::common_type_t<T, S>>;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix3D& operator/=(const S& scalar);

        // Determinants
        // Calculates the determinant for the current Matrix3D.
        T determinant() const;

        // Static wrapper for Matrix 3D determinants.
        static T determinant(const Matrix3D& matrix);

        // Transpose
        Matrix3D transpose() const;

        static Matrix3D transpose(const Matrix3D& matrix);

        // Matrix Inverse
        Matrix3D inverse() const;

        static Matrix3D inverse(const Matrix3D& matrix);
    };

    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
              typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    auto operator*(const S& scalar, const Matrix3D<T>& matrix) -> Matrix3D<std::common_type_t<T, S>>;

    /**
     * Multiplies a Vector3D by a Matrix3D.
     * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
     * @tparam T Type for matrix values
     * @tparam S Type for vector values
     * @param vec vector to be multiplied.
     * @param mat matrix to be multiplied against.
     * @return a new Vector3D transposed(row major form)
     */
    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
              typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    auto operator*(const Vector3D<S>& vec, const Matrix3D<T>& mat) -> Vector3D<std::common_type_t<T, S>>;

    /**
     * Multiplies a Vector3D by a Matrix3D.
     * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
     * NOTE: This operation returns a new vector so it is strictly for testing purposes and completeness and is not
     * desirable to be used in game engine.
     * @tparam T Type for matrix values
     * @tparam S Type for vector values
     * @param vec vector to be multiplied.
     * @param mat matrix to be multiplied against.
     * @return the passed in vector
     */
    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<T>>,
              typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    auto operator*=(Vector3D<S>& vec, const Matrix3D<T>& mat) -> Vector3D<std::common_type_t<T, S>>;


}; // namespace fgm

#include "Matrix3D.tpp"