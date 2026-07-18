/**
 * @file TraceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref fgm::Mat4 trace operation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Mat4Trace: public ::testing::Test
{
protected:
    fgm::Mat4<T> _mat;
    T _expectedSum;

    void SetUp() override
    {
        _mat = {
            { T(5.1234523151234), T(1.2521412341253), T(5.481578329483), T(5.123891234) },
            { T(8.1234983217498234), T(3.12348219341342), T(1.2138348294893), T(7.9123048192) },
            { T(1.3482939843), T(12.38424812934), T(7.248381294829), T(1.2839812348) },
            { T(3.5382939843), T(1.38324812934), T(1.1232194829), T(5.139832212348) },
        };
        _expectedSum = T(20.63514801571382);
    }
};
/** @brief Test fixtures for @ref fgm::Mat4 trace operation, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Mat4Trace, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Trace
 * @{
 */

/** @brief Verify that the matrix trace operation is available at compile time. */
namespace
{
    constexpr fgm::Mat4 MAT(3, 2, 5, 7, 5, 12, 8, 11, 12, 13, 14, 15, 16, 17, 18, 19);
    static_assert(MAT.trace() == 48);                   // Member function
    static_assert(fgm::Mat4<int>::trace(MAT) == 48); // Static function

} // namespace


/** @brief Verify that trace of a 2D matrix returns the sum of diagonal elements. */
TYPED_TEST(Mat4Trace, ReturnsSumOfDiagonalElements) { EXPECT_MAG_EQ(this->_expectedSum, this->_mat.trace()); }


/** @brief Verify that trace of a 2D matrix using static variant returns the sum of diagonal elements. */
TYPED_TEST(Mat4Trace, StaticWrapper_ReturnsSumOfDiagonalElements)
{
    EXPECT_MAG_EQ(this->_expectedSum, fgm::Mat4<TypeParam>::trace(this->_mat));
}

/** @} */
