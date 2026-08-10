/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::Vec2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Vec2TestSetup.h"




/**
 * @addtogroup T_FGM_Vec2_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace
    {
        constexpr fgm::Vec2 vector(1, 2);

        /// @test Verify that vector is accessible as <x, y> at compile time.
        static_assert(vector.x() == 1);
        static_assert(vector.y() == 2);

        /// @test Verify that vector is accessible as <r, g> at compile time.
        static_assert(vector.r() == 1);
        static_assert(vector.g() == 2);

        /// @test Verify that vector is accessible as <s, t> at compile time.
        static_assert(vector.s() == 1);
        static_assert(vector.t() == 2);
    } // namespace

} // namespace


/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @brief Verify that the components are accessible via named spatial aliases (x, y). */
TEST(Vec2AccessTests, AccessibleAsXYZW)
{
    static const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @brief Verify that the components are accessible via named spatial aliases (s, t). */
TEST(Vec2AccessTests, AccessibleAsSTPQ)
{
    const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @brief Verify that the components are accessible via named spatial aliases (r, g). */
TEST(Vec2AccessTests, AccessibleAsRGBA)
{
    const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @brief Verify that the components are accessible via subscript indexing for reads. */
TEST(Vec2AccessTests, AccessibleAsArray)
{
    const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @brief Verify that the components can be mutated via named spatial aliases (x, y). */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vec2<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @brief Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vec2<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @brief Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vec2<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @brief Verify that the components are accessible via subscript indexing for writing. */
TEST(Vec2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vec2<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}



/** @} */
