///**
// * @file StringRepresentationTests.cpp
// * @author Alan Abraham P Kochumon
// * @date Created on: April 04, 2026
// *
// * @brief Verifies @ref fgm::Vector3D string representation.
// *
// * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
// */
//
//
//#include "Vector3DTestSetup.h"
//
//#include <sstream>
//
//
//
///**************************************
// *                                    *
// *                SETUP               *
// *                                    *
// **************************************/
//
//class Vector3DStringRepresentationTests: public ::testing::Test
//{
//    /** @brief Switch to use full precision for testing. */
//    void SetUp() override
//    {
//        fgm::Config::useFullPrecision = true;
//    }
//
//    /** @brief Switch back to normal log precision. */
//    void TearDown() override
//    {
//        fgm::Config::useFullPrecision = false;
//    }
//};
//
//
//
///**
// * @addtogroup T_FGM_Vec3_String_Repr
// * @{
// */
//
///** @test Verify that the string representation matches the expected format for integral types. */
//TEST_F(Vector3DStringRepresentationTests, IntegralRepresentation)
//{
//    constexpr fgm::Vector3D vec(1, 2, 3);
//    std::stringstream ss;
//
//    ss << vec;
//
//    EXPECT_EQ(ss.str(), "<1, 2, 3>\n");
//}
//
//
///**
// * @test Verify that the string representation matches the expected format for single-precision
// *       floating-point types.
// */
//TEST_F(Vector3DStringRepresentationTests, FloatRepresentation)
//{
//    constexpr fgm::Vector3D vec(1.2345f, 2.0f, 3.56789f);
//    std::stringstream ss;
//
//    ss << vec;
//
//    EXPECT_EQ(ss.str(), "<1.23450, 2.00000, 3.56789>\n");
//}
//
//
///**
// * @test Verify that the string representation matches the expected format for double-precision
// *       floating-point types.
// */
//TEST_F(Vector3DStringRepresentationTests, DoubleRepresentation)
//{
//    constexpr fgm::Vector3D vec(1.2345789777, 2.65831, 3.161285);
//    std::stringstream ss;
//
//    ss << vec;
//
//    EXPECT_EQ(ss.str(), "<1.234578977700000, 2.658310000000000, 3.161285000000000>\n");
//}
//
///** @} */
