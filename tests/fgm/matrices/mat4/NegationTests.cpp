/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat4TestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat4Negation: public ::testing::Test
{
protected:
    fgm::Mat4<T> _matA, _expectedMat;

    void SetUp() override
    {
        _matA        = { fgm::Vec4<T>(-1, 2, 3, -4), fgm::Vec4<T>(5, 6, 7, 8), fgm::Vec4<T>(0, 15, -12, 22),
                         fgm::Vec4<T>(1, 3, 1, 6) };
        _expectedMat = { fgm::Vec4<T>(1, -2, -3, 4), fgm::Vec4<T>(-5, -6, -7, -8), fgm::Vec4<T>(0, -15, 12, -22),
                         fgm::Vec4<T>(-1, -3, -1, -6) };
    }
};
/** @brief Test fixture for @ref fgm::Mat4 negation, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Mat4Negation, SupportedSignedArithmeticTypes);



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
    constexpr fgm::Mat4 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    constexpr fgm::Mat4 NEG_MAT = -MAT;

    static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
    static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
    static_assert(NEG_MAT(0, 2) == -MAT(0, 2));
    static_assert(NEG_MAT(0, 3) == -MAT(0, 3));
    static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
    static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
    static_assert(NEG_MAT(1, 2) == -MAT(1, 2));
    static_assert(NEG_MAT(1, 3) == -MAT(1, 3));
    static_assert(NEG_MAT(2, 0) == -MAT(2, 0));
    static_assert(NEG_MAT(2, 1) == -MAT(2, 1));
    static_assert(NEG_MAT(2, 2) == -MAT(2, 2));
    static_assert(NEG_MAT(2, 3) == -MAT(2, 3));
    static_assert(NEG_MAT(3, 0) == -MAT(3, 0));
    static_assert(NEG_MAT(3, 1) == -MAT(3, 1));
    static_assert(NEG_MAT(3, 2) == -MAT(3, 2));
    static_assert(NEG_MAT(3, 3) == -MAT(3, 3));

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the negation operator perform an element-wise sign inversion.
 */
TYPED_TEST(Mat4Negation, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat4 negMat = -this->_matA;

    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
