/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vector2D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**
 * @addtogroup T_FGM_Vec2_Access
 * @{
 */

/** @brief Verify that vector accessors are available at compile time. */
namespace
{
    constexpr fgm::Vector2D vector(1, 2);

    static_assert(vector.x() == 1);
    static_assert(vector.y() == 2);

    static_assert(vector.r() == 1);
    static_assert(vector.g() == 2);

    static_assert(vector.s() == 1);
    static_assert(vector.t() == 2);
} // namespace

/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the components are accessible via named spatial aliases (x, y). */
TEST(Vector2DAccess, AccessibleAsXYZW)
{
    static const fgm::Vector2D vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @brief Verify that the components are accessible via named spatial aliases (s, t). */
TEST(Vector2DAccess, AccessibleAsSTPQ)
{
    const fgm::Vector2D vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @brief Verify that the components are accessible via named spatial aliases (r, g). */
TEST(Vector2DAccess, AccessibleAsRGBA)
{
    const fgm::Vector2D vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @brief Verify that the components are accessible via subscript indexing for reads. */
TEST(Vector2DAccess, AccessibleAsArray)
{
    const fgm::Vector2D vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}

/** @} */



/**
 * @addtogroup T_FGM_Vec2_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the components can be mutated via named spatial aliases (x, y). */
TEST(Vector2DMutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vector2D<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @brief Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(Vector2DMutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vector2D<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @brief Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(Vector2DMutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vector2D<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @brief Verify that the components are accessible via subscript indexing for writing. */
TEST(Vector2DMutation, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vector2D<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}

/** @} */
