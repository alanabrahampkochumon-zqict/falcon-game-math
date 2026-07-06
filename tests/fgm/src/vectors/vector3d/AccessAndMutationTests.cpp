/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 10, 2026
 *
 * @brief Verify @ref fgm::Vector3 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3TestSetup.h"



#ifdef ENABLE_DEBUG_TESTS
class Vector3Indexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Vector2Tests, Vector3Indexing, testing::Values(4, 5, 100));
#endif



/**
 * @addtogroup T_FGM_Vec3_Access
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
    constexpr fgm::Vector3 vector(1, 2, 3);

    static_assert(vector.x() == 1);
    static_assert(vector.y() == 2);
    static_assert(vector.z() == 3);

    static_assert(vector.r() == 1);
    static_assert(vector.g() == 2);
    static_assert(vector.b() == 3);

    static_assert(vector.s() == 1);
    static_assert(vector.t() == 2);
    static_assert(vector.p() == 3);
} // namespace


/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the components are accessible via named spatial aliases (x, y, z). */
TEST(Vector3Access, AccessibleAsXYZW)
{
    const fgm::Vector3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
}


/** @brief Verify that the components are accessible via named spatial aliases (s, t, p). */
TEST(Vector3Access, AccessibleAsSTPQ)
{
    const fgm::Vector3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
}


/** @brief Verify that the components are accessible via named spatial aliases (r, g, b). */
TEST(Vector3Access, AccessibleAsRGBA)
{
    const fgm::Vector3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
}


/** @brief Verify that the components are accessible via subscript indexing for reads. */
TEST(Vector3Access, AccessibleAsArray)
{
    const fgm::Vector3 vec(3.0f, 1.0f, 6.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vector3 out-of-bounds access triggers assert in debug mode. */
TEST_P(Vector3Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Vector3 vec(1, 2, 3);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}
#endif

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

/** @brief Verify that the components can be mutated via named spatial aliases (x, y, z). */
TEST(Vector3Mutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vector3<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;
    vec.z() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
}


/** @brief Verify that the components can be mutated via named spatial aliases (s, t, p). */
TEST(Vector3Mutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vector3<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;
    vec.p() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
}


/** @brief Verify that the components can be mutated via named spatial aliases (r, g, b). */
TEST(Vector3Mutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vector3<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;
    vec.b() = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
}


/** @brief Verify that the components are accessible via subscript indexing for writing. */
TEST(Vector3Mutation, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vector3<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
}

#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vector3 out-of-bounds mutation triggers assert in debug mode. */
TEST_P(Vector3Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    fgm::Vector3 vec(1, 2, 3);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}
#endif

/** @} */
