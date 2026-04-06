/**
 * @file Swizzling.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 06, 2026
 *
 * @brief Verifies @ref fgm::Vector4D swizzling logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"



// template <fgm::Arithmetic T, typename U>
//     requires fgm::Arithmetic<U> || fgm::Vector<U>
// struct Vector4DSwizzlingParams
//{
//     fgm::Vector4D<T> VECTOR;
//     U swizzledResult;
// };
//
///** @brief Test fixture for testing @fgm::Vector4D swizzling, paramterized by @ref Vec
// class Vector4DToVector4DSwizzleTests
//     : public ::testing::TestWithParam<Vector4DSwizzlingParams<float, fgm::Vector4D<float>>>
//{};
//
// class Vector4DToVector3DSwizzleTests
//     : public ::testing::TestWithParam<Vector4DSwizzlingParams<float, fgm::Vector4D<float>>>
//{};
//
// class Vector4DToVector2DSwizzleTests
//     : public ::testing::TestWithParam<Vector4DSwizzlingParams<float, fgm::Vector4D<float>>>
//{};
//
// class Vector4DToScalarSwizzleTests
//     : public ::testing::TestWithParam<Vector4DSwizzlingParams<float, fgm::Vector4D<float>>>
//{};

/**
 * @addtogroup T_FGM_Vec4_Swizzle
 * @{
 */


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector4D returns correct vectors 
 *        for axis coordinates.
 */
namespace
{
    constexpr fgm::Vector4D VECTOR(1.0f, 2.0f, 3.0f, 4.0f);

    using namespace fgm::axis;
    static_assert(VECTOR.swizzle<X, Y, Z, W>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, Y, Z, W>().y() == 2.0f);
    static_assert(VECTOR.swizzle<X, Y, Z, W>().z() == 3.0f);
    static_assert(VECTOR.swizzle<X, Y, Z, W>().w() == 4.0f);

    static_assert(VECTOR.swizzle<X, X, Y, Y>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, Y, Y>().y() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, Y, Y>().z() == 2.0f);
    static_assert(VECTOR.swizzle<X, X, Y, Y>().w() == 2.0f);

    static_assert(VECTOR.swizzle<X, X, X, Y>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X, Y>().y() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X, Y>().z() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X, Y>().w() == 2.0f);

    static_assert(VECTOR.swizzle<X, X, X, X>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X, X>().y() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X, X>().z() == 1.0f);
    static_assert(VECTOR.swizzle<X, X, X, X>().w() == 1.0f);

    static_assert(VECTOR.swizzle<Y, Y, Z, Z>().x() == 2.0f);
    static_assert(VECTOR.swizzle<Y, Y, Z, Z>().y() == 2.0f);
    static_assert(VECTOR.swizzle<Y, Y, Z, Z>().z() == 3.0f);
    static_assert(VECTOR.swizzle<Y, Y, Z, Z>().w() == 3.0f);

    static_assert(VECTOR.swizzle<W, Z, Y, X>().x() == 4.0f);
    static_assert(VECTOR.swizzle<W, Z, Y, X>().y() == 3.0f);
    static_assert(VECTOR.swizzle<W, Z, Y, X>().z() == 2.0f);
    static_assert(VECTOR.swizzle<W, Z, Y, X>().w() == 1.0f);

    static_assert(VECTOR.swizzle<Z, W, Y, X>().x() == 3.0f);
    static_assert(VECTOR.swizzle<Z, W, Y, X>().y() == 4.0f);
    static_assert(VECTOR.swizzle<Z, W, Y, X>().z() == 2.0f);
    static_assert(VECTOR.swizzle<Z, W, Y, X>().w() == 1.0f);

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

    static_assert(VECTOR.swizzle<W, Z, Y>().x() == 4.0f);
    static_assert(VECTOR.swizzle<W, Z, Y>().y() == 3.0f);
    static_assert(VECTOR.swizzle<W, Z, Y>().z() == 2.0f);

    static_assert(VECTOR.swizzle<Z, Y, X>().x() == 3.0f);
    static_assert(VECTOR.swizzle<Z, Y, X>().y() == 2.0f);
    static_assert(VECTOR.swizzle<Z, Y, X>().z() == 1.0f);

    static_assert(VECTOR.swizzle<X, Y>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, Y>().y() == 2.0f);

    static_assert(VECTOR.swizzle<X, X>().x() == 1.0f);
    static_assert(VECTOR.swizzle<X, X>().y() == 1.0f);

    static_assert(VECTOR.swizzle<Y, Y>().x() == 2.0f);
    static_assert(VECTOR.swizzle<Y, Y>().y() == 2.0f);

    static_assert(VECTOR.swizzle<W, Z>().x() == 4.0f);
    static_assert(VECTOR.swizzle<W, Z>().y() == 3.0f);

    static_assert(VECTOR.swizzle<Y, X>().x() == 2.0f);
    static_assert(VECTOR.swizzle<Y, X>().y() == 1.0f);

