/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verifies @ref fgm::Vector4D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


/**
 * @addtogroup T_FGM_Vec4_Access
 * @{
 */

/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y, z, w). */
TEST(Vector4DAccess, AccessibleAsXYZW)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}


/** @test Verify that the components are accessible via named spatial aliases (s, t, p, q). */
TEST(Vector4DAccess, AccessibleAsSTPQ)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
    EXPECT_FLOAT_EQ(2.0f, vec.q);
}


/** @test Verify that the components are accessible via named spatial aliases (r, g, b, a). */
TEST(Vector4DAccess, AccessibleAsRGBA)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
    EXPECT_FLOAT_EQ(2.0f, vec.a);
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(Vector4DAccess, AccessibleAsArray)
{
    constexpr fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
    EXPECT_FLOAT_EQ(2.0f, vec.elements[3]);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec4_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y, z, w). */
TEST(Vector4DMutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vector4D<float> vec;

    vec.x = 3.0f;
    vec.y = 1.0f;
    vec.z = 6.0f;
    vec.w = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
    EXPECT_FLOAT_EQ(2.0f, vec.w);
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t, p, q). */
TEST(Vector4DMutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vector4D<float> vec;

    vec.s = 3.0f;
    vec.t = 1.0f;
    vec.p = 6.0f;
    vec.q = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
    EXPECT_FLOAT_EQ(2.0f, vec.q);
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g, b, a). */
TEST(Vector4DMutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vector4D<float> vec;

    vec.r = 3.0f;
    vec.g = 1.0f;
    vec.b = 6.0f;
    vec.a = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
    EXPECT_FLOAT_EQ(2.0f, vec.a);
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(Vector4DMutation, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vector4D<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    vec[3] = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

/** @} */