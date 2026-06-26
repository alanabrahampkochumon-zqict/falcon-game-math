/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Matrix3 utility functions.
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
struct Matrix3UtilityParams
{
    fgm::Matrix3<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix3 infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix3InfChecker: public ::testing::TestWithParam<Matrix3UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix3 NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix3NaNChecker: public ::testing::TestWithParam<Matrix3UtilityParams<float>>
{};


template <typename T>
class Matrix3IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix3 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Matrix3IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Matrix3 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f);
    constexpr fgm::Matrix3 MAT(1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Matrix3<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Matrix3<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Matrix3<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix3::hasInf returns `true` if any of elements are IEE754 infinity
 *        and False otherwise.
 */
TEST_P(Matrix3InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix3InfCheckerTestSuite, Matrix3InfChecker,
    ::testing::Values(Matrix3UtilityParams{ fgm::Matrix3(fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Matrix3UtilityParams{ fgm::Matrix3(1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Matrix3UtilityParams{ fgm::Matrix3(1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Matrix3UtilityParams{ fgm::Matrix3(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F),
                                             true },
                      Matrix3UtilityParams{ fgm::Matrix3(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix3::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix3IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3(value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix3::hasInf returns `true` if any of elements are IEE754
 *        infinity and False otherwise.
 */
TEST_P(Matrix3InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix3<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix3::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix3IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3<TypeParam>::hasInf(fgm::Matrix3(value, value, value)));
}



/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix3::hasNaN returns `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Matrix3NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix3NaNCheckerTestSuite, Matrix3NaNChecker,
    ::testing::Values(Matrix3UtilityParams{ fgm::Matrix3(fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix3UtilityParams{ fgm::Matrix3(1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix3UtilityParams{ fgm::Matrix3(1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix3UtilityParams{
                          fgm::Matrix3(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN), true },
                      Matrix3UtilityParams{ fgm::Matrix3(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix3::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix3IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3(value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix3::hasNaN returns `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Matrix3NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix3<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix3::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix3IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3<TypeParam>::hasNaN(fgm::Matrix3(value, value, value)));
}

/** @} */
