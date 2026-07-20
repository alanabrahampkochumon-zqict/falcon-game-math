/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 20, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x4TestSetup.h"


#ifdef ENABLE_DEBUG_TESTS
    #include <utility>

class Mat3x4Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
{};
INSTANTIATE_TEST_SUITE_P(Mat3x4Tests, Mat3x4Indexing,
                         testing::Values(std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(4, 3),
                                         std::make_pair(100, 100)));

class Mat3x4ColumnIndexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Mat3x4Tests, Mat3x4ColumnIndexing, testing::Values(4, 5, 100));
#endif




/**
 * @addtogroup T_FGM_Mat3x4_Access
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
    constexpr fgm::Mat3x4 MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    constexpr fgm::Vec3 VEC0(1, 5, 9);
    constexpr fgm::Vec3 VEC1(2, 6, 10);
    constexpr fgm::Vec3 VEC2(3, 7, 11);
    constexpr fgm::Vec3 VEC3(4, 8, 12);

    // Verify that matrix elements are accessible as (row, column) during compile time.
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

    static_assert(MAT[3].x() == VEC3[0]);
    static_assert(MAT[3].y() == VEC3[1]);
    static_assert(MAT[3].z() == VEC3[2]);

} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Mat3x4Access, AccessibleAsElements)
{
    constexpr fgm::Mat3x4 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);

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


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Mat3x4Access, AccessibleAsColumnVectors)
{
    constexpr fgm::Mat3x4 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f);

    EXPECT_VEC_EQ(fgm::Vec3(1.0f, 5.0f, 9.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vec3(2.0f, 6.0f, 10.0f), mat[1]);
    EXPECT_VEC_EQ(fgm::Vec3(3.0f, 7.0f, 11.0f), mat[2]);
    EXPECT_VEC_EQ(fgm::Vec3(4.0f, 8.0f, 12.0f), mat[3]);
}


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat3x4 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Mat3x4ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Mat3x4 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Mat3x4Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
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
TEST(Mat3x4Access, ElementsCanBeMutatedUsingIndex)
{
    fgm::Mat3x4<float> mat;

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


/** @brief Verify that the matrix columns are accessible as vectors for writes. */
TEST(Mat3x4Access, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vec3 col0 = { 1.0f, 5.0f, 9.0f };
    const fgm::Vec3 col1 = { 2.0f, 6.0f, 10.0f };
    const fgm::Vec3 col2 = { 3.0f, 7.0f, 11.0f };
    const fgm::Vec3 col3 = { 4.0f, 8.0f, 12.0f };
    fgm::Mat3x4<float> mat;

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

/** @brief Verify that @ref fgm::Mat3x4 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Mat3x4ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec3<int>::zero()), "");
}


/** @brief Verify that @ref fgm::Mat3x4 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Mat3x4Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

#endif

/** @} */
