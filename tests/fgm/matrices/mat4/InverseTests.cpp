/**
 * @file InverseTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 09, 2026
 *
 * @brief Verify @ref fgm::Mat4 inverse logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**************************************
 *                                    *
 *              SETUP                 *
 *                                    *
 **************************************/

template <typename T>
class Mat4Inverse: public ::testing::Test
{
protected:
    using Mag = fgm::Magnitude<T>;
    fgm::Mat4<T> _matrix;
    fgm::Mat4<Mag> _expectedInverse;

    void SetUp() override
    {
        _matrix          = { { T(3), T(1), T(8), T(4) },
                             { T(3), T(7), T(4), T(2) },
                             { T(6), T(1), T(2), T(1) },
                             { T(3), T(1), T(6), T(2) } };
        _expectedInverse = { { Mag(-0.037878787878788), Mag(-0.022727272727273), Mag(0.196969696969697), Mag(0.0) },
                             { Mag(-0.068181818181818), Mag(0.159090909090909), Mag(-0.045454545454545), Mag(0.0) },
                             { Mag(-0.204545454545455), Mag(-0.022727272727273), Mag(-0.136363636363636), Mag(0.5) },
                             { Mag(0.704545454545455), Mag(0.022727272727273), Mag(0.136363636363636), Mag(-1.0) } };
    }
};
/** @brief Test fixture for @ref fgm::Mat4 inverse, parameterized @ref SupportedSignedArithmeticTypes */
TYPED_TEST_SUITE(Mat4Inverse, SupportedSignedArithmeticTypes);


