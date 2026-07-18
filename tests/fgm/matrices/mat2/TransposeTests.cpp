/**
 * @file TransposeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Mat2 transpose logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *              SETUP                 *
 *                                    *
 **************************************/

template <typename T>
class Mat2Transpose: public ::testing::Test
{
protected:
    fgm::Mat2<T> _matrix, _expectedTranspose;

    void SetUp() override
    {
        _matrix            = { fgm::Vec2{ T(1), T(2) }, fgm::Vec2{ T(3), T(4) } };
        _expectedTranspose = { fgm::Vec2{ T(1), T(3) }, fgm::Vec2{ T(2), T(4) } };
    }
};
/** @brief Test fixture for @ref fgm::Mat2 transpose, parameterized @ref SupportedTypes */
TYPED_TEST_SUITE(Mat2Transpose, SupportedTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Transpose
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix transpose is available at compile time. */
namespace
{
    constexpr fgm::Mat2 MAT(1, 2, 3, 4);

    // Verify matrix transpose (member function)
    constexpr fgm::Mat2 TRANSPOSE_MAT = MAT.transpose();
    static_assert(TRANSPOSE_MAT(0, 0) == 1);
    static_assert(TRANSPOSE_MAT(0, 1) == 3);
    static_assert(TRANSPOSE_MAT(1, 0) == 2);
    static_assert(TRANSPOSE_MAT(1, 1) == 4);

    // Verify matrix transpose (static function)
    constexpr fgm::Mat2 TRANSPOSE_MAT_S = fgm::Mat2<int>::transpose(MAT);
    static_assert(TRANSPOSE_MAT_S(0, 0) == 1);
    static_assert(TRANSPOSE_MAT_S(0, 1) == 3);
    static_assert(TRANSPOSE_MAT_S(1, 0) == 2);
    static_assert(TRANSPOSE_MAT_S(1, 1) == 4);
} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that transposing a matrix exchanges row and column elements and returns a new matrix. */
TYPED_TEST(Mat2Transpose, ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedTranspose, this->_matrix.transpose());
}


/**
 * @brief Verify that transposing a matrix using static variant of @ref fgm::Mat2::transpose exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Mat2Transpose, StaticWrapper_ExchangesRowsAndColumnElements)
{
    EXPECT_MAT_EQ(this->_expectedTranspose, fgm::Mat2<TypeParam>::transpose(this->_matrix));
}

/** @} */
