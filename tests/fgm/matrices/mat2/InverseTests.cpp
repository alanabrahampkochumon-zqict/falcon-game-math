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



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Mat2Inverse: public ::testing::Test
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
/** @brief Test fixture for @ref fgm::Mat2 inverse, parameterized @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Mat2Inverse, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Mat2 inverse with singular matrices */
class SingularMat2Inverse: public ::testing::TestWithParam<fgm::Mat2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Mat2InverseTestSuite, SingularMat2Inverse,
                         ::testing::Values(fgm::Mat2{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ 1.0f, 2.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 2.0f, 2.0f }, fgm::Vec2{ 2.0f, 2.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 3.0f, 2.0f }, fgm::Vec2{ 6.0f, 4.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 0.0f, 0.0f }, fgm::Vec2{ 4.0f, 5.0f } },
                                           fgm::Mat2{ fgm::Vec2{ 0.0f, 3.0f }, fgm::Vec2{ 0.0f, 5.0f } }));



/** @brief Test fixture for @ref fgm::Mat2 inverse with NaN vectors. */
class NaNMat2Inverse: public ::testing::TestWithParam<fgm::Mat2<float>>
{};
INSTANTIATE_TEST_SUITE_P(Mat2InverseTestSuite, NaNMat2Inverse,
                         ::testing::Values(fgm::Mat2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                           fgm::Mat2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                           fgm::Mat2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                           fgm::Mat2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                           fgm::Mat2<float>(fgm ::constants::NaN, fgm::constants::NaN,
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
    constexpr fgm::Mat2 MAT(1.0f, 2.0f, 3.0f, 4.0f);
    // Verify matrix inverse (member function)
    constexpr fgm::Mat2 INV_MAT = MAT.inverse();
    static_assert(INV_MAT(0, 0) == -2.0f);
    static_assert(INV_MAT(0, 1) == 1.0f);
    static_assert(INV_MAT(1, 0) == 1.5f);
    static_assert(INV_MAT(1, 1) == -0.5f);

    // Verify matrix inverse (static function)
    constexpr fgm::Mat2 INV_MAT_S = fgm::Mat2<float>::inverse(MAT);
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
 * @brief Verify that inverting a matrix using @ref fgm::Mat2::inverse returns a new matrix that when multiplied
 *        with the original matrix returns an identity matrix.
 */
TYPED_TEST(Mat2Inverse, ReturnsInverseMatrix) { EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


/** @brief Verify that inverse of matrix times itself is an identity matrix. */
TYPED_TEST(Mat2Inverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Mat2::inverse returns a new matrix that
 *        when multiplied with the original matrix returns an identity matrix.
 */
TYPED_TEST(Mat2Inverse, StaticWrapper_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat2<TypeParam>::inverse(this->_matrix));
}


/** @brief Verify that inverse of matrix (using the static variant) times itself is an identity matrix. */
TYPED_TEST(Mat2Inverse, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Mat2<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat2::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(SingularMat2Inverse, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat2::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(SingularMat2Inverse, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat2<float>::inverse(matrix)), "");
}

#endif


/**************************************
 *                                    *
 *          SAFE INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Mat2::safeInverse returns a new matrix that when multiplied
 *        with the original matrix returns an identity matrix.
 */
TYPED_TEST(Mat2Inverse, SafeInverse_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse());
}


/** @brief Verify that inverse of matrix (using @ref fgm::Mat2::safeInverse) times itself is an identity matrix. */
TYPED_TEST(Mat2Inverse, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat2::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(SingularMat2Inverse, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat2::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(SingularMat2Inverse, SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat2::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(NaNMat2Inverse, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat2::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(NaNMat2Inverse, SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Mat2::safeInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix.
 */
TYPED_TEST(Mat2Inverse, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat2<TypeParam>::safeInverseOf(this->_matrix));
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Mat2::safeInverse) times itself is an
 *        identity matrix.
 */
TYPED_TEST(Mat2Inverse, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Mat2<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat2::safeInverseOf
 *        returns identity matrix by default.
 */
TEST_P(SingularMat2Inverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat2::safeInverseOf
 *        returns passed-in fallback.
 */
TEST_P(SingularMat2Inverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::Mat2<ParamType::value_type>::zero()));
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat2::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(NaNMat2Inverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat2::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(NaNMat2Inverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**************************************
 *                                    *
 *          TRY INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Mat2::tryInverse returns a new matrix
 *        that when multiplied with the original matrix returns an identity matrix and sets status flag to
 *        @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2Inverse, TryInverse_ReturnsInverseMatrix)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using @ref fgm::Mat2::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2Inverse, TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
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
TEST_P(SingularMat2Inverse, TryInverse_ReturnsIdentityMatrixByDefault)
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
TEST_P(SingularMat2Inverse, TryInverse_ReturnsPassedInFallback)
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
TEST_P(NaNMat2Inverse, TryInverse_ReturnsIdentityMatrixByDefault)
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
TEST_P(NaNMat2Inverse, TryInverse_ReturnsPassedInFallback)
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
TYPED_TEST(Mat2Inverse, StaticWrapper_TryInverse_ReturnsInverseMatrix)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat2<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Mat2::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat2Inverse, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
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
TEST_P(SingularMat2Inverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
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
TEST_P(SingularMat2Inverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
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
TEST_P(NaNMat2Inverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
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
TEST_P(NaNMat2Inverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, fgm::Mat2<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