    static_assert(VECTOR.swizzle<X>() == 1.0f);
    static_assert(VECTOR.swizzle<Y>() == 2.0f);
    static_assert(VECTOR.swizzle<Z>() == 3.0f);
    static_assert(VECTOR.swizzle<W>() == 4.0f);

} // namespace


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector4D returns correct vectors
 *        for color coordinates.
 */
namespace
{
    using namespace fgm::colors;
    static_assert(VECTOR.swizzle<R, G, B, A>().r() == 1.0f);
    static_assert(VECTOR.swizzle<R, G, B, A>().g() == 2.0f);
    static_assert(VECTOR.swizzle<R, G, B, A>().b() == 3.0f);
    static_assert(VECTOR.swizzle<R, G, B, A>().a() == 4.0f);

    static_assert(VECTOR.swizzle<A, B, G, R>().r() == 4.0f);
    static_assert(VECTOR.swizzle<A, B, G, R>().g() == 3.0f);
    static_assert(VECTOR.swizzle<A, B, G, R>().b() == 2.0f);
    static_assert(VECTOR.swizzle<A, B, G, R>().a() == 1.0f);

    static_assert(VECTOR.swizzle<R, G, B>().r() == 1.0f);
    static_assert(VECTOR.swizzle<R, G, B>().g() == 2.0f);
    static_assert(VECTOR.swizzle<R, G, B>().b() == 3.0f);

    static_assert(VECTOR.swizzle<A, B, G>().r() == 4.0f);
    static_assert(VECTOR.swizzle<A, B, G>().g() == 3.0f);
    static_assert(VECTOR.swizzle<A, B, G>().b() == 2.0f);

    static_assert(VECTOR.swizzle<R, G>().r() == 1.0f);
    static_assert(VECTOR.swizzle<R, G>().g() == 2.0f);
    static_assert(VECTOR.swizzle<B, A>().r() == 3.0f);
    static_assert(VECTOR.swizzle<B, A>().g() == 4.0f);

    static_assert(VECTOR.swizzle<A, B>().r() == 4.0f);
    static_assert(VECTOR.swizzle<A, B>().g() == 3.0f);
    static_assert(VECTOR.swizzle<G, R>().r() == 2.0f);
    static_assert(VECTOR.swizzle<G, R>().g() == 1.0f);

    static_assert(VECTOR.swizzle<R>() == 1.0f);
    static_assert(VECTOR.swizzle<G>() == 2.0f);
    static_assert(VECTOR.swizzle<B>() == 3.0f);
    static_assert(VECTOR.swizzle<A>() == 4.0f);

} // namespace


/**
 * @brief Statically verify that the swizzle variadic template of @ref std::Vector4D returns correct vectors
 *        for STP coordinates.
 */
namespace
{
    using namespace fgm::stp;
    static_assert(VECTOR.swizzle<S, T, P, Q>().s() == 1.0f);
    static_assert(VECTOR.swizzle<S, T, P, Q>().t() == 2.0f);
    static_assert(VECTOR.swizzle<S, T, P, Q>().p() == 3.0f);
    static_assert(VECTOR.swizzle<S, T, P, Q>().q() == 4.0f);

    static_assert(VECTOR.swizzle<Q, P, T, S>().s() == 4.0f);
    static_assert(VECTOR.swizzle<Q, P, T, S>().t() == 3.0f);
    static_assert(VECTOR.swizzle<Q, P, T, S>().p() == 2.0f);
    static_assert(VECTOR.swizzle<Q, P, T, S>().q() == 1.0f);

    static_assert(VECTOR.swizzle<S, T, P>().s() == 1.0f);
    static_assert(VECTOR.swizzle<S, T, P>().t() == 2.0f);
    static_assert(VECTOR.swizzle<S, T, P>().p() == 3.0f);

    static_assert(VECTOR.swizzle<Q, P, T>().s() == 4.0f);
    static_assert(VECTOR.swizzle<Q, P, T>().t() == 3.0f);
    static_assert(VECTOR.swizzle<Q, P, T>().p() == 2.0f);

    static_assert(VECTOR.swizzle<S, T>().s() == 1.0f);
    static_assert(VECTOR.swizzle<S, T>().t() == 2.0f);
    static_assert(VECTOR.swizzle<P, Q>().s() == 3.0f);
    static_assert(VECTOR.swizzle<P, Q>().t() == 4.0f);

    static_assert(VECTOR.swizzle<Q, P>().s() == 4.0f);
    static_assert(VECTOR.swizzle<Q, P>().t() == 3.0f);
    static_assert(VECTOR.swizzle<T, S>().s() == 2.0f);
    static_assert(VECTOR.swizzle<T, S>().t() == 1.0f);

    static_assert(VECTOR.swizzle<S>() == 1.0f);
    static_assert(VECTOR.swizzle<T>() == 2.0f);
    static_assert(VECTOR.swizzle<P>() == 3.0f);
    static_assert(VECTOR.swizzle<Q>() == 4.0f);

} // namespace

/** @} */