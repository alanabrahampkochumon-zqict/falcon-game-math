/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2D trace operation logic.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix2DTrace: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat;
    T _expectedSum;

    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(5.1234523151234), T(1.2521412341253) }, fgm::Vector2D{ T(8.1234983217498234), T(3.12348219341342) } };
        _expectedSum = T(8.24693450853682);
    }
};
/** @brief Test fixtures for @ref fgm::Matrix2D trace operation, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DTrace, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Trace
 * @{
 */

/** @brief Verify that trace of a 2D matrix returns the sum of diagonal elements. */
TYPED_TEST(Matrix2DTrace, ReturnsSumOfDiagonalElements)
{ EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


/** @brief Verify that trace of a 2D matrix using static variant returns the sum of diagonal elements. */
TYPED_TEST(Matrix2DTrace, StaticWrapper_ReturnsSumOfDiagonalElements)
{
    EXPECT_MAG_EQ(this->_expectedSum, fgm::Matrix2D<TypeParam>::trace(this->_mat));
}

/** @} */