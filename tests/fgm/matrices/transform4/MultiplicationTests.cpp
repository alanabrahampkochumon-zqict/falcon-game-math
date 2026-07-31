/**
 * @file MultiplicationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 31, 2026
 *
 * @brief Verify @ref fgm::Transform4 multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Transform4TestSetup.h"


/**
 * @addtogroup T_FGM_Transform4_Multiplication
 * @{
 */

namespace
{

    /**************************************
     *                                    *
     *             TEST SETUP             *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Transform4 transform(matrix) multiplication.
     *
     * @tparam T The scalar type (e.g., uint32_t, int32_t, float, double) used for the values.
     */
    template <typename T>
    class Transform4TransformMultiplication: public testing::Test
    {
    protected:
        fgm::Transform4<T> _transformA, _transformB, _expectedFPTransform, _expectedIntTransform;

        void SetUp() override
        {
            _transformA = {
                { T(7.12345678912345), T(6.12345678912345), T(1.2389123488213) },
                { T(5.12345678912345), T(4.12345678912345), T(2.53283924821338) },
                { T(1.32189342348), T(8.238192312343), T(5.12398423821223) },
                { T(4.8934233348), T(1.9233212312343), T(4.3984231212233) },
            };
            _transformB = {
                { T(3.12345678912345), T(5.12345678912345), T(1.213849123421) },
                { T(8.12345678912345), T(3.12345678912345), T(2.3218934118233) },
                { T(7.23912389492341), T(4.291238423419123), T(4.18234983241234) },
                { T(5.932123894923), T(3.338423419123), T(7.3498324123324) },
            };

            _expectedFPTransform  = { { T(50.10419811337752805), T(50.25262787869461789), T(23.06632540504888595) },
                                      { T(76.93928493851146300), T(81.75128018451636080), T(29.87281012174309325) },
                                      { T(79.08218162897063053), T(96.47820080937790976), T(41.26795171031561438) },
                                      { T(73.97061482922748610), T(112.56360315835962638), T(57.86391996678334948) } };
            _expectedIntTransform = { { 47, 46, 18 }, { 73, 76, 24 }, { 73, 90, 35 }, { 61, 99, 50 }

            };
        }
    };
    TYPED_TEST_SUITE(Transform4TransformMultiplication, SupportedArithmeticTypes);


    // template <typename T>
    // class Transform4VectorMultiplication: public testing::Test
    // {
    // protected:
    //     fgm::Transform4<T> _mat;
    //     fgm::Vec4<T> _vec;
    //     fgm::Vec4<T> _expectedFloatingColVector, _expectedIntegralColVector, _expectedFloatingRowVector,
    //         _expectedIntegralRowVector;
    //
    //     void SetUp() override
    //     {
    //         _mat = { fgm::Vec4{ T(7.12345678912345), T(13.12345678912345), T(1.32893912338), T(1.2384912349) },
    //                  fgm::Vec4{ T(5.12345678912345), T(4.12345678912345), T(3.3129381239321), T(3.2983192312) },
    //                  fgm::Vec4{ T(2.238929123125), T(11.238924194839), T(9.2389291239898), T(8.2813941329) },
    //                  fgm::Vec4{ T(7.32129123125), T(8.2314213412), T(2.2323329898), T(3.12343151324) } };
    //         _vec = { T(2.123456789123456), T(3.123456832912), T(1.2318492394128), T(4.18293482134) };
    //         _expectedFloatingColVector = { T(64.5117559627963), T(89.02269187729473), T(33.888435234319466),
    //                                        T(36.19857986352777) };
    //         _expectedIntegralColVector = { T(59), T(81), T(28), T(31) };
    //         _expectedFloatingRowVector = { T(62.93448422105393), T(41.636573058119154), T(85.88006351993967),
    //                                        T(57.07194293730016) };
    //         _expectedIntegralRowVector = { T(58), T(37), T(78), T(52) };
    //     }
    // };
    // /** @brief Test fixture for @ref fgm::Transform4 vector multiplication, parameterized by @ref
    //  * SupportedArithmeticTypes.
    //  */
    // TYPED_TEST_SUITE(Transform4VectorMultiplication, SupportedArithmeticTypes);
    //
    //
    // template <typename T>
    // class Transform4VectorFractionalMultiplication: public testing::Test
    // {
    // protected:
    //     fgm::Transform4<T> _mat;
    //     fgm::Vec4<T> _vec, _expectedColVector, _expectedRowVector;
    //
    //     void SetUp() override
    //     {
    //         _mat = { { T(0.1234568989329), T(0.1234214891234), T(0.12348923829), T(0.0893829192) },
    //                  { T(-0.123489823149), T(-0.123489757623), T(0.89281239432), T(0.00123849123) },
    //                  { T(-0.38291023892), T(0.29381938232), T(-0.0038291382), T(0.000832891234231) },
    //                  { T(0.58291023892), T(0.6381938232), T(-0.000291382), T(0.008391234231) } };
    //         _vec = fgm::Vec4{ T(0.8923764912287), T(0.78352829112384), T(0.234891238341), T(-0.9382938123) };
    //
    //         _expectedColVector =
    //             fgm::Vec4{ T(-0.623471066313721), T(-0.516417000150393), T(0.809116633699507), T(0.073055804425393)
    //             };
    //         _expectedRowVector =
    //             fgm::Vec4{ T(0.152013362841589), T(0.001594606404517), T(-0.113165224639696), T(1.012276423171081) };
    //     }
    // };
    // /**
    //  * @brief Test fixture for @ref fgm::Transform4 vector multiplication with small fractions,
    //  *        parameterized by @ref SupportedFloatingPointTypes.
    //  */
    // TYPED_TEST_SUITE(Transform4VectorFractionalMultiplication, SupportedFloatingPointTypes);




    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Transform4 TRANSFORM_A(7, 5, 1, 4, 6, 4, 8, 1, 1, 2, 5, 4);
        constexpr fgm::Transform4 TRANSFORM_B(3, 8, 7, 5, 5, 3, 4, 3, 1, 2, 4, 7);


