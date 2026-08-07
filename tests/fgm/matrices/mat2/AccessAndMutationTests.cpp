/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Mat2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"


/**
 * @addtogroup T_FGM_Mat2x2_Access
 * @{
 */

namespace
{
    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2 MAT(1, 2, 3, 4);
        constexpr fgm::Vec2 VEC0(1, 3);
        constexpr fgm::Vec2 VEC1(2, 4);

        /// @test Verify that matrix elements are accessible as (row, column) at compile time.
        static_assert(MAT(0, 0) == 1);
        static_assert(MAT(0, 1) == 2);
        static_assert(MAT(1, 0) == 3);
        static_assert(MAT(1, 1) == 4);

        /// @test Verify that matrix columns are accessible as 2D-vectors at compile time.
        static_assert(MAT[0].x() == VEC0[0]);
        static_assert(MAT[0].y() == VEC0[1]);
        static_assert(MAT[1].x() == VEC1[0]);
        static_assert(MAT[1].y() == VEC1[1]);

    } // namespace static_tests

} // namespace



/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Mat2AccessTests, AccessibleAsElements)
{
    constexpr fgm::Mat2 mat(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
}


/** @test Verify that the matrix columns are accessible as vectors for reads. */
TEST(Mat2AccessTests, AccessibleAsColumnVectors)
{
    constexpr fgm::Mat2 mat(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_VEC_EQ(fgm::Vec2(1.0f, 3.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vec2(2.0f, 4.0f), mat[1]);
}

/** @} */



/**
 * @addtogroup T_FGM_Mat2x2_Mutation
 * @{
 */

/**************************************
 *           MUTATION TESTS           *
**************************************/

/** @test Verify that the matrix elements are accessible via subscript indexing for writes. */
TEST(Mat2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    fgm::Mat2<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(1, 0) = 3.0f;
    mat(1, 1) = 4.0f;

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
}


/** @test Verify that the matrix columns are accessible as vectors for writes. */
TEST(Mat2MutationTests, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vec2 col0 = { 1.0f, 3.0f };
    const fgm::Vec2 col1 = { 2.0f, 4.0f };
    fgm::Mat2<float> mat;

    mat[0] = col0;
    mat[1] = col1;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
}

/** @} */
