/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref fgm::Mat2 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



template <typename T>
class Mat2Trace: public ::testing::Test
{
protected:
    fgm::Mat2<T> _mat;
    T _expectedSum;

    void SetUp() override
    {
        _mat         = { fgm::Vec2{ T(5.1234523151234), T(1.2521412341253) },
                         fgm::Vec2{ T(8.1234983217498234), T(3.12348219341342) } };
        _expectedSum = T(8.24693450853682);
    }
};
/** @brief Test fixtures for @ref fgm::Mat2 trace operation, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat2Trace, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Trace
 * @{
 */

/** @brief Verify that the matrix trace operation is available at compile time. */
namespace
{
    constexpr fgm::Mat2 MAT(3, 2, 5, 7);
    static_assert(MAT.trace() == 10);                   // Member function
    static_assert(fgm::Mat2<int>::trace(MAT) == 10); // Static function
} // namespace


/** @brief Verify that trace of a 2D matrix returns the sum of diagonal elements. */
TYPED_TEST(Mat2Trace, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


/** @brief Verify that trace of a 2D matrix using static variant returns the sum of diagonal elements. */
TYPED_TEST(Mat2Trace, StaticWrapper_ReturnsSumOfDiagonalElements)
{
    EXPECT_MAG_EQ(this->_expectedSum, fgm::Mat2<TypeParam>::trace(this->_mat));
}

/** @} */
