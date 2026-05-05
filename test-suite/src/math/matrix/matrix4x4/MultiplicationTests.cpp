/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 05, 2026
 *
 * @brief Verify @ref fgm::Matrix4D multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix4DScalarMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix4D<T> _mat;
    T _scalar;
    fgm::Matrix4D<T> _expectedFloatingMat;
    fgm::Matrix4D<T> _expectedIntegralMat;



    void SetUp() override
    {
        _mat = { { T(7), T(8), T(1.23894234), T(5.28389123134) },
                 { T(5.539), T(1.91238432), T(0.1329843), T(9.0129) },
                 { T(5.5), T(11.25), T(1.332), T(3.8329) },
                 { T(9.912384), T(1.2399132), T(5.383912), T(12.19381) } };
        _scalar = T(2.123456789123456);
        _expectedFloatingMat = {
            { T(14.864197523864192), T(11.761827154954823), T(11.679012340179007), T(21.048519101198718) },
            { T(16.987654312987647), T(4.060865467717243), T(23.88888887763888), T(2.632902102463789) },
            { T(2.630840523205501), T(0.28238641468183), T(2.828444443112443), T(11.432504488443243) },
            { T(11.220114708178821), T(19.138503694690797), T(8.138997527031295), T(25.893028629781487) }
        };
        _expectedIntegralMat = { { T(14), T(11), T(11), T(21) },
                                 { T(16), T(4), T(23), T(2) },
                                 { T(2), T(0), T(2), T(11) },
                                 { T(11), T(19), T(8), T(25) }

        };
    }
};
/** @brief Test fixture for @ref fgm::Matrix4D scalar multiplication, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Matrix4DScalarMultiplication, SupportedArithmeticTypes);


// template <typename T>
// class Matrix4DVectorMultiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix4D<T> _mat;
//     fgm::Vector4D<T> _vec;
//     fgm::Vector4D<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
//         _expectedIntegralRowVector;
//
//     void SetUp() override
//     {
//         _mat = { fgm::Vector4D{ T(7.12345678912345), T(13.12345678912345), T(1.32893912338) },
//                  fgm::Vector4D{ T(5.12345678912345), T(4.12345678912345), T(3.3129381239321) },
//                  fgm::Vector4D{ T(2.238929123125), T(11.238924194839), T(9.2389291239898) } };
//         _vec = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128) };
//         _expectedFloatingColVector = { T(33.88727193442948), T(54.59119292006805), T(24.550731838459015) };
//         _expectedIntegralColVector = { T(31), T(49), T(20) };
//         _expectedFloatingRowVector = { T(57.753956108666344), T(27.839918694037294), T(51.239531632191486) };
//         _expectedIntegralRowVector = { T(54), T(25), T(46) };
//     }
// };
// /** @brief Test fixture for @ref fgm::Matrix4D vector multiplication, parameterized by @ref SupportedArithmeticTypes. */
// TYPED_TEST_SUITE(Matrix4DVectorMultiplication, SupportedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4DVectorFractionalMultiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix4D<T> _mat;
//     fgm::Vector4D<T> _vec, _expectedColVector, _expectedRowVector;
//
//     void SetUp() override
//     {
//         _mat = {
//             fgm::Vector4D{ T(0.1234568989329), T(0.1234214891234), T(0.12348923829) },
//             fgm::Vector4D{ T(-0.123489823149), T(-0.123489757623), T(0.89281239432) },
//             fgm::Vector4D{ T(-0.38291023892), T(0.29381938232), T(-0.0038291382) },
//         };
//         _vec = fgm::Vector4D{ T(0.8923764912287), T(0.78352829112384), T(0.234891238341) };
//
//         _expectedColVector = fgm::Vector4D{ T(-0.07652999600877063), T(0.08239631520624698), T(0.8088432317718919) };
//         _expectedRowVector = fgm::Vector4D{ T(0.2358808028522597), T(0.0027566750622143033), T(-0.11238372794829783) };
//     }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4D vector multiplication with small fractions,
//  *        parameterized by @ref SupportedFloatingPointTypes.
//  */
// TYPED_TEST_SUITE(Matrix4DVectorFractionalMultiplication, SupportedFloatingPointTypes);
//
//
// template <typename T>
// class Matrix4DMultiplication: public ::testing::Test
// {
// protected:
//     fgm::Matrix4D<T> _matA, _matB, _expectedFloatingMat, _expectedIntegralMat;
//
//     void SetUp() override
//     {
//         _matA = { fgm::Vector4D{ T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
//                   fgm::Vector4D{ T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
//                   fgm::Vector4D{ T(9.32189342348), T(8.238192312343), T(5.12398423821223) } };
//         _matB = { fgm::Vector4D{ T(3.12345678912345), T(5.12345678912345), T(1.213849123421) },
//                   fgm::Vector4D{ T(8.12345678912345), T(3.12345678912345), T(2.3218934118233) },
//                   fgm::Vector4D{ T(7.23912389492341), T(4.291238423419123), T(4.18234983241234) } };
//
//         _expectedFloatingMat = { fgm::Vector4D{ T(59.81499110074553), T(50.25262787869462), T(23.066325405048886) },
//                                  fgm::Vector4D{ T(95.51443223309786), T(81.75128018451636), T(29.872810121743093) },
//                                  fgm::Vector4D{ T(112.54098028826937), T(96.47820080937791), T(41.267951710315614) } };
//
//         _expectedIntegralMat = { fgm::Vector4D{ T(55), T(46), T(18) }, fgm::Vector4D{ T(89), T(76), T(24) },
//                                  fgm::Vector4D{ T(105), T(90), T(35) } };
//     }
// };
/** @brief Test fixture for @ref fgm::Matrix4D matrix multiplication, parameterized by @ref SupportedArithmeticTypes.
/*/
TYPED_TEST_SUITE(Matrix4DMultiplication, SupportedArithmeticTypes);


