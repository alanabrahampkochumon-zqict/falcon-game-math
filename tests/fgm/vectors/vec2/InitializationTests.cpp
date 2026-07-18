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



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vec2Initialization: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Vec2 initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(Vec2Initialization, SupportedTypes);



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
    constexpr fgm::Vec2 vecA(1, 2);
    constexpr fgm::Vec2<int> vecB{};

    static_assert(vecA.x() == 1);
    static_assert(vecA.y() == 2);

    static_assert(vecB.x() == 0);
    static_assert(vecB.y() == 0);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vec2Initialization, EmptyConstructorInitializesZeroVector)
{
    const fgm::Vec2<TypeParam> vec{};

    EXPECT_VEC_ZERO(vec);
}


/** @brief Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vec2Initialization, ConstructorParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);

    const fgm::Vec2<TypeParam> vec(a, b);

    EXPECT_VEC_CONTAINS(vec, a, b);
}

/** @} */
