/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief `Vector3D` access and mutation tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vector3DTestSetup.h"


/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

TEST(Vector3DAccess, AccessibleAsXYZ)
{
    // Given a vector with arbitrary values passed in
    const math::Vector3D vec(3.0f, 1.0f, 6.0f);

    // Then, it's elements are accessible as x, y, z
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3DAccess, AccessibleAsSTP)
{
    // Given a vector with arbitrary values passed in
    const math::Vector3D vec(3.0f, 1.0f, 6.0f);

    // Then, it's elements are accessible as s, t, p
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}

TEST(Vector3DAccess, AccessibleAsRGB)
{
    // Given a vector with arbitrary values passed in
    const math::Vector3D vec(3.0f, 1.0f, 6.0f);

    // Then, it's elements are accessible as r, g, b
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}

TEST(Vector3DAccess, AccessibleAsArray)
{
    // Given a vector with arbitrary values passed in
    const math::Vector3D vec(3.0f, 1.0f, 6.0f);

    // Then, it's elements are accessible as array elements
    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
}

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/


TEST(Vector3DMutation, ElementsCanBeMutatedUsingXYZ)
{
    // Given a default initialized vector
    math::Vector3D<float> vec;

    // When, it's elements are modified using x, y, z
    vec.x = 3.0f;
    vec.y = 1.0f;
    vec.z = 6.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}

TEST(Vector3DMutation, ElementsCanBeMutatedUsingSTP)
{
    // Given a default initialized vector
    math::Vector3D<float> vec;

    // When, it's elements are modified using s, t, p
    vec.s = 3.0f;
    vec.t = 1.0f;
    vec.p = 6.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}

TEST(Vector3DMutation, ElementsCanBeMutatedUsingRGB)
{
    // Given a default initialized vector
    math::Vector3D<float> vec;

    // When, it's elements are modified using r, g, b
    vec.r = 3.0f;
    vec.g = 1.0f;
    vec.b = 6.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}

TEST(Vector3DMutation, ElementsCanBeMutatedUsingIndex)
{
    // Given a vector initialization without parameters
    math::Vector3D<float> vec;

    // When it's elements are mutated at a particular index
    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;

    // Then, it's element reflect the change
    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}