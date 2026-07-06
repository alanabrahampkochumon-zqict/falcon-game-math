/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 14, 2026
 *
 * @brief Verify @ref fgm::Matrix2 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <MatrixTestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Matrix2UtilityParams
{
    fgm::Matrix2<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix2 infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix2InfChecker: public ::testing::TestWithParam<Matrix2UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix2 NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix2NaNChecker: public ::testing::TestWithParam<Matrix2UtilityParams<float>>
{};


template <typename T>
class Matrix2IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix2 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Matrix2IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat2x2_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Matrix2 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Matrix2 MAT(1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        /// Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Matrix2<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Matrix2<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Matrix2<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix2::hasInf returns  `true` if any of elements are IEE754 infinity
 *        and `false` otherwise.
 */
TEST_P(Matrix2InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix2InfCheckerTestSuite, Matrix2InfChecker,
    ::testing::Values(Matrix2UtilityParams{ fgm::Matrix2(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Matrix2UtilityParams{ fgm::Matrix2(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                         fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                            true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix2::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix2IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2(value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix2::hasInf returns  `true` if any of elements are IEE754
 *        infinity and `false` otherwise.
 */
TEST_P(Matrix2InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix2<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix2::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix2IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2<TypeParam>::hasInf(fgm::Matrix2(value, value)));
}


/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix2::hasNaN returns  `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Matrix2NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix2NaNCheckerTestSuite, Matrix2NaNChecker,
    ::testing::Values(Matrix2UtilityParams{ fgm::Matrix2(fgm::constants::NaN, 1.0f), true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix2UtilityParams{ fgm::Matrix2(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN,
                                                         fgm::constants::NaN),
                                            true },
                      Matrix2UtilityParams{ fgm::Matrix2(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix2::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix2IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2(value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix2::hasNaN returns  `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Matrix2NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix2<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix2::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix2IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix2<TypeParam>::hasNaN(fgm::Matrix2(value, value)));
}

/** @} */
