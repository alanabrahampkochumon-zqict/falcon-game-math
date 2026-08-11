/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x2_Access
 * @{
 */

namespace
{

    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3x2 MAT(1, 2, 3, 4, 5, 6);
        constexpr fgm::Vec3 VEC0(1, 3, 5);
        constexpr fgm::Vec3 VEC1(2, 4, 6);

        /// @test Verify that matrix elements are accessible as (row, column) during at compile time.
        static_assert(MAT(0, 0) == 1);
        static_assert(MAT(0, 1) == 2);
        static_assert(MAT(1, 0) == 3);
        static_assert(MAT(1, 1) == 4);
        static_assert(MAT(2, 0) == 5);
        static_assert(MAT(2, 1) == 6);

        /// @test Verify that matrix columns are accessible as 3D-vectors during at compile time.
        static_assert(MAT[0].x() == VEC0[0]);
        static_assert(MAT[0].y() == VEC0[1]);
        static_assert(MAT[0].z() == VEC0[2]);
        static_assert(MAT[1].x() == VEC1[0]);
        static_assert(MAT[1].y() == VEC1[1]);
        static_assert(MAT[1].z() == VEC1[2]);

    } // namespace static_tests
} // namespace



/**************************************
 *            ACCESS TESTS            *
 **************************************/

/** @test Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Mat3x2AccessTests, AccessibleAsElements)
{
    constexpr fgm::Mat3x2 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(5.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(2, 1));
}


/** @test Verify that the matrix columns are accessible as vectors for reads. */
TEST(Mat3x2AccessTests, AccessibleAsColumnVectors)
{
    constexpr fgm::Mat3x2 mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);

    EXPECT_VEC_EQ(fgm::Vec3(1.0f, 3.0f, 5.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vec3(2.0f, 4.0f, 6.0f), mat[1]);
}



/**************************************
 *           MUTATION TESTS           *
 **************************************/

TEST(Mat3x2MutationTests, ElementsCanBeMutatedUsingIndex)
{
    fgm::Mat3x2<float> mat;

    mat(0, 0) = 1.0f;
    mat(0, 1) = 2.0f;
    mat(1, 0) = 3.0f;
    mat(1, 1) = 4.0f;
    mat(2, 0) = 5.0f;
    mat(2, 1) = 6.0f;

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
    EXPECT_FLOAT_EQ(5.0f, mat(2, 0));
    EXPECT_FLOAT_EQ(6.0f, mat(2, 1));
}


TEST(Mat3x2MutationTests, ColumnsCanBeMutatedUsingIndex)
{
    const fgm::Vec3 col0 = { 1.0f, 3.0f, 5.0f };
    const fgm::Vec3 col1 = { 2.0f, 4.0f, 6.0f };
    fgm::Mat3x2<float> mat;

    mat[0] = col0;
    mat[1] = col1;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
}

/** @} */
