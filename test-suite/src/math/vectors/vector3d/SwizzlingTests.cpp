/**
 * @file Swizzling.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verifies @ref fgm::Vector3D swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



/**
 * @brief Test fixture for @ref fgm::Vector3D swizzling,
 *        for verifying swizzling across different types.
 */
template <typename T>
class Vector3DSwizzlingTest: public ::testing::Test
{};
TYPED_TEST_SUITE(Vector3DSwizzlingTest, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Vec4_Swizzle
 * @{
 */


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector3D returns correct vectors
 *        for axis coordinates.
 */
namespace
{
    constexpr fgm::Vector3D VECTOR(1.0f, 2.0f, 3.0f);

    using namespace fgm::axis;

    static_assert(VECTOR.swizzle<X, Y, Z>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, Y, Z>().y() == 2.0f);
    static_assert(VECTOR.swizzle<X, Y, Z>().z() == 3.0f);

    static_assert(VECTOR.swizzle<X, Y, Y>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, Y, Y>().y() == 2.0f);
    static_assert(VECTOR.swizzle<X, Y, Y>().z() == 2.0f);

    static_assert(VECTOR.swizzle<X, X, Y>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, Y>().y() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, Y>().z() == 2.0f);

    static_assert(VECTOR.swizzle<X, X, X>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X>().y() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X>().z() == 1.0f);

    static_assert(VECTOR.swizzle<Y, Y, Z>().x() == 2.0f);
    static_assert(VECTOR.swizzle<Y, Y, Z>().y() == 2.0f);
    static_assert(VECTOR.swizzle<Y, Y, Z>().z() == 3.0f);

    static_assert(VECTOR.swizzle<Z, Y, X>().x() == 3.0f);
    static_assert(VECTOR.swizzle<Z, Y, X>().y() == 2.0f);
    static_assert(VECTOR.swizzle<Z, Y, X>().z() == 1.0f);

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
    static_assert(VECTOR.swizzle<Z>() == 3.0f);

} // namespace


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector3D returns correct vectors
 *        for color coordinates.
 */
namespace
{
    using namespace fgm::colors;

    static_assert(VECTOR.swizzle<R, G, B>().r() == 1.0f);
    static_assert(VECTOR.swizzle<R, G, B>().g() == 2.0f);
    static_assert(VECTOR.swizzle<R, G, B>().b() == 3.0f);

    static_assert(VECTOR.swizzle<B, G, R>().r() == 3.0f);
    static_assert(VECTOR.swizzle<B, G, R>().g() == 2.0f);
    static_assert(VECTOR.swizzle<B, G, R>().b() == 1.0f);

    static_assert(VECTOR.swizzle<R, G>().r() == 1.0f);
    static_assert(VECTOR.swizzle<R, G>().g() == 2.0f);

    static_assert(VECTOR.swizzle<G, R>().r() == 2.0f);
    static_assert(VECTOR.swizzle<G, R>().g() == 1.0f);

    static_assert(VECTOR.swizzle<R>() == 1.0f);
    static_assert(VECTOR.swizzle<G>() == 2.0f);
    static_assert(VECTOR.swizzle<B>() == 3.0f);

} // namespace


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector3D returns correct vectors
 *        for STP coordinates.
 */
namespace
{
    using namespace fgm::stp;

    static_assert(VECTOR.swizzle<S, T, P>().s() == 1.0f);
    static_assert(VECTOR.swizzle<S, T, P>().t() == 2.0f);
    static_assert(VECTOR.swizzle<S, T, P>().p() == 3.0f);

    static_assert(VECTOR.swizzle<P, T, S>().s() == 3.0f);
    static_assert(VECTOR.swizzle<P, T, S>().t() == 2.0f);
    static_assert(VECTOR.swizzle<P, T, S>().p() == 1.0f);

    static_assert(VECTOR.swizzle<S, T>().s() == 1.0f);
    static_assert(VECTOR.swizzle<S, T>().t() == 2.0f);

    static_assert(VECTOR.swizzle<T, S>().s() == 2.0f);
    static_assert(VECTOR.swizzle<T, S>().t() == 1.0f);

    static_assert(VECTOR.swizzle<S>() == 1.0f);
    static_assert(VECTOR.swizzle<T>() == 2.0f);
    static_assert(VECTOR.swizzle<P>() == 3.0f);

} // namespace


/** @brief Verify that swizzling returns shuffled vector across different numeric. */
TYPED_TEST(Vector3DSwizzlingTest, SwizzlingWorksAcrossDifferentTypes)
{
    constexpr fgm::Vector3D vector(TypeParam(1), TypeParam(2), TypeParam(3));
    constexpr fgm::Vector3D expectedSwizzling(TypeParam(3), TypeParam(2), TypeParam(1));
    
    constexpr auto swizzledVector = vector.template swizzle<Z, Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @brief Verify that swizzling returns shuffled vector for boolean vector. */
TEST(Vector3DSwizzlingTest, SwizzlingWorksForBooleanVector)
{
    constexpr fgm::Vector3D vector(true, false, false);
    constexpr fgm::Vector3D expectedSwizzling(false, false, true);

    constexpr auto swizzledVector = vector.swizzle<Z, Y, X>();

    EXPECT_VEC_EQ(expectedSwizzling, swizzledVector);
}


/** @} */