        /// @test Verify that Transform4 * Transform4 returns a valid Transform4 at compile time.
        constexpr auto TRANSFORM_MAT_MUL = TRANSFORM_A * TRANSFORM_B;
        static_assert(TRANSFORM_MAT_MUL[0] == fgm::Vec3{ 47, 46, 18 });
        static_assert(TRANSFORM_MAT_MUL[1] == fgm::Vec3{ 73, 76, 24 });
        static_assert(TRANSFORM_MAT_MUL[2] == fgm::Vec3{ 73, 90, 35 });
        static_assert(TRANSFORM_MAT_MUL[3] == fgm::Vec3{ 61, 99, 50 });

        // constexpr fgm::Transform4 mat2(5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21);
        // constexpr fgm::Vec4 vec4D(1, 2, 3, 4);
        //
        // // Verify matrix * scalar multiplication
        // constexpr fgm::Transform4 binaryProduct1 = mat1 * 2;
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
        // constexpr fgm::Transform4 binaryProduct2 = 2 * mat1;
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
        //
        // // TODO: Add static tests
        // // Verify matrix * vector multiplication
        // constexpr fgm::Vec4 colVectorProduct = mat1 * vec4D;
        // static_assert(colVectorProduct[0] == 30);
        // static_assert(colVectorProduct[1] == 70);
        // static_assert(colVectorProduct[2] == 110);
        // static_assert(colVectorProduct[3] == 150);
        //
        // // Verify vector * matrix multiplication
        // constexpr fgm::Vec4 rowVectorProduct = vec4D * mat1;
        // static_assert(rowVectorProduct[0] == 90);
        // static_assert(rowVectorProduct[1] == 100);
        // static_assert(rowVectorProduct[2] == 110);
        // static_assert(rowVectorProduct[3] == 120);
        //
        // // Verify matrix * matrix multiplication
        // constexpr fgm::Transform4 matProduct = mat1 * mat2;
        // static_assert(matProduct(0, 0) == 139);
        // static_assert(matProduct(0, 1) == 149);
        // static_assert(matProduct(0, 2) == 159);
        // static_assert(matProduct(0, 3) == 169);
        // static_assert(matProduct(1, 0) == 327);
        // static_assert(matProduct(1, 1) == 353);
        // static_assert(matProduct(1, 2) == 379);
        // static_assert(matProduct(1, 3) == 405);
        // static_assert(matProduct(2, 0) == 515);
        // static_assert(matProduct(2, 1) == 557);
        // static_assert(matProduct(2, 2) == 599);
        // static_assert(matProduct(2, 3) == 641);
        // static_assert(matProduct(3, 0) == 703);
        // static_assert(matProduct(3, 1) == 761);
        // static_assert(matProduct(3, 2) == 819);
        // static_assert(matProduct(3, 3) == 877);
    } // namespace static_tests

} // namespace

