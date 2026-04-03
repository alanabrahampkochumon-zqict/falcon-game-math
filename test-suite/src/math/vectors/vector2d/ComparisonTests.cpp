///**
// * @file ComparisonTests.cpp
// * @author Alan Abraham P Kochumon
// * @date Created on: April 02, 2026
// *
// * @brief Verifies @ref fgm::Vector3D<bool> comparison operator (>, >=, <, <=) and their functional counterpart's (gt,
// * gte, lt, lte) logic.
// *
// * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
// */
//
//
//#include "Vector3DTestSetup.h"
//
//#include <common/Constants.h>
//
//
//
//constexpr auto NAN_F = fgm::constants::NaN;
//constexpr auto INF = fgm::constants::INFINITY_F;
//
//
//
///**************************************
// *                                    *
// *                SETUP               *
// *                                    *
// **************************************/
//
//template <typename T>
//class Vector3DComparison: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vecA;
//    fgm::Vector3D<T> _vecB;
//    fgm::Vector3D<bool> _expectedGT, _expectedGTE, _expectedLT,
//        _expectedLTE; // GT-> Greater Than, GTE-> Greater Than or Equal, LT -> Less than, LTE -> Less than or equal
//
//    void SetUp() override
//    {
//        _vecA = { T(1.1234568789), T(2.123458319), T(5.123412593891)};
//        _vecB = { T(5.1234568789), T(1.123458319), T(8.123412593891)};
//        _expectedGT = { false, true, false };
//        _expectedGTE = { false, true, false };
//        _expectedLT = { true, false, true };
//        _expectedLTE = { true, false, true };
//    }
//};
///** @brief Test fixture for @fgm::Vector3D comparisons, parameterized by @ref SupportedArithmeticTypes */
//TYPED_TEST_SUITE(Vector3DComparison, SupportedArithmeticTypes);
//
//
//
///**
// * @addtogroup T_FGM_Vec3_GT_Comp
// * @{
// */
//
///**************************************
// *                                    *
// *         GREATER THAN TESTS         *
// *                                    *
// **************************************/
//
///**
// * @test Verify that the greater-than (gt) function perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA.gt(this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedGT, mask);
//}
//
//
///**
// * @test Verify that the greater-than operator perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, GreaterThanOperator_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA > this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedGT, mask);
//}
//
//
///**
// * @test Verify that the static variant of greater-than (gt) function performs a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, StaticWrapper_GreaterThan_ReturnsBooleanVectorWithElementsGreaterThanAsTrue)
//{
//    const fgm::Vector3D<bool> mask = fgm::Vector3D<TypeParam>::gt(this->_vecA, this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedGT, mask);
//}
//
//
///**
// * @test Verify that the greater-than (gt) function perform a component-wise comparison
// *       when handling infinite values.
// */
//TEST(Vector3DComparison, InfinityVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2, 4.5, 6.8);
//    constexpr fgm::Vector3D infVec(INF, INF, -INF);
//    constexpr fgm::Vector3D expected(false, false, true);
//
//    constexpr fgm::Vector3D<bool> mask = vec.gt(infVec);
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the greater-than (gt) function perform a component-wise comparison
// *       when handling NaN values.
// */
//TEST(Vector3DComparison, NaNVector_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2f, 4.5f, 6.8f);
//    constexpr fgm::Vector3D infVec(NAN_F, NAN_F, -5.9f);
//    constexpr fgm::Vector3D expected(false, false, true);
//
//    constexpr fgm::Vector3D<bool> mask = vec.gt(infVec);
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the greater-than (gt) function perform a component-wise comparison
// *       when handling vectors of different types.
// */
//TEST(Vector3DComparison, MixedType_GreaterThan_ReturnsBooleanVectorWithCorrectValues)
//{
//    // Given two arbitrary vectors of different types
//    constexpr fgm::Vector3D vecA(1.2, 4.5, 7.5);
//    constexpr fgm::Vector3D vecB(5, 6, 7);
//    constexpr fgm::Vector3D expected(false, false, true);
//
//    // When compared with greater than or equal
//    constexpr fgm::Vector3D<bool> mask = vecA.gt(vecB);
//
//    // Then, the resulting elements are as expected
//    EXPECT_VEC_EQ(expected, mask);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_GTE_Comp
// * @{
// */
//
///**************************************
// *                                    *
// *    GREATER THAN OR EQUALS TESTS    *
// *                                    *
// **************************************/
//
///**
// * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA.gte(this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedGTE, mask);
//}
//
//
///**
// * @test Verify that the greater-than-or-equal operator performs a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, GreaterThanOrEqualOperator_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA >= this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedGTE, mask);
//}
//
//
///**
// * @test Verify that the static variant of greater-than-or-equal (gte) function perform a component-wise
// *       comparison and returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison,
//           StaticWrapper_GreaterThanOrEqual_ReturnsBooleanVectorWithElementsGreaterThanOrEqualAsTrue)
//{
//    const fgm::Vector3D<bool> mask = fgm::Vector3D<TypeParam>::gte(this->_vecA, this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedGTE, mask);
//}
//
//
///**
// * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
// *       when handling infinite values.
// */
//TEST(Vector3DComparison, InfinityVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2f, 4.5f, 6.8f);
//    constexpr fgm::Vector3D infVec(INF, INF, -INF);
//    constexpr fgm::Vector3D expected(false, false, true);
//
//    constexpr fgm::Vector3D<bool> mask = vec.gte(infVec);
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the greater-than-or-equal (gte) function perform a component-wise comparison
// *       when handling NaN values.
// */
//TEST(Vector3DComparison, NanVector_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2, 4.5, 6.8);
//    constexpr fgm::Vector3D infVec(NAN_F, NAN_F, -5.9f);
//    constexpr fgm::Vector3D expected(false, false, true);
//
//    constexpr fgm::Vector3D<bool> mask = vec.gte(infVec);
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the greater-than-or-equal (gte) function performs a component-wise comparison
// *       when handling vectors of different types.
// */
//TEST(Vector3DComparison, MixedType_GreaterThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
//{
//    // Given two arbitrary vectors of different types
//    constexpr fgm::Vector3D vecA(1.2, 4.5, 7.5);
//    constexpr fgm::Vector3D vecB(5, 6, 7);
//    constexpr fgm::Vector3D expected(false, false, true);
//
//    // When compared with greater or equal than
//    constexpr fgm::Vector3D<bool> mask = vecA.gte(vecB);
//
//    // Then, the resulting elements are as expected
//    EXPECT_VEC_EQ(expected, mask);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_LT_Comp
// * @{
// */
//
///**************************************
// *                                    *
// *          LESS THAN TESTS           *
// *                                    *
// **************************************/
//
///**
// * @test Verify that the less-than (lt) function perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA.lt(this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedLT, mask);
//}
//
//
///**
// * @test Verify that the less-than operator perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, LessThanOperator_ReturnsBooleanVectorWithElementsLessThanAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA < this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedLT, mask);
//}
//
//
///**
// * @test Verify that the static variant of less-than (lt) function perform a component-wise comparison and
// *		 returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, StaticWrapper_LessThan_ReturnsBooleanVectorWithElementsLessThanAsTrue)
//{
//    const fgm::Vector3D<bool> mask = fgm::Vector3D<TypeParam>::lt(this->_vecA, this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedLT, mask);
//}
//
//
///**
// * @test Verify that the less-than (lt) function perform a component-wise comparison
// *       when handling infinite values.
// */
//TEST(Vector3DComparison, InfinityVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2, 4.5, 6.8);
//    constexpr fgm::Vector3D infVec(INF, INF, -INF);
//    constexpr fgm::Vector3D expected(true, true, false);
//
//    constexpr fgm::Vector3D<bool> mask = vec.lt(infVec);
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the less-than (lt) function perform a component-wise comparison
// *       when handling NaN values.
// */
//TEST(Vector3DComparison, NanVector_LessThan_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2f, 4.5f, 6.8f);
//    constexpr fgm::Vector3D nanVec(NAN_F, NAN_F, -5.9f);
//    constexpr fgm::Vector3D expected(false, false, false);
//
//#if defined(_MSC_VER) && !defined(__clang__)
//    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
//    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
//    // Resharper disable all
//    const fgm::Vector3D<bool> mask = vec.lt(nanVec);
//    // Resharper restore all
//#else
//    // Clang and GCC follow IEEE 754 strictly at compile-time.
//    constexpr fgm::Vector3D<bool> mask = vec.lt(nanVec);
//#endif
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the less-than (lt) function perform a component-wise comparison
// *       when handling vectors of different types.
// */
//TEST(Vector3DComparison, MixedType_LessThan_ReturnsBooleanVectorWithCorrectValues)
//{
//    // Given two arbitrary vectors of different types
//    constexpr fgm::Vector3D vecA(1.2, 4.5, 7.5);
//    constexpr fgm::Vector3D vecB(5, 6, 7);
//    constexpr fgm::Vector3D expected(true, true, false);
//
//    // When compared with less than or equal
//    constexpr fgm::Vector3D<bool> mask = vecA.lt(vecB);
//
//    // Then, the resulting elements are as expected
//    EXPECT_VEC_EQ(expected, mask);
//}
//
///** @} */
//
//
//
///**
// * @addtogroup T_FGM_Vec3_LTE_Comp
// * @{
// */
//
///**************************************
// *                                    *
// *      LESS THAN OR EQUALS TESTS     *
// *                                    *
// **************************************/
//
///**
// * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA.lte(this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedLTE, mask);
//}
//
//
///**
// * @test Verify that the less-than-or-equal operator perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, LessThanOrEqualOperator_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
//{
//    const fgm::Vector3D<bool> mask = this->_vecA <= this->_vecB;
//
//    EXPECT_VEC_EQ(this->_expectedLTE, mask);
//}
//
//
///**
// * @test Verify that the static variant of less-than-or-equal (lte) function perform a component-wise comparison and
// *       returns the correct boolean mask.
// */
//TYPED_TEST(Vector3DComparison, StaticWrapper_LessThanOrEqual_ReturnsBooleanVectorWithElementsLessThanOrEqualAsTrue)
//{
//    const fgm::Vector3D<bool> mask = fgm::Vector3D<TypeParam>::lte(this->_vecA, this->_vecB);
//
//    EXPECT_VEC_EQ(this->_expectedLTE, mask);
//}
//
//
///**
// * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison
// *       when handling infinite values.
// */
//TEST(Vector3DComparison, InfinityVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2, 4.5, 6.8);
//    constexpr fgm::Vector3D infVec(INF, INF, -INF);
//    constexpr fgm::Vector3D expected(true, true, false);
//
//    constexpr fgm::Vector3D<bool> mask = vec.lte(infVec);
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison
// *       when handling NaN values.
// */
//TEST(Vector3DComparison, NanVector_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
//{
//    constexpr fgm::Vector3D vec(1.2f, 4.5f, 6.8f);
//    constexpr fgm::Vector3D nanVec(NAN_F, NAN_F, -5.9f);
//    constexpr fgm::Vector3D expected(false, false, false);
//
//#if defined(_MSC_VER) && !defined(__clang__)
//    // MSVC constant evaluator incorrectly returns true for NAN_F comparisons.
//    // We fallback to 'const' (runtime) to verify the hardware/logic is correct.
//    // Resharper disable all
//    const fgm::Vector3D<bool> mask = vec.lte(nanVec);
//    // Resharper restore all
//#else
//    // Clang and GCC follow IEEE 754 strictly at compile-time.
//    constexpr fgm::Vector3D<bool> mask = vec.lte(nanVec);
//#endif
//
//    EXPECT_VEC_EQ(expected, mask);
//}
//
//
///**
// * @test Verify that the less-than-or-equal (lte) function perform a component-wise comparison 
// *       when handling vectors of different types.
// */
//TEST(Vector3DComparison, MixedType_LessThanOrEqual_ReturnsBooleanVectorWithCorrectValues)
//{
//    // Given two arbitrary vectors of different types
//    constexpr fgm::Vector3D vecA(1.2, 4.5, 7.5);
//    constexpr fgm::Vector3D vecB(5, 6, 7);
//    constexpr fgm::Vector3D expected(true, true, false);
//
//    // When compared with less than or equal
//    constexpr fgm::Vector3D<bool> mask = vecA.lte(vecB);
//
//    // Then, the resulting elements are as expected
//    EXPECT_VEC_EQ(expected, mask);
//}
//
///** @} */
