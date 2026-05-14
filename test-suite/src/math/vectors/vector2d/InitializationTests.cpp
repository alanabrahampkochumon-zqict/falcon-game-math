/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector2D initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector2DInitialization: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Vector2D initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(Vector2DInitialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Vec2_Init
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that vector can be instantiated during compile time. */
namespace
{
    constexpr fgm::Vector2D vec1(1, 2);
    constexpr fgm::Vector2D<int> vec2;

    static_assert(vec1.x() == 1);
    static_assert(vec1.y() == 2);

    static_assert(vec2.x() == 0);
    static_assert(vec2.y() == 0);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vector2DInitialization, EmptyConstructorInitializesZeroVector)
{
    const fgm::Vector2D<TypeParam> vec;

    EXPECT_VEC_ZERO(vec);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vector2DInitialization, ConstructorParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);

    const fgm::Vector2D<TypeParam> vec(a, b);

    EXPECT_VEC_CONTAINS(vec, a, b);
}

/** @} */
