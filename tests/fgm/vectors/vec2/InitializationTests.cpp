/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec2 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



/**
 * @addtogroup T_FGM_Vec2_Init
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref Vec2 initialization.
     */
    template <typename>
    class Vec2InitializationTests: public testing::Test
    {};
    TYPED_TEST_SUITE(Vec2InitializationTests, SupportedTypes);
} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Vec2InitializationTests, EmptyCtor_InitializesZeroVector)
{
    const fgm::Vec2<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


TYPED_TEST(Vec2InitializationTests, Ctor_ParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);

    const fgm::Vec2<TypeParam> vec(a, b);
    EXPECT_VEC_CONTAINS(vec, a, b);
}


TYPED_TEST(Vec2InitializationTests, Ctor_SingleParameterInitializesVector)
{
    const auto a = static_cast<TypeParam>(3);
    const fgm::Vec2<TypeParam> vec(a);
    EXPECT_VEC_CONTAINS(vec, a, a);
}

/** @} */
