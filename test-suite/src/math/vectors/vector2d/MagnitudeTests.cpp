///**
// * @file MagnitudeTests.cpp
// * @author Alan Abraham P Kochumon
// * @date Created on: April 04, 2026
// *
// * @brief Verifies @ref fgm::Vector3D magnitude logic.
// *
// * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
// */
//
//
//#include "Vector3DTestSetup.h"
//
//
//
///**************************************
// *                                    *
// *               SETUP                *
// *                                    *
// **************************************/
//
//template <typename T>
//class Vector3DMagnitude: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vec;
//    fgm::Magnitude<T> _expectedMagnitude;
//
//    void SetUp() override
//    {
//        _vec = { T(3), T(4), T(12)};
//        _expectedMagnitude = fgm::Magnitude<T>(13);
//    }
//};
///** @brief Test fixture for @ref fgm::Vector3D magnitude, parameterized by @ref SupportedArithmeticTypes. */
//TYPED_TEST_SUITE(Vector3DMagnitude, SupportedArithmeticTypes);
//
//
//template <typename T>
//class Vector3DUncleanMagnitude: public ::testing::Test
//{
//protected:
//    fgm::Vector3D<T> _vec;
//    fgm::Magnitude<T> _expectedMagnitude;
//
//    void SetUp() override
//    {
//        _vec = { T(1), T(2), T(3) };
//        _expectedMagnitude = fgm::Magnitude<T>(3.7416573867739413);
//    }
//};
///**
// * @brief Test fixture for @ref fgm::Vector3D magnitude, parameterized by @ref SupportedArithmeticTypes,
// *        for testing high-precision magnitude.
// */
//TYPED_TEST_SUITE(Vector3DUncleanMagnitude, SupportedArithmeticTypes);
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Magnitude
// * @{
// */
//
///** @test Verify that taking the magnitude of a zero vector returns exactly zero. */
//TEST(Vector3DMagnitude, ZeroVectorReturnsZero)
//{
//    constexpr fgm::Vector3D vec(0.0f, 0.0f, 0.0f);
//
//    EXPECT_FLOAT_EQ(0.0f, vec.mag());
//}
//
//
///** @test Verify that taking the magnitude of a one vector returns non-unit scalar. */
//TEST(Vector3DMagnitude, OneComponentVectorReturnsNonUnitScalar)
//{
//    constexpr fgm::Vector3D vec(1.0f, 1.0f, 1.0f);
//
//    EXPECT_NE(1.0f, vec.mag());
//}
//
//
///** @test Verify that taking the magnitude of a non-unit vector returns non-unit scalar. */
//TYPED_TEST(Vector3DMagnitude, NonUnitVectorReturnsCorrectMagnitude)
//{
//    const auto magnitude = this->_vec.mag();
//
//    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
//}
//
//
///** @test Verify that taking the magnitude always returns a floating-point scalar. */
//TYPED_TEST(Vector3DMagnitude, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
//{
//    [[maybe_unused]] const auto magnitude = this->_vec.mag();
//    static_assert(std::is_floating_point_v<decltype(magnitude)>);
//}
//
//
///**
// * @test Verify that taking the magnitude of a non-unit vector using static variant of @ref fgm::Vector3D::mag
// *       returns non-unit scalar.
// */
//TYPED_TEST(Vector3DMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
//{
//    const auto magnitude = fgm::Vector3D<TypeParam>::mag(this->_vec);
//
//    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
//}
//
//
///** @test Verify that the magnitude calculations for non-unit vectors ensure minimal precision loss. */
//TYPED_TEST(Vector3DUncleanMagnitude, NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
//{
//    const auto magnitude = this->_vec.mag();
//
//    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
//}
//
//
///**
// * @test Verify that the magnitude calculations for non-unit vectors using static variant of @ref fgm::Vector3D::mag
// *       ensure minimal precision loss.
// */
//TYPED_TEST(Vector3DUncleanMagnitude, StaticWrapper_NonUnitVectorReturnsCorrectMagnitudeWithMinimalPrecisionLoss)
//{
//    const auto magnitude = fgm::Vector3D<TypeParam>::mag(this->_vec);
//
//    EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
//}
//
///** @} */