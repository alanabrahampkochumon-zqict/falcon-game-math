/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector4 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4TestSetup.h"



#ifdef ENABLE_DEBUG_TESTS
class Vector4Indexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Vector3Tests, Vector4Indexing, testing::Values(4, 5, 100));
#endif



/**
 * @addtogroup T_FGM_Vec4_Access
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
    constexpr fgm::Vector4 vector(1, 2, 3, 4);

    static_assert(vector.x() == 1);
    static_assert(vector.y() == 2);
    static_assert(vector.z() == 3);
    static_assert(vector.w() == 4);

    static_assert(vector.r() == 1);
    static_assert(vector.g() == 2);
    static_assert(vector.b() == 3);
    static_assert(vector.a() == 4);

    static_assert(vector.s() == 1);
    static_assert(vector.t() == 2);
    static_assert(vector.p() == 3);
    static_assert(vector.q() == 4);
} // namespace


/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the components are accessible via named spatial aliases (x, y, z, w). */
TEST(Vector4Access, AccessibleAsXYZW)
{
    const fgm::Vector4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
    EXPECT_FLOAT_EQ(2.0f, vec.w());
}


/** @brief Verify that the components are accessible via named spatial aliases (s, t, p, q). */
TEST(Vector4Access, AccessibleAsSTPQ)
{
    const fgm::Vector4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
    EXPECT_FLOAT_EQ(2.0f, vec.q());
}


/** @brief Verify that the components are accessible via named spatial aliases (r, g, b, a). */
TEST(Vector4Access, AccessibleAsRGBA)
{
    const fgm::Vector4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
    EXPECT_FLOAT_EQ(2.0f, vec.a());
}


/** @brief Verify that the components are accessible via subscript indexing for reads. */
TEST(Vector4Access, AccessibleAsArray)
{
    const fgm::Vector4 vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vector4 out-of-bounds access triggers assert in debug mode. */
TEST_P(Vector4Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Vector4 vec(1, 2, 3, 4);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}
#endif

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

/** @brief Verify that the components can be mutated via named spatial aliases (x, y, z, w). */
TEST(Vector4Mutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vector4<float> vec;

    vec.x() = 3.0f;
    vec.y() = 1.0f;
    vec.z() = 6.0f;
    vec.w() = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
    EXPECT_FLOAT_EQ(2.0f, vec.w());
}


/** @brief Verify that the components can be mutated via named spatial aliases (s, t, p, q). */
TEST(Vector4Mutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vector4<float> vec;

    vec.s() = 3.0f;
    vec.t() = 1.0f;
    vec.p() = 6.0f;
    vec.q() = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
    EXPECT_FLOAT_EQ(2.0f, vec.q());
}


/** @brief Verify that the components can be mutated via named spatial aliases (r, g, b, a). */
TEST(Vector4Mutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vector4<float> vec;

    vec.r() = 3.0f;
    vec.g() = 1.0f;
    vec.b() = 6.0f;
    vec.a() = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
    EXPECT_FLOAT_EQ(2.0f, vec.a());
}


/** @brief Verify that the components are accessible via subscript indexing for writing. */
TEST(Vector4Mutation, ElementsCanBeMutatedUsingIndex)
{
    fgm::Vector4<float> vec;

    vec[0] = 3.0f;
    vec[1] = 1.0f;
    vec[2] = 6.0f;
    vec[3] = 2.0f;

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}

#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vector4 out-of-bounds mutation triggers assert in debug mode. */
TEST_P(Vector4Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    fgm::Vector4 vec(1, 2, 3, 4);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}
#endif

/** @} */
