/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"


#ifdef ENABLE_DEBUG_TESTS
    #include <utility>

class Mat4x2Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
{};
INSTANTIATE_TEST_SUITE_P(Mat4x2Tests, Mat4x2Indexing,
                         testing::Values(std::make_pair(3, 3), std::make_pair(4, 2), std::make_pair(2, 4),
                                         std::make_pair(100, 100)));

class Mat4x2ColumnIndexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Mat4x2Tests, Mat4x2ColumnIndexing, testing::Values(2, 3, 100));
#endif




/**
 * @addtogroup T_FGM_Mat4x2_Access
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
    constexpr fgm::Mat4x2 MAT(1, 2, 3, 4, 5, 6, 7, 8);
    constexpr fgm::Vec4 VEC0(1, 3, 5, 7);
    constexpr fgm::Vec4 VEC1(2, 4, 6, 8);

    // Verify that matrix elements are accessible as (row, column) during compile time.
    static_assert(MAT(0, 0) == 1);
    static_assert(MAT(0, 1) == 2);
    static_assert(MAT(1, 0) == 3);
    static_assert(MAT(1, 1) == 4);
    static_assert(MAT(2, 0) == 5);
    static_assert(MAT(2, 1) == 6);
    static_assert(MAT(3, 0) == 7);
    static_assert(MAT(3, 1) == 8);

    // Verify that matrix columns are accessible as 4D-vectors during compile time.
    static_assert(MAT[0].x() == VEC0[0]);
    static_assert(MAT[0].y() == VEC0[1]);
    static_assert(MAT[0].z() == VEC0[2]);
    static_assert(MAT[0].w() == VEC0[3]);
    static_assert(MAT[1].x() == VEC1[0]);
    static_assert(MAT[1].y() == VEC1[1]);
    static_assert(MAT[1].z() == VEC1[2]);
    static_assert(MAT[1].w() == VEC1[3]);

} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Mat4x2Access, AccessibleAsElements)
{
    constexpr fgm::Mat4x2 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(5.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(2, 1));
}


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Mat4x2Access, AccessibleAsColumnVectors)
{
    constexpr fgm::Mat4x2 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

    EXPECT_VEC_EQ(fgm::Vec4(1.0f, 3.0f, 5.0f, 7.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vec4(2.0f, 4.0f, 6.0f, 8.0f), mat[1]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat4x2 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Mat4x2ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat4x2 mat(1, 2, 3, 4, 5, 6, 7, 8);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Mat4x2 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Mat4x2Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat4x2 mat(1, 2, 3, 4, 5, 6, 7, 8);
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
TEST(Mat4x2Access, ElementsCanBeMutatedUsingIndex)
{
    fgm::Mat4x2<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(1, 0) = 3.0f;
    mat(1, 1) = 4.0f;
    mat(2, 0) = 5.0f;
    mat(2, 1) = 6.0f;
    mat(3, 0) = 7.0f;
    mat(3, 1) = 8.0f;

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(5.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(2, 1));
    EXPECT_FLOAT_EQ(7.0f, mat(3, 0));
    EXPECT_FLOAT_EQ(8.0f, mat(3, 1));
}


/** @brief Verify that the matrix columns are accessible as vectors for writes. */
TEST(Mat4x2Access, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vec4 col0 = { 1.0f, 3.0f, 5.0f, 7.0f };
    const fgm::Vec4 col1 = { 2.0f, 4.0f, 6.0f, 8.0f };
    fgm::Mat4x2<float> mat;

    mat[0] = col0;
    mat[1] = col1;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat4x2 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Mat4x2ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat4x2 mat(1, 2, 3, 4, 5, 6, 7, 8);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec4<int>::zero()), "");
}


/** @brief Verify that @ref fgm::Mat4x2 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Mat4x2Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat4x2 mat(1, 2, 3, 4, 5, 6, 7, 8);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

#endif

/** @} */
