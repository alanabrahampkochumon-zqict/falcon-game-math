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


/**
 * @addtogroup T_FGM_Mat2x2_Det
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 Determinants.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2DeterminantTests: public testing::Test
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
    TYPED_TEST_SUITE(Mat2DeterminantTests, SupportedSignedArithmeticTypes);



    /**
     * @brief Test fixture for @ref fgm::Mat2 Determinants.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    class Mat2DeterminantSingularTests: public ::testing::TestWithParam<fgm::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2DeterminantTests, Mat2DeterminantSingularTests,
                             ::testing::Values(fgm::Mat2{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ 1.0f, 2.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 2.0f, 2.0f }, fgm::Vec2{ 2.0f, 2.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 3.0f, 2.0f }, fgm::Vec2{ 6.0f, 4.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 0.0f, 0.0f }, fgm::Vec2{ 4.0f, 5.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 0.0f, 3.0f }, fgm::Vec2{ 0.0f, 5.0f } }));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat2 MAT{ fgm::Vec2{ 4, 2 }, fgm::Vec2{ 3, 4 } };

        /// @test Verify that Mat2 determinant returns a valid value at compile time.
        static_assert(MAT.determinant() == 10);

        /// @test Verify that Mat2 determinant (static wrapper) returns a valid value at compile time.
        static_assert(fgm::Mat2<int>::determinant(MAT) == 10);

    } // namespace

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat2DeterminantTests, NonSingularMatrix_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, this->_matrix.determinant()); }


TYPED_TEST(Mat2DeterminantTests, StaticWrapper_NonSingularMatrix_ReturnsNonZeroScalar)
{ EXPECT_MAG_EQ(this->_expectedDeterminant, fgm::Mat2<TypeParam>::determinant(this->_matrix)); }


TEST_P(Mat2DeterminantSingularTests, SingularMatrix_ReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, matrix.determinant());
}


TEST_P(Mat2DeterminantSingularTests, StaticWrapper_SingularMatrix_ReturnsZero)
{
    const auto& matrix = GetParam();
    EXPECT_MAG_EQ(0.0f, fgm::Mat2<float>::determinant(matrix));
}

/** @} */
