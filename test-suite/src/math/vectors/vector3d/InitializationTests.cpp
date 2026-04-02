/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector3D initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"


using namespace testutils;


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector3DInitialization: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Vector3D initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(Vector3DInitialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Vec4_Init
 * @{
 */
/** @test Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vector3DInitialization, EmptyConstructorInitializesZeroVector)
{
    const fgm::Vector3D<TypeParam> vec;

    EXPECT_VEC_ZERO(vec);
}


/** @test Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vector3DInitialization, ConstructorParametersInitializesVector)
{
    TypeParam a = static_cast<TypeParam>(3);
    TypeParam b = static_cast<TypeParam>(1);
    TypeParam c = static_cast<TypeParam>(6);

    const fgm::Vector3D<TypeParam> vec(a, b, c);

    EXPECT_VEC_CONTAINS(vec, a, b, c);
}


/**
 * @test Verify that the parameterized constructor correctly composes a 4D vector from a
 *       @ref fgm::Vector2D instance and a scalar.
 */
TYPED_TEST(Vector3DInitialization, One2DVectorAndScalarCanInitializeA3DVector)
{
    TypeParam a = static_cast<TypeParam>(3);
    TypeParam b = static_cast<TypeParam>(1);
    const fgm::Vector2D<TypeParam> vec1(a, b);
    TypeParam scalar = static_cast<TypeParam>(6);

    const fgm::Vector3D<TypeParam> vec(vec1, scalar);

    EXPECT_VEC_CONTAINS(vec, a, b, scalar);
}