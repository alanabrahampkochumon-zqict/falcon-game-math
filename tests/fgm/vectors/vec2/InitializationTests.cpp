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



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_wrapper
    {

        /// @test Verify that Vec2 can be initialized with parameters at compile time.
        constexpr fgm::Vec2 SCALAR_INIT_VEC(1, 2);
        static_assert(SCALAR_INIT_VEC.x() == 1);
        static_assert(SCALAR_INIT_VEC.y() == 2);

        /// @test Verify that Vec2 can be initialized using braced initialization at compile time.
        constexpr fgm::Vec2<int> BRACED_INIT_VEC{};
        static_assert(BRACED_INIT_VEC.x() == 0);
        static_assert(BRACED_INIT_VEC.y() == 0);

    } // namespace static_wrapper
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

/** @} */
