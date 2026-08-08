/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 27, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"

#include <fgm/matrices/Mat2x3.h>


/**
 * @addtogroup T_FGM_Mat3x2_Transpose
 * @{
 */

namespace
{
    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3x2 matrix transposition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat3x2TransposeTests: public ::testing::Test
    {
    protected:
        fgm::Mat3x2<T> _matrix;
        fgm::Mat2x3<T> _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { fgm::Vec3{ T(1), T(2), T(3) }, fgm::Vec3{ T(4), T(5), T(6) } };
            _expectedTranspose = { fgm::Vec2{ T(1), T(4) }, fgm::Vec2{ T(2), T(5) }, fgm::Vec2{ T(3), T(6) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x2TransposeTests, SupportedTypes);




    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3x2 MAT(1, 2, 3, 4, 5, 6);

        // NOTE: The matrix takes elements in row, col order
        //       but when compared with Vec2, we are taking col, row order.
        //       That's why Vec2(1, 2) is the transpose and not Vec2(1, 3)

        /// @test Verify matrix transpose is returns a 2x3 matrix with swapped rows and
        ///       columns at compile time.
        constexpr auto TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT[0] == fgm::Vec2(1, 2));
        static_assert(TRANSPOSE_MAT[1] == fgm::Vec2(3, 4));
        static_assert(TRANSPOSE_MAT[2] == fgm::Vec2(5, 6));

        /// @test Verify matrix transpose using static variant returns a 2x3 matrix with
        ///       swapped rows and columns at compile time.
        constexpr auto TRANSPOSE_MAT_STATIC = fgm::Mat3x2<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_STATIC[0] == fgm::Vec2(1, 2));
        static_assert(TRANSPOSE_MAT_STATIC[1] == fgm::Vec2(3, 4));
        static_assert(TRANSPOSE_MAT_STATIC[2] == fgm::Vec2(5, 6));

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x2TransposeTests, Returns2x3MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat3x2TransposeTests, StaticWrapper_Returns2x3MatrixWithRowAndColumnElementsExchanged)
{ EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Mat3x2<TypeParam>::transpose(this->_matrix)); }

/** @} */
