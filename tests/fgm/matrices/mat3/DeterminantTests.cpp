/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 27, 2026
 *
 * @brief Verify @ref fgm::Mat3 determinant logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat3TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat3Determinant: public ::testing::Test
{
protected:
    fgm::Mat3<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix              = { { T(3), T(4), T(2) }, { T(1), T(1), T(1) }, { T(2), T(1), T(2) } };
        _expectedDeterminant = static_cast<T>(1);
    }
};
/** @brief Test fixture for @ref fgm::Mat3 determinant, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Mat3Determinant, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Mat3 determinant with singular matrices */
class SingularMat3Determinant: public ::testing::TestWithParam<fgm::Mat3<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Mat3DeterminantTestSuite, SingularMat3Determinant,
    ::testing::Values(
        fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 7.0f, 8.0f, 9.0f } },
        fgm::Mat3{ fgm::Vec3{ 1.0f, 1.0f, 5.0f }, fgm::Vec3{ 2.0f, 2.0f, 3.0f }, fgm::Vec3{ 3.0f, 3.0f, 9.0f } },
        fgm::Mat3{ fgm::Vec3{ 0.0f, 0.0f, 0.0f }, fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 1.0f, 8.0f, 9.0f } },
        fgm::Mat3{ fgm::Vec3{ 0.0f, 5.0f, 1.0f }, fgm::Vec3{ 0.0f, 2.0f, 3.0f }, fgm::Vec3{ 0.0f, 8.0f, 9.0f } },
        fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 2.0f, 4.0f, 6.0f }, fgm::Vec3{ 7.0f, 8.0f, 9.0f } },
        fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 1.0f }, fgm::Vec3{ 2.0f, 4.0f, 3.0f }, fgm::Vec3{ 3.0f, 6.0f, 9.0f } }));



/**
 * @addtogroup T_FGM_Mat3x3_Det
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
    constexpr fgm::Mat3 MAT{ fgm::Vec3{ 1, 2, 5 }, fgm::Vec3{ 5, 1, 7 }, fgm::Vec3{ 8, 9, 10 } };

    // Verify determinant (member function)
    static_assert(MAT.determinant() == 144);

    // Verify determinant (static function)
    static_assert(fgm::Mat3<int>::determinant(MAT) == 144);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Mat3Determinant, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMat3Determinant, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Mat3::determinant returns a non-zero value.
 */
TYPED_TEST(Mat3Determinant, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Mat3<TypeParam>::determinant(this->_matrix));
}


/**
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Mat3::determinant returns zero.
 */
TEST_P(SingularMat3Determinant, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Mat3<float>::determinant(matrix));
}

/** @} */
