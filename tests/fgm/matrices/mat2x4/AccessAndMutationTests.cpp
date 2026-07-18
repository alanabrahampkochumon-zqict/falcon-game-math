/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2x4TestSetup.h"


#ifdef ENABLE_DEBUG_TESTS
    #include <utility>

class Mat2x4Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
{};
INSTANTIATE_TEST_SUITE_P(Mat2x4Tests, Mat2x4Indexing,
                         testing::Values(std::make_pair(2, 4), std::make_pair(2, 3), std::make_pair(3, 2),
                                         std::make_pair(100, 100)));

class Mat2x4ColumnIndexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Mat2x4Tests, Mat2x4ColumnIndexing, testing::Values(4, 5, 100));
#endif




/**
 * @addtogroup T_FGM_Mat2x4_Access
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
    constexpr fgm::Mat2x4 MAT(1, 2, 3, 4, 5, 6, 7, 8);
    constexpr fgm::Vec2 VEC0(1, 5);
    constexpr fgm::Vec2 VEC1(2, 6);
    constexpr fgm::Vec2 VEC2(3, 7);
    constexpr fgm::Vec2 VEC3(4, 8);

    // Verify that matrix elements are accessible as (row, column) during compile time.
    static_assert(MAT(0, 0) == 1);
    static_assert(MAT(0, 1) == 2);
    static_assert(MAT(0, 2) == 3);
    static_assert(MAT(0, 3) == 4);
    static_assert(MAT(1, 0) == 5);
    static_assert(MAT(1, 1) == 6);
    static_assert(MAT(1, 2) == 7);
    static_assert(MAT(1, 3) == 8);

    // Verify that matrix columns are accessible as 2D-vectors during compile time.
    static_assert(MAT[0].x() == VEC0[0]);
    static_assert(MAT[0].y() == VEC0[1]);
    static_assert(MAT[1].x() == VEC1[0]);
    static_assert(MAT[1].y() == VEC1[1]);
    static_assert(MAT[2].x() == VEC2[0]);
    static_assert(MAT[2].y() == VEC2[1]);
    static_assert(MAT[3].x() == VEC3[0]);
    static_assert(MAT[3].y() == VEC3[1]);

} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Mat2x4Access, AccessibleAsElements)
{
    constexpr fgm::Mat2x4 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(0, 3));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(8.0f, mat(1, 3));
}


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Mat2x4Access, AccessibleAsColumnVectors)
{
    constexpr fgm::Mat2x4 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_VEC_EQ(fgm::Vec2(1.0f, 5.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vec2(2.0f, 6.0f), mat[1]);
    EXPECT_VEC_EQ(fgm::Vec2(3.0f, 7.0f), mat[2]);
    EXPECT_VEC_EQ(fgm::Vec2(4.0f, 8.0f), mat[3]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat2x4 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Mat2x4ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat2x4 mat(1, 2, 3, 4, 5, 6, 7, 8);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Mat2x4 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Mat2x4Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat2x4 mat(1, 2, 3, 4, 5, 6, 7, 8);
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
TEST(Mat2x4Access, ElementsCanBeMutatedUsingIndex)
{
    fgm::Mat2x4<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(0, 2) = 3.0f;
    mat(0, 3) = 4.0f;
    mat(1, 0) = 5.0f;
    mat(1, 1) = 6.0f;
    mat(1, 2) = 7.0f;
    mat(1, 3) = 8.0f;

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(0, 2));
    EXPECT_FLOAT_EQ(4.0f, mat(0, 3));
    EXPECT_FLOAT_EQ(5.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(1, 2));
    EXPECT_FLOAT_EQ(8.0f, mat(1, 3));
}


/** @brief Verify that the matrix columns are accessible as vectors for writes. */
TEST(Mat2x4Access, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vec2 col0 = { 1.0f, 5.0f };
    const fgm::Vec2 col1 = { 2.0f, 6.0f };
    const fgm::Vec2 col2 = { 3.0f, 7.0f };
    const fgm::Vec2 col3 = { 4.0f, 8.0f };
    fgm::Mat2x4<float> mat;

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;
    mat[3] = col3;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
    EXPECT_VEC_EQ(col3, mat[3]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat2x4 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Mat2x4ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat2x4 mat(1, 2, 3, 4, 5, 6, 7, 8);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec2<int>::zero()), "");
}


/** @brief Verify that @ref fgm::Mat2x4 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Mat2x4Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat2x4 mat(1, 2, 3, 4, 5, 6, 7, 8);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

#endif

/** @} */
