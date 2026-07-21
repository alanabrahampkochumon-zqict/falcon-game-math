/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x2 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat4x2TestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat4x2Negation: public ::testing::Test
{
protected:
    fgm::Mat4x2<T> _matA, _expectedMat;

    void SetUp() override
    {
        _matA        = { fgm::Vec4<T>(-1, 2, 3, -4), fgm::Vec4<T>(5, 6, 7, 8) };
        _expectedMat = { fgm::Vec4<T>(1, -2, -3, 4), fgm::Vec4<T>(-5, -6, -7, -8) };
    }
};
/** @brief Test fixture for @ref fgm::Mat4x2 negation, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Mat4x2Negation, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Negation
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix negation operations are available at compile time. */
namespace
{
    constexpr fgm::Mat4x2 MAT(1, 2, 3, 4, 5, 6, 7, 8);
    constexpr fgm::Mat4x2 NEG_MAT = -MAT;

    static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
    static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
    static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
    static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
    static_assert(NEG_MAT(2, 0) == -MAT(2, 0));
    static_assert(NEG_MAT(2, 1) == -MAT(2, 1));
    static_assert(NEG_MAT(3, 0) == -MAT(3, 0));
    static_assert(NEG_MAT(3, 1) == -MAT(3, 1));

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the negation operator perform an element-wise sign inversion.
 */
TYPED_TEST(Mat4x2Negation, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat4x2 negMat = -this->_matA;

    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