template <typename T>
class Matrix4DFractionalMultiplication: public ::testing::Test
{
protected:
    fgm::Matrix4D<T> _matA, _matB, _expectedMat;

    void SetUp() override
    {
        _matA = { { T(0.1234568989329), T(0.1234214891234), T(0.382348912394), T(0.1234923482394) },
                  { T(-0.123489823149), T(-0.123489757623), T(0.093218349323), T(0.3928192323233) },
                  { T(0.0123489823149), T(0.53489757623), T(-0.93218349323), T(0.1210348932859) },
                  { T(-0.233298321932), T(-0.53219381923), T(0.785783564256), T(0.129348321982) } };
        _matB = { { T(0.8923764912287), T(0.78352829112384), T(0.0523812349234), T(0.00382912384813) },
                  { T(0.0123412348958), T(-0.0231423489589), T(0.3829123948324), T(0.00382312343491) },
                  { T(-0.539282348958), T(0.00033423489589), T(-0.8239123948324), T(0.00382912332432) },
                  { T(0.12343211234), T(0.2134213123321), T(-0.765243234532), T(0.23457875642343) } };

        _expectedMat = { { 0.110170034287718, -0.001524016914723, -0.00665958819002, -0.028796504681444 },
                         { 0.096704228460817, 0.002857843063761, 0.000178781435703, -0.113581503315099 },
                         { 0.020027908202817, 0.035694461381593, 0.768037534330362, -0.601315556353345 },
                         { 0.000472867495705, 0.001501796412779, 0.000463457532938, 0.030342368515995 } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix4D matrix multiplication with fractional values(<1),
 *        parameterized by @ref SupportedFloatingPointTypes.
 */
TYPED_TEST_SUITE(Matrix4DFractionalMultiplication, SupportedFloatingPointTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Multiplication
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that matrix multiplication operations are available at compile time. */
namespace
{
    constexpr fgm::Matrix4D matA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    constexpr fgm::Matrix4D matB(5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21);
    constexpr fgm::Vector4D vec4D(1, 2, 3, 4);

    // Verify matrix * scalar multiplication
    // constexpr fgm::Matrix4D binaryProduct1 = matA * 2;
    // static_assert(binaryProduct1(0, 0) == 2);
    // static_assert(binaryProduct1(0, 1) == 4);
    // static_assert(binaryProduct1(0, 2) == 6);
    // static_assert(binaryProduct1(0, 3) == 8);
    // static_assert(binaryProduct1(1, 0) == 10);
    // static_assert(binaryProduct1(1, 1) == 12);
    // static_assert(binaryProduct1(1, 2) == 14);
    // static_assert(binaryProduct1(1, 3) == 16);
    // static_assert(binaryProduct1(2, 0) == 18);
    // static_assert(binaryProduct1(2, 1) == 20);
    // static_assert(binaryProduct1(2, 2) == 22);
    // static_assert(binaryProduct1(2, 3) == 24);
    // static_assert(binaryProduct1(3, 0) == 26);
    // static_assert(binaryProduct1(3, 1) == 28);
    // static_assert(binaryProduct1(3, 2) == 30);
    // static_assert(binaryProduct1(3, 3) == 32);
    //
    //
    // // Verify scalar * matrix multiplication
    // constexpr fgm::Matrix4D binaryProduct2 = 2 * matA;
    // static_assert(binaryProduct2(0, 0) == 2);
    // static_assert(binaryProduct2(0, 1) == 4);
    // static_assert(binaryProduct2(0, 2) == 6);
    // static_assert(binaryProduct2(0, 3) == 8);
    // static_assert(binaryProduct2(1, 0) == 10);
    // static_assert(binaryProduct2(1, 1) == 12);
    // static_assert(binaryProduct2(1, 2) == 14);
    // static_assert(binaryProduct2(1, 3) == 16);
    // static_assert(binaryProduct2(2, 0) == 18);
    // static_assert(binaryProduct2(2, 1) == 20);
    // static_assert(binaryProduct2(2, 2) == 22);
    // static_assert(binaryProduct2(2, 3) == 24);
    // static_assert(binaryProduct2(3, 0) == 26);
    // static_assert(binaryProduct2(3, 1) == 28);
    // static_assert(binaryProduct2(3, 2) == 30);
    // static_assert(binaryProduct2(3, 3) == 32);

    // Verify matrix * vector multiplication
    // constexpr fgm::Vector4D colVectorProduct = matA * vec4D;
    // static_assert(colVectorProduct[0] == 14);
    // static_assert(colVectorProduct[1] == 32);
    // static_assert(colVectorProduct[2] == 50);
    //
    // // Verify vector * matrix multiplication
    // constexpr fgm::Vector4D rowVectorProduct = vec4D * matA;
    // static_assert(rowVectorProduct[0] == 30);
    // static_assert(rowVectorProduct[1] == 36);
    // static_assert(rowVectorProduct[2] == 42);
    //
    // // Verify matrix * matrix multiplication
    // constexpr fgm::Matrix4D matProduct = matA * matB;
    // static_assert(matProduct(0, 0) == 57);
    // static_assert(matProduct(0, 1) == 65);
    // static_assert(matProduct(0, 2) == 71);
    // static_assert(matProduct(1, 0) == 132);
    // static_assert(matProduct(1, 1) == 152);
    // static_assert(matProduct(1, 2) == 167);
    // static_assert(matProduct(2, 0) == 207);
    // static_assert(matProduct(2, 1) == 239);
    // static_assert(matProduct(2, 2) == 263);
} // namespace



/**************************************
 *                                    *
 *     SCALAR MULTIPLICATION TESTS    *
 *                                    *
 **************************************/

/** @brief Verify that scalar multiplication by zero returns a zero matrix. */
TEST(Matrix4DScalarMultiplication, MultiplicationByZeroReturnsZeroMatrix)
{
    constexpr fgm::Matrix4D mat{ 3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,  9.0f,  10.0f,
                                 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };

    constexpr fgm::Matrix4D product = mat * 0;

    EXPECT_MAT_ZERO(product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix4DScalarMultiplication, MultiplicationByOneReturnsOriginalMatrix)
{
    constexpr fgm::Matrix4D mat{ 3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,  9.0f,  10.0f,
                                 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };

    constexpr fgm::Matrix4D product = mat * 1;

    EXPECT_MAT_EQ(mat, product);
}


/** @brief Verify that scalar multiplication by one returns original matrix. */
TEST(Matrix4DScalarMultiplication, MultiplicationByNegativeScalarFlipsSigns)
{
    constexpr fgm::Matrix4D mat = { 1.0f,  -2.0f, 3.0f,  -4.0f, 5.0f,  6.0f,  7.0f,  8.0f,
                                    -9.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };
    constexpr fgm::Matrix4D expected = { -2.0f, 4.0f,   -6.0f,  8.0f,   -10.0f, -12.0f, -14.0f, -16.0f,
                                         18.0f, -24.0f, -26.0f, -28.0f, -30.0f, -32.0f, -34.0f, -36.0f };
    constexpr float scalar = -2.0f;

    constexpr fgm::Matrix4D product = mat * scalar;

    EXPECT_MAT_EQ(expected, product);
}


/**
 * @brief Verify that the binary multiplication operator (matrix * scalar) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix4DScalarMultiplication, MatrixTimesScalarReturnsScaledMatrix)
{
    const fgm::Matrix4D product = this->_mat * this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @brief Verify that the binary multiplication operator (scalar * matrix) perform an element-wise product
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix4DScalarMultiplication, ScalarTimesAMatrixReturnsScaledMatrix)
{
    const fgm::Matrix4D product = this->_scalar * this->_mat;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, product);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, product);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) performs an element-wise product
 *        and mutates the matrix in-place.
 */
TYPED_TEST(Matrix4DScalarMultiplication, MatrixTimesEqualScalarIsTheSameMatrixScaled)
{
    this->_mat *= this->_scalar;

    if (std::is_floating_point_v<TypeParam>)
        EXPECT_MAT_EQ(this->_expectedFloatingMat, this->_mat);
    else
        EXPECT_MAT_EQ(this->_expectedIntegralMat, this->_mat);
}


/**
 * @brief Verify that the binary multiplication operator (scalar) perform automatic type promotion
 *        to the wider numeric type.
 */
TYPED_TEST(Matrix4DScalarMultiplication, MixedTypeScalarMultiplicationPromotesType)
{
    constexpr double scalar = 2.123456789123456;

    [[maybe_unused]] const fgm::Matrix4D product = this->_mat * scalar;

    static_assert(std::is_same_v<typename decltype(product)::value_type, double>);
}


/**
 * @brief Verify that the compound multiplication assignment operator (scalar) maintains the destination type and
 *        perform an implicit cast.
 */
TEST(Matrix4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentDoesNotPromoteType)
{
    fgm::Matrix4D mat = { 1.0f,  -2.0f, 3.0f,  -4.0f, 5.0f,  6.0f,  7.0f,  8.0f,
                          -9.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f };
    constexpr double scalar = 5.0;
    mat *= scalar;

    static_assert(std::is_same_v<decltype(mat)::value_type, float>);
}


/**
 * @brief Verify that the compound multiplication operator (scalar) for mixed type
 *        ensure minimal precision loss.
 */
TEST(Matrix4DScalarMultiplication, MixedTypeScalarMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
{
    fgm::Matrix4D mat = { 1, -2, 3, -4, 5, 6, 7, 8, -9, 10, 12, 13, 14, 16, 18, 20 };
    constexpr double scalar = 2.5;
    constexpr fgm::Matrix4D expected{ 2, -5, 7, -10, 12, 15, 17, 20, -22, 25, 30, 32, 35, 40, 45, 50 };

    mat *= scalar;

    EXPECT_MAT_EQ(expected, mat);
}



/**************************************
 *                                    *
 *    VECTOR MULTIPLICATION TESTS     *
 *                                    *
 **************************************/
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform linear transformation
//  *        and returns a new column vector.
//  */
// TYPED_TEST(Matrix4DVectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
// {
//     const auto transformedVector = this->_mat * this->_vec;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
//     else
//         EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new column vector.
//  */
// TYPED_TEST(Matrix4DVectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
// {
//     const auto transformedVector = this->_mat * this->_vec;
//     EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation(mat * vec) with identity matrix
//  *        and returns the original column vector.
//  */
// TEST(Matrix4DVectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
// {
//     constexpr fgm::Matrix4D<float> iMatrix;
//     constexpr fgm::vec3 vec{ 2.0f, 1.0f, 2.5 };
//
//     constexpr fgm::vec3 transformedVector = iMatrix * vec;
//
//     EXPECT_VEC_EQ(vec, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Matrix4DVectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     constexpr fgm::Matrix4D mat{ 1.0, 2.0, 3.0 };
//     constexpr fgm::iVec3 vec{ 2, 1, 3 };
//
//     [[maybe_unused]] constexpr auto transformedVector = mat * vec;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform linear transformation
//  *        and returns a new row vector.
//  */
// TYPED_TEST(Matrix4DVectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
// {
//     const auto transformedVector = this->_vec * this->_mat;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
//     else
//         EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new row vector.
//  */
// TYPED_TEST(Matrix4DVectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
// {
//     const auto transformedVector = this->_vec * this->_mat;
//     EXPECT_VEC_EQ(this->_expectedRowVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with identity matrix
//  *        and returns the original row vector.
//  */
// TEST(Matrix4DVectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
// {
//     constexpr fgm::Matrix4D<float> iMatrix;
//     constexpr fgm::vec3 vec{ 2.0f, 1.0f, 3.0f };
//
//     constexpr fgm::vec3 transformedVector = vec * iMatrix;
//
//     EXPECT_VEC_EQ(vec, transformedVector);
// }
//
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Matrix4DVectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
// {
//     constexpr fgm::Matrix4D mat{ 1.0, 2.0, 3.0 };
//     constexpr fgm::iVec3 vec{ 2, 1, 3 };
//
//     [[maybe_unused]] constexpr auto transformedVector = vec * mat;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation perform linear transformation
//  *        and mutates the vector in-place.
//  */
// TYPED_TEST(Matrix4DVectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
// {
//     auto transformedVector = this->_vec;
//     transformedVector *= this->_mat;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
//     else
//         EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation with identity matrix
//  *        does not mutate the row vector components.
//  */
// TEST(Matrix4DVectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
// {
//     constexpr fgm::Matrix4D<float> iMatrix;
//     fgm::vec3 vec{ 2.0f, 1.0f, 3.0f };
//
//     vec *= iMatrix;
//
//     EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f, 3.0f);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation maintains the destination type and
//  *        perform an implicit cast.
//  */
// TEST(Matrix4DVectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     constexpr fgm::Matrix4D<double> iMatrix;
//     [[maybe_unused]] fgm::iVec3 vec{ 2, 1, 5 };
//
//     (void) (vec *= iMatrix);
//     static_assert(std::is_same_v<decltype(vec)::value_type, int>);
// }
//
//
// /**
//  * @brief Verify that the compound multiplication operator (vector) for mixed type
//  *        ensure minimal precision loss.
//  */
// TEST(Matrix4DVectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     constexpr fgm::Matrix4D mat{ 2.5, 3.5, 0.5, 1.5, 12.0, 3.25, 5.0, 11.5, 5.0 };
//     fgm::Vector4D vec{ 10, 20, 30 };
//     constexpr fgm::Vector4D expected{ 205, 620, 220 };
//
//     vec *= mat;
//
//     EXPECT_VEC_EQ(expected, vec);
// }
//
//
//
// /**************************************
//  *                                    *
//  *    MATRIX MULTIPLICATION TESTS     *
//  *                                    *
//  **************************************/
//
// /** @brief Verify that the binary vector multiplication operation return matrix product. */
// TYPED_TEST(Matrix4DMultiplication, MatrixTimesMatrixReturnsAMatrixProduct)
// {
//     const auto transformedVector = this->_matA * this->_matB;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
//     else
//         EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
// }
//
//
// /** @brief Verify that the binary vector multiplication operation return matrix product for denormals. */
// TYPED_TEST(Matrix4DFractionalMultiplication, MatrixTimesMatrixReturnsMatrixWithPrecision)
// {
//     const auto transformedVector = this->_matA * this->_matB;
//     EXPECT_MAT_EQ(this->_expectedMat, transformedVector);
// }
//
//
// /**
//  * @brief Verify that binary matrix multiplication with identity matrix
//  *        returns original matrix.
//  */
// TEST(Matrix4DMultiplication, MultipliedByIdentityMatrixReturnsOriginalMatrix)
// {
//     constexpr fgm::Matrix4D<float> iMatrix;
//     constexpr fgm::Matrix4D mat{ 1.0f, 2.0f, 3.0f };
//
//     constexpr fgm::Matrix4D matrixProduct = iMatrix * mat;
//
//     EXPECT_MAT_EQ(mat, matrixProduct);
// }
//
//
// /**
//  * @brief Verify that the binary matrix multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Matrix4DMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     constexpr fgm::Matrix4D matA{ 1.0, 2.0, 3.0 };
//     constexpr fgm::Matrix4D matB{ 2, 1, 3 };
//
//     [[maybe_unused]] constexpr auto transformedVector = matA * matB;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /** @brief Verify that the compound vector multiplication operation perform an in-place matrix multiplication. */
// TYPED_TEST(Matrix4DMultiplication, CompoundMultiplicationOperationPerformInPlaceMatrixMultiplication)
// {
//     auto transformedVector = this->_matA;
//     transformedVector *= this->_matB;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//         EXPECT_MAT_EQ(this->_expectedFloatingMat, transformedVector);
//     else
//         EXPECT_MAT_EQ(this->_expectedIntegralMat, transformedVector);
// }
//
//
// /**
//  * @brief Verify that components matrix multiplication with identity matrix
//  *        does not mutate the calling matrix.
//  */
// TEST(Matrix4DMultiplication, TimesEqualIdentityMatrixReturnsOriginalMatrix)
// {
//     constexpr fgm::Matrix4D<float> iMatrix;
//     fgm::Matrix4D mat{ 1.0f, 2.0f, 3.0f };
//
//     mat *= iMatrix;
//     EXPECT_MAT_CONTAINS(std::vector{ 1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 3.0f }, mat);
// }
//
//
// /**
//  * @brief Verify that the compound matrix multiplication operation maintains the destination type and
//  *        perform an implicit cast.
//  */
// TEST(Matrix4DMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     constexpr fgm::Matrix4D<double> iMatrix;
//     fgm::Matrix4D mat{ 1, 2, 3 };
//
//     mat *= iMatrix;
//     static_assert(std::is_same_v<decltype(mat)::value_type, int>);
// }
//
//
// /**
//  * @brief Verify that the compound multiplication operator (matrix) for mixed type
//  *        ensure minimal precision loss.
//  */
// TEST(Matrix4DMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     constexpr fgm::Matrix4D matA{ 2.5, 3.5, 0.5, 1.5, 2.5, -12.5, 5.45, 23.25, 85.5 };
//     fgm::Matrix4D matB{ 5, 10, 15, 20, 25, 30, 35, 40, 45 };
//     constexpr fgm::Matrix4D expectedMatrix{ 109, 391, 1160, 251, 830, 2262, 392, 1268, 3365 };
//
//     matB *= matA;
//
//     EXPECT_MAT_EQ(expectedMatrix, matB);
// }
//

/** @} */