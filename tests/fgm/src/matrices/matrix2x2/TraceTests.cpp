/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2Trace: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _mat;
    T _expectedSum;

    void SetUp() override
    {
        _mat         = { fgm::Vector2{ T(5.1234523151234), T(1.2521412341253) },
                         fgm::Vector2{ T(8.1234983217498234), T(3.12348219341342) } };
        _expectedSum = T(8.24693450853682);
    }
};
/** @brief Test fixtures for @ref fgm::Matrix2 trace operation, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2Trace, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Trace
 * @{
 */

/** @brief Verify that the matrix trace operation is available at compile time. */
namespace
{
    constexpr fgm::Matrix2 MAT(3, 2, 5, 7);
    static_assert(MAT.trace() == 10);                   // Member function
    static_assert(fgm::Matrix2<int>::trace(MAT) == 10); // Static function
} // namespace


/** @brief Verify that trace of a 2D matrix returns the sum of diagonal elements. */
TYPED_TEST(Matrix2Trace, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


/** @brief Verify that trace of a 2D matrix using static variant returns the sum of diagonal elements. */
TYPED_TEST(Matrix2Trace, StaticWrapper_ReturnsSumOfDiagonalElements)
{
    EXPECT_MAG_EQ(this->_expectedSum, fgm::Matrix2<TypeParam>::trace(this->_mat));
}

/** @} */
