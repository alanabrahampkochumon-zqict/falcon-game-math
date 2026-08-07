/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Mat2 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transpose
 * @{
 */

namespace
{


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 Transpose.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2TransposeTests: public ::testing::Test
    {
    protected:
        fgm::Mat2<T> _matrix, _expectedTranspose;

        void SetUp() override
        {
            _matrix            = { fgm::Vec2{ T(1), T(2) }, fgm::Vec2{ T(3), T(4) } };
            _expectedTranspose = { fgm::Vec2{ T(1), T(3) }, fgm::Vec2{ T(2), T(4) } };
        }
    };
    TYPED_TEST_SUITE(Mat2TransposeTests, SupportedTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2 MAT(1, 2, 3, 4);

        /** @test Verify that matrix transpose returns a valid matrix at compile time. */
        constexpr fgm::Mat2 TRANSPOSE_MAT = MAT.transpose();
        static_assert(TRANSPOSE_MAT(0, 0) == 1);
        static_assert(TRANSPOSE_MAT(0, 1) == 3);
        static_assert(TRANSPOSE_MAT(1, 0) == 2);
        static_assert(TRANSPOSE_MAT(1, 1) == 4);

        /** @test Verify that matrix transpose (static wrapper) returns a valid matrix at compile time. */
        constexpr fgm::Mat2 TRANSPOSE_MAT_S = fgm::Mat2<int>::transpose(MAT);
        static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
        static_assert(TRANSPOSE_MAT_S(0, 1) == 3);
        static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
        static_assert(TRANSPOSE_MAT_S(1, 1) == 4);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2TransposeTests, ReturnsMatrixWithExchangedRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose()); }


TYPED_TEST(Mat2TransposeTests, StaticWrapper_ReturnsMatrixWithExchangedRowsAndColumnElements)
{ EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Mat2<TypeParam>::transpose(this->_matrix)); }

/** @} */
