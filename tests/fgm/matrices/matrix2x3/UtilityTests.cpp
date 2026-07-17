/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm:: Matrix2x3 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Matrix2x3TestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Matrix2x3UtilityParams
{
    fgm::Matrix2x3<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix2x3 infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix2x3InfChecker: public ::testing::TestWithParam<Matrix2x3UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix2x3 NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix2x3NaNChecker: public ::testing::TestWithParam<Matrix2x3UtilityParams<float>>
{};


template <typename T>
class Matrix2x3IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix2x3 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Matrix2x3IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat2x3_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Matrix2x3 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Matrix2x3 MAT(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        /// Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Matrix2x3<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Matrix2x3<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Matrix2x3<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Matrix2x3::hasInf returns  `true` if any of elements are IEE754 infinity
 *        and `false` otherwise.
 */
TEST_P(Matrix2x3InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix2x3InfCheckerTestSuite, Matrix2x3InfChecker,
    ::testing::Values(
        Matrix2x3UtilityParams{ fgm::Matrix2x3(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f, 1.0f), true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                               fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                               fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                true },
        Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std:: Matrix2x3::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix2x3IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2x3(value, value, value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std:: Matrix2x3::hasInf returns  `true` if any of elements are IEE754
 *        infinity and `false` otherwise.
 */
TEST_P(Matrix2x3InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix2x3<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std:: Matrix2x3::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix2x3IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2x3<TypeParam>::hasInf(fgm::Matrix2x3(value, value, value, value, value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std:: Matrix2x3::hasNaN returns  `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Matrix2x3NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix2x3NaNCheckerTestSuite, Matrix2x3NaNChecker,
    ::testing::Values(Matrix2x3UtilityParams{ fgm::Matrix2x3(fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f, 1.0f), true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(fgm::constants::NaN, fgm::constants::NaN,
                                                             fgm::constants::NaN, fgm::constants::NaN,
                                                             fgm::constants::NaN, fgm::constants::NaN),
                                              true },
                      Matrix2x3UtilityParams{ fgm::Matrix2x3(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std:: Matrix2x3::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix2x3IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2x3(value, value, value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std:: Matrix2x3::hasNaN returns  `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Matrix2x3NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix2x3<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std:: Matrix2x3::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix2x3IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2x3<TypeParam>::hasNaN(fgm::Matrix2x3(value, value, value, value, value, value)));
}

/** @} */
