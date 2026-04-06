/**
 * @file SwizzlingTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verifies @ref fgm::Vector2D swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**
 * @brief Test fixture for @ref fgm::Vector2D swizzling,
 *        for verifying swizzling across different types.
 */
template <typename T>
class Vector2DSwizzlingTest: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector2DSwizzlingTest, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Vec2_Swizzle
 * @{
 */


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector2D returns correct vectors
 *        for axis coordinates.
 */
namespace
{
    constexpr fgm::Vector2D VECTOR(1.0f, 2.0f);

    using namespace fgm::axis;

    static_assert(VECTOR.swizzle<X, Y>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, Y>().y() == 2.0f);

    static_assert(VECTOR.swizzle<X, X>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X>().y() == 1.0f);

    static_assert(VECTOR.swizzle<Y, Y>().x() == 2.0f);
    static_assert(VECTOR.swizzle<Y, Y>().y() == 2.0f);

    static_assert(VECTOR.swizzle<Y, X>().x() == 2.0f);
    static_assert(VECTOR.swizzle<Y, X>().y() == 1.0f);

    static_assert(VECTOR.swizzle<X>() == 1.0f);
    static_assert(VECTOR.swizzle<Y>() == 2.0f);

} // namespace


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector2D returns correct vectors
 *        for color coordinates.
 */
namespace
{
    using namespace fgm::colors;

    static_assert(VECTOR.swizzle<R, G>().r() == 1.0f);
    static_assert(VECTOR.swizzle<R, G>().g() == 2.0f);

    static_assert(VECTOR.swizzle<G, R>().r() == 2.0f);
    static_assert(VECTOR.swizzle<G, R>().g() == 1.0f);

} // namespace


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector2D returns correct vectors
 *        for STP coordinates.
 */
namespace
{
    using namespace fgm::stp;

    static_assert(VECTOR.swizzle<S, T>().s() == 1.0f);
    static_assert(VECTOR.swizzle<S, T>().t() == 2.0f);

    static_assert(VECTOR.swizzle<T, S>().s() == 2.0f);
    static_assert(VECTOR.swizzle<T, S>().t() == 1.0f);

    static_assert(VECTOR.swizzle<S>() == 1.0f);
    static_assert(VECTOR.swizzle<T>() == 2.0f);

} // namespace


/** @brief Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vector2DSwizzlingTest, SwizzlingWorksAcrossDifferentTypes)
{
    constexpr fgm::Vector2D vector(TypeParam(1), TypeParam(2));
    constexpr fgm::Vector2D expectedSwizzling(TypeParam(2), TypeParam(1));
    
    constexpr auto swizzledVector = vector.template swizzle<Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @brief Verify that swizzling returns shuffled vector for boolean vector. */
TEST(Vector2DSwizzlingTest, SwizzlingWorksForBooleanVector)
{
    constexpr fgm::Vector2D vector(true, false);
    constexpr fgm::Vector2D expectedSwizzling(false, true);

    constexpr auto swizzledVector = vector.swizzle<Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @} */