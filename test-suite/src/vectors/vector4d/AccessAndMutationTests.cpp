/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief `Vector4D` access and mutation tests.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

TEST(Vector4DAccess, AccessibleAsXYZW)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as x, y, z, w
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}

TEST(Vector4DAccess, AccessibleAsSTPQ)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as s, t, p, q
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
    EXPECT_FLOAT_EQ(2.0f, vec.q);
}

TEST(Vector4DAccess, AccessibleAsRGBA)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as r, g, b, a
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
    EXPECT_FLOAT_EQ(2.0f, vec.a);
}

TEST(Vector4DAccess, AccessibleAsArray)
{
    // Given a vector with arbitrary values passed in
    const math::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    // Then, it's elements are accessible as array elements
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
    EXPECT_FLOAT_EQ(2.0f, vec.elements[3]);
}


/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

TEST(Vector4DMutation, ElementsCanBeMutatedUsingXYZW)
{
    // Given a default initialized vector
    math::Vector4D<float> vec;

    // When, it's elements are modified using x, y, z, w
    vec.x = 3.0f;
    vec.y = 1.0f;
    vec.z = 6.0f;
    vec.w = 2.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}

TEST(Vector4DMutation, ElementsCanBeMutatedUsingSTPQ)
{
    // Given a default initialized vector
    math::Vector4D<float> vec;

    // When, it's elements are modified using s, t, p, q
    vec.s = 3.0f;
    vec.t = 1.0f;
    vec.p = 6.0f;
    vec.q = 2.0f;

    // Then, it's elements are modified
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
    EXPECT_FLOAT_EQ(2.0f, vec.q);
}

TEST(Vector4DMutation, ElementsCanBeMutatedUsingRGBA)
{
    // Given a default initialized vector
    math::Vector4D<float> vec;

    // When, it's elements are modified using r, g, b, a
    vec.r = 3.0f;
    vec.g = 1.0f;
    vec.b = 6.0f;
    vec.a = 2.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
    EXPECT_FLOAT_EQ(2.0f, vec.a);
}

TEST(Vector4DMutation, ElementsCanBeMutatedUsingIndex)
{
    // Given a vector initialization without parameters
    math::Vector4D<float> vec;

    // When it's elements are mutated at a particular index
    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    vec[3] = 2.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}
