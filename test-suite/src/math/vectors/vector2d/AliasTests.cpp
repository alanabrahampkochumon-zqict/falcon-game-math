///**
// * @file AliasTests.cpp
// * @author Alan Abraham P Kochumon
// * @date Created on: April 02, 2026
// *
// * @brief Verify alias for @ref fgm::Vector3D returning correct data type.
// *
// * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
// */
//
//
//#include "Vector3DTestSetup.h"
//
//
//
///**
// * @addtogroup T_FGM_Vec3_Alias
// * @{
// */
//
///** @test Verify @ref fgm::bVec3 has `bool` value_type. */
//TEST(Vector3DAlias, bVec3IsA3DBoolVector)
//{
//    static_assert(std::is_same_v<fgm::bVec3::value_type, bool> && "bVec3 must contain boolean elements");
//    static_assert(std::is_same_v<fgm::bVec3, fgm::Vector3D<bool>> && "bVec3 must be an alias of Vector3D<bool>");
//}
//
//
///** @test Verify @ref fgm::iVec3 has `int` value_type. */
//TEST(Vector3DAlias, iVec3IsA3DIntVector)
//{
//    static_assert(std::is_same_v<fgm::iVec3::value_type, int> && "iVec3 must contain int elements");
//    static_assert(std::is_same_v<fgm::iVec3, fgm::Vector3D<int>> && "iVec3 must be an alias of Vector3D<int>");
//}
//
//
///** @test Verify @ref fgm::uVec3 has `unsigned int` value_type. */
//TEST(Vector3DAlias, uVec3IsA3DUnsignedIntVector)
//{
//    static_assert(std::is_same_v<fgm::uVec3::value_type, unsigned int> && "uVec3 must contain unsigned int elements");
//    static_assert(std::is_same_v<fgm::uVec3, fgm::Vector3D<unsigned int>> &&
//                  "uVec3 must be an alias of Vector3D<unsigned int>");
//}
//
//
///** @test Verify @ref fgm::vec3 has `float` value_type. */
//TEST(Vector3DAlias, vec3IsA3DFloatVector)
//{
//    static_assert(std::is_same_v<fgm::vec3::value_type, float> && "vec3 must contain float elements");
//    static_assert(std::is_same_v<fgm::vec3, fgm::Vector3D<float>> && "vec3 must be an alias of Vector3D<float>");
//}
//
//
///** @test Verify @ref fgm::lVec3 has `long long` value_type. */
//TEST(Vector3DAlias, lVec3IsA3DLongLongVector)
//{
//    static_assert(std::is_same_v<fgm::lVec3::value_type, long long> && "lVec3 must contain long long elements");
//    static_assert(std::is_same_v<fgm::lVec3, fgm::Vector3D<long long>> &&
//                  "lVec3 must be an alias of Vector3D<long long>");
//}
//
//
///** @test Verify @ref fgm::dVec3 has `double` value_type. */
//TEST(Vector3DAlias, dVec3IsA3DDoubleVector)
//{
//    static_assert(std::is_same_v<fgm::dVec3::value_type, double> && "dVec3 must contain double elements");
//    static_assert(std::is_same_v<fgm::dVec3, fgm::Vector3D<double>> && "dVec3 must be an alias of Vector3D<double>");
//}
//
//
///** @test Verify @ref fgm::ulVec3 has `unsigned long long` value_type. */
//TEST(Vector3DAlias, ulVec3IsA3DUnsignedLongLongVector)
//{
//    static_assert(std::is_same_v<fgm::ulVec3::value_type, unsigned long long> &&
//                  "ulVec3 must contain unsigned long long elements");
//    static_assert(std::is_same_v<fgm::ulVec3, fgm::Vector3D<unsigned long long>> &&
//                  "ulVec3 must be an alias of Vector3D<unsigned long long>");
//}
//
///** @} */