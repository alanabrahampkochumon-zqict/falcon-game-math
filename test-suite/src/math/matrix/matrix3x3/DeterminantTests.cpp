/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verify @ref fgm::Matrix3D determinant logic.
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
class Matrix3DDeterminant: public ::testing::Test
{
protected:
    fgm::Matrix3D<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix = { { T(1), T(2), T(5) }, { T(5), T(1), T(7) }, { T(8), T(9), T(10) } };
        _expectedDeterminant = 144;
    }
};
/** @brief Test fixture for @ref fgm::Matrix3D determinant, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix3DDeterminant, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix3D determinant with singular matrices */
class SingularMatrix3DDeterminant: public ::testing::TestWithParam<fgm::Matrix3D<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Matrix3DDeterminantTestSuite, SingularMatrix3DDeterminant,
    ::testing::Values(fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 2.0f, 3.0f }, fgm::Vector3D{ 1.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 7.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 1.0f, 5.0f }, fgm::Vector3D{ 2.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 3.0f, 3.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 0.0f, 0.0f, 0.0f }, fgm::Vector3D{ 1.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 1.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 0.0f, 5.0f, 1.0f }, fgm::Vector3D{ 0.0f, 2.0f, 3.0f },
                                     fgm::Vector3D{ 0.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 2.0f, 3.0f }, fgm::Vector3D{ 2.0f, 4.0f, 6.0f },
                                     fgm::Vector3D{ 7.0f, 8.0f, 9.0f } },
                      fgm::Matrix3D{ fgm::Vector3D{ 1.0f, 2.0f, 1.0f }, fgm::Vector3D{ 2.0f, 4.0f, 3.0f },
                                     fgm::Vector3D{ 3.0f, 6.0f, 9.0f } }));



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
    constexpr fgm::Matrix3D MAT{ fgm::Vector3D{ 1, 2, 5 }, fgm::Vector3D{ 5, 1, 7 }, fgm::Vector3D{ 8, 9, 10 } };

    // Verify determinant (member function)
    static_assert(MAT.determinant() == 144);

    // Verify determinant (static function)
    static_assert(fgm::Matrix3D<int>::determinant(MAT) == 144);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Matrix3DDeterminant, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMatrix3DDeterminant, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Matrix3D::determinant returns a non-zero value.
 */
TYPED_TEST(Matrix3DDeterminant, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Matrix3D<TypeParam>::determinant(this->_matrix));
}


/**
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Matrix3D::determinant returns zero.
 */
TEST_P(SingularMatrix3DDeterminant, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Matrix3D<float>::determinant(matrix));
}

/** @} */
