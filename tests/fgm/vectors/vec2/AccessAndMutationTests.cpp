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


#ifdef ENABLE_DEBUG_TESTS
class Vec2Indexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Vec2Tests, Vec2Indexing, testing::Values(3, 4, 100));
#endif



/**
 * @addtogroup T_FGM_Vec2_Access
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that vector accessors are available at compile time. */
namespace
{
    constexpr fgm::Vec2 vector(1, 2);

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
TEST(Vec2Access, AccessibleAsXYZW)
{
    static const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @brief Verify that the components are accessible via named spatial aliases (s, t). */
TEST(Vec2Access, AccessibleAsSTPQ)
{
    const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @brief Verify that the components are accessible via named spatial aliases (r, g). */
TEST(Vec2Access, AccessibleAsRGBA)
{
    const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @brief Verify that the components are accessible via subscript indexing for reads. */
TEST(Vec2Access, AccessibleAsArray)
{
    const fgm::Vec2 vec(3.0f, 1.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vec2 out-of-bounds access triggers assert in debug mode. */
TEST_P(Vec2Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Vec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}
#endif

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
TEST(Vec2Mutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vec2<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
}


/** @brief Verify that the components can be mutated via named spatial aliases (s, t). */
TEST(Vec2Mutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vec2<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
}


/** @brief Verify that the components can be mutated via named spatial aliases (r, g). */
TEST(Vec2Mutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vec2<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
}


/** @brief Verify that the components are accessible via subscript indexing for writing. */
TEST(Vec2Mutation, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vec2<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
}


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vec2 out-of-bounds mutation triggers assert in debug mode. */
TEST_P(Vec2Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    fgm::Vec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}
#endif

/** @} */
