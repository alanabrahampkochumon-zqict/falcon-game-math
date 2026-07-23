/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */
template <typename T>
class Mat2Reflection: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedReflectionX, _expectedReflectionY, _expectedReflectionOrigin;

    void SetUp() override
    {
        _expectedReflectionX      = { fgm::Vec2{ T(1), T(0) }, fgm::Vec2{ T(0), T(-1) } };
        _expectedReflectionY      = { fgm::Vec2{ T(-1), T(0) }, fgm::Vec2{ T(0), T(1) } };
        _expectedReflectionOrigin = { fgm::Vec2{ T(-1), T(0) }, fgm::Vec2{ T(0), T(-1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 reflection across coordinate axis and origin
 *        parameterized @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2Reflection, SupportedSignedArithmeticTypes);


/** @brief Verify that reflection transform factory is available at compile time.  */
namespace
{
    // Reflection across x-axis
    constexpr auto REFLECTION_MAT_X = fgm::Mat2<int>::makeReflection<fgm::reflect::X>();
    static_assert(REFLECTION_MAT_X(0, 0) == 1);
    static_assert(REFLECTION_MAT_X(0, 1) == 0);
    static_assert(REFLECTION_MAT_X(1, 0) == 0);
    static_assert(REFLECTION_MAT_X(1, 1) == -1);


    // Reflection across y-axis
    constexpr auto REFLECTION_MAT_Y = fgm::Mat2<int>::makeReflection<fgm::reflect::Y>();
    static_assert(REFLECTION_MAT_Y(0, 0) == -1);
    static_assert(REFLECTION_MAT_Y(0, 1) == 0);
    static_assert(REFLECTION_MAT_Y(1, 0) == 0);
    static_assert(REFLECTION_MAT_Y(1, 1) == 1);


    // Reflection across x-axis
    constexpr auto REFLECTION_MAT_ORIGIN = fgm::Mat2<int>::makeReflection<fgm::reflect::ORIGIN>();
    static_assert(REFLECTION_MAT_ORIGIN(0, 0) == -1);
    static_assert(REFLECTION_MAT_ORIGIN(0, 1) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(1, 0) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(1, 1) == -1);

} // namespace



/** @brief Verify that reflection transformation factory for x-axis returns a matrix with negated y value. */
TYPED_TEST(Mat2Reflection, X_ReturnsMatrixWithNegatedY)
{ EXPECT_MAT_EQ(this->_expectedReflectionX, fgm::Mat2<TypeParam>::template makeReflection<fgm::reflect::X>()); }


/** @brief Verify that reflection transformation factory for y-axis returns a matrix with negated x value. */
TYPED_TEST(Mat2Reflection, Y_ReturnsMatrixWithNegatedX)
{ EXPECT_MAT_EQ(this->_expectedReflectionY, fgm::Mat2<TypeParam>::template makeReflection<fgm::reflect::Y>()); }

/** @brief Verify that reflection transformation factory for origin returns a matrix with negated x, y values. */
TYPED_TEST(Mat2Reflection, Origin_ReturnsMatrixWithNegatedXY)
{
    EXPECT_MAT_EQ(this->_expectedReflectionOrigin,
                  fgm::Mat2<TypeParam>::template makeReflection<fgm::reflect::ORIGIN>());
}


/** @} */
