/**
 * @file NegationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat2x3 negation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Mat2x3TestSetup.h>

/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat2x3Negation: public ::testing::Test
{
protected:
    fgm::Mat2x3<T> _matA, _expectedMat;

    void SetUp() override
    {
        _matA        = { fgm::Vec2<T>(-1, 2), fgm::Vec2<T>(5, 6), fgm::Vec2<T>(0, 15) };
        _expectedMat = { fgm::Vec2<T>(1, -2), fgm::Vec2<T>(-5, -6), fgm::Vec2<T>(0, -15) };
    }
};
/** @brief Test fixture for @ref fgm::Mat2x3 negation, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Mat2x3Negation, SupportedSignedArithmeticTypes);



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
    constexpr fgm::Mat2x3 MAT(1, 2, 3, 4, 5, 6);
    constexpr fgm::Mat2x3 NEG_MAT = -MAT;

    static_assert(NEG_MAT(0, 0) == -MAT(0, 0));
    static_assert(NEG_MAT(0, 1) == -MAT(0, 1));
    static_assert(NEG_MAT(0, 2) == -MAT(0, 2));
    static_assert(NEG_MAT(1, 0) == -MAT(1, 0));
    static_assert(NEG_MAT(1, 1) == -MAT(1, 1));
    static_assert(NEG_MAT(1, 2) == -MAT(1, 2));

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the negation operator perform an element-wise sign inversion.
 */
TYPED_TEST(Mat2x3Negation, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat2x3 negMat = -this->_matA;

    EXPECT_MAT_EQ(this->_expectedMat, negMat);
}

/** @} */
