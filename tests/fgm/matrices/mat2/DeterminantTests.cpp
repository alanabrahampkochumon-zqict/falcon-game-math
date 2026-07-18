/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Mat2 determinant logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat2TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat2Determinant: public ::testing::Test
{
protected:
    fgm::Mat2<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix              = { fgm::Vec2<T>{ 4, 1 }, fgm::Vec2<T>{ 2, 5 } };
        _expectedDeterminant = 18;
    }
};
/** @brief Test fixture for @ref fgm::Mat2 determinant, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Mat2Determinant, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Mat2 determinant with singular matrices */
class SingularMat2Determinant: public ::testing::TestWithParam<fgm::Mat2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Mat2DeterminantTestSuite, SingularMat2Determinant,
                         ::testing::Values(fgm::Mat2{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ 1.0f, 2.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 2.0f, 2.0f }, fgm::Vec2{ 2.0f, 2.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 3.0f, 2.0f }, fgm::Vec2{ 6.0f, 4.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 0.0f, 0.0f }, fgm::Vec2{ 4.0f, 5.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 0.0f, 3.0f }, fgm::Vec2{ 0.0f, 5.0f } }));



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
    constexpr fgm::Mat2 MAT{ fgm::Vec2{ 4, 2 }, fgm::Vec2{ 3, 4 } };

    // Verify determinant (member function)
    static_assert(MAT.determinant() == 10);

    // Verify determinant (static function)
    static_assert(fgm::Mat2<int>::determinant(MAT) == 10);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Mat2Determinant, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMat2Determinant, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Mat2::determinant returns a non-zero value.
 */
TYPED_TEST(Mat2Determinant, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Mat2<TypeParam>::determinant(this->_matrix));
}


/**
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Mat2::determinant returns zero.
 */
TEST_P(SingularMat2Determinant, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Mat2<float>::determinant(matrix));
}

/** @} */
