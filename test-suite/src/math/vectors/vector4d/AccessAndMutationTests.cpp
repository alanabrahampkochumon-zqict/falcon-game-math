/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vector4D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"



#ifdef ENABLE_DEBUG_TESTS
class Vector4DIndexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Vector3DTests, Vector4DIndexing, testing::Values(4, 5, 100));
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
    constexpr fgm::Vector4D vector(1, 2, 3, 4);

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
TEST(Vector4DAccess, AccessibleAsXYZW)
{
    const fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.x());
    EXPECT_FLOAT_EQ(1.0f, vec.y());
    EXPECT_FLOAT_EQ(6.0f, vec.z());
    EXPECT_FLOAT_EQ(2.0f, vec.w());
}


/** @brief Verify that the components are accessible via named spatial aliases (s, t, p, q). */
TEST(Vector4DAccess, AccessibleAsSTPQ)
{
    const fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.s());
    EXPECT_FLOAT_EQ(1.0f, vec.t());
    EXPECT_FLOAT_EQ(6.0f, vec.p());
    EXPECT_FLOAT_EQ(2.0f, vec.q());
}


/** @brief Verify that the components are accessible via named spatial aliases (r, g, b, a). */
TEST(Vector4DAccess, AccessibleAsRGBA)
{
    const fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec.r());
    EXPECT_FLOAT_EQ(1.0f, vec.g());
    EXPECT_FLOAT_EQ(6.0f, vec.b());
    EXPECT_FLOAT_EQ(2.0f, vec.a());
}


/** @brief Verify that the components are accessible via subscript indexing for reads. */
TEST(Vector4DAccess, AccessibleAsArray)
{
    const fgm::Vector4D vec(3.0f, 1.0f, 6.0f, 2.0f);

    EXPECT_FLOAT_EQ(3.0f, vec[0]);
    EXPECT_FLOAT_EQ(1.0f, vec[1]);
    EXPECT_FLOAT_EQ(6.0f, vec[2]);
    EXPECT_FLOAT_EQ(2.0f, vec[3]);
}


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vector4D out-of-bounds access triggers assert in debug mode. */
TEST_P(Vector4DIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Vector4D vec(1, 2, 3, 4);
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
TEST(Vector4DMutation, ElementsCanBeMutatedUsingXYZW)
{
    fgm::Vector4D<float> vec;

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
TEST(Vector4DMutation, ElementsCanBeMutatedUsingSTPQ)
{
    fgm::Vector4D<float> vec;

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
TEST(Vector4DMutation, ElementsCanBeMutatedUsingRGBA)
{
    fgm::Vector4D<float> vec;

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

#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vector4D out-of-bounds mutation triggers assert in debug mode. */
TEST_P(Vector4DIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    fgm::Vector4D vec(1, 2, 3, 4);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}
#endif

/** @} */