/** @brief Test fixture for calculating @ref fgm::Mat4 inverse with singular matrices */
class SingularMat4Inverse: public ::testing::TestWithParam<fgm::Mat4<float>>
{};
INSTANTIATE_TEST_SUITE_P(
    Mat4InverseTestSuite, SingularMat4Inverse,
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


/** @brief Test fixture for @ref fgm::Mat4 inverse with NaN vectors. */
class NaNMat4Inverse: public ::testing::TestWithParam<fgm::Mat4<float>>
{};
INSTANTIATE_TEST_SUITE_P(Mat4InverseTestSuite, NaNMat4Inverse,
                         ::testing::Values(fgm::Mat4<float>{ fgm::constants::NaN, 3.0f, 3.0f, 3.0f },
                                           fgm::Mat4<float>{ 3.0f, fgm::constants::NaN, 3.0f, 3.0f },
                                           fgm::Mat4<float>{ 3.0f, 3.0f, fgm::constants::NaN, 3.0f },
                                           fgm::Mat4<float>{ 3.0f, 3.0f, 3.0f, fgm::constants::NaN },
                                           fgm::Mat4<float>{ fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN }));


/**
 * @addtogroup T_FGM_Mat4x4_Inverse
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that matrix inverse functions are available at compile time. */
namespace
{
    constexpr fgm::Mat4 mat(1.0f, -1.0f, 0.0f, -2.0f, 2.0f, -1.0f, -2.0f, -6.0f, 0.0f, -1.0f, 3.0f, 3.0f, -2.0f,
                               2.0f, -2.0f, 3.0f);

    //  Verify matrix inverse (member function)
    constexpr fgm::Mat4 invMat = mat.inverse();
    static_assert(invMat(0, 0) - -9.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(0, 1) - 7.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(0, 2) - 6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(0, 3) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(1, 0) - -6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(1, 1) - 3.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(1, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(1, 3) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(2, 0) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(2, 1) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(2, 2) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(2, 3) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(3, 0) - -2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(3, 1) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(3, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMat(3, 3) - 1.0f <= fgm::Config::FLOAT_EPSILON);

    // Verify matrix inverse (static function)
    constexpr fgm::Mat4 invMatS = fgm::Mat4<float>::inverse(mat);
    static_assert(invMatS(0, 0) - -9.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(0, 1) - 7.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(0, 2) - 6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(0, 3) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(1, 0) - -6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(1, 1) - 3.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(1, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(1, 3) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(2, 0) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(2, 1) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(2, 2) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(2, 3) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(3, 0) - -2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(3, 1) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(3, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(invMatS(3, 3) - 1.0f <= fgm::Config::FLOAT_EPSILON);

    // TODO: Add back
    // Verify matrix safeInverse (member function)
    constexpr fgm::Mat4 safeInvMat = mat.safeInverse();
    static_assert(safeInvMat(0, 0) - -9.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(0, 1) - 7.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(0, 2) - 6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(0, 3) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(1, 0) - -6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(1, 1) - 3.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(1, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(1, 3) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(2, 0) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(2, 1) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(2, 2) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(2, 3) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(3, 0) - -2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(3, 1) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(3, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMat(3, 3) - 1.0f <= fgm::Config::FLOAT_EPSILON);

    // Verify matrix safeInverse (static function)
    constexpr fgm::Mat4 safeInvMatS = fgm::Mat4<float>::safeInverseOf(mat);
    static_assert(safeInvMatS(0, 0) - -9.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(0, 1) - 7.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(0, 2) - 6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(0, 3) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(1, 0) - -6.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(1, 1) - 3.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(1, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(1, 3) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(2, 0) - 0.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(2, 1) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(2, 2) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(2, 3) - -1.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(3, 0) - -2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(3, 1) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(3, 2) - 2.0f <= fgm::Config::FLOAT_EPSILON);
    static_assert(safeInvMatS(3, 3) - 1.0f <= fgm::Config::FLOAT_EPSILON);
} // namespace



/**************************************
 *                                    *
 *       INVERSE TESTS (RUNTIME)      *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Mat4::inverse returns a new matrix that when multiplied
 *        with the original matrix returns an identity matrix.
 */
TYPED_TEST(Mat4Inverse, ReturnsInverseMatrix) { EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.inverse()); }


/** @brief Verify that inverse of matrix times itself is an identity matrix. */
TYPED_TEST(Mat4Inverse, InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.inverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}

/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Mat4::inverse returns a new matrix that
 *        when multiplied with the original matrix returns an identity matrix.
 */
TYPED_TEST(Mat4Inverse, StaticWrapper_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat4<TypeParam>::inverse(this->_matrix));
}


/** @brief Verify that inverse of matrix (using the static variant) times itself is an identity matrix. */
TYPED_TEST(Mat4Inverse, StaticWrapper_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Mat4<TypeParam>::inverse(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat4::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(SingularMat4Inverse, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat4::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(SingularMat4Inverse, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat4<float>::inverse(matrix)), "");
}

#endif




/**************************************
 *                                    *
 *          SAFE INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Mat4::safeInverse exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Mat4Inverse, SafeInverse_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.safeInverse());
}


/**
 * @brief Verify that inverse of matrix (using @ref fgm::Mat4::safeInverse) times itself
 *        is an identity matrix.
 */
TYPED_TEST(Mat4Inverse, SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = this->_matrix.safeInverse();
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat4::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(SingularMat4Inverse, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat4::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(SingularMat4Inverse, SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat4::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(NaNMat4Inverse, SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.safeInverse());
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat4::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(NaNMat4Inverse, SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = GetParam().safeInverse(fgm::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Mat4::safeInverse exchanges row and
 *        column elements and returns a new matrix.
 */
TYPED_TEST(Mat4Inverse, StaticWrapper_SafeInverse_ReturnsInverseMatrix)
{
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat4<TypeParam>::safeInverseOf(this->_matrix));
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Mat4::safeInverse) times itself is an
 *        identity matrix.
 */
TYPED_TEST(Mat4Inverse, StaticWrapper_SafeInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    const auto invMatrix = fgm::Mat4<TypeParam>::safeInverseOf(this->_matrix);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat4::safeInverseOf
 *         returns identity matrix by default.
 */
TEST_P(SingularMat4Inverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat4::safeInverseOf
 *         returns passed-in fallback.
 */
TEST_P(SingularMat4Inverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::safeInverseOf(matrix, fgm::Mat4<ParamType::value_type>::zero()));
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat4::safeInverse
 *        returns identity matrix by default.
 */
TEST_P(NaNMat4Inverse, StaticWrapper_SafeInverse_ReturnsIdentityMatrixByDefault)
{
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::safeInverseOf(matrix));
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat4::safeInverse
 *        returns passed-in fallback.
 */
TEST_P(NaNMat4Inverse, StaticWrapper_SafeInverse_ReturnsPassedInFallback)
{
    const auto& inverseMatrix = ParamType::safeInverseOf(GetParam(), fgm::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
}


/**************************************
 *                                    *
 *          TRY INVERSE TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that inverting a matrix using @ref fgm::Mat4::tryInverse exchanges row and column elements and
 *        returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4Inverse, TryInverse_ReturnsInverseMatrix)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, this->_matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using @ref fgm::Mat4::tryInverse) times itself is an identity matrix and
 *        sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4Inverse, TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    fgm::OperationStatus flag;
    const auto invMatrix = this->_matrix.tryInverse(flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat4::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMat4Inverse, TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat4::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMat4Inverse, TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat4::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat4Inverse, TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(matrix.tryInverse(flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using @ref fgm::Mat4::tryInverse returns passed-in fallback
 *        and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat4Inverse, TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = GetParam().tryInverse(flag, fgm::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}


/**
 * @brief Verify that inverting a matrix using static variant of @ref fgm::Mat4::tryInverse exchanges row and
 *        column elements and returns a new matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4Inverse, StaticWrapper_TryInverse_ReturnsInverseMatrix)
{
    fgm::OperationStatus flag;
    EXPECT_MAT_EQ(this->_expectedInverse, fgm::Mat4<TypeParam>::tryInverseOf(this->_matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverse of matrix (using static variant of @ref fgm::Mat4::tryInverse) times itself is an
 *        identity matrix and sets status flag to @ref OperationStatus::SUCCESS.
 */
TYPED_TEST(Mat4Inverse, StaticWrapper_TryInverse_InverseTimesMatrixReturnsIdentityMatrix)
{
    fgm::OperationStatus flag;
    const auto invMatrix = fgm::Mat4<TypeParam>::tryInverseOf(this->_matrix, flag);
    EXPECT_MAT_IDENTITY(this->_matrix * invMatrix);
    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat4::tryInverseOf
 *         returns identity matrix by default and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMat4Inverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat4::tryInverseOf
 *         returns passed-in fallback and sets status flag to @ref OperationStatus::DIVISIONBYZERO.
 */
TEST_P(SingularMat4Inverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_ZERO(ParamType::tryInverseOf(matrix, flag, fgm::Mat4<ParamType::value_type>::zero()));
    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
}


/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat4::tryInverse
 *        returns identity matrix by default and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat4Inverse, StaticWrapper_TryInverse_ReturnsIdentityMatrixByDefault)
{
    fgm::OperationStatus flag;
    const auto& matrix = GetParam();
    EXPECT_MAT_IDENTITY(ParamType::tryInverseOf(matrix, flag));
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}



/**
 * @brief Verify that inverting a NaN matrix using static variant of @ref fgm::Mat4::tryInverse
 *        returns passed-in fallback and sets status flag to @ref OperationStatus::NANOPERAND.
 */
TEST_P(NaNMat4Inverse, StaticWrapper_TryInverse_ReturnsPassedInFallback)
{
    fgm::OperationStatus flag;
    const auto& inverseMatrix = ParamType::tryInverseOf(GetParam(), flag, fgm::Mat4<ParamType::value_type>::zero());
    EXPECT_MAT_ZERO(inverseMatrix);
    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
}

/** @} */
