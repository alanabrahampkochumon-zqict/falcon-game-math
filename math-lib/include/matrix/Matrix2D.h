#pragma once
#include "vector/Vector2D.h"

#include <cstddef>
#include <type_traits>

namespace fgm
{
    template <typename T>
    struct Matrix2D
    {
        static_assert(std::is_arithmetic_v<T>,
                      "Matrix2D can only be instantiated with numbers like floats, integers, etc.");

        using value_type = T;

    private:
        union {
            Vector2D<T> columns[2];
            T elements[2][2];
        };

    public:
        Matrix2D();
        Matrix2D(T v_0_0, T v_0_1, T v_1_0, T v_1_1);
        Matrix2D(Vector2D<T> col0, Vector2D<T> col1);

        template <typename S, std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D(const Matrix2D& other);

        Vector2D<T>& operator[](size_t index);
        const Vector2D<T>& operator[](size_t index) const;

        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;

        // Math Operators
        Matrix2D operator+(const Matrix2D& other) const;
        Matrix2D& operator+=(const Matrix2D& other);

        Matrix2D operator-(const Matrix2D& other) const;
        Matrix2D& operator-=(const Matrix2D& other);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D operator*(const S& scalar) const;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D& operator*=(const S& scalar);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Vector2D<T> operator*(const Vector2D<S>& vec) const;

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D<T> operator*(const Matrix2D<S>& other) const;

        /**
         * Multiplies a matrix by a matrix with *= operator.
         * @tparam S Type of the other Matrix
         * @param other The matrix to be multiplied with.
         * @return Matrix on which *= is called, but with new values
         */
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D& operator*=(const Matrix2D<S>& other);

        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D operator/(const S& scalar) const;
        template <typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
        Matrix2D& operator/=(const S& scalar);

        // Determinants
        // Calculates the determinant for the current Matrix2D.
        T determinant() const;

        // Static wrapper for Matrix 3D determinants.
        static T determinant(const Matrix2D<T>& matrix);

        // Transpose
        Matrix2D transpose() const;

        static Matrix2D transpose(const Matrix2D& matrix);

        // Matrix Inverse
        Matrix2D inverse() const;

        static Matrix2D inverse(const Matrix2D& matrix);
    };

    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    Matrix2D<T> operator*(const S& scalar, const Matrix2D<T>& matrix);

    /**
     * Multiplies a Vector2D by a Matrix2D.
     * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
     * @tparam T Type for matrix values
     * @tparam S Type for vector values
     * @param vec vector to be multiplied.
     * @param mat matrix to be multiplied against.
     * @return a new Vector2D transposed(row major form)
     */
    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    Vector2D<T> operator*(const Vector2D<S>& vec, const Matrix2D<T>& mat);

    /**
     * Multiplies a Vector2D by a Matrix2D.
     * NOTE: This operation transposes the 3x1 vector to a 1x3 vector(matrix), and may not be desirable in engine code.
     * NOTE: This operation returns a new vector so it is strictly for testing purposes and completeness and is not
     * desirable to be used in game engine.
     * @tparam T Type for matrix values
     * @tparam S Type for vector values
     * @param vec vector to be multiplied.
     * @param mat matrix to be multiplied against.
     * @return the passed in vector
     */
    template <typename T, typename S, typename = std::enable_if_t<std::is_arithmetic_v<S>>>
    Vector2D<T> operator*=(Vector2D<S>& vec, const Matrix2D<T>& mat);


} // namespace fgm

#include "Matrix2D.tpp"