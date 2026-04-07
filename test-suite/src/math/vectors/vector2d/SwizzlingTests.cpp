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
 * @brief Statically verify that the swizzle variadic template
 *        returns correct vectors for spatial axis coordinates.
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
 * @brief Statically verify that the swizzle variadic template
 *        returns correct vectors for color coordinates.
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
 * @brief Statically verify that the swizzle variadic template
 *        returns correct vectors for STP coordinates.
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


/**
 * @brief Statically verify that the static variant of swizzle variadic template
 *        returns correct vectors for spatial axis coordinates.
 */
namespace
{
    using namespace fgm::axis;

    static_assert(fgm::Vector2D<float>::swizzle<X, Y>(VECTOR).x() == 1.0f);
    static_assert(fgm::Vector2D<float>::swizzle<X, Y>(VECTOR).y() == 2.0f);

    static_assert(fgm::Vector2D<float>::swizzle<X, X>(VECTOR).x() == 1.0f);
    static_assert(fgm::Vector2D<float>::swizzle<X, X>(VECTOR).y() == 1.0f);

    static_assert(fgm::Vector2D<float>::swizzle<Y, Y>(VECTOR).x() == 2.0f);
    static_assert(fgm::Vector2D<float>::swizzle<Y, Y>(VECTOR).y() == 2.0f);

    static_assert(fgm::Vector2D<float>::swizzle<Y, X>(VECTOR).x() == 2.0f);
    static_assert(fgm::Vector2D<float>::swizzle<Y, X>(VECTOR).y() == 1.0f);

    static_assert(fgm::Vector2D<float>::swizzle<X>(VECTOR) == 1.0f);
    static_assert(fgm::Vector2D<float>::swizzle<Y>(VECTOR) == 2.0f);

} // namespace


/**
 * @brief Statically verify that the static variant of swizzle variadic template
 *        returns correct vectors for color coordinates.
 */
namespace
{
    using namespace fgm::colors;

    static_assert(fgm::Vector2D<float>::swizzle<R, G>(VECTOR).r() == 1.0f);
    static_assert(fgm::Vector2D<float>::swizzle<R, G>(VECTOR).g() == 2.0f);

    static_assert(fgm::Vector2D<float>::swizzle<G, R>(VECTOR).r() == 2.0f);
    static_assert(fgm::Vector2D<float>::swizzle<G, R>(VECTOR).g() == 1.0f);

} // namespace


/**
 * @brief Statically verify that the static variant of swizzle variadic template
 *        returns correct vectors for STP coordinates.
 */
namespace
{
    using namespace fgm::stp;

    static_assert(fgm::Vector2D<float>::swizzle<S, T>(VECTOR).s() == 1.0f);
    static_assert(fgm::Vector2D<float>::swizzle<S, T>(VECTOR).t() == 2.0f);

    static_assert(fgm::Vector2D<float>::swizzle<T, S>(VECTOR).s() == 2.0f);
    static_assert(fgm::Vector2D<float>::swizzle<T, S>(VECTOR).t() == 1.0f);

    static_assert(fgm::Vector2D<float>::swizzle<S>(VECTOR) == 1.0f);
    static_assert(fgm::Vector2D<float>::swizzle<T>(VECTOR) == 2.0f);

} // namespace


/**
 * @brief Verify that swizzling using static variant of @ref fgm::Vector2D::swizzle
 *        returns shuffled vector across different numeric.
 */
TYPED_TEST(Vector2DSwizzlingTest, StaticWrapper_SwizzlingWorksAcrossDifferentTypes)
{
    constexpr fgm::Vector2D vector(TypeParam(1), TypeParam(2));
    constexpr fgm::Vector2D expectedSwizzling(TypeParam(2), TypeParam(1));

    constexpr auto swizzledVector = fgm::Vector2D<TypeParam>::template swizzle<Y, X>(vector);

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/**
 * @brief Verify that swizzling using static variant of @ref fgm::Vector2D::swizzle
 *        returns shuffled vector for boolean vector.
 */
TEST(Vector2DSwizzlingTest, StaticWrapper_SwizzlingWorksForBooleanVector)
{
    constexpr fgm::Vector2D vector(true, false);
    constexpr fgm::Vector2D expectedSwizzling(false, true);

    constexpr auto swizzledVector = fgm::Vector2D<bool>::template swizzle<Y, X>(vector);

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @} */