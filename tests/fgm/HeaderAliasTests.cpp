// /**
//  * @file HeaderAliasTests.cpp
//  * @author Alan Abraham P Kochumon
//  * @date Created on: June 19, 2026
//  *
//  * @brief Verify Header Alias point to correct structs and functions.
//  *
//  * @copyright Copyright(c) 2026 Alan Abraham P Kochumon
//  */
//
//
// #include <fgm/Mat>
// #include <fgm/Vec>
// #include <type_traits>
//
// /**
//  * @addtogroup T_FGM_Header_Alias
//  * @{
//  */
//
// namespace
// {
//     /**
//      * @brief Verify that Vec header alias is the full vector struct.
//      */
//     static_assert(std::is_same_v<fgm::Vec2<int>, fgm::Vec2<int>>);
//     static_assert(std::is_same_v<fgm::Vec2<float>, fgm::Vec2<float>>);
//
//
//     static_assert(std::is_same_v<fgm::Vec3<int>, fgm::Vec3<int>>);
//     static_assert(std::is_same_v<fgm::Vec3<float>, fgm::Vec3<float>>);
//
//     static_assert(std::is_same_v<fgm::Vec4<int>, fgm::Vec4<int>>);
//     static_assert(std::is_same_v<fgm::Vec4<float>, fgm::Vec4<float>>);
//
//
//     /**
//      * @brief Verify that Mat header alias is the full matrix struct.
//      */
//     static_assert(std::is_same_v<fgm::Mat2<int>, fgm::Mat2<int>>);
//     static_assert(std::is_same_v<fgm::Mat2<float>, fgm::Mat2<float>>);
//
//
//     static_assert(std::is_same_v<fgm::Mat3<int>, fgm::Mat3<int>>);
//     static_assert(std::is_same_v<fgm::Mat3<float>, fgm::Mat3<float>>);
//
//     static_assert(std::is_same_v<fgm::Mat4<int>, fgm::Mat4<int>>);
//     static_assert(std::is_same_v<fgm::Mat4<float>, fgm::Mat4<float>>);
//
// } // namespace
//
//
// /** @} */
