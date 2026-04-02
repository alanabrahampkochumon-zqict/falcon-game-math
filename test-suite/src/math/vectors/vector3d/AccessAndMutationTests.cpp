/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Verifies @ref fgm::Vector3D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



/**
 * @addtogroup T_FGM_Vec3_Access
 * @{
 */

/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @test Verify that the components are accessible via named spatial aliases (x, y, z). */
TEST(Vector3DAccess, AccessibleAsXYZW)
{
    constexpr fgm::Vector3D vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}


/** @test Verify that the components are accessible via named spatial aliases (s, t, p). */
TEST(Vector3DAccess, AccessibleAsSTPQ)
{
    constexpr fgm::Vector3D vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}


/** @test Verify that the components are accessible via named spatial aliases (r, g, b). */
TEST(Vector3DAccess, AccessibleAsRGBA)
{
    constexpr fgm::Vector3D vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(Vector3DAccess, AccessibleAsArray)
{
    constexpr fgm::Vector3D vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.elements[0]);
    EXPECT_FLOAT_EQ(1.0f, vec.elements[1]);
    EXPECT_FLOAT_EQ(6.0f, vec.elements[2]);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec3_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y, z). */
TEST(Vector3DMutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vector3D<float> vec;

    vec.x = 3.0f;
    vec.y = 1.0f;
    vec.z = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x);
    EXPECT_FLOAT_EQ(1.0f, vec.y);
    EXPECT_FLOAT_EQ(6.0f, vec.z);
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t, p). */
TEST(Vector3DMutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vector3D<float> vec;

    vec.s = 3.0f;
    vec.t = 1.0f;
    vec.p = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s);
    EXPECT_FLOAT_EQ(1.0f, vec.t);
    EXPECT_FLOAT_EQ(6.0f, vec.p);
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g, b). */
TEST(Vector3DMutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vector3D<float> vec;

    vec.r = 3.0f;
    vec.g = 1.0f;
    vec.b = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r);
    EXPECT_FLOAT_EQ(1.0f, vec.g);
    EXPECT_FLOAT_EQ(6.0f, vec.b);
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(Vector3DMutation, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vector3D<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}

/** @} */