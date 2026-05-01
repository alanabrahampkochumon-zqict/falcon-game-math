/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Matrix3D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



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
    constexpr fgm::Matrix3D MAT(1, 2, 3, 4, 5, 6, 7, 8, 9);
    constexpr fgm::Vector3D VEC0(1, 4, 7);
    constexpr fgm::Vector3D VEC1(2, 5, 8);
    constexpr fgm::Vector3D VEC2(3, 6, 9);

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
TEST(Matrix3DAccess, AccessibleAsElements)
{
    constexpr fgm::Matrix3D mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

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
TEST(Matrix3DAccess, AccessibleAsColumnVectors)
{
    constexpr fgm::Matrix3D mat(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

    EXPECT_VEC_EQ(fgm::Vector3D(1.0f, 4.0f, 7.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vector3D(2.0f, 5.0f, 8.0f), mat[1]);
    EXPECT_VEC_EQ(fgm::Vector3D(3.0f, 6.0f, 9.0f), mat[2]);
}

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
TEST(Matrix3DAccess, ElementsCanBeMutatedUsingIndex)
{
    fgm::Matrix3D<float> mat;

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
TEST(Matrix3DAccess, ColumnsCanBeMutatedUsingIndex)
{
    constexpr fgm::Vector3D col0 = { 1.0f, 4.0f, 7.0f };
    constexpr fgm::Vector3D col1 = { 2.0f, 5.0f, 8.0f };
    constexpr fgm::Vector3D col2 = { 3.0f, 6.0f, 9.0f };
    fgm::Matrix3D<float> mat;

    mat[0] = col0;
    mat[1] = col1;
    mat[2] = col2;

    EXPECT_VEC_EQ(col0, mat[0]);
    EXPECT_VEC_EQ(col1, mat[1]);
    EXPECT_VEC_EQ(col2, mat[2]);
}
/** @} */