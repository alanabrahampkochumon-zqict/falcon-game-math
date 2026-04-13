/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D determinants.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Matrix2DDeterminant: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix = { fgm::Vector2D<T>{ 4, 1 }, fgm::Vector2D<T>{ 2, 5 } };
        _expectedDeterminant = 18;
    }
};
/** @brief Test fixture for @ref fgm::Matrix2D determinant, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2DDeterminant, SupportedArithmeticTypes);


class SingularMatrix2D: public ::testing::TestWithParam<fgm::Matrix2D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2DDeterminantTestSuite, SingularMatrix2D,
                         ::testing::Values(fgm::Matrix2D{ fgm::Vector2D{ 1, 2 }, fgm::Vector2D{ 1, 2 } },
                                           fgm::Matrix2D{ fgm::Vector2D{ 2, 2 }, fgm::Vector2D{2, 2} },
                                           fgm::Matrix2D{ fgm::Vector2D{ 3, 2 }, fgm::Vector2D{6, 4} },
                                           fgm::Matrix2D{ fgm::Vector2D{ 0, 0 }, fgm::Vector2D{4, 5} },
                                           fgm::Matrix2D{ fgm::Vector2D{ 0, 3 }, fgm::Vector2D{0, 5} }
                                           ));


/**
 * @addtogroup T_FGM_Mat2x2_Det
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix determinant operation is available at compile time. */
namespace 
{
    constexpr fgm::Matrix2D MATRIX{ fgm::Vector2D{ 4, 2 }, fgm::Vector2D{ 3, 4 } };
    
    // Determinant
    static_assert(MATRIX.determinant() == 10);
    static_assert(fgm::Matrix2D<int>::determinant(MATRIX) == 10);

}



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Matrix2DDeterminant, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMatrix2D, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Matrix2D::determinant returns a non-zero value.
 */
 TYPED_TEST(Matrix2DDeterminant, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Matrix2D<TypeParam>::determinant(this->_matrix));
}


/** 
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Matrix2D::determinant returns zero.
 */
TEST_P(SingularMatrix2D, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Matrix2D<float>::determinant(matrix));
}

/** @} */
