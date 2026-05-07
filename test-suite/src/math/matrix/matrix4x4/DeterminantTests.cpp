/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref fgm::Matrix4D determinant logic.
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
class Matrix4DDeterminant: public ::testing::Test
{
protected:
    fgm::Matrix4D<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix = { { T(1), T(2), T(3), T(4) },
                    { T(1), T(2), T(1), T(3) },
                    { T(2), T(3), T(4), T(12) },
                    { T(2), T(1), T(3), T(2) } };
        _expectedDeterminant = T(39);
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D determinant, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix4DDeterminant, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix4D determinant with singular matrices */
class SingularMatrix4DDeterminant: public ::testing::TestWithParam<fgm::Matrix4D<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Matrix4DDeterminantTestSuite, SingularMatrix4DDeterminant,
    ::testing::Values(fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vector4D{ 1.0f, 2.0f, 3.0f, 4.0f },
                                     fgm::Vector4D{ 7.0f, 8.0f, 9.0f, 12.0f }, fgm::Vector4D { 2.5f, 6.1f, 31.6f, 2.0f} }
                                     // ,
                      // fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 1.0f, 5.0f }, fgm::Vector4D{ 2.0f, 2.0f, 3.0f },
                      //                fgm::Vector4D{ 3.0f, 3.0f, 9.0f } },
                      // fgm::Matrix4D{ fgm::Vector4D{ 0.0f, 0.0f, 0.0f }, fgm::Vector4D{ 1.0f, 2.0f, 3.0f },
                      //                fgm::Vector4D{ 1.0f, 8.0f, 9.0f } },
                      // fgm::Matrix4D{ fgm::Vector4D{ 0.0f, 5.0f, 1.0f }, fgm::Vector4D{ 0.0f, 2.0f, 3.0f },
                      //                fgm::Vector4D{ 0.0f, 8.0f, 9.0f } },
                      // fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 2.0f, 3.0f }, fgm::Vector4D{ 2.0f, 4.0f, 6.0f },
                      //                fgm::Vector4D{ 7.0f, 8.0f, 9.0f } },
                      // fgm::Matrix4D{ fgm::Vector4D{ 1.0f, 2.0f, 1.0f }, fgm::Vector4D{ 2.0f, 4.0f, 3.0f },
                                     // fgm::Vector4D{ 3.0f, 6.0f, 9.0f } }
));



/**
 * @addtogroup T_FGM_Mat4x4_Det
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
    constexpr fgm::Matrix4D MAT{ fgm::Vector4D{ 1, 2, 3, 4 }, fgm::Vector4D{ 1, 2, 1, 3 }, fgm::Vector4D{ 2, 3, 4, 12 }, fgm::Vector4D{ 2, 1, 3, 2 } };

    // Verify determinant (member function)
    // static_assert(MAT.determinant() == 39);

    // Verify determinant (static function)
    // static_assert(fgm::Matrix4D<int>::determinant(MAT) == 39);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Matrix4DDeterminant, ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant()); }


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMatrix4DDeterminant, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Matrix4D::determinant returns a non-zero value.
 */
TYPED_TEST(Matrix4DDeterminant, StaticWrapper_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Matrix4D<TypeParam>::determinant(this->_matrix)); }


/**
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Matrix4D::determinant returns zero.
 */
TEST_P(SingularMatrix4DDeterminant, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Matrix4D<float>::determinant(matrix));
}

/** @} */
