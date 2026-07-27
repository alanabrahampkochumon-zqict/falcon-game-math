/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"

#include <fgm/matrices/Mat4x2.h>


/**
 * @addtogroup T_FGM_Mat2x4_Transpose
 * @{
 */

namespace
{
    /**************************************
     *                                    *
     *               SETUP                *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2x4 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x4Transpose: public testing::Test
    {
    protected:
        fgm::Mat2x4<T> _matrix;
        fgm::Mat4x2<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { fgm::Vec2{ T(1), T(5) }, fgm::Vec2{ T(2), T(6) }, fgm::Vec2{ T(3), T(7) },
                                   fgm::Vec2{ T(4), T(8) } };
            _expectedTranspose = { fgm::Vec4{ T(1), T(2), T(3), T(4) }, fgm::Vec4{ T(5), T(6), T(7), T(8) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4Transpose, SupportedTypes);




    /**************************************
     *                                    *
     *           STATIC TESTS             *
     *                                    *
     **************************************/

    /** @brief Verify that matrix transpose is available at compile time. */
    namespace static_tests
    {
        constexpr fgm::Mat2x4 MAT(1, 2, 3, 4, 5, 6, 7, 8);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec4, we are taking col, row order.
        //       That's why Vec4(1, 2, 3, 4) is the transpose and not Vec4(1, 5, 2, 6)

        /// @test Verify matrix transpose is returns a 4x2 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == fgm::Vec4(1, 2, 3, 4));
        static_assert(TRANSPOSE_MAT[1] == fgm::Vec4(5, 6, 7, 8));

        /// @test Verify matrix transpose using static variant returns a 4x2 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = fgm::Mat2x4<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == fgm::Vec4(1, 2, 3, 4));
        static_assert(TRANSPOSE_MAT_STATIC[1] == fgm::Vec4(5, 6, 7, 8));

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat2x4Transpose, Returns4x2MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat2x4Transpose, StaticWrapper_Returns4x2MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Mat2x4<TypeParam>::transpose(this->_matrix)); }

/** @} */
