/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` tests for conversion constructor.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithPromotedType)
{
    // Given a float vector
    math::Vector4D vec1(3.0f, 1.0f, 6.0f, 2.0f);

    // When it is converted to a double vector
    math::Vector4D<double> vec2(vec1);
    // And some values of new vector is mutated
    vec2.x = 5;

    // Then, the float vector remains unchanged
    ASSERT_FLOAT_EQ(3.0f, vec1.x);
    ASSERT_FLOAT_EQ(1.0f, vec1.y);
    ASSERT_FLOAT_EQ(6.0f, vec1.z);
    ASSERT_FLOAT_EQ(2.0f, vec1.w);

    // And, the new vector is of type double with the mutated value
    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
    ASSERT_DOUBLE_EQ(5.0, vec2.x);
    ASSERT_DOUBLE_EQ(1.0, vec2.y);
    ASSERT_DOUBLE_EQ(6.0, vec2.z);
    ASSERT_DOUBLE_EQ(2.0, vec2.w);
}

TEST(Vector4DConversionConstructor, ConversionConstructorCreatesNewVectorWithDemotedType)
{
    // Given a double vector
    math::Vector4D vec1(3.0, 1.0, 6.0, 2.0);

    // When it is converted to a float vector
    math::Vector4D<float> vec2(vec1);
    // And some values of new vector is mutated
    vec2.x = 5;

    // Then, the float vector remains unchanged
    ASSERT_DOUBLE_EQ(3.0, vec1.x);
    ASSERT_DOUBLE_EQ(1.0, vec1.y);
    ASSERT_DOUBLE_EQ(6.0, vec1.z);
    ASSERT_DOUBLE_EQ(2.0, vec1.w);

    // And, the new vector is of type float with the mutated value
    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
    ASSERT_FLOAT_EQ(5.0f, vec2.x);
    ASSERT_FLOAT_EQ(1.0f, vec2.y);
    ASSERT_FLOAT_EQ(6.0f, vec2.z);
    ASSERT_FLOAT_EQ(2.0f, vec2.w);
}
