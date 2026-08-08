/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 27, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x3TestSetup.h"

#include <fgm/matrices/Mat3x4.h>


/**
 * @addtogroup T_FGM_Mat4x3_Transpose
 * @{
 */

namespace
{
    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4x3 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x3Transpose: public ::testing::Test
    {
    protected:
        fgm::Mat4x3<T> _matrix;
        fgm::Mat3x4<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { fgm::Vec4{ T(1), T(4), T(7), T(10) }, fgm::Vec4{ T(2), T(5), T(8), T(11) },
                                   fgm::Vec4{ T(3), T(6), T(9), T(12) } };
            _expectedTranspose = { fgm::Vec3{ T(1), T(2), T(3) }, fgm::Vec3{ T(4), T(5), T(6) },
                                   fgm::Vec3{ T(7), T(8), T(9) }, fgm::Vec3{ T(10), T(11), T(12) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x3Transpose, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat4x3 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec3, we are taking col, row order.
        //       That's why Vec3(1, 2, 3) is the transpose and not Vec4(1, 4, 7)

        /// @test Verify matrix transpose is returns a 3x4 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == fgm::Vec3(1, 2, 3));
        static_assert(TRANSPOSE_MAT[1] == fgm::Vec3(4, 5, 6));
        static_assert(TRANSPOSE_MAT[2] == fgm::Vec3(7, 8, 9));
        static_assert(TRANSPOSE_MAT[3] == fgm::Vec3(10, 11, 12));

        /// @test Verify matrix transpose using static variant returns a 3x4 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = fgm::Mat4x3<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == fgm::Vec3(1, 2, 3));
        static_assert(TRANSPOSE_MAT_STATIC[1] == fgm::Vec3(4, 5, 6));
        static_assert(TRANSPOSE_MAT_STATIC[2] == fgm::Vec3(7, 8, 9));
        static_assert(TRANSPOSE_MAT_STATIC[3] == fgm::Vec3(10, 11, 12));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x3Transpose, Returns3x4MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat4x3Transpose, StaticWrapper_Returns3x4MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Mat4x3<TypeParam>::transpose(this->_matrix)); }

/** @} */
