/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Matrix4 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */

// template <typename T>
// class Matrix4NoReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(1), T(0) }, fgm::Vector4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4NoReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4XAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(-1), T(0) }, fgm::Vector4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4XAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4YAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(1), T(0) }, fgm::Vector4{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along y-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4YAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4OriginReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(-1), T(0) }, fgm::Vector4{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along the origin(0, 0), parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4OriginReflection, SupportedSignedArithmeticTypes);
//
// /** @brief Verify that reflection transform factory is available at compile time.  */
// namespace
// {
//     // Reflection through origin
//     constexpr auto REFLECTION_MAT = fgm::Matrix4<int>::reflect(true, true);
//     static_assert(REFLECTION_MAT(0, 0) == -1);
//     static_assert(REFLECTION_MAT(0, 1) == 0);
//     static_assert(REFLECTION_MAT(1, 0) == 0);
//     static_assert(REFLECTION_MAT(1, 1) == -1);

// } // namespace

//
// /**************************************
//  *                                    *
//  *          REFLECTION TESTS          *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that reflection transformation factory for no reflection along any axis
//  *        returns a reflection matrix.
//  */
// TYPED_TEST(Matrix4NoReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(false, false)); }
//
//
// /** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
// TYPED_TEST(Matrix4XAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(true, false)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Matrix4YAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(false, true)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Matrix4OriginReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(true, true)); }
//

/** @} */
