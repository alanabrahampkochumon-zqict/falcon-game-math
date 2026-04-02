/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verifies @ref fgm::Vector3D conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"



/**
 * @addtogroup T_FGM_Vec3_Type_Conv
 * @{
 */

/**
 * @test Verify that the conversion constructor correctly promotes components from float to double.
 */
TEST(Vector3DConversionConstructor, PromotesType)
{
    constexpr fgm::Vector3D vec1(3.0f, 1.0f, 6.0f);

    [[maybe_unused]] constexpr fgm::Vector3D<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @test Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Vector3DConversionConstructor, ReturnsNewInstance)
{
    // Given a float vector
    constexpr fgm::Vector3D vec1(3.0f, 1.0f, 6.0f);

    // When converted to a double vector
    fgm::Vector3D<double> vec2(vec1);
    // And one of its value mutated
    vec2.x = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f, 6.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0, 6.0);
}


/**
 * @test Verify that the conversion constructor correctly demotes components from double to float.
 */
TEST(Vector3DConversionConstructor, DemotesType)
{
    constexpr fgm::Vector3D vec1(3.0, 1.0, 6.0);

    [[maybe_unused]] constexpr fgm::Vector3D<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}

/** @} */