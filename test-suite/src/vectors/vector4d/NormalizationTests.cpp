/**
 * @file NormalizationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 28, 2026
 *
 * @brief Verifies @ref fgm::Vector4D normalization logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Vector4DNormalization: public ::testing::Test
{
    using R = fgm::Magnitude<T>;

    protected:
    fgm::Vector4D<T> _vec;
    fgm::Vector4D<R> _expectedUnitVec;

    void SetUp() override
    {
        _vec = { T(14), T(27), T(83), T(52) };
        _expectedUnitVec = { static_cast<R>(0.13650905255670645), static_cast<R>(0.2632674585022196),
                             static_cast<R>(0.8093036687290455), static_cast<R>(0.5070336237820525) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D normalization, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DNormalization, SupportedArithmeticTypes);


template <typename T>
class Vector4DZeroNormalization: public ::testing::Test
{
    protected:
    fgm::Vector4D<T> _vec;

    void SetUp() override
    {
        _vec = { T(0), T(0), T(0), T(0) };
    }
};
/** @brief Test fixture for @ref fgm::Vector4D zero-vector normalization, parameterized by SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DZeroNormalization, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Normalize
 * @{
 */

/**************************************
 *                                    *
 *        NORMALIZATION TESTS         *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector4D::normalize returns a unit vector. */
TYPED_TEST(Vector4DNormalization, Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->_vec.normalize();

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalizing a vector using static variant of @ref fgm::Vector4D::normalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_Normalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::normalize(this->_vec);

    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that normalization a vector using @ref fgm::Vector4D::normalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.normalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**************************************
 *                                    *
 *     SAFE NORMALIZATION TESTS       *
 *                                    *
 **************************************/

/** @test Verify that normalizing a vector using @ref fgm::Vector4D::safeNormalize returns a unit vector. */
TYPED_TEST(Vector4DNormalization, SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = this->_vec.safeNormalize();
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using @ref fgm::Vector4D::safeNormalize
 *       returns a zero-vector.
 */
TEST(Vector4DNormalization, SafeNormalize_ZeroVectorCausesDeath)
{
    constexpr fgm::Vector4D vec(0.0, 0.0, 0.0, 0.0);
    EXPECT_VEC_ZERO(vec.safeNormalize());
}


/**
 * @test Verify that normalization a vector using @ref fgm::Vector4D::safeNormalize always
 *       return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = this->_vec.safeNormalize();
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}


/**
 * @test Verify that normalizing a 4D vector using static variant of @ref fgm::Vector4D::safeNormalize
 *       returns a unit vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_NonZeroVectorReturnsUnitVector)
{
    const fgm::Vector4D normalized = fgm::Vector4D<TypeParam>::safeNormalize(this->_vec);
    EXPECT_VEC_EQ(this->_expectedUnitVec, normalized);
}


/**
 * @test Verify that attempting to normalize a zero-magnitude vector using static variant of
 *       @ref fgm::Vector4D::safeNormalize returns a zero-vector.
 */
TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_ZeroVectorCausesDeath)
{
    constexpr fgm::Vector4D vec(0.0, 0.0, 0.0, 0.0);
    EXPECT_VEC_ZERO(fgm::Vector4D<double>::safeNormalize(vec));
}


/**
 * @test Verify that the normalizing a 4D vector using static variant of @ref fgm::Vector4D::safeNormalize
 *       always return a floating-point vector.
 */
TYPED_TEST(Vector4DNormalization, StaticWrapper_SafeNormalize_NormalizedVectorIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto normalized = fgm::Vector4D<TypeParam>::safeNormalize(this->_vec);
    static_assert(std::is_floating_point_v<typename decltype(normalized)::value_type>);
}

/** @} */