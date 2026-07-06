/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix2 inverse logic.
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
class Matrix2Inverse: public ::testing::Test
{
protected:
    using Mag = fgm::Magnitude<T>;
    fgm::Matrix2<T> _matrix;
    fgm::Matrix2<Mag> _expectedInverse;

    void SetUp() override
    {
        _matrix          = { fgm::Vector2{ T(5), T(4) }, fgm::Vector2{ T(2), T(3) } };
        _expectedInverse = { fgm::Vector2{ Mag(0.42857142857142855), Mag(-0.5714285714285714) },
                             fgm::Vector2{ Mag(-0.2857142857142857), Mag(0.7142857142857143) } };
    }
};
/** @brief Test fixture for @ref fgm::Matrix2 inverse, parameterized @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Matrix2Inverse, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Matrix2 inverse with singular matrices */
class SingularMatrix2Inverse: public ::testing::TestWithParam<fgm::Matrix2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2InverseTestSuite, SingularMatrix2Inverse,
                         ::testing::Values(fgm::Matrix2{ fgm::Vector2{ 1.0f, 2.0f }, fgm::Vector2{ 1.0f, 2.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 2.0f, 2.0f }, fgm::Vector2{ 2.0f, 2.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 3.0f, 2.0f }, fgm::Vector2{ 6.0f, 4.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 0.0f, 0.0f }, fgm::Vector2{ 4.0f, 5.0f } },
                                           fgm::Matrix2{ fgm::Vector2{ 0.0f, 3.0f }, fgm::Vector2{ 0.0f, 5.0f } }));



/** @brief Test fixture for @ref fgm::Matrix2 inverse with NaN vectors. */
class NaNMatrix2Inverse: public ::testing::TestWithParam<fgm::Matrix2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Matrix2InverseTestSuite, NaNMatrix2Inverse,
                         ::testing::Values(fgm::Matrix2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                           fgm::Matrix2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Matrix2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Matrix2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Matrix2<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                               fgm ::constants::NaN, fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Mat2x2_Inverse
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix inverse is available at compile time. */
namespace
{
    constexpr fgm::Matrix2 MAT(1.0f, 2.0f, 3.0f, 4.0f);
    // Verify matrix inverse (member function)
    constexpr fgm::Matrix2 INV_MAT = MAT.inverse();
    static_assert(INV_MAT(0, 0) == -2.0f);
    static_assert(INV_MAT(0, 1) == 1.0f);
    static_assert(INV_MAT(1, 0) == 1.5f);
    static_assert(INV_MAT(1, 1) == -0.5f);

    // Verify matrix inverse (static function)
    constexpr fgm::Matrix2 INV_MAT_S = fgm::Matrix2<float>::inverse(MAT);
    static_assert(INV_MAT_S(0, 0) == -2.0f);
    static_assert(INV_MAT_S(0, 1) == 1.0f);
    static_assert(INV_MAT_S(1, 0) == 1.5f);
    static_assert(INV_MAT_S(1, 1) == -0.5f);
} // namespace



/**************************************
 *                                    *
 *       INVERSE TESTS (RUNTIME)      *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix2::inverse returns a new matrix that when multiplied
 *        with the original matrix returns an identity matrix.
 */
TYPED_TEST(Matrix2Inverse, ReturnsInverseMatrix) { EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


/** @brief Verify that inverse of matrix times itself is an identity matrix. */
TYPED_TEST(Matrix2Inverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix2::inverse returns a new matrix that
 *        when multiplied with the original matrix returns an identity matrix.
 */
TYPED_TEST(Matrix2Inverse, StaticWrapper_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix2<TypeParam>::inverse(this->_matrix));
}


/** @brief Verify that inverse of matrix (using the static variant) times itself is an identity matrix. */
TYPED_TEST(Matrix2Inverse, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Matrix2<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(SingularMatrix2Inverse, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(SingularMatrix2Inverse, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Matrix2<float>::inverse(matrix)), "");
}

#endif


/**************************************
 *                                    *
 *          SAFE INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix2::safeInverse returns a new matrix that when multiplied
 *        with the original matrix returns an identity matrix.
 */
TYPED_TEST(Matrix2Inverse, SafeInverse_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse());
}


/** @brief Verify that inverse of matrix (using @ref fgm::Matrix2::safeInverse) times itself is an identity matrix. */
TYPED_TEST(Matrix2Inverse, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(SingularMatrix2Inverse, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(SingularMatrix2Inverse, SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Matrix2<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix2::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix2Inverse, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix2::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix2Inverse, SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Matrix2<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix2::safeInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix.
 */
TYPED_TEST(Matrix2Inverse, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix2<TypeParam>::safeInverseOf(this->_matrix));
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix2::safeInverse) times itself is an
 *        identity matrix.
 */
TYPED_TEST(Matrix2Inverse, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Matrix2<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2::safeInverseOf
 *        returns identity matrix by default.
 */
TEST_P(SingularMatrix2Inverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2::safeInverseOf
 *        returns passed-in fallback.
 */
TEST_P(SingularMatrix2Inverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::Matrix2<ParamType::value_type>::ZERO()));
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix2::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(NaNMatrix2Inverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix2::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(NaNMatrix2Inverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), fgm::Matrix2<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**************************************
 *                                    *
 *          TRY INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Matrix2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2Inverse, TryInverse_ReturnsInverseMatrix)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using @ref fgm::Matrix2::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2Inverse, TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    fgm::OperationStatus flag;
    const auto invMatrix = this->_matrix.tryInverse(flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMatrix2Inverse, TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Matrix2::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMatrix2Inverse, TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::Matrix2<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Inverse, TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Matrix2::tryInverse returns passed-in fallback
 *        and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Inverse, TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::Matrix2<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Matrix2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2Inverse, StaticWrapper_TryInverse_ReturnsInverseMatrix)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Matrix2<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Matrix2::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Matrix2Inverse, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    fgm::OperationStatus flag;
    const auto invMatrix = fgm::Matrix2<TypeParam>::tryInverseOf(this->_matrix, flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2::tryInverseOf
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMatrix2Inverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Matrix2::tryInverseOf
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMatrix2Inverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, fgm::Matrix2<ParamType::value_type>::ZERO()));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix2::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Inverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Matrix2::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMatrix2Inverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, fgm::Matrix2<ParamType::value_type>::ZERO());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
