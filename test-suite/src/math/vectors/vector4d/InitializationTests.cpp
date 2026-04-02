/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4DInitialization: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Vector4D initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(Vector4DInitialization, SupportedTypes);




/**
 * @addtogroup T_FGM_Vec4_Init
 * @{
 */

/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vector4DInitialization, EmptyConstructorInitializesZeroVector)
{
    const fgm::Vector4D<TypeParam> vec;

    EXPECT_VEC_ZERO(vec);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vector4DInitialization, ConstructorInitializesVectorsWithCorrectValue)
{
    constexpr TypeParam a = static_cast<TypeParam>(3);
    constexpr TypeParam b = static_cast<TypeParam>(1);
    constexpr TypeParam c = static_cast<TypeParam>(6);
    constexpr TypeParam d = static_cast<TypeParam>(4);

    const fgm::Vector4D<TypeParam> vec(a, b, c, d);

    EXPECT_VEC_CONTAINS(vec, a, b, c, d);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from
 *       two @ref fgm::Vector2D instances.
 */
TYPED_TEST(Vector4DInitialization, Two2DVectorsCanInitializeA4DVector)
{
    constexpr TypeParam a = static_cast<TypeParam>(3);
    constexpr TypeParam b = static_cast<TypeParam>(1);
    constexpr TypeParam c = static_cast<TypeParam>(6);
    constexpr TypeParam d = static_cast<TypeParam>(4);
    const fgm::Vector2D<TypeParam> vec1(a, b);
    const fgm::Vector2D<TypeParam> vec2(c, d);

    const fgm::Vector4D<TypeParam> vec(vec1, vec2);

    EXPECT_VEC_CONTAINS(vec, a, b, c, d);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from a
 *       @ref fgm::Vector3D instance and a scalar.
 */
TYPED_TEST(Vector4DInitialization, 3DVectorAndScalarCanInitializeA4DVector)
{
    constexpr TypeParam a = static_cast<TypeParam>(3);
    constexpr TypeParam b = static_cast<TypeParam>(1);
    constexpr TypeParam c = static_cast<TypeParam>(6);
    const fgm::Vector3D vec1(a, b, c);
    constexpr TypeParam scalar = static_cast<TypeParam>(4);

    const fgm::Vector4D vec(vec1, scalar);

    EXPECT_VEC_CONTAINS(vec, a, b, c, scalar);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from a scalar and
 *        a @ref fgm::Vector3D instance.
 */
TYPED_TEST(Vector4DInitialization, ScalarAnd3DVectorCanInitializeA4DVector)
{
    constexpr TypeParam a = static_cast<TypeParam>(3);
    constexpr TypeParam b = static_cast<TypeParam>(1);
    constexpr TypeParam c = static_cast<TypeParam>(6);
    const fgm::Vector3D vec1(a, b, c);
    constexpr TypeParam scalar = static_cast<TypeParam>(4);

    const fgm::Vector4D vec(scalar, vec1);

    EXPECT_VEC_CONTAINS(vec, scalar, a, b, c);
}


/** @} */
