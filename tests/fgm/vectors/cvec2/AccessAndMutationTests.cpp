/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verify @ref fgm::CVec2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CVec2TestSetup.h"




/**
 * @addtogroup T_FGM_CVec2_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace
    {
        constexpr fgm::CVec2 vector(1, 2);

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

/** @test Verify that the components are accessible via named spatial aliases (x, y). */
TEST(CVec2AccessTests, AccessibleAsXYZW)
{
    static const fgm::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components are accessible via named spatial aliases (s, t). */
TEST(CVec2AccessTests, AccessibleAsSTPQ)
{
    const fgm::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components are accessible via named spatial aliases (r, g). */
TEST(CVec2AccessTests, AccessibleAsRGBA)
{
    const fgm::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for reads. */
TEST(CVec2AccessTests, AccessibleAsArray)
{
    const fgm::CVec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

/** @test Verify that the components can be mutated via named spatial aliases (x, y). */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingXYZW)
{
    fgm::CVec2<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @test Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::CVec2<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @test Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingRGBA)
{
    fgm::CVec2<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @test Verify that the components are accessible via subscript indexing for writing. */
TEST(CVec2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    fgm::CVec2<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}



/** @} */
