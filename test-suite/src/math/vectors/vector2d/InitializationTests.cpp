/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verifies @ref fgm::Vector2D initialization logic.
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
/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vector2DInitialization, EmptyConstructorInitializesZeroVector)
{
    constexpr fgm::Vector2D<TypeParam> vec;

    EXPECT_VEC_ZERO(vec);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vector2DInitialization, ConstructorParametersInitializesVector)
{
    constexpr TypeParam a = static_cast<TypeParam>(3);
    constexpr TypeParam b = static_cast<TypeParam>(1);

    constexpr fgm::Vector2D<TypeParam> vec(a, b);

    EXPECT_VEC_CONTAINS(vec, a, b);
}
