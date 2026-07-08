/**
 * @file TransformationFactoryTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 04, 2026
 *
 * @brief Verify @ref fgm::Matrix4 transformation factory function (E.g: MakeRotation, MakeScale, etc.) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */




/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

namespace
{
    /**
     * @brief Verify that rotation transform factory is available at compile time.
     *         Only available for **C++26 and above** since trigonometric functions
     *         are constexpr starting from C++26.
     */
    namespace
    {
#if __cplusplus >= 202603L // TODO: Add static tests after making trig functions constexpr
        // Rotation matrix for 180° or 2π radians
        constexpr auto ROTATION_MAT = fgm::Matrix4<int>::rotate(fgm::constants::PI<float>);
        static_assert(ROTATION_MAT(0, 0) == 1);
        static_assert(ROTATION_MAT(0, 1) == 0);
        static_assert(ROTATION_MAT(0, 2) == 0);
        static_assert(ROTATION_MAT(1, 0) == 0);
        static_assert(ROTATION_MAT(1, 1) == -1);
        static_assert(ROTATION_MAT(1, 2) == 0);
        static_assert(ROTATION_MAT(2, 0) == 0);
        static_assert(ROTATION_MAT(2, 1) == 0);
        static_assert(ROTATION_MAT(2, 2) == -1);
#endif

    } // namespace

} // namespace