//
//
//
// /**************************************
//  *                                    *
//  *    VECTOR MULTIPLICATION TESTS     *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform linear transformation
//  *        and returns a new column vector.
//  */
// TYPED_TEST(Transform4VectorMultiplication, MatrixTimesVectorReturnsATransformedVector)
// {
//     const auto transformedVector = this->_mat * this->_vec;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingColVector, transformedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralColVector, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new column vector.
//  */
// TYPED_TEST(Transform4VectorFractionalMultiplication, MatrixTimesVectorReturnsATransformedVectorWithPrecision)
// {
//     const auto transformedVector = this->_mat * this->_vec;
//     EXPECT_VEC_EQ(this->_expectedColVector, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation(mat * Vec) with identity matrix
//  *        and returns the original column vector.
//  */
// TEST(Transform4VectorMultiplication, IdentityMatrixTimesVectorReturnsOriginalVector)
// {
//     const fgm::Transform4<float> iMatrix = fgm::Transform4<float>::identity();
//     const fgm::Vec4F vec{ 2.0f, 1.0f, 2.5f, 12.5f };
//
//     const fgm::Vec4F transformedVector = iMatrix * vec;
//
//     EXPECT_VEC_EQ(vec, transformedVector);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform automatic type promotion
//  *        to the wider numeric type.
//  */
// TEST(Transform4VectorMultiplication, MatTimesVec_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Transform4 mat{ 1.0, 2.0, 3.0, 4.0 };
//     const fgm::Vec4I vec{ 2, 1, 3, 4 };
//
//     [[maybe_unused]] const auto transformedVector = mat * vec;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation perform linear transformation
//  *        and returns a new row vector.
//  */
// TYPED_TEST(Transform4VectorMultiplication, VectorTimesMatrixReturnsATransformedVector)
// {
//     const auto transformedVector = this->_vec * this->_mat;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that the binary vector multiplication operation with fractional values perform linear transformation
//  *        and returns a new row vector.
//  */
// TYPED_TEST(Transform4VectorFractionalMultiplication, VectorTimesMatrixReturnsATransformedVectorWithPrecision)
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
// TEST(Transform4VectorMultiplication, VectorTimesIdentityMatrixReturnsOriginalVector)
// {
//     const fgm::Transform4<float> iMatrix = fgm::Transform4<float>::identity();
//     const fgm::Vec4F vec{ 2.0f, 1.0f, 2.5f, 12.5f };
//
//     const fgm::Vec4F transformedVector = vec * iMatrix;
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
// TEST(Transform4VectorMultiplication, VecTimesMat_MixedTypeScalarMultiplicationPromotesType)
// {
//     const fgm::Transform4 mat{ 1.0, 2.0, 3.0, 4.0 };
//     const fgm::Vec4I vec{ 2, 1, 3, 4 };
//
//     [[maybe_unused]] const auto transformedVector = vec * mat;
//     static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation perform linear transformation
//  *        and mutates the vector in-place.
//  */
// TYPED_TEST(Transform4VectorMultiplication, VectorTimesEqualMatrixReturnsATransformedVector)
// {
//     auto transformedVector = this->_vec;
//     transformedVector *= this->_mat;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFloatingRowVector, transformedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntegralRowVector, transformedVector);
//     }
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation with identity matrix
//  *        does not mutate the row vector components.
//  */
// TEST(Transform4VectorMultiplication, VectorTimesEqualIdentityMatrixReturnsOriginalVector)
// {
//     const fgm::Transform4<float> iMatrix = fgm::Transform4<float>::identity();
//     fgm::Vec4F vec{ 2.0f, 1.0f, 3.0f, 12.0f };
//
//     vec *= iMatrix;
//
//     EXPECT_VEC_CONTAINS(vec, 2.0f, 1.0f, 3.0f, 12.0f);
// }
//
//
// /**
//  * @brief Verify that the compound vector multiplication operation maintains the destination type and
//  *        perform an implicit cast.
//  */
// TEST(Transform4VectorMultiplication, MixedTypeVectorMultiplicationAssignmentDoesNotPromoteType)
// {
//     const fgm::Transform4<double> iMatrix = fgm::Transform4<double>::identity();
//     [[maybe_unused]] fgm::Vec4I vec{ 2, 1, 5, 4 };
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
// TEST(Transform4VectorMultiplication, MixedTypeVectorMultiplicationAssignmentEnsuresMinimalPrecisionLoss)
// {
//     const fgm::Transform4 mat{ 2.5, 3.5,  0.5,  1.5,   12.0, 3.25, 5.0,   11.5,
//                                5.0, 20.0, 12.0, 12.25, 15.0, 16.0, 13.75, 15.5 };
//     fgm::Vec4 vec{ 10, 20, 30, 40 };
//     const fgm::Vec4 expected{ 1015, 1340, 1015, 1232 };
//
//     vec *= mat;
//
//     EXPECT_VEC_EQ(expected, vec);
// }
//
//

/**************************************
 *                                    *
 *    MATRIX MULTIPLICATION TESTS     *
 *                                    *
 **************************************/

TYPED_TEST(Transform4TransformMultiplication, TimesOperator_ReturnsValidTransformMatrix)
{
    const auto transformResult = this->_transformA * this->_transformB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPTransform, transformResult);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntTransform, transformResult);
    }
}


TEST(Transform4TransformMultiplication, TimesOperator_MixedTypes_PromotesToWiderType)
{
    const fgm::Transform4 transformA{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    const fgm::Transform4 transformB{ 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    [[maybe_unused]] const auto transformedVector = transformA * transformB;
    static_assert(std::is_same_v<decltype(transformedVector)::value_type, double>);
}


TYPED_TEST(Transform4TransformMultiplication, TimesEqualOperator_MutatesCurrentTransformMatrix)
{
    this->_transformA *= this->_transformB;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPTransform, this->_transformA);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntTransform, this->_transformA);
    }
}


TEST(Transform4TransformMultiplication, TimesEqualOperator_MixedTypes_DoesNotPromotesToWiderType)
{
    fgm::Transform4 transformA{ 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    const fgm::Transform4 transformB{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

    transformA *= transformB;
    static_assert(std::is_same_v<decltype(transformA)::value_type, int>);
}

/** @} */
