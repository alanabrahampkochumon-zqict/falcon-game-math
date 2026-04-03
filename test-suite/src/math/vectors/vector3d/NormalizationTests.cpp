/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 03, 2026
 *
 * @brief Verifies @ref fgm::Vector3D normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3DTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector3DNormalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

protected:
    fgm::Vector3D<T> _vec;
    fgm::Vector3D<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec = { T(14), T(27), T(83) };
        _expectedUnitVec = { static_cast<R>(0.1583767155508236), static_cast<R>(0.30544080856230266),
                             static_cast<R>(0.9389476707655972) };
    }
};
/** @brief Test fixture for @ref fgm::Vector3D normalization, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector3DZeroNormalization: public ::testing::Test
{
protected:
    fgm::Vector3D<T> _vec;

    void SetUp() override
    {
        _vec = { T(0), T(0), T(0) };
    }
};
/**
 * @brief Test fixture for @ref fgm::Vector3D zero-vector normalization, parameterized by
 *        @ref SupportedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vector3DZeroNormalization, SupportedArithmeticTypes);


/** @brief Test fixture for @fgm::Vector3D normalization with NaN vectors. */
class Vector3DNormalizationNaNTests: public ::testing::TestWithParam<fgm::Vector3D<float>>
{};
INSTANTIATE_TEST_SUITE_P(Vector3DNormalizationNaNTestSuite, Vector3DNormalizationNaNTests,
                         ::testing::Values(fgm::Vector3D<float>(fgm::constants::NaN, 1.0f, 1.0f),
                                           fgm::Vector3D<float>(1.0f, fgm::constants::NaN, 1.0f),
                                           fgm::Vector3D<float>(1.0f, 1.0f, fgm::constants::NaN),
                                           fgm::Vector3D<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN)));



/**
 * @addtogroup T_FGM_Vec3_Normalize
 * @{
 */

/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector3D::normalize returns a unit vector. */
TYPED_TEST(Vector3DNormalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector3D normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using static variant of @ref fgm::Vector3D::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector3DNormalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector3D normalized = fgm::Vector3D<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using @ref fgm::Vector3D::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector3DNormalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}

