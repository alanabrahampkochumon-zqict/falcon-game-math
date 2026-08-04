/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 03, 2026
 *
 * @brief Verify @ref fgm::Quaternion quaternion algebra(Conjugate, Inverse,...).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"


/**
 * @addtogroup T_FGM_Quaternion_Algebra
 * @{
 */
//
// namespace
// {
//
//     /**************************************
//      *            TEST SETUP              *
//      **************************************/
//
//     /**
//      * @brief Test fixture for verifying quaternion conjugate across different scalar types.
//      *
//      * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
//      */
//     template <typename T>
//     class QuaternionConjugateTests: public testing::Test
//     {
//     protected:
//         fgm::Quaternion<T> _quat;
//         fgm::Quaternion<T> _expectedConjugate;
//
//         void SetUp() override
//         {
//             _quat              = { T(8), T(-4), T(7), T(8) };
//             _expectedConjugate = { T(-8), T(4), T(-7), T(8) };
//         }
//     };
//     TYPED_TEST_SUITE(QuaternionConjugateTests, SupportedSignedArithmeticTypes);
//
//
//
//     /**************************************
//      *            STATIC TESTS            *
//      **************************************/
//
//     /** @brief Verify that quaternion arithmetic operations are available at compile time. */
//     namespace static_tests
//     {
//         // constexpr fgm::Quaternion QUAT_A(-1, 12, 3, 4);
//         // constexpr fgm::Quaternion QUAT_B(5, 12, -5, 3);
//         //
//         // /// @test Verify that quaterion addition returns a valid quaternion at compile-time.
//         // constexpr auto QUAT_SUM = QUAT_A + QUAT_B;
//         // static_assert(QUAT_SUM.i() == 4);
//         // static_assert(QUAT_SUM.j() == 24);
//         // static_assert(QUAT_SUM.k() == -2);
//         // static_assert(QUAT_SUM.s() == 7);
//
//
//     } // namespace static_tests
//
//
// } // namespace
//
//
//
// /**************************************
//  *           CONJUGATE TESTS          *
//  **************************************/
//
// TYPED_TEST(QuaternionConjugateTests, ReturnsAQuaternionWithInvertedVectorPart)
// { EXPECT_QUAT_EQ(this->_expectedConjugate, this->_quat.conjugate()); }
//
//
// TYPED_TEST(QuaternionConjugateTests, StaticWrapper_ReturnsAQuaternionWithInvertedVectorPart)
// { EXPECT_QUAT_EQ(this->_expectedConjugate, fgm::Quaternion<TypeParam>::conjugate(this->_quat)); }

/** @} */
