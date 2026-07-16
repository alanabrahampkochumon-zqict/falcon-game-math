/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector3 initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector3Initialization: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Vector3 initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(Vector3Initialization, SupportedTypes);



/**
 * @addtogroup T_FGM_Vec3_Init
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
    constexpr fgm::Vector3 vecA(1, 2, 3);
    constexpr fgm::Vector3 vecB({ 1, 2 }, 3);
    constexpr fgm::Vector3 vecC(1, { 2, 3 });
    constexpr fgm::Vector3<int> vecD{};

    static_assert(vecA.x() == 1);
    static_assert(vecA.y() == 2);
    static_assert(vecA.z() == 3);

    static_assert(vecB.x() == 1);
    static_assert(vecB.y() == 2);
    static_assert(vecB.z() == 3);

    static_assert(vecC.x() == 1);
    static_assert(vecC.y() == 2);
    static_assert(vecC.z() == 3);

    static_assert(vecD.x() == 0);
    static_assert(vecD.y() == 0);
    static_assert(vecD.z() == 0);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the default constructor initializes all components to zero. */
TYPED_TEST(Vector3Initialization, EmptyConstructorInitializesZeroVector)
{
    const fgm::Vector3<TypeParam> vec{};

    EXPECT_VEC_ZERO(vec);
}


/** @brief Verify that the parameterized constructor correctly assigns components from the provided arguments. */
TYPED_TEST(Vector3Initialization, ConstructorParametersInitializesVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);

    const fgm::Vector3<TypeParam> vec(a, b, c);

    EXPECT_VEC_CONTAINS(vec, a, b, c);
}


/**
 * @brief Verify that the parameterized constructor correctly composes a 3D vector from a
 *       @ref fgm::Vector2 instance and a scalar.
 */
TYPED_TEST(Vector3Initialization, 2DVectorAndScalarCanInitializeA3DVector)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const fgm::Vector2<TypeParam> vec1(a, b);
    const TypeParam scalar = static_cast<TypeParam>(6);

    const fgm::Vector3<TypeParam> vec(vec1, scalar);

    EXPECT_VEC_CONTAINS(vec, a, b, scalar);
}


/**
 * @brief Verify that the parameterized constructor correctly composes a 3D vector from a
 *       @ref fgm::Vector2 instance and a scalar.
 */
TYPED_TEST(Vector3Initialization, ScalarAnd2DVectorCanInitializeA3DVector)
{
    const TypeParam scalar = static_cast<TypeParam>(3);
    const TypeParam a      = static_cast<TypeParam>(1);
    const TypeParam b      = static_cast<TypeParam>(6);
    const fgm::Vector2<TypeParam> vec1(a, b);

    const fgm::Vector3<TypeParam> vec(scalar, vec1);

    EXPECT_VEC_CONTAINS(vec, scalar, a, b);
}
