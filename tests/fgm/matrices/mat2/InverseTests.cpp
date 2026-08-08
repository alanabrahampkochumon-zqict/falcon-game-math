/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Mat2 inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Inverse
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 Inverse.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2InverseTests: public testing::Test
    {
    protected:
        using Mag = fgm::Magnitude<T>;
        fgm::Mat2<T> _matrix;
        fgm::Mat2<Mag> _expectedInverse;

        void SetUp() override
        {
            _matrix          = { fgm::Vec2{ T(5), T(4) }, fgm::Vec2{ T(2), T(3) } };
            _expectedInverse = { fgm::Vec2{ Mag(0.42857142857142855), Mag(-0.5714285714285714) },
                                 fgm::Vec2{ Mag(-0.2857142857142857), Mag(0.7142857142857143) } };
        }
    };
    TYPED_TEST_SUITE(Mat2InverseTests, SupportedSignedArithmeticTypes);



    /** @brief Test fixture for calculating @ref fgm::Mat2 inverse with singular matrices. */
    class Mat2InverseSingularTests: public testing::TestWithParam<fgm::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2SingularMatrixInverse, Mat2InverseSingularTests,
                             ::testing::Values(fgm::Mat2{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ 1.0f, 2.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 2.0f, 2.0f }, fgm::Vec2{ 2.0f, 2.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 3.0f, 2.0f }, fgm::Vec2{ 6.0f, 4.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 0.0f, 0.0f }, fgm::Vec2{ 4.0f, 5.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 0.0f, 3.0f }, fgm::Vec2{ 0.0f, 5.0f } }));



    /** @brief Test fixture for @ref fgm::Mat2 inverse with NaN elements. */
    class Mat2InverseNaNTests: public testing::TestWithParam<fgm::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2NaNMatrixInverse, Mat2InverseNaNTests,
                             ::testing::Values(fgm::Mat2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Mat2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Mat2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Mat2<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    /** @brief Verify that matrix inverse is available at compile time. */
    namespace static_tests
    {
        constexpr fgm::Mat2 MAT(1.0f, 2.0f, 3.0f, 4.0f);

        /// @test Verify matrix inverse returns a valid matrix at compile time.
        constexpr fgm::Mat2 INV_MAT = MAT.inverse();
        static_assert(INV_MAT(0, 0) == -2.0f);
        static_assert(INV_MAT(0, 1) == 1.0f);
        static_assert(INV_MAT(1, 0) == 1.5f);
        static_assert(INV_MAT(1, 1) == -0.5f);

        /// @test Verify matrix inverse (static wrapper) returns a valid matrix at compile time.
        constexpr fgm::Mat2 INV_MAT_STATIC = fgm::Mat2<float>::inverse(MAT);
        static_assert(INV_MAT_STATIC(0, 0) == -2.0f);
        static_assert(INV_MAT_STATIC(0, 1) == 1.0f);
        static_assert(INV_MAT_STATIC(1, 0) == 1.5f);
        static_assert(INV_MAT_STATIC(1, 1) == -0.5f);

        /// @test Verify matrix inverse returns a valid matrix at compile time.
        constexpr fgm::Mat2 SAFE_INV_MAT = MAT.safeInverse();
        static_assert(SAFE_INV_MAT(0, 0) == -2.0f);
        static_assert(SAFE_INV_MAT(0, 1) == 1.0f);
        static_assert(SAFE_INV_MAT(1, 0) == 1.5f);
        static_assert(SAFE_INV_MAT(1, 1) == -0.5f);

        /// @test Verify matrix inverse (static wrapper) returns a valid matrix at compile time.
        constexpr fgm::Mat2 SAFE_INV_MAT_STATIC = fgm::Mat2<float>::safeInverseOf(MAT);
        static_assert(SAFE_INV_MAT_STATIC(0, 0) == -2.0f);
        static_assert(SAFE_INV_MAT_STATIC(0, 1) == 1.0f);
        static_assert(SAFE_INV_MAT_STATIC(1, 0) == 1.5f);
        static_assert(SAFE_INV_MAT_STATIC(1, 1) == -0.5f);

    } // namespace static_tests

} // namespace



/**************************************
 *              INVERSE               *
 **************************************/

TYPED_TEST(Mat2InverseTests, Inverse_NonSingularMatrix_ReturnsValidInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


TYPED_TEST(Mat2InverseTests, Inverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TYPED_TEST(Mat2InverseTests, StaticWrapper_Inverse_NonSingularMatrix_ReturnsValidInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat2<TypeParam>::inverse(this->_matrix)); }


TYPED_TEST(Mat2InverseTests, StaticWrapper_Inverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Mat2<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}



/**************************************
 *             SAFE INVERSE           *
 **************************************/

TYPED_TEST(Mat2InverseTests, SafeInverse_NonSingularMatrix_ReturnsValidInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse()); }


TYPED_TEST(Mat2InverseTests, SafeInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat2InverseSingularTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat2InverseSingularTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TEST_P(Mat2InverseNaNTests, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


TEST_P(Mat2InverseNaNTests, SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


TYPED_TEST(Mat2InverseTests, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{ EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat2<TypeParam>::safeInverseOf(this->_matrix)); }


TYPED_TEST(Mat2InverseTests, StaticWrapper_SafeInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Mat2<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


TEST_P(Mat2InverseSingularTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat2InverseSingularTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::Mat2<ParamType::value_type>::zero()));
}


TEST_P(Mat2InverseNaNTests, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


TEST_P(Mat2InverseNaNTests, StaticWrapper_SafeInverse_ReturnsPassedInFallbackMatrix)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}



/**************************************
 *            TRY INVERSE             *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Mat2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests, TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using @ref fgm::Mat2::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests, TryInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto invMatrix = this->_matrix.tryInverse(flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat2::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat2::tryInverse returns passed-in fallback
 *        and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Mat2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests, StaticWrapper_TryInverse_ReturnsInverseMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat2<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Mat2::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2InverseTests,
           StaticWrapper_TryInverse_InverseMatrixTimesOriginalMatrixReturnsIdentityMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto invMatrix = fgm::Mat2<TypeParam>::tryInverseOf(this->_matrix, flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat2::tryInverseOf
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat2::tryInverseOf
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(Mat2InverseSingularTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, fgm::Mat2<ParamType::value_type>::zero()));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefaultAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat2::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(Mat2InverseNaNTests, StaticWrapper_TryInverse_ReturnsPassedInFallbackMatrixAndSetsCorrectFlag)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
