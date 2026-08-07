/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 Reflection Factory.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2ReflectionFactoryTests: public testing::Test
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
    TYPED_TEST_SUITE(Mat2ReflectionFactoryTests, SupportedSignedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that the reflection factory for x-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_X = fgm::Mat2<int>::makeReflection<fgm::reflect::X>();
        static_assert(REFLECTION_MAT_X(0, 0) == 1);
        static_assert(REFLECTION_MAT_X(0, 1) == 0);
        static_assert(REFLECTION_MAT_X(1, 0) == 0);
        static_assert(REFLECTION_MAT_X(1, 1) == -1);


        /// @test Verify that the reflection factory for y-axis return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_Y = fgm::Mat2<int>::makeReflection<fgm::reflect::Y>();
        static_assert(REFLECTION_MAT_Y(0, 0) == -1);
        static_assert(REFLECTION_MAT_Y(0, 1) == 0);
        static_assert(REFLECTION_MAT_Y(1, 0) == 0);
        static_assert(REFLECTION_MAT_Y(1, 1) == 1);


        /// @test Verify that the reflection factory for origin return a valid matrix at compile time.
        constexpr auto REFLECTION_MAT_ORIGIN = fgm::Mat2<int>::makeReflection<fgm::reflect::ORIGIN>();
        static_assert(REFLECTION_MAT_ORIGIN(0, 0) == -1);
        static_assert(REFLECTION_MAT_ORIGIN(0, 1) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(1, 0) == 0);
        static_assert(REFLECTION_MAT_ORIGIN(1, 1) == -1);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2ReflectionFactoryTests, X_ReturnsMatrixWithNegatedY)
{ EXPECT_MAT_EQ(this->_expectedReflectionX, fgm::Mat2<TypeParam>::template makeReflection<fgm::reflect::X>()); }


TYPED_TEST(Mat2ReflectionFactoryTests, Y_ReturnsMatrixWithNegatedX)
{ EXPECT_MAT_EQ(this->_expectedReflectionY, fgm::Mat2<TypeParam>::template makeReflection<fgm::reflect::Y>()); }


TYPED_TEST(Mat2ReflectionFactoryTests, Origin_ReturnsMatrixWithNegatedXY)
{
    EXPECT_MAT_EQ(this->_expectedReflectionOrigin,
                  fgm::Mat2<TypeParam>::template makeReflection<fgm::reflect::ORIGIN>());
}


/** @} */
