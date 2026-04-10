/**
 * @file AccessAndMutationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D accessors and mutators.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



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
    constexpr fgm::Matrix2D matrix(1, 2, 3, 4);
    constexpr fgm::Vector2D vec0(1, 3);
    constexpr fgm::Vector2D vec1(2, 4);

    // Verify that matrix elements are accessible as (row, column) during compile time.
    static_assert(matrix(0, 0) == 1);
    static_assert(matrix(0, 1) == 2);
    static_assert(matrix(1, 0) == 3);
    static_assert(matrix(1, 1) == 4);

    // Verify that matrix columns are accessible as 2D-vectors during compile time.
    static_assert(matrix[0].x() == vec0[0]);
    static_assert(matrix[0].y() == vec0[1]);
    static_assert(matrix[1].x() == vec1[0]);
    static_assert(matrix[1].y() == vec1[1]);
}



/**************************************
 *                                    *
 *            ACCESS TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that the matrix elements are accessible via subscript indexing for reads. */
TEST(Matrix2DAccess, AccessibleAsElements)
{
    constexpr fgm::Matrix2D mat(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_FLOAT_EQ(1.0f, mat(0, 0));
    EXPECT_FLOAT_EQ(2.0f, mat(0, 1));
    EXPECT_FLOAT_EQ(3.0f, mat(1, 0));
    EXPECT_FLOAT_EQ(4.0f, mat(1, 1));
}


/** @brief Verify that the matrix columns are accessible as vectors for reads. */
TEST(Matrix2DAccess, AccessibleAsColumnVectors)
{
    constexpr fgm::Matrix2D mat(1.0f, 2.0f, 3.0f, 4.0f);

    EXPECT_VEC_EQ(fgm::Vector2D(1.0f, 3.0f), mat[0]);
    EXPECT_VEC_EQ(fgm::Vector2D(2.0f, 4.0f), mat[1]);
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
TEST(Matrix2DAccess, ElementsCanBeMutatedUsingIndex)
{
    fgm::Matrix2D<float> mat;

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
TEST(Matrix2DAccess, ColumnsCanBeMutatedUsingIndex)
{
    constexpr fgm::Vector2D col1 = {1.0f, 3.0f};
    constexpr fgm::Vector2D col2 = {2.0f, 4.0f};
    fgm::Matrix2D<float> mat;

    mat[0] = col1;
    mat[1] = col2;

    EXPECT_VEC_EQ(col1, mat[0]);
    EXPECT_VEC_EQ(col2, mat[1]);
}
/** @} */