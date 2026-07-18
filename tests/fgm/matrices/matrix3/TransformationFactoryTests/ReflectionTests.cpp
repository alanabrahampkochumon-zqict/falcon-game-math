/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"

/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */

// template <typename T>
// class Mat3NoReflection: public ::testing::Test
// {
// protected:
//     fgm::Mat3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vec4{ T(1), T(0) }, fgm::Vec4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Mat3 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Mat3NoReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Mat3XAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Mat3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vec4{ T(-1), T(0) }, fgm::Vec4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Mat3 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Mat3XAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Mat3YAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Mat3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vec4{ T(1), T(0) }, fgm::Vec4{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Mat3 reflection along y-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Mat3YAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Mat3OriginReflection: public ::testing::Test
// {
// protected:
//     fgm::Mat3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vec4{ T(-1), T(0) }, fgm::Vec4{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Mat3 reflection along the origin(0, 0), parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Mat3OriginReflection, SupportedSignedArithmeticTypes);
//
// /** @brief Verify that reflection transform factory is available at compile time.  */
// namespace
// {
//     // Reflection through origin
//     constexpr auto REFLECTION_MAT = fgm::Mat3<int>::reflect(true, true);
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
// TYPED_TEST(Mat3NoReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::reflect(false, false)); }
//
//
// /** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
// TYPED_TEST(Mat3XAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::reflect(true, false)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Mat3YAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::reflect(false, true)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Mat3OriginReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::reflect(true, true)); }
//

/** @} */
