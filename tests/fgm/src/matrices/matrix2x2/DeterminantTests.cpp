/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Matrix2 determinant logic.
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
class Matrix2Determinant: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix              = { fgm::Vector2<T>{ 4, 1 }, fgm::Vector2<T>{ 2, 5 } };
        _expectedDeterminant = 18;
    }
};
/** @brief Test fixture for @ref fgm::Matrix2 determinant, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix2Determinant, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix2 determinant with singular matrices */
class SingularMatrix2Determinant: public ::testing::TestWithParam<fgm::Matrix2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2DeterminantTestSuite, SingularMatrix2Determinant,
                         ::testing::Values(fgm::Matrix2{ fgm::Vector2{ 1.0f, 2.0f }, fgm::Vector2{ 1.0f, 2.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 2.0f, 2.0f }, fgm::Vector2{ 2.0f, 2.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 3.0f, 2.0f }, fgm::Vector2{ 6.0f, 4.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 0.0f, 0.0f }, fgm::Vector2{ 4.0f, 5.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 0.0f, 3.0f }, fgm::Vector2{ 0.0f, 5.0f } }));



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
    constexpr fgm::Matrix2 MAT{ fgm::Vector2{ 4, 2 }, fgm::Vector2{ 3, 4 } };

    // Verify determinant (member function)
    static_assert(MAT.determinant() == 10);

    // Verify determinant (static function)
    static_assert(fgm::Matrix2<int>::determinant(MAT) == 10);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Matrix2Determinant, ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant()); }


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMatrix2Determinant, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Matrix2::determinant returns a non-zero value.
 */
TYPED_TEST(Matrix2Determinant, StaticWrapper_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Matrix2<TypeParam>::determinant(this->_matrix)); }


/**
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Matrix2::determinant returns zero.
 */
TEST_P(SingularMatrix2Determinant, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Matrix2<float>::determinant(matrix));
}

/** @} */
