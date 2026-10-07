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



/**
 * @addtogroup T_FGM_Mat4x4_Det
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4 Determinants.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
template <typename T>
class Mat4DeterminantTests: public testing::Test
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
TYPED_TEST_SUITE(Mat4DeterminantTests, SupportedSignedArithmeticTypes);


    /**
       * @brief Test fixture for @ref fgm::Mat4 Determinants with singular matrices.
       */
class SingularMat4DeterminantTests: public testing::TestWithParam<fgm::Mat4<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Mat4DeterminantTestSuite, SingularMat4DeterminantTests,
    ::testing::Values(fgm::Mat4{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f },
                                 fgm::Vec4{ 7.0f, 8.0f, 9.0f, 12.0f }, fgm::Vec4{ 1.0f, 85.0f, 19.0f, 12.0f } },
                      fgm::Mat4{ fgm::Vec4{ 1.0f, 1.0f, 3.0f, 4.0f }, fgm::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                 fgm::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 0.0f, 0.0f, 0.0f, 0.0f }, fgm::Vec4{ 2.0f, 2.0f, 3.0f, 4.0f },
                                 fgm::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 0.0f, 1.0f, 3.0f, 4.0f }, fgm::Vec4{ 0.0f, 2.0f, 3.0f, 4.0f },
                                 fgm::Vec4{ 0.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 0.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ 2.0f, 4.0f, 6.0f, 8.0f },
                                 fgm::Vec4{ 3.0f, 3.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 4.0f, 31.6f, 2.0f } },
                      fgm::Mat4{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ 2.0f, 4.0f, 5.0f, 10.0f },
                                 fgm::Vec4{ 3.0f, 6.0f, 9.0f, 12.0f }, fgm::Vec4{ 4.0f, 8.0f, 31.6f, 2.0f } }));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
    constexpr fgm::Mat4 MAT{ fgm::Vec4{ 1, 2, 3, 4 }, fgm::Vec4{ 1, 2, 1, 3 }, fgm::Vec4{ 2, 3, 4, 12 },
                             fgm::Vec4{ 2, 1, 3, 2 } };

        /// @test Verify that Mat4 determinant returns a valid value at compile time.
    static_assert(MAT.determinant() == 39);

        /// @test Verify that Mat4 determinant (static wrapper) returns a valid value at compile time.
    static_assert(fgm::Mat4<int>::determinant(MAT) == 39);

} // namespace
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4DeterminantTests, ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant());
}


TEST_P(SingularMat4DeterminantTests, SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


TYPED_TEST(Mat4DeterminantTests, StaticWrapper_ReturnsNonZeroScalar)
{
    EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Mat4<TypeParam>::determinant(this->_matrix));
}


TEST_P(SingularMat4DeterminantTests, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Mat4<float>::determinant(matrix));
}

/** @} */
