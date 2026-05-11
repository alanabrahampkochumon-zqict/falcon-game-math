/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Matrix4D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x4_Access
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
    constexpr fgm::Matrix4D MAT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    constexpr fgm::Vector4D VEC0(1, 5, 9, 13);
    constexpr fgm::Vector4D VEC1(2, 6, 10, 14);
    constexpr fgm::Vector4D VEC2(3, 7, 11, 15);
    constexpr fgm::Vector4D VEC3(4, 8, 12, 16);

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
    static_assert(MAT(3, 0) == 13);
    static_assert(MAT(3, 1) == 14);
    static_assert(MAT(3, 2) == 15);
    static_assert(MAT(3, 3) == 16);

    // Verify that matrix columns are accessible as 3D-vectors during compile time.
    static_assert(MAT[0].x() == VEC0[0]);
    static_assert(MAT[0].y() == VEC0[1]);
    static_assert(MAT[0].z() == VEC0[2]);
    static_assert(MAT[0].w() == VEC0[3]);
    static_assert(MAT[1].x() == VEC1[0]);
    static_assert(MAT[1].y() == VEC1[1]);
    static_assert(MAT[1].z() == VEC1[2]);
    static_assert(MAT[1].w() == VEC1[3]);
    static_assert(MAT[2].x() == VEC2[0]);
    static_assert(MAT[2].y() == VEC2[1]);
    static_assert(MAT[2].z() == VEC2[2]);
    static_assert(MAT[2].w() == VEC2[3]);
    static_assert(MAT[3].x() == VEC3[0]);
    static_assert(MAT[3].y() == VEC3[1]);
    static_assert(MAT[3].z() == VEC3[2]);
    static_assert(MAT[3].w() == VEC3[3]);
} // namespace



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Matrix4DAccess, AccessibleAsElements)
{
    constexpr fgm::Matrix4D mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

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
    EXPECT_FLOAT_EQ(13.0f, mat(3, 0));
    EXPECT_FLOAT_EQ(14.0f, mat(3, 1));
    EXPECT_FLOAT_EQ(15.0f, mat(3, 2));
    EXPECT_FLOAT_EQ(16.0f, mat(3, 3));
}


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Matrix4DAccess, AccessibleAsColumnVectors)
{
    constexpr fgm::Matrix4D mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f,
                                15.0f, 16.0f);

    EXPECT_VEC_EQ(fgm::Vector4D(1.0f, 5.0f, 9.0f, 13.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vector4D(2.0f, 6.0f, 10.0f, 14.0f), mat[1]);
    EXPECT_VEC_EQ(fgm::Vector4D(3.0f, 7.0f, 11.0f, 15.0f), mat[2]);
    EXPECT_VEC_EQ(fgm::Vector4D(4.0f, 8.0f, 12.0f, 16.0f), mat[3]);
}

/** @} */



/**
 * @addtogroup T_FGM_Mat4x4_Mutation
 * @{
 */

/**************************************
 *                                    *
 *           MUTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for writes. */
TEST(Matrix4DAccess, ElementsCanBeMutatedUsingIndex)
{
    fgm::Matrix4D<float> mat;

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
    mat(3, 0) = 13.0f;
    mat(3, 1) = 14.0f;
    mat(3, 2) = 15.0f;
    mat(3, 3) = 16.0f;


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
    EXPECT_FLOAT_EQ(13.0f, mat(3, 0));
    EXPECT_FLOAT_EQ(14.0f, mat(3, 1));
    EXPECT_FLOAT_EQ(15.0f, mat(3, 2));
    EXPECT_FLOAT_EQ(16.0f, mat(3, 3));
}


/** @brief Verify that the matrix columns are accessible as vectors for writes. */
TEST(Matrix4DAccess, ColumnsCanBeMutatedUsingIndex)
{
    constexpr fgm::Vector4D col0 = { 1.0f, 5.0f, 9.0f, 13.0f };
    constexpr fgm::Vector4D col1 = { 2.0f, 6.0f, 10.0f, 14.0f };
    constexpr fgm::Vector4D col2 = { 3.0f, 7.0f, 11.0f, 15.0f };
    constexpr fgm::Vector4D col3 = { 4.0f, 8.0f, 12.0f, 16.0f };
    fgm::Matrix4D<float> mat;

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;
    mat[3] = col3;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
    EXPECT_VEC_EQ(col3, mat[3]);
}
/** @} */