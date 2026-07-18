/**
 * @file DeterminantTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 07, 2026
 *
 * @brief Verify @ref fgm::Mat4 determinant logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat4TestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat4Determinant: public ::testing::Test
{
protected:
    fgm::Mat4<T> _matrix;
    T _expectedDeterminant;

    void SetUp() override
    {
        _matrix              = { { T(1), T(2), T(3), T(4) },
                                 { T(1), T(2), T(1), T(3) },
                                 { T(2), T(3), T(4), T(12) },
                                 { T(2), T(1), T(3), T(2) } };
        _expectedDeterminant = T(39);
    }
};
/** @brief Test fixture for @ref fgm::Mat4 determinant, parameterized by @ref SupportedSignedArithmeticTypes. */
TYPED_TEST_SUITE(Mat4Determinant, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Mat4 determinant with singular matrices */
class SingularMat4Determinant: public ::testing::TestWithParam<fgm::Mat4<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Mat4DeterminantTestSuite, SingularMat4Determinant,
    ::testing::Values(fgm::Mat4{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f },
                                    fgm::Vec4{ 7.0f, 8.0f, 9.0f, 12.0f },
                                    fgm::Vec4{ 1.0f, 85.0f, 19.0f, 12.0f } },
                      fgm::Mat4{ fgm::Vec4{ 1.0f, 1.0f, 3.0f, 4.0f }, fgm::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                    fgm::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 0.0f, 0.0f, 0.0f, 0.0f }, fgm::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                    fgm::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 0.0f, 1.0f, 3.0f, 4.0f }, fgm::Vec4{ 0.0f, 2.0f, 3.0f, 4.0f },
                                    fgm::Vec4{ 0.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 0.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ 2.0f, 4.0f, 6.0f, 8.0f },
                                    fgm::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ 2.0f, 4.0f, 5.0f, 10.0f },
                                    fgm::Vec4{ 3.0f, 6.0f, 9.0f, 12.0f },
                                    fgm::Vec4{ 4.0f, 8.0f, 31.6f, 2.0f } }));



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
    constexpr fgm::Mat4 MAT{ fgm::Vec4{ 1, 2, 3, 4 }, fgm::Vec4{ 1, 2, 1, 3 }, fgm::Vec4{ 2, 3, 4, 12 },
                                fgm::Vec4{ 2, 1, 3, 2 } };

    // Verify determinant (member function)
    static_assert(MAT.determinant() == 39);

    // Verify determinant (static function)
    static_assert(fgm::Mat4<int>::determinant(MAT) == 39);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/** @brief Verify that computing the determinant of a non-singular matrix returns a non-zero value. */
TYPED_TEST(Mat4Determinant, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


/** @brief Verify that computing the determinant of a singular matrix returns zero. */
TEST_P(SingularMat4Determinant, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


/**
 * @brief Verify that computing the determinant of a non-singular matrix using static variant of
 *        @ref fgm::Mat4::determinant returns a non-zero value.
 */
TYPED_TEST(Mat4Determinant, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Mat4<TypeParam>::determinant(this->_matrix));
}


/**
 * @brief Verify that computing the determinant of a singular matrix using static variant of
 *        @ref fgm::Mat4::determinant returns zero.
 */
TEST_P(SingularMat4Determinant, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Mat4<float>::determinant(matrix));
}

/** @} */
