/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 31, 2026
 *
 * @brief Verify @ref fgm::Transform4 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Transform4TestSetup.h"


/**
 * @addtogroup T_FGM_Transform4_Access
 * @{
 */

namespace
{

    /**************************************
     *                                    *
     *             DEBUG TESTS            *
     *                                    *
     **************************************/

#ifdef ENABLE_DEBUG_TESTS
    #include <utility>


    /// @brief Parameterized Test Fixture for @ref fgm::Transform4 element access/mutation out-of-bounds.
    class Transform4Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {
    public:
        fgm::Transform4<int> transform{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    };
    INSTANTIATE_TEST_SUITE_P(Transform4ElementAccessOutOfBoundsTests, Transform4Indexing,
                             testing::Values(std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(4, 3),
                                             std::make_pair(100, 100)));


    /// @brief Parameterized Test Fixture for @ref fgm::Transform4 vector access/mutation out-of-bounds.
    class Transform4VectorIndexing: public testing::TestWithParam<std::size_t>
    {
    public:
        fgm::Transform4<int> transform{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    };
    INSTANTIATE_TEST_SUITE_P(Transform4VectorAccessOutOfBoundsTests, Transform4VectorIndexing,
                             testing::Values(5, 6, 100));

#endif


    /// @brief Test Fixture for fgm::Transform4 accessors.
    class Transform4Access: public testing::Test
    {
    public:
        fgm::Transform4<float> mat{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f };
    };


    /// @brief Test Fixture for fgm::Transform4 accessors.
    class Transform4Mutation: public testing::Test
    {
    public:
        [[maybe_unused]] fgm::Transform4<float> mat{};
    };



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Transform4<int> MAT{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        constexpr fgm::Vec3 VEC0(1, 5, 9);
        constexpr fgm::Vec3 VEC1(2, 6, 10);
        constexpr fgm::Vec3 VEC2(3, 7, 11);
        constexpr fgm::Vec3 VEC3(4, 8, 12);

        /// @test Verify that matrix elements are accessible as (row, column) at compile time.
        static_assert(MAT(0, 0) == 1);
        static_assert(MAT(0, 1) == 2);
        static_assert(MAT(0, 2) == 3);
        static_assert(MAT(0, 3) == 4);
        static_assert(MAT(1, 0) == 5);
        static_assert(MAT(1, 1) == 6);
        static_assert(MAT(1, 2) == 7);
        static_assert(MAT(1, 3) == 8);
        static_assert(MAT(2, 0) == 9);
        static_assert(MAT(2, 1) == 10);
        static_assert(MAT(2, 2) == 11);
        static_assert(MAT(2, 3) == 12);

        /// @test Verify that matrix columns are accessible as 3D-vectors at compile time.
        static_assert(MAT[0] == VEC0);
        static_assert(MAT[1] == VEC1);
        static_assert(MAT[2] == VEC2);
        static_assert(MAT[3] == VEC3);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

TEST_F(Transform4Access, AccessibleAsElements)
{

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(0, 3));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(8.0f, mat(1, 3));
    EXPECT_FLOAT_EQ(9.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(10.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(11.0f, mat(2, 2));
    EXPECT_FLOAT_EQ(12.0f, mat(2, 3));
}


TEST_F(Transform4Access, AccessibleAsColumnVectors)
{

    EXPECT_VEC_EQ(fgm::Vec3(1.0f, 5.0f, 9.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vec3(2.0f, 6.0f, 10.0f), mat[1]);
    EXPECT_VEC_EQ(fgm::Vec3(3.0f, 7.0f, 11.0f), mat[2]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Transform4 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Transform4VectorIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform[col]), "");
}


/** @brief Verify that @ref fgm::Transform4 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Transform4Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform(row, col)), "");
}

#endif

/** @} */



/**
 * @addtogroup T_FGM_Transform4_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

TEST_F(Transform4Mutation, ElementsCanBeMutatedUsingIndex)
{
    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(0, 2) = 3.0f;
    mat(0, 3) = 4.0f;
    mat(1, 0) = 5.0f;
    mat(1, 1) = 6.0f;
    mat(1, 2) = 7.0f;
    mat(1, 3) = 8.0f;
    mat(2, 0) = 9.0f;
    mat(2, 1) = 10.0f;
    mat(2, 2) = 11.0f;
    mat(2, 3) = 12.0f;


    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(0, 3));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(8.0f, mat(1, 3));
    EXPECT_FLOAT_EQ(9.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(10.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(11.0f, mat(2, 2));
    EXPECT_FLOAT_EQ(12.0f, mat(2, 3));
}


TEST_F(Transform4Access, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vec3 col0 = { 1.0f, 4.0f, 7.0f };
    const fgm::Vec3 col1 = { 2.0f, 5.0f, 8.0f };
    const fgm::Vec3 col2 = { 3.0f, 6.0f, 9.0f };

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @test Verify that @ref fgm::Transform4 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Transform4VectorIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform[col] = fgm::Vec3<int>::zero()), "");
}


/** @test Verify that @ref fgm::Transform4 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Transform4Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(transform(row, col) = 5), "");
}

#endif

/** @} */
