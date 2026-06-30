/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Matrix2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"


#ifdef ENABLE_DEBUG_TESTS
    #include <utility>

class Matrix2Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2Tests, Matrix2Indexing,
                         testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                         std::make_pair(100, 100)));

class Matrix2ColumnIndexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2Tests, Matrix2ColumnIndexing, testing::Values(3, 4, 100));
#endif




/**
 * @addtogroup T_FGM_Mat2x2_Access
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
    constexpr fgm::Matrix2 MAT(1, 2, 3, 4);
    constexpr fgm::Vector2 VEC0(1, 3);
    constexpr fgm::Vector2 VEC1(2, 4);

    // Verify that matrix elements are accessible as (row, column) during compile time.
    static_assert(MAT(0, 0) == 1);
    static_assert(MAT(0, 1) == 2);
    static_assert(MAT(1, 0) == 3);
    static_assert(MAT(1, 1) == 4);

    // Verify that matrix columns are accessible as 2D-vectors during compile time.
    static_assert(MAT[0].x() == VEC0[0]);
    static_assert(MAT[0].y() == VEC0[1]);
    static_assert(MAT[1].x() == VEC1[0]);
    static_assert(MAT[1].y() == VEC1[1]);

} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Matrix2Access, AccessibleAsElements)
{
    constexpr fgm::Matrix2 mat(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
}


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Matrix2Access, AccessibleAsColumnVectors)
{
    constexpr fgm::Matrix2 mat(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_VEC_EQ(fgm::Vector2(1.0f, 3.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vector2(2.0f, 4.0f), mat[1]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Matrix2 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Matrix2ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Matrix2 mat(1, 2);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Matrix2 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Matrix2Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Matrix2 mat(1, 2);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}

#endif

/** @} */



/**
 * @addtogroup T_FGM_Mat2x2_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for writes. */
TEST(Matrix2Access, ElementsCanBeMutatedUsingIndex)
{
    fgm::Matrix2<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(1, 0) = 3.0f;
    mat(1, 1) = 4.0f;

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
}


/** @brief Verify that the matrix columns are accessible as vectors for writes. */
TEST(Matrix2Access, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vector2 col0 = { 1.0f, 3.0f };
    const fgm::Vector2 col1 = { 2.0f, 4.0f };
    fgm::Matrix2<float> mat;

    mat[0] = col0;
    mat[1] = col1;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Matrix2 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Matrix2ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Matrix2 mat(1, 2);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vector2<int>::ZERO()), "");
}


/** @brief Verify that @ref fgm::Matrix2 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Matrix2Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Matrix2 mat(1, 2);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

#endif

/** @} */
