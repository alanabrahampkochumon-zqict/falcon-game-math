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



/**
 * @addtogroup T_FGM_Mat3x3_Det
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3 Determinants.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3DeterminantTests: public testing::Test
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
    TYPED_TEST_SUITE(Mat3DeterminantTests, SupportedSignedArithmeticTypes);



    /**
     * @brief Test fixture for @ref fgm::Mat3 Determinants with singular matrices.
     */
    class Mat3DeterminantSingularTests: public testing::TestWithParam<fgm::Mat3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3InvalidDeterminantTests, Mat3DeterminantSingularTests,
        ::testing::Values(
            fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 7.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 1.0f, 1.0f, 5.0f }, fgm::Vec3{ 2.0f, 2.0f, 3.0f }, fgm::Vec3{ 3.0f, 3.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 0.0f, 0.0f, 0.0f }, fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 1.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 0.0f, 5.0f, 1.0f }, fgm::Vec3{ 0.0f, 2.0f, 3.0f }, fgm::Vec3{ 0.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 2.0f, 4.0f, 6.0f }, fgm::Vec3{ 7.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 1.0f }, fgm::Vec3{ 2.0f, 4.0f, 3.0f }, fgm::Vec3{ 3.0f, 6.0f, 9.0f } }));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3 MAT{ fgm::Vec3{ 1, 2, 5 }, fgm::Vec3{ 5, 1, 7 }, fgm::Vec3{ 8, 9, 10 } };

        /// @test Verify that Mat3 determinant returns a valid value at compile time.
        static_assert(MAT.determinant() == 144);

        /// @test Verify that Mat3 determinant (static wrapper) returns a valid value at compile time.
        static_assert(fgm::Mat3<int>::determinant(MAT) == 144);

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3DeterminantTests, ReturnsNonZeroScalarMatrix)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant()); }


TEST_P(Mat3DeterminantSingularTests, SingularMatrixReturnsZeroMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


TYPED_TEST(Mat3DeterminantTests, StaticWrapper_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Mat3<TypeParam>::determinant(this->_matrix)); }


TEST_P(Mat3DeterminantSingularTests, StaticWrapper_SingularMatrixReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Mat3<float>::determinant(matrix));
}

/** @} */
