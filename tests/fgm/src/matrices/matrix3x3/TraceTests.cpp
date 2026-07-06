/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 05, 2026
 *
 * @brief Verify @ref fgm::Matrix3 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix3Trace: public ::testing::Test
{
protected:
    fgm::Matrix3<T> _mat;
    T _expectedSum;

    void SetUp() override
    {
        _mat         = { { T(5.1234523151234), T(1.2521412341253), T(5.481578329483) },
                         { T(8.1234983217498234), T(3.12348219341342), T(1.2138348294893) },
                         { T(1.3482939843), T(12.38424812934), T(7.248381294829) } };
        _expectedSum = T(15.49531580336582);
    }
};
/** @brief Test fixtures for @ref fgm::Matrix3 trace operation, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix3Trace, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Trace
 * @{
 */

/** @brief Verify that the matrix trace operation is available at compile time. */
namespace
{
    constexpr fgm::Matrix3 MAT(3, 2, 5, 7, 5, 12, 8, 11, 12);
    static_assert(MAT.trace() == 20);                   // Member function
    static_assert(fgm::Matrix3<int>::trace(MAT) == 20); // Static function

} // namespace


/** @brief Verify that trace of a 2D matrix returns the sum of diagonal elements. */
TYPED_TEST(Matrix3Trace, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


/** @brief Verify that trace of a 2D matrix using static variant returns the sum of diagonal elements. */
TYPED_TEST(Matrix3Trace, StaticWrapper_ReturnsSumOfDiagonalElements)
{
    EXPECT_MAG_EQ(this->_expectedSum, fgm::Matrix3<TypeParam>::trace(this->_mat));
}

/** @} */
