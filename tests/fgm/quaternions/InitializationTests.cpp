/**
 * @file InitializationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 01, 2026
 *
 * @brief Verify @ref fgm::Quaternion initialization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"


/**
 * @addtogroup T_FGM_Quaternion_Init
 * @{
 */

namespace
{


    /**************************************
     *                                    *
     *            TEST SETUP              *
     *                                    *
     **************************************/

    /**
     * @brief Test Fixture for Quaternion initialization.
     *
     * @tparam T The scalar type (uint8_t, float, uint32_t...) used for the values.
     */
    template <typename T>
    class QuaternionInitialization: public testing::Test
    {};
    TYPED_TEST_SUITE(QuaternionInitialization, SupportedTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that quaternions can be initialized with braced initializer has zero out components
        ///       at compile time.
        constexpr fgm::Quaternion<int> ZERO_QUATERNION{};
        static_assert(ZERO_QUATERNION.x() == 0);
        static_assert(ZERO_QUATERNION.y() == 0);
        static_assert(ZERO_QUATERNION.z() == 0);
        static_assert(ZERO_QUATERNION.w() == 0);


        /// @test Verify that quaternions can be initialized with individuals values at compile time.
        constexpr fgm::Quaternion QUATERNION(1, 2, 3, 4);
        static_assert(QUATERNION.x() == 1);
        static_assert(QUATERNION.y() == 2);
        static_assert(QUATERNION.z() == 3);
        static_assert(QUATERNION.w() == 4);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(QuaternionInitialization, BracedInitializer_InitializesAllComponentsToZero)
{
    const fgm::Quaternion<TypeParam> quat{};
    const auto zero = TypeParam(0);
    EXPECT_QUAT_CONTAINS(quat, zero, zero, zero, zero);
}


TYPED_TEST(QuaternionInitialization, ParameterizedCtor_InitializesQuaternionWithIndividalComponents)
{
    const TypeParam a = static_cast<TypeParam>(3);
    const TypeParam b = static_cast<TypeParam>(1);
    const TypeParam c = static_cast<TypeParam>(6);
    const TypeParam d = static_cast<TypeParam>(4);

    const fgm::Quaternion<TypeParam> quat(a, b, c, d);

    EXPECT_QUAT_CONTAINS(quat, a, b, c, d);
}

//
// /**
//  * @brief Verify that the parameterized constructor correctly composes a 4D quattor from
//  *       two @ref fgm::Vec2 instances.
//  */
// TYPED_TEST(QuaternionInitialization, Two2DVectorsCanInitializeA4DVector)
// {
//     const TypeParam a = static_cast<TypeParam>(3);
//     const TypeParam b = static_cast<TypeParam>(1);
//     const TypeParam c = static_cast<TypeParam>(6);
//     const TypeParam d = static_cast<TypeParam>(4);
//     const fgm::Vec2<TypeParam> quat1(a, b);
//     const fgm::Vec2<TypeParam> quat2(c, d);
//
//     const fgm::Quaternion<TypeParam> quat(quat1, quat2);
//
//     EXPECT_VEC_CONTAINS(quat, a, b, c, d);
// }
//
//
// /**
//  * @brief Verify that the parameterized constructor correctly composes a 4D quattor from a
//  *       @ref fgm::Vec3 instance and a scalar.
//  */
// TYPED_TEST(QuaternionInitialization, 3DVectorAndScalarCanInitializeA4DVector)
// {
//     const TypeParam a = static_cast<TypeParam>(3);
//     const TypeParam b = static_cast<TypeParam>(1);
//     const TypeParam c = static_cast<TypeParam>(6);
//     const fgm::Vec3 quat1(a, b, c);
//     const TypeParam scalar = static_cast<TypeParam>(4);
//
//     const fgm::Quaternion quat(quat1, scalar);
//
//     EXPECT_VEC_CONTAINS(quat, a, b, c, scalar);
// }
//
//
// /**
//  * @brief Verify that the parameterized constructor correctly composes a 4D quattor from a scalar and
//  *        a @ref fgm::Vec3 instance.
//  */
// TYPED_TEST(QuaternionInitialization, ScalarAnd3DVectorCanInitializeA4DVector)
// {
//     const TypeParam a = static_cast<TypeParam>(3);
//     const TypeParam b = static_cast<TypeParam>(1);
//     const TypeParam c = static_cast<TypeParam>(6);
//     const fgm::Vec3 quat1(a, b, c);
//     const TypeParam scalar = static_cast<TypeParam>(4);
//
//     const fgm::Quaternion quat(scalar, quat1);
//
//     EXPECT_VEC_CONTAINS(quat, scalar, a, b, c);
// }


/** @} */