//
///**************************************
// *                                    *
// *     SAFE NORMALIZATION TESTS       *
// *                                    *
// **************************************/
//
///** @test Verify that normalizing a vector using @ref fgm::Vector3D::safeNormalize returns a unit vector. */
//TYPED_TEST(Vector3DNormalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
//{
//    const fgm::Vector3D normalized = this->_vec.safeNormalize();
//    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
//}
//
//
///**
// * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector3D::safeNormalize
// *       returns a zero-vector.
// */
//TYPED_TEST(Vector3DNormalization, SafeNormalize_ZeroVectorReturnsZeroVector)
//{
//    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>.safeNormalize());
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vector3D::safeNormalize
// *       returns a zero-vector.
// */
//TEST(Vector3DNormalization, SafeNormalize_NaNVectorReturnsZeroVector)
//{
//    EXPECT_VEC_ZERO(fgm::vec4d::nan<float>.safeNormalize());
//}
//
//
///**
// * @test Verify that normalizing a vector using @ref fgm::Vector3D::safeNormalize always
// *       return a floating-point vector.
// */
//TYPED_TEST(Vector3DNormalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
//{
//    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
//    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
//}
//
//
///**
// * @test Verify that normalizing a 4D vector using static variant of @ref fgm::Vector3D::safeNormalize
// *       returns a unit vector.
// */
//TYPED_TEST(Vector3DNormalization, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
//{
//    const fgm::Vector3D normalized = fgm::Vector3D<TypeParam>::safeNormalize(this->_vec);
//    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
//}
//
//
///**
// * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
// *       @ref fgm::Vector3D::safeNormalize returns a zero-vector.
// */
//TYPED_TEST(Vector3DNormalization, StaticWrapper_SafeNormalize_ZeroVectorReturnsZeroVector)
//{
//    EXPECT_VEC_ZERO(fgm::Vector3D<double>::safeNormalize(fgm::vec4d::zero<TypeParam>));
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3D::safeNormalize
// *       returns a zero-vector.
// */
//TEST(Vector3DNormalization, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
//{
//    EXPECT_VEC_ZERO(fgm::Vector3D<float>::safeNormalize(fgm::vec4d::nan<float>));
//}
//
//
///**
// * @test Verify that the normalizing a 4D vector using static variant of @ref fgm::Vector3D::safeNormalize
// *       always return a floating-point vector.
// */
//TYPED_TEST(Vector3DNormalization, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
//{
//    [[maybe_unused]] const auto normalized = fgm::Vector3D<TypeParam>::safeNormalize(this->_vec);
//    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
//}
//
//
///**************************************
// *                                    *
// *      TRY NORMALIZATION TESTS       *
// *                                    *
// **************************************/
//
///**
// * @test Verify that normalizing a vector using @ref fgm::Vector3D::tryNormalize
// *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
// */
//TYPED_TEST(Vector3DNormalization, TryNormalize_NonZeroVectorReturnsUnitVector)
//{
//    fgm::OperationStatus flag;
//    const fgm::Vector3D normalized = this->_vec.tryNormalize(flag);
//
//    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector3D::tryNormalize
// *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
// */
//TYPED_TEST(Vector3DNormalization, TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>.tryNormalize(flag));
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector using @ref fgm::Vector3D::tryNormalize
// *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TEST(Vector3DNormalization, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    EXPECT_VEC_ZERO(fgm::vec4d::nan<float>.tryNormalize(flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that normalizing a vector using @ref fgm::Vector3D::tryNormalize always
// *       return a floating-point vector.
// */
//TYPED_TEST(Vector3DNormalization, TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
//{
//    [[maybe_unused]] fgm::OperationStatus flag;
//    [[maybe_unused]] const auto normalized = this->_vec.tryNormalize(flag);
//    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
//}
//
//
///**
// * @test Verify that normalizing a 4D vector using static variant of @ref fgm::Vector3D::tryNormalize
// *       returns a unit vector and sets the flag to @ref fgm::OperationStatus::SUCCESS.
// */
//TYPED_TEST(Vector3DNormalization, StaticWrapper_TryNormalize_NonZeroVectorReturnsUnitVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const fgm::Vector3D normalized = fgm::Vector3D<TypeParam>::tryNormalize(this->_vec, flag);
//
//    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
//    EXPECT_EQ(fgm::OperationStatus::SUCCESS, flag);
//}
//
//
///**
// * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
// *       @ref fgm::Vector3D::tryNormalize returns a zero-vector and
// *       sets the flag to @ref fgm::OperationStatus::DIVISIONBYZERO.
// */
//TYPED_TEST(Vector3DNormalization, StaticWrapper_TryNormalize_ZeroVectorReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>.tryNormalize(flag));
//    EXPECT_EQ(fgm::OperationStatus::DIVISIONBYZERO, flag);
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3D::tryNormalize
// *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TEST(Vector3DNormalization, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    EXPECT_VEC_ZERO(fgm::Vector3D<float>::tryNormalize(fgm::vec4d::nan<float>, flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that the normalizing a 4D vector using static variant of @ref fgm::Vector3D::tryNormalize
// *       always return a floating-point vector.
// */
//TYPED_TEST(Vector3DNormalization, StaticWrapper_TryNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
//{
//    [[maybe_unused]] fgm::OperationStatus flag;
//    [[maybe_unused]] const auto normalized = fgm::Vector3D<TypeParam>::tryNormalize(this->_vec, flag);
//    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
//}
//
//
///**************************************
// *                                    *
// *      NAN NORMALIZATION TESTS       *
// *                                    *
// **************************************/
//
///**
// * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vector3D::safeNormalize
// *       returns a zero-vector.
// */
//TEST_P(Vector3DNormalizationNaNTests, SafeNormalize_NaNVectorReturnsZeroVector)
//{
//    const auto& vec = GetParam();
//
//    EXPECT_VEC_ZERO(vec.safeNormalize());
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3D::safeNormalize
// *       returns a zero-vector.
// */
//TEST_P(Vector3DNormalizationNaNTests, StaticWrapper_SafeNormalize_NaNVectorReturnsZeroVector)
//{
//    const auto& vec = GetParam();
//
//    EXPECT_VEC_ZERO(fgm::Vector3D<ParamType::value_type>::safeNormalize(vec));
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector of @ref fgm::Vector3D::tryNormalize
// *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TEST_P(Vector3DNormalizationNaNTests, TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto& vec = GetParam();
//
//    EXPECT_VEC_ZERO(vec.tryNormalize(flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}
//
//
///**
// * @test Verify that attempting to normalize a NaN vector using static variant of @ref fgm::Vector3D::tryNormalize
// *       returns a zero-vector and sets the flag to @ref fgm::OperationStatus::NANOPERAND.
// */
//TEST_P(Vector3DNormalizationNaNTests, StaticWrapper_TryNormalize_NaNVectorReturnsZeroVectorAndSetsCorrectFlag)
//{
//    fgm::OperationStatus flag;
//    const auto& vec = GetParam();
//
//    EXPECT_VEC_ZERO(fgm::Vector3D<ParamType::value_type>::tryNormalize(vec, flag));
//    EXPECT_EQ(fgm::OperationStatus::NANOPERAND, flag);
//}

/** @} */