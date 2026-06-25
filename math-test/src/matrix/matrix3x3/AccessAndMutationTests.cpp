/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Matrix3 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



#ifdef ENABLE_DEBUG_TESTS
    #include <utility>

class Matrix3Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix3Tests, Matrix3Indexing,
                         testing::Values(std::make_pair(4, 4), std::make_pair(3, 4), std::make_pair(4, 3),
                                         std::make_pair(100, 100)));

class Matrix3ColumnIndexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Matrix3Tests, Matrix3ColumnIndexing, testing::Values(4, 5, 100));
#endif



/**
 * @addtogroup T_FGM_Mat3x3_Access
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix accessors are available at compile time. */
namespace
{
    constexpr fgm::Matrix3 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr fgm::Vector3 VEC0(1, 4, 7);
    constexpr fgm::Vector3 VEC1(2, 5, 8);
    constexpr fgm::Vector3 VEC2(3, 6, 9);

    // Verify that matrix elements are accessible as (row, column) during compile time.
    static_assert(MAT(0, 0) == 1);
    static_assert(MAT(0, 1) == 2);
    static_assert(MAT(0, 2) == 3);
    static_assert(MAT(1, 0) == 4);
    static_assert(MAT(1, 1) == 5);
    static_assert(MAT(1, 2) == 6);
    static_assert(MAT(2, 0) == 7);
    static_assert(MAT(2, 1) == 8);
    static_assert(MAT(2, 2) == 9);

    // Verify that matrix columns are accessible as 3D-vectors during compile time.
    static_assert(MAT[0].x() == VEC0[0]);
    static_assert(MAT[0].y() == VEC0[1]);
    static_assert(MAT[0].z() == VEC0[2]);
    static_assert(MAT[1].x() == VEC1[0]);
    static_assert(MAT[1].y() == VEC1[1]);
    static_assert(MAT[1].z() == VEC1[2]);
    static_assert(MAT[2].x() == VEC2[0]);
    static_assert(MAT[2].y() == VEC2[1]);
    static_assert(MAT[2].z() == VEC2[2]);
} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Matrix3Access, AccessibleAsElements)
{
    constexpr fgm::Matrix3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(7.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(8.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(9.0f, mat(2, 2));
}


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Matrix3Access, AccessibleAsColumnVectors)
{
    constexpr fgm::Matrix3 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

    EXPECT_VEC_EQ(fgm::Vector3(1.0f, 4.0f, 7.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vector3(2.0f, 5.0f, 8.0f), mat[1]);
    EXPECT_VEC_EQ(fgm::Vector3(3.0f, 6.0f, 9.0f), mat[2]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Matrix3 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Matrix3ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Matrix3 mat(1, 2, 3);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Matrix3 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Matrix3Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Matrix3 mat(1, 2, 3);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}

#endif


/** @} */



/**
 * @addtogroup T_FGM_Mat3x3_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for writes. */
TEST(Matrix3Access, ElementsCanBeMutatedUsingIndex)
{
    fgm::Matrix3<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(0, 2) = 3.0f;
    mat(1, 0) = 4.0f;
    mat(1, 1) = 5.0f;
    mat(1, 2) = 6.0f;
    mat(2, 0) = 7.0f;
    mat(2, 1) = 8.0f;
    mat(2, 2) = 9.0f;


    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(7.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(8.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(9.0f, mat(2, 2));
}


/** @brief Verify that the matrix columns are accessible as vectors for writes. */
TEST(Matrix3Access, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vector3 col0 = { 1.0f, 4.0f, 7.0f };
    const fgm::Vector3 col1 = { 2.0f, 5.0f, 8.0f };
    const fgm::Vector3 col2 = { 3.0f, 6.0f, 9.0f };
    fgm::Matrix3<float> mat;

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Matrix3 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Matrix3ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Matrix3 mat(1, 2, 3);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::vec3d::zero<int>), "");
}


/** @brief Verify that @ref fgm::Matrix3 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Matrix3Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Matrix3 mat(1, 2, 3);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

#endif

/** @} */
