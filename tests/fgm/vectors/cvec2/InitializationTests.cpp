/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::CVec2 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CVec2TestSetup.h"



/**
 * @addtogroup T_FGM_CVec2_Init
 * @{
 */

namespace
{
    /**************************************
     *           TEST SETUP               *
     **************************************/

    /**
     * @brief Test fixture for @ref CVec2 initialization.
     */
    template <typename>
    class CVec2InitializationTests: public testing::Test
    {};
    TYPED_TEST_SUITE(CVec2InitializationTests, SupportedTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_wrapper
    {

        /// @test Verify that CVec2 can be initialized with parameters at compile time.
        constexpr fgm::CVec2 SCALAR_INIT_VEC(1, 2);
        static_assert(SCALAR_INIT_VEC.x() == 1);
        static_assert(SCALAR_INIT_VEC.y() == 2);

        /// @test Verify that CVec2 can be initialized using braced initialization at compile time.
        constexpr fgm::CVec2<int> BRACED_INIT_VEC{};
        static_assert(BRACED_INIT_VEC.x() == 0);
        static_assert(BRACED_INIT_VEC.y() == 0);

    } // namespace static_wrapper
} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(CVec2InitializationTests, EmptyCtor_InitializesZeroVector)
{
    const fgm::CVec2<TypeParam> vec{};
    EXPECT_VEC_ZERO(vec);
}


TYPED_TEST(CVec2InitializationTests, Ctor_ParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);

    const fgm::CVec2<TypeParam> vec(a, b);
    EXPECT_VEC_CONTAINS(vec, a, b);
}

/** @} */
