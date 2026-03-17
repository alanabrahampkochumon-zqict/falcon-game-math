/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref Vector4D conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"

using testutils::EXPECT_VEC_CONTAINS;


/**
 * @test Verify that the @ref fgm::Vector4D conversion constructor correctly promotes components from float to double.
 */
TEST(Vector4DConversionConstructor, PromotesType)
{
    const fgm::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

    [[maybe_unused]] const fgm::Vector4D<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @test Verify that the @ref fgm::Vector4D conversion constructor ensures deep-copy value semantics. */
TEST(Vector4DConversionConstructor, ReturnsNewInstance)
{
    // Given a float vector
    const fgm::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

    // When converted to a double vector
    fgm::Vector4D<double> vec2(vec1);
    // And one of its value mutated
    vec2.x = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f, 6.0f, 2.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0, 6.0, 2.0);
}


/**
 * @test Verify that the @ref fgm::Vector4D conversion constructor correctly demotes components from double to float.
 */
TEST(Vector4DConversionConstructor, DemotesType)
{
    const fgm::Vector4D vec1(3.0, 1.0, 6.0, 2.0);

    [[maybe_unused]] const fgm::Vector4D<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}